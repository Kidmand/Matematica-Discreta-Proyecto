# COMO EJECUTAR -> python3 tests/v2.construirGrafo.test.py
import subprocess

use_valgrind = False


def compilar_archivo(c_file, c_file2):
    try:
        # Ejecutar el comando make para compilar el archivo
        subprocess.run(['make', 'test-compile', f'FILE={c_file}'], check=True)
        subprocess.run(['make', 'test-compile', f'FILE={c_file2}'], check=True)
    except subprocess.CalledProcessError as e:
        # Manejar errores si la compilación falla
        print(f"Error al compilar el archivo: {e}")


def ejecutar(params, input_file):
    try:
        print("\n-------------------------------------\n")
        print('Ejecutando el test v2', input_file)
        if use_valgrind:
            # ['valgrind', '--leak-check=full', '--show-leak-kinds=all', '--track-origins=yes', '--verbose']
            comando = ['valgrind'] + \
                ['./tests/v2.construirGrafo.test.out'] + params
        else:
            comando = [f'./tests/v2.construirGrafo.test.out'] + params

        proceso = subprocess.run(comando,
                                 stdin=open(input_file),
                                 stdout=subprocess.PIPE,
                                 check=True)
        # Imprimir la salida del programa en la consola
        print(proceso.stdout.decode())
        print("\n-------------------------------------\n")
        # print('Ejecutando el test ', input_file)
        print('Ejecutando test v1 ', input_file)
        proceso = subprocess.run([f'./tests/construirGrafo.test.out'],
                                 stdin=open(input_file),
                                 stdout=subprocess.PIPE,
                                 check=True)
        # Imprimir la salida del programa en la consola
        print(proceso.stdout.decode())
    except subprocess.CalledProcessError as e:
        # Manejar errores si la compilación o la ejecución fallan
        print(f"Error: {e}")


if __name__ == "__main__":
    # Ruta del archivo .c que deseas compilar
    archivo_c = "tests/v2.construirGrafo.test.c"
    archivo_c2 = "tests/construirGrafo.test.c"
    compilar_archivo(archivo_c, archivo_c2)

    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_basico.txt")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_muchos_espacios.txt")
    ejecutar(['5', '10'], "tests/ejemplos_inputs/K5.txt")
    ejecutar(['9', '14'], "tests/ejemplos_inputs/K5_con_lados_de_mas.txt")
    ejecutar(['8', '10', '3'], "tests/ejemplos_inputs/grafo_chico.txt")
    ejecutar(['256', '320', '3'], "tests/ejemplos_inputs/64gb.txt")
    ejecutar(['536', '114036', '437'], "tests/ejemplos_inputs/4CBQ10.txt")
    ejecutar(['1072', '84424', '169'],
             "tests/ejemplos_inputs/grafo_mediano.txt")
    # # Si se desea probar con grafos más grandes, descomentar las siguientes líneas y agregar el archivo de prueba (NO SUBIR A GITHUB)
    # ejecutar(['2000000', '7196008'],
    #          "tests/ejemplos_inputs_extremos/grafo_muy_grande.txt")
    # ejecutar(['6160', '18092520', '6057'],
    #          "tests/ejemplos_inputs_extremos/harkon.txt")

    print("\n---Ejemplos con comentarios---")
    ejecutar(['2', '1'], "tests/ejemplos_inputs/ejemplo_comentarios_1.txt")
    ejecutar(['2', '1'], "tests/ejemplos_inputs/ejemplo_comentarios_2.txt")
    ejecutar(['2', '1'], "tests/ejemplos_inputs/ejemplo_comentarios_3.txt")
    ejecutar(['2', '1'], "tests/ejemplos_inputs/ejemplo_comentarios_4.txt")

    print("\n---Ejemplos con errores----")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_error_1.txt")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_error_2.txt")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_error_3.txt")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_error_4.txt")
    ejecutar(['8', '10'], "tests/ejemplos_inputs/ejemplo_con_error_5.txt")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_error_6.txt")
    ejecutar(['4', '6'], "tests/ejemplos_inputs/ejemplo_con_error_7.txt")
