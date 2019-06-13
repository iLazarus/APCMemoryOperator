.CODE

decrypt_uworld PROC
	cmp rcx, 0h
	jz decrypt_failure
	PUSH RBP
	PUSH RBX
	MOV RBP, RSP
	SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	movzx eax,dx
	mov ecx,edx
	mov r9,rdx
	shr ecx,10h
	xor ecx,eax
	shr r9,20h
	and edx,0FFFF0000h
	or ecx,edx
	add ecx,9EDE6602h
	mov edx,ecx
	movzx ecx,cx
	shr edx,10h
	xor ecx,edx
	movzx eax,dx
	ror ax,08h
	mov edx,r9d
	shr edx,10h
	movzx r8d,ax
	movzx eax,dx
	ror ax,08h
	xor dx,r9w
	ror dx,08h
	shl r8d,10h
	or r8d,ecx
	movzx edx,dx
	movzx ecx,ax
	xor r8d,9EDE6602h
	shl ecx,10h
	or edx,ecx
	mov [rsp],r8d
	add edx,9DC19D42h
	mov eax,edx
	shr eax,10h
	xor ax,dx
	and edx,0FFFF0000h
	ror ax,08h
	movzx ecx,ax
	or ecx,edx
	xor ecx,623E62BEh
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;	
	MOV RSP, RBP
	POP RBX
	POP RBP
	RET
decrypt_uworld ENDP


decrypt_gameinst PROC
	cmp rcx, 0h
	jz decrypt_failure
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	lea eax,[rcx-046450EBh]
	xor eax,0FB9BAF15h
	shr rcx,20h
	add ecx,7AF47A35h
	mov [rsp],eax
	xor ecx,850B85CBh
	mov [rsp+4h],ecx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
	POP RBX
    POP RBP
    RET
decrypt_gameinst ENDP

decrypt_level PROC
	cmp rcx, 0h
	jz decrypt_failure
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rax,rcx
	rol eax,10h
	add eax,7CFC0CC4h
	rol eax,10h
	xor eax,7CFC0CC4h
	mov [rsp],eax
	shr rcx,20h
	mov eax,ecx
	ror eax,08h
	add eax,7B437B44h
	ror eax,08h
	xor eax,84BC84BCh
	mov [rsp+4h],eax
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
	POP RBX
    POP RBP
    RET
decrypt_level ENDP

decrypt_actors PROC
	cmp rcx, 0h
	jz decrypt_failure
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	mov r8,rcx
	shr rdx,20h
	shr r8,20h
	mov eax,ecx
	and ecx,0EAEAEAEAh
	and eax,015151515h
	xor ecx,eax
	and edx,0EAEAEAEAh
	and r8d,015151515h
	sub ecx,074D4007Bh
	xor edx,r8d
	xor ecx,8B2BFF85h
	add edx,0A640AA5h
	mov [rsp],ecx
	xor edx,0F59BF55Bh
	mov [rsp+4h],edx
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
	POP RBX
    POP RBP
    RET
decrypt_actors ENDP

decrypt_local PROC
	cmp rcx, 0h
	jz decrypt_failure
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rax,rcx
	mov ecx,eax
	xor ecx,097703BDh
	shr rax,20h
	ror ecx,10h
	xor eax,6EA6C6E8h
	sub ecx,5BDB6BE4h
	ror eax,08h
	xor ecx,0A47703BDh
	sub eax,5C645C64h
	ror ecx,10h
	xor eax,09A6C6E8h
	xor ecx,0A424941Ch
	ror eax,08h
	xor eax,5C645C64h
	mov [rsp],ecx
	mov [rsp+4h],eax
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
	POP RBX
    POP RBP
    RET
decrypt_local ENDP

decrypt_controller PROC
	cmp rcx, 0h
	jz decrypt_failure
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rdx,rcx
	movzx eax,dx
	mov ecx,edx
	mov r8,rdx
	shr ecx,10h
	xor ecx,eax
	shr r8,20h
	and edx,0FFFF0000h
	or ecx,edx
	add ecx,989838E8h
	movzx eax,cx
	mov edx,ecx
	shr edx,10h
	and ecx,0FFFF0000h
	xor edx,eax
	or edx,ecx
	xor edx,989838E8h
	mov [rsp],edx
	mov edx,r8d
	shr edx,10h
	movzx eax,dx
	xor dx,r8w
	ror ax,08h
	movzx ecx,ax
	rol dx,08h
	movzx eax,dx
	shl ecx,10h
	or ecx,eax
	add ecx,97E797E8h
	mov edx,ecx
	shr edx,10h
	movzx eax,dx
	xor dx,cx
	ror ax,08h
	movzx r8d,ax
	rol dx,08h
	shl r8d,10h
	movzx eax,dx
	or r8d,eax
	xor r8d,68186818h
	mov [rsp+4h],r8d
	mov rax,[rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
	POP RBX
    POP RBP
    RET
decrypt_controller ENDP


decrypt_property PROC
	cmp rcx, 0h
	jz decrypt_failure
	call decrypt_level
	ret
decrypt_property ENDP

decrypt_objectid PROC
	cmp rcx, 0h
	jz decrypt_failure
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	;;;;;;;;;;;;;;;;;;;;;;;;;
	mov rbx,rcx
	xor ebx,0D6BDDD32h
	ror ebx,0Fh
	mov eax,ebx
	shl eax,10h
	xor eax,155D340Bh
	xor eax,ebx
	;;;;;;;;;;;;;;;;;;;;;;;;;
    MOV RSP, RBP
	POP RBX
    POP RBP
    RET
decrypt_objectid ENDP

decrypt_failure PROC
    PUSH RBP
	PUSH RBX
    MOV RBP, RSP
    SUB RSP, 8H
	mov rax, 0h
	MOV RSP, RBP
	POP RBX
    POP RBP
	ret
decrypt_failure ENDP


END