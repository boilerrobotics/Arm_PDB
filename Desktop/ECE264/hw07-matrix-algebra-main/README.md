# HW07 - Matrix Algebra

In this homework, you will implement C functions to perform basic matrix operations, including reading and writing matrices to binary files.

## Part 0: Creating a matrix.

For this part, you will be asked to fill `struct matrix` to encode an `n` by `m` matrix of doubles. Then, you will need to fill in the function `create_matrix(int n, int m)` to return a `mat*` to a new `n` by `m` matrix of doubles.
PS: `mat*` is simply an alias for `struct matrix`, defined in `matrix_algebra.h`. This just makes it so you dont need to type `struct matrix` all the time.

## Part 1: IO Functions.

You will be asked to implemention two functions to read and write form binary files. Each binary file will store a single matrix. The format is as follows:

- The first 2 * `sizeof(int)` bytes are two integers, `n` and `m`, indicating the ammount of rows and columns in the matrix. This is follows by `nm * sizeof(double)` bytes representing the rows of the matrix. That is, the next `m * sizeof(double)` are the first row of the matrix. The `m * sizeof(double)` bytes after are the second row, and so on.

You must implement the following functions:

-`mat* matrix_read(char* filename)` -> returns an new `mat*` containing the matrix stored in the file named `filename`. If the file cannot be parsed into a matrix for any reason, this function should return `NULL`.

-`int matrix_write(char* filename, mat* A)` -> writes the matrix `A` into the file `filename`. If this fails for any reason, return 0. Otherwise, return 1.

## Part 2: Matrix operations.

For this part, you will be asked to implement functions for matrix addition, multiplication and scalar multiplication. The precise requirements are as follows:

-`mat* matrix_multiply(mat* A, mat* B)` -> returns an new `mat*` to the matrix `AB`, if it exists. If this product is not defined (think about when this happens. You may want to brush up on your calc 2 content), return `NULL`.

-`mat* matrix_add(mat* A, mat* B)` -> returns an new `mat*` to the matrix `A+B`, if it exists. If this addition is not defined, return `NULL`. (Again, think about when we can add two matrices. What are the conditions on their dimensions?). 

-`mat* matrix_scale(double c, mat* A)` -> returns an new `mat*` to the matrix `cA`, the scalar product of `c` and `A`.

Additionally, all the above functions must return NULL if any of the matrix arguments are `NULL`.

## Part 3: Testing your code.

You can check your code against the local test cases by running `make test`. You can also check for memory leaks by using `make memory`.

## Part 4: Submitting your code. 

Submit `matrix_algebra.c` ONLY to gradescope.
