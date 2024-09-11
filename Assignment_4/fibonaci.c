#include <omp.h>
#include <stdio.h>

long sequential_fib(int n) {
    if (n < 2) return n;

    long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

long parallel_fib(int n, int num_threads) {
    if (n < 2) return n;

    long a = 0, b = 1, c;
    long partial_a = 0, partial_b = 1;

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for
        for (int i = 2; i <= n; i++) {
            #pragma omp critical
            {
                c = a + b;
                a = b;
                b = c;
            }
        }
    }

    return b;
}

int main() {
    int n;
    long result;
    int num_threads;
    printf("Enter the number: ");
    scanf("%d", &num_threads);


    printf("Enter a number: ");
    scanf("%d", &n);



    omp_set_num_threads(num_threads);

    printf("Sequential Execution\n");
    double sequential_start_time = omp_get_wtime();
    result = sequential_fib(n);
    double sequential_end_time = omp_get_wtime();
    double sequential_time = sequential_end_time - sequential_start_time;
    printf("Fibonacci number F(%d) = %ld\n", n, result);
    printf("Time taken (sequential): %f seconds\n", sequential_time);

    printf("Parallel Execution\n");
    double parallel_start_time = omp_get_wtime();
    result = parallel_fib(n, num_threads);
    double parallel_end_time = omp_get_wtime();
    double parallel_time = parallel_end_time - parallel_start_time;
    printf("Fibonacci number F(%d) = %ld\n", n, result);
    printf("Time taken (parallel): %f seconds\n", parallel_time);
    
    double speedup = sequential_time / parallel_time;
    printf("Speed Up: %f\n", speedup);

    return 0;
}

