#!/bin/bash

# Lista de programas a compilar y ejecutar
programas=("mSST" "mSFS" "mSNFS1" "mSNFS2")

# Elimina los archivos de resultados existentes (si los hay)
for programa in "${programas[@]}"; do
    if [ -e "${programa}CPP_results.txt" ]; then
        echo "Eliminando archivo de resultados existente para $programa"
        rm "${programa}CPP_results.txt"
    fi
    if [ -e "${programa}" ]; then
        echo "Eliminando archivo de compilacion existente para $programa"
        rm "${programa}"
    fi
    if [ -e "${programa}BenchCPP_results.txt" ]; then
        echo "Eliminando archivo de benchmark existente para $programa"
        rm "${programa}BenchCPP_results.txt"
    fi
done

# Compila y ejecuta todos los programas
for programa in "${programas[@]}"; do
    echo "Compilando $programa..."
    g++ -o "$programa" "${programa}.cpp" -pthread -std=c++11 -lbenchmark

    # Verifica si la compilación fue exitosa
    if [ $? -eq 0 ]; then
        echo "Guardando resultado de Benchmark para $programa..."
        "./$programa"> "${programa}BenchCPP_results.txt"
        echo "Ejecutando Valgrind con Cachegrind para $programa..."
        valgrind --tool=cachegrind "./$programa" 2> "${programa}CPP_results.txt"
        
    else
        echo "Error: La compilación de $programa ha fallado."
    fi
done
