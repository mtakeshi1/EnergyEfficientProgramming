/***********************************************************************************************************
*  MMX Intrinsics

** Name: Intel_MMX_Intrinsics.c
** Date: Spring 2023
** Adviser: Prof Vesselin Iossifov, HTW Berlin
** System: Visual Studio C++ ... Win64, MASM, Intel's VTune Profiler 2021.3
* 
/***********************************************************************************************************
Tasks:

1. 	Build a Console Application project EXERCISE8_MMX_SSE_AVX for Intel_MMX_Intrinsics.c with Debug x86.
2. 	Analyse EXERCISE8_MMX_SSE_AVX.exe by debugging.
		
**********************************************************************************************************/

/*

Link to oracle.com 	x86 Assembly Language Reference Manual
https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html

The Intel Intrinsics Guide
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#expand=4428,5417,5503,5289,2816&techs=MMX

MMX and SSE examples
- Robert van Engelen
https://www.cs.fsu.edu/~engelen/courses/HPC-adv/MMXandSSEexamples.txt

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include <emmintrin.h>
#include <mmintrin.h>
#include <xmmintrin.h>

//#define N 65536
#define N 8

int main() {

	int i;

	//INIT __m64 _mm_add_pi8 (__m64 a, __m64 b)
	unsigned char b[N];
	unsigned char c[N];
	unsigned char a[N];

	//INIT __m64 _mm_madd_pi16 (__m64 a, __m64 b)
	short _b[N];
	short _c[N];
	short _a[N];
	short _d[N];
	
	short VDP;
	srand((unsigned)time(NULL));
	for (i = 0; i < N; i++) {
		_b[i] = rand() % 10;
		_c[i] = rand() % 10;
		_a[i] = 0;
		_d[i] = 0;
	}

	__m64 *_av, *_bv, *_cv, *_dv, *_ev;
	_av = (__m64*)_a; // assume 16-byte aligned
	_bv = (__m64*)_b; // assume 16-byte aligned
	_cv = (__m64*)_c; // assume 16-byte aligned
	_dv = (__m64*)_d; // assume 16-byte aligned
	_ev = (__m64*)_d; // assume 16-byte aligned
	__m64 count_32 = {32};

/*
__m64
https://docs.microsoft.com/de-de/cpp/cpp/m64?view=vs-2019

Synopsis
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=MMX&expand=4428,5417,5503,5289,2816

__m64 _mm_add_pi8 (__m64 a, __m64 b)
#include <mmintrin.h>
Instruction: paddb mm, mm
CPUID Flags: MMX
Description
Add packed 8-bit integers in a and b, and store the results in dst.
Operation
FOR j := 0 to 7
	i := j*8
	dst[i+7:i] := a[i+7:i] + b[i+7:i]
ENDFOR

MMX intrinsics (aligned load/store):

char a[N], b[N], c[N];
...
__m64 *av, *bv, *cv;
av = (__m64*)a; // assume 8-byte aligned
bv = (__m64*)b; // assume 8-byte aligned
cv = (__m64*)c; // assume 8-byte aligned
for (i = 0; i < N/8; i++)
  av[i] = _mm_add_pi8(bv[i], cv[i]);
*/
/*
	for (i = 0; i < N/8; i++)
		av[i] = _mm_add_pi8(bv[i], cv[i]);

	printf("\n\n    printout of vector a add vector b :=vector c\n\n");
	for (i = 0; i < N; i++) {
		printf("\n");
			printf("\t%d", a[i]);
		printf("\n");
	}
	_getch();
*/

/*
Synopsis
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=MMX&expand=4428,5417,5503,5289,2816

__m64 _mm_madd_pi16 (__m64 a, __m64 b)
#include <mmintrin.h>
Instruction: pmaddwd mm, mm
CPUID Flags: MMX
Description
Multiply packed signed 16-bit integers in a and b, producing intermediate signed 32-bit integers. Horizontally add adjacent pairs of intermediate 32-bit integers, and pack the results in dst.
Operation
FOR j := 0 to 1
	i := j*32
	dst[i+31:i] := SignExtend32(a[i+31:i+16]*b[i+31:i+16]) + SignExtend32(a[i+15:i]*b[i+15:i])
ENDFOR

*/
	for (i = 0; i < N/4; i++)
		_av[i] = _mm_madd_pi16(_bv[i], _cv[i]);
/*
Synopsis
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=MMX&expand=4428,5417,5503,5289,2816
__m64 _m_psrlq (__m64 a, __m64 count)
#include <mmintrin.h>
Instruction: psrlq mm, mm
CPUID Flags: MMX
Description
Shift 64-bit integer a right by count while shifting in zeros, and store the result in dst.
Operation
IF count[63:0] > 63
	dst[63:0] := 0
ELSE
	dst[63:0] := ZeroExtend64(a[63:0] >> count[63:0])
FI

*/

	for (i = 0; i < N / 4; i++) {
		_dv[i] = _m_psrlq(_av[i], count_32);
		_av[i] = _mm_add_pi32(_av[i], _dv[i]);
	}
	VDP = 0;
	for (i = 0; i < N; i+=4) {
		VDP += _a[i];
	}

/**/
	printf("\n\n    Printout VDP: %d", VDP);
	printf("\n");
//	_getch();

   return 0;
}