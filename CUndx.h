#ifndef _CUNDX_H_
#define _CUNDX_H_

#include"CRealCodedGa.h"
#include<vector>

const int UNDX_SUCCESS = 0;
const int UNDX_FATAL_ERROR = -201;
const int UNDX_MEMORY_ALLOCATE_ERROR = -202;
const int UNDX_MEMORY_RELEASE_ERROR = -203;
const int UNDX_ARRAY_INDEX_ERROR = -204;

class CUndx : public CRealCodedGa
{
public:
	CUndx();
	virtual ~CUndx();

	// ���J�֐�
public:
	void vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData, int iCrossOverNumData );
	void vImplement();
	void vTerminate();
	inline void vSetCrossOverNum( int iData ){iCrossOverNum = iData;};
	inline int iGetCrossOverNum(){ return iCrossOverNum;};

	// ���J�֐�get set �֐��Q
public:
	inline void vSetAlpha( double lfAlphaData ){ lfAlpha = lfAlphaData; };
	inline double lfGetAlpha(){ return lfAlpha; };
	inline void vSetBeta( double lfBetaData ){ lfBeta = lfBetaData; };
	inline double lfGetBeta(){ return lfBeta; };
	inline void vSetParentOutputFlag( int iData ){iParentOutputFlag = iData;};
	inline int iGetParentOutputFlag(){ return iParentOutputFlag; };
	inline void vSetChildrenOutputFlag( int iData ){iChildrenOutputFlag = iData;};
	inline int iGetChildrenOutputFlag(){ return iChildrenOutputFlag; };

public:
	/**
	 * <PRE>
	 * �@�����_�ł̑I�������e���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 0.1
	 */
	void vOutputCurrentParent( double *plfParent1, double *plfParent2 );

	/**
	 * <PRE>
	 * �@�����_�ł̐��������q���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 0.1
	 */
	void vOutputCurrentChildren( double** pplfChildrenData );


	// ����J�֐�
private:
	void vSelectParent( double **pplfParent1, double **pplfParent2, double **pplfParent3, int *piLoc1, int *piLoc2, int *piLoc3 );
	void vUndx( double *plfParent1, double *plfParent2, double *plfParent3, double lfAlpha, double lfBeta, double *plfChild1, double *plfChild2 );
	void vSelectGens( double** pplfChildren, int *pi1stGenLoc, int *pi2ndGenLoc );
	double normalRand( double sigma, double mean );

	// �����o�ϐ�
private:
	int iCrossOverNum;
	int iChildrenNumber;
	double lfAlpha;
	double lfBeta;
	int iParentOutputFlag;
	int iChildrenOutputFlag;
	double **pplfChildren;
	double *plfChild1;
	double *plfChild2;
};

class CUndxException
{
public:
	CUndxException();
	CUndxException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail );
	CUndxException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iErrorLine );
	~CUndxException();
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


#endif /* _CUNDX_H_ */