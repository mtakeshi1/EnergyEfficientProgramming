/***********************************************************************************************************
*  MATRIX MULTIPLICATION WITH 256 bit AVX Intrinsics
* https://de.wikipedia.org/wiki/Streaming-Codec
*
** Name: MxM_SIMD_AVX.c
** Date: Spring 2023
** Author: Prof Vesselin Iossifov, HTW Berlin
** System: Visual Studio C++ ... Win64, MASM, Intel's VTune Profiler 2021.3
** Debug x86
***********************************************************************************************************/

/** QUELLEN
** MATRIX MULTIPLICATION
https://en.wikipedia.org/wiki/Matrix_multiplication

Link to oracle.com 	x86 Assembly Language Reference Manual
https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html

The Intel Intrinsics Guide
https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#cats=Arithmetic&techs=AVX_ALL

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:
1. 	Build a Console Application project EXERCISE10_INTRINSICS for MxM_SIMD_AVX.c.
2. Set line 41 in theis way
					41		#define IMPLEMENTATION 2 // 0 is serial 1 is unrolled 2 is with intrinsics
3.  Compile MxM_SIMD_AVX.c mit DEBUG x64
4. 	Analyse EXERCISE10_INTRINSICS.exe by debugging.
**********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <immintrin.h>	

#define TEST 1			// triggers test on when set to 1
//#define TEST 0		N 1024, *.exe to be analysed with VTune
//#define TEST 1		N 8 plus printf (); to analyse code semantics


#define IMPLEMENTATION 2 // 0 is serial 1 is unrolled 2 is with intrinsics
#if (TEST == 1)			
# define N 8			
#else
# define N 8		
#endif

#define row N			// number of matrix rows
#define col N			// number of matrix columns
#define unroll 8		// loop unrolling factor


void main(void)
{
	// declares counter variables
	int i, j, k;
	float maxRand = 5.0;
	// allocates memory and returns pointer to it
	float* mat_a = (float*)malloc(row * col * sizeof(float));
	float* mat_b = (float*)malloc(row * col * sizeof(float));
	float* mat_c0 = (float*)malloc(row * col * sizeof(float));
	float* mat_c1 = (float*)malloc(row * col * sizeof(float));
	float* mat_c2 = (float*)malloc(row * col * sizeof(float));

	// initializes matrices
	srand((unsigned)time(NULL));
	// this loop has no measurement data as it wasn't included in the vtune results or all values were close to 0
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			*(mat_a + i * row + j) = (((float)rand() / (float)(RAND_MAX)) * maxRand);
			*(mat_b + i * row + j) = (((float)rand() / (float)(RAND_MAX)) * maxRand);
			// only initialize result matrice values when it is needed
			if (IMPLEMENTATION == 0 || TEST == 1) {
				*(mat_c0 + i * row + j) = 0;
			}
			if (IMPLEMENTATION == 1 || TEST == 1) {
				*(mat_c1 + i * row + j) = 0;
			}
			if (IMPLEMENTATION == 2 || TEST == 1) {
				*(mat_c2 + i * row + j) = 0;
			}

		}
	}

	if (IMPLEMENTATION == 0 || TEST == 1) {
		// serial multiplication
		// this loop has no measurement data as it wasn't included in the vtune results or all values were close to 0
		for (i = 0; i < row; i++) {
			// this loop has no measurement data as it wasn't included in the vtune results or all values were close to 0
			for (j = 0; j < col; j++) {
				for (k = 0; k < row; k++) {
					*(mat_c0 + i * row + j) += *(mat_a + i * row + k) * *(mat_b + k * row + j);
				}
			}
		}
	}
	if (IMPLEMENTATION == 1 || TEST == 1) {
		// unrolled multiplication
		// this loop has no measurement data as it wasn't included in the vtune results or all values were close to 0
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				// unrolled loop with factor eight
				for (k = 0; k < row; k += unroll) {
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 0)) * *(mat_b + (k + 0) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 1)) * *(mat_b + (k + 1) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 2)) * *(mat_b + (k + 2) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 3)) * *(mat_b + (k + 3) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 4)) * *(mat_b + (k + 4) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 5)) * *(mat_b + (k + 5) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 6)) * *(mat_b + (k + 6) * row + j);
					*(mat_c1 + i * row + j) += *(mat_a + i * row + (k + 7)) * *(mat_b + (k + 7) * row + j);
				}
			}
		}
	}
	if (IMPLEMENTATION == 2 || TEST == 1) {
		// multiplication with avx intrinsics 
		__m256 vA, vB, vC;
		// this loop has no measurement data as it wasn't included in the vtune results or all values were close to 0
		for (i = 0; i < row; i++) {

			for (k = 0; k < row; k++) {
				/*
				void _mm256_store_ps (float * mem_addr, __m256 a)
				Instruction: vmovaps m256, ymm
				Description: Store 256-bits (composed of 8 packed single-precision (32-bit) floating-point elements) from a into memory. 
							 mem_addr must be aligned on a 32-byte boundary or a general-protection exception may be generated.
				Operation:	MEM[mem_addr+255:mem_addr] := a[255:0]

				*/
				/*
				__m256 _mm256_set1_ps (float a)
				Instruction: Sequence
				Description:	Broadcast single-precision (32-bit) floating-point value a to all elements of dst.
				Operation:
					FOR j := 0 to 7
						i := j*32
						dst[i+31:i] := a[31:0]
					ENDFOR
					dst[MAX:256] := 0
				*/
				_mm256_store_ps(&vA, _mm256_set1_ps(*(mat_a + i * row + k)));

				/* Loop in line in main

				*/
				for (j = 0; j < col; j += unroll) {
					/*
					__m256 _mm256_loadu_ps (float const * mem_addr)
					Instruction: vmovups ymm, m256
					Description:	Load 256-bits (composed of 8 packed single-precision (32-bit) floating-point elements) from memory into dst. 
					mem_addr does not need to be aligned on any particular boundary.
					Operation:
						dst[255:0] := MEM[mem_addr+255:mem_addr]
						dst[MAX:256] := 0
					*/
					_mm256_store_ps(&vB, _mm256_loadu_ps((__m256*) & *(mat_b + k * row + j)));
					_mm256_store_ps(&vC, _mm256_loadu_ps((__m256*) & *(mat_c2 + i * row + j)));

					/*
					__m256 _mm256_add_ps (__m256 a, __m256 b)
					Instruction: vaddps ymm, ymm, ymm
					Description:	Add packed single-precision (32-bit) floating-point elements in a and b, and store the results in dst.
					Operation:
						FOR j := 0 to 7
							i := j*32
							dst[i+31:i] := a[i+31:i] + b[i+31:i]
							ENDFOR
						dst[MAX:256] := 0
					*/
					/*
					__m256 _mm256_mul_ps (__m256 a, __m256 b)
					Instruction: vmulps ymm, ymm, ymm
					Description:	Multiply packed single-precision (32-bit) floating-point elements in a and b, and store the results in dst.
					Operation:
						FOR j := 0 to 7
							i := j*32
							dst[i+31:i] := a[i+31:i] * b[i+31:i]
						ENDFOR
						dst[MAX:256] := 0
					*/
					_mm256_store_ps(&vC, _mm256_add_ps(vC, _mm256_mul_ps(vA, vB)));

					_mm256_store_ps((__m256*) & *(mat_c2 + i * row + j), vC);
				}
			}
		}
	}

	// if test value is 1 print out matrices to compare the results
	if (TEST == 1) {
		printf("\n--mat_c0 ------------------------------------------------- \n");
		for (i = 0; i < row; i++) {
			printf("\n");
			for (j = 0; j < col; j++) {
				printf("\ %3.3f", *(mat_c0 + i * col + j));
			}
			printf("\n");
		}
		printf("\n--mat_c1 -------------------------------------------------  \n");
		for (i = 0; i < row; i++) {
			printf("\n");
			for (j = 0; j < col; j++) {
				printf("\ %3.3f", *(mat_c1 + i * col + j));
			}
			printf("\n");
		}
		printf("\n--mat_c2 -------------------------------------------------  \n");
		for (i = 0; i < row; i++) {
			printf("\n");
			for (j = 0; j < col; j++) {
				printf("\ %3.3f", *(mat_c2 + i * col + j));
			}
			printf("\n");
		}
	}

	// END OF TEST

	// frees allocated memory for matrices
	free(mat_a);
	free(mat_b);
	free(mat_c0);
	free(mat_c1);
	free(mat_c2);

	if (TEST == 1) 	_getch();
	return(0);
}