#include "genf5.h"
#include "parser.h"
#include "hdf5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int N = 0;

    char *N_s = (char*)malloc(10 * sizeof(char));
    char *letter_1 = "x";
    char *letter_2 = "y";
    char *name_1;
    char *name_2;
    char *prefix = (char*)malloc(100 * sizeof(char));

    config_option_t co;
    if ((co = read_config_file("configuration.conf")) == NULL) {
        perror("read_config_file()");
        return -1;
    }

    config_option_t co_iter = co;
    while (co_iter != NULL) {
        if (strcmp("N", co_iter->key) == 0) N = atoi(co_iter->value);
        if (strcmp("prefix", co_iter->key) == 0) strcpy(prefix, co_iter->value);
        co_iter = co_iter->prev;
    }

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

    hsize_t dims[1] = {N};

    hid_t file_id = H5Fcreate(name_1, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    hid_t dataset_id = H5Dcreate(file_id, "x", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, x_vec);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    file_id = H5Fcreate(name_2, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    dataspace_id = H5Screate_simple(1, dims, NULL);
    dataset_id = H5Dcreate(file_id, "y", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, y_vec);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    free(x_vec);
    free(y_vec);
    free(N_s);
    free(name_1);
    free(name_2);
    free(prefix);

    return 0;
}

