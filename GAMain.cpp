#include<cstdio>
#include<cstring>
#include<iostream>
#include"EvaluationFunction.h"
#include"CUndx.h"
#include"CRex.h"
#include"cmd_check.h"

extern void vInitialize( CCmdCheck *pcCmd, void *pvGaClass );
extern void vSetObjectiveFunction( CCmdCheck *pcCmd, void *pvGaClass );
extern void vStartGa( CCmdCheck *pcCmd, void *pvGaClass );
extern void vTerminate( CCmdCheck *pcCmd, void *pvGaClass );
extern void vOutputData( CCmdCheck *pcCmd, void *pvGaClass );
extern void vSetRandom( CCmdCheck *pcCmd, void *pvGaClass );

int main(int argc, char* argv[])
{
	int i;
	long lRet = 0L;
	CUndx undx;
	CRex rex;
	void *pvGaClass;
	CCmdCheck cmd;

	try
	{
		lRet = cmd.lCommandCheck( argc, argv );
		if( lRet == 0 )
		{
			if( cmd.iGetGaMethod() == 1 )		pvGaClass = &undx;
			else if( cmd.iGetGaMethod() == 2 )	pvGaClass = &rex;
			else if( cmd.iGetGaMethod() == 3 )	pvGaClass = &rex;
			// �����������s���܂��B
			vInitialize( &cmd, pvGaClass );
			
			// �����l��ݒ肵�܂��B
			vSetRandom( &cmd, pvGaClass );
			
			// �ړI�֐���ݒ肵�܂��B
			vSetObjectiveFunction( &cmd, pvGaClass );
			
			// ���ʂ��o�͂��܂��B
			vOutputData( &cmd, pvGaClass );
			
			for( i = 0;i < cmd.iGetGenerationNumber(); i++ )
			{
				// �����l�f�`�����s���܂��B
				vStartGa( &cmd, pvGaClass );
				
				// ���ʂ��o�͂��܂��B
				vOutputData( &cmd, pvGaClass );
			}
			// �I�����������s���܂��B
			vTerminate( &cmd, pvGaClass );
		}
		else
		{
			// �R�}���h�̎g�p���@��\�����܂��B
			cmd.vHelp();
		}
	}
	catch( CCmdCheckException cce )
	{
		std::cout << cce.strGetClassName() << "::" << cce.strGetMethodName() << ":" << cce.strGetErrDetail() << std::endl;
		return cce.iGetErrCode();
	}
	catch( CRealCodedGaException crcgae )
	{
		std::cout << crcgae.strGetClassName() << "::" << crcgae.strGetMethodName() << ":" << crcgae.strGetErrDetail() << std::endl;
		return crcgae.iGetErrCode();
	}
	catch( CUndxException cae )
	{
		std::cout << cae.strGetClassName() << "::" << cae.strGetMethodName() << ":" << cae.strGetErrDetail() << std::endl;
		return cae.iGetErrCode();
	}
	catch( CRexException cre )
	{
		std::cout << cre.strGetClassName() << "::" << cre.strGetMethodName() << ":" << cre.strGetErrDetail() << std::endl;
		return cre.iGetErrCode();
	}
	catch( ... )
	{
		return -1;
	}
	return 0;
}

/**
 *<PRE>
 *  �����������s���܂��B
 *  ver 0.1 ����
 *</PRE>
 * @param pcCmd	�R�}���h�`�F�b�N�N���X
 * @param pvGaClass	�e�����lGA�A���S���Y�������s����N���X�C���X�^���X
 * @throw CUndxException
 * @author kobayashi
 * @since 0.1 2015/07/28
 * @version 0.1
 */
