#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


double mean_matrix(gsl_matrix *m, int d){
	
	double sum = 0;

	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			sum += gsl_matrix_get(m,i,j);
		}
	}
	
	return sum / (d * d);
}


double median_matrix(gsl_matrix *m, int d){
	
	int k = 0;
	double median = 0;
	double new_array[d*d];

	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			new_array[k++] = gsl_matrix_get(m,i,j);
		}
	}
	
	int size = d*d;

	//This is order n^2 of complexity
	/*
	for(int i=0; i<size-1; i++){
		for(int j=0; j<size-i-1; j++){
			if(new_array[j]>new_array[j+1]){
				double temp = new_array[j];
				new_array[j] = new_array[j+1];
				new_array[j+1] = temp;
			}
		}
	}
	*/ 

       	// Order n log n of complexity
	qsort(new_array, d, sizeof(new_array[0]), compare);

	if(size%2!=0){
		median = new_array[size/2];
	}
	else{
		median = (new_array[size/2-1] + new_array[size/2])/2;
	}
	
	return median;

}


void print_matrix(gsl_matrix *m, int d){
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			printf("%f\t",gsl_matrix_get(m,i,j));
		}
		printf("\n");
	}
}


void r2c_converter(gsl_matrix *r_m, gsl_matrix_complex *c_m, int d){
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			gsl_matrix_complex_set(c_m, i, j, gsl_complex_rect(gsl_matrix_get(r_m,i,j),0.0));
		}
	}
}


void c2r_converter(gsl_matrix_complex *c_m, gsl_matrix *r_m, int d){
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
		        double real = GSL_REAL(gsl_matrix_complex_get(c_m,i,j));
			gsl_matrix_set(r_m, i, j, real);
		}
	}
}
