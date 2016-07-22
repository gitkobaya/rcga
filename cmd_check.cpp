#include <iostream>
#include <cstdio>
#include <cstdarg>
#include<cstdlib>
#include<cstring>
#include "cmd_check.h"

CCmdCheck::CCmdCheck()
{
	iGenerationNumber = 0;
	iGenDataNum = 0;
	iGenVectorDimNum = 0;
	iCrossOverNum = 0;
	iGaMethod = 0;				// �����l�f�`�̎�@�ݒ�
	iOutputFlag = 0;
	pcFuncName = NULL;
	lfAlpha = 0.0;
	lfBeta = 0.0;
	lfRangeMin = 0.0;
	lfRangeMax = 0.0;
}

CCmdCheck::~CCmdCheck()
{
}

/**
 *<PRE>
 *  ���͂��ꂽ�R�}���h���`�F�b�N
 *  ver 0.1 ����
 *  ver 0.2 �I�v�V�������̒ǉ��A����т��̂ق��̏C���B
 *  ver 0.3 �l�H�m�\�p�O���t�����c�[���쐬�̂��ߐV���ɏC���B
 *</PRE>
 * @param argc	�R�}���h�̓��͍��ڐ�
 * @param argv	���͂����R�}���h�̏ڍ�
 * @return	CCMD_SUCCESS
 * 			CCMD_ERROR_INVALID_FORMAT
 * 			CCMD_ERROR_INVALID_DATA
 * 			CCMD_ERROR_MEMORY_ALLOCATE
 * 			CCMD_ERROR_MEMORY_RELEASE
 * @author kobayashi
 * @since 0.1 2014/05/02
 * @version 0.1
 */
long CCmdCheck::lCommandCheck( int argc, char* argv[] )
{
	int i;
	long lRet = 0;
	CCmdCheckException cce;

	/* �R�}���h�̃`�F�b�N */
	if( argc <= 1 )
	{
		return CCMD_ERROR_INVALID_FORMAT;
	}
	if( argv == NULL )
	{
		cce.SetErrorInfo( CCMD_ERROR_INVALID_FORMAT, "lCommandCheck", "CCmdCheck", "�s���ȃR�}���h�ł��B", __LINE__ );
		throw( cce );
	}
	for( i=1; i<argc ;i++ )
	{
		/* �v�Z�� */
		if( strcmp( argv[i], "-gn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGenerationNumber = atoi( argv[i+1] );
			i++;
		}
		/* ��`�q�� */
		else if( strcmp( argv[i], "-n" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGenDataNum = atoi( argv[i+1] );
			i++;
		}
		/* ��`�q�̃x�N�g���� */
		else if( strcmp( argv[i], "-gv" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGenVectorDimNum = atoi( argv[i+1] );
			i++;
		}
		/* ��1�e�Ƒ�2�e�����̕��U�̍L����Ɋւ���p�����[�^�[ */
		else if( strcmp( argv[i], "-alpha" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfAlpha = atof( argv[i+1] );
			i++;
		}
		/* �e�Ƒ�3�̐e�����̕��U�̍L����Ɋւ���p�����[�^�[ */
		else if( strcmp( argv[i], "-beta" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfBeta = atof( argv[i+1] );
			i++;
		}
		/* ������ */
		else if( strcmp( argv[i], "-con" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iCrossOverNum = atoi( argv[i+1] );
			i++;
		}
		/* �]�������{����ړI�֐� */
		else if( strcmp( argv[i], "-f" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			pcFuncName = new char[strlen(argv[i+1])+1];
			memset( pcFuncName, '\0', sizeof(pcFuncName) );
			strcpy( pcFuncName, argv[i+1] );
			i++;
		}
		/* �����lGA�̎�@ */
		else if( strcmp( argv[i], "-gm" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGaMethod = atoi( argv[i+1] );
			i++;
		}
		/* ���ʏo�� */
		else if( strcmp( argv[i], "-out" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iOutputFlag = atoi( argv[i+1] );
			i++;
		}
		/* �]���֐��̒�`��̍ŏ��l */
		else if( strcmp( argv[i], "-dmin" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfRangeMin = atof( argv[i+1] );
			i++;
		}
		/* �]���֐��̒�`��̍ő�n */
		else if( strcmp( argv[i], "-dmax" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfRangeMax = atof( argv[i+1] );
			i++;
		}
		/* �e���̐ݒ� */
		else if( strcmp( argv[i], "-pn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iParentNumber = atoi( argv[i+1] );
			i++;
		}
		/* �q���̌��ݒ� */
		else if( strcmp( argv[i], "-cn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iChildrenNumber = atoi( argv[i+1] );
			i++;
		}
		/* �]���l��ʂ̎q���̌� */
		else if( strcmp( argv[i], "-uecn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iUpperEvalChildrenNumber = atoi( argv[i+1] );
			i++;
		}
		/* �w�K�� */
		else if( strcmp( argv[i], "-lr" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfLearningRate = atoi( argv[i+1] );
			i++;
		}
		/* �w���v�̕\�� */
		else if( strcmp( argv[i], "-h" ) == 0 )
		{
			vHelp();
		}
		else
		{
			lRet = CCMD_ERROR_INVALID_DATA;
			break;
		}
	}
	return lRet;
}

/**
 *<PRE>
 * ���̓I�v�V�������ǂ������`�F�b�N����
 * ver 0.1 �V�K�쐬
 * ver 0.2 �l�H�m�\�p�O���t�����c�[���쐬�p�ɏC���B
 *</PRE>
 * @param argc
 * @param argv
 * @return 0
 *		  -1
 *        -2
 * @author kobayashi
 * @since 2013/1/1
 * @version 0.2
 */
long CCmdCheck::lCommandErrorCheck( char *argv )
{
	long lRet = 0L;
	if( ( strcmp( argv, "-gn" ) == 0 ) ||
		( strcmp( argv, "-n" ) == 0 ) ||
		( strcmp( argv, "-gv" ) == 0 ) ||
		( strcmp( argv, "-alpha" ) == 0 ) ||
		( strcmp( argv, "-beta" ) == 0 ) ||
		( strcmp( argv, "-con" ) == 0 ) ||
		( strcmp( argv, "-gm" ) == 0 ) ||
		( strcmp( argv, "-f" ) == 0 )  ||
		( strcmp( argv, "-dmin" ) == 0 )  ||
		( strcmp( argv, "-dmax" ) == 0 )  ||
		( strcmp( argv, "-pn" ) == 0 )  ||
		( strcmp( argv, "-cn" ) == 0 )  ||
		( strcmp( argv, "-out" ) == 0 ) ||
		( strcmp( argv, "-lr" ) == 0 ) ||
		( strcmp( argv, "-uecn" ) == 0 ) ||
		( strcmp( argv, "-h" ) == 0 ))
	{
		lRet = 0;
	}
	else
	{
		lRet = -2;
	}
	return lRet;
}

/**
 *<PRE>
 * �g�p���@��\������B
 *</PRE>
 * @author kobayashi
 * @since 2015/6/10
 * @version 0.2
 */
void CCmdCheck::vHelp()
{
	printf("�����l�f�`�v�Z\n");
	printf("�g�p���@\n");
	printf("rga [-f]\n");
	printf("-gn �X�V��\n");
	printf("-n ��`�q�̐�\n");
	printf("-gv ��`�q�̃x�N�g����\n");
	printf("-alpha ���e�Ƒ��e�̕��U�l�𒲐�����p�����[�^\n");
	printf("-beta ���e���e�Ƒ�O�e�̕��U�l�𒲐�����p�����[�^\n");
	printf("-con ������\n");
	printf("-pn �e�̌��iREX�Ŏg�p�j\n");
	printf("-cn �����񐔁iREX�Ŏg�p�j\n");
	printf("-gm �����l�f�`�̎�@�ݒ�\n");
	printf("-f ���p����֐�\n");
	printf("-dmin �]���֐��̒�`��̍ŏ��l\n");
	printf("-dmax �]���֐��̒�`��̍ő�l\n");
	printf("-out ���ʏo��\n");
}

double CCmdCheck::lfGetAlpha()
{
	return lfAlpha;
}

double CCmdCheck::lfGetBeta()
{
	return lfBeta;
}

int CCmdCheck::iGetCrossOverNum()
{
	return iCrossOverNum;
}

char* CCmdCheck::pcGetFuncName()
{
	return pcFuncName;
}

int CCmdCheck::iGetGenerationNumber()
{
	return iGenerationNumber;
}

int CCmdCheck::iGetGenDataNum()
{
	return iGenDataNum;
}

int CCmdCheck::iGetGenVectorDimNum()
{
	return iGenVectorDimNum;
}

int CCmdCheck::iGetGaMethod()
{
	return iGaMethod;
}

int CCmdCheck::iGetOutputFlag()
{
	return iOutputFlag;
}

double CCmdCheck::lfGetRangeMin()
{
	return lfRangeMin;
}

double CCmdCheck::lfGetRangeMax()
{
	return lfRangeMax;
}

int CCmdCheck::iGetChildrenNumber()
{
	return iChildrenNumber;
}

int CCmdCheck::iGetParentNumber()
{
	return iParentNumber;
}

int CCmdCheck::iGetUpperEvalChildrenNumber()
{
	return iUpperEvalChildrenNumber;
}

double CCmdCheck::lfGetLearningRate()
{
	return lfLearningRate;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////CCmdCheckException�N���X

/**
 * <PRE>
 * �R���X�g���N�^(�G���[����ݒ肷��)
 * </PRE>
 * @author kobayashi
 * @since 2015/6/10
 * @version 1.0
 */
CCmdCheckException::CCmdCheckException()
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
 * @since 2009/6/14
 * @version 1.0
 */
CCmdCheckException::CCmdCheckException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
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
 * @since 2009/6/14
 * @version 1.0
 */
CCmdCheckException::CCmdCheckException(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
{
	iErrCode = iCode;
	iErrLine = iLine;
	strMethodName = sMethodName;
	strClassName = sClassName;
	strErrDetail = sDetail;
}


/**
 * <PRE>
 * �f�X�g���N�^
 * </PRE>
 * @author kobayashi
 * @since 2015/6/10
 * @version 1.0
 */
CCmdCheckException::~CCmdCheckException()
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
 * @since 2009/6/14
 * @version 1.0
 */
void CCmdCheckException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail)
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
 * @since 2009/6/14
 * @version 1.0
 */
void CCmdCheckException::SetErrorInfo(int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iLine)
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
 * @since 2009/6/14
 * @version 1.0
 */
int CCmdCheckException::iGetErrCode()
{
	return iErrCode;
}

/**
 * �G���[���N�������s�����o�͂���
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
int CCmdCheckException::iGetErrLine()
{
	return iErrLine;
}

/**
 * �G���[���N�������֐������o�͂���
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
std::string CCmdCheckException::strGetMethodName()
{
	return strMethodName;
}

/**
 * �G���[���N�������N���X���o�͂���
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
std::string CCmdCheckException::strGetClassName()
{
	return strClassName;
}

/**
 * �G���[�̏ڍ׏����o�͂���
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
std::string CCmdCheckException::strGetErrDetail()
{
	return strErrDetail;
}
