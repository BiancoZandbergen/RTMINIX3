.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .dvf4
.sect .text
.dvf4:
push ebp
mov ebp,esp
sub	esp,24
push 4
lea eax,-12(ebp)
push eax
lea eax,12(ebp)
push eax
call .extend
add esp,12
push 4
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
call .div_ext
pop ecx
pop ecx
push 4
lea eax,12(ebp)
push eax
lea eax,-12(ebp)
push eax
call .compact
add esp,12
leave
ret
