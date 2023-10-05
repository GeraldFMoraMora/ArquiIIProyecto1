# Abre el archivo de texto en modo lectura
with open('mSFSCPP_results.txt', 'r') as archivo:
    lineas = archivo.readlines()

# Inicializa diccionarios para almacenar los valores
valores_I = {}
valores_D = {}
valores_LL = {}

# Función para convertir números con comas en números con puntos
def convertir_a_float(texto):
    # Utiliza una expresión regular para extraer los dígitos y el punto decimal
    import re
    numero = re.sub(r'[^0-9.]', '', texto)
    return float(numero)

# Busca las líneas relevantes y almacena los valores en los diccionarios
for linea in lineas:
    if 'I1 misses:' in linea:
        valores_I['I1 misses'] = convertir_a_float(linea.split(':')[1].strip())
    elif 'LLi misses:' in linea:
        valores_I['LLi misses'] = convertir_a_float(linea.split(':')[1].strip())
    elif 'D1 misses:' in linea:
        valores_D['D1 misses'] = convertir_a_float(linea.split(':')[1].strip())
    elif 'LLd misses:' in linea:
        valores_D['LLd misses'] = convertir_a_float(linea.split(':')[1].strip())
    elif 'LL refs:' in linea:
        valores_LL['LL refs'] = convertir_a_float(linea.split(':')[1].strip())
    elif 'LL misses:' in linea:
        valores_LL['LL misses'] = convertir_a_float(linea.split(':')[1].strip())

# Imprime los valores almacenados
print("Valores de I:")
print(valores_I)
print("\nValores de D:")
print(valores_D)
print("\nValores de LL:")
print(valores_LL)
