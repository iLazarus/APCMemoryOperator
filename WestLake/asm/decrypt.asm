.CODE

decrypt_uworld PROC
	cmp rcx, 0h
	jz exit
	PUSH RBP
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov eax,ecx
	not eax
	shr rcx,20h
	add eax,29128A8Fh
	not ecx
	not eax
	sub ecx,654C2A88h
	add eax,0D6D3963h
	not ecx
	not eax
	sub ecx,737D73BDh
	sub eax,47ED7571h
	not ecx
	xor eax,0F292C69Ch
	add ecx,29B3D578h
	xor ecx,8C828C42h
	mov [rsp],eax
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;	
	MOV RSP, RBP
	POP RBP
	RET
decrypt_uworld ENDP


decrypt_gameinst PROC
	cmp rcx, 0h
	jz exit
    PUSH RBP
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax,ecx
	shr rcx,20h
	not eax
	rol ecx,08h
	add eax,01E1DD2Fh
	not ecx
	xor eax,0FE1E22D0h
	sub ecx,7F317F71h
	mov [rsp],eax
	rol ecx,08h
	xor ecx,80CE808Eh
	mov [rsp + 4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
    POP RBP
    RET
decrypt_gameinst ENDP

decrypt_level PROC
	cmp rcx, 0h
	jz exit
    PUSH RBP
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	mov rcx,rdx
	mov r8,rdx
	shr rcx,20h
	shr r8,20h
	mov eax,edx
	and edx,0EAEAEAEAh
	and ecx,0EAEAEAEAh
	and eax,15151515h
	and r8d,15151515h
	xor edx,eax
	xor ecx,r8d
	sub edx,147420DBh
	add ecx,6A046A45h
	xor edx,0EB8BDF25h
	xor ecx,95FB95BBh
	mov [rsp],edx
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
    POP RBP
    RET
decrypt_level ENDP

decrypt_actors PROC
	cmp rcx, 0h
	jz exit
    PUSH RBP
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rax,rcx
	mov rcx,rax
	shr rcx,20h
	not eax
	add eax,09128A8Fh
	not ecx
	not eax
	add ecx,7AB3D578h
	add eax,6DCD1903h
	not ecx
	not eax
	sub ecx,13DD131Dh
	sub eax,67ED7571h
	not ecx
	xor eax,9232E6FCh
	add ecx,09B3D578h
	xor ecx,0EC22ECE2h
	mov [rsp],eax
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
    POP RBP
    RET
decrypt_actors ENDP

decrypt_local PROC
	cmp rcx, 0h
	jz exit
    PUSH RBP
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov r10, rcx
	mov ecx,r10d
	shr ecx,10h
	mov r8,r10
	movzx eax,cx
	shr r8,20h
	rol ax,08h
	movzx edx,ax
	shl edx,10h
	movzx eax,r10w
	xor ecx,eax
	or edx,ecx
	add edx,13B3677Dh
	movzx eax,dx
	mov ecx,edx
	shr ecx,10h
	and edx,0FFFF0000h
	xor ecx,eax
	mov eax,r8d
	or ecx,edx
	shr eax,10h
	xor ax,r8w
	xor ecx,13B3677Dh
	ror ax,08h
	and r8d,0FFFF0000h
	mov [rsp],ecx
	movzx ecx,ax
	or ecx,r8d
	add ecx,925C929Dh
	mov edx,ecx
	shr edx,10h
	movzx eax,dx
	xor dx,cx
	rol ax,08h
	movzx r8d,ax
	ror dx,08h
	shl r8d,10h
	movzx eax,dx
	or r8d,eax
	xor r8d,6DA36D63h
	mov [rsp+4h],r8d
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
    POP RBP
    RET
decrypt_local ENDP

decrypt_controller PROC
	cmp rcx, 0h
	jz exit
    PUSH RBP
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rax,rcx
	mov ecx,eax
	ror ecx,08h
	add ecx,07270B49h
	shr rax,20h
	ror ecx,08h
	sub eax,79577917h
	xor ecx,07270B49h
	xor eax,79577917h
	mov [rsp],ecx
	mov [rsp+4h],eax
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
    POP RBP
    RET
decrypt_controller ENDP


decrypt_property PROC
	call decrypt_level
	ret
decrypt_property ENDP

decrypt_objectid PROC
	cmp rcx, 0h
	jz exit
    PUSH RBP
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rbx,rcx
	xor ebx,3B71BAF3h
	ror ebx,0Dh
	mov eax,ebx
	shl eax,10h
	xor eax,7B4B64C1h
	xor eax,ebx
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
    POP RBP
    RET
decrypt_objectid ENDP

exit PROC
	mov rax, 0h
	RET
exit ENDP


END