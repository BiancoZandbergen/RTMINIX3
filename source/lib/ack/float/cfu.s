.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .cfu
.sect .text
.cfu:
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
dec edx
o16 mov -20(ebp),edx
movsx eax,-10(ebp)
movsx ebx,-20(ebp)
cmp eax,ebx
jle I1_7
push 3
call __fptrp
pop ecx
movsx eax,-10(ebp)
movsx ebx,-20(ebp)
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
