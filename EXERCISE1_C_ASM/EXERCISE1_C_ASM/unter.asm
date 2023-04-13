;unter.asm

	.686P
	.model flat
	.data
	.code

public c ASM_Addition
ASM_Addition proc c A:DWORD, B:DWORD
	mov eax,A
	add	eax,B
	ret
ASM_Addition endp


	end