.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .mlf8
.sect .text
.mlf8:
push ebp
mov ebp,esp
sub	esp,24
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
call .mul_ext
pop ecx
pop ecx
push 8
lea eax,16(ebp)
push eax
lea eax,-12(ebp)
push eax
call .compact
add esp,12
leave
ret
