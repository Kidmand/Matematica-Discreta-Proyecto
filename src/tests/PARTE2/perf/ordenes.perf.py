import subprocess
import os
import glob
import time

# Si esta activa, repeticiones = 1 y no se muestra tiempo.
use_valgrind = True
remove_out = True
repeticiones = 100


class Tester:
    def __init__(self, use_valgrind=False, remove_out=True):
        self.use_valgrind = use_valgrind
        self.remove_out = remove_out

        # Ruta absoluta del directorio de ejecución del programa
        self.current_dir = os.path.abspath('.')

        # Ruta absoluta del directorio padre de este archivo python
        self.python_dir = os.path.dirname(os.path.abspath(__file__))

        # Ruta absoluta del directorio donde se encuentra el makefile
        self.make_dir = os.path.join(self.python_dir, '../../../')

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

    def ejecutar(self, name_test_file, name_input_file, repeticiones=10):
        '''
        Recibe en <name_test_file> el nombre del archivo compilado .out.
        El archivo debe estar en el mismo directorio que este python.
        Recibe en <name_input_file> el nombre del archivo de input.
        El archivo debe estar en PARTE2/inputs/
        Recibe en <repeticiones> la cantidad de veces que se ejecutará el programa.
        '''
        try:
            print("-"*25 + name_input_file + "-"*25 + "\n")
            ruta_input_file = os.path.abspath(os.path.join(
                self.python_dir, '../inputs', name_input_file))
            ruta_greedy_test_out = os.path.abspath(
                os.path.join(self.python_dir, name_test_file))
            if self.use_valgrind:
                # Valgrind: ['valgrind', '--leak-check=full', '--show-leak-kinds=all', '--track-origins=yes']
                # Callgrind: ['valgrind', '--tool=callgrind', '--dump-instr=yes', '--collect-jumps=yes']
                comando = ['valgrind', '--leak-check=full', '--show-leak-kinds=all', '--track-origins=yes'] + \
                    [ruta_greedy_test_out]
            else:
                comando = [ruta_greedy_test_out]

            tiempos = []
            for _ in range(repeticiones):
                inicio = time.time()
                proceso = subprocess.run(comando,
                                         stdin=open(ruta_input_file),
                                         #  stdout=subprocess.PIPE,
                                         #  stderr=subprocess.STDOUT,  # Tambien capturamos el stderr
                                         check=True)
                fin = time.time()
                tiempo_transcurrido = fin - inicio
                tiempos.append(tiempo_transcurrido)
            if proceso.returncode == 0:
                print("El programa se ejecutó correctamente.✅")
            else:
                print("Hubo un error al ejecutar el programa.⛔")
            # Imprimir el mensaje de error en la salida de errores estándar
            if not self.use_valgrind:
                tiempo_maximo = max(tiempos)
                tiempo_minimo = min(tiempos)
                diferencia = ((tiempo_maximo-tiempo_minimo)/tiempo_maximo)*100
                tiempo_promedio = sum(tiempos) / repeticiones
                print(
                    f"El caso {name_input_file} tardó en ejecutarse {repeticiones} veces los siguientes tiempos:")
                print(f"Tiempo promedio: {tiempo_promedio:.5f} segundos")
                print(f"Tiempo máximo: {tiempo_maximo:.5f} segundos")
                print(f"Tiempo mínimo: {tiempo_minimo:.5f} segundos")
                print(f"Diferencia entre maximo y minimo: {diferencia:.5f}%\n")

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
        if use_valgrind:
            repeticiones = 1

        # Test de GulDukat:
        archivo_c = "tests/PARTE2/perf/orden_GulDukat.perf.c"  # Ruta desde el makefile
        t.compilar_archivo(archivo_c)

        print("Test de GulDukat:")
        # t.ejecutar("orden_GulDukat.perf.out",
        #            "../../ejemplos_inputs_extremos/harkon.txt", 1)
        t.ejecutar("orden_GulDukat.perf.out", "PGJ10_500.txt", repeticiones)
        t.ejecutar("orden_GulDukat.perf.out",
                   "ejemplo_basico.txt", repeticiones)
        t.ejecutar("orden_GulDukat.perf.out",
                   "ejemplo_2.txt", repeticiones)

        # Test de ElimGarak:
        archivo_c = "tests/PARTE2/perf/orden_ElimGarak.perf.c"  # Ruta desde el makefile
        t.compilar_archivo(archivo_c)
        print("Test de ElimGarak:")
        # t.ejecutar("orden_ElimGarak.perf.out",
        #            "../../ejemplos_inputs_extremos/harkon.txt", 1)
        t.ejecutar("orden_ElimGarak.perf.out", "PGJ10_500.txt", repeticiones)
        t.ejecutar("orden_ElimGarak.perf.out",
                   "ejemplo_basico.txt", repeticiones)
        t.ejecutar("orden_ElimGarak.perf.out", "ejemplo_2.txt", repeticiones)

    except Exception as e:
        print(f"Error inesperado: {e}")


# --------------------------------Documentacion-----------------------------------------#

''' DOC:
Si use_valgrind esta activo es para chequear errores de memoria con valgrind o
contar la cantidad de instrucciones con callgrind (modificar el camando para esto).

Si use_valgrind no esta activo, entonces solo hara mediciones de tiempo.
'''

''' DOC:
COMO EJECUTAR: 
Ejecutar -> python3 ordenes.perf.py
Se puede ejecutar desde cualquier directorio :)
'''

''' DOC:
COMO AGREGAR TESTs:
1. Agregar el archivo_perf.txt en la carpeta inputs.
(Indicar perf para diferenciarlo de los archivos que sirven para los tests)

3. Agregar test al python:

t.ejecutar("orden_algunOrden.perf.out", "ejemplo_basico.txt", repeticiones)
t.ejecutar("orden_otroOrden.perf.out", "ejemplo_basico.txt", repeticiones)
'''


# --------------------------------Observaciones-----------------------------------------#

''' NOTE: Uso de callgrind para ver datos de profilado (Profile data)

1. Poner las variables globales del test arriba del todo en estos valores:
use_valgrind = True
remove_out = False

2. Ejecutar el test.

3. Luego de ejecutar el test, se generan archivos callgrind.out.<Numero de proceso>

4. Para ver los datos de perfilado hay dos opciones:

A. kcachegrind
Se pueden ver con una app llamada kcachegrind, que se instala con: sudo apt-get install kcachegrind
Solo hay que hacer los pasos del 1 al 3, y luego ejecutar: kcachegrind

B. callgrind_annotate
Sino, se pueden ver con el comando callgrind_annotate:
usage: callgrind_annotate [options] [callgrind-out-file [source-files...]]

Basicamente:
Ejecutar -> callgrind_annotate callgrind.out.<Numero de proceso>

Para mas detalles tenemos las flags:
-v: Muestra una versión más detallada del perfil.
--inclusive=yes: Incluye tiempo de espera en la cuenta de cada función.
--tree=none: Muestra una lista plana de las funciones y líneas de código.
      =caller: Muestra para cada función las funciones que la llaman. 
               Es decir, muestra las funciones que están antes en la pila de llamadas.
      =calling: Muestra para cada función las funciones que llama. 
                Es decir, muestra las funciones que están después en la pila de llamadas.
      =both: Muestra tanto las funciones que llaman como las que son llamadas por cada función. 
--threshold=X: Muestra solo líneas de código que han sido ejecutadas al menos X veces.
-- ...

Por ejemplo, para mostrar un perfil más detallado con inclusión de tiempo y 
un umbral de ejecución de 10, usarías:

Ejecutar ->  callgrind_annotate --inclusive=yes callgrind.out

OPTIONAL: Lo siguiente no hay sido investigado.
Eventos: 

Valgrind Callgrind permite analizar varios tipos de eventos durante la ejecución de un programa. Algunos de los eventos comunes que se pueden analizar incluyen:

Instrucciones ejecutadas (Ir): Este evento cuenta el número de instrucciones de programa ejecutadas durante la ejecución del programa. Es útil para medir la carga de trabajo del procesador.
Accesos a memoria (Dr, Dw): Estos eventos cuentan el número de lecturas (Dr) y escrituras (Dw) a memoria realizadas durante la ejecución del programa. Son útiles para identificar patrones de acceso a memoria y posibles cuellos de botella de rendimiento.
Cache misses (I1mr, D1mr, D2mr, D3mr): Estos eventos cuentan el número de misses en las diferentes jerarquías de caché durante la ejecución del programa. Ayudan a identificar la eficiencia del uso de la caché y posibles áreas de optimización.
Branch mispredictions (Bcm): Este evento cuenta el número de predicciones fallidas de saltos condicionales durante la ejecución del programa. Es útil para identificar el rendimiento de la predicción de saltos y posibles mejoras en la estructura del código.
Llamadas a funciones (Cfn): Este evento cuenta el número de llamadas a funciones durante la ejecución del programa. Ayuda a entender la estructura del programa y la distribución del tiempo de ejecución entre funciones.
Ciclos de CPU (I1c, D1c, D2c, D3c): Estos eventos cuentan el número de ciclos de CPU utilizados durante la ejecución del programa en las diferentes jerarquías de la caché. Son útiles para medir el rendimiento en términos de tiempo de CPU utilizado.

'''
