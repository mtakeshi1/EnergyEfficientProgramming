
/***********************************************************************************************************
*  VECTOR SCALAR PRODUCT: MATHEMATICAL BASIS OF STREAMING CODEC
* https://de.wikipedia.org/wiki/Streaming-Codec
*
*
** Name: VDP_SISDzuSIMD_float_RELEASE.c
** Date: Spring 2022
** Author: Prof. Vesselin Iossifov, HTW Berlin
** System: Intel CPU Gen. i9 or higher, Win10, VC++ Win64, MASM, Intel VTune, Amplifier 2019
** Project configuration:	RELEASE x86
***********************************************************************************************************/

/** Sources
** Skalarprodukt
https://de.wikipedia.org/wiki/Skalarprodukt

Link to oracle.com 	x86 Assembly Language Reference Manual
https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html

MMX and SSE examples
- Robert van Engelen
https://www.cs.fsu.edu/~engelen/courses/HPC-adv/MMXandSSEexamples.txt

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:

1.	Build VTune project for EXERCISE12_VDP_VTune.exe
2.	Analyse FIRST EXERCISE12_VDP_VTune_SISD.exe with the Intel's VTune Profiler 2021.3 tool. Notice the results
	in the way presented in Read Me EXERCISE12_VDP_VTune.txt.
	C:\PROJEKTE\EEP_Exercises_WinDbg\EXERCISE12_VDP_SISD_VTune\Release
3.	Analyse SECOND EXERCISE12_VDP_VTune_SIMD.exe with the Intel's VTune Profiler 2021.3 tool. Notice the results
	in the way presented in Read Me EXERCISE12_VDP_VTune.txt.
	C:\PROJEKTE\EEP_Exercises_WinDbg\EXERCISE12_VDP_SIMD_VTune\Release
4. 	Compare the Results of points 2. and  3 and evaluuate in %.

**********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Dimension of the task is to be selected depending on the performance parameters of the computer,  
// Intel CPU generation and memory capacity

#define dim_float 2097152
//#define dim_float 1048576

#define dim_mmx 4
#define dim_sse 4
#define range_superscalar 4

static struct feld_f {float array1f;
					  float array2f;
					  }vector_f[dim_float];

float dot_prod_f[range_superscalar];

float vector_af[dim_float];
float vector_bf[dim_float];
float teilsummen_f[3];
float *ptr_vector_af, *ptr_vector_bf;

void main (void)
{

	int i;
	float dp_f, VDP_f[3];

// Initialize DATA STRUCTURE  for Vector Scalar Product with Sequential/SSE Streaming Data instructions FLOAT
	srand((float)time(NULL));
	for (i = 0; i < dim_float; i++) {
		vector_af[i] = rand()/1000;
		vector_bf[i] = rand()/1000;
	}

	for (i = 0; i < 3; i++) {
		VDP_f[i] = 0.0;
	}

// TASK 1. Sequential FLOAT Code
/**/	
for (i = 0; i < dim_float; i++) {
	VDP_f[0] += vector_af[i] * vector_bf[i];
}
							
//printf("\nFLOAT VECTOR DOT PRODUKCT SEQUENTIEL   = %.3f\n", VDP_f[0]);


// TASK 2. Sequential FLOAT code is replaced with SSE Streaming data instructions in inline assembly

/*
dp_f = 0;
ptr_vector_af = vector_af;
ptr_vector_bf = vector_bf;

__asm {
//X86 Assembly/SSE
//https://en.wikibooks.org/wiki/X86_Assembly/SSE#Shuffling_example_using_shufps


	// Parametertransfer 
	mov	esi, ptr_vector_af
	mov	edi, ptr_vector_bf

	mov	ecx, dim_float						// Number of elements vector_af, vector_bf;
	mov	ebx, dim_sse						// Degree of SSE parallelisation

	xorps xmm7, xmm7						//xmm7:= Partial DotProd_f; set xmm7 = NULL
	xorps xmm6, xmm6						//xmm7:=Summing up the partial DotProd_f; set xmm6 = NULL
											//for both vectors in two partial sums

// SSE calculation of the vector dot product for each 4 FLOAT elements in parallel

	s3 :
		movaps	xmm0, [esi]					//1. Set 4 x 32 Bit FLOAT elements vector_af
		movaps	xmm1, [edi]					//1. Set 4 x 32 Bit FLOAT elements vector_bf

		mulps	xmm0, xmm1					//Multiply by element
		
		//MOVLHPS Move two packed single - precision floating - point values from the low quadword of an XMM
		//register to the high quadword of another XMM register.
		movlhps xmm2, xmm0
		addps	xmm2, xmm0					//..and add the products

		//MOVHLPS Move two packed single-precision floating-point values from the high quadword of an XMM
		//register to the low quadword of another XMM register.
		movhlps xmm7, xmm2					//xmm7:= DotProd_f(Teil1), DotProd_f(part 1) 
		addps	xmm6, xmm7					//xmm6:= DotProd_f(Teil1), DotProd_f(part 2) sum up
		sub		ecx, ebx					//(Number of elements vector_af, vector_bf) - Degree of parallelisation									
											// modulo - range_sse
		jz		s4							//If no other elements, then s4:

		add		esi, 16						//Pointer next set 4 x 32 Bit elements vector_af
		add		edi, 16						//Pointer next set  4 x 32 Bit elements vector_bf
		jnz		s3

	s4 :
		//Move Low Packed Single - Precision Floating - Point Values
		//https://c9x.me/x86/html/file_module_x86_id_191.html
		movlps	teilsummen_f, xmm6
		emms
	}

teilsummen_f[2] = teilsummen_f[0] + teilsummen_f[1];
VDP_f[2] = teilsummen_f[2];
//printf("\nFLOAT VECTOR DOT PRODUCT REPLACED WITH SIMD SSE/inline assembly   = %.3f\n", VDP_f[2]);
//_getch();
*/
}