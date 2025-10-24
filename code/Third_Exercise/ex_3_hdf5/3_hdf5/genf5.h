#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gen_vec(int N, double a, double b, double *x, double *y) {
	for (int i = 0; i < N; i++) {
		x[i] = a;
		y[i] = b;
	}
}


char *gen_str(const char *dim, const char *prefix, const char *letter) {
        const char *str1 = "N";
        const char *str3 = "_";
        const char *str4 = ".hdf5";

        size_t len = strlen(prefix) + strlen(str1) + strlen(dim) + strlen(str3) + strlen(letter) + strlen(str4) + 1;

        char *new_string = malloc(len);
        if (!new_string) return NULL;
        
	strcpy(new_string, prefix);
	strcat(new_string, str1);
	strcat(new_string, dim);
	strcat(new_string, str3);
	strcat(new_string, letter);
	strcat(new_string, str4);
	
	//Remember to write free(new_string) at the end of the code since this function allocates memory dynamically
	return new_string; 
}
