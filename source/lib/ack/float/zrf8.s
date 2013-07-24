.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .zrf8
.sect .text
.zrf8:
push ebp
mov ebp,esp
mov eax,8(ebp)
mov (eax),0
! kill eax
mov edx,8(ebp)
mov 4(edx),0
leave
ret
