#ifndef _CREX_H_
#define _CREX_H_

#include"CRealCodedGa.h"
#include<vector>

const int REX_SUCCESS				= 0;
const int REX_FATAL_ERROR			= -301;
const int REX_MEMORY_ALLOCATE_ERROR = -302;
const int REX_MEMORY_RELEASE_ERROR	= -303;
const int REX_ARRAY_INDEX_ERROR		= -304;

class CRex : public CRealCodedGa
{
public:
	CRex();
	virtual ~CRex();

public:
	void vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData, int iParentNumberData, int iChildrenNumberData );
	void vInitialize( int iGenerationNum, int iGenNum, int iGenVectorData, int iParentNumberData, int iChildrenNumberData, double lfLearningRateData,int iUpperEvalChildrenNum );
	void vRex();
	void vRexStar();
	void vARex();
	void vTerminate();

	// ���J�֐�get set �֐��Q
public:
	inline int iGetParentNumber(){return iParentNumber; };
	inline int iGetChildrenNumber(){return iChildrenNumber; };
	inline void vSetParentNumber( int iData ) {iParentNumber = iData; };
	inline void vSetChildrenNumber( int iData ) {iChildrenNumber = iData; };
	inline void vSetParentOutputFlag( int iData ){iParentOutputFlag = iData;};
	inline int iGetParentOutputFlag(){ return iParentOutputFlag; };
	inline void vSetChildrenOutputFlag( int iData ){iChildrenOutputFlag = iData;};
	inline int iGetChildrenOutputFlag(){ return iChildrenOutputFlag; };

	/**
	 * <PRE>
	 * �@�����_�ł̑I�������e���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 0.1
	 */
	void vOutputCurrentParent( std::vector<int> stlSelectParentLocData );

	/**
	 * <PRE>
	 * �@�����_�ł̐��������q���o�͂��܂��B
	 * </PRE>
	 * @author kobayashi
	 * @since 2015/12/16
	 * @version 0.1
	 */
	void vOutputCurrentChildren( double **pplfChildrenData );

private:
	int iParentOutputFlag;
	int iChildrenOutputFlag;
	int iParentNumber;
	int iChildrenNumber;
	int iUpperEvalChildrenNumber;
	double **pplfChildren;
	double *plfTempVector;
	double *plfCentroid;
	double *plfChildVector;
	double *plfChildCentroid;
	double *plfUpperEvalCentroid;
	double *plfNormalizeRand;
	double *plfChildrenCentroid;
	double *plfUpperEvalChildrenCentroid;
	double lfLcdp;
	double lfLavg;
	double lfLearningRate;
	double lfAlpha;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////CRexException�N���X

class CRexException
{
public:
	CRexException();
	CRexException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail );
	CRexException( int iCode, std::string sMethodName, std::string sClassName, std::string sDetail, int iErrorLine );
	~CRexException();
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


#endif /* _CREX_H_ */