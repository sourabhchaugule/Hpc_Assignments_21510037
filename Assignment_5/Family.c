#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    const char *family_members[] = {"A", "B", "C", "D"};
    int num_members = sizeof(family_members) / sizeof(family_members[0]);
    int num_threads;
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    double sequential_time, parallel_time;
    
    double start_time = omp_get_wtime();
    for (int i = 0; i < num_members; i++) {
        printf("Sequential: %s\n", family_members[i]);
    }
    double end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential Time: %f seconds\n", sequential_time);
    
    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < num_members; i++) {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: %s\n", thread_id, family_members[i]);
    }

    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel Time: %f seconds\n", parallel_time);

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}

