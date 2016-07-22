#include<cmath>
#include<ctime>
#include"mseq.h"
#include"cdfrand.h"

///////////////////////////////////////////////////////////////////////////
/////���K����
double grand(double sigma,double mean)
{
	static int sw = 0;
	static double u1 = 0;
	static double u2 = 0;
	static double t = 0.0;
	static double u = 0.0;
//	initrand( time(NULL) );
//	initrnd();
	if(sw == 0)
	{
		sw = 1;
		u1 = 1.0/((double)(RAND_MAX+1.0))*(double)mrand();
		u2 = 1.0/((double)(RAND_MAX+1.0))*(double)mrand();
		t = sqrt(-2.0*log(1.0-u1));
		u = cos(2*pi*u2);
	}
	else
	{
		sw = 0;
		u = sin(2*pi*u2);
	}
	return sigma*t*u+mean;
}

//////////////////////////////////////////////////////////////////////////
/////�|�A�\�����z�ɏ]������
double prand(double mean)
{
	return 0.0;
}

