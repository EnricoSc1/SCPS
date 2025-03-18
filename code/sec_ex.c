#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main() {

	double a = 3.0;
	double p = 1e-1;
	int N[] = {10 , 1000000 , 100000000};
	bool check[3];

	clock_t t;
	t = clock();

	for(int i = 0; i < 3; i++) 
	{
		/* This are declarations of arrays using fixed memory
		double x[N[i]];
		double y[N[i]];
		double d[N[i]];
		However to deal with a huge dimension of ana array it is better to deal with dynamic memory using
                */
                
                double *x = (double*)malloc(N[i] * sizeof(double));
                double *y = (double*)malloc(N[i] * sizeof(double));
                double *d = (double*)malloc(N[i] * sizeof(double));

                
		for (int j = 0; j < N[i]; j++) {
			
			x[j] = 1.0 / 10.0;
			y[j] = 71.0 / 10.0;
			d[j] = a * x[j] + y[j];
			
			if (fabs(d[j] - 7.4) >= p) {
				check[i] = false;
				break;
			}
			else {
				check[i] = true;
			}
		}
	printf("%s\n", check[i] ? "True" : "False");
	}

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("The program took %f s to execute \n",time_taken);
}
