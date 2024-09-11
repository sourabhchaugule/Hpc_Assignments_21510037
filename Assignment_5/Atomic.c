#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int num_threads;
    int sum = 0;
    double sequential_time, parallel_time;
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    double start_time = omp_get_wtime();
    for (int i = 0; i < omp_get_max_threads(); i++) {
        int square = i * i;
        sum += square;
    }
    double end_time = omp_get_wtime();
    sequential_time = end_time - start_time;

    printf("Sequential Sum of squares of thread IDs: %d\n", sum);
    printf("Sequential Time: %f seconds\n", sequential_time);

    sum = 0; 

    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();

    #pragma omp parallel reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;
        printf("Thread %d: Square = %d\n", thread_id, square);
        sum += square;
    }

    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;

    printf("Parallel Sum of squares of thread IDs: %d\n", sum);
    printf("Parallel Time: %f seconds\n", parallel_time);

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

