#include "mini_unit_test.h"

int sum(int a, int b)
{
    return a + b;
}

int sum_with_error(int a, int b)
{
    return a * b;
}

// Se definen los tests:
MU_TEST(test_sum_error)
{
    mu_assert(sum_with_error(2, 5) == 5, "Error: La suma de 2 y 3 no es igual a 5");
}

MU_TEST(test_sum_success)
{
    mu_assert(sum(2, 3) == 5, "Error: La suma de 2 y 3 no es igual a 5");
}

// Se define la suite de tests:
MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_sum_error);
    MU_RUN_TEST(test_sum_success);
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite); // Se corren todos los tests de la suite.
    MU_REPORT();              // Se imprime el reporte de los tests.
    return 0;
}
