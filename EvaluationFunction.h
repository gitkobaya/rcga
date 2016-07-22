#ifndef _EVALUATION_FUNCTION_H_
#define _EVALUATION_FUNCTION_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////�]���֐�

/**
 * <PRE>
 * �@�ړI�֐���Sphere(1st De Jong's function)�֐��̌v�Z�����s���܂��B
 * �@-5.12 <= x_i <= 5.12 f_i(x_i)=0,  x_i=0, i = 1,2,���,n
 * �@f(x) = sum(x_{i}^{2})
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lfSphere( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Hyper-Ellipsoid�֐��̌v�Z�����s���܂��B
 * �@-1 <= x_i <= 1 f_i(x_i)=0,  x_i=0, i = 1,2,���,n
 * �@f(x) = sum(i^{2}*x_{i}^{2})
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lfHyperEllipsoid( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Axis Parallel hyper-ellipsoid�֐��̌v�Z�����s���܂��B
 * �@-5.12 <= x_i <= 5.12,  f_{i}(x_{i})=0,  x_{i}=0, i = 1,2,���,n
 * �@f(x) = sum(i*x_{i}^{2})
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lfAxisParallelHyperEllipsoid( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Rotated hyper-ellipsoid�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� x_{i} = 0 �̂Ƃ�f(x_{i}) = 0 (-65.536 <= Xi <= 65.536)
 * �@\sum_{i=1}^{n}(\sum_{j=1}^{i}(x_{j}))^{2}
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lfRotatedHyperEllipsoid( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Moved axis parallel hyper-ellipsoid�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� x_{i} = 5i �̂Ƃ�f(x_{i})=0 (-5.12 <= x_{i} <= 5.12)
 * �@\sum{i=1}^{n}(5*i*x_{i}^{2})
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lfMovedAxisParallelHyperEllipsoid( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Sum of different power�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� x_{i}=0 �̂Ƃ� f(x_{i})=0
 *   \sum_{i=1}^{n}|x_{i}|^{i+1}
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lfSumOfDifferentPower( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Rosenbrock(2nd De Jong's function)�֐��̌v�Z�����s���܂��B
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lfRosenbrock( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���3rd De Jong's�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 1 �̂Ƃ�f(Xi) = 0
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lf3rdDeJongsFunc( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Modified 3rd De Jong's�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 1 �̂Ƃ�f(Xi) = 0
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lfModified3rdDeJongsFunc( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���4th DeJong's Function�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 1 �̂Ƃ�f(Xi) = 0
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/12
 * @version 1.0
 */
extern double lf4thDeJongsFunc( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Modified 4th DeJong's Function�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 1 �̂Ƃ�f(Xi) = 0
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/10/16
 * @version 1.0
 */
extern double lfModified4thDeJongsFunc( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���De Jong's f5�֐��̌v�Z�����s���܂��B
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lf5thDeJongsFunc( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Ackley Function�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 0 �̂Ƃ�f(Xi) = 0
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/10/16
 * @version 1.0
 */
extern double lfAckley( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Easom's Function�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = pi �̂Ƃ�f(Xi) = -1
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/10/16
 * @version 1.0
 */
extern double lfEasoms( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Easom's Function(Xin-She Yang extended in 2008 this function to n dimensions)�̌v�Z�����s���܂��B
 *   ���I�œK�� x_{i}=pi �̂Ƃ� f(x_{i}) = -1, -2��<=x_{i}<=2��
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/10/16
 * @version 1.0
 */
extern double lfExtendEasoms( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Griewank�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 0 �̂Ƃ�f(Xi) = 0 (-600 <= Xi <= 600)
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lfGriewank( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Michaelwicz's�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = (X1, X2) = (2.20319, 1.57049) �̂Ƃ�f(Xi) = -1.8013 (-65536 <= Xi <= 65536)
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lfMichaelwicz( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Katsuura's�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 0 �̂Ƃ�f(Xi) = 1 (-1000 <= Xi <= 1000)
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lfKatsuura( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Rastrigin�֐��̌v�Z�����s���܂��B
 * �@���I�œK�� Xi = 0 f(Xi) = 0 (-5.12 <= Xi <= 5.12)
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/17
 * @version 1.0
 */
extern double lfRastrigin( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Schwefel's �֐��̌v�Z�����s���܂��B
 * �@���I�œK�� x_{i}=420.09687 f(x_{i})=-418.9829n (-512<=x_{i}<=512)
 *   \sum^{n}_{i=1}(x_{i}\sin\sqr(|x_{i}|))
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/17
 * @version 1.0
 */
extern double lfSchwefel( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Six-hump camel back �֐��̌v�Z�����s���܂��B
 * �@���I�œK�� (x_{1},x_{2})=420.09687 f(x_{1},x_{2})=-1.0316 (-3<=x_{1}<=3, -2<=x_{2}<=2)
 *   \sum^{n}_{i=1}(x_{i}\sin\sqr(|x_{i}|))
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/17
 * @version 1.0
 */
extern double lfSixHumpCamelBack( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Katsuura's�֐��̌v�Z�����s���܂��B
 *   ���I�œK�� Xi = 0 �̂Ƃ�f(Xi) = 1 (-1000 <= Xi <= 1000)
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/6
 * @version 1.0
 */
extern double lfKatsuura( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Langermann's �֐��̌v�Z�����s���܂��B
 *	 \sum^{m}_{i=1}c_{i}*\exp( -\dfrac{1}{\pi}\sum^{n}_{j=1}(x_{j}-a_{ij})^{2} )cos(\pi\sum^{n}_{j=1}(x_{j}-a_{ij})^{2})
 * �@���I�œK�� -5.12 \leq X_{1}, X_{2} \leq 5.12
 *   M �̒l�͐����l��5�Ƃ���Ă���B
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/17
 * @version 1.0
 */
extern double lfLangermann( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Branins's rcos �֐��̌v�Z�����s���܂��B(2�����֐�)
 * �@���I�œK�� (x_{1},x_{2})=0.397887 f(x_{1},x_{2})=(-��,12.275), (��,2.275) (9.42478,2.475)
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/17
 * @version 1.0
 */
extern double lfBraninsRCos( double *plfX, int iVectorLen );

/**
 * <PRE>
 * �@�ړI�֐���Shubert's �֐��̌v�Z�����s���܂��B(2�����֐�)
 * �@���I�œK�� (x_{1},x_{2})=-186.7309 f(x_{1},x_{2})=-1.0316 (-3<=x_{1}<=3, -2<=x_{2}<=2)
 *   \sum^{n}_{i=1}(i*\cos(i+(i+1x))*\sum^{n}_{i=1}(i*\cos(i+(i+1x))
 * </PRE>
 * @param plfX			����
 * @param iVectorLen	�����̎�����
 * @author kobayashi
 * @since 2015/6/17
 * @version 1.0
 */
extern double lfShubert( double *plfX, int iVectorLen );

#endif /* _EVALUATION_FUNCTION_H_ */