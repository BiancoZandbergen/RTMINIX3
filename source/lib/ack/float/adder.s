.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .b64_add
.sect .text
.b64_add:
push ebp
mov ebp,esp
sub	esp,8
push esi
push edi
mov esi,8(ebp)
mov edi,12(ebp)
mov edx,-1
sub edx,(esi)
xor eax,eax
cmp (edi),edx
jbe 1f
inc eax
1:
mov -4(ebp),eax
mov edx,(edi)
add (esi),edx
mov edx,-1
sub edx,4(esi)
xor eax,eax
cmp 4(edi),edx
jbe 1f
inc eax
1:
mov -8(ebp),eax
mov edx,4(edi)
add 4(esi),edx
cmp -8(ebp),0
je I1_4
mov edx,(esi)
inc edx
mov (esi),edx
jne I1_4
mov eax,1
jmp I1_1
I1_4:
mov eax,-4(ebp)
I1_1:
pop edi
pop esi
leave
ret
