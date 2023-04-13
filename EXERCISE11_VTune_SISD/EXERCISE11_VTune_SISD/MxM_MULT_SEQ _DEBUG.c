/***********************************************************************************************************
*  Multiplies two matrices, DATA TYP float in SISD C
* https://de.wikipedia.org/wiki/Streaming-Codec
*
*
** Name: MxM_MULT_SEQ_DEBUG.c
** Date: Spring 2022
** Advisor: Prof. Vesselin Iossifov, HTW Berlin
** System: Intel CPU Gen. i9 or higher, Win10, VC++ Win64, MASM, Intel VTune, Amplifier 2019
** Project configuration:	DEBUG x86
***********************************************************************************************************/

/** Sources
** Matrizenmultiplikation
https://de.wikipedia.org/wiki/Matrizenmultiplikation

** C Dynamic Memory Allocation
https://www.programiz.com/c-programming/c-dynamic-memory-allocation

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:
1.  Build a Console Application project EXERCISE11_VTune_SISD for MxM_MULT_SEQ_DEBUG.c.
2.  Build project EXERCISE11_VTune_SISD.exe with DEBUG x86 option
5.	Test EXERCISE11_VTune_SISD.exe with WinDbg
**********************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define row  8			// number of matrix rows
#define col  8			// number of matrix column
//#define row  2048			// number of matrix rows
//#define col  2048			// number of matrix column

void main(void)
{
	// declares counter variables
	int i, j, k;

	// allocates memory and returns pointer to it
	int *mat_a = (int *)malloc(row * col * sizeof(int));
	int *mat_b = (int *)malloc(row * col * sizeof(int));
	int *mat_c = (int *)malloc(row * col * sizeof(int));

	// initializes matrices
	srand((unsigned)time(NULL));
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			*(mat_a + i*row + j) = rand() % 10;
			*(mat_b + i*row + j) = rand() % 10;
			*(mat_c + i*row + j) = 0;
		}
	}

	 // multiplies one matrix with another sequentially (cache misses)
	 for (i = 0; i < row; i++) {
	 	for (j = 0; j < col; j++) {
	 		for (k = 0; k < row; k++) {
	 			*(mat_c + i*row + j) += *(mat_a + i*row + k) * *(mat_b + k*row + j);
	 		}
	 	}
	 }
  
/**/
	 for (i = 0; i < col; i++) {
		 printf("\n");
		 for (j = 0; j < row; j++) {
			 printf("\t%d", *(mat_c + i * col + j));
		 }
		 printf("\n");
	 }

	// frees allocated memory for matrices
	free(mat_a);
	free(mat_b);
	free(mat_c);
}

