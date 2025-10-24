#include "genf5.h"
#include "hdf5.h"
#include "parser.h"
#include <gsl/gsl_vector.h>

int main() {
	
	int N = 0;
	int a = 0;
        
	char *N_s = (char*)malloc(3 *sizeof(char));
	char *xfile = (char*)malloc(100 * sizeof(char));
	char *yfile = (char*)malloc(100 * sizeof(char));
	char *prefix_o = "vector_";
	char *name_o = gen_str(N_s, prefix_o, "sum");
	config_option_t co;
	
	if ((co = read_config_file("configuration.conf")) == NULL) {
		perror("read_config_file()");
		return -1;
	}
	
	while (co != NULL) {
	        if (strcmp("x_file",co->key) == 0) strcpy(xfile,co->value);
	        if (strcmp("y_file",co->key) == 0) strcpy(yfile,co->value);
	        if (strcmp("N",co->key) == 0) {strcpy(N_s,co->value); N = atoi(N_s);}
	        if (strcmp("a",co->key) == 0) a = atoi(co->value);
	        co = co->prev;
	}
	
	gsl_vector *x_vec = gsl_vector_alloc(N);
	gsl_vector *y_vec = gsl_vector_alloc(N);
	gsl_vector *d_vec = gsl_vector_alloc(N);
	
	hid_t fx, fy, fo;         
        hid_t dx, dy, dd;         
        hid_t space_id;           
        herr_t status;

        fx = H5Fopen(xfile, H5F_ACC_RDONLY, H5P_DEFAULT);
        fy = H5Fopen(yfile, H5F_ACC_RDONLY, H5P_DEFAULT);

        dx = H5Dopen(fx, "x", H5P_DEFAULT);
        dy = H5Dopen(fy, "y", H5P_DEFAULT);

        H5Dread(dx, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, x_vec->data);
        H5Dread(dy, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, y_vec->data);

        gsl_vector_memcpy(d_vec, y_vec);           
        gsl_vector_axpby((double)a, x_vec, 1.0, d_vec);   

        hsize_t dims[1] = {N};
        space_id = H5Screate_simple(1, dims, NULL);

        fo = H5Fcreate(name_o, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        dd = H5Dcreate(fo, name_o, H5T_NATIVE_DOUBLE, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

        H5Dwrite(dd, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, d_vec->data);

        H5Dclose(dx);
        H5Dclose(dy);
        H5Dclose(dd);
        H5Sclose(space_id);
        H5Fclose(fx);
        H5Fclose(fy);
        H5Fclose(fo);

        gsl_vector_free(x_vec);
        gsl_vector_free(y_vec);
        gsl_vector_free(d_vec);
        free(N_s);
        free(xfile);
        free(yfile);
        free(name_o);

	printf("Done\n");
        return 0;
}
