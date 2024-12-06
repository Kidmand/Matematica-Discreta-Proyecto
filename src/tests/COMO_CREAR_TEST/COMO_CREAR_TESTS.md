# ¿Como crear/usar `mini_unit_test`?

## INICIO:
1. Crea un archivo en la carpeta `tests` con el prefijo `test.c`, por ejemplo `funcionlidad_1.test.c`.
2. Importar la libreria `#include "mini_unit_test.h"`
3. Se tienen que crear lo test:
    - Se definen los tests con la macro `MU_TEST(test_name)`
      y **se implementan las pruebas dentro de la función**.
    - Para ello tenemos distinas herramientas para hacer las pruebas:
        - `mu_assert_string_eq(expected, actual)`
        - `mu_assert_double_eq(expected, actual)`
        - `mu_assert_int_eq(expected, actual)`
        - `mu_assert(condition, message)`
        - `mu_fail(message)`
        - `mu_check(condition)`
4. Se definen las suites de tests:
    - Se crea el **lugar en donde estan todos los tests** con `MU_TEST_SUITE(suite_name)`.
    - Dentro de la suite se agregan los tests con la macro `MU_RUN_TEST(test_name)`.
5. Se corren los tests:
    - Se corre la suite de tests con la macro `MU_RUN_SUITE(suite_name)`.
    - Se imprime el reporte de los tests con la macro `MU_REPORT()`.

## HERRAMIENTAS: 
- `mu_assert_string_eq(expected, actual)`:
    Esta macro se utiliza para comparar dos cadenas de caracteres. Comprueba si las
    dos cadenas son iguales. Si las cadenas son diferentes, la prueba fallará y se 
    mostrará un mensaje de error.

- `mu_assert_double_eq(expected, actual)`: 
    Esta macro se utiliza para comparar dos valores de tipo double. Comprueba si 
    los valores son iguales dentro de un margen de error aceptable. Si los valores 
    son diferentes fuera del margen de error, la prueba fallará y 
    se mostrará un mensaje de error.

- `mu_assert_int_eq(expected, actual)`: 
    Esta macro se utiliza para comparar dos valores de tipo int. Comprueba si los 
    valores son iguales. Si los valores son diferentes, la prueba fallará y 
    se mostrará un mensaje de error.

- `mu_assert(condition, message)`: 
    Esta macro se utiliza para evaluar una condición. Si la condición es falsa, la 
    prueba fallará y se mostrará el mensaje de error especificado.

- `mu_fail(message)`: 
    Esta macro se utiliza para marcar una prueba como fallida sin realizar ninguna comprobación.
    Puede ser útil para marcar una prueba como fallida intencionalmente en ciertas condiciones.

- `mu_check(condition)`: 
    Esta macro se utiliza para verificar una condición. Si la condición es falsa, la 
    prueba fallará y se mostrará un mensaje de error.

## EJEMPLO: 
Podes mirar el archivo `tests/example.test.c`