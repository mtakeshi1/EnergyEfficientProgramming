/***********************************************************************************************************
*  VECTOR SCALAR PRODUCT: MATHEMATICAL BASIS OF STREAMING CODECS
* https://de.wikipedia.org/wiki/Streaming-Codec
* 
** Name: VDP_SISD_SSE_float.c
** Date: Spring 2023
** Author: Prof Vesselin Iossifov, HTW Berlin
** System: Visual Studio C++ ... Win64, MASM, Intel's VTune Profiler 2021.3
** Debug x86
***********************************************************************************************************/

/** Sources
** Vector dot product
https://de.wikipedia.org/wiki/Skalarprodukt

Link to oracle.com 	x86 Assembly Language Reference Manual
https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html

The Intel Intrinsics Guide
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#expand=4428,5417,5503,5289,2816&techs=MMX

MMX and SSE examples
- Robert van Engelen
https://www.cs.fsu.edu/~engelen/courses/HPC-adv/MMXandSSEexamples.txt

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:
1. 	Build a Console Application project EXERCISE9_SSE_ASM for VSP_SIMD_SSE_float.c.
2. 	Analyse EXERCISE9_SSE_ASM.exe by debugging.
		
**********************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


//#define dim_float 2097152
#define dim_float 8
#define dim_sse 4

float vector_af[dim_float];
float vector_bf[dim_float];
//float teilsummen_f[3];
float partialsum_f[3];
float *ptr_vector_af, *ptr_vector_bf;

void main (void)
{

	int i;
	float dp_f, VDP_f[3];
	
	srand((float)time(NULL));
	for (i = 0; i < dim_float; i++) {
		vector_af[i] = rand() / 1000;
		vector_bf[i] = rand() / 1000;
	}


	for (i = 0; i < 3; i++) {
		VDP_f[i] = 0.0;
	}

dp_f = 0;
ptr_vector_af = vector_af;
ptr_vector_bf = vector_bf;

__asm {
	//X86 Assembly/SSE: https://en.wikibooks.org/wiki/X86_Assembly/SSE

	// parameter transfer
	mov	esi, ptr_vector_af
	mov	edi, ptr_vector_bf

	mov	ecx, dim_float						// Number of elements vector_af, vector_bf;
	mov	ebx, dim_sse						// Degree of SSE parallelization

	xorps xmm7, xmm7						//xmm7:= Partial sum DotProd_f; set xmm7 = NULL
	xorps xmm6, xmm6						//xmm7:= Summing up the partial DotProd_f; set xmm6 = NULL
											//For both vectors into two partial sums

// SSE calculation of the vector scalar product for each 4 FLOAT elements in parallel
	s3 :
		movaps	xmm0, [esi]					//1. Set 4 x 32 Bit float elements vector_af
		movaps	xmm1, [edi]					//1. Set 4 x 32 Bit float elements vector_bf

		mulps	xmm0, xmm1					//Multiply element by element
		
		//MOVLHPS Move two packed single - precision floating - point values from the low quadword of an XMM
		//register to the high quadword of another XMM register.
		movlhps xmm2, xmm0					//and add the products
		addps	xmm2, xmm0					//

		//MOVHLPS Move two packed single-precision floating-point values from the high quadword of an XMM
		//register to the low quadword of another XMM register.
		movhlps xmm7, xmm2					//xmm7:= DotProd_f(Teil1), DotProd_f(Teil2) 
		addps	xmm6, xmm7					//xmm6:= DotProd_f(Teil1), DotProd_f(Teil2) add up
		sub		ecx, ebx					//(Number of elements vector_af, vector_bf)  Parallelization level								
											// modulo - range_sse
		jz		s4							//If no other elements, then s4:

		add		esi, 16						//Pointer on next set 4 x 32 Bit elements of  vector_af
		add		edi, 16						//Pointer on next set 4 x 32 Bit elements of vector_bf
		jnz		s3

	s4 :
		//Move Low Packed Single - Precision Floating - Point Values
		//https://c9x.me/x86/html/file_module_x86_id_191.html
		movlps	partialsum_f, xmm6
		emms
	}

partialsum_f[2] = partialsum_f[0] + partialsum_f[1];
VDP_f[2] = partialsum_f[2];

printf("\nFLOAT VECTOR DOT PRODUKT WITH SIMD SSE/inline Assembly   = %.3f\n", VDP_f[2]);
//_getch();

}