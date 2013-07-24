.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .b64_sft
.sect .text
.b64_sft:
push ebp
mov ebp,esp
push esi
push edi
mov esi,8(ebp)
mov edi,12(ebp)
! kill cc
test edi,edi
jle I1_4
cmp edi,63
jle I1_7
mov 4(esi),0
mov (esi),0
jmp I1_1
I1_7:
cmp edi,32
jl I1_10
mov edx,(esi)
mov 4(esi),edx
mov (esi),0
sub edi,32
I1_10:
! kill cc
test edi,edi
jle I1_1
mov ecx,edi
mov edx,4(esi)
shr edx,cl
mov 4(esi),edx
cmp (esi),0
je I1_1
mov edx,32
sub edx,edi
mov ecx,edx
mov edx,(esi)
sal edx,cl
or 4(esi),edx
mov ecx,edi
mov edx,(esi)
shr edx,cl
mov (esi),edx
jmp I1_1
I1_4:
neg edi
! kill cc
test edi,edi
jle I1_1
cmp edi,63
jle I1_22
mov 4(esi),0
mov (esi),0
jmp I1_1
I1_22:
cmp edi,32
jl I1_25
mov edx,4(esi)
mov (esi),edx
mov 4(esi),0
sub edi,32
I1_25:
! kill cc
test edi,edi
jle I1_1
mov ecx,edi
mov edx,(esi)
sal edx,cl
mov (esi),edx
cmp 4(esi),0
je I1_1
mov edx,32
sub edx,edi
mov ecx,edx
mov edx,4(esi)
shr edx,cl
or (esi),edx
mov ecx,edi
mov edx,4(esi)
sal edx,cl
mov 4(esi),edx
I1_1:
pop edi
pop esi
leave
ret
.extern .b64_lsft
.b64_lsft:
push ebp
mov ebp,esp
push esi
mov esi,8(ebp)
sal (esi),1
test 4(esi),-2147483648
je I2_4
or (esi),1
I2_4:
mov edx,4(esi)
sal edx,1
mov 4(esi),edx
pop esi
leave
ret
.extern .b64_rsft
.b64_rsft:
push ebp
mov ebp,esp
push esi
mov esi,8(ebp)
mov edx,4(esi)
shr edx,1
mov 4(esi),edx
mov edx,(esi)
testb dl,1
je I3_4
or 4(esi),-2147483648
I3_4:
shr (esi),1
pop esi
leave
ret
