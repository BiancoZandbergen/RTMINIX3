.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .cmf8
.sect .text
.cmf8:
push ebp
mov ebp,esp
sub	esp,28
push esi
push edi
mov edi,12(ebp)
mov esi,20(ebp)
test edi,edi
jns I1_4
mov eax,-1
jmp I1_5
I1_4:
mov eax,1
I1_5:
mov -12(ebp),eax
test esi,esi
jns I1_7
mov eax,-1
jmp I1_8
I1_7:
mov eax,1
I1_8:
mov -16(ebp),eax
cmp -12(ebp),eax
je I1_10
and edi,2147483647
and esi,2147483647
test edi,edi
jne I1_12
test esi,esi
je I1_10
I1_12:
! kill cc
cmp -12(ebp),0
jle I1_17
mov eax,-1
jmp I1_1
I1_17:
mov eax,1
jmp I1_1
I1_10:
cmp edi,esi
je I1_20
cmp edi,esi
jge I1_23
mov eax,1
jmp I1_24
I1_23:
mov eax,-1
I1_24:
mov -20(ebp),eax
jmp I1_21
I1_20:
mov edx,8(ebp)
mov -24(ebp),edx
mov edx,16(ebp)
mov -28(ebp),edx
cmp -24(ebp),edx
jne I1_26
xor eax,eax
jmp I1_1
I1_26:
mov edx,-28(ebp)
cmp -24(ebp),edx
jae I1_29
mov -20(ebp),1
jmp I1_21
I1_29:
mov -20(ebp),-1
I1_21:
mov edx,-12(ebp)
imul edx,-20(ebp)
mov eax,edx
I1_1:
pop edi
pop esi
leave
ret
