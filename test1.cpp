#include <iostream>
#include <thread>

const int arraySize = 10000;
int data[arraySize];

void increment(int start, int end) {
    for (int i = start; i < end; ++i) {
        data[i]++;
    }
}

int main() {
    // Inicializa el arreglo de datos
    for (int i = 0; i < arraySize; ++i) {
        data[i] = 0;
    }

    // Crea dos hilos que operan en diferentes partes del arreglo
    std::thread t1(increment, 0, arraySize / 2);
    std::thread t2(increment, arraySize / 2, arraySize);

    // Espera a que los hilos terminen
    t1.join();
    t2.join();

    // Imprime algunos valores del arreglo
    std::cout << "data[0] = " << data[0] << std::endl;
    std::cout << "data[" << arraySize / 2 << "] = " << data[arraySize / 2] << std::endl;

    return 0;
}