#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define VECTOR_SIZE 2000000
#define SCALAR 5

void vector_scalar_add(float *result, float *vector, float scalar, int size, int chunk_size, const char* schedule_type) {
    if (strcmp(schedule_type, "static") == 0) {
        #pragma omp parallel for schedule(static, chunk_size)
        for (int i = 0; i < size; i++) {
            result[i] = vector[i] + scalar;
        }
    } else if (strcmp(schedule_type, "dynamic") == 0) {
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int i = 0; i < size; i++) {
            result[i] = vector[i] + scalar;
        }
    }
}

double measure_time(float *result, float *vector, float scalar, int size, int chunk_size, const char* schedule_type) {
    double start_time = omp_get_wtime();
    vector_scalar_add(result, vector, scalar, size, chunk_size, schedule_type);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
    float *vector = (float *)malloc(VECTOR_SIZE * sizeof(float));
    float *result = (float *)malloc(VECTOR_SIZE * sizeof(float));

    srand(time(NULL));
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = (float)rand() / RAND_MAX;
    }

    printf("Enter the number of threads: ");
    int num_threads;
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);

    clock_t sequential_start_time = clock();
    for (int i = 0; i < VECTOR_SIZE; i++) {
        result[i] = vector[i] + SCALAR;
    }
    clock_t sequential_end_time = clock();
    double sequential_time = (double)(sequential_end_time - sequential_start_time) / CLOCKS_PER_SEC;
    printf("Time taken (sequential): %f seconds\n", sequential_time);

    printf("Parallel Execution\n");

    int static_chunk_sizes[] = {1, 5, 10, 20, 50};
    for (int i = 0; i < sizeof(static_chunk_sizes) / sizeof(int); i++) {
        double static_execution_time = measure_time(result, vector, SCALAR, VECTOR_SIZE, static_chunk_sizes[i], "static");
        double static_speedup = sequential_time / static_execution_time;
        printf("STATIC schedule, Chunk size %d: Time = %.6f seconds, Speedup = %.2f\n", static_chunk_sizes[i], static_execution_time, static_speedup);
    }

    int dynamic_chunk_sizes[] = {1, 5, 10, 20, 50};
    for (int i = 0; i < sizeof(dynamic_chunk_sizes) / sizeof(int); i++) {
        double dynamic_execution_time = measure_time(result, vector, SCALAR, VECTOR_SIZE, dynamic_chunk_sizes[i], "dynamic");
        double dynamic_speedup = sequential_time / dynamic_execution_time;
        printf("DYNAMIC schedule, Chunk size %d: Time = %.6f seconds, Speedup = %.2f\n", dynamic_chunk_sizes[i], dynamic_execution_time, dynamic_speedup);
    }

    double start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(static) nowait
        for (int i = 0; i < VECTOR_SIZE / 2; i++) {
            result[i] = vector[i] + SCALAR;
        }

        #pragma omp for schedule(static) nowait
        for (int i = VECTOR_SIZE / 2; i < VECTOR_SIZE; i++) {
            result[i] = vector[i] + SCALAR;
        }
    }
    double end_time = omp_get_wtime();
    double nowait_execution_time = end_time - start_time;
    double nowait_speedup = sequential_time / nowait_execution_time;
    printf("Nowait Execution: Time = %.6f seconds, Speedup = %.2f\n", nowait_execution_time, nowait_speedup);

    free(vector);
    free(result);

    return 0;
}

