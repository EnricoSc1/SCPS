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


char *gen_str(char *dim, char *prefix, char *letter) {

	char *str1 = "N";
	char *str2 = dim;
	char *str3 = "_";
	char *str4 = ".dat";
	char *new_string = (char*)malloc(100 * sizeof(char));

	strcpy(new_string, prefix);
	
	strcat(new_string, str1);
	strcat(new_string, str2);
	strcat(new_string, str3);
	strcat(new_string, letter);
	strcat(new_string, str4);
	
	return new_string;
}
