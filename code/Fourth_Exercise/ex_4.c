#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_exp.h>
#include <gsl/gsl_sf_trig.h>
#define _USE_MATH_DEFINES
#define ITRUE ((expl(M_PI_2)-1.0l)/2.0l)

double simple_fun(double x){
	return exp(x)*cos(x);
}

double adv_fun(double x, void *parameters){
	
	double result;
	result = gsl_sf_exp(x) * gsl_sf_cos(x);

	return result;
}

int main(){
	
	int N = 0;

	printf("Type the number of intervals N:\n");
	scanf("%d",&N);

	double x_inf = 0;
	double x_sup = M_PI_2;
	double *xaxis = malloc((N+1)*sizeof(double));
	double *faxis = malloc((N+1)*sizeof(double));
	double delta = ( x_sup - x_inf ) / N;

	//Writing data on an external file

	FILE* file;

	file = fopen("ex4_data.txt","w");
	
	for(int i=0; i<=N; i++){
		xaxis[i] = x_inf + i * delta;
		faxis[i] = simple_fun(xaxis[i]);
	}

	for(int i=0; i<=N; i++){
		fprintf(file,"%lf\t%lf\n",xaxis[i],faxis[i]);
	}
		
	fclose(file);	

	//Trapezoidal rule for numerical integration

	double integral;
	double first_piece = delta * ( ( simple_fun(x_inf) + simple_fun(x_sup) )/2 );
	double second_piece = 0;
	double rel;

	for(int i=1; i<N; i++){
		second_piece += delta * faxis[i];
	}
	
	integral = first_piece + second_piece;
	
	//GSL numerical integration
	
	double gsleps_abs = 0;
	double gsleps_rel = 1e-11;
	double gslresult;
	double gslerror;

	gsl_integration_workspace *w = gsl_integration_workspace_alloc(N);
	
	gsl_function F;
	F.function = &adv_fun;
	F.params = NULL;
	
	gsl_integration_qag(&F, x_inf, x_sup, gsleps_abs, gsleps_rel, N, 6, w, &gslresult, &gslerror);

	printf("The numerical integration using the trapezoidal rules is I = %.16lf with relative error %.16Le.\n", integral, integral / ITRUE - 1);
	printf("The numerical integration with GSL is I_gsl = %.16lf with relative error %.30Le.\n", gslresult, (long double)gslresult / ITRUE - 1);
	
	free(xaxis);
	free(faxis);
	gsl_integration_workspace_free(w);
	return 0;
}
