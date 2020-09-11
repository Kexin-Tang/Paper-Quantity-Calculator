#include <stdio.h>
#include <math.h>
#include "cal.h"

extern double CAP_INIT;

void cp_init(CP *cp, Cal *cal)
{
	int i;
	for (i = 0; i < N; i++)
	{
		cp->paper_num[i] = 0;
		cp->cap[i] = 0.00;
		cp->distance[i] = 0.00;
	}

	cal->e = 2.5 * 8.85;
	cal->S = 2.5;
	cal->cap_bias = CAP_INIT;
}

void cap_aquire(int *x, double *y, int start, int stop, CP *cp)
{
	int i;
	for (i = start; i <= stop; i++)
	{
		cp->paper_num[i] = x[i];
		cp->cap[i] = y[i];
	}
}

void cap_to_distance(CP *cp, Cal *cal)
{
	int i;

	for (i = 0; i < N; i++)
	{
		if (cp->paper_num[i])
		{
			cp->distance[i] = cal->e * cal->S / (cp->cap[i] - cal->cap_bias);
		}
	}
}

void linEquSolve(float *mat, int n)
{
	int k, j, i;
	// to up triangular mat
	for (k = 0; k < n - 1; k++)
	{
		// find major row
		int major = k;
		for (j = k + 1; j < n; j++)
		{
			if (mat[j * (n + 1) + k] > mat[major * (n + 1) + k])
				major = j;
		}
		// swap major row
		if (major != k)
		{
			float t;
			for (i = 0; i < n + 1; i++)
			{
				t = mat[k * (n + 1) + i];
				mat[k * (n + 1) + i] = mat[major * (n + 1) + i];
				mat[major * (n + 1) + i] = t;
			}
		}
		// eliminating column k, form row k + 1 to n - 1
		for (j = k + 1; j < n; j++)
		{
			float c = mat[j * (n + 1) + k] / mat[k * (n + 1) + k];
			for (i = k; i < n + 1; i++)
			{
				mat[j * (n + 1) + i] -= mat[k * (n + 1) + i] * c;
			}
		}
	}
	// to 1
	for (k = 0; k < n; k++)
	{
		float c = mat[k * (n + 1) + k];
		for (i = k; i < n + 1; i++)
		{
			mat[k * (n + 1) + i] /= c;
		}
	}
	//
	for (k = n - 1; k >= 1; k--)
	{
		for (j = k - 1; j >= 0; j--)
		{
			float c = mat[j * (n + 1) + k];
			for (i = k; i < n + 1; i++)
			{
				mat[j * (n + 1) + i] -= mat[k * (n + 1) + i] * c;
			}
		}
	}
}

//////////////////////////// ni he ////////////////////////////
// x: a set of 'x' in y=f(x)
// y: a set of 'y' in y=f(x)
// n: the number of elements in this set
// a: the 'a' in 'y=bx+a'
// b: the 'b' in 'y=bx+a'
void irApprox(float *x, float *y, int n, float *a, float *b)
{
	int i;
	float sumx = 0.0f, sumy = 0.0f, sumx2 = 0.0f, sumxy = 0.0f;
	float equ[2][3];
	/*for (i = 0; i < n; i++)
	{
		y[i] = logf(y[i]);
		x[i] = logf(x[i]);
	}*/
	for (i = 0; i < N; i++)
	{
		//printf("paper[%d] = %f, distance[%d] = %f\n", i, x[i], i, y[i]);
		if (x[i] > 0.01)
		{
			sumx += x[i];
			sumy += y[i];
			sumx2 += x[i] * x[i];
			sumxy += x[i] * y[i];
		}
	}
	equ[0][0] = n;
	equ[0][1] = sumx;
	equ[0][2] = sumy;
	equ[1][0] = sumx;
	equ[1][1] = sumx2;
	equ[1][2] = sumxy;
	linEquSolve(&equ[0][0], 2);
	*a = equ[0][2];
	*b = equ[1][2];
}

void ni_he(CP *cp, float *a, float *b)
{
	int i, cnt = 0;
	float paper_num_float[N];
	float distance_float[N];

	for (i = 0; i < N; i++)
	{
		if (cp->paper_num[i])
		{
			paper_num_float[i] = (float)cp->paper_num[i];
			distance_float[i] = (float)cp->distance[i];
			cnt++;
		}
		else
		{
			paper_num_float[i] = 0.00;
			distance_float[i] = 0.00;
		}
	}
	irApprox(paper_num_float, distance_float, cnt, a, b);
}

void jiao_zhun(CP *cp, Cal *cal, int *x, double *y, int start, int stop, float *a, float *b)
{
	cp_init(cp, cal);
	cap_aquire(x, y, start, stop, cp);
	cap_to_distance(cp, cal);    //将电容值转换为距离
	ni_he(cp, a, b);            //拟合出纸张-距离的直线
	printf("y = %.3fx + %.3f\n", *b, *a);
}



/*
void main()
{
	int x[35] = { 0, 1,  2,  3,  4,  5,
		6,  7,  8,  9, 10,
		11, 12, 13, 14, 15,
		16, 17, 18, 19, 20,
		21, 22, 23, 24, 25,
		26, 27, 28, 29, 30,
		31, 32, 33, 34 };
	float y[35] = { 0, 157.15, 143.87, 132.51, 123.14, 116.47,
		110.97, 106.93, 100.58, 97.20,  93.82,
		91.91,  89.71,  87.19,  86.36,  83.78,
		82.80,  80.88,  79.73,  78.98,  77.45,
		77.19,  76.25,  75.34,  74.32,  73.96,
		73.48,  72.88,  72.47,  71.74,  71.17,
		70.36,  69.82,  69.47,  69.01 };
	int i, j;
	float a, b;
	double e_sum_new = 0.0;

	CP cp;
	Cal cal;


	//jiao_zhun(&cp, &cal, x, y, 1, 34, &a, &b);
	for (i = 0; i <= 31; i++)
	{
		for (j = i+3; j <= 34; j++)
		{
			jiao_zhun(&cp, &cal, x, y, i, j, &a, &b);
		}
	}




	getchar();
}
*/




