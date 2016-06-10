.text
.thumb
.align 2

alloc_new_struct_hook:
	bl alloc_new_struct
	ldr r2, =0x8056F4A|1
	bx r2

.align 2
.pool

free_new_struct_hook:
	bl free_new_struct
	mov r5, #0x0
	ldr r2, =0x8057050|1
	bx r2
.align 2
