# C-MATRIX

C-MATRIX is a C library designed for matrix operations, including allocation, multiplication, and transformation of matrices. This library is useful for mathematical computations and educational purposes, providing a foundation for understanding matrix manipulations in C.

## Features

- Matrix allocation and deallocation
- Basic matrix operations (addition, multiplication)
- Special matrix functions (identity matrix, zero matrix)
- Dynamic memory management for matrices
- Support for matrices of arbitrary size

## Getting Started

### Prerequisites

To compile and use the C-MATRIX library, you need:
- A C compiler (e.g., GCC)
- Make utility (optional but recommended)

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/n0connect/C-MATRIX.git
    cd C-MATRIX
    ```

2. Compile the code:
    ```sh
    gcc -o main main.c ./VMATRIX/vmatrix.c ./CMATH/vec.c
    ```

3. Run the executable:
    ```sh
    ./main
    ```

### Functions
matrix __create_matrix(MX row, MX col, ...) - Create a matrix with specified values.
matrix __identity_matrix(MX row, MX col) - Create an identity matrix.
matrix __multiply_matrices(matrix A, matrix B) - Multiply two matrices.
void __print_matrix(matrix mat) - Print a matrix to the console.
...

### Usage

Here's an example of how to use the library to create and manipulate matrices:

```c
#include <stdio.h>
#include "VMATRIX/vmatrix.h"
#include "CMATH/vec.h"

int main() {
    matrix A = __create_matrix(3, 3, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    __print_matrix(A);

    matrix B = __identity_matrix(3, 3);
    __print_matrix(B);

    matrix C = __multiply_matrices(A, B);
    __print_matrix(C);

    return 0;
}
```

Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure your code follows the project's style and includes appropriate tests.

Contact
For issues or questions, please open an issue on the GitHub repository.
