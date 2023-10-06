#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#define numRows 100
#define numCols 100

struct Data {
  int matrix[numRows][numCols];
  // Añade padding para asegurarte de que cada hilo trabaje en una línea de caché diferente.
  char padding[64];  // 64 bytes por línea de caché en muchos sistemas.
};

// Utiliza una variable global compartida para almacenar la suma total.
int totalSum = 0;

// Función que realiza la suma de filas en la estructura de datos compartida.
void* sum_rows(void* arg) {
  struct Data* data = (struct Data*)arg;
  int rowSums[numRows];

  for (int i = 0; i < numRows; ++i) {
    rowSums[i] = 0;
    for (int j = 0; j < numCols; ++j) {
      rowSums[i] += data->matrix[i][j];
    }
  }

  // Agrega la suma de esta fila a la suma total.
  for (int i = 0; i < numRows; ++i) {
    __sync_fetch_and_add(&totalSum, rowSums[i]);
  }

  return NULL;
}

int main() {
  struct Data data;
  pthread_t threads[8];

  // Inicializa la matriz con valores.
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      data.matrix[i][j] = 1;
    }
  }

  // Crea y ejecuta múltiples hilos que realizan la suma de filas.
  for (int i = 0; i < 8; ++i) {
    pthread_create(&threads[i], NULL, sum_rows, &data);
  }

  // Espera a que todos los hilos terminen.
  for (int i = 0; i < 8; ++i) {
    pthread_join(threads[i], NULL);
  }

  // Imprime el resultado total.
  printf("Total sum: %d\n", totalSum);

  return 0;
}
