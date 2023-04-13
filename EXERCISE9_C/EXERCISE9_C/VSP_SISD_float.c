/***********************************************************************************************************
*  VEKTORSKALARPRODUKT: MATHEMATISCHE GRUNDLAGE DER STREAMING CODECS
* https://de.wikipedia.org/wiki/Streaming-Codec
*
** name: VSP_SISD_float.c
** date: Spring 2023
** author: Prof Vesselin Iossifov, HTW Berlin
** system: Visual Studio C++ ... Win64, MASM, Intel's VTune Profiler 2021.3
** Debug x86
***********************************************************************************************************/

/** QUELLEN
** Skalarprodukt
https://de.wikipedia.org/wiki/Skalarprodukt

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:
1. 	Build a Console Application project EXERCISE9_SSE_ASM for VSP_SISD_float.c.
2. 	Analyse EXERCISE9_SSE_ASM.exe by debugging.

**********************************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


//#define dim_float 2097152
#define dim_float 8

float vector_af[dim_float];
float vector_bf[dim_float];

void main(void)
{

	int i;
	float dp_f, VDP_f[3];


	/**/
	// Initialize DATA STRUCTURE  for Vector Scalar Product with Sequential/SSE Streaming Data instructions FLOAT
	srand((float)time(NULL));
	for (i = 0; i < dim_float; i++) {
		vector_af[i] = rand() / 1000;
		vector_bf[i] = rand() / 1000;
	}

	/**/
	for (i = 0; i < 3; i++) {
		VDP_f[i] = 0.0;
	}

	// Sequential code, data type float
	/**/
	for (i = 0; i < dim_float; i++) {
		VDP_f[0] += vector_af[i] * vector_bf[i];			
	}

	printf("\nFLOAT VECTOR DOT PRODUCT SISD   = %.3f\n", VDP_f[0]);
}