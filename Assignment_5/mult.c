#include <stdio.h>
#include <omp.h>

int main() {
    int Arya = 10;
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    double start_time, end_time, sequential_time, parallel_time;

    start_time = omp_get_wtime();
    #pragma omp parallel num_threads(1) private(Arya)
    {
        int thread_id = omp_get_thread_num();
        int result = thread_id * Arya;
        printf("Thread %d: %d * %d = %d\n", thread_id, thread_id, Arya, result);
    }
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential Execution Time: %f seconds\n", sequential_time);

    start_time = omp_get_wtime();
    #pragma omp parallel private(Arya)
    {
        int thread_id = omp_get_thread_num();
        int result = thread_id * Arya;
        printf("Thread %d: %d * %d = %d\n", thread_id, thread_id, Arya, result);
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

