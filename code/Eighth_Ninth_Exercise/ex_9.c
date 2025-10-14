#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>


int main() {

	int N[] = {40 , 6000 , 8000000};
	int chunk_size = 2000000;

	double a = 3.0;
	double p = 1e-1;

	bool check[] = {true, true, true};

	clock_t t;
	t = clock();

	printf("OpenMP max threads: %d\n\n", omp_get_max_threads());

	for(int i = 0; i < 3; i++) {
	
		int number_of_chunks = (int)ceil((double)N[i] / chunk_size);
		int thread_id = 0;
	
		double sum = 0;
		double *x = (double*)malloc(N[i] * sizeof(double));
		double *y = (double*)malloc(N[i] * sizeof(double));
		double *d = (double*)malloc(N[i] * sizeof(double));
		double *partial_chunk_sum = (double*)malloc(number_of_chunks * sizeof(double));
		memset(partial_chunk_sum, 0, number_of_chunks * sizeof(double));

		bool local_check = true;

		#pragma omp parallel for private(thread_id) reduction(&&:local_check) reduction(+:sum)
		for(int i_ch=0; i_ch<=number_of_chunks-1; i_ch++){
			
			int current_start = i_ch * chunk_size;
			int current_end = (i_ch + 1) * chunk_size;
	
			bool continue_loop = true;
	
			thread_id = omp_get_thread_num();

			if(current_end > N[i]){
				current_end = N[i];
			}

			for(int j=current_start; j<current_end; j++){
					
				if(!continue_loop) continue;

				x[j] = 1.0 / 10.0;
				y[j] = 71.0 / 10.0;
				d[j] = a * x[j] + y[j];	
				
				sum += d[j];

				if (fabs(d[j] - 7.4) >= p) {
					local_check = false;
					continue_loop = false;
					//break;
				}
			}
			printf("Process: %d\n", omp_get_thread_num());
		}

		check[i] = local_check;

		printf("%.2f\n",sum);
		printf("%s\n\n", check[i] ? "True" : "False");

		free(partial_chunk_sum);
		free(x);
		free(y);
		free(d);
	}
	
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("The program took %f s to execute \n",time_taken);

	return 0;
}

