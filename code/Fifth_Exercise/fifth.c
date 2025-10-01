#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){ 
	long double vec[4] = {1.0, 1.0e+16, -1.0e+16, -0.5}; 
	long double sum = 0;
	long double sum_mod = 0;

	for (int i = 0; i < 4; i++){
		sum += vec[i];
		sum_mod += fabs(vec[i]);
		
	}
	printf("The sum is: %.10f\n",sum);
	printf("The condition number is: %.10Lf\n", sum_mod);
}
