#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <sys/sysinfo.h> // Para get_nprocs
#include <string.h>

#define numRows 100
#define numCols 100

int** matrix;

struct AlignedType {
    atomic_int val;
} __attribute__((aligned(64)));

struct ThreadArgs {
    int startRow;
    int endRow;
    atomic_int* resultRowSum;
};

void initializeMatrix() {
    matrix = (int**)malloc(numRows * sizeof(int*));
    for (int i = 0; i < numRows; ++i) {
        matrix[i] = (int*)malloc(numCols * sizeof(int));
        for (int j = 0; j < numCols; ++j) {
            matrix[i][j] = 1;
        }
    }
}

void freeMatrix() {
    for (int i = 0; i < numRows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void* sumRow(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int sum = 0;
    
    for (int i = args->startRow; i <= args->endRow; ++i) {
        for (int j = 0; j < numCols; ++j) {
            sum += matrix[i][j];
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

    // Agregar información de hardware
    printf("System Information:\n");
    system("lscpu");
    
    FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), cpuinfo)) {
            if (strstr(line, "cache size") || strstr(line, "core id") || strstr(line, "processor")) {
                printf("%s", line);
            }
        }
        fclose(cpuinfo);
    }
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

    freeMatrix(); // Liberar la memoria de la matriz

    return 0;
}
