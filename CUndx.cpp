#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<cfloat>
#include<cstring>
#include<memory>
#include<algorithm>

#include"mseq.h"
#include"cdfrand.h"
#include"CRealCodedGa.h"
#include"CUndx.h"

CUndx::CUndx()
{
	iCrossOverNum = 0;
	lfAlpha = 0.0;
	lfBeta = 0.0;
	iParentOutputFlag = 0;
	iChildrenOutputFlag = 0;
	iChildrenNumber = 0;
	pplfChildren = NULL;
	plfChild1 = NULL;
	plfChild2 = NULL;
}

CUndx::~CUndx()
{
}

void CUndx::vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData, int iCrossOverNumData )
{
	int i;
	CUndxException cue;

	// �����lGA�̏����������s���܂��B
	CRealCodedGa::vInitialize( iGenerationNum, iGenNum, iGenVectorData );

	// �����񐔂�ݒ肵�܂��B
	iCrossOverNum = iCrossOverNumData;

	// �ő�ō쐬�����q���̌���ݒ肵�܂��B
	iChildrenNumber = iCrossOverNum * 2 + 2;
	try
	{
		// �q���̃f�[�^���쐬���܂��B
		pplfChildren = new double*[iChildrenNumber];
		if( pplfChildren == NULL )
		{
			cue.SetErrorInfo( UNDX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CUndx", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cue );
		}
		for( i = 0;i < iChildrenNumber; i++ )
		{
			pplfChildren[i] = new double[iGenVector];
			if( pplfChildren[i] == NULL )
			{
				cue.SetErrorInfo( UNDX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CUndx", "�������m�ۂɎ��s���܂����B", __LINE__ );
				throw( cue );
			}
		}
		
		for( i = 0;i < iChildrenNumber; i++ )
		{
			memset( pplfChildren[i], 0, iGenVector*sizeof(double) );
		}

		plfChild1 = new double[iGenVector];
		plfChild2 = new double[iGenVector];
		for( i = 0;i < iGenVector; i++ )
		{
			plfChild1[i] = 0.0;
			plfChild2[i] = 0.0;
		}
		initrand( (unsigned long)time(NULL) );
		initrnd();
	}
	catch( std::bad_alloc ba )
	{
		cue.SetErrorInfo( UNDX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CUndx", "�������m�ۂɎ��s���܂����B", __LINE__ );
		throw( cue );
	}
	catch( ... )
	{
		cue.SetErrorInfo( UNDX_ARRAY_INDEX_ERROR, "vInitialize", "CUndx", "�z��͈͊O���Q�Ƃ��܂����B", __LINE__ );
		throw( cue );
	}
}

void CUndx::vTerminate()
{
	int i;
	CUndxException cue;

	try
	{
		// �p�����N���X�ɑ����郁���o�ϐ��̏I�����������s���܂��B
		CRealCodedGa::vTerminate();

		// �I�����������s���܂��B
		if( pplfChildren != NULL )
		{
			for( i = 0;i < iChildrenNumber; i++ )
			{
				if( pplfChildren[i] != NULL )
				{
					delete[] pplfChildren[i];
					pplfChildren[i] = NULL;
				}
			}
			delete[] pplfChildren;
			pplfChildren = NULL;
		}
		if( plfChild1 != NULL )
		{
			delete[] plfChild1;
			plfChild1 = NULL;
		}
		if( plfChild2 != NULL )
		{	
			delete[] plfChild2;
			plfChild2 = NULL;
		}
	}
	catch( ... )
	{
		cue.SetErrorInfo( UNDX_MEMORY_RELEASE_ERROR, "vTerminate", "CUndx", "�m�ۂ����������̉���Ɏ��s���܂����B", __LINE__ );
		throw( cue );
	}
}

void CUndx::vImplement()
{
	CUndxException cundxe;
	int i,j;
	int i1,i2,i3;
	int i1stGenLoc;
	int i2ndGenLoc;
	double *plfParent1 = NULL;
	double *plfParent2 = NULL;
	double *plfParent3 = NULL;

	double lfPrevProb = 0.0;
	double lfProb = 0.0;

	try
	{
		for( i = 0;i < iCrossOverNum; i++ )
		{
			// UNDX��2�̐e��I�����܂��B
			vSelectParent( &plfParent1, &plfParent2, &plfParent3, &i1, &i2, &i3 );
			
			// �����ŁA�t���O���L���ɂȂ��Ă���ꍇ�Ɍ���e���o�͂��܂��B
			vOutputCurrentParent( plfParent1, plfParent2 );
		
			// UNDX�����s���܂��B
			vUndx( plfParent1, plfParent2, plfParent3, lfAlpha, lfBeta, plfChild1, plfChild2 );

			// ���������q����ǉ����܂��B
			for( j = 0;j < iGenVector; j++ )
			{
				pplfChildren[2*i][j] = plfChild1[j];
				pplfChildren[2*i+1][j] = plfChild2[j];
			}
		}
		// �Ō�ɐe�����̏W�c�ɒǉ����܂��B
		for( j = 0;j < iGenVector; j++ )
		{
			pplfChildren[2*iCrossOverNum][j] = plfParent1[j];
			pplfChildren[2*iCrossOverNum+1][j] = plfParent2[j];
		}

		// �����ŁA�t���O���L���ɂȂ��Ă���ꍇ�Ɍ���q���o�͂��܂��B
		vOutputCurrentChildren( pplfChildren );
		
	// ����������{���܂��B2�̂悢��`�q��I�����܂�

		// �ł��]���l�̂悢��`�q�ƁA���[���b�g�I���ɂ�茈�肵����`�q��I�����܂��B
		vSelectGens( pplfChildren, &i1stGenLoc, &i2ndGenLoc );

		// ����I�������e�Ǝq���������܂��B
		for( j = 0;j < iGenVector; j++ )
		{
			pplfGens[i1][j] = pplfChildren[i1stGenLoc][j];
			pplfGens[i2][j] = pplfChildren[i2ndGenLoc][j];
		}
		// �ꎞ�I�ɕێ����Ă����q�̏W�����폜���܂��B
		for(i = 0;i < iChildrenNumber; i++ )
		{
			memset( pplfChildren[i], 0, iGenVector*sizeof(double) );
		}
	}
	catch( ... )
	{
		cundxe.SetErrorInfo( UNDX_ARRAY_INDEX_ERROR, "vImplement", "CUndx", "�z��͈͊O�Q�Ƃ����܂����B", __LINE__ );
		throw( cundxe );
	}
}

void CUndx::vSelectParent( double **pplfParent1, double **pplfParent2, double **pplfParent3, int *piLoc1, int *piLoc2, int *piLoc3 )
{
	int i;
	int i1 = 0;
	int i2 = 0;
	int i3 = 0;
	double lfSumAbs1 = 0.0;
	double lfSumAbs2 = 0.0;
	// UNDX���s���e��2���肵�܂��B
	i1 = mrand() % iGenNumber;
	for(;;)
	{
	  // �d�Ȃ�Ȃ��悤�ɂ��܂��B
		i2 = mrand() % iGenNumber;
		if( i1 != i2 )
		{
			lfSumAbs1 = 0.0;
			for( i = 0;i < iGenVector; i++ )
			{
				lfSumAbs1 += fabs((pplfGens[i1][i] - pplfGens[i2][i])*(pplfGens[i1][i] - pplfGens[i2][i]));
			}
			if( lfSumAbs1 > 0.00000001 )
			{
				break;
			}
		}
	}
	// ��O�̐e���I�����܂��B
	for(;;)
	{
	  // �d�Ȃ�Ȃ��悤�ɂ��܂��B
		i3 = mrand() % iGenNumber;
		if( i1 != i3 && i2 != i3 )
		{
			lfSumAbs1 = 0.0;
			for( i = 0;i < iGenVector; i++ )
			{
				lfSumAbs1 += fabs((pplfGens[i1][i] - pplfGens[i3][i])*(pplfGens[i1][i] - pplfGens[i3][i]));
			}
			if( lfSumAbs1 > 0.00000001 )
			{
				lfSumAbs2 = 0.0;
				for( i = 0;i < iGenVector; i++ )
				{
					lfSumAbs2 += fabs((pplfGens[i2][i] - pplfGens[i3][i])*(pplfGens[i2][i] - pplfGens[i3][i]));
				}
				if( lfSumAbs2 > 0.00000001 )
				{
					break;
				}
			}
		}
	}
	*pplfParent1 = pplfGens[i1];
	*pplfParent2 = pplfGens[i2];
	*pplfParent3 = pplfGens[i3];
	*piLoc1 = i1;
	*piLoc2 = i2;
	*piLoc3 = i3;
}

void CUndx::vUndx( double *plfParent1, double *plfParent2, double *plfParent3, double lfAlpha, double lfBeta, double *plfChild1, double *plfChild2 )
{
	int i;
	std::vector<double> stlUnityVector1,stlMedian;
	std::vector<double> stlTempT1,stlTempT2;
	double lfDistTemp = 0.0;
	double lfDistTemp1 = 0.0;
	double lfDistTemp2 = 0.0;
	double lfDistTemp3 = 0.0;
	double lfDistTemp31 = 0.0;
	double lfProduct = 0.0;
	double lfDist1 = 0.0;
	double lfDist2 = 0.0;
	double lfDist3 = 0.0;
	double lfSub = 0.0;
	double lfSigma1 = 0.0;
	double lfSigma2 = 0.0;
	double lfS = 0.0;
	// 2�̐e�̒��_���Z�o���܂��B
	for( i = 0;i < iGenVector; i++ )
	{
		stlMedian.push_back( ( plfParent1[i]+plfParent2[i] )/2.0 );
		stlUnityVector1.push_back( plfParent1[i]-plfParent2[i] );
	}

	// 2�̐e�̋��������߂܂��B
	lfDist1 = 0.0;
	for( i = 0; i < iGenVector; i++ )
	{
		lfSub = stlUnityVector1.at(i);
		lfDist1 += lfSub*lfSub;
	}
	lfDist1 = sqrt( lfDist1 );
	lfSigma1 = lfDist1*lfAlpha;
	// �P�ʃx�N�g�����쐬���܂��B
	for( i = 0; i < iGenVector; i++ )
	{
		stlUnityVector1[i] /= lfDist1;
	}

	// ��3�̐e��2�̐e�Ƃ̋��������߂܂��B
	lfDist2 = 0.0;
	for( i = 0; i < iGenVector; i++ )
	{
		lfSub = (plfParent3[i]-plfParent1[i]);
		lfDist2 += lfSub*lfSub;
	}
	lfDist2 = sqrt( lfDist2 );
	lfDistTemp3 = 0.0;
	for( i = 0; i < iGenVector; i++ )
	{
		lfProduct = (plfParent3[i]-plfParent1[i])*(plfParent2[i]-plfParent1[i]);
		lfDistTemp3 += lfProduct;
	}
	lfDistTemp = lfDistTemp3/(lfDist1*lfDist2);
	lfDist3 = lfDist2*sqrt(1.0-lfDistTemp*lfDistTemp);
	
	lfSigma2 = lfDist3*lfBeta/sqrt((double)iGenVector);

	// �����ŁAz1,z2�𐶐����܂��Bz1=N(0,��_{1}^2), z2=N(0,��_{2}^2)�Ȃ̂ŁA����ɏ]���Đ������܂��B
	for( i = 0;i < iGenVector; i++ )
	{
		stlTempT1.push_back(grand(lfSigma1, 0.0));
		stlTempT2.push_back(grand(lfSigma2, 0.0));
	}
	//�܂�z2�ɒ��s����x�N�g�����Z�o���܂��B
	// ���ς����߂܂��B
	lfProduct = 0.0;
	for( i = 0;i < iGenVector; i++ )
	{
		lfProduct += stlTempT2[i]*stlUnityVector1[i];
	}
	// z2�ɒ��s����x�N�g���𐶐����܂��B
	for( i = 0;i < iGenVector; i++ )
	{
		stlTempT2[i] = stlTempT2[i] - lfProduct*stlUnityVector1[i];
	}
	lfS = grand(lfSigma1,0.0);
	for( i = 0;i < iGenVector; i++ )
	{
		stlTempT2[i] = stlTempT2[i] + lfS*stlUnityVector1[i];
	}
	// 2�q���𐶐����܂��B
	for( i = 0;i < iGenVector; i++ )
	{
		plfChild1[i] = stlMedian[i]+stlTempT2[i];
		plfChild2[i] = stlMedian[i]-stlTempT2[i];
	}
}

void CUndx::vSelectGens( double **pplfChildren, int *pi1stGenLoc, int *pi2ndGenLoc )
{
	unsigned int i;
	double lfProb = 0.0;
	double lfPrevProb = 0.0;
	double lfRes = 0.0;
	double lf1stGen = DBL_MAX;
	double lfRand = 0.0;
	int i1stGenLoc = INT_MAX;
	int i2ndGenLoc = INT_MAX;
	int iRank = 0;
	std::vector<Rank_t> stlFitProb;
	Rank_t tTempRankData;
	// �܂��A�K���x�֐��̒l���v�Z���܂��B
	lfRes = 0.0;
	for( i = 0;i < (unsigned int)iChildrenNumber; i++ )
	{
		tTempRankData.lfFitProb = pflfConstraintFunction( pplfChildren[i], iGenVector );
		tTempRankData.iLoc = i;
		stlFitProb.push_back( tTempRankData );
		lfRes += stlFitProb[i].lfFitProb;
		if( stlFitProb[i].lfFitProb < lf1stGen )
		{
			lf1stGen = stlFitProb[i].lfFitProb;
			i1stGenLoc = i;
		}
	}
	// �ړI�֐��l�ɂ��\�[�g�����{���܂��B
	std::sort( stlFitProb.begin(), stlFitProb.end(), CCompareToRank() );
	// �����N�Ɋ�Â����[���b�g�I�������s�B
	iRank = mrand() % ( iChildrenNumber-1 ) + 1;
	i2ndGenLoc = stlFitProb[iRank].iLoc;
	// �ŗǌ̂̈ʒu�Ƃ���ȊO�Ń��[���b�g�I���ɂ��I�΂ꂽ�ʒu��ԋp���܂��B
	*pi1stGenLoc = i1stGenLoc;
	*pi2ndGenLoc = i2ndGenLoc;
}

/**
 * <PRE>
 * �@���U�͈͓̔��Ɋm���ɐ��K�����𔭐�������悤�ɂ��܂��B
 * </PRE>
 * @param sigma ���U
 * @param mean ����
 * @author kobayashi
 * @since 2016/06/16
 * @version 0.1
 */
double CUndx::normalRand( double sigma, double mean )
{
	double lfRes = 0.0;
	double lfMin,lfMax;
	lfMin = -sigma + mean;
	lfMax = sigma + mean;
	for(;;)
	{
		lfRes = grand( sigma, mean );
		if( -lfMin <= lfRes && lfRes <= lfMax ) break;
	}
	return lfRes;
}

/**
 * <PRE>
 * �@�����_�ł̑I�������e���o�͂��܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 0.1
 */
void CUndx::vOutputCurrentParent( double *plfParent1, double *plfParent2 )
{
	int j;
	double lfRes = 0.0;
	double lfAvgDist = 0.0;
	double lfDist = 0.0;
	double lfDist2 = 0.0;
	if( iParentOutputFlag == 1 )
	{
		// �����_�őI���������e���o�͂��܂��B
		for( j = 0;j < iGenVector; j++ )
		{
			printf("%lf,",plfParent1[j]);
		}
		printf("\n");
		// �����_�őI���������e���o�͂��܂��B
		for( j = 0;j < iGenVector; j++ )
		{
			printf("%lf,",plfParent2[j]);
		}
		printf("\n");
	}
}

/**
 * <PRE>
 * �@�����_�ł̐��������q���o�͂��܂��B
 * </PRE>
 * @param pplfChildrenData 
 * @author kobayashi
 * @since 2015/12/16
 * @version 0.1
 */
void CUndx::vOutputCurrentChildren( double** pplfChildrenData )
{
	int i,j;

	if( iChildrenOutputFlag == 1 )
	{
		for( i= 0; i < iChildrenNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				printf("%lf,",pplfChildrenData[i][j]);
			}
			printf("\n");
		}
	}
}

/**
 * <PRE>
 * �@��`�q�ɒl��ݒ肵�܂��B
 *   ver 0.1 ���� 
 * </PRE>
 * @param pplfGenData 
 * @author kobayashi
 * @since 2016/08/10
 * @version 0.1
 */
void CUndx::vSetGenData( double** pplfGenData )
{
	int i,j;
	for( i= 0; i < iGenNumber; i++ )
	{
		for( j = 0;j < iGenVector; j++ )
		{
			pplfGens[i][j] = pplfGenData[i][j];
		}
	}
}

/**
 * <PRE>
 * �@���݂̈�`�q�f�[�^���擾���܂��B
 *   ver 0.1 ���� 
 * </PRE>
 * @param pplfGenData 
 * @author kobayashi
 * @since 2016/08/10
 * @version 0.1
 */
void CUndx::vGetGenData( double** pplfGenData )
{
	int i,j;
	for( i= 0; i < iGenNumber; i++ )
	{
		for( j = 0;j < iGenVector; j++ )
		{
			pplfGenData[i][j] = pplfGens[i][j];
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////CCmdCheckException�N���X

CUndxException::CUndxException()
{
	iErrCode = 0;
	strMethodName = "";
	strClassName = "";
	strErrDetail = "";
}

/**
 * �R���X�g���N�^(�G���[����ݒ肷��)
 * @param iCode       �G���[�R�[�h
 * @param sMethodName �֐���
 * @param sClassName  �N���X��
 * @param sDetail     �G���[�ڍ�
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
CUndxException::CUndxException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
{
	iErrCode = iCode;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}

/**
 * �R���X�g���N�^(�G���[����ݒ肷��)
 * @param iCode       �G���[�R�[�h
 * @param iLine       �s��
 * @param sMethodName �֐���
 * @param sClassName  �N���X��
 * @param sDetail     �G���[�ڍ�
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
CUndxException::CUndxException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
{
	iErrCode = iCode;
	iErrLine = iLine;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}


CUndxException::~CUndxException()
{
	iErrCode = 0;
	strMethodName = "";
	strClassName = "";
	strErrDetail = "";
}

/**
 * �R���X�g���N�^(�G���[����ݒ肷��)
 * @param iCode       �G���[�R�[�h
 * @param sMethodName �֐���
 * @param sClassName  �N���X��
 * @param sDetail     �G���[�ڍ�
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
void CUndxException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
{
	iErrCode = iCode;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}

/**
 * �R���X�g���N�^(�G���[����ݒ肷��)
 * @param iCode       �G���[�R�[�h
 * @param iLine       �s��
 * @param sMethodName �֐���
 * @param sClassName  �N���X��
 * @param sDetail     �G���[�ڍ�
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
void CUndxException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
{
	iErrCode = iCode;
	iErrLine = iLine;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}

/**
 * �G���[�ԍ����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
int CUndxException::iGetErrCode()
{
	return iErrCode;
}

/**
 * �G���[���N�������s�����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
int CUndxException::iGetErrLine()
{
	return iErrLine;
}

/**
 * �G���[���N�������֐������o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CUndxException::strGetMethodName()
{
	return strMethodName;
}

/**
 * �G���[���N�������N���X���o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CUndxException::strGetClassName()
{
	return strClassName;
}

/**
 * �G���[�̏ڍ׏����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CUndxException::strGetErrDetail()
{
	return strErrDetail;
}
