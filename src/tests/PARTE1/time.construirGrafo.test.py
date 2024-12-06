import subprocess
import time

archivo_out = "tests/time.construirGrafo.test.out"


def compilar_archivo(c_file):
    try:
        # Ejecutar el comando make para compilar el archivo
        subprocess.run(['make', 'test-compile', f'FILE={c_file}'], check=True)
    except subprocess.CalledProcessError as e:
        # Manejar errores si la compilación falla
        print(f"Error al compilar el archivo: {e}")


def ejecutar(input_file, repeticiones=10):

    tiempos = []
    for _ in range(repeticiones):
        inicio = time.time()
        resultado = subprocess.run([archivo_out], stdin=open(input_file))
        fin = time.time()
        tiempo_transcurrido = fin - inicio
        tiempos.append(tiempo_transcurrido)
    if resultado.returncode == 0:
        print("El programa se ejecutó correctamente.✅")
    else:
        print("Hubo un error al ejecutar el programa.⛔")
    # Imprimir el mensaje de error en la salida de errores estándar
    
    tiempo_maximo = max(tiempos)
    tiempo_minimo = min(tiempos)
    diferencia = ((tiempo_maximo-tiempo_minimo)/tiempo_maximo)*100
    tiempo_promedio = sum(tiempos) / repeticiones
    print(f"El caso {input_file} tardó en ejecutarse los siguientes tiempos:")
    print(f"Tiempo promedio: {tiempo_promedio:.5f} segundos")
    print(f"Tiempo máximo: {tiempo_maximo:.5f} segundos")
    print(f"Tiempo mínimo: {tiempo_minimo:.5f} segundos")
    print(f"Diferencia entre maximo y minimo: {diferencia:.5f}%\n")


if __name__ == "__main__":
    archivo_c = "tests/time.construirGrafo.test.c"
    compilar_archivo(archivo_c)

    # ejecutar("tests/ejemplos_inputs/ejemplo_basico.txt")
    # ejecutar("tests/ejemplos_inputs/ejemplo_con_error.txt")
    # ejecutar("tests/ejemplos_inputs/K5.txt")
    # ejecutar("tests/ejemplos_inputs/K5_con_lados_de_mas.txt")
    # ejecutar("tests/ejemplos_inputs/grafo_chico.txt")
    # ejecutar("tests/ejemplos_inputs/64gb.txt")
    # ejecutar("tests/ejemplos_inputs/4CBQ10.txt")
    # ejecutar("tests/ejemplos_inputs/grafo_mediano.txt")
    ejecutar("tests/ejemplos_inputs_extremos/harkon.txt")
    ejecutar("tests/ejemplos_inputs/ejemplo_comentarios_3.txt")
