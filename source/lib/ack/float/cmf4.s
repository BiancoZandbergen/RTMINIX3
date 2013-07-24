.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .cmf4
.sect .text
.cmf4:
push ebp
mov ebp,esp
sub	esp,8
push esi
push edi
mov edi,8(ebp)
mov esi,12(ebp)
cmp edi,esi
jne I1_4
xor eax,eax
jmp I1_1
I1_4:
test edi,edi
jns I1_7
mov eax,-1
jmp I1_8
I1_7:
mov eax,1
I1_8:
mov -4(ebp),eax
test esi,esi
jns I1_10
mov eax,-1
jmp I1_11
I1_10:
mov eax,1
I1_11:
mov -8(ebp),eax
cmp -4(ebp),eax
je I1_13
test edi,2147483647
jne I1_16
test esi,2147483647
jne I1_16
xor eax,eax
jmp I1_1
I1_16:
! kill cc
cmp -4(ebp),0
jle I1_20
mov eax,-1
jmp I1_1
I1_20:
mov eax,1
jmp I1_1
I1_13:
cmp edi,esi
jge I1_23
mov eax,1
jmp I1_24
I1_23:
mov eax,-1
I1_24:
imul eax,-4(ebp)
I1_1:
pop edi
pop esi
leave
ret
