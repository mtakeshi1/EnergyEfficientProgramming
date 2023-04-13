/***********************************************************************************************************
* 
** SOURCE CODE C/ASM
* 
** Name: mainE3.c
** Date: Spring 2023
** Author: Prof Vesselin Iossifov, HTW Berlin
** System: MS Visual Studio C++, MASM
** Debug x86
***********************************************************************************************************/

/** 

Microsoft Macro Assembler reference,
https://learn.microsoft.com/lv-lv/cpp/assembler/masm/microsoft-macro-assembler-reference?view=msvc-170

x86 Assembly Language Reference Manual
https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html

***********************************************************************************************************/

/***********************************************************************************************************
Tasks:
1. Build a Console Application project for mainE3.c, subE3.c.
2. Translate subE3.c via Visual Studio C++ to subE3.asm
3. Link subE3.obj with mainE3.c to EXERCISE3_C_ASM.exe
4. Analyse the code structure of subE3.asm debugging EXERCISE3_C_ASM.exe

**********************************************************************************************************/

#include <stdio.h>
#include <conio.h>

#define  N 20

extern void Feld_Add(long C[],long A[],long B[]);

void main (){
	int i;

	long FeldA[N]={ 1, 2,3 , 4, 5, 6, 7, 8, 9,10,
		           11,12,13,14,15,16,17,18,19,20};   
	long FeldB[N]={20,19,18,17,16,15,14,13,12,11,
		10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	long FeldC[N];
	Feld_Add(FeldC,FeldA,FeldB);
	for(i=0;i<N;i++){
		printf("%2i + %2i = %2i\n",FeldA[i],
			    FeldB[i],FeldC[i]);
	}
	_getch();
}
