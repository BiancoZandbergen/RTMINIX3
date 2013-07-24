.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .add_ext
.sect .text
.add_ext:
push ebp
mov ebp,esp
sub	esp,12
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
je I1_10
mov edx,4(esi)
cmp 4(edi),edx
ja I1_12
cmp 4(edi),edx
jne I1_13
mov edx,8(esi)
cmp 8(edi),edx
jbe I1_13
I1_12:
push esi
lea eax,-12(ebp)
push eax
mov ecx,3
call .blm
push edi
push esi
mov ecx,3
call .blm
mov edx,-4(ebp)
cmp 8(esi),edx
jae I1_18
mov edx,4(esi)
sub edx,1
mov 4(esi),edx
I1_18:
mov edx,4(esi)
sub edx,-8(ebp)
mov 4(esi),edx
mov edx,8(esi)
sub edx,-4(ebp)
mov 8(esi),edx
jmp I1_11
I1_13:
mov edx,8(esi)
cmp 8(edi),edx
jbe I1_21
mov edx,4(esi)
sub edx,1
mov 4(esi),edx
I1_21:
mov edx,4(esi)
sub edx,4(edi)
mov 4(esi),edx
mov edx,8(esi)
sub edx,8(edi)
mov 8(esi),edx
jmp I1_11
I1_10:
lea eax,4(edi)
push eax
lea eax,4(esi)
push eax
call .b64_add
pop ecx
pop ecx
test eax,eax
je I1_11
lea eax,4(esi)
push eax
call .b64_rsft
pop ecx
or 4(esi),-2147483648
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_11:
push esi
call .nrm_ext
pop ecx
I1_1:
pop edi
pop esi
leave
ret
