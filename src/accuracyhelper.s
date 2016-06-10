.text
.thumb
.thumb_func
.align 2

accuracyhelper:
	ldr r2, =(current_move)
	ldrh r0, [r2]
	cmp r0, #0x5C
	beq toxic
	bl weather_abilities_effect
	cmp r0, #0
	beq return
	ldr r0, =(battle_weather)
	ldr r1, [r0]
	mov r0, #0x80
	lsl r0, r0, #5
	add r0, #7
	and r0, r1
	cmp r0, #0
	beq return
	ldrh r0, [r2]
	cmp r0, #0x57
	beq always_hits
	mov r1, #0x87
	lsl r1, r1, #2
	add r1, #2
	cmp r0, r1
	beq always_hits
return:
	ldr r0, =(0x08046622 + 1)
	bx r0
always_hits:
	ldr r0, =(0x08046634 + 1)
	bx r0
toxic:
	ldr r0, =(bank_attacker)
	ldrb r0, [r0]
	mov r1, #3
	bl is_of_type
	cmp r0, #0
	beq return
	b always_hits
