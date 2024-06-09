#include <stdarg.h>
#include <stdio.h>

#include "vec.h"
#include "cmath.h"

typedef unsigned int MX;

#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Bu Struct tanımı matrixin genel tanımıdır.
 *
 */
typedef struct
{
    /* Row and Col */
    unsigned int row;
    unsigned int col;

    /* Matrix Vectors */
    float **elements;

} matrix;

/**
 * @brief Tanımsız ifade oluşturabilecek durumlarda geri dönüş değeridir.
 *
 */
extern const matrix MATRIX_UNDEFINED;

/**
 * @brief Matrix için bellekten alan tahsilatı
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix allocate_matrix_mem(MX row, MX col);

/**
 * @brief Matrix konsolda yazdırmak için kullanılan fonksiyon.
 *
 * @param matx
 */
void print_matrix(matrix matx);

/**
 * @brief Row*Col Boyutunda Birim matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix identity_matrix(MX row, MX col);

/**
 * @brief Row*Col Boyutunda 0(sıfır) Matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix zero_matrix(MX row, MX col);

/**
 * @brief Matrix objesi oluşturmak için
 *
 * @param row
 * @param col
 * @param ... (liste şeklinde istenilen elemanları alır)
 * @return matrix
 */
matrix create_matrix(MX row, MX col, ...);

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

#endif