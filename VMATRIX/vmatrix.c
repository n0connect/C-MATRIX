#include <stdlib.h>
#include <string.h>
#include <math.h>

//
//      VMATRIX.H
//     Tasarım olarak vektör
//  kullanan matrix kütüphanesi
//
//
#include "vmatrix.h"
#include "../CMATH/vec.h"

/**
 * @file vmatrix.c
 * @author Ahmet Berat
 * @brief
 * @version 0.1
 * @date 2024-06-08
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief Tanımsız bir matrix yapısı oluştur.
 * işlem basamakalrında yaşanacak olumsuzluklar
 * için bir geridönüş değeridir.
 */
const matrix MATRIX_UNDEFINED = {0, 0, NULL};

/**
 * @brief Fonksiyonlarda meydana gelen bellek tahsilat hataları kontrolü
 *
 * @param ptr
 * @param msg
 */
void __allocation_err(void *ptr, const char *msg)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed: %s\n", msg);
        exit(1);
    }

    // Clear
}

/**
 * @brief Vektör pointerını işaret eden pointerın işaret ettiği vektör.
 *
 * @param size
 * @return vec*
 */
vec *__allocate_vector_mem(MX size)
{
    vec *v = (vec *)malloc(sizeof(vec));

    __allocation_err(v, "vector pointer");

    v->dim = size;
    v->elements = (float *)malloc(size * sizeof(float));

    __allocation_err(v->elements, "vector elements pointer");

    return v;
}

/**
 * @brief Matrix'i vektörler ile ifade etmek.
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix __allocate_row_vectors(MX row, MX col)
{

    matrix rt_matrix;
    rt_matrix.row = row;
    rt_matrix.col = col;

    /* Vektör boyutunda row adet vektör yeri bellekten tahsil edilir */
    rt_matrix.vrows = (vec **)malloc(row * sizeof(vec *));

    __allocation_err(rt_matrix.vrows, "Row Vectors");

    for (MX i = 0; i < row; i++)
    {
        rt_matrix.vrows[i] = __allocate_vector_mem(col); // her vektör için bellek tahsis et
    }

    return rt_matrix;
}

/**
 * @brief Oluşturulan matrixin bellekten serbest bırakan fonksiyon
 *
 * @param matx matrixi işaret eden pointerdir.
 */
void __free_matrix(matrix *matx)
{
    for (MX i = 0; i < matx->row; i++)
    {
        free(matx->vrows[i]->elements);
        free(matx->vrows[i]);
    }
    free(matx->vrows);
}

/**
 * @brief Matrix konsolda yazdırmak için kullanılan fonksiyon.
 *
 * @param matx
 */
