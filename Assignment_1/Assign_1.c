#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;
    double seq_total, par_total, speedup;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);

    double seq_start = omp_get_wtime();
    
    printf("Sequential Execution:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Hello, World from thread %d\n", i);
    }
    
    double seq_end = omp_get_wtime();
    seq_total = seq_end - seq_start;

    double par_start = omp_get_wtime();
    
    printf("Parallel Execution:\n");
    #pragma omp parallel
    {
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }
    
    double par_end = omp_get_wtime();
    par_total = par_end - par_start;

    speedup = seq_total / par_total;

    printf("Sequential Execution Time: %f seconds\n", seq_total);
    printf("Parallel Execution Time: %f seconds\n", par_total);
    printf("Speedup: %f\n", speedup);

    return 0;
}

