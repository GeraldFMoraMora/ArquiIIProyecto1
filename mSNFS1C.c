#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <sys/sysinfo.h> // Para get_nprocs

#define numRows 100
#define numCols 100

struct AlignedRow {
    int data[numCols];
};

struct AlignedType {
    atomic_int val;
};

struct ThreadArgs {
    int startRow;
    int endRow;
    atomic_int* resultRowSum;
};

struct AlignedRow matrix[numRows];

void initializeMatrix() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            matrix[i].data[j] = 1;
        }
    }
}

void* sumRow(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int sum = 0;
    
    for (int i = args->startRow; i <= args->endRow; ++i) {
        for (int j = 0; j < numCols; ++j) {
            sum += matrix[i].data[j];
        }
    }

    atomic_fetch_add(args->resultRowSum, sum);
    return NULL;
}

void no_false_sharing() {
    int numThreads = get_nprocs(); // Obtener el número de procesadores disponibles (Linux)
    pthread_t threads[numThreads];
    struct ThreadArgs threadArgs[numThreads];
    atomic_int totalSum;
    atomic_init(&totalSum, 0);

    int rowsPerThread = numRows / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        threadArgs[i].startRow = i * rowsPerThread;
        threadArgs[i].endRow = (i == numThreads - 1) ? numRows - 1 : threadArgs[i].startRow + rowsPerThread - 1;
        threadArgs[i].resultRowSum = &totalSum;
        
        pthread_create(&threads[i], NULL, sumRow, &threadArgs[i]);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Total sum: %d\n", atomic_load(&totalSum));
}

double measure_time(void (*function)()) {
    clock_t start, end;
    double elapsed_time;

    start = clock();
    function();
    end = clock();

    elapsed_time = ((double)(end - start)) / (CLOCKS_PER_SEC / 1000.0); // Multiplica por 1000 para obtener ms

    return elapsed_time;
}

int main() {
    initializeMatrix(); // Inicializar la matriz con 1
    double elapsed_time_ms = measure_time(no_false_sharing);

    printf("Elapsed time: %f ms\n", elapsed_time_ms);

    return 0;
}
