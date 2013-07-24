.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .fef8
.sect .text
.fef8:
push ebp
mov ebp,esp
sub	esp,12
push esi
mov esi,8(ebp)
push 8
lea eax,-12(ebp)
push eax
lea eax,12(ebp)
push eax
call .extend
add esp,12
movzx edx,-10(ebp)
test edx,edx
jne I1_4
cmp -8(ebp),0
jne I1_4
cmp -4(ebp),0
jne I1_4
mov (esi),0
jmp I1_5
I1_4:
movsx eax,-10(ebp)
inc eax
mov (esi),eax
o16 mov -10(ebp),-1
I1_5:
push 8
lea eax,4(esi)
push eax
lea eax,-12(ebp)
push eax
call .compact
add esp,12
pop esi
leave
ret
