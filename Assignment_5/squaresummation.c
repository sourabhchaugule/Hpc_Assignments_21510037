#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    int sum = 0;

    double parallel_start_time = omp_get_wtime();

    #pragma omp parallel reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;
        printf("Thread %d: Square = %d\n", thread_id, square);
        sum += square;
    }

    double parallel_end_time = omp_get_wtime();
    double parallel_time = parallel_end_time - parallel_start_time;

    printf("Sum of squares of thread IDs: %d\n", sum);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    double sequential_time = 0.1; 
    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

