#include <stdlib.h>
#include <string.h>
#include "matrix_algebra.h"
#include <time.h>
#include <math.h>

#define TOLERANCE 1e-4

double rand_double()
{
	return (double)rand()/RAND_MAX*2.0-1.0;//float in range -1 to 1

}


int matrix_compare(char* filename1, char* filename2)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.
	FILE* fptr = fopen(filename1, "rb"); // open the file 
	if(fptr == NULL)
	{
		//opening file failed,
		return 0;
	}
	FILE* fptr2 = fopen(filename2, "rb"); // open the file 

	if(fptr2 == NULL)
	{
		fclose(fptr);
		return 0;
	}

	int n, m;
	int n1,m1;
	int read = 0;
	read = fread(&n, sizeof(int), 1, fptr);
	if(read <= 0)
	{	
		// could not read the integer, file is corrupted or EOF?
		fclose(fptr);
		fclose(fptr2);
		return 0;
	}
	read = fread(&n1, sizeof(int), 1, fptr2);
	if(read <= 0)
	{	
		// could not read the integer, file is corrupted or EOF?
		fclose(fptr);
		fclose(fptr2);
		return 0;
	}
	if(n != n1)
	{
		fclose(fptr);
		fclose(fptr2);
		return 0;
	}
	read = fread(&m, sizeof(int), 1, fptr);
	if(read <= 0)
	{	
		// could not read the integer, file is corrupted or EOF?
		fclose(fptr);
		fclose(fptr2);
		return 0;
	}
	read = fread(&m1, sizeof(int), 1, fptr2);
	if(read <= 0)
	{	
		// could not read the integer, file is corrupted or EOF?
		fclose(fptr);
		fclose(fptr2);
		return 0;
	}
	if(m != m1)
	{
		fclose(fptr);
		fclose(fptr2);
		return 0;
	}

	for(int i = 0; i < m*n; i++)
	{
		double k1, k2;
		read = fread(&k1, sizeof(double), 1, fptr);
		if(read != 1)
		{
			fclose(fptr);
			fclose(fptr2);
			return 0;
		}
		read = fread(&k2, sizeof(double), 1, fptr2);
		if(read != 1)
		{
			fclose(fptr);
			fclose(fptr2);
			return 0;
		}
		if(fabs(k1 - k2) > TOLERANCE)
		{
			fclose(fptr);
			fclose(fptr2);
			return 0;
		}
	}

	fclose(fptr);
	fclose(fptr2);
	return 1;



}

void test(int t)
{
	char filename[100];
	snprintf(filename, 100, "tests/test%d_1.b", t);
	mat* A = matrix_read(filename);
	snprintf(filename, 100, "tests/test%d_2.b", t);
	mat* B = matrix_read(filename);
	mat* ApB = matrix_add(A, B);
	mat* AB = matrix_multiply(A, B);
	mat* cA = matrix_scale(3.14, A);
	snprintf(filename, 100, "tests/out%d_add.b", t);
	matrix_write(filename,  ApB);
	snprintf(filename, 100, "tests/out%d_mult.b", t);
	matrix_write(filename,  AB);
	snprintf(filename, 100, "tests/out%d_scale.b", t);
	matrix_write(filename,  cA);
	matrix_free(A);
	matrix_free(B);
	matrix_free(ApB);
	matrix_free(AB);
	matrix_free(cA);
	char filenameexp[100];
	printf("=========== TEST %d RESULT ===============\n", t);
	snprintf(filename, 100, "tests/out%d_scale.b", t);
	snprintf(filenameexp, 100, "tests/exp%d_scale.b", t);
	if(matrix_compare(filename, filenameexp))
	{
		printf("PASSED");
	}else 
	{
		printf("FAILED");
	}
		printf(" Test %d (matrix_scale)\n", t);
	
	snprintf(filename, 100, "tests/out%d_add.b", t);
	snprintf(filenameexp, 100, "tests/exp%d_add.b", t);
	if(matrix_compare(filename, filenameexp))
	{
		printf("PASSED");
	}else 
	{
		printf("FAILED");
	}

		printf(" Test %d (matrix_add)\n", t);
	
	snprintf(filename, 100, "tests/out%d_mult.b", t);
	snprintf(filenameexp, 100, "tests/exp%d_mult.b", t);
	if(matrix_compare(filename, filenameexp))
	{
	printf("PASSED");
	}else 
	{
	printf("FAILED");	
	}

		printf(" Test %d (matrix_multiply)\n", t);
	printf("==========================================\n");
}


int main(int argc, char** argv)
{

	if(strcmp("-t", argv[1]) == 0)
	{
		for(int i = 0; i < 20; i++)
		{
			test(i);
		}
	}
}
