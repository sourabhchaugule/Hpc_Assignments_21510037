#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int array[ARRAY_SIZE];
    long long total_sum = 0;
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    double start_time, end_time, sequential_time, parallel_time;

    start_time = omp_get_wtime();
    total_sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        total_sum += array[i];
    }
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential Execution Time: %f seconds\n", sequential_time);

    start_time = omp_get_wtime();
    total_sum = 0;
    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        total_sum += array[i];
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    printf("Total sum: %lld\n", total_sum);

    return 0;
}

