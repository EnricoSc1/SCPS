#include <check.h>
#include "test.h"

START_TEST(test_multiply_idmatrices){
       
	int d = 3;
	double tolerance = 1e-4;
	double **A = malloc(d * sizeof(double *));
	double **B = malloc(d * sizeof(double *));
	double **C = malloc(d * sizeof(double *));

	for(int i=0; i<d; i++){
		
		A[i] = (double *)malloc(d * sizeof(double));
		B[i] = (double *)malloc(d * sizeof(double));
		C[i] = (double *)malloc(d * sizeof(double));

		for(int j=0; j<d; j++){
		
			if(i==j){
				A[i][j]=1.0;
				B[i][j]=1.0;
			}
			else{
				A[i][j]=0.0;
				B[i][j]=0.0;
			}
		}
	}

	multiply_matrices(A, B, C, d);

	bool check = true;

	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			if(i == j){
				ck_assert(fabs(C[i][j] - 1.0) < tolerance);
			}
			else if( i != j){
				ck_assert(fabs(C[i][j] - 0.0) < tolerance);
			}
		}
	}			
	
	// Free memory
       	free_matrix(A, d);
	free_matrix(B, d);
	free_matrix(C, d);
	
}
END_TEST


int main(void) {
	
	int nf;
	
	//Create a Suite in check framework
	Suite *s1 = suite_create("Test matrix multiplication");
	//Create a Test Case
	TCase *tc1_1 = tcase_create("Core");

        // Add the function you want to test to the case and then add the test to the suite
        tcase_add_test(tc1_1, test_multiply_idmatrices);
	suite_add_tcase(s1, tc1_1);
	
	//SRunner to execute the test suites
	SRunner *sr =srunner_create(s1);
	srunner_run_all(sr, CK_ENV);

	nf = srunner_ntests_failed(sr);

        //Clean Up
	srunner_free(sr);
	
	//Return with ternary condition equivalent to the if and else statements
	return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE; 
}
