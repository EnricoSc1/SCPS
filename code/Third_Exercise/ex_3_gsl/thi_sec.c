#include "gen.h"
#include "parser.h"

int main() {
	
	int N = 0, a = 0;

	char *N_s = (char*)malloc(3 *sizeof(char));
	char *xfile = (char*)malloc(100 * sizeof(char));
	char *yfile = (char*)malloc(100 * sizeof(char));
	char *nameo = (char*)malloc(100 * sizeof(char));
	char *prefixo = "vector_";

	FILE *fx;
	FILE *fy;
	FILE *fo;
	
	config_option_t co;
	//config_option_t co1;
	//config_option_t co2;
	
	if ((co = read_config_file("configuration.conf")) == NULL) {
		perror("read_config_file()");
		return -1;
	}
	
	//co1 = co;
	//co2 = co; //I need to assign to head the co linked list because in the first cycle I traverse it to the start(since is backward oriented from the parser header)

	/*
	while (1) {
		printf("Key: %s\nValue: %s\n", co->key, co->value);
		if (co->prev != NULL){
			co = co->prev;
		} else {
			break;
		}
	}
	*/

	//co = co1;

	while (co != NULL) {
	if (strcmp("x_file",co->key) == 0){
		strcpy(xfile,co->value);
	}
	if (strcmp("y_file",co->key) == 0){
		strcpy(yfile,co->value);
	}
	if (strcmp("N",co->key) == 0){
		strcpy(N_s,co->value);
		N = atoi(N_s);
	}
	if (strcmp("a",co->key) == 0){
		a = atoi(co->value);
	}
	co = co->prev;
	}
	
	double *x = (double*)malloc(N * sizeof(double));
	double *y = (double*)malloc(N * sizeof(double));
	double *d = (double*)malloc(N * sizeof(double));
	//Remember: dealing with only arr is equal to deal with arr[0] automatically

	//co = co2;
	
	nameo = gen_str(N_s, prefixo, "sum");

	fx = fopen(xfile, "r");
	if (fx == NULL){perror("Error opening file for vector x.\n"); return -1;}
	fy = fopen(yfile, "r");
	if (fy == NULL){perror("Error opening file for vector y.\n"); return -1;}
	
	for (int i = 0; i < N; i++) {
		fscanf(fx,"%lf", &x[i]);
		fscanf(fy,"%lf", &y[i]);
		//fscanf needs a memory address to store a value, that's why &arr[i] and not arr[i].
	}
	
	//fscanf read data sequentially and automatically move forward in the file at each call! 
	//It moves the file pointer forward! That's why we don't need to specify the positions like in arr[i]
	
	fclose(fx);
	fclose(fy);

	fo = fopen(nameo, "w");
	for (int i = 0; i < N; i++){
		d[i] = a * x[i] + y[i];
		fprintf(fo,"%.1f\n",d[i]);
	}
	fclose(fo);

	free(xfile);
	free(yfile);
	free(x);
	free(y);

	printf("Done\n");
}
