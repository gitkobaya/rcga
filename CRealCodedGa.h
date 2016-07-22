#ifndef _CREAL_CODED_GA_H_
#define _CREAL_CODED_GA_H_

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<memory>
#include<string>

const int RCGA_SUCCESS = 0;
const int RCGA_FATAL_ERROR = -101;
const int RCGA_MEMORY_ALLOCATE_ERROR = -102;
const int RCGA_MEMORY_RELEASE_ERROR = -103;
const int RCGA_ARRAY_INDEX_ERROR = -104;

typedef struct tagRank_t
{
	double lfFitProb;
	int iLoc;
}Rank_t;

class CRealCodedGa
{
public:
	CRealCodedGa();
	CRealCodedGa( int iGenerationNum, int iGenNum, int iGenVectorData );
	virtual ~CRealCodedGa();
	void vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData );
	void vSetRandom();
	void vSetRandom( double lfDomainMin, double lfDomainMax );
	void vTerminate();
	/**
	 * 	<PRE>
     * �@�ړI�֐����C���X�g�[�����܂��B
	 * �@���ۂɂ̓R�[���o�b�N�֐����C���X�g�[�����܂��B
	 * </PRE>
	 * @param pflfFunction �ړI�֐��̊֐��|�C���^
	 * @author kobayashi
	 * @since 2015/10/30
	 * @version 1.0
	 */
	void vSetConstraintFunction( double (*pflfFunction)( double *plfData, int iVectorLen ) );

	/**
	 * <PRE>
	 * �@�ړI�֐����A���C���X�g�[�����܂��B
	 * �@���ۂɂ̓R�[���o�b�N�֐����A���C���X�g�[�����܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/10/30
	 * @version 1.0
	 */
	void vReleaseCallConstraintFunction();

	/**
	  *<PRE>
	  * �R�[���o�b�N�֐��̒�`�ł��B
	  *</PRE>
	  */
	double (*pflfConstraintFunction)( double *pplfData, int iVectorLen );

	/**
	 * <PRE>
	 * �@�����l�f�`�̌��ʂ��o�͂��܂��B(�e��`�q�̃x�N�g��)
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 1.0
	 */
	void vOutputGenData();

	/**
	 * <PRE>
	 * �@���݂̎����lGA�ɖړI�֐���K�p�������ʂ��o�͂��܂��B(�e��`�q�̖ړI�֐��l)
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 1.0
	 */
	void vOutputConstraintFunction();
	
	/**
	 * <PRE>
	 * �@�����_�ł̂����Ƃ��悢��`�q�̈ʒu���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 1.0
	 */
	void vOutputGlobalMaxGenData();

	/**
	 * <PRE>
	 * �@�����_�ł̂����Ƃ��悢��`�q�̖ړI�֐��l���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 1.0
	 */
	void vOutputGlobalMaxConstFuncValue();

	 /**
	 * <PRE>
	 * �@�����_�ł̂����Ƃ��悢��`�q�y�т��̖ړI�֐��l���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 1.0
	 */
	void vOutputGlobalMaxGenDataConstFuncValue();

protected:
	int iGenerationNumber;
	int iGenNumber;
	int iGenVector;
	double **pplfGens;
};

// �\�[�g�֐��p��r���Z�q�N���X
class CCompareToRank
{
public:
	bool operator()( const Rank_t& tLeft, const Rank_t& tRight )
	{
		return tLeft.lfFitProb < tRight.lfFitProb;
	}
};


class CRealCodedGaException
{
public:
	CRealCodedGaException();
	CRealCodedGaException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail );
	CRealCodedGaException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iErrorLine );
	~CRealCodedGaException();
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

#endif /* _CREAL_CODED_GA_H_ */
