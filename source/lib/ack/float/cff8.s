.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .cff8
.sect .text
.cff8:
push ebp
mov ebp,esp
sub	esp,12
push 4
lea eax,-12(ebp)
push eax
lea eax,8(ebp)
push eax
call .extend
add esp,12
push 8
lea eax,8(ebp)
push eax
lea eax,-12(ebp)
push eax
call .compact
add esp,12
leave
ret
