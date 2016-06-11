.text
.thumb
.thumb_func
.align 2

itemtarget:
	ldr r0, =(bank_target)
	ldrb r1, [r0]
	mov r2, #0
	str r2, [sp]
	mov r0, #4
	mov r3, #0
	bl ability_battle_effects
	ldr r0, =(bank_target)
	ldrb r1, [r0]
	mov r0, #2
	mov r2, #0
	bl item_battle_effects
	ldr r1, =(0x804C0B3)
	bx r1
