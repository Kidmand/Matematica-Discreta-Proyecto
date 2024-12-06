import subprocess
import os
import glob

use_valgrind = False
remove_out = False


class Tester:
    def __init__(self, use_valgrind=False, remove_out=True):
        self.use_valgrind = use_valgrind
        self.remove_out = remove_out

        # Ruta absoluta del directorio de ejecución del programa
        self.current_dir = os.path.abspath('.')

        # Ruta absoluta del directorio padre de este archivo python
        self.python_dir = os.path.dirname(os.path.abspath(__file__))

        # Ruta absoluta del directorio donde se encuentra el makefile
        self.make_dir = os.path.join(self.python_dir, '../../')

        # Calcular la ruta relativa entre las dos rutas
        self.rutaAl_current_dir = os.path.relpath(
            self.current_dir, self.python_dir)

        # Calcular la ruta relativa entre las dos rutas
        self.rutaAl_python_dir = os.path.relpath(
            self.python_dir, self.current_dir)

    def compilar_archivo(self, c_file):
        '''
        Recibe en <c_file> la ruta desde el makefile al archivo .c que se desea compilar.
        Si la compilación falla, se lanza una excepción.
        '''
        # Ejecutar el comando make para compilar el archivo
        subprocess.run(['make', '-C', self.make_dir, 'test-compile',
                       f'FILE={c_file}'], check=True, stdout=subprocess.DEVNULL)
        print("Compilación exitosa \n")

    def ejecutar(self, params, name_input_file):
        '''
        Recibe en <name_input_file> solo el nombre del archivo de input, sin la ruta.
        El archivo debe estar en PARTE2/inputs/
        '''
        try:
            print("-"*25 + name_input_file + "-"*25 + "\n")
            print("Parametros: ")
            print("Color Cromatico esperado: ", params[0])
            print("Orden de coloreo: ", params[1:(len(params)+1)//2])
            print("Coloreo esperado: ", params[(len(params)+1)//2:])
            print()
            ruta_input_file = os.path.abspath(os.path.join(
                self.python_dir, 'inputs', name_input_file))
            ruta_greedy_test_out = os.path.abspath(os.path.join(
                self.python_dir, 'greedy.test.out'))
            if self.use_valgrind:
                # Valgrind: ['valgrind', '--leak-check=full', '--show-leak-kinds=all', '--track-origins=yes', '--verbose']
                # Callgrind: ['valgrind', '--tool=callgrind', '--dump-instr=yes', '--collect-jumps=yes']
                comando = ['valgrind'] + \
                    [ruta_greedy_test_out] + params
            else:
                comando = [ruta_greedy_test_out] + params

            proceso = subprocess.run(comando,
                                     stdin=open(ruta_input_file),
                                     stdout=subprocess.PIPE,
                                     stderr=subprocess.STDOUT,  # Tambien capturamos el stderr
                                     check=True)
            # Imprimir la salida del programa en la consola
            print(proceso.stdout.decode())

            if self.use_valgrind and self.remove_out:
                # Eliminar los archivos callgrind.out.*
                callgrind_out_files = glob.glob(
                    os.path.join(self.current_dir, 'callgrind.out.*'))
                for callgrind_out_file in callgrind_out_files:
                    os.remove(callgrind_out_file)
                # Eliminamos greedy.test.out ???
                # Si su, completar.

        except subprocess.CalledProcessError as e:
            # Manejar errores si la compilación o la ejecución fallan
            print(f"Error: {e}")


if __name__ == "__main__":
    try:
        # Ruta del archivo .c que deseas compilar
        t = Tester(use_valgrind, remove_out)
        archivo_c = "tests/PARTE2/greedy.test.c"  # Ruta desde el makefile
        t.compilar_archivo(archivo_c)

        t.ejecutar(['4', '0', '1', '2', '3', '1', '2', '3', '4'],
                "ejemplo_basico.txt")
        t.ejecutar(['4', '3', '2', '1', '0', '1', '2', '3', '4'],
                "ejemplo_basico.txt")
        t.ejecutar(['2', '0', '1', '2', '3', '4', '5', '1', '1',
                    '1', '2', '2', '2'], "ejemplo_2.txt")
        t.ejecutar(['3', '0', '3', '1', '4', '2', '5', '1', '1',
                    '2', '2', '3', '3'], "ejemplo_2.txt")
    except Exception as e:
        print(f"Error inesperado: {e}")

#--------------------------------Documentacion-----------------------------------------#
''' DOC:
COMO EJECUTAR: 
Ejecutar -> python3 greedy.test.py
Se puede ejecutar desde cualquier directorio :)
'''

''' DOC:
COMO AGREGAR TESTs:
1. Agregar el archivo.txt en la carpeta inputs.

2. Sea, 
x: numero cromatico esperado ej: 4
ys: orden[] para greedy ej: 0 1 2 3
zs: colores esperados para cada vertice (en el mismo orden) ej: 1 2 3 4

Escribir en el con el siguiente formato:
c
c
c numero cromatico: x
c orden: ys
c coloreo: zs
c comando: ./tests/PARTE2/greedy.test.out x ys zs < tests/PARTE2/inputs/archivo.txt
c
p edge 6 6      ---
e 0 4             |
e 0 5             |
e 1 3             |  Grafo de ejemplo
e 1 5             |
e 2 3             |
e 2 4           ---
TEXTO BASURA QUE NO DEBE LEERSE ........

3. Agregar test al python:
             x           ys                   xs 
             |   |----------------|  |-----------------|
t.ejecutar(['4', '0', '1', '2', '3', '1', '2', '3', '4'], "archivo.txt")
'''