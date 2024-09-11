#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000

int main() {
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    long sequential_product = 0; 
    long parallel_product = 0;   

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    printf("Enter the number of threads: ");
    int num_threads;
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);

    double sequential_start_time = omp_get_wtime();  
    for (int i = 0; i < N; i++) {
        sequential_product += (long)a[i] * b[i];
    }
    double sequential_end_time = omp_get_wtime();

    double sequential_time = sequential_end_time - sequential_start_time;
    printf("Scalar product (sequential): %ld\n", sequential_product);
    printf("Time taken (sequential): %f seconds\n", sequential_time);

    double parallel_start_time = omp_get_wtime();  
    #pragma omp parallel for reduction(+:parallel_product) schedule(static, 1000)
    for (int i = 0; i < N; i++) {
        parallel_product += (long)a[i] * b[i];
    }
    double parallel_end_time = omp_get_wtime();
    
    double parallel_time = parallel_end_time - parallel_start_time;
    printf("Scalar product (parallel): %ld\n", parallel_product);
    printf("Time taken (parallel): %f seconds\n", parallel_time);

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    free(a);
    free(b);

    return 0;
}

