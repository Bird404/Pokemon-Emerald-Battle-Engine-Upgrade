.text
.thumb
.thumb_func
.align 2

truant_end_turn:
	lsl r3, r0, #0x1F
	lsr r3, r3, #0x1F
	mov r2, #1
	eor r2, r3
	mov r3, #2
	neg r3, r3
	and r3, r0
	orr r3, r2
	mov r0, r3
	bx lr
