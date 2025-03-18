#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int main() {
	
	int N[] = {10,100,500};
	double p = 1e-02;
	double a = 3.0;
	double b = 7.1;
	bool check;
	clock_t t;
	t = clock();
	
	for (int k = 0; k < 3; k++) {
		
	        double A[N[k]][N[k]];
	        double B[N[k]][N[k]];
        	double C[N[k]][N[k]];
	
		for (int i = 0; i < N[k]; i++) {
			for (int j = 0; j < N[k]; j++){
				A[i][j] = a;
				B[i][j]	= b;
			}
		}	
		for (int i = 0; i < N[k]; i++) {
			for (int j = 0; j < N[k]; j++) {
				double cij = 0;
				for (int l = 0; l < N[k]; l++){
					cij += A[i][l] * B[l][j];
				}
				C[i][j] = cij;
				if (fabs(C[i][j] - 21.3 * N[k]) < p) {
					check = true;
				}
				else {
					check = false;
					printf("%s","The matrix entries are NOT 21.3 * N.");
					break;
				}
			}
		}	
		printf("%s\n", check ? "True" : "False");
	}		

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("The program took %f s to compute.\n",time_taken);
}
