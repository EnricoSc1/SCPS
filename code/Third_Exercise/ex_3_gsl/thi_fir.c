#include "gen.h"
#include "parser.h"

int main() {

	int N = 0;

	char *N_s = (char*)malloc(3 * sizeof(char));
	char *letter_1 = "x";
	char *letter_2 = "y";
	char *name_1 = (char*)malloc(100 * sizeof(char));
	char *name_2 = (char*)malloc(100 * sizeof(char));
	char *xfile = (char*)malloc(100 * sizeof(char));
	char *yfile = (char*)malloc(100 * sizeof(char));
	char *prefix = (char*)malloc(100 * sizeof(char));


        FILE *fx;
	FILE *fy;
	FILE *vec1;
	FILE *vec2;

        config_option_t co;
	config_option_t co1;

        if ((co = read_config_file("configuration.conf")) == NULL) {
		perror("read_config_file()");
		return -1;
	}
        
        co1 = co;
        
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
	if (strcmp("prefix",co->key) == 0){
	        strcpy(prefix,co->value);
	}
	co = co->prev;
	}

	name_1 = gen_str(N_s,prefix,letter_1);
	name_2 = gen_str(N_s,prefix,letter_2);

	double x_elem = 0.1;
	double y_elem = 7.1;
	double x_vec[N];
        double y_vec[N];
	
	gen_vec(N,x_elem,y_elem,x_vec,y_vec);

	vec1 = fopen(name_1, "w");
	vec2 = fopen(name_2, "w");
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
