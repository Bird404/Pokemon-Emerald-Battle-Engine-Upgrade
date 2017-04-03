.text
.thumb
.align 1

illusion_throw_different_ball: @r0 contains bank
	bl b_get_ball_to_throw
	mov r4, r0
	ldr r2, =(0x080754DA | 1)
r2_caller:
	bx r2
	
illusion_on_player_switch_in:
	push {r5}
	mov r5, r0 @party address
	mov r1, r6 @bank
	bl try_illusion_change
	cmp r0, #0x0
	beq illusion_on_player_switch_in_get_normal_species
	mov r0, r6 @bank
	bl get_transform_species
	mov r8, r0
illusion_on_player_switch_in_get_normal_species:
	mov r0, r5 @party address
	mov r1, #0xB
	ldr r2, =(get_attributes)
	bl r2_caller
	mov r8, r0
illusion_on_player_switch_in_return:
	pop {r5}
	ldr r0, =(0x0805B29C | 1)
	bx r0
	
illusion_pokenick_hpbox:
	mov r0, r7
	bl update_pokenick_in_healthbox
	ldr r0, =(0x08074278 | 1)
	bx r0

anim_spritechange_pal:
	mov r0, r7 @bank
	mov r1, r6 @arg1
	bl update_transform_sprite_pal
	ldr r0, =(0x0805E726 | 1)
	bx r0
	
illusion_on_opponent_switch_in:
	push {r5}
	add r5, r0, r5 @poke ptr
	mov r0, r5
	mov r1, r6 @bank
	bl try_illusion_change
	cmp r0, #0x0
	beq illusion_on_opponent_switch_in_normal
	mov r0, r6 @bank
	bl get_transform_species
	mov r8, r0
	b illusion_on_opponent_switch_in_return
illusion_on_opponent_switch_in_normal:
	mov r0, r5
	mov r1, #0xB
	ldr r2, =(get_attributes)
	bl r2_caller
	mov r8, r0
illusion_on_opponent_switch_in_return:
	pop {r5}
	ldr r0, =(0x08061426 | 1)
	bx r0
	
illusion_playcorrectcry: @r7 = pokestruct, r5 = bank
	mov r0, r5
	bl get_transform_species
	cmp r0, #0x0
	beq illusion_playcorrectcry_nottransformed
	mov r9, r0
	b illusion_playcorrectcry_return
illusion_playcorrectcry_nottransformed:
	mov r0, r7
	mov r1, #0xB
	ldr r2, =(get_attributes)
	bl r2_caller
	mov r9, r0
illusion_playcorrectcry_return:
	ldr r1, =(0x08075DE4 | 1)
	bx r1
	
illusion_special_fdecoder_name:
	ldrb r0, [r4, #1] @bank
	bl get_party_ptr
	mov r2, #0x64
	ldrb r1, [r4, #2] @pos in party
	mul r1, r2
	add r0, r0, r1
	ldrb r1, [r4, #1] @bank
	mov r2, r6
	bl get_poke_nick2
	ldr r0, =(0x0814F8DE | 1)
	bx r0
	