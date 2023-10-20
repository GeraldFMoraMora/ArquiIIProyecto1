import sys

def combine_results(program_name):
    perf_filename = f'{program_name}_perf.txt'
    txt_filename = f'{program_name}.txt'
    output_filename = f'{program_name}_combined.txt'

    # Leer el contenido del archivo de métricas de rendimiento
    perf_data = {}
    with open(perf_filename, 'r') as perf_file:
        for line in perf_file:
            if 'Performance counter stats' in line:
                for _ in range(5):
                    line = next(perf_file)
                perf_data = {metric.split()[0]: metric.split()[1] for metric in line.split()}

    # Leer el contenido del archivo de texto original
    txt_data = []
    with open(txt_filename, 'r') as txt_file:
        for line in txt_file:
            txt_data.append(line.strip())

    # Crear un archivo combinado con la información
    with open(output_filename, 'w') as output_file:
        # Escribir encabezados
        output_file.write('-' * 77 + '\n')
        output_file.write(f'{"Benchmark":<31} {"Time":<14} {"CPU":<14} {"Iterations":<14}')
        for metric in perf_data:
            output_file.write(f' {metric:<14}')
        output_file.write('\n')
        output_file.write('-' * 77 + '\n')

        # Escribir datos del archivo original
        for line in txt_data[2:]:
            output_file.write(line + ' ' * (77 - len(line)) + ' ')
            if len(perf_data) > 0:
                for metric in perf_data:
                    output_file.write(f'{perf_data[metric]:<14}')
                perf_data = {}
            output_file.write('\n')

    print(f'Archivo combinado creado en {output_filename}')

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python combine_results.py <nombre_programa>")
    else:
        program_name = sys.argv[1]
        combine_results(program_name)
