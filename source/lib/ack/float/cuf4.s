.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .cuf4
.sect .text
.cuf4:
push ebp
mov ebp,esp
sub	esp,16
push esi
push edi
lea eax,-12(ebp)
push eax
call .zrf_ext
pop ecx
cmp 8(ebp),4
jne I1_4
o16 mov -10(ebp),31
mov esi,12(ebp)
lea edi,12(ebp)
jmp I1_5
I1_4:
lea edx,12(ebp)
mov -16(ebp),edx
movsx eax,(edx)
mov esi,eax
o16 mov -10(ebp),15
lea edi,8(ebp)
I1_5:
test esi,esi
jne I1_7
mov (edi),0
jmp I1_1
I1_7:
cmp 8(ebp),4
je I1_10
sal esi,16
I1_10:
mov -8(ebp),esi
lea eax,-12(ebp)
push eax
call .nrm_ext
pop ecx
push 4
push edi
lea eax,-12(ebp)
push eax
call .compact
add esp,12
I1_1:
pop edi
pop esi
leave
ret
