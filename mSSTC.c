#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define numRows 100
#define numCols 100

struct Data {
    int matrix[numRows][numCols];
    char padding[64]; // 64 bytes por línea de caché en muchos sistemas.
};

int totalSum = 0;

void* sum_rows(void* arg) {
    struct Data* data = (struct Data*)arg;
    int rowSums[numRows];

    for (int i = 0; i < numRows; ++i) {
        rowSums[i] = 0;
        for (int j = 0; j < numCols; ++j) {
            rowSums[i] += data->matrix[i][j];
        }
    }

    for (int i = 0; i < numRows; ++i) {
        __sync_fetch_and_add(&totalSum, rowSums[i]);
    }

    return NULL;
}

void print_system_info() {
    printf("System Information:\n");

    // Ejecutar el comando "lscpu" y mostrar la salida.
    system("lscpu");

    // Leer y mostrar la información de la CPU desde /proc/cpuinfo.
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

int main() {
    struct Data data;
    pthread_t threads[8];

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            data.matrix[i][j] = 1;
        }
    }

    print_system_info();

    for (int i = 0; i < 8; ++i) {
        pthread_create(&threads[i], NULL, sum_rows, &data);
    }

    for (int i = 0; i < 8; ++i) {
        pthread_join(threads[i], NULL);
    }

    // printf("Total sum: %d\n", totalSum);

    return 0;
}
