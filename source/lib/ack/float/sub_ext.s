.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .sub_ext
.sect .text
.sub_ext:
push ebp
mov ebp,esp
push esi
push edi
mov esi,8(ebp)
mov edi,12(ebp)
mov edx,8(edi)
or edx,4(edi)
je I1_1
mov edx,8(esi)
or edx,4(esi)
jne I1_7
push edi
push esi
mov ecx,3
call .blm
movzx edx,(edi)
test edx,edx
je I1_10
xor eax,eax
jmp I1_11
I1_10:
mov eax,1
I1_11:
o16 mov (esi),eax
jmp I1_1
I1_7:
push edi
push esi
call .sft_ext
pop ecx
pop ecx
movsx eax,(esi)
movsx ebx,(edi)
cmp eax,ebx
je I1_13
lea eax,4(edi)
push eax
lea eax,4(esi)
push eax
call .b64_add
pop ecx
pop ecx
test eax,eax
je I1_14
lea eax,4(esi)
push eax
call .b64_rsft
pop ecx
or 4(esi),-2147483648
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
jmp I1_14
I1_13:
mov edx,4(esi)
cmp 4(edi),edx
ja I1_18
cmp 4(edi),edx
jne I1_19
mov edx,8(esi)
cmp 8(edi),edx
jbe I1_19
I1_18:
mov edx,8(edi)
cmp 8(esi),edx
jbe I1_24
mov edx,4(edi)
sub edx,1
mov 4(edi),edx
I1_24:
mov edx,4(edi)
sub edx,4(esi)
mov 4(edi),edx
mov edx,8(edi)
sub edx,8(esi)
mov 8(edi),edx
push edi
push esi
mov ecx,3
call .blm
movzx edx,(edi)
test edx,edx
je I1_27
xor eax,eax
jmp I1_28
I1_27:
mov eax,1
I1_28:
o16 mov (esi),eax
jmp I1_14
I1_19:
mov edx,8(esi)
cmp 8(edi),edx
jbe I1_30
mov edx,4(esi)
sub edx,1
mov 4(esi),edx
I1_30:
mov edx,4(esi)
sub edx,4(edi)
mov 4(esi),edx
mov edx,8(esi)
sub edx,8(edi)
mov 8(esi),edx
I1_14:
push esi
call .nrm_ext
pop ecx
I1_1:
pop edi
pop esi
leave
ret
