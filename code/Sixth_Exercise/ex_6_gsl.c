#include "functions.h"
#include "parser.h"

int main(void){

	//Initialization
	int d = 1000;
	double mean = 1.0;
	double sigma = 1.0;
	
	gsl_rng_env_setup();
	gsl_rng *r = gsl_rng_alloc(gsl_rng_taus);
	gsl_rng_set(r,time(NULL));
	
	gsl_matrix *A = gsl_matrix_alloc(d,d);
	gsl_matrix *A2 = gsl_matrix_alloc(d,d);
	gsl_matrix_complex *A_c = gsl_matrix_complex_alloc(d,d);
	gsl_matrix_complex *C = gsl_matrix_complex_alloc(d,d);
	gsl_matrix *R = gsl_matrix_alloc(d,d);
	
	
	
	//Set matrix elements
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			gsl_matrix_set(A,i,j,gsl_ran_gaussian(r,sigma) + mean);
		}
	}
	
	double mean_A = mean_matrix(A,d);
	double median_A = median_matrix(A,d);
	printf("The mean of the A matrix is %.16lf\n", mean_A);
	printf("The median of the A matrix is %.16lf\n\n", median_A);

	//Complex version of the real matrix
	r2c_converter(A,A_c,d);
	gsl_matrix_memcpy(A2,A);

	//Workspace and wavetable for FFT
	gsl_fft_real_wavetable *wav = gsl_fft_real_wavetable_alloc(d);
	gsl_fft_real_workspace *w = gsl_fft_real_workspace_alloc(d);
	gsl_fft_complex_wavetable *c_wav = gsl_fft_complex_wavetable_alloc(d);
	gsl_fft_complex_workspace *c_w = gsl_fft_complex_workspace_alloc(d);
	gsl_fft_halfcomplex_wavetable *h_wav = gsl_fft_halfcomplex_wavetable_alloc(d);

	//Fast Fourier transform
	//c2c
	
	for(int i=0; i<d; i++){
		gsl_vector_complex_view A_row = gsl_matrix_complex_row(A_c,i);
		gsl_vector_complex_view C_row = gsl_matrix_complex_row(C,i);	

		gsl_vector_complex_memcpy(&C_row.vector, &A_row.vector);

		gsl_fft_complex_forward(C_row.vector.data,1,d,c_wav,c_w);
	}


	for(int i=0; i<d; i++){
		gsl_vector_complex_view C_row = gsl_matrix_complex_row(C,i);
		gsl_fft_complex_inverse(C_row.vector.data,1,d,c_wav,c_w);
	}
	
	//Complex to real converter (only for complex matrices describing real matrices)
	c2r_converter(C,A,d);
	
	double mean_A_rec = mean_matrix(A,d);
	double median_A_rec = median_matrix(A,d);
	
	printf("The mean of the reconstructed A (c2c) matrix is %.20lf\n", mean_A_rec);
	printf("The median of the reconstructed A (c2c) matrix is %.20lf\n\n", median_A_rec);
	printf("The absolute error of the mean is %e\n",fabs(mean_A - mean_A_rec));
	printf("The relative error of the mean is %e\n\n",mean_A / mean_A_rec);

	//r2c
	for(int i=0; i<d; i++){
		gsl_vector_view row = gsl_matrix_row(A2,i);;
		gsl_vector_view c_row = gsl_matrix_row(R,i);	

		gsl_vector_memcpy(&c_row.vector, &row.vector);

		gsl_fft_real_transform(c_row.vector.data,1,d,wav,w);
	}

	for(int i=0; i<d; i++){
		gsl_vector_view row = gsl_matrix_row(R,i);
		gsl_fft_halfcomplex_inverse(row.vector.data,1,d,h_wav,w);
	}

	double mean_A_rec2 = mean_matrix(R,d);
	double median_A_rec2 = median_matrix(R,d);
	
	printf("The mean of the reconstructed A (r2c) matrix is %.20lf\n", mean_matrix(R,d));
	printf("The median of the reconstructed A (r2c) matrix is %.20lf\n", median_matrix(R,d));
	printf("The absolute error of the mean is %e\n",fabs(mean_A - mean_A_rec2));
	printf("The relative error of the mean is %e\n\n",mean_A / mean_A_rec2);


	gsl_rng_free(r);
	gsl_matrix_free(A);		
	gsl_matrix_complex_free(A_c);	
	gsl_fft_real_wavetable_free(wav);	
	gsl_fft_real_workspace_free(w);	
	gsl_fft_complex_wavetable_free(c_wav);
	gsl_fft_complex_workspace_free(c_w);
	gsl_fft_halfcomplex_wavetable_free(h_wav);

	return 0;
}