void vInitialize( CCmdCheck *pcCmd, void *pvGaClass )
{
	int iGenerationNumber;
	int iGenDataNum;
	int iGenVectorDimNum;
	int iCrossOverNum;
	double lfAlpha;
	double lfBeta;

	int iChildrenNumber;
	int iParentNumber;
	int iUpperEvalChildrenNumber;
	double lfLearningRate;

	CUndx *pcUndx = NULL;
	CRex *pcRex = NULL;
	CRex *pcARex = NULL;
	
	iGenerationNumber			= pcCmd->iGetGenerationNumber();
	iGenDataNum					= pcCmd->iGetGenDataNum();
	iGenVectorDimNum			= pcCmd->iGetGenVectorDimNum();
	iUpperEvalChildrenNumber	= pcCmd->iGetUpperEvalChildrenNumber();
	lfLearningRate				= pcCmd->lfGetLearningRate();

	// UNDX
	if( pcCmd->iGetGaMethod() == 1 )
	{
		iCrossOverNum		= pcCmd->iGetCrossOverNum();
		lfAlpha				= pcCmd->lfGetAlpha();
		lfBeta				= pcCmd->lfGetBeta();
		pcUndx = (CUndx*)pvGaClass;
		pcUndx->vInitialize( iGenerationNumber, iGenDataNum, iGenVectorDimNum, iCrossOverNum );
//		pcUndx->vSetCrossOverNum( iCrossOverNum );
		pcUndx->vSetAlpha( lfAlpha );
		pcUndx->vSetBeta( lfBeta );
	}
	// REX( RealCoded Ensamble Crossover )
	else if( pcCmd->iGetGaMethod() == 2 )
	{
		iChildrenNumber	= pcCmd->iGetChildrenNumber();
		iParentNumber	= pcCmd->iGetParentNumber();
		pcRex = (CRex*)pvGaClass;
		pcRex->vInitialize( iGenerationNumber, iGenDataNum, iGenVectorDimNum, iParentNumber, iChildrenNumber );
		pcRex->vSetChildrenNumber( iChildrenNumber );
		pcRex->vSetParentNumber( iParentNumber );
	}
	// AREX( Adaptaion RealCoded Ensamble Crossover )
	else if( pcCmd->iGetGaMethod() == 3 )
	{
		iChildrenNumber	= pcCmd->iGetChildrenNumber();
		iParentNumber	= pcCmd->iGetParentNumber();
		pcARex = (CRex*)pvGaClass;
		pcARex->vInitialize( iGenerationNumber, iGenDataNum, iGenVectorDimNum, iParentNumber, iChildrenNumber, lfLearningRate, iUpperEvalChildrenNumber );
		pcARex->vSetChildrenNumber( iChildrenNumber );
		pcARex->vSetParentNumber( iParentNumber );
	}

}

/**
 *<PRE>
 *  �I�����������s���܂��B
 *  ver 0.1 ����
 *</PRE>
 * @param pvGaClass	�e�����lGA�A���S���Y�������s����N���X�C���X�^���X
 * @throw CUndxException
 * @author kobayashi
 * @since 0.1 2015/12/15
 * @version 0.1
 */
void vTerminate( CCmdCheck *pcCmd, void *pvGaClass )
{
	CUndx *pcUndx = NULL;
	CRex *pcRex = NULL;
	CRex *pcARex = NULL;
	
	// UNDX
	if( pcCmd->iGetGaMethod() == 1 )
	{
		pcUndx = (CUndx*)pvGaClass;
		// �ړI�֐��̃A���C���X�g�[�������s���܂��B
		pcUndx->vReleaseCallConstraintFunction();
		
		// �����l�f�`�̏������I�����܂��B
		pcUndx->vTerminate();
	}
	// REX( RealCoded Ensamble Crossover )
	else if( pcCmd->iGetGaMethod() == 2 )
	{
		pcRex = (CRex*)pvGaClass;
		// �ړI�֐��̃A���C���X�g�[�������s���܂��B
		pcRex->vReleaseCallConstraintFunction();
		
		// �����l�f�`�̏������I�����܂��B
		pcRex->vTerminate();
	}
	// AREX( Adaptaion RealCoded Ensamble Crossover )
	else if( pcCmd->iGetGaMethod() == 3 )
	{
		pcARex = (CRex*)pvGaClass;
		// �ړI�֐��̃A���C���X�g�[�������s���܂��B
		pcARex->vReleaseCallConstraintFunction();
		
		// �����l�f�`�̏������I�����܂��B
		pcARex->vTerminate();
	}
}

/**
 *<PRE>
 *  �ړI�֐���ݒ肵�܂��B
 *  ver 0.1 ����
 *</PRE>
 * @param pcCmd	�R�}���h�`�F�b�N�N���X
 * @param pvGaClass	�e�����lGA�A���S���Y�������s����N���X�C���X�^���X
 * @throw CUndxException
 * @author kobayashi
 * @since 0.1 2015/12/15
 * @version 0.1
 */
void vSetObjectiveFunction( CCmdCheck *pcCmd, void *pvGaClass )
{
	CUndx *pcUndx = NULL;
	CRex *pcRex = NULL;
	CRealCodedGa *pcRealCodedGa = NULL;
	
	pcRealCodedGa = (CRealCodedGa*)pvGaClass;
	if( strcmp(pcCmd->pcGetFuncName(), "sphere" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfSphere );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "hyper-ellipsoid" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfHyperEllipsoid );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "axis-parallel-hyper-ellipsoid" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfAxisParallelHyperEllipsoid );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "rotated-hyper-ellipsoid" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfRotatedHyperEllipsoid );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "moved-axis-parallel-hyper-ellipsoid" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfMovedAxisParallelHyperEllipsoid );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "sum-of-different-power" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfSumOfDifferentPower );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "rosenbrock" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfRosenbrock );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "rastrigin" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfRastrigin );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "griewank" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfGriewank );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "3rd-de-jongs" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lf3rdDeJongsFunc );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "modified-3rd-de-jongs" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfModified3rdDeJongsFunc );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "4th-de-jongs" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lf4thDeJongsFunc );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "modified-4th-de-jongs" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfModified4thDeJongsFunc );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "5th-de-jongs" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lf5thDeJongsFunc );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "Ackley" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfAckley );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "Branins" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfBraninsRCos );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "Schwefel" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfSchwefel );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "katsuura" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfKatsuura );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "langermann" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfLangermann );
	}
	else if( strcmp(pcCmd->pcGetFuncName(), "Shubert" ) == 0 )
	{
		pcRealCodedGa->vSetConstraintFunction( lfShubert );
	}
	else
	{
	}
}

/**
 *<PRE>
 *  �����l�f�`�����s���܂��B
 *  ver 0.1 ����
 *</PRE>
 * @param pcCmd	�R�}���h�`�F�b�N�N���X
 * @param pvGaClass	�e�����lGA�A���S���Y�������s����N���X�C���X�^���X
 * @throw CUndxException
 * @author kobayashi
 * @since 0.1 2015/07/28
 * @version 0.1
 */
void vStartGa( CCmdCheck *pcCmd, void *pvGaClass )
{
	CUndx *pcUndx = NULL;
	CRex *pcRex = NULL;
	CRex *pcARex = NULL;
	
	// UNDX
	if( pcCmd->iGetGaMethod() == 1 )
	{
		pcUndx = (CUndx*)pvGaClass;
		pcUndx->vImplement();
	}
	// REX
	else if( pcCmd->iGetGaMethod() == 2 )
	{
		pcRex = (CRex*)pvGaClass;
		pcRex->vRex();
	}
	// AREX
	else if( pcCmd->iGetGaMethod() == 3 )
	{
		pcARex = (CRex*)pvGaClass;
		pcARex->vARex();
	}
	else
	{
	}
}

