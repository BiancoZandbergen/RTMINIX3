.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .nrm_ext
.sect .text
.nrm_ext:
push ebp
mov ebp,esp
sub	esp,4
push esi
push edi
mov esi,8(ebp)
mov edx,8(esi)
or edx,4(esi)
je I1_1
cmp 4(esi),0
jne I1_7
mov edx,8(esi)
mov 4(esi),edx
mov 8(esi),0
movsx eax,2(esi)
sub eax,32
movsx eax,eax
o16 mov 2(esi),eax
I1_7:
test 4(esi),-2147483648
jne I1_1
mov -4(ebp),1073741824
mov edi,-1
I1_13:
mov edx,-4(ebp)
test 4(esi),edx
jne I1_12
shr -4(ebp),1
dec edi
jmp I1_13
I1_12:
movsx eax,2(esi)
add eax,edi
movsx eax,eax
o16 mov 2(esi),eax
push edi
lea eax,4(esi)
push eax
call .b64_sft
pop ecx
pop ecx
I1_1:
pop edi
pop esi
leave
ret
