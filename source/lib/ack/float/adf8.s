.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .adf8
.sect .text
.adf8:
push ebp
mov ebp,esp
sub	esp,24
cmp 16(ebp),0
jne I1_4
cmp 20(ebp),0
jne I1_4
mov edx,8(ebp)
mov ecx,12(ebp)
mov 16(ebp),edx
mov 20(ebp),ecx
jmp I1_1
I1_4:
cmp 8(ebp),0
jne I1_8
cmp 12(ebp),0
je I1_1
I1_8:
push 8
lea eax,-12(ebp)
push eax
lea eax,16(ebp)
push eax
call .extend
add esp,12
push 8
lea eax,-24(ebp)
push eax
lea eax,8(ebp)
push eax
call .extend
add esp,12
lea eax,-24(ebp)
push eax
lea eax,-12(ebp)
push eax
call .add_ext
pop ecx
pop ecx
push 8
lea eax,16(ebp)
push eax
lea eax,-12(ebp)
push eax
call .compact
add esp,12
I1_1:
leave
ret
