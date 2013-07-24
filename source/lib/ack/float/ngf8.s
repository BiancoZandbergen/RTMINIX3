.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .ngf8
.sect .text
.ngf8:
push ebp
mov ebp,esp
push esi
cmp 8(ebp),0
jne I1_3
cmp 12(ebp),0
je I1_1
I1_3:
lea esi,15(ebp)
movzxb edx,(esi)
xor edx,128
movb (esi),dl
I1_1:
pop esi
leave
ret