void __print_matrix(matrix matx)
{

    if (matx.row == 0 && matx.col == 0 && matx.vrows == NULL)
    {
        printf("\nThis matrix is UNDEFINED\n");
        return;
    }

    for (MX i = 0; i < matx.row; i++)
    {
        printf("[");
        for (MX c = 0; c < matx.col; c++)
        {
            printf(" %.3f ", matx.vrows[i]->elements[c]);

            if (c >= matx.col - 1)
            {
                printf("]\n");
                break;
            }
        }
    }

    printf("\n");
}
/**
 * @brief Row*Col Boyutunda Birim matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix __identity_matrix(MX row, MX col)
{
    if ((row != col) || row < 1 || col < 1)
    {
        return MATRIX_UNDEFINED;
    }

    matrix rt_matrix = __allocate_row_vectors(row, col);

    for (MX i = 0; i < row; i++)
    {
        for (MX c = 0; c < col; c++)
        {
            if (i == c)
            {
                rt_matrix.vrows[i]->elements[c] = 1.0f;
            }
            else
            {

                rt_matrix.vrows[i]->elements[c] = 0.0f;
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
matrix __zero_matrix(MX row, MX col)
{

    matrix rt_matrix = __allocate_row_vectors(row, col);

    for (MX i = 0; i < row; i++)
    {
        for (MX c = 0; c < col; c++)
        {
            rt_matrix.vrows[i]->elements[c] = 0.0f;
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
matrix __create_matrix(MX row, MX col, ...)
{
    matrix ret_matrix = __allocate_row_vectors(row, col);

    va_list list;

    /**
     * @brief Construct a new va start object
     *
     * va_start(list, last_fixed_arg);
     *
     * last_fixed_arg: Son adlandırılmış parametre.
     *  Bu, değişken argüman listesinden önce gelen son adlandırılmış parametredir.
     *  Bu, değişken argüman listesinin başlangıç noktasını belirlemek için kullanılır.
     *
     */
    va_start(list, col);

    for (MX i = 0; i < row; i++)
    {
        for (MX c = 0; c < col; c++)
        {
            ret_matrix.vrows[i]->elements[c] = (float)va_arg(list, double); // Argümanı float'a dönüştür
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
matrix __copy_matrix(matrix matx)
{
    matrix ret_matrix = __allocate_row_vectors(matx.row, matx.col);

    for (MX i = 0; i < ret_matrix.row; i++)
    {
        for (MX c = 0; c < ret_matrix.col; c++)
        {
            ret_matrix.vrows[i]->elements[c] = matx.vrows[i]->elements[c];
        }
    }

    return ret_matrix;
}

/**
 * @brief Matrixi kopyalamak için bir pointer kullanır.
 *
 * @param matx Kopyalanacak öğenin kendisi.
 * @return matrix* Kopyalanmış matrisin pointer'ı.
 */
matrix *__copy_matrix_ptr(matrix matx)
{
    matrix *ret_ptr = (matrix *)malloc(sizeof(matrix));

    __allocation_err(ret_ptr, "Copy function");

    *ret_ptr = __allocate_row_vectors(matx.row, matx.col);

    for (MX i = 0; i < matx.row; i++)
    {
        for (MX c = 0; c < matx.col; c++)
        {
            ret_ptr->vrows[i]->elements[c] = matx.vrows[i]->elements[c];
        }
    }

    return ret_ptr;
}

/**
 * @brief İki adet Matrix'in toplamını hesaplayan fonksiyon
 *
 * @param matx1 Toplanacak Matris
 * @param matx2 Toplama işlemi uygulanacak ikinci matris
 * @return matrix Toplam Matrisi
 */
matrix __sum_matrix(matrix matx1, matrix matx2)
{
    if (matx1.row != matx2.row || matx1.col != matx2.col)
    {
        printf("\n\nDimention Error add function\n\n");
        return MATRIX_UNDEFINED;
    }

    matrix ret_matx = __allocate_row_vectors(matx1.row, matx2.col);

    for (MX i = 0; i < matx1.row; i++)
    {
        for (MX c = 0; c < matx2.col; c++)
        {
            ret_matx.vrows[i]->elements[c] = matx1.vrows[i]->elements[c] +
                                             matx2.vrows[i]->elements[c];
        }
    }

    return ret_matx;
}

/**
 * @brief Toplam sonucunu birinci matrise pointer ile eşitler.
 *
 * @param matx1 Toplam sonucunu içeren matris
 * @param matx2 Toplanacak ikinci matris
 */
void __sum_matrix_ptr(matrix *matx1, matrix matx2)
{
    if (matx1->row != matx2.row || matx1->col != matx2.col)
    {
        printf("\n\nDimention Error add with pointer function\n\n");
        return;
    }

    for (MX i = 0; i < matx1->row; i++)
    {
        for (MX c = 0; c < matx2.row; c++)
        {
            matx1->vrows[i]->elements[c] += matx2.vrows[i]->elements[c];
        }
    }

    return;
}

/**
 * @brief İki adet Matrix'in Farkını hesaplayan fonksiyon
 *
 * @param matx1 Çıkarma işleminin ilk Matris elemanı
 * @param matx2 İkinci matris elemanı
 * @return matrix Çıkartma Matrisi
 */
matrix __substract_matrix(matrix matx1, matrix matx2)
{
    if (matx1.row != matx2.row || matx1.col != matx2.col)
    {
        printf("\n\nDimention Error substract function\n\n");
        return MATRIX_UNDEFINED;
    }

    matrix ret_matx = __allocate_row_vectors(matx1.row, matx2.col);

    for (MX i = 0; i < matx1.row; i++)
    {
        for (MX c = 0; c < matx2.col; c++)
        {
            ret_matx.vrows[i]->elements[c] = matx1.vrows[i]->elements[c] -
                                             matx2.vrows[i]->elements[c];
        }
    }

    return ret_matx;
}

/**
 * @brief İki adet Matrix'in Farkını pointer hesaplayan fonksiyon
 *
 * @param matx1 Çıkarma işleminin sonucunu içeren matris
 * @param matx2 İkinci matris elemanı
 */
void __substract_matrix_ptr(matrix *matx1, matrix matx2)
{
    if (matx1->row != matx2.row || matx1->col != matx2.col)
    {
        printf("\n\nDimention Error substract with pointer function\n\n");
        return;
    }

    for (MX i = 0; i < matx1->row; i++)
    {
        for (MX c = 0; c < matx2.row; c++)
        {
            matx1->vrows[i]->elements[c] -= matx2.vrows[i]->elements[c];
        }
    }

    return;
}

/**
 * @brief İki matrisin karşılık gelen elemanlarının bir birine olan bölümüdür
 *
 * @param matx1 Pay matrisi
 * @param matx2 Payda matrisi (non-zero)
 * @return matrix
 */
matrix __divide_matrix(matrix matx1, matrix matx2)
{
    if (matx1.row != matx2.row || matx1.col != matx2.col)
    {
        printf("\n\nDimention Error substract function\n\n");
        return MATRIX_UNDEFINED;
    }

    matrix ret_matx = __allocate_row_vectors(matx1.row, matx2.col);

    for (MX i = 0; i < matx1.row; i++)
    {
        for (MX c = 0; c < matx2.col; c++)
        {
            if (matx2.vrows[i]->elements[c] == 0.0f)
            {
                printf("\n\nSecond Matris has a value of 0 (zero)\n\n");
                return MATRIX_UNDEFINED;
            }
            else
            {
                ret_matx.vrows[i]->elements[c] = matx1.vrows[i]->elements[c] /
                                                 matx2.vrows[i]->elements[c];
            }
        }
    }

    return ret_matx;
}

/**
 * @brief İki matrisin elementer bölümünü pointer yardımıyla hesaplayan fonskiyon
 *
 * @param matx1 Elementer bölümün sonucunu içerecek matrix
 * @param matx2 İkinci matrix elemanı
 * @return matrix
 */
void __divide_matrix_ptr(matrix *matx1, matrix matx2)
{
    if (matx1->row != matx2.row || matx1->col != matx2.col)
    {
        printf("\n\nDimention Error divide with pointer function\n\n");
        return;
    }

    for (MX i = 0; i < matx1->row; i++)
    {
        for (MX c = 0; c < matx2.row; c++)
        {
            if (matx2.vrows[i]->elements[c] == 0.0f)
            {
                printf("\n\nSecond Matris has a value of 0 (zero)\n\n");
                __free_matrix(matx1);
                return;
            }
            else
            {
                matx1->vrows[i]->elements[c] /= matx2.vrows[i]->elements[c];
            }
        }
    }

    return;
}

/**
 * @brief Bir matrisin bir skalel ile çarpımı.
 *
 * @param matx1
 * @param scalar
 * @return matrix
 */
matrix __scalar_multiplication(matrix matx1, float scalar)
{

    matrix ret_matrix = __allocate_row_vectors(matx1.row, matx1.col);

    for (MX i = 0; i < matx1.row; i++)
    {
        for (MX c = 0; c < matx1.row; c++)
        {
            ret_matrix.vrows[i]->elements[c] = scalar * matx1.vrows[i]->elements[c];
        }
    }

    return ret_matrix;
}

/**
 * @brief Bir matrixin skaler ile çarpımını pointer ile hesaplayan fonksiyon.
 *
 * @param matx1 Sonucun atanacağı matrix
 * @param scalar Çarpım elemanı olacak skaler sayı
 */
void __scalar_multiplication_ptr(matrix *matx1, float scalar)
{

    for (MX i = 0; i < matx1->row; i++)
    {
        for (MX c = 0; c < matx1->col; c++)
        {
            matx1->vrows[i]->elements[c] *= scalar;
        }
    }

    return;
}

/**
 * @brief İki matrixin çarpımını hesaplayan fonksiyon (Satır ve sütun matrisleri arasında çarpma)(A.B) != (B.A)
 *
 * @param matx1 A
 * @param matx2 B
 * @return matrix Sonuç matrixi
 */
matrix __multiplication_matrix(matrix matx1, matrix matx2)
{
    if (matx1.col != matx2.row)
    {
        printf("\n\nDimention Error substract function\n\n");
        return MATRIX_UNDEFINED;
    }

    // Sonuç vektörünün boyutudur. -> (matx1.row, matx2.col)
    matrix ret_matrix = __allocate_row_vectors(matx1.row, matx2.col);

    // Çarpma işlemini kolaylaştırmak için Transposu alınır !
    matx2 = __transpose_matrix(matx2);

    if (matx2.vrows == NULL)
    {
        printf("\n\n *Failed Transpose second Matrix \n\n");
        return MATRIX_UNDEFINED;
    }

    for (MX i = 0; i < ret_matrix.row; i++)
    {
        vec *r_ptr = (vec *)matx1.vrows[i];

        for (MX c = 0; c < ret_matrix.col; c++)
        {
            vec *c_ptr = (vec *)matx2.vrows[c];

            ret_matrix.vrows[i]->elements[c] = (float)dot_product_of_vector((vec)*r_ptr, (vec)*c_ptr);
        }
    }

    return ret_matrix;
}

/**
 * @brief Bir matrixin transpoze değerini döndürür.
 *
 * @param matx Transpose bulunacak matrix.
 * @return matrix
 */
matrix __transpose_matrix(matrix matx)
{
    matrix ret_matrix = __allocate_row_vectors(matx.col, matx.row);

    for (MX i = 0; i < matx.row; i++)
    {
        for (MX c = 0; c < matx.col; c++)
        {
            ret_matrix.vrows[c]->elements[i] = matx.vrows[i]->elements[c];
        }
    }

    return ret_matrix;
}

/**
 * @brief Bir matrixin pozitif kuvvetini bulan fonksiyondur.
 *
 * @param matx Kuvveti alınacak matrix
 * @param pow int olarak girilmelidir.
 * @return matrix Hesaplanan matrix sonucu.
 */
matrix __power_matrix(matrix matx, unsigned int pow)
{
    if (pow <= 0)
    {
        printf("Negative power error.");
        return MATRIX_UNDEFINED;
    }
    else if (pow == 2)
    {
        return __multiplication_matrix(matx, matx);
    }

    matrix ret_matrix = __multiplication_matrix(matx, matx);

    for (MX i = 0; i < pow - 2; i++)
    {
        ret_matrix = __multiplication_matrix(ret_matrix, matx);
    }

    return ret_matrix;
}