#!/bin/bash

# Lista de programas a compilar y ejecutar
programas=("mSSTC" "mSFSC" "mSNFS1C" "mSNFS2C")

# Elimina los archivos de resultados existentes (si los hay)
for programa in "${programas[@]}"; do
    if [ -e "${programa}C_results.txt" ]; then
        echo "Eliminando archivo de resultados existente para $programa"
        rm "${programa}C_results.txt"
    fi
    if [ -e "${programa}" ]; then
        echo "Eliminando archivo de compilacion existente para $programa"
        rm "${programa}"
    fi
done

# Compila y ejecuta todos los programas
for programa in "${programas[@]}"; do
    echo "Compilando $programa..."
    gcc -o "$programa" "${programa}.c" -lpthread

    # Verifica si la compilación fue exitosa
    if [ $? -eq 0 ]; then
        echo "Guardando resultado de Benchmark para $programa..."
        "./$programa"> "${programa}BenchC_results.txt"
        valgrind --tool=cachegrind "./$programa" 2> "${programa}C_results.txt"
        
    else
        echo "Error: La compilación de $programa ha fallado."
    fi
done
