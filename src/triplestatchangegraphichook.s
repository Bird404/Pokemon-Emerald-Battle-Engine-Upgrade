.text
.thumb
.thumb_func
.align 2

graphic_triple_statchange:
	cmp r2, #0x90
	beq lower_stat_by_one
	cmp r2, #0xA0
	beq lower_stat_by_two
	cmp r2, #0xA0
	bgt triple_lower
	cmp r2, #0xA0
	blt triple_raise
	
lower_stat_by_one:
	mov r3, #0x16
	b return
	
lower_stat_by_two:
	mov r3, #0x2E
	b return

triple_lower:
	mov r3, #0x47
	b return
	
triple_raise:
	mov r3, #0x37
	
return:
	ldr r1, =(0x0804B9B4 + 1)
	bx r1
