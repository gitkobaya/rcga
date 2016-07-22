#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<memory>
#include<cfloat>
#include"mseq.h"
#include"CRealCodedGa.h"

CRealCodedGa::CRealCodedGa()
{
	iGenerationNumber = 0;
	iGenNumber = 0;
	iGenVector = 0;
	pplfGens =  NULL;
}

CRealCodedGa::CRealCodedGa( int iGenerationNum, int iGenNum, int iGenVectorData )
{
	vInitialize( iGenerationNum, iGenNum, iGenVectorData );
}

CRealCodedGa::~CRealCodedGa()
{
//	vTerminate();
}

void CRealCodedGa::vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData )
{
	int i,j;
	CRealCodedGaException crcgae;

	iGenerationNumber = iGenerationNum;
	iGenNumber = iGenNum;
	iGenVector = iGenVectorData;
	srand( time(NULL) );

	try
	{
		pplfGens = new double*[iGenNumber];
		if( pplfGens == NULL )
		{
			crcgae.SetErrorInfo( RCGA_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRealCodedGa", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( crcgae );
		}
		for( i = 0;i < iGenNumber; i++ )
		{
			pplfGens[i] = new double[iGenVector];
		}
		
		for( i = 0;i < iGenNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				pplfGens[i][j] = 0.0;
			}
		}
		initrand( time(NULL) );
		initrnd();
	}
	catch( std::bad_alloc ba )
	{
		crcgae.SetErrorInfo( RCGA_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRealCodedGa", "�������m�ۂɎ��s���܂����B", __LINE__ );
		throw( crcgae );
	}
	catch( ... )
	{
		crcgae.SetErrorInfo( RCGA_ARRAY_INDEX_ERROR, "vInitialize", "CRealCodedGa", "�z��͈͊O���Q�Ƃ��܂����B", __LINE__ );
		throw( crcgae );
	}
}

/**
 * <PRE>
 * �@�����ɂ��GA��ݒ肵�܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/10/30
 * @version 1.0
 */
void CRealCodedGa::vSetRandom()
{
	int i,j;
	CRealCodedGaException crcgae;

	try
	{
		for( i = 0;i < iGenNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				pplfGens[i][j] = rnd();
			}
		}
	}
	catch( ... )
	{
		crcgae.SetErrorInfo( RCGA_ARRAY_INDEX_ERROR, "vSetRandom", "CRealCodedGa", "�z��͈̔͊O���Q�Ƃ��܂����B", __LINE__ );
		throw( crcgae );
	}
}

/**
 * <PRE>
 * �@�ړI�֐����C���X�g�[�����܂��B
 * </PRE>
 * @param lfDomainMin ���������ŏ��l
 * @param lfDomainMax ���������ő�l
 * @author kobayashi
 * @since 2015/10/30
 * @version 1.0
 */
void CRealCodedGa::vSetRandom( double lfDomainMin, double lfDomainMax )
{
	int i,j;
	CRealCodedGaException crcgae;

	try
	{
		for( i = 0;i < iGenNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				pplfGens[i][j] = rnd()*(lfDomainMax-lfDomainMin) + lfDomainMin;
			}
		}
	}
	catch( ... )
	{
		crcgae.SetErrorInfo( RCGA_ARRAY_INDEX_ERROR, "vSetRandom", "CRealCodedGa", "�z��͈̔͊O���Q�Ƃ��܂����B", __LINE__ );
		throw( crcgae );
	}
}

/**
 * <PRE>
 * �@�ړI�֐����C���X�g�[�����܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/10/30
 * @version 1.0
 */
void CRealCodedGa::vTerminate()
{
	int i;
	CRealCodedGaException crcgae;

	try
	{
		if( pplfGens != NULL )
		{
			for( i = 0;i < iGenNumber; i++ )
			{
				if( pplfGens[i] != NULL )
				{
					delete[] pplfGens[i];
					pplfGens[i] = NULL;
				}
			}
			delete[] pplfGens;
			pplfGens = NULL;
		}
	}
	catch( ... )
	{
		crcgae.SetErrorInfo( RCGA_MEMORY_RELEASE_ERROR, "vSetRandom", "CRealCodedGa", "�m�ۂ����������̉���Ɏ��s���܂����B", __LINE__ );
		throw( crcgae );
	}
}

/**
 * <PRE>
 * �@�ړI�֐����C���X�g�[�����܂��B
 * �@���ۂɂ̓R�[���o�b�N�֐����C���X�g�[�����܂��B
 * </PRE>
 * @param pflfFunction �ړI�֐��̊֐��|�C���^
 * @author kobayashi
 * @since 2015/10/30
 * @version 1.0
 */
void CRealCodedGa::vSetConstraintFunction( double (*pflfFunction)( double *plfData, int iVectorLen ) )
{
	pflfConstraintFunction = pflfFunction;
}

/**
 * <PRE>
 * �@�ړI�֐����A���C���X�g�[�����܂��B
 * �@���ۂɂ̓R�[���o�b�N�֐����A���C���X�g�[�����܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/10/30
 * @version 1.0
 */
void CRealCodedGa::vReleaseCallConstraintFunction()
{
	pflfConstraintFunction = NULL;
}

