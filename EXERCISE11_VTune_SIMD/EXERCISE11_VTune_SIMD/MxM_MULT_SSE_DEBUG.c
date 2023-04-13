/***********************************************************************************************************
*  Multiplies two matrices, DATA TYP float, in Streaming SIMD Extensions Intrinsics.
* https://de.wikipedia.org/wiki/Streaming-Codec
*
** ENERGIEEFFIZIENZ DER  MATRIX MULTIPLIKATION LÖSUNGEN MIT VERSCHIEDENEN
   BEFEHLSSÄTZEN/SPEICHERSTRUKTUREN IN C/INTRINSICS CODIEREN UND VERGLEICHEN.
*
** Name: MxM_MULT_SSE_DEBUG.c
** Date: Spring 2022
** Advisor: Prof. Vesselin Iossifov, HTW Berlin
** System: Intel CPU Gen. i9 or higher, Win10, VC++ Win64, MASM, Intel VTune, Amplifier 2019
** Project configuration:	DEBUG x86
***********************************************************************************************************/

/** QUELLEN
** Matrizenmultiplikation
https://de.wikipedia.org/wiki/Matrizenmultiplikation

** C Dynamic Memory Allocation
https://www.programiz.com/c-programming/c-dynamic-memory-allocation

The Intel Intrinsics Guide
https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#expand=4428,5417,5503,5289,2816&techs=SSE_ALL

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:
1.  Build a Console Application project EXERCISE11_VTune_SIMD for MxM_MULT_SSE_DEBUG.c.
2.  Build project EXERCISE11_VTune_SIMD.exe with DEBUG x86 option
5.	Test EXERCISE11_VTune_SIMD.exe with WinDbg

**********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <smmintrin.h>	

#define TEST 1	// triggers test on when set to 1

#if (TEST == 1)		
# define N 8			
#else
# define N 2048			
#endif

#define row N			// number of matrix rows
#define col N			// number of matrix columns
#define unroll 4		// loop unrolling factor

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

	/*
		__m128i is data type used with the Streaming SIMD Extensions 2 (SSE2) instructions intrinsics
		__m128i will cause the compiler to generate the SSE2 movdqa instruction.
		
		Variable of type __m128i maps to the XMM[0-7] registers, 
		and is automatically aligned on 16-byte boundaries.
	*/
	__m128i vA, vB, vR;

	for (i = 0; i < row; i++) {
		for (k = 0; k < row; k++) {
			/*
				void _mm_storeu_si128 (__m128i* mem_addr, __m128i a)
				Instruction:	movdqu m128, xmm
				CPUID Flags:	SSE2
				Description:	Store 128-bits of integer data from a into memory.
								mem_addr does not need to be aligned on any particular boundary.

				Operation:		MEM[mem_addr+127:mem_addr] := a[127:0]
			*/
			_mm_storeu_si128(&vA, _mm_set1_epi32(*(mat_a + i*row + k)));
			/*
				__m128i _mm_set1_epi32 (int a)
				Instruction:	Seqeuence
				CPUID Flags:	SSE2
				Description:	Broadcast 32-bit integer a to all elements of dst. This intrinsic may generate vpbroadcastd.

				Operation:		FOR j := 0 to 3
									i := j*32
									dst[i+31:i] := a[31:0]
								ENDFOR
			*/
			for (j = 0; j < col; j += unroll) {
				/*
					__m128i _mm_loadu_si128 (__m128i const* mem_addr)
					Instruction:	movdqu xmm, m128
					CPUID Flags:	SSE2
					Description:	Load 128-bits of integer data from memory into dst. 
									mem_addr does not need to be aligned on any particular boundary.

					Operation:		dst[127:0] := MEM[mem_addr+127:mem_addr]
				*/
				_mm_storeu_si128(&vB, _mm_loadu_si128((__m128i*)&*(mat_b + k*row + j)));
				_mm_storeu_si128(&vR, _mm_loadu_si128((__m128i*)&*(mat_c + i*row + j)));
				/*
					__m128i _mm_add_epi32 (__m128i a, __m128i b)
					Instruction:	paddd xmm, xmm
					CPUID Flags:	SSE2
					Description:	Add packed 32-bit integers in a and b, and store the results in dst.

					Operation:		FOR j := 0 to 3
										i := j*32
										dst[i+31:i] := a[i+31:i] + b[i+31:i]
									ENDFOR
				*/
				_mm_storeu_si128(&vR, _mm_add_epi32(vR, _mm_mullo_epi32(vA, vB)));
				/*
					__m128i _mm_mullo_epi32 (__m128i a, __m128i b)
					Instruction:	pmulld xmm, xmm
					CPUID Flags:	SSE4.1
					Description:	Multiply the packed 32-bit integers in a and b, producing intermediate 64-bit 
									integers, and store the low 32 bits of the intermediate integers in dst.

					Operation:		FOR j := 0 to 3
										i := j*32
										tmp[63:0] := a[i+31:i] * b[i+31:i]
										dst[i+31:i] := tmp[31:0]
									ENDFOR
				*/				
				_mm_storeu_si128((__m128i*)&*(mat_c + i*row + j), vR);
			}
		}
	}

	// TEST
	if (TEST == 1) {
		
/**/
		for (i = 0; i < row; i++) {
			printf("\n");
			for (j = 0; j < col; j++) {
				printf("\t%d", *(mat_c + i*col + j));
			}
			printf("\n");
		}
	}
	// END OF TEST

	// frees allocated memory for matrices
	free(mat_a);
	free(mat_b);
	free(mat_c);

	if (TEST == 1) 	_getch();
}
