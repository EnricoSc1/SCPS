#include "gen.h"
#include "parser.h"

int main() {
	
	int N = 0, a = 0;

	char *N_s = (char*)malloc(3 *sizeof(char));
	char *xfile = (char*)malloc(100 * sizeof(char));
	char *yfile = (char*)malloc(100 * sizeof(char));
	char *prefix_o = "vector_";

	FILE *f_x;
	FILE *f_y;
	FILE *f_o;
	
	config_option_t co;
	if ((co = read_config_file("configuration.conf")) == NULL) {
		perror("read_config_file()");
		return -1;
	}

	while (co != NULL) {
	if (strcmp("x_file",co->key) == 0) strcpy(xfile,co->value);
	if (strcmp("y_file",co->key) == 0) strcpy(yfile,co->value);
	if (strcmp("N", co->key) == 0) { strcpy(N_s, co->value); N = atoi(N_s); }
	if (strcmp("a",co->key) == 0) a = atoi(co->value);
	co = co->prev;
	}
	
	double *x = (double*)malloc(N * sizeof(double));
	double *y = (double*)malloc(N * sizeof(double));
	double *d = (double*)malloc(N * sizeof(double));
	if (!x || !y || !d) { perror("malloc()"); return -1; }
	
	char *name_o = gen_str(N_s, prefix_o, "sum");

	f_x = fopen(xfile, "r");
	if (f_x == NULL){perror("Error opening file for vector x"); return -1;}
	f_y = fopen(yfile, "r");
	if (f_y == NULL){perror("Error opening file for vector y"); return -1;}
	
	for (int i = 0; i < N; i++) {
		fscanf(f_x,"%lf", &x[i]);
		fscanf(f_y,"%lf", &y[i]);
	}
	
	fclose(f_x);
	fclose(f_y);

	f_o = fopen(name_o, "w");
	for (int i = 0; i < N; i++){
		d[i] = a * x[i] + y[i];
		fprintf(f_o,"%.1f\n",d[i]);
	}
	fclose(f_o);

	printf("Done\n");
	
	free(N_s);
        free(name_o);
	free(xfile);
	free(yfile);
	free(x);
	free(y);
	free(d);
}
