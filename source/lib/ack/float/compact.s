.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .compact
.sect .text
.compact:
push ebp
mov ebp,esp
sub	esp,16
push esi
push edi
mov esi,8(ebp)
mov -4(ebp),0
cmp 16(ebp),8
jne I1_4
mov edi,12(ebp)
mov edx,-768
and edx,8(esi)
or edx,4(esi)
jne I1_7
push edi
call .zrf8
pop ecx
jmp I1_1
I1_7:
movsx eax,2(esi)
add eax,1023
movsx eax,eax
o16 mov 2(esi),eax
movsx ebx,2(esi)
cmp ebx,2046
jle I1_10
I1_12:
push 4
call __fptrp
pop ecx
o16 mov 2(esi),2047
mov 4(esi),0
mov 8(esi),0
mov edx,-4(ebp)
mov ecx,edx
inc ecx
mov -4(ebp),ecx
test edx,edx
je I1_11
jmp I1_1
I1_10:
movsx eax,2(esi)
! kill cc
test eax,eax
jg I1_11
lea eax,4(esi)
push eax
call .b64_rsft
pop ecx
movsx eax,2(esi)
test eax,eax
jns I1_11
movsx eax,2(esi)
neg eax
push eax
lea eax,4(esi)
push eax
call .b64_sft
pop ecx
pop ecx
o16 mov 2(esi),0
I1_11:
mov edx,4(esi)
shr edx,11
mov (edi),edx
mov edx,8(esi)
shr edx,11
mov 4(edi),edx
lea edx,4(edi)
mov -12(ebp),edx
mov ecx,4(esi)
sal ecx,21
or ecx,(edx)
mov eax,-12(ebp)
mov (eax),ecx
! kill eax
mov edx,2047
and edx,8(esi)
cmp edx,1024
ja I1_22
mov edx,2047
and edx,8(esi)
cmp edx,1024
jne I1_23
test 8(esi),2048
je I1_23
I1_22:
lea edx,4(edi)
mov -12(ebp),edx
mov ecx,1
add ecx,(edx)
mov eax,-12(ebp)
mov (eax),ecx
! kill eax
cmp 4(edi),0
jne I1_28
mov -12(ebp),edi
mov edx,1
add edx,(edi)
mov eax,-12(ebp)
mov (eax),edx
! kill eax
movzx edx,2(esi)
test edx,edx
jne I1_31
test (edi),-1048576
je I1_31
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_31:
test (edi),2097152
je I1_28
mov edx,(edi)
testb dl,1
je I1_38
mov 4(edi),-2147483648
I1_38:
mov -12(ebp),edi
mov edx,(edi)
shr edx,1
mov eax,-12(ebp)
mov (eax),edx
! kill eax
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_28:
movsx eax,2(esi)
cmp eax,2046
jg I1_12
I1_23:
mov -12(ebp),edi
mov edx,1048575
and edx,(edi)
mov eax,-12(ebp)
mov (eax),edx
! kill eax
mov -12(ebp),edi
movsx eax,2(esi)
sal eax,4
sal eax,16
or eax,(edi)
mov ebx,-12(ebp)
mov (ebx),eax
! kill ebx
movzx edx,(esi)
test edx,edx
je I1_44
mov -12(ebp),edi
mov edx,-2147483648
or edx,(edi)
mov eax,-12(ebp)
mov (eax),edx
! kill eax
I1_44:
mov edx,4(edi)
mov -16(ebp),edx
mov edx,(edi)
mov 4(edi),edx
mov edx,-16(ebp)
mov (edi),edx
jmp I1_1
I1_4:
mov edi,12(ebp)
test 4(esi),-128
jne I1_47
mov (edi),0
jmp I1_1
I1_47:
movsx eax,2(esi)
add eax,127
movsx eax,eax
o16 mov 2(esi),eax
movsx ebx,2(esi)
cmp ebx,254
jle I1_50
I1_52:
push 4
call __fptrp
pop ecx
o16 mov 2(esi),255
mov 4(esi),0
mov 8(esi),0
mov edx,-4(ebp)
mov ecx,edx
inc ecx
mov -4(ebp),ecx
test edx,edx
je I1_51
jmp I1_1
I1_50:
movsx eax,2(esi)
! kill cc
test eax,eax
jg I1_51
lea eax,4(esi)
push eax
call .b64_rsft
pop ecx
movsx eax,2(esi)
test eax,eax
jns I1_51
movsx eax,2(esi)
neg eax
push eax
lea eax,4(esi)
push eax
call .b64_sft
pop ecx
pop ecx
o16 mov 2(esi),0
I1_51:
mov edx,4(esi)
shr edx,8
mov (edi),edx
mov edx,4(esi)
movzxb ecx,dl
cmp ecx,128
ja I1_62
cmpb dl,128
jne I1_63
test 4(esi),256
je I1_63
I1_62:
inc (edi)
movzx edx,2(esi)
test edx,edx
jne I1_68
test (edi),-8388608
je I1_68
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_68:
test (edi),16777216
je I1_72
shr (edi),1
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
I1_72:
movsx eax,2(esi)
cmp eax,254
jg I1_52
I1_63:
and (edi),8388607
movsx eax,2(esi)
sal eax,7
sal eax,16
or (edi),eax
movzx edx,(esi)
test edx,edx
je I1_78
or (edi),-2147483648
I1_78:
mov edi,(edi)
I1_1:
pop edi
pop esi
leave
ret
