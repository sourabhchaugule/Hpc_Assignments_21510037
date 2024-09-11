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

    double parallel_start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for reduction(+:total_sum)
        for (int i = 0; i < ARRAY_SIZE; i++) {
            total_sum += array[i];
        }
    }

    double parallel_end_time = omp_get_wtime();
    double parallel_time = parallel_end_time - parallel_start_time;

    printf("Total sum: %lld\n", total_sum);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    double sequential_time = 0.1;
    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

