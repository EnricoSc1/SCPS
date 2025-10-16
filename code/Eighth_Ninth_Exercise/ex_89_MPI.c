#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {
	
	int rankp, numprocs;
	int N[] = {(int)1e+1 ,(int)1e+3 ,(int)1e+6};
	double a = 3.0;
	double p = 1e-1;
	bool check[] = {true, true, true};
	
	// Initialize MPI: all processors execute the same code simultaneously, but each works on different data based on its unique rank (0 to numprocs-1).
        // This is SPMD (Single Program, Multiple Data), not a loop. 
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankp);
	
	double t_start = MPI_Wtime();

	for(int i_n = 0; i_n < 3; i_n++) {

		int chunk_size = (int)ceil((double)N[i_n] / numprocs);
                int start = rankp * chunk_size;
                int end = (rankp + 1) * chunk_size;
                int local_size = end - start;
                // Since chunk_size uses ceil(), numprocs * chunk_size may exceed N[i_n]. Fix the last process's end index to avoid accessing memory beyond the array.
                if (rankp == numprocs-1){
			end = N[i_n];
			local_size = end - start;
		}
                              
		bool local_check = true;
                double sum = 0.0;
                double global_sum;
		double *x = (double*)malloc(local_size * sizeof(double));
		double *y = (double*)malloc(local_size * sizeof(double));
		double *d = (double*)malloc(local_size * sizeof(double));
					
          	for(int j=0; j<local_size; j++){
				
		      	x[j] = 1.0 / 10.0;
			y[j] = 71.0 / 10.0;
			d[j] = a * x[j] + y[j];
			sum += d[j];

			if (fabs(d[j] - 7.4) >= p) {
				local_check = false;
				break;
			}
		}
		
		MPI_Reduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
                MPI_Allreduce(&local_check, &check[i_n], 1, MPI_C_BOOL, MPI_LAND, MPI_COMM_WORLD);

		//The rank 0 is the main processor, responsible to the main communications.
		if(rankp==0){ 
		printf("%.2f\n",global_sum);
		printf("%s\n\n", check[i_n] ? "True" : "False");
                }

		free(x);
		free(y);
		free(d);
	}
	
	double t_end = MPI_Wtime();
	double time_taken = t_end - t_start;
	//The parallelization is still in action so we have to select the rank 0 processor among the others.
	if (rankp==0){printf("The program run time is %f s.\n",time_taken);}

	MPI_Finalize();
	return 0;
}
