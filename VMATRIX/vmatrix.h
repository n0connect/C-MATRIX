#include <stdarg.h>
#include <stdio.h>

#include "../CMATH/vec.h"
#include "../CMATH/cmath.h"

typedef unsigned int MX;

#ifndef VMATRIX_H
#define VMATRIX_H

/**
 * @brief Bu Struct tanımı matrixin genel tanımıdır.
 *
 */
typedef struct
{
    /* Row and Col */
    unsigned int row;
    unsigned int col;

    /* Vektörler ile beraber */
    vec **vrows;

} matrix;

/**
 * @brief Tanımsız ifade oluşturabilecek durumlarda geri dönüş değeridir.
 *
 */
extern const matrix MATRIX_UNDEFINED;

/**
 * @brief Fonksiyonlarda meydana gelen bellek tahsilat hataları kontrolü
 *
 * @param ptr
 * @param msg
 */
void __allocation_err(void *ptr, const char *msg);

/**
 * @brief Vektör pointerını işaret eden pointerın işaret ettiği vektör.
 *
 * @param size
 * @return vec*
 */
vec *__allocate_vector_mem(MX size);

/**
 * @brief Matrix'i vektörler ile ifade etmek.
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix __allocate_row_vectors(MX row, MX col);

/**
 * @brief Matrix konsolda yazdırmak için kullanılan fonksiyon.
 *
 * @param matx
 */
void __print_matrix(matrix matx);

/**
 * @brief Oluşturulan matrixin bellekten serbest bırakan fonksiyon
 *
 * @param matx matrixi işaret eden pointerdir.
 */
void __free_matrix(matrix *matx);

/**
 * @brief Row*Col Boyutunda Birim matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix __identity_matrix(MX row, MX col);

/**
 * @brief Row*Col Boyutunda 0(sıfır) Matris oluşturur
 *
 * @param row
 * @param col
 * @return matrix
 */
matrix __zero_matrix(MX row, MX col);

/**
 * @brief Matrix objesi oluşturmak için
 *
 * @param row
 * @param col
 * @param ... (liste şeklinde istenilen elemanları alır)
 * @return matrix
 */
matrix __create_matrix(MX row, MX col, ...);

/**
 * @brief Bir Matrix öğesini kopyalamak için.
 *
 * @param mat
 * @return matrix
 */
matrix __copy_matrix(matrix matx);

/**
 * @brief Matrixi kopyalamak için bir pointer kullanır.
 *
 * @param matx Kopyalanacak öğenin kendisi.
 * @return matrix* Kopyalanmış matrisin pointer'ı.
 */
matrix *__copy_matrix_ptr(matrix matx);

/**
 * @brief İki adet Matrix'in toplamını hesaplayan fonksiyon
 *
 * @param matx1 Toplanacak Matris
 * @param matx2 Toplama işlemi uygulanacak ikinci matris
 * @return matrix Toplam Matrisi
 */
matrix __sum_matrix(matrix matx1, matrix matx2);

/**
 * @brief Toplam sonucunu birinci matrise pointer ile eşitler.
 *
 * @param matx1 Toplam sonucunu içeren matris
 * @param matx2 Toplanacak ikinci matris
 */
void __sum_matrix_ptr(matrix *matx1, matrix matx2);

/**
 * @brief İki adet Matrix'in Farkını hesaplayan fonksiyon
 *
 * @param matx1 Çıkarma işleminin ilk Matris elemanı
 * @param matx2 İkinci matris elemanı
 * @return matrix Çıkartma Matrisi
 */
matrix __substract_matrix(matrix matx1, matrix matx2);

/**
 * @brief İki adet Matrix'in Farkını pointer hesaplayan fonksiyon
 *
 * @param matx1 Çıkarma işleminin sonucunu içeren matris
 * @param matx2 İkinci matris elemanı
 */
void __substract_matrix_ptr(matrix *matx1, matrix matx2);

/**
 * @brief İki matrisin karşılık gelen elemanlarının bir birine olan bölümüdür
 *
 * @param matx1 Pay matrisi
 * @param matx2 Payda matrisi (non-zero)
 * @return matrix
 */
matrix __divide_matrix(matrix matx1, matrix matx2);

/**
 * @brief İki matrisin elementer bölümünü pointer yardımıyla hesaplayan fonskiyon
 *
 * @param matx1 Elementer bölümün sonucunu içerecek matrix
 * @param matx2 İkinci matrix elemanı
 * @return matrix
 */
void __divide_matrix_ptr(matrix *matx1, matrix matx2);

/**
 * @brief Bir matrisin bir skalel ile çarpımı.
 *
 * @param matx1
 * @param scalar
 * @return matrix
 */
matrix __scalar_multiplication(matrix matx1, float scalar);

/**
 * @brief Bir matrixin skaler ile çarpımını pointer ile hesaplayan fonksiyon.
 *
 * @param matx1 Sonucun atanacağı matrix
 * @param scalar Çarpım elemanı olacak skaler sayı
 */
void __scalar_multiplication_ptr(matrix *matx1, float scalar);

/**
 * @brief İki matrixin çarpımını hesaplayan fonksiyon (A.B) != (B.A)
 *
 * @param matx1 A
 * @param matx2 B
 * @return matrix Sonuç matrixi
 */
matrix __multiplication_matrix(matrix matx1, matrix matx2);

/**
 * @brief Bir matrixin transpoze değerini döndürür.
 *
 * @param matx Transpose bulunacak matrix.
 * @return matrix
 */
matrix __transpose_matrix(matrix matx);

/**
 * @brief Bir matrixin pozitif kuvvetini bulan fonksiyondur.
 *
 * @param matx
 * @param pow
 * @return matrix
 */
matrix __power_matrix(matrix matx, unsigned int pow);

#endif