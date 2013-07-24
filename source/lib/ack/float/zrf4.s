.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .zrf4
.sect .text
.zrf4:
push ebp
mov ebp,esp
mov eax,8(ebp)
mov (eax),0
! kill eax
leave
ret
