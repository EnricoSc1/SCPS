#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_vector.h>

int main(){ 
	printf("The elements of the GSL vector are:\n");
	double sum = 0;
	
	gsl_vector_long_double * vec = gsl_vector_long_double_alloc(4);
	
	gsl_vector_long_double_set(vec, 0, 1.0);
	gsl_vector_long_double_set(vec, 1, 1.0 * pow(10,16));
	gsl_vector_long_double_set(vec, 2, -1.0 * pow(10,16));
	gsl_vector_long_double_set(vec, 3, -0.5);
			
	for (int i = 0; i < 4; i++){
		printf("%.1Lf\n",gsl_vector_long_double_get(vec,i));
	}
	
	sum = gsl_vector_long_double_sum(vec);
	printf("The sum of the elements of the GSL vector is: %.1f\n",sum);
	
	gsl_vector_long_double_free(vec);
}
