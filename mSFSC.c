#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define numRows 100
#define numCols 100

int matrix[numRows][numCols];

typedef struct {
    int startRow;
    int endRow;
    int* resultRowSum;
} ThreadArgs;

// Variables globales para almacenar información del hardware
int cacheLineSize = 0;
int numCores = 0;
int numThreads = 0;

void get_hardware_info() {
    // Obtener información de la línea de caché
    FILE* cache_info_file = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
    if (cache_info_file != NULL) {
        fscanf(cache_info_file, "%d", &cacheLineSize);
        fclose(cache_info_file);
    }

    // Obtener el número de núcleos
    numCores = sysconf(_SC_NPROCESSORS_ONLN);

    // Obtener el número de hilos
    numThreads = sysconf(_SC_NPROCESSORS_CONF);
}

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
    pthread_t threads[numThreads];
    int totalSum = 0;
    int rowSums[numRows];

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

    get_hardware_info(); // Recopilar información del hardware

    // Imprimir información del hardware
    printf("Cache Line Size: %d bytes\n", cacheLineSize);
    printf("Number of Cores: %d\n", numCores);
    printf("Number of Threads: %d\n", numThreads);

    int numIterations = 100; // Número de iteraciones para medir el tiempo promedio
    double totalElapsedTime = 0.0;

    for (int i = 0; i < numIterations; ++i) {
        double elapsed_time = measure_time(false_sharing);
        totalElapsedTime += elapsed_time;
    }

    double averageElapsedTime = totalElapsedTime / numIterations;

    printf("Average Elapsed Time: %f seconds\n", averageElapsedTime);

    return 0;
}
