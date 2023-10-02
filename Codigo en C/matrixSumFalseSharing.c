#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define numRows 100
#define numCols 100

int matrix[numRows][numCols];

typedef struct {
    int startRow;
    int endRow;
    int* resultRowSum;
} ThreadArgs;

void* sumRow(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;

    for (int i = threadArgs->startRow; i < threadArgs->endRow; ++i) {
        int sum = 0;
        for (int j = 0; j < numCols; ++j) {
            sum += matrix[i][j];
        }
        *(threadArgs->resultRowSum + i) = sum;
    }

    return NULL;
}

void false_sharing() {
    pthread_t threads[numRows];
    int totalSum = 0;
    int rowSums[numRows];

    int numThreads = numRows;
    int rowsPerThread = numRows / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        ThreadArgs* args = malloc(sizeof(ThreadArgs));
        args->startRow = i * rowsPerThread;
        args->endRow = (i == numThreads - 1) ? numRows : (i + 1) * rowsPerThread;
        args->resultRowSum = rowSums;

        pthread_create(&threads[i], NULL, sumRow, args);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < numRows; ++i) {
        totalSum += rowSums[i];
    }

    printf("Total sum: %d\n", totalSum);
}

double measure_time(void (*function)()) {
    clock_t start, end;
    double elapsed_time;

    start = clock();
    function();
    end = clock();

    elapsed_time = ((double)(end - start)) / (CLOCKS_PER_SEC);

    return elapsed_time;
}

int main() {
    // Inicializa la matriz con valores apropiados (en este caso, todos 1).
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            matrix[i][j] = 1;
        }
    }

    //false_sharing();

    double elapsed_time = measure_time(false_sharing);

    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
