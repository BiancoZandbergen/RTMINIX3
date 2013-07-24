.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .ngf4
.sect .text
.ngf4:
push ebp
mov ebp,esp
push esi
cmp 8(ebp),0
je I1_1
lea esi,11(ebp)
movzxb edx,(esi)
xor edx,128
movb (esi),dl
I1_1:
pop esi
leave
ret
