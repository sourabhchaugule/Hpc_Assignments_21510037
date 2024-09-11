#include <stdio.h>
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

    double start_time = omp_get_wtime();

    #pragma omp parallel reduction(+:total_sum)
    {
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            total_sum += array[i]; 
        }
    }

    double end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;

    printf("Total sum: %lld\n", total_sum);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    double sequential_start_time = omp_get_wtime();
    long long sequential_sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sequential_sum += array[i];
    }
    double sequential_end_time = omp_get_wtime();
    double sequential_time = sequential_end_time - sequential_start_time;

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

