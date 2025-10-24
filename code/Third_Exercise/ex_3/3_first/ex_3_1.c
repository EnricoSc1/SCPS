#include "gen.h"
#include "parser.h"

int main() {

        int N = 0;

        char *N_s = (char*)malloc(10 * sizeof(char));
        char *letter_1 = "x";
        char *letter_2 = "y";
        char *name_1;
        char *name_2;
       	char *xfile = (char*)malloc(100 * sizeof(char));
	char *yfile = (char*)malloc(100 * sizeof(char));
	char *prefix = (char*)malloc(100 * sizeof(char));

        config_option_t co;
        if ((co = read_config_file("configuration.conf")) == NULL) {
		perror("read_config_file()");
		return -1;
	}
        
        config_option_t co_iter = co;
        while (co_iter != NULL) {
                if (strcmp("x_file",co->key) == 0) strcpy(xfile,co->value);
	        if (strcmp("y_file",co->key) == 0) strcpy(yfile,co->value);
                if (strcmp("N", co_iter->key) == 0) N = atoi(co_iter->value);
                if (strcmp("prefix", co_iter->key) == 0) strcpy(prefix, co_iter->value);
                co_iter = co_iter->prev;
        }
         
        FILE *fx;
	FILE *fy;
	FILE *vec1;
	FILE *vec2; 
         
        snprintf(N_s, 10, "%d", N);
        name_1 = gen_str(N_s, prefix, letter_1);
        name_2 = gen_str(N_s, prefix, letter_2);

        double *x_vec = (double*)malloc(N * sizeof(double));
        double *y_vec = (double*)malloc(N * sizeof(double));
        if (!x_vec || !y_vec) {
                perror("read_config_file()"); 
                return -1;
        }

        double x_elem = 0.1;
        double y_elem = 7.1;
        gen_vec(N, x_elem, y_elem, x_vec, y_vec);

	vec1 = fopen(name_1, "w");
	vec2 = fopen(name_2, "w");
	for (int j = 0; j < N; j++){
		fprintf(vec1,"%.1f\n",x_vec[j]);
		fprintf(vec2,"%.1f\n",y_vec[j]);
	}
	fclose(vec1);
	fclose(vec2);
	
	printf("Done\n");
	
	free(xfile);
        free(yfile);
        free(prefix);
        free(N_s);
        free(x_vec);
        free(y_vec);
	free(name_1);
	free(name_2);
}



