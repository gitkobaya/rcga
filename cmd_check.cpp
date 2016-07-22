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
	iGaMethod = 0;				// 実数値ＧＡの手法設定
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
 *  入力されたコマンドをチェック
 *  ver 0.1 初版
 *  ver 0.2 オプション等の追加、およびそのほかの修正。
 *  ver 0.3 人工知能用グラフ生成ツール作成のため新たに修正。
 *</PRE>
 * @param argc	コマンドの入力項目数
 * @param argv	入力したコマンドの詳細
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

	/* コマンドのチェック */
	if( argc <= 1 )
	{
		return CCMD_ERROR_INVALID_FORMAT;
	}
	if( argv == NULL )
	{
		cce.SetErrorInfo( CCMD_ERROR_INVALID_FORMAT, "lCommandCheck", "CCmdCheck", "不正なコマンドです。", __LINE__ );
		throw( cce );
	}
	for( i=1; i<argc ;i++ )
	{
		/* 計算回数 */
		if( strcmp( argv[i], "-gn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGenerationNumber = atoi( argv[i+1] );
			i++;
		}
		/* 遺伝子数 */
		else if( strcmp( argv[i], "-n" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGenDataNum = atoi( argv[i+1] );
			i++;
		}
		/* 遺伝子のベクトル数 */
		else if( strcmp( argv[i], "-gv" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGenVectorDimNum = atoi( argv[i+1] );
			i++;
		}
		/* 第1親と第2親方向の分散の広がりに関するパラメーター */
		else if( strcmp( argv[i], "-alpha" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfAlpha = atof( argv[i+1] );
			i++;
		}
		/* 親と第3の親方向の分散の広がりに関するパラメーター */
		else if( strcmp( argv[i], "-beta" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfBeta = atof( argv[i+1] );
			i++;
		}
		/* 交叉回数 */
		else if( strcmp( argv[i], "-con" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iCrossOverNum = atoi( argv[i+1] );
			i++;
		}
		/* 評価を実施する目的関数 */
		else if( strcmp( argv[i], "-f" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			pcFuncName = new char[strlen(argv[i+1])+1];
			memset( pcFuncName, '\0', sizeof(pcFuncName) );
			strcpy( pcFuncName, argv[i+1] );
			i++;
		}
		/* 実数値GAの手法 */
		else if( strcmp( argv[i], "-gm" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iGaMethod = atoi( argv[i+1] );
			i++;
		}
		/* 結果出力 */
		else if( strcmp( argv[i], "-out" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iOutputFlag = atoi( argv[i+1] );
			i++;
		}
		/* 評価関数の定義域の最小値 */
		else if( strcmp( argv[i], "-dmin" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfRangeMin = atof( argv[i+1] );
			i++;
		}
		/* 評価関数の定義域の最大地 */
		else if( strcmp( argv[i], "-dmax" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfRangeMax = atof( argv[i+1] );
			i++;
		}
		/* 親個数の設定 */
		else if( strcmp( argv[i], "-pn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iParentNumber = atoi( argv[i+1] );
			i++;
		}
		/* 子供の個数設定 */
		else if( strcmp( argv[i], "-cn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iChildrenNumber = atoi( argv[i+1] );
			i++;
		}
		/* 評価値上位の子供の個数 */
		else if( strcmp( argv[i], "-uecn" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			iUpperEvalChildrenNumber = atoi( argv[i+1] );
			i++;
		}
		/* 学習率 */
		else if( strcmp( argv[i], "-lr" ) == 0 )
		{
			lRet = lCommandErrorCheck( argv[i] );
			if( lRet != 0 ) return lRet;
			lfLearningRate = atoi( argv[i+1] );
			i++;
		}
		/* ヘルプの表示 */
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
 * 入力オプションかどうかをチェックする
 * ver 0.1 新規作成
 * ver 0.2 人工知能用グラフ生成ツール作成用に修正。
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
 * 使用方法を表示する。
 *</PRE>
 * @author kobayashi
 * @since 2015/6/10
 * @version 0.2
 */
void CCmdCheck::vHelp()
{
	printf("実数値ＧＡ計算\n");
	printf("使用方法\n");
	printf("rga [-f]\n");
	printf("-gn 更新回数\n");
	printf("-n 遺伝子の数\n");
	printf("-gv 遺伝子のベクトル数\n");
	printf("-alpha 第一親と第二親の分散値を調整するパラメータ\n");
	printf("-beta 第一親第二親と第三親の分散値を調整するパラメータ\n");
	printf("-con 交叉回数\n");
	printf("-pn 親の個数（REXで使用）\n");
	printf("-cn 交叉回数（REXで使用）\n");
	printf("-gm 実数値ＧＡの手法設定\n");
	printf("-f 利用する関数\n");
	printf("-dmin 評価関数の定義域の最小値\n");
	printf("-dmax 評価関数の定義域の最大値\n");
	printf("-out 結果出力\n");
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
////////////////CCmdCheckExceptionクラス

/**
 * <PRE>
 * コンストラクタ(エラー情報を設定する)
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
 * コンストラクタ(エラー情報を設定する)
 * @param iCode       エラーコード
 * @param sMethodName 関数名
 * @param sClassName  クラス名
 * @param sDetail     エラー詳細
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
 * コンストラクタ(エラー情報を設定する)
 * @param iCode       エラーコード
 * @param iLine       行数
 * @param sMethodName 関数名
 * @param sClassName  クラス名
 * @param sDetail     エラー詳細
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
 * デストラクタ
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
 * コンストラクタ(エラー情報を設定する)
 * @param iCode       エラーコード
 * @param sMethodName 関数名
 * @param sClassName  クラス名
 * @param sDetail     エラー詳細
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
 * コンストラクタ(エラー情報を設定する)
 * @param iCode       エラーコード
 * @param iLine       行数
 * @param sMethodName 関数名
 * @param sClassName  クラス名
 * @param sDetail     エラー詳細
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
 * エラー番号を出力する
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
int CCmdCheckException::iGetErrCode()
{
	return iErrCode;
}

/**
 * エラーを起こした行数を出力する
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
int CCmdCheckException::iGetErrLine()
{
	return iErrLine;
}

/**
 * エラーを起こした関数名を出力する
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
std::string CCmdCheckException::strGetMethodName()
{
	return strMethodName;
}

/**
 * エラーを起こしたクラスを出力する
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
std::string CCmdCheckException::strGetClassName()
{
	return strClassName;
}

/**
 * エラーの詳細情報を出力する
 * @author kobayashi
 * @since 2009/6/14
 * @version 1.0
 */
std::string CCmdCheckException::strGetErrDetail()
{
	return strErrDetail;
}
