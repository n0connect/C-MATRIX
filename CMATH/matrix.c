#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"

/**
 * @brief Tanımsız bir matrix yapısı oluştur.
 * işlem basamakalrında yaşanacak olumsuzluklar
 * için bir geridönüş değeridir.
 */
const matrix MATRIX_UNDEFINED = {0, 0, NULL, NULL};

/**
 * @brief Matrix için bellekten alan tahsilatı
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix allocate_matrix_mem(MX row, MX col)
{
    /* MATRIX ESLESMESI */
    matrix rt_matrix;
    rt_matrix.row = row;
    rt_matrix.col = col;

    /* ilk pointer için row adet float pointer tahsil edilir */
    // BURADA ASLINDA SADECE ROW ADET float POINTER OLUŞTURUYORUZ
    rt_matrix.elements = malloc(row * sizeof(float));

    /* ayrılan her bir pointer için col adet float değer tahsil edilir */
    for (MX i = 0; i < row; i++)
    {
        rt_matrix.elements[i] = malloc(col * sizeof(float));
    }

    return rt_matrix;
}

/**
 * @brief Matrix konsolda yazdırmak için kullanılan fonksiyon.
 *
 * @param matx
 */
void print_matrix(matrix matx)
{

    if (matx.row == 0 && matx.col == 0 && matx.elements == NULL)
    {
        printf("\nThis matrix is UNDEFINED\n");
        return;
    }

    {
        printf("\n__");
        for (MX i = 0; i < matx.col; i++)
        {
            for (MX j = 0; j < 10; j++)
            {
                printf(" ");
            }
        }
        printf("\n");
    } /* Matrixin baş satırı */

    {
        for (MX i = 0; i < matx.row; i++)
        {
            printf("|");
            for (MX j = 0; j < matx.col; j++)
            {
                printf(" %f ", matx.elements[i][j]);
                if (j >= matx.col - 1)
                {
                    printf("|\n");
                }
            }
        }
    } /* Matrixin gövde kısmı */

    {
        printf("\n");
    } /* Matrixin son satırı */
}

/**
 * @brief Row*Col Boyutunda Birim matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix identity_matrix(MX row, MX col)
{
    if ((row != col) || row < 1 || col < 1)
    {
        return MATRIX_UNDEFINED;
    }

    matrix rt_matrix = allocate_matrix_mem(row, col);

    for (MX i = 0; i < row; i++)
    {
        for (MX c = 0; c < col; c++)
        {
            if (i == c)
            {
                rt_matrix.elements[i][c] = 1.0f;
            }
            else
            {

                rt_matrix.elements[i][c] = 0.0f;
            }
        }
    }

    return rt_matrix;
}

/**
 * @brief Row*Col Boyutunda 0(sıfır) Matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix zero_matrix(MX row, MX col)
{

    matrix rt_matrix = allocate_matrix_mem(row, col);

    for (MX i = 0; i < row; i++)
    {
        for (MX c = 0; c < col; c++)
        {
            rt_matrix.elements[i][c] = 0.0f;
        }
    }

    return rt_matrix;
}

/**
 * @brief Matrix objesi oluşturmak için
 *
 * @param row Satır Sayısı
 * @param col Stun Sayısı
 * @param ... (liste şeklinde elemanları alır)
 * @return matrix
 */
matrix create_matrix(MX row, MX col, ...)
{
    matrix ret_matrix = allocate_matrix_mem(row, col);
    MX size = row * col;

    va_list list;
    va_start(list, size);

    for (MX i = 0; i < row; i++)
    {
        for (MX c = 0; c < col; c++)
        {
            ret_matrix.elements[i][c] = va_arg(list, double);
        }
    }

    va_end(list);

    return ret_matrix;
}

/**
 * @brief Bir Matrix öğesini kopyalamak için.
 *
 * @param mat
 * @return matrix
 */
matrix copy_matrix(matrix mat);

/**
 * @brief Bir matrix öğesini pointer ile kopyalamak için.
 *
 * @param mat Kopyalanacak öğe
 * @return void
 */
void copy_matrix_ptr(matrix *mat);