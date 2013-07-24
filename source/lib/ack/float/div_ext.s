.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .div_ext
.sect .text
.div_ext:
push ebp
mov ebp,esp
sub	esp,20
push esi
push edi
mov esi,8(ebp)
o16 mov -2(ebp),0
mov edx,12(ebp)
mov ecx,12(ebp)
mov ecx,8(ecx)
or ecx,4(edx)
jne I1_4
push 7
call __fptrp
pop ecx
xor edx,edx
mov 8(esi),edx
mov 4(esi),edx
o16 mov 2(esi),16383
jmp I1_1
I1_4:
mov edx,8(esi)
or edx,4(esi)
jne I1_7
o16 mov 2(esi),0
jmp I1_1
I1_7:
lea eax,4(esi)
push eax
call .b64_rsft
pop ecx
mov edx,12(ebp)
! kill edx
add edx,4
push edx
call .b64_rsft
pop ecx
movsx eax,2(esi)
inc eax
movsx eax,eax
o16 mov 2(esi),eax
mov edx,12(ebp)
! kill edx
movsx ebx,2(edx)
inc ebx
mov eax,ebx
movsx eax,eax
mov edx,12(ebp)
! kill edx
o16 mov 2(edx),eax
mov edx,12(ebp)
movsx eax,(edx)
movsx ebx,(esi)
xor ebx,eax
o16 mov (esi),ebx
movsx eax,2(esi)
mov edx,12(ebp)
! kill edx
movsx ecx,2(edx)
sub ecx,eax
neg ecx
mov eax,ecx
movsx eax,eax
o16 mov 2(esi),eax
o16 mov -18(ebp),64
mov -12(ebp),0
mov -8(ebp),0
I1_10:
movzx edx,-18(ebp)
mov eax,edx
movsx eax,eax
dec eax
o16 mov -18(ebp),eax
mov eax,edx
movsx eax,eax
test eax,eax
je I1_9
lea eax,-12(ebp)
push eax
call .b64_lsft
pop ecx
mov edx,12(ebp)
mov edx,4(edx)
cmp 4(esi),edx
jb I1_14
mov edx,12(ebp)
mov edx,4(edx)
cmp 4(esi),edx
jne I1_13
mov edx,12(ebp)
mov edx,8(edx)
cmp 8(esi),edx
jb I1_14
I1_13:
inc -8(ebp)
mov edx,12(ebp)
mov ecx,8(esi)
cmp 8(edx),ecx
jbe I1_18
mov edx,4(esi)
sub edx,1
mov 4(esi),edx
I1_18:
mov edx,12(ebp)
mov ecx,4(esi)
sub ecx,4(edx)
mov 4(esi),ecx
mov edx,12(ebp)
mov ecx,8(esi)
sub ecx,8(edx)
mov 8(esi),ecx
I1_14:
mov edi,esi
add edi,4
mov edx,(edi)
or edx,4(edi)
je I1_21
mov eax,1
jmp I1_22
I1_21:
xor eax,eax
I1_22:
o16 mov -2(ebp),eax
movzx edx,-2(ebp)
test edx,edx
je I1_9
lea eax,4(esi)
push eax
call .b64_lsft
pop ecx
jmp I1_10
I1_9:
movsx eax,-18(ebp)
! kill cc
test eax,eax
jle I1_27
lea edi,-12(ebp)
movsx eax,-18(ebp)
cmp eax,31
jle I1_30
mov edx,4(edi)
mov (edi),edx
movsx eax,-18(ebp)
sub eax,32
o16 mov -18(ebp),eax
mov 4(edi),0
I1_30:
cmp (edi),0
je I1_33
movsx eax,-18(ebp)
mov ecx,eax
mov edx,(edi)
sal edx,cl
mov (edi),edx
I1_33:
add edi,4
cmp (edi),0
je I1_27
movsx eax,-18(ebp)
sub eax,32
neg eax
mov ecx,eax
mov edx,(edi)
shr edx,cl
or -12(ebp),edx
movsx eax,-18(ebp)
mov ecx,eax
mov edx,(edi)
sal edx,cl
mov (edi),edx
I1_27:
lea eax,-12(ebp)
push eax
lea eax,4(esi)
push eax
mov ecx,2
call .blm
push esi
call .nrm_ext
pop ecx
movsx eax,2(esi)
cmp eax,-16382
jge I1_39
push 5
call __fptrp
pop ecx
o16 mov 2(esi),-16382
xor edx,edx
mov 8(esi),edx
mov 4(esi),edx
jmp I1_1
I1_39:
movsx eax,2(esi)
cmp eax,16383
jl I1_1
push 4
call __fptrp
pop ecx
o16 mov 2(esi),16383
xor edx,edx
mov 8(esi),edx
mov 4(esi),edx
I1_1:
pop edi
pop esi
leave
ret
