.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .extend
.sect .text
.extend:
push ebp
mov ebp,esp
sub	esp,12
push esi
push edi
mov esi,12(ebp)
mov -12(ebp),0
mov edi,8(ebp)
push edi
cmp 16(ebp),8
jne I1_4
mov eax,6
jmp I1_5
I1_4:
mov eax,2
I1_5:
pop edx
add edx,eax
movsx eax,(edx)
o16 mov 2(esi),eax
movsx ebx,2(esi)
and ebx,32768
o16 mov (esi),ebx
movsx eax,(esi)
movsx ecx,2(esi)
xor ecx,eax
mov eax,ecx
movsx eax,eax
o16 mov 2(esi),eax
cmp 16(ebp),8
jne I1_7
movsx ebx,2(esi)
sar ebx,4
mov eax,ebx
movsx eax,eax
o16 mov 2(esi),eax
jmp I1_8
I1_7:
movsx eax,2(esi)
sar eax,7
movsx eax,eax
o16 mov 2(esi),eax
I1_8:
movsx eax,2(esi)
! kill cc
test eax,eax
jle I1_10
inc -12(ebp)
jmp I1_11
I1_10:
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_11:
cmp 16(ebp),8
jne I1_13
mov edx,(edi)
mov -8(ebp),edx
add edi,4
mov edx,(edi)
mov 4(esi),edx
movsx eax,2(esi)
cmp eax,1
jne I1_16
cmp 4(esi),0
jne I1_16
cmp -8(ebp),0
jne I1_16
o16 mov 2(esi),0
o16 mov (esi),0
mov 4(esi),0
mov 8(esi),0
jmp I1_1
I1_16:
mov edx,4(esi)
sal edx,11
mov 4(esi),edx
movsx eax,2(esi)
sub eax,1023
movsx eax,eax
o16 mov 2(esi),eax
mov edx,-8(ebp)
shr edx,21
or 4(esi),edx
mov edx,-8(ebp)
sal edx,11
mov 8(esi),edx
jmp I1_14
I1_13:
mov edx,(edi)
mov 4(esi),edx
sal edx,8
mov 4(esi),edx
movsx eax,2(esi)
cmp eax,1
jne I1_21
cmp 4(esi),0
jne I1_21
o16 mov 2(esi),0
o16 mov (esi),0
mov 4(esi),0
mov 8(esi),0
jmp I1_1
I1_21:
movsx eax,2(esi)
sub eax,127
movsx eax,eax
o16 mov 2(esi),eax
mov 8(esi),0
I1_14:
or 4(esi),-2147483648
cmp -12(ebp),0
jne I1_1
and 4(esi),2147483647
push esi
call .nrm_ext
pop ecx
I1_1:
pop edi
pop esi
leave
ret
