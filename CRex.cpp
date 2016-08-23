
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
#include"CRex.h"

CRex::CRex()
{
	iParentOutputFlag = 0;
	iChildrenOutputFlag = 0;
	iParentNumber = 0;
	iChildrenNumber = 0;
	pplfChildren = NULL;
}

CRex::~CRex()
{
///	vTerminate();
}

void CRex::vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData, int iParentNumberData, int iChildrenNumberData )
{
	int i;
	CRexException cre;

	// �e�̐�������ݒ肵�܂��B
	iParentNumber = iParentNumberData;

	// �q���̐�������ݒ肵�܂��B
	iChildrenNumber = iChildrenNumberData;

	// �����lGA�̏����������s���܂��B
	CRealCodedGa::vInitialize( iGenerationNum, iGenNum, iGenVectorData );

	try
	{
		// �q���̃f�[�^���쐬���܂��B
		pplfChildren = new double*[iChildrenNumber];
		if( pplfChildren == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		for( i = 0;i < iChildrenNumber; i++ )
		{
			pplfChildren[i] = new double[iGenVector];
			if( pplfChildren[i] == NULL )
			{
				cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
				throw( cre );
			}
		}
		
		plfTempVector = new double[iGenVector];
		if( plfTempVector == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfCentroid = new double[iGenVector];
		if( plfCentroid == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfChildVector = new double[iGenVector];
		if( plfChildVector == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfNormalizeRand = new double[iParentNumber];
		if( plfNormalizeRand == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfChildrenCentroid = new double[iGenVector];
		if( plfChildrenCentroid == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfUpperEvalChildrenCentroid = new double[iGenVector];
		if( plfUpperEvalChildrenCentroid == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfCentroidSteep = new double[iGenVector];
		if( plfCentroidSteep == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}

		for( i = 0;i < iChildrenNumber; i++ )
		{
			memset( pplfChildren[i], 0, iGenVector*sizeof(double) );
		}
		for( i = 0;i < iGenVector; i++ )
		{
			plfCentroid[i] = 0.0;
			plfChildVector[i] = 0.0;
			plfTempVector[i] = 0.0;
			plfUpperEvalChildrenCentroid[i] = 0.0;
			plfChildrenCentroid[i] = 0.0;
			plfCentroidSteep[i] = 0.0;
		}
		for( i = 0;i < iParentNumber; i++ )
		{
			plfNormalizeRand[i] = 0.0;
		}

		initrand( (unsigned long)time(NULL) );
		initrnd();
	}
	catch( std::bad_alloc ba )
	{
		cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
		throw( cre );
	}
	catch( ... )
	{
		cre.SetErrorInfo( REX_ARRAY_INDEX_ERROR, "vInitialize", "CRex", "�z��͈͊O���Q�Ƃ��܂����B", __LINE__ );
		throw( cre );
	}
}

void CRex::vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData, int iParentNumberData, int iChildrenNumberData, double lfLearningRateData,int iUpperEvalChildrenNum )
{
	int i;
	CRexException cre;

	// �e�̐�������ݒ肵�܂��B	iParentNumber = iParentNumberData;

	// �q���̐�������ݒ肵�܂��B
	iChildrenNumber = iChildrenNumberData;

	// �����lGA�̏����������s���܂��B
	CRealCodedGa::vInitialize( iGenerationNum, iGenNum, iGenVectorData );

	// �w�K���̐ݒ�����܂��B
	lfLearningRate = lfLearningRateData;

	// ������̕]���l��ʂ̎q���̐���臒l��ݒ肵�܂��B
	iUpperEvalChildrenNumber = iUpperEvalChildrenNum;

	lfAlpha = 1.0;
	
	try
	{
		// �q���̃f�[�^���쐬���܂��B
		pplfChildren = new double*[iChildrenNumber];
		if( pplfChildren == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		for( i = 0;i < iChildrenNumber; i++ )
		{
			pplfChildren[i] = new double[iGenVector];
			if( pplfChildren[i] == NULL )
			{
				cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
				throw( cre );
			}
		}
		
		plfTempVector = new double[iGenVector];
		if( plfTempVector == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfCentroid = new double[iGenVector];
		if( plfCentroid == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfChildVector = new double[iGenVector];
		if( plfChildVector == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfNormalizeRand = new double[iParentNumber];
		if( plfNormalizeRand == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfChildrenCentroid = new double[iGenVector];
		if( plfChildrenCentroid == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfUpperEvalChildrenCentroid = new double[iGenVector];
		if( plfUpperEvalChildrenCentroid == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}
		plfCentroidSteep = new double[iGenVector];
		if( plfCentroidSteep == NULL )
		{
			cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
			throw( cre );
		}


		for( i = 0;i < iChildrenNumber; i++ )
		{
			memset( pplfChildren[i], 0, iGenVector*sizeof(double) );
		}
		for( i = 0;i < iGenVector; i++ )
		{
			plfCentroid[i] = 0.0;
			plfChildVector[i] = 0.0;
			plfTempVector[i] = 0.0;
			plfUpperEvalChildrenCentroid[i] = 0.0;
			plfChildrenCentroid[i] = 0.0;
			plfCentroidSteep[i] = 0.0;
		}
		for( i = 0;i < iParentNumber; i++ )
		{
			plfNormalizeRand[i] = 0.0;
		}

		initrand( (unsigned long)time(NULL) );
		initrnd();
	}
	catch( std::bad_alloc ba )
	{
		cre.SetErrorInfo( REX_MEMORY_ALLOCATE_ERROR, "vInitialize", "CRex", "�������m�ۂɎ��s���܂����B", __LINE__ );
		throw( cre );
	}
	catch( ... )
	{
		cre.SetErrorInfo( REX_ARRAY_INDEX_ERROR, "vInitialize", "CRex", "�z��͈͊O���Q�Ƃ��܂����B", __LINE__ );
		throw( cre );
	}
}

void CRex::vTerminate()
{
	int i;
	CRexException cre;

	try
	{
		// �p�����N���X�ɑ����郁���o�ϐ��̏I�����������s���܂��B
		CRealCodedGa::vTerminate();
		
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
		if( plfTempVector != NULL )
		{
			delete[] plfTempVector;
			plfTempVector = NULL;
		}
		if( plfCentroid != NULL )
		{
			delete[] plfCentroid;
			plfCentroid = NULL;
		}
		if( plfChildVector != NULL )
		{
			delete[] plfChildVector;
			plfChildVector = NULL;
		}
		if( plfNormalizeRand != NULL )
		{
			delete[] plfNormalizeRand;
			plfNormalizeRand = NULL;
		}
		if( plfChildrenCentroid != NULL )
		{
			delete[] plfChildrenCentroid;
			plfChildrenCentroid = NULL;
		}
		if( plfUpperEvalChildrenCentroid != NULL )
		{
			delete[] plfUpperEvalChildrenCentroid;
			plfUpperEvalChildrenCentroid = NULL;
		}
		if( plfCentroidSteep != NULL )
		{
			delete[] plfCentroidSteep;
			plfCentroidSteep = NULL;
		}
	}
	catch( ... )
	{
		cre.SetErrorInfo( REX_MEMORY_RELEASE_ERROR, "vTerminate", "CUndx", "�m�ۂ����������̉���Ɏ��s���܂����B", __LINE__ );
		throw( cre );
	}
}

void CRex::vRex()
{
	CRexException cre;
	int i,j,k;
	int iLoc;
	int iMaxSize = 0;
	int iOverLapLoc = 0;
	double lfSigma = 0.0;
	std::vector<Rank_t> stlFitProb;
	Rank_t tTempRankData;
	std::vector<int> stlSelectParentLoc;
	
/* JGG���f�� */

	try
	{
		// �e�������_����Np�I�����܂��B
		for(;;)
		{
			iLoc = mrand() % iGenNumber;
			// �I�������e�Əd�Ȃ��Ă��Ȃ����������܂��B
			iOverLapLoc = -1;
			for( i = 0;i < stlSelectParentLoc.size(); i++ )
			{
				if( stlSelectParentLoc.at(i) == iLoc )
				{
					iOverLapLoc = i;
					break;
				}
			}
			// �d�Ȃ��Ă��Ȃ���΁A�ʒu��ǉ����܂��B
			if( iOverLapLoc == -1 )
			{
				stlSelectParentLoc.push_back( iLoc );
				iMaxSize++;
			}
			// �w�肵���e�̐��ɂȂ�����I�����܂��B
			if( iMaxSize == iParentNumber ) break;
		}
	
		// �d�S���Z�o���܂��B
		for( i = 0;i < iGenVector; i++ )
		{
			plfCentroid[i] = 0.0;
		}
		for( i = 0;i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				plfCentroid[j] += pplfGens[stlSelectParentLoc.at(i)][j];
			}
		}
		for( i = 0;i < iGenVector; i++ )
		{
			plfCentroid[i] /= (double)iParentNumber;
		}
	// REX(RealCoded Emsanble )�����s���܂��B������Nc����s���ANc�̎q���𐶐����܂��B
		// ���v�ʈ�`�ɂ����镁�Օ��U���Z�o���܂��B
		lfSigma = 1.0/(double)sqrt( (double)iParentNumber );
//		lfSigma = 0.05;
//		lfSigma = 0.5;

		for( i = 0;i < iChildrenNumber; i++ )
		{
			// ���K�����ɂ�藐���𔭐������܂��B
			for( j = 0;j < iParentNumber; j++ )
			{
				plfNormalizeRand[j] = grand(lfSigma, 0.0);
			}
			for( j = 0;j < iGenVector; j++ )
			{
				plfTempVector[j] = 0.0;
				plfChildVector[j] = 0.0;
			}
			for( j = 0;j < iParentNumber; j++ )
			{
			// REX�����s���āA�q���𐶐����܂��B
				for( k = 0;k < iGenVector; k++ )
				{
					plfTempVector[k] += plfNormalizeRand[j] * ( pplfGens[stlSelectParentLoc.at(j)][k] - plfCentroid[k] );
				}
			}
			for( k = 0;k < iGenVector; k++ )
			{
				plfChildVector[k] = plfCentroid[k] + plfTempVector[k];
			}
			for( j = 0;j < iGenVector; j++ )
			{
				pplfChildren[i][j] = plfChildVector[j];
			}
		}
		
		// �]���l��Np�Z�o���܂��B
		for( i = 0;i < iChildrenNumber; i++ )
		{
			tTempRankData.lfFitProb = pflfConstraintFunction( pplfChildren[i], iGenVector );
			tTempRankData.iLoc = i;
			stlFitProb.push_back( tTempRankData );
//			printf( "%lf,",tTempRankData.lfFitProb );
		}
//		printf("\n");
		// �ړI�֐��l�ɂ��\�[�g�����{���܂��B
		std::sort( stlFitProb.begin(), stlFitProb.end(), CCompareToRank() );
		for( i = 0;i < iChildrenNumber; i++ )
		{
//			printf("%lf ",stlFitProb.at(i).lfFitProb );
		}
		// �e�����ւ��܂��B(JGG���f���̏ꍇ�͐e�͂��ׂĕύX������̂Ƃ��܂��B)
		for( i = 0; i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				pplfGens[stlSelectParentLoc.at(i)][j] = pplfChildren[stlFitProb[i].iLoc][j];
			}
		}
	}
	catch(...)
	{
		cre.SetErrorInfo( REX_ARRAY_INDEX_ERROR, "vImplement", "CRex", "�z��͈͊O�Q�Ƃ����܂����B", __LINE__ );
		throw( cre );
	}
	stlSelectParentLoc.clear();
}

void CRex::vRexStar()
{
	CRexException cre;
	int i,j,k;
	int iLoc;
	int iMaxSize = 0;
	int iOverLapLoc = 0;
	double lfSigma = 0.0;
	std::vector<Rank_t> stlFitProb;
	Rank_t tTempRankData;
	std::vector<int> stlSelectParentLoc;
	
/* JGG���f�� */

	try
	{
		// �e�������_����Np�I�����܂��B
		for(;;)
		{
			iLoc = mrand() % iGenNumber;
			// �I�������e�Əd�Ȃ��Ă��Ȃ����������܂��B
			iOverLapLoc = -1;
			for( i = 0;i < (unsigned int)stlSelectParentLoc.size(); i++ )
			{
				if( stlSelectParentLoc.at(i) == iLoc )
				{
					iOverLapLoc = i;
					break;
				}
			}
			// �d�Ȃ��Ă��Ȃ���΁A�ʒu��ǉ����܂��B
			if( iOverLapLoc == -1 )
			{
				stlSelectParentLoc.push_back( iLoc );
				iMaxSize++;
			}
			// �w�肵���e�̐��ɂȂ�����I�����܂��B
			if( iMaxSize == iParentNumber ) break;
		}
		// �d�S���Z�o���܂��B
		for( i = 0;i < iGenVector; i++ )
		{
			plfCentroid[i] = 0.0;
		}
		for( i = 0;i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				plfCentroid[j] += ( pplfGens[stlSelectParentLoc.at(i)][j] );
			}
		}
		for( i = 0;i < iParentNumber; i++ )
		{
			plfCentroid[j] /= (double)iParentNumber;
		}
	// REX(RealCoded Emsanble )�����s���܂��B������Nc����s���ANc�̎q���𐶐����܂��B
		// ���v�ʈ�`�ɂ����镁�Օ��U���Z�o���܂��B
		lfSigma = 1.0/(double)sqrt( (double)iParentNumber );
		
		for( i = 0;i < iChildrenNumber; i++ )
		{
			// ���K�����ɂ�藐���𔭐������܂��B
			for( j = 0;j < iParentNumber; j++ )
			{
				plfNormalizeRand[j] = grand(lfSigma, 0.0);
			}
			for( j = 0;j < iGenVector; j++ )
			{
				plfTempVector[j] = 0.0;
				plfChildVector[j] = 0.0;
			}
			for( j = 0;j < iParentNumber; j++ )
			{
			// REX�����s���āA�q���𐶐����܂��B
				for( k = 0;k < iGenVector; k++ )
				{
					plfTempVector[k] += plfNormalizeRand[j] * ( pplfGens[stlSelectParentLoc.at(j)][k] - plfCentroid[k] );
				}
			}
			for( k = 0;k < iGenVector; k++ )
			{
				plfChildVector[k] = plfCentroid[k] + plfTempVector[k];
			}
			for( j = 0;j < iGenVector; j++ )
			{
				pplfChildren[i][j] = plfChildVector[j];
			}
		}
		
		// �]���l��Np�Z�o���܂��B
		for( i = 0;i < iChildrenNumber; i++ )
		{
			tTempRankData.lfFitProb = pflfConstraintFunction( pplfChildren[i], iGenVector );
			tTempRankData.iLoc = i;
			stlFitProb.push_back( tTempRankData );
		}
		// �ړI�֐��l�ɂ��\�[�g�����{���܂��B
		std::sort( stlFitProb.begin(), stlFitProb.end(), CCompareToRank() );
		// �e�����ւ��܂��B(JGG���f���̏ꍇ�͐e�͂��ׂĕύX������̂Ƃ��܂��B)
		for( i = 0; i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				pplfGens[stlSelectParentLoc.at(i)][j] = pplfChildren[stlFitProb[i].iLoc][j];
			}
		}
	}
	catch(...)
	{
		cre.SetErrorInfo( REX_ARRAY_INDEX_ERROR, "vImplement", "CRex", "�z��͈͊O�Q�Ƃ����܂����B", __LINE__ );
		throw( cre );
	}
	stlSelectParentLoc.clear();
}

/**
 * <PRE>
 *    �K���I�����l����AREX�����s���܂��B
 * </PRE>
 * @author kobayashi
 * @since 2016/6/10
 * @version 1.0
 */
void CRex::vARex()
{
	CRexException cre;
	int i,j,k;
	int iLoc;
	int iMaxSize = 0;
	int iOverLapLoc = 0;
	double lfSigma = 0.0;
	double l;
	double lAvgDist = 0.0;
	double lfTemp = 0.0;
	std::vector<Rank_t> stlFitProb;
	std::vector<Rank_t> stlParentFitProb;
	Rank_t tTempRankData;
	std::vector<int> stlSelectParentLoc;
	
/* JGG���f�� */

	try
	{
		// �e�������_����Np�I�����܂��B
		for(;;)
		{
			iLoc = mrand() % iGenNumber;
			// �I�������e�Əd�Ȃ��Ă��Ȃ����������܂��B
			iOverLapLoc = -1;
			for( i = 0;i < (unsigned int)stlSelectParentLoc.size(); i++ )
			{
				if( stlSelectParentLoc.at(i) == iLoc )
				{
					iOverLapLoc = i;
					break;
				}
			}
			// �d�Ȃ��Ă��Ȃ���΁A�ʒu��ǉ����܂��B
			if( iOverLapLoc == -1 )
			{
				stlSelectParentLoc.push_back( iLoc );
				iMaxSize++;
				
				// �e�f�[�^��K���x�Ń\�[�g���邽�߁A�f�[�^�������܂��B
				tTempRankData.lfFitProb = pflfConstraintFunction( pplfGens[iLoc], iGenVector );
				tTempRankData.iLoc = iLoc;
				stlParentFitProb.push_back( tTempRankData );
			}
			// �w�肵���e�̐��ɂȂ�����I�����܂��B
			if( iMaxSize == iParentNumber ) break;
		}
		std::sort( stlParentFitProb.begin(), stlParentFitProb.end(), CCompareToRank() );
	
		// �d�S���Z�o���܂��B
		for( j = 0;j < iGenVector; j++ )
		{
			plfCentroid[j] = 0.0;
		}
		for( j = 0;j < iParentNumber; j++ )
		{
			for( k = 0;k < iGenVector; k++ )
			{
				plfCentroid[k] += ( pplfGens[stlSelectParentLoc.at(j)][k]/(double)iParentNumber );
			}
		}
	// REX(RealCoded Emsanble )�����s���܂��B������Nc����s���ANc�̎q���𐶐����܂��B
		// ���v�ʈ�`�ɂ����镁�Օ��U���Z�o���܂��B
		lfSigma = 1.0/(double)sqrt( (double)iParentNumber );

		// �������S�~�����Z�o���܂��B
		for( i = 0;i < iGenVector; i++ )
		{
			plfCentroidSteep[i] = 0.0;
		}
		for( i = 0;i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				plfCentroidSteep[j] += 2.0*(double)(iParentNumber+1-i)/(double)(iParentNumber*(iParentNumber+1))*pplfGens[stlParentFitProb.at(i).iLoc][j];
			}
		}
		
		for( i = 0;i < iChildrenNumber; i++ )
		{
			// ���K�����ɂ�藐���𔭐������܂��B
			for( j = 0;j < iParentNumber; j++ )
			{
				plfNormalizeRand[j] = grand(lfSigma, 0.0);
			}
			for( j = 0;j < iGenVector; j++ )
			{
				plfTempVector[j] = 0.0;
				plfChildVector[j] = 0.0;
			}
			for( j = 0;j < iParentNumber; j++ )
			{
			// REX�����s���āA�q���𐶐����܂��B
				for( k = 0;k < iGenVector; k++ )
				{
					plfTempVector[k] += plfNormalizeRand[j] * ( pplfGens[stlSelectParentLoc.at(j)][k] - plfCentroid[k] );
				}
			}
			for( j = 0;j < iGenVector; j++ )
			{
				plfChildVector[j] = plfCentroidSteep[j] + lfAlpha*plfTempVector[j];
			}
			for( j = 0;j < iGenVector; j++ )
			{
				pplfChildren[i][j] = plfChildVector[j];
			}
		}
		
		// �]���l��Np�Z�o���܂��B
		for( i = 0;i < iChildrenNumber; i++ )
		{
			tTempRankData.lfFitProb = pflfConstraintFunction( pplfChildren[i], iGenVector );
			tTempRankData.iLoc = i;
			stlFitProb.push_back( tTempRankData );
		}
		// �ړI�֐��l�ɂ��\�[�g�����{���܂��B
		std::sort( stlFitProb.begin(), stlFitProb.end(), CCompareToRank() );

		// �����̒��S�����߂܂��B
		for( i = 0;i < iChildrenNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				plfChildrenCentroid[j] += pplfChildren[i][j];
			}
		}
		for( j = 0;j < iGenVector; j++ )
		{
			plfChildrenCentroid[j] /= (double)(iChildrenNumber);
		}

		// �]���l��ʃʃ��̎q���̒��S�����߂܂��B
		for( i = 0;i < iUpperEvalChildrenNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				plfUpperEvalChildrenCentroid[i] += pplfChildren[stlFitProb[i].iLoc][j];
			}
		}
		for( i = 0;i < iUpperEvalChildrenNumber; i++ )
		{
			plfUpperEvalChildrenCentroid[i] /= (double)iUpperEvalChildrenNumber;
		}

		// Ldcp���Z�o���܂��B
		lfLcdp = 0.0;
		for( i = 0;i < iGenVector; i++ )
		{
			lfTemp = plfUpperEvalChildrenCentroid[i] - plfChildrenCentroid[i];
			lfLcdp += lfTemp*lfTemp;
		}

		// Lavg���Z�o���܂��B
		lfLavg = 0.0;
		for( i = 0;i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				lfTemp = pplfGens[stlSelectParentLoc.at(i)][j] - plfCentroid[j];
			}
			lfLavg += lfTemp*lfTemp;
		}
		lfLavg = lfLavg+lfAlpha*lfAlpha*lfSigma*lfSigma;

		// ���̍X�V���s���܂��B
		lfTemp = lfAlpha * sqrt( (1.0-lfLearningRate)+lfLearningRate*lfLcdp/lfLavg );
		lfAlpha = lfTemp > 1 ? 1.0 : lfTemp;

		// �e�����ւ��܂��B(JGG���f���̏ꍇ�͐e�͂��ׂĕύX������̂Ƃ��܂��B)
		for( i = 0; i < iParentNumber; i++ )
		{
			for( j = 0;j < iGenVector; j++ )
			{
				pplfGens[stlSelectParentLoc.at(i)][j] = pplfChildren[stlFitProb[i].iLoc][j];
			}
		}
	}
	catch(...)
	{
		cre.SetErrorInfo( REX_ARRAY_INDEX_ERROR, "vImplement", "CRex", "�z��͈͊O�Q�Ƃ����܂����B", __LINE__ );
		throw( cre );
	}
	stlSelectParentLoc.clear();
}

/**
 * <PRE>
 * �@�����_�ł̑I�������e���o�͂��܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 0.1
 */
void CRex::vOutputCurrentParent( std::vector<int> stlSelectParentLocData )
{
	int i,j;
	double lfRes = 0.0;
	double lfAvgDist = 0.0;
	double lfDist = 0.0;
	double lfDist2 = 0.0;
	if( iParentOutputFlag == 1 )
	{
		for(i = 0;i < (unsigned int)stlSelectParentLocData.size(); i++ )
		{
			// �����_�őI���������e���o�͂��܂��B
			for( j = 0;j < iGenVector; j++ )
			{
				printf( "%lf," ,pplfGens[stlSelectParentLocData.at(i)][j] );
			}
			printf("\n");
		}
	}
}

/**
 * <PRE>
 * �@�����_�ł̐��������q���o�͂��܂��B
 * </PRE>
 * @author kobayashi
 * @since 2015/12/16
 * @version 0.1
 */
void CRex::vOutputCurrentChildren( double** pplfChildrenData )
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////CRexException�N���X

CRexException::CRexException()
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
CRexException::CRexException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
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
CRexException::CRexException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
{
	iErrCode = iCode;
	iErrLine = iLine;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}

CRexException::~CRexException()
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
void CRexException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
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
void CRexException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
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
int CRexException::iGetErrCode()
{
	return iErrCode;
}

/**
 * �G���[���N�������s�����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
int CRexException::iGetErrLine()
{
	return iErrLine;
}

/**
 * �G���[���N�������֐������o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CRexException::strGetMethodName()
{
	return strMethodName;
}

/**
 * �G���[���N�������N���X���o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CRexException::strGetClassName()
{
	return strClassName;
}

/**
 * �G���[�̏ڍ׏����o�͂���
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
std::string CRexException::strGetErrDetail()
{
	return strErrDetail;
}
