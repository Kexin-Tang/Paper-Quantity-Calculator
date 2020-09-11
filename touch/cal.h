#ifndef SRC_TOUCH_CAL_H_
#define SRC_TOUCH_CAL_H_
#define N 101

typedef struct CP
{
	int paper_num[N];     //piece
	double cap[N];     //pF
	double distance[N];     //mm
}CP;

typedef struct Cal
{
	double e;     //10-12
	double S;     //10-3*m2
	double cap_bias;     //pF
}Cal;

void cp_init(CP *cp, Cal *cal);
void cap_aquire(int *x, double *y, int start, int stop, CP *cp);
void cap_to_distance(CP *cp, Cal *cal);
void linEquSolve(float *mat, int n);
void irApprox(float *x, float *y, int n, float *a, float *b);
void ni_he(CP *cp, float *a, float *b);
void jiao_zhun(CP *cp, Cal *cal, int *x, double *y, int start, int stop, float *a, float *b);

#endif /* SRC_TOUCH_CAL_H_ */