/**
 * <PRE>
 * �@�����l�f�`�̌��ʂ��o�͂��܂��B(�e��`�q�̃x�N�g��)
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 1.0
 */
void CRealCodedGa::vOutputGenData()
{
	int i,j;
	// �����_�ł̗��q�̈ʒu���o�͂��܂��B
	for( i = 0; i < iGenNumber; i++ )
	{
		for( j = 0;j < iGenVector; j++ )
		{
			printf("%lf,", pplfGens[i][j]);
		}
		printf("\n");
	}
}

/**
 * <PRE>
 * �@���݂̎����lGA�ɖړI�֐���K�p�������ʂ��o�͂��܂��B(�e��`�q�̖ړI�֐��l)
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 1.0
 */
void CRealCodedGa::vOutputConstraintFunction()
{
	int i;
	// �����_�ł̊e���q�̖ړI�֐��̒l���o�͂��܂��B
	for( i = 0; i < iGenNumber; i++ )
	{
		printf("%lf,", pflfConstraintFunction(pplfGens[i], iGenVector) );
	}
	printf("\n");
}

/**
 * <PRE>
 * �@�����_�ł̂����Ƃ��悢��`�q�̈ʒu���o�͂��܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/6/19
 * @version 1.0
 */
void CRealCodedGa::vOutputGlobalMaxGenData()
{
	int i;
	int iLoc = 0;
	double lfTemp = 0.0;
	double lfRes = 0.0;
	lfTemp = DBL_MAX;
	for( i = 0;i < iGenNumber; i++ )
	{
		// �����_�ł̊e��`�q�̖ړI�֐��̒l�������Ƃ��œK�l�ɂȂ��Ă�����̂��o�͂��܂��B
		lfRes = pflfConstraintFunction(pplfGens[i], iGenVector);
		if( lfRes <= lfTemp )
		{
			lfTemp = lfRes;
			iLoc = i;
		}
	}
	// �œK�l�ɂȂ��Ă����`�q���o�͂��܂��B
	for( i = 0;i < iGenVector; i++ )
	{
		printf("%lf,", pplfGens[iLoc][i] );
	}
	printf("\n");
}

/**
 * <PRE>
 * �@�����_�ł̂����Ƃ��悢��`�q�̖ړI�֐��l���o�͂��܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 1.0
 */
void CRealCodedGa::vOutputGlobalMaxConstFuncValue()
{
	int i;
	double lfTemp = 0.0;
	double lfRes = 0.0;
	lfTemp = DBL_MAX;
	for( i = 0;i < iGenNumber; i++ )
	{
		// �����_�ł̊e��`�q�̖ړI�֐��̒l���o�͂��܂��B
		lfRes = pflfConstraintFunction(pplfGens[i], iGenVector);
		if( lfRes <= lfTemp )
		{
			lfTemp = lfRes;
		}
	}
	// �œK�l�ɂȂ��Ă���ړI�֐��̒l���o�͂��܂��B
	printf("%lf\n", lfTemp );
}

/**
 * <PRE>
 * �@�����_�ł̂����Ƃ��悢��`�q�y�т��̖ړI�֐��l���o�͂��܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 1.0
 */
void CRealCodedGa::vOutputGlobalMaxGenDataConstFuncValue()
{
	int i;
	int iLoc = 0;
	double lfTemp = 0.0;
	double lfRes = 0.0;
	lfTemp = DBL_MAX;
	for( i = 0;i < iGenNumber; i++ )
	{
		// �����_�ł̊e��`�q�̖ړI�֐��̒l���o�͂��܂��B
		lfRes = pflfConstraintFunction(pplfGens[i], iGenVector);
		if( lfRes <= lfTemp )
		{
			lfTemp = lfRes;
			iLoc = i;
		}
	}
	// �œK�l�ɂȂ��Ă����`�q���o�͂��܂��B
	for( i = 0;i < iGenVector; i++ )
	{
		printf("%lf,", pplfGens[iLoc][i] );
	}
	// �œK�l�ɂȂ��Ă���ړI�֐��̒l���o�͂��܂��B
	printf("%lf\n", lfTemp );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////CCmdCheckException�N���X

CRealCodedGaException::CRealCodedGaException()
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
CRealCodedGaException::CRealCodedGaException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
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
CRealCodedGaException::CRealCodedGaException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
{
	iErrCode = iCode;
	iErrLine = iLine;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}


CRealCodedGaException::~CRealCodedGaException()
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
void CRealCodedGaException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
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
void CRealCodedGaException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
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
int CRealCodedGaException::iGetErrCode()
{
	return iErrCode;
}

/**
 * �G���[���N�������s�����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
int CRealCodedGaException::iGetErrLine()
{
	return iErrLine;
}

/**
 * �G���[���N�������֐������o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CRealCodedGaException::strGetMethodName()
{
	return strMethodName;
}

/**
 * �G���[���N�������N���X���o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CRealCodedGaException::strGetClassName()
{
	return strClassName;
}

/**
 * �G���[�̏ڍ׏����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CRealCodedGaException::strGetErrDetail()
{
	return strErrDetail;
}
