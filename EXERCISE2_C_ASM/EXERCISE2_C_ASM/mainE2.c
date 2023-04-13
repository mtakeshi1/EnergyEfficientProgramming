/***********************************************************************************************************
*
** SOURCE CODE C/ASM
*
** Name: mainE2.c
** Date: Spring 2023
** Author: Prof Vesselin Iossifov, HTW Berlin
** System: MS Visual Studio C++, MASM
** Debug x86
***********************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define dim 32

int vector_a [dim];
int vector_b [dim];

static struct feld { int array1;
	int array2;
	}vector[dim];

static struct result { int sum1;
	int sum2;
	}dot_prod;

extern int vdp_sequential(struct feld vector[], struct result dot_prod);

void main (void)
{
	int i;

//Initialise vectors for dot product.

srand( (unsigned)time( NULL ) );

	for (i=0; i<dim;i++) {
	  vector[i].array1 = rand()%10;
	  vector[i].array2 = rand()%10;
	}

// Sequencial computed vector dot product

dot_prod.sum1 = 0;
dot_prod.sum1 = vdp_sequential(vector, dot_prod);

printf("\ndot product in ANSI C = %xh\n",dot_prod.sum1);

}