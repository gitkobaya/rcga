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
	 * 入力されたコマンドを解析
	 *</PRE>
	 * @author kobayashi
	 * @param argc
	 * @param argv
	 * @version 1.0
	 */
	long lCommandCheck( int argc, char* argv[] );

	/**
	 *<PRE>
	 * 入力されたコマンドがフォーマットに適していない場合、エラーを返却
	 *</PRE>
	 * @author kobayashi
	 * @param argc
	 * @param argv
	 * @version 1.0
	 */
	long lCommandErrorCheck( char* argv );
	
	/**
	 *<PRE>
	 * 使用方法を表示する。
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
	int iGenerationNumber;		// 計算回数
	int iGenDataNum;			// 遺伝子の数
	int iGenVectorDimNum;		// 各遺伝子の特徴ベクトル
	int iGaMethod;				// 実数値ＧＡの手法設定
	char* pcFuncName;			// 使用する関数用フラグ
	int iOutputFlag;			// 結果出力用フラグ
	double lfRangeMin;			// 目的関数の探索領域の最小値
	double lfRangeMax;			// 目的関数の探索領域の最大値
	// UNDX用パラメータ
	int iCrossOverNum;			// 交叉回数
	double lfAlpha;				// 第一親と第二親との分散の調整パラメータ
	double lfBeta;				// 第一親第二親と第三親との分散の調整パラメータ)
	// REX用パラメータ
	int iChildrenNumber;		// 生成する子供の個数
	int iParentNumber;			// 生成する親の個数（次元数を超える数を指定する。）
	// AREX用パラメータ
	int iUpperEvalChildrenNumber;	// 評価値上位の子供の個数
	double lfLearningRate;			// 学習率

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
