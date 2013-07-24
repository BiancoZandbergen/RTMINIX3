.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .mul_ext
.sect .text
.mul_ext:
push ebp
mov ebp,esp
sub	esp,60
push esi
push edi
mov esi,8(ebp)
mov edx,12(ebp)
movsx eax,(edx)
movsx ebx,(esi)
xor ebx,eax
o16 mov (esi),ebx
mov edx,12(ebp)
! kill edx
movsx eax,2(edx)
inc eax
movsx ecx,2(esi)
add ecx,eax
mov eax,ecx
movsx eax,eax
o16 mov 2(esi),eax
mov edx,4(esi)
shr edx,16
and edx,65535
o16 mov -16(ebp),edx
mov edx,65535
and edx,4(esi)
o16 mov -14(ebp),edx
mov edx,8(esi)
shr edx,16
and edx,65535
o16 mov -12(ebp),edx
mov edx,65535
and edx,8(esi)
o16 mov -10(ebp),edx
mov edx,12(ebp)
mov edx,4(edx)
shr edx,16
and edx,65535
o16 mov -24(ebp),edx
mov edx,12(ebp)
mov ecx,65535
and ecx,4(edx)
o16 mov -22(ebp),ecx
mov edx,8(edx)
shr edx,16
and edx,65535
o16 mov -20(ebp),edx
mov edx,12(ebp)
mov ecx,65535
and ecx,8(edx)
o16 mov -18(ebp),ecx
mov edi,8
I1_6:
mov edx,edi
dec edx
push edi
mov edi,edx
pop edx
test edx,edx
je I1_3
o16 mov -40(ebp)(edi*2),0
jmp I1_6
I1_3:
mov edi,4
lea edx,-32(ebp)
mov -44(ebp),edx
I1_10:
mov edx,edi
dec edx
push edi
mov edi,edx
pop edx
test edx,edx
je I1_7
movzx edx,-16(ebp)(edi*2)
test edx,edx
je I1_8
o16 mov -46(ebp),0
movzx edx,-16(ebp)(edi*2)
mov -52(ebp),edx
mov -8(ebp),4
I1_17:
mov edx,-8(ebp)
mov ecx,edx
dec ecx
mov -8(ebp),ecx
test edx,edx
je I1_14
mov edx,-44(ebp)
movzx ebx,-46(ebp)
movzx eax,0(edx)(ecx*2)
add ebx,eax
mov -56(ebp),ebx
movzx edx,-24(ebp)(ecx*2)
test edx,edx
je I1_19
movzx edx,-24(ebp)(ecx*2)
imul edx,-52(ebp)
add -56(ebp),edx
I1_19:
mov edx,65535
and edx,-56(ebp)
mov ecx,-8(ebp)
mov ebx,-44(ebp)
o16 mov 0(ebx)(ecx*2),edx
mov edx,-56(ebp)
shr edx,16
and edx,65535
o16 mov -46(ebp),edx
jmp I1_17
I1_14:
mov edx,-44(ebp)
! kill edx
o16 mov cx,-46(ebp)
o16 mov -2(edx),cx
I1_8:
add -44(ebp),-2
jmp I1_10
I1_7:
movzx edx,-40(ebp)
test edx,32768
jne I1_22
movsx eax,2(esi)
dec eax
movsx eax,eax
o16 mov 2(esi),eax
xor edi,edi
I1_27:
cmp edi,3
jg I1_24
lea edx,-40(ebp)(edi*2)
mov -60(ebp),edx
movzx ecx,(edx)
sal ecx,1
and ecx,65535
o16 mov (edx),ecx
mov edx,edi
inc edx
movzx ecx,-40(ebp)(edx*2)
test ecx,32768
je I1_25
lea edx,-40(ebp)(edi*2)
mov -60(ebp),edx
movzx ecx,(edx)
or ecx,1
and ecx,65535
o16 mov (edx),ecx
I1_25:
inc edi
jmp I1_27
I1_24:
movzx edx,-32(ebp)
sal edx,1
and edx,65535
o16 mov -32(ebp),edx
I1_22:
movzx edx,-40(ebp)
sal edx,16
movzx ecx,-38(ebp)
add ecx,edx
mov 4(esi),ecx
movzx edx,-36(ebp)
sal edx,16
movzx ecx,-34(ebp)
add ecx,edx
mov 8(esi),ecx
movzx edx,-32(ebp)
test edx,32768
je I1_32
add 8(esi),1
jne I1_32
add 4(esi),1
jne I1_32
mov 4(esi),-2147483648
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_32:
movsx eax,2(esi)
cmp eax,16383
jl I1_41
push 4
call __fptrp
pop ecx
o16 mov 2(esi),16383
I1_43:
xor edx,edx
mov 8(esi),edx
mov 4(esi),edx
jmp I1_1
I1_41:
movsx eax,2(esi)
cmp eax,-16382
jge I1_1
push 5
call __fptrp
pop ecx
o16 mov 2(esi),-16382
jmp I1_43
I1_1:
pop edi
pop esi
leave
ret
