.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .zrf_ext
.sect .text
.zrf_ext:
push ebp
mov ebp,esp
push esi
mov esi,8(ebp)
mov 4(esi),0
mov 8(esi),0
o16 mov 2(esi),0
o16 mov (esi),0
pop esi
leave
ret
