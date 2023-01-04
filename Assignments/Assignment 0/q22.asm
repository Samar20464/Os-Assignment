bits 64
default rel
global main

extern printf
extern scanf

section .data
 	type db "%s",0
	type2 db "%s",0
	line db 10,0
section .bss
	input resb 2048
	input2 resb 2048
	output resb 2048
	output2 resb 2048
section .text
main:
	sub rsp, 8

	lea rdi, [type]
	lea rsi, [input]
	mov rax, 0
	call scanf wrt ..plt

	lea rdi, [type2]
	lea rsi, [input2]
	mov rax, 0
	call scanf wrt ..plt

	mov rdi, output
	mov rsi, input
	mov rcx, 2048
	cld
	rep movsb

	mov rdi, output2
	mov rsi , input2
	mov rcx, 2048
	cld
	rep movsb

	lea rdi, [type]
	lea rsi, [output]
	mov rax,0
	call printf wrt ..plt

	lea rdi, [line]
	mov rax ,1
	call printf wrt ..plt

	lea rdi, [type2]
	lea rsi, [output2]
	mov rax, 0
	call printf wrt ..plt

	lea rdi, [line]
	mov rax,1
	call printf wrt ..plt

	add rsp,8
	xor eax,eax
	ret
