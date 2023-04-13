;/***********************************************************************************************************
;* 
;** SOURCE CODE ASM_SUPERSCALAR
;* 
;** Name: sub_P_OPT2.asm
;** Date: Spring 2023
;** Author: Prof Vesselin Iossifov, HTW Berlin
;** System: Visual Studio C++, MASM
;** Debug/x86
;***********************************************************************************************************/

;/** Sources

;Intels Itanium-Architektur
;https://de.wikipedia.org/wiki/Itanium-Architektur

;Link to oracle.com x86 Assembly Language Reference Manual
;https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html

;***********************************************************************************************************/

;/***********************************************************************************************************
;Tasks:
;1. Build a Console Application project for mainE7.c, sub_P_OPT2.asm.
;2. Compuile and link sub_P_OPT2.asm. with mainE7.c to EXERCISE7_P_OPT2.exe
;3. Analyse the code structure of subE1_ASM.asm debugging EXERCISE7_P_OPT2.exe

;**********************************************************************************************************/

;Comment on ASM code extracted from the C code with the Microsoft (MS) C compiler

;The translation of C code by the MS compiler to a source code file with the command line 
;ML /c /Zi /coff ..\source_code_c_to_asm.asm
;creates a source code file with x86/x64 ASM code according to the compiler's settings.

;In the ASM code generated in this way, we recognize three code groups:

;1. The interface between the ASM code generated in this way and the function and data 
;structures of the executable *.exe file created by the C compiler. Here the values of the 
;function parameters of the original C function are passed to the ASM data structure.
;This code group extends to the beginning of the data processing, in the examples given here 
;to the C "for loop", which is recognizable as a comment in the generated ASM code.

;2.  The data processing  in the examples below starts with the  C "for-loop", which 
;is recognizable as a comment in the generated ASM code. The ASM code in this group attracts 
;our attention because it is where the resources intensive data processing takes place and we 
;want to learn techniques for minimizing the number of commands and further learn how to convert 
;the minimized code to the Execution Units architecture of superscalar CPUs. This allows the 
;minimized ASM code to be executed in parallel, which reduces execution time and thus reduces 
;energy consumption.The second phase ends with the end of the C "for loop".

;3. In the  third group Code  the  pointers are put back to the C code and data structure. 
;It starts with the end of the C-for loop.

	TITLE	c:\USER\sub_P_OPT2.asm
	.686P
	.model FLAT
	.code
PUBLIC	_Feld_Add
_TEXT	SEGMENT
_C$ = 8
_A$ = 12
_B$ = 16

_Feld_Add PROC NEAR

; 3    : void Feld_Add(long C[], long A[], long B[]){

	push	ebp
	mov	ebp, esp
	PUSH    ESI
	PUSH    EDI
; 4    : 	int i;
; 5    : 
; 6    : 	for (i=0;i<N;i++){
    	XOR ECX,ECX 
	MOV ESI,_A$[ebp]     ; Pointer Initialization _A
	MOV EDI,_B$[ebp]     ; Pointer Initialization _B  
	MOV EBX,_C$[ebp]     ; Pointer Initialization _C
;	jmp	SHORT $L30
$L31:
;    INC ECX
;$L30:
    CMP ECX,20 
	jge	$L32
; 7    : 		C[i++]=A[i]+B[i];	; 1. Loop iteration 
; 8    : 		C[i++]=A[i]+B[i]; 	; 2. Loop iteration 
;	
	MOV EAX,[ESI+ECX*4]			; 1. Loop iteration, issued to the U pipeline
		MOV EDX,[ESI+ECX*4+4]	; 2. Loop iteration, with Register Renaming,  issued to the V pipeline
	ADD EAX,[EDI+ECX*4]			; 1. Loop iteration, issued to the U pipeline
		ADD EDX,[EDI+ECX*4+4]	; 2. Loop iteration, with Register Renaming,  issued to the V pipeline
    MOV [EBX+ECX*4],EAX			; 1. Loop iteration, issued to the U pipeline
		MOV [EBX+ECX*4+4],EDX	; 2. Loop iteration, with Register Renaming,  issued to the V pipeline

; 9    : 		C[i++]=A[i]+B[i];	; 3. Loop iteration 
; 10   : 		C[i++]=A[i]+B[i];	; 4. Loop iteration 

	MOV EAX,[ESI+ECX*4+08]			; 3. Loop iteration, issued to the U pipeline
     	MOV EDX,[ESI+ECX*4+12]		; 4. Loop iteration, with Register Renaming,  issued to the V pipeline
	ADD EAX,[EDI+ECX*4+08]			; 3. Loop iteration, issued to the U pipeline
		ADD EDX,[EDI+ECX*4+12]		; 4. Loop iteration, with Register Renaming,  issued to the V pipeline
	MOV [EBX+ECX*4+08],EAX			; 3. Loop iteration, issued to the U pipeline
		MOV [EBX+ECX*4+12],EAX 		; 4. Loop iteration, with Register Renaming,  issued to the V pipeline
	ADD ECX,4;
;  11   : 	}/* for */
	jmp	$L31
$L32:
; 12   : }/* Feld_Add */
	POP EDI
	POP ESI
	pop	ebp
	ret	0
_Feld_Add ENDP
_TEXT	ENDS
END
