/***********************************************************************************************************
*
** SOURCE CODE C/ASM
*
** Name: mainE1.c
** Date: Spring 2023
** Author: Prof Vesselin Iossifov, HTW Berlin
** System: MS Visual Studio C++, MASM
** Debug x86
***********************************************************************************************************/


#include <stdio.h>
// #include <conio.h>

extern int ASM_Addition(int A, int B);

void main (){
	int a=5,b=3,c;
	

	c=ASM_Addition(a,b);
	printf("%i + %i = %i\n",a,b,c);
	getch();
}