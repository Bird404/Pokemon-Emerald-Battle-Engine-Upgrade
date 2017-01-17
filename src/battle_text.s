.text
.thumb
.thumb_func
.align 2
	
display_custom_text:
	mov r0, r6
	bl battle_string_loader
	ldr r0, =(0x0814E6DE + 1)
	bx r0
	
.align 2
