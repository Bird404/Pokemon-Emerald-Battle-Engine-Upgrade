.text
.thumb
.thumb_func
.align 2

magicbounce:
	mov r4, r3
	mov r0, r3
	mov r1, #1
	mov r2, #2
	bl has_ability_effect
	cmp r0, #0
	beq return
	ldr r0, =(battle_participants)
	mov r1, #0x58
	mul r1, r4
	add r0, r0, r1
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #0x9C
	bne return
	ldr r2, =(move_table)
	ldr r0, =(current_move)
	ldrh r1, [r0]
	lsl r0, r1, #1
	add r0, r0, r1
	lsl r0, r0, #2
	add r0, r0, r2
	ldrb r1, [r0, #8]
	mov r0, #4
	and r0, r1
	cmp r0, #0
	beq return
	bl magicbounce_loop_avoider
	cmp r0, #0
	beq return
	ldr r2, =(battlescript_push)
	bl callviar2
	mov r0, r4
	mov r1, #0x9C
	ldr r2, =(record_usage_of_ability)
	bl callviar2
	ldr r1, =(battlescripts_curr_instruction)
	ldr r0, =(magicbounce_bs)
	ldr r2, =(0x08046396 + 1)

callviar2:
	bx r2
	
return:
	mov r2, #0
	ldr r0, =(no_of_all_banks)
	ldrb r0, [r0]
	ldr r1, =(0x080461F2 + 1)
	bx r1
