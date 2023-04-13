;subE5_ASM_OPT2.asm

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

	.686P
	.model FLAT
	.code
PUBLIC	_Feld_Add
_C$ = 8
_A$ = 12
_B$ = 16
_Feld_Add PROC NEAR

; 4    : void Feld_Add(long C[], long A[], long B[]){

	push	ebp
	mov		ebp, esp
	PUSH	ESI
	PUSH	EDI

; 5    : 	int i;
; 6    : 
; 7    : 	for (i=0;i<N;i++){

	XOR ECX,ECX
	MOV ESI,_A$[EBP]
	MOV EDI,_B$[EBP]
	MOV EBX,_C$[EBP]
	jmp	SHORT $L30
$L31:
	INC ECX
$L30:
	CMP ECX,20
	jge	SHORT $L32

; 8    : 		C[i]=A[i]+B[i];

	MOV EAX,[ESI+ECX*4]
	ADD EAX,[EDI+ECX*4]
	MOV [EBX+ECX*4],EAX

; 9    : 	}/* for */

	jmp	SHORT $L31
$L32:

; 10   : }/* Feld_Add */

	POP	EDI
	POP ESI
	pop	ebp
	ret	0
_Feld_Add ENDP
END
