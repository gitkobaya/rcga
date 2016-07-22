#ifndef _CCMD_CHECK_H_
#define _CCMD_CHECK_H_

#include<string>

#define CCMD_SUCCESS							 0
#define CCMD_ERROR_INVALID_FORMAT				-1
#define CCMD_ERROR_INVALID_DATA					-2
#define CCMD_ERROR_MEMORY_ALLOCATE				-3
#define CCMD_ERROR_MEMORY_RELEASE				-4

class CCmdCheck
{
public:
	CCmdCheck();
	virtual ~CCmdCheck();
	
	/**
	 *<PRE>
	 * ���͂��ꂽ�R�}���h�����
	 *</PRE>
	 * @author kobayashi
	 * @param argc
	 * @param argv
	 * @version 1.0
	 */
	long lCommandCheck( int argc, char* argv[] );

	/**
	 *<PRE>
	 * ���͂��ꂽ�R�}���h���t�H�[�}�b�g�ɓK���Ă��Ȃ��ꍇ�A�G���[��ԋp
	 *</PRE>
	 * @author kobayashi
	 * @param argc
	 * @param argv
	 * @version 1.0
	 */
	long lCommandErrorCheck( char* argv );
	
	/**
	 *<PRE>
	 * �g�p���@��\������B
	 *</PRE>
	 * @author kobayashi
	 * @since 2015/6/10
	 * @version 0.2
	 */
	void vHelp();

public:

	int iGetGenerationNumber();
	int iGetGenDataNum();
	int iGetGenVectorDimNum();
	char* pcGetFuncName();
	int iGetGaMethod();
	int iGetOutputFlag();
	double lfGetRangeMin();
	double lfGetRangeMax();

	double lfGetAlpha();
	double lfGetBeta();
	int iGetCrossOverNum();

	int iGetChildrenNumber();
	int iGetParentNumber();

	int iGetUpperEvalChildrenNumber();
	double lfGetLearningRate();

private:
	int iGenerationNumber;		// �v�Z��
	int iGenDataNum;			// ��`�q�̐�
	int iGenVectorDimNum;		// �e��`�q�̓����x�N�g��
	int iGaMethod;				// �����l�f�`�̎�@�ݒ�
	char* pcFuncName;			// �g�p����֐��p�t���O
	int iOutputFlag;			// ���ʏo�͗p�t���O
	double lfRangeMin;			// �ړI�֐��̒T���̈�̍ŏ��l
	double lfRangeMax;			// �ړI�֐��̒T���̈�̍ő�l
	// UNDX�p�p�����[�^
	int iCrossOverNum;			// ������
	double lfAlpha;				// ���e�Ƒ��e�Ƃ̕��U�̒����p�����[�^
	double lfBeta;				// ���e���e�Ƒ�O�e�Ƃ̕��U�̒����p�����[�^)
	// REX�p�p�����[�^
	int iChildrenNumber;		// ��������q���̌�
	int iParentNumber;			// ��������e�̌��i�������𒴂��鐔���w�肷��B�j
	// AREX�p�p�����[�^
	int iUpperEvalChildrenNumber;	// �]���l��ʂ̎q���̌�
	double lfLearningRate;			// �w�K��

};

class CCmdCheckException
{
public:
	CCmdCheckException();
	CCmdCheckException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail );
	CCmdCheckException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iErrorLine );
	~CCmdCheckException();
	void SetErrorInfo( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail );
	void SetErrorInfo( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iErrorLine );
	int iGetErrCode();
	int iGetErrLine();
	std::string strGetMethodName();
	std::string strGetClassName();
	std::string strGetErrDetail();
private:
	int iErrCode;
	int iErrLine;
	std::string strMethodName;
	std::string strClassName;
	std::string strModuleName;
	std::string strErrDetail;
};

#endif /*_CCMDCHECK_H_*/
