#include <stdio.h>
#include "CMATH/cmath.h"
#include "CMATH/vec.h"
#include "VMATRIX/vmatrix.h"

int main()
{

    printf("\n\n      ***Done Run***      \n\n");

    printf("_________________________IDENTITY MATRIX______________________\n");
    matrix test = __identity_matrix(2, 2);
    __print_matrix(test);
    //__free_matrix(&test);

    printf("_________________________ZERO MATRIX______________________\n");
    matrix zero = __zero_matrix(5, 5);
    __print_matrix(zero);
    //__free_matrix(&zero);

    printf("_________________________CREATE MATRIX______________________\n");
    matrix cre = __create_matrix(2, 3, -1.0f, 3.0f, 9.0f, 1.0f, -7.3f);
    __print_matrix(cre);
    //__free_matrix(&cre);

    {
        // matrix cpy = __copy_matrix(cre);
        //__print_matrix(cpy);
        //__free_matrix(&cpy);

        // matrix *ptr = __copy_matrix_ptr(test);
        //__print_matrix(*ptr);
        //__free_matrix(ptr);

        // ADD Algebra Test
        // matrix add = __sum_matrix(test, cre);
        //__print_matrix(add);
        //__free_matrix(&add);

        // SUBSTRACT Algebra Test
        //__substract_matrix_ptr(&add, cre);
        //__print_matrix(add);

        // SUBSTRACT Algebra Test
        //__divide_matrix_ptr(&add, cre);
        //__print_matrix(add);
    }

    printf("_________________________TRANSPOSE MATRIX______________________\n");
    // TRANSPOSE Algebra Test
    matrix trs = __transpose_matrix(cre);
    __print_matrix(trs);

    printf("_________________________MULTIPLICATION______________________\n");

    matrix m1 = __create_matrix(3, 2, -1.0f, 3.0f, 9.0f, 1.0f, -7.3f, 5.3f);
    __print_matrix(m1);

    matrix m2 = __create_matrix(2, 3, -3.2f, 1.2f, -2.5f, -8.4f, 7.3f, 97.3f);
    __print_matrix(m2);

    matrix mul = __multiplication_matrix(m1, m2);
    __print_matrix(mul);

    mul = __multiplication_matrix(m2, m1);
    __print_matrix(mul);

    printf("_________________________POWER MATRIX______________________\n");
    matrix poew = __power_matrix(mul, 7);
    __print_matrix(poew);

    return 0;
}