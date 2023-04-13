
/***********************************************************************************************************
*  Multiplies two matrices, DATA TYP float, with AVX Streaming SIMD Extensions instructions intrinsics

*  MATRIX MULTIPLICATION: MATHEMATICAL BASIS OF STREAMING CODEC
* https://de.wikipedia.org/wiki/Streaming-Codec
*
*
** Name: MxM_SISD_SIMD_AVX_R.c
** Date: Spring 2022
** Advisor: Prof. Vesselin Iossifov, HTW Berlin
** System: Intel CPU Gen. i9 or higher, Win10, VC++ Win64, MASM, Intel VTune, Amplifier 2019
** Project configuration:	RELEASE x64
***********************************************************************************************************/

/*Sources
** Matrix multiplication
https://de.wikipedia.org/wiki/Matrizenmultiplikation

** C Dynamic Memory Allocation
https://www.programiz.com/c-programming/c-dynamic-memory-allocation

The Intel Intrinsics Guide
https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#expand=4428,5417,5503,5289,2816&techs=AVX_ALL

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:

1.	Build VTune project EXERCISE13_MxM_SISD_VTune
2.	Analyse FIRST EXERCISE13_MxM_SISD_VTune.exe with the Intel's VTune Profiler 2021.3 tool. Notice the results
	in the way presented in Read Me EXERCISE13_MxM_VTune.txt.
	C:\PROJEKTE\EEP_Exercises_WinDbg\EXERCISE13_MxM_SISD_VTune\x64\Release
3.	Analyse SECOND EXERCISE13_MxM_SIMD_VTune.exe with the Intel's VTune Profiler 2021.3 tool. Notice the results
	in the way presented in Read Me EXERCISE13_MxM_VTune.txt.
	C:\PROJEKTE\EEP_Exercises_WinDbg\EXERCISE13_MxM_SIMD_VTune\x64\Release
4. 	Compare the Results of points 2. and  3 and evaluuate in %.

**********************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <immintrin.h>	

#define TEST 0			// triggers test on when set to 1
//#define TEST 0		N 1024, *.exe to be analysed with VTune
//#define TEST 1		N 8 plus printf (); to analyse code semantics

#define IMPLEMENTATION 0// 0 is serial 1 is unrolled 2 is with intrinsics
#if (TEST == 1)			
# define N 8			
#else
# define N 1024
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
		printf("--------------------------------- \n");
		for (i = 0; i < row; i++) {
			printf("\n");
			for (j = 0; j < col; j++) {
				printf("\ %3.3f", *(mat_c0 + i * col + j));
			}
			printf("\n");
		}
		printf("--------------------------------- \n");
		for (i = 0; i < row; i++) {
			printf("\n");
			for (j = 0; j < col; j++) {
				printf("\ %3.3f", *(mat_c1 + i * col + j));
			}
			printf("\n");
		}
		printf("--------------------------------- \n");
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

	if (TEST == 1) _getch();
	
}