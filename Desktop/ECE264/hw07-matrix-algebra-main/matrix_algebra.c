#include "matrix_algebra.h"
#include <stdlib.h>
#include <stdio.h>

//define a struct to represent an n by m matrix. 
// the entries of this matrix should be doubles.
struct matrix 
{
	int rows;
	int cols;
	double **data;
};

typedef struct matrix mat;

mat* create_matrix(int n, int m)
{
	//Fill this function to return an n x m matrix of zeros.
	//The matrix should be allocated on the heap (that is, you return a mat* pointer)
	mat *output = malloc(sizeof(*output));
	if (!output){
		return NULL;
	}

	output -> data = calloc((size_t)n, sizeof(*output->data)); //allocates double pointer memory for n columns of length m 
	if (! output -> data){
		free(output);
		return NULL;
	}
	for (int i = 0; i < n; i++){
		output -> data[i] = calloc((size_t)m, sizeof(*output->data[i]));
		if (!output->data[i]){
			for(int k=0; k < i; k++){
				free(output->data[k]);
			}
			free(output->data);
			free(output);
			return NULL;
		}
	}

	output -> rows = m;
	output -> cols = n;
	return output;
}

mat* matrix_read(char* filename)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.
	if (!filename){
		return NULL;
	}

	FILE *f = fopen(filename, "rb");
	if(!f) {
		return NULL;
	}

	int n_rows = 0;
	int n_cols = 0;
	if (fread(&n_rows, sizeof n_rows, 1, f) != 1 || fread(&n_cols, sizeof n_cols, 1, f) != 1){
		fclose(f);
		return NULL;
	}
	if (n_rows <= 0 || n_cols <= 0){
		fclose(f);
		return NULL;
	}

	mat *M = create_matrix(n_cols, n_rows);
	if(!M){
		fclose(f);
		return NULL;
	}

	for (int r=0; r < n_rows; r++){
		for (int c = 0; c < n_cols; c++){
			double x;
			if (fread(&x, sizeof x, 1, f) != 1){
				matrix_free(M);
				fclose(f);
				return NULL;
			}
			M->data[c][r] = x;
		}
	}
	fclose(f);
	return M;
}

mat* matrix_multiply(mat* A, mat*B)
{
	//fill this function to return a new matrix AB, the product of A and B. Return NULL if the product does not exist.
	if (A->cols != B->rows){  //confirms compatibility
		return NULL;
	}

	mat *C = create_matrix(B->cols, A->rows);  //return matrix allocation and error handling
	if (!C){
		return NULL;
	}

	for (int i=0; i < B->cols; i++){  //matrix multiplication
		for (int j=0; j < A->rows; j++){
			for (int k=0; k < A->cols; k++){
				C ->data[i][j] += B->data[i][k] * A->data[k][j];
			}
		}
	}

	return C;
}

mat* matrix_add(mat* A, mat* B)
{
	//fill this function to return the matrix A+B, the addition of A and B. Return NULL if the addition does not exist.
	if ((A->rows != B->rows) || (A->cols != B->cols)){
		return NULL;
	}

	mat *C = create_matrix(A->cols, A->rows);
	if (!C){
		return NULL;
	}

	for (int i=0; i < A->cols; i++){
		for (int j=0; j < A->rows; j++){
			C->data[i][j] = A->data[i][j] + B->data[i][j];
		}
	}
	
	return C;
}

void matrix_free(mat* A)
{
	if (!A) return;
	//fill in this funciton to free the matrix A.
	if (A->data){
		for (int i=0; i < A->cols; i++){
			free(A->data[i]);
		}
		free(A->data);
	}
	free(A);
}

int matrix_write(char* filename, mat* A)
{
	// write A to the binary file filename. If this fails for whatever reason, return 0.
	if (!filename || !A) return 0;

    FILE *f = fopen(filename, "wb");
    if (!f) return 0;

    int n_rows = A->rows;
    int n_cols = A->cols;

    // write header: rows then cols
    if (fwrite(&n_rows, sizeof n_rows, 1, f) != 1 ||
        fwrite(&n_cols, sizeof n_cols, 1, f) != 1) {
        fclose(f);
        return 0;
    }

    // write payload row-major: for each row r, write n_cols doubles
    double *rowbuf = malloc((size_t)n_cols * sizeof *rowbuf);
    if (!rowbuf) { fclose(f); return 0; }

    for (int r = 0; r < n_rows; r++) {
        // gather this row from column-pointer storage
        for (int c = 0; c < n_cols; c++) {
            rowbuf[c] = A->data[c][r];   // internal: [col][row]
        }
        if (fwrite(rowbuf, sizeof *rowbuf, (size_t)n_cols, f) != (size_t)n_cols) {
            free(rowbuf);
            fclose(f);
            return 0;
        }
    }

    free(rowbuf);
    if (fclose(f) != 0) return 0;
    return 1;
}

// fill this function to modify A into cA, that is, to multiply each entry of A by c.
mat* matrix_scale(double c, mat* A)
{
	mat *C = create_matrix(A->cols, A->rows);
	if (!C){
		free(C);
		return NULL;
	}

	for (int i=0; i < A->cols; i++){
		for (int j=0; j < A->rows; j++){
			C->data[i][j] = A->data[i][j] * c;
		}
	}
	return C;
}





