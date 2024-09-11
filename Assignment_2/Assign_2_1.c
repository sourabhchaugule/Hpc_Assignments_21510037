#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VECTOR_SIZE 100000000
#define SCALAR 5.0           

int main() {
    float *vector, *result;
    int i;
    double start_time, end_time;

    vector = (float*) malloc(VECTOR_SIZE * sizeof(float));
    result = (float*) malloc(VECTOR_SIZE * sizeof(float));

    for (i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = (float) i;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < VECTOR_SIZE; i++) {
        result[i] = vector[i] + SCALAR;
    }

    end_time = omp_get_wtime();

    printf("Size of Vector :%d \n" , VECTOR_SIZE);
    printf("Vector Scalar Addition completed in %f seconds\n", end_time - start_time);

    free(vector);
    free(result);

    return 0;
}

