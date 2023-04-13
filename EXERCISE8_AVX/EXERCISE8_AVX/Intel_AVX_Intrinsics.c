/***********************************************************************************************************
*  AVX Intrinsics

** Name: Intel_AVX_Intrinsics.c
** Date: Spring 2023
** Adviser: Prof Vesselin Iossifov, HTW Berlin
** System: Visual Studio C++ ... Win64, MASM, Intel's VTune Profiler 2021.3

/***********************************************************************************************************
Tasks:

1. 	Build a Console Application project EXERCISE8_MMX_SSE_AVX for Intel_AVX_Intrinsics.c with Debug x64.
2. 	Analyse EXERCISE8_MMX_SSE_AVX.exe by debugging.

**********************************************************************************************************/

/*The Intel Intrinsics Guide
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX,AVX2

Crunching Numbers with AVX and AVX2
https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX

*/


#include <immintrin.h>
#include <stdio.h>

int main() {

  /* Initialize the two argument vectors */
  __m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
  __m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

  /* Compute the difference between the two vectors */
  __m256 result = _mm256_sub_ps(evens, odds);

  /* Display the elements of the result vector */
  float* f = (float*)&result;
  printf("%f %f %f %f %f %f %f %f\n",
    f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);

  return 0;
}