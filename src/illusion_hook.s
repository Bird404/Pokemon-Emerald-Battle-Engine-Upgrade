.text
.thumb
.align 2

illusion_throw_different_ball:
	mov r4, r0 @r4 contains poke's data ptr
	mov r1, r5 @r5 contains poke's bank
	bl b_get_ball_to_throw
	ldr r2, =(ball_index_to_processing_id)
	bl r2_caller
	mov r4, r0
	ldr r2, =(0x080754D8 | 1)

r2_caller:
	bx r2

illusion_playername1:
	mov r0, #0
	mov r1, sp
	bl get_poke_nick
	b illusion_name_return
	
illusion_playername2:
	mov r0, #2
	mov r1, sp
	bl get_poke_nick
	b illusion_name_return
	
illusion_opponentname1:
	mov r0, #1
	mov r1, sp
	bl get_poke_nick
	b illusion_name_return
	
illusion_opponentname2:
	mov r0, #3
	mov r1, sp
	bl get_poke_nick
	b illusion_name_return
	
illusion_attacker_name:
	ldr r0, =(bank_attacker)
	ldrb r0, [r0]
	bl get_bank_poke_ptr 
	mov r1, sp
	bl get_poke_nick
	b illusion_name_return
	
illusion_target_name:
	ldr r0, =(bank_target)
	ldrb r0, [r0]
	mov r1, sp
	bl get_poke_nick
	b illusion_name_return
	
illusion_attacker_name_with_prefix:
	ldr r0, =(bank_attacker)
	ldrb r0, [r0]
	mov r1, sp
	mov r2, r8
	bl get_poke_nick_with_prefix
	b illusion_name_return
	
illusion_target_name_with_prefix:
	ldr r0, =(bank_target)
	ldrb r0, [r0]
	mov r1, sp
	mov r2, r8
	bl get_poke_nick_with_prefix
	b illusion_name_return
	
illusion_active_with_prefix:
	ldr r0, =(active_bank)
	ldrb r0, [r0]
	mov r1, sp
	mov r2, r8
	bl get_poke_nick_with_prefix
	b illusion_name_return
	
illusion_scripting_active_with_prefix:
	ldr r5, =(battle_scripting)
	ldrb r0, [r5, #0x17]
	mov r1, sp
	mov r2, r8
	bl get_poke_nick_with_prefix
	b illusion_name_return
	
illusion_name_return:
	ldr r0, =(0x0814F5BE | 1)
	bx r0
	
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
	