; Listing generated by Microsoft (R) Optimizing Compiler Version 19.29.30141.0 

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

	TITLE	C:\PROJEKTE\EXERCISE6_P_OPT1\Debug\sub_P_OPT1.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

msvcjmc	SEGMENT
__BD7CEEEE_sub_P_OPT1@c DB 01H
msvcjmc	ENDS
PUBLIC	_Feld_Add
;PUBLIC	__JustMyCode_Default
EXTRN	@__CheckForDebuggerJustMyCode@4:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
;__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
;__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
; Function compile flags: /Odt
;	COMDAT __JustMyCode_Default
_TEXT	SEGMENT
;__JustMyCode_Default PROC				; COMDAT
	push	ebp
	mov	ebp, esp
	pop	ebp
	ret	0
;__JustMyCode_Default ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File C:\PROJEKTE\EXERCISE6_P_OPT1\sub_P_OPT1.c
;	COMDAT _Feld_Add
_TEXT	SEGMENT
_i$ = -8						; size = 4
_C$ = 8							; size = 4
_A$ = 12						; size = 4
_B$ = 16						; size = 4
_Feld_Add PROC						; COMDAT

; 5    : void Feld_Add(long C[], long A[], long B[]){

	push	ebp
	mov	ebp, esp
	sub	esp, 204				; 000000ccH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-12]
	mov	ecx, 3
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __BD7CEEEE_sub_P_OPT1@c
	call	@__CheckForDebuggerJustMyCode@4

; 6    : 	int i;
; 7    : 	for (i=0;i<N;i++){

	mov	DWORD PTR _i$[ebp], 0
	jmp	SHORT $LN4@Feld_Add
$LN2@Feld_Add:
	mov	eax, DWORD PTR _i$[ebp]
	add	eax, 1
	mov	DWORD PTR _i$[ebp], eax
$LN4@Feld_Add:
	cmp	DWORD PTR _i$[ebp], 20			; 00000014H
	jge	$LN1@Feld_Add

; 8    : 		C[i++]=A[i]+B[i];

	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _A$[ebp]
	mov	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _B$[ebp]
	add	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _C$[ebp]
	mov	DWORD PTR [ecx+eax*4], edx
	mov	edx, DWORD PTR _i$[ebp]
	add	edx, 1
	mov	DWORD PTR _i$[ebp], edx

; 9    : 		C[i++]=A[i]+B[i];

	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _A$[ebp]
	mov	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _B$[ebp]
	add	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _C$[ebp]
	mov	DWORD PTR [ecx+eax*4], edx
	mov	edx, DWORD PTR _i$[ebp]
	add	edx, 1
	mov	DWORD PTR _i$[ebp], edx

; 10   : 		C[i++]=A[i]+B[i];

	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _A$[ebp]
	mov	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _B$[ebp]
	add	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _C$[ebp]
	mov	DWORD PTR [ecx+eax*4], edx
	mov	edx, DWORD PTR _i$[ebp]
	add	edx, 1
	mov	DWORD PTR _i$[ebp], edx

; 11   : 		C[i]  =A[i]+B[i];

	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _A$[ebp]
	mov	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _B$[ebp]
	add	edx, DWORD PTR [ecx+eax*4]
	mov	eax, DWORD PTR _i$[ebp]
	mov	ecx, DWORD PTR _C$[ebp]
	mov	DWORD PTR [ecx+eax*4], edx

; 12   : 	}

	jmp	$LN2@Feld_Add
$LN1@Feld_Add:

; 13   : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 204				; 000000ccH
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_Feld_Add ENDP
_TEXT	ENDS
END
