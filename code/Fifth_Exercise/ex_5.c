#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

double KahanSum(long double x[]){
	long double sum = 0.0;
	long double c = 0.0;
	long double ord_x[4];

	for (int i = 0; i < 4; i++){
		long double y = x[i] - c;
		long double t = sum + y;
		c = (t - sum) - y;
		sum = t;
	}

	return sum;
}


int main(){ 
	
	double precision = 1e-03;
	double mean = 1.0;
	double sigma = 1.0;
	double sum = 0;
	
	long double a = 3.0;
	long double sum_x = 0;
	long double sum_y = 0;
	long double sum_d = 0;
	long double sum_k = 0;
	long double vec_k[4] = {1.0, 1.0e+16, - (1.0e+16), -0.5};

 	gsl_rng_env_setup();
	gsl_rng *r = gsl_rng_alloc(gsl_rng_taus);
	gsl_rng_set(r,time(NULL));
	
	gsl_vector_long_double *vec = gsl_vector_long_double_alloc(4);
	gsl_vector_long_double_set(vec, 0, 1.0);
	gsl_vector_long_double_set(vec, 1, 1.0 * pow(10,16));
	gsl_vector_long_double_set(vec, 2, -1.0 * pow(10,16));
	gsl_vector_long_double_set(vec, 3, -0.5);

	gsl_vector_long_double *x = gsl_vector_long_double_alloc(4);
	gsl_vector_long_double *y = gsl_vector_long_double_alloc(4);
	gsl_vector_long_double *d = gsl_vector_long_double_alloc(4);
	for (int i = 0; i < 4; i++){
		gsl_vector_long_double_set(x, i, gsl_ran_gaussian(r,sigma));
		gsl_vector_long_double_set(y, i, gsl_ran_gaussian(r,sigma));
		gsl_vector_long_double_set(d, i, a * gsl_vector_long_double_get(x, i) + gsl_vector_long_double_get(y, i) );
		sum_x += gsl_vector_long_double_get(x,i);
		sum_y += gsl_vector_long_double_get(y,i);	
		sum_d += gsl_vector_long_double_get(d,i);
	}

	printf("The elements of the GSL vector are:\n");		
	for (int i = 0; i < 4; i++){
		printf("%.3Lf\n",gsl_vector_long_double_get(vec,i));
	}
	printf("\n");	
	
	sum = gsl_vector_long_double_sum(vec);
	sum_k = KahanSum(vec_k);	
	
	
	printf("The sum of the elements of the vector using GSL is:%.16f\n",sum);
	printf("The sum of the elements of the vector using Kahan is:%.16Lf\n\n",sum_k);
	printf("The elements of the GSL random vector x are:\n");		
	for (int i = 0; i < 4; i++){
		printf("%.3Lf\n",gsl_vector_long_double_get(x,i));
	}
	printf("\n");

	printf("The elements of the GSL random vector y are:\n");		
	for (int i = 0; i < 4; i++){
		printf("%.3Lf\n",gsl_vector_long_double_get(y,i));
	}
	printf("\n");
	
	printf("The elements of the GSL sum vector d are:\n");		
	for (int i = 0; i < 4; i++){
		printf("%3Lf\n",gsl_vector_long_double_get(d,i));
	}
	printf("\n");

	if(fabsl(sum_d - (a * sum_x + sum_y)) < precision){
		printf("The sum is correctly implemented!\n");
	}
	else{
		printf("The sum is WRONGLY implemented!\n");
	}

	gsl_vector_long_double_free(vec);	
	gsl_vector_long_double_free(x);	
	gsl_vector_long_double_free(y);	
	gsl_vector_long_double_free(d);
	gsl_rng_free(r);
}