/**
 *<PRE>
 *  �����l�f�`�����s�������ʂ��o�͂��܂��B
 *  ver 0.1 ����
 *</PRE>
 * @param pcCmd	�R�}���h�`�F�b�N�N���X
 * @param pvGaClass	�e�����lGA�A���S���Y�������s����N���X�C���X�^���X
 * @throw CUndxException
 * @author kobayashi
 * @since 0.1 2015/07/28
 * @version 0.1
 */
void vOutputData( CCmdCheck *pcCmd, void *pvGaClass )
{
	CUndx *pcUndx = NULL;
	CRex *pcRex = NULL;
	CRex *pcARex = NULL;
	
//	printf("�o�̓t���O�F%d\n",pcCmd->iGetOutputFlag());
	if( pcCmd->iGetOutputFlag() == 1 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vOutputGenData();
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vOutputGenData();
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vOutputGenData();
		}
	}
	else if( pcCmd->iGetOutputFlag() == 2 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vOutputConstraintFunction();
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vOutputConstraintFunction();
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vOutputConstraintFunction();
		}
	}
	else if( pcCmd->iGetOutputFlag() == 3 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vOutputGlobalMaxGenData();
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vOutputGlobalMaxGenData();
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vOutputGlobalMaxGenData();
		}
	}
	else if( pcCmd->iGetOutputFlag() == 4 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vOutputGlobalMaxConstFuncValue();
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vOutputGlobalMaxConstFuncValue();
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vOutputGlobalMaxConstFuncValue();
		}
	}
	else if( pcCmd->iGetOutputFlag() == 5 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vOutputGlobalMaxGenDataConstFuncValue();
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vOutputGlobalMaxGenDataConstFuncValue();
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vOutputGlobalMaxGenDataConstFuncValue();
		}
	}
	else if( pcCmd->iGetOutputFlag() == 6 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vSetParentOutputFlag( 1 );
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vSetParentOutputFlag( 1 );
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vSetParentOutputFlag( 1 );
		}
	}
	else if( pcCmd->iGetOutputFlag() == 7 )
	{
		if( pcCmd->iGetGaMethod() == 1 )
		{
			pcUndx = (CUndx*)pvGaClass;
			pcUndx->vSetChildrenOutputFlag( 1 );
		}
		else if( pcCmd->iGetGaMethod() == 2 )
		{
			pcRex = (CRex*)pvGaClass;
			pcRex->vSetChildrenOutputFlag( 1 );
		}
		else if( pcCmd->iGetGaMethod() == 3 )
		{
			pcARex = (CRex*)pvGaClass;
			pcARex->vSetChildrenOutputFlag( 1 );
		}
	}
}

/**
 *<PRE>
 *  �o�ꂷ�闱�q�̒l�������_���ɐݒ肵�܂��B
 *  ver 0.1 ����
 *</PRE>
 * @param pcCmd	�R�}���h�`�F�b�N�N���X
 * @param pvGaClass	�e�����lGA�A���S���Y�������s����N���X�C���X�^���X
 * @throw CUndxException
 * @author kobayashi
 * @since 0.1 2015/07/28
 * @version 0.1
 */
void vSetRandom( CCmdCheck *pcCmd, void *pvGaClass )
{
	CUndx *pcUndx = NULL;
	CRex *pcRex = NULL;
	CRex *pcARex = NULL;
	
	if( pcCmd->iGetGaMethod() == 1 )
	{
		pcUndx = (CUndx*)pvGaClass;
		pcUndx->vSetRandom( pcCmd->lfGetRangeMin(), pcCmd->lfGetRangeMax() );
	}
	else if( pcCmd->iGetGaMethod() == 2 )
	{
		pcRex = (CRex*)pvGaClass;
		pcRex->vSetRandom( pcCmd->lfGetRangeMin(), pcCmd->lfGetRangeMax() );
	}
	else if( pcCmd->iGetGaMethod() == 3 )
	{
		pcARex = (CRex*)pvGaClass;
		pcARex->vSetRandom( pcCmd->lfGetRangeMin(), pcCmd->lfGetRangeMax() );
	}
}
