.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .cfi
.sect .text
.cfi:
push ebp
mov ebp,esp
sub	esp,20
push esi
push 12(ebp)
lea eax,-12(ebp)
push eax
lea eax,16(ebp)
push eax
call .extend
add esp,12
movsx eax,-10(ebp)
test eax,eax
jns I1_4
xor eax,eax
cmp 12(ebp),8
jne 1f
inc eax
1:
mov 16(ebp)(eax*4),0
xor eax,eax
jmp I1_1
I1_4:
mov edx,8(ebp)
sal edx,3
sub edx,2
o16 mov -18(ebp),edx
movsx eax,-10(ebp)
movsx ebx,-18(ebp)
cmp eax,ebx
jle I1_7
movsx eax,-18(ebp)
inc eax
movsx ebx,-10(ebp)
cmp eax,ebx
jne I1_10
movzx edx,-12(ebp)
test edx,edx
je I1_10
cmp -8(ebp),-2147483648
jne I1_10
cmp -4(ebp),0
je I1_7
I1_10:
push 3
call __fptrp
pop ecx
movsx eax,-10(ebp)
movsx ebx,-18(ebp)
cdq
idiv ebx
o16 mov -10(ebp),edx
I1_7:
movsx eax,-10(ebp)
sub eax,31
neg eax
mov ecx,eax
mov edx,-8(ebp)
shr edx,cl
mov esi,edx
movzx edx,-12(ebp)
test edx,edx
je I1_18
neg esi
I1_18:
xor eax,eax
cmp 12(ebp),8
jne 1f
inc eax
1:
mov 16(ebp)(eax*4),esi
mov eax,esi
I1_1:
pop esi
leave
ret
