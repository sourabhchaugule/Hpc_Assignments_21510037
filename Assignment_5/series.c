#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    omp_set_num_threads(num_threads);

    double start_time = omp_get_wtime();
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("2\n");
        }
        #pragma omp section
        {
            printf("4\n");
        }
    }

    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;
    printf("Execution Time: %f seconds\n", execution_time);

    double sequential_time = 0.1;
    double speedup = sequential_time / execution_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

