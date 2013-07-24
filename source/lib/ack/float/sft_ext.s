.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .sft_ext
.sect .text
.sft_ext:
push ebp
mov ebp,esp
push esi
push edi
mov edx,8(ebp)
! kill edx
movsx eax,2(edx)
mov edx,12(ebp)
! kill edx
movsx ebx,2(edx)
sub ebx,eax
neg ebx
mov edi,ebx
test edi,edi
je I1_1
test edi,edi
jns I1_7
neg edi
mov esi,8(ebp)
jmp I1_8
I1_7:
mov esi,12(ebp)
I1_8:
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
