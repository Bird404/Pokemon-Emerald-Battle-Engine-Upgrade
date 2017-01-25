.text
.thumb
.thumb_func
.align 2

battlestringhook:
	mov r0, #0xBE
	lsl r0, r0, #1
	cmp r1, r0
	bhi new_way
	ldr r0, =(0x085CC270)
	sub r1, #0xC
	lsl r1, r1, #2
	add r1, r1, r0
	ldr r1, [r1]
	b return
	
new_way:
	ldr r2, =(new_strings_table)
	sub r1, r1, r0
	lsl r1, r1, #2
	add r1, r1, r2
	ldr r1, [r1]
	
return:
	ldr r0, =(0x0814F8BE + 1)
	bx r0
	