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

char *gen_str_i(char *dim, char *prefix, char *letter) {

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


int main(int argc, char *argv[]) {

	int N = atoi(argv[1]);

	double x_elem = 0.1;
	double y_elem = 7.1;
	double x_vec[N];
        double y_vec[N];

	char *letter_1 = "x";
	char *letter_2 = "y";
	char *name_1 = (char*)malloc(100 * sizeof(char));
	char *name_2 = (char*)malloc(100 * sizeof(char));

	FILE *vec1;
	FILE *vec2;

	name_1 = gen_str_i(argv[1],argv[2],letter_1);
	name_2 = gen_str_i(argv[1],argv[2],letter_2);
	
	gen_vec(N,x_elem,y_elem,x_vec,y_vec);

	vec1 = fopen(name_1, "w");
	vec2 = fopen(name_2,"w");
	for (int j = 0; j < N; j++){
		fprintf(vec1,"%.1f\n",x_vec[j]);
		fprintf(vec2,"%.1f\n",y_vec[j]);
	}
	fclose(vec1);
	fclose(vec2);
	
	printf("Done\n");
	
	free(name_1);
	free(name_2);
}
