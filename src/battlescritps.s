.text
.thumb

.include "asm_defines.s"
.include "defines/bs_commands.s"

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@Poke Ball block
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global BS_BALL_BLOCK
BS_BALL_BLOCK:
	jumpifword 4 battle_flags BATTLE_TRAINER BS_TRAINER_BLOCK
	printstring 0x22B
	waitmessage 0x40
BALLBLOCK_CONTINUE:
	cmdf6
	setbyte 0x2024488 0xF
	cmd49 0x1 0x0
	end_cmd
BS_TRAINER_BLOCK:
	printstring 0x103
	waitmessage 0x40
	printstring 0x104
	waitmessage 0x40
	goto_cmd BALLBLOCK_CONTINUE
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@Custom loss
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global BS_CUSTOM_LOSS
BS_CUSTOM_LOSS:
	printstring 0x22C
	waitmessage 0x40
	cmd76 1 19 @return to ball
	waitstate
	cmd76 1 20 @return to ball second poke
	waitstate
	trainer_slide 1
	waitstate
	printstring 0x22D
	waitmessage 0x30
	jumpifword Has_One_Bit_Common battle_flags BATTLE_MULTI BS_CUSTOM_SLIDE_TRAINER2
	end_cmd
BS_CUSTOM_SLIDE_TRAINER2:
	trainer_back_slide 1
	waitstate
	trainer_slide 3
	waitstate
	trainer_back_slide 3
	waitstate
	end_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@Trainer sliding
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
.global BS_TRAINER_SLIDE_MSG_RETURN
BS_TRAINER_SLIDE_MSG_RETURN:
	callasm_cmd 133
	trainer_slide 1
	waitstate
	printstring 0x22F
	waitmessage 0x30
	trainer_back_slide 1
	waitstate
	callasm_cmd 134
	return_cmd
	
.global BS_TRAINER_SLIDE_MSG_END2	
BS_TRAINER_SLIDE_MSG_END2:
	call BS_TRAINER_SLIDE_MSG_RETURN
	end2

BS_POKE_FAINTS_EXP_SLIDEIN:
	callasm_cmd 135
	setbyte 0x02024490 0x0 @exp command state tracker
	giveexp 0
	end2
	
.global BS_PRINT_SPORT_FADED
BS_PRINT_SPORT_FADED:
	printstring 0x231
	waitmessage 0x40
	end2
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@Frisk battlescript
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global FRISK_BS
FRISK_BS:
	pause_cmd 0x20
	setbyte 0x202420C 0x0
FRISK_BS_MAIN:
	cmde1 FRISK_BS_END
	jumpifsecondarystatus 0x0 0x100000 FRISK_BS_ITER
	callasm_cmd 0x7 @@callasm from table
	waitmessage 0x40
FRISK_BS_ITER:
	addbyte 0x202420C 0x1
	goto_cmd FRISK_BS_MAIN
FRISK_BS_END:
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ bad dreams
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BAD_DREAMS_BS
BAD_DREAMS_BS:	
	pause_cmd 0x20
	setbyte 0x202420C 0x0
BAD_DREAMS_BS_MAIN:
	cmde1 BAD_DREAMS_BS_END
	jumpifstatus 0x0 0x7 BAD_DREAMS_BS_DAMAGE
	goto_cmd BAD_DREAMS_BS_ITER
BAD_DREAMS_BS_DAMAGE:
	jumpifsecondarystatus 0x0 0x100000 BAD_DREAMS_BS_ITER
	jumpifability 0x0 0x62 BAD_DREAMS_BS_ITER
	callasm_cmd 0xB @@callasm from table
	@@ playanimation
	printstring 0x1A2
	waitmessage 0x40
	graphicalhpupdate 0
	datahpupdate 0
	faintpokemon 0 0 0
BAD_DREAMS_BS_ITER:
	addbyte 0x202420C 0x1
	goto_cmd BAD_DREAMS_BS_MAIN
BAD_DREAMS_BS_END:
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ mega evolution and fervent wish
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MEGA_EVO
BS_MEGA_EVO:
	callasm_cmd 88
	printstring 0x205
BS_MEGA_EVO_STUFF:
	playanimation bank_attacker 0x1E 0x0
	waitstate
	callasm_cmd 106
	callasm_cmd 89
	printstring 0x204
	callasm_cmd 0
	end3
	
.global BS_FERVENT_EVO
BS_FERVENT_EVO:
	callasm_cmd 88
	printstring 0x206
	goto_cmd BS_MEGA_EVO_STUFF

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ primal reversion
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ALPHA_PRIMAL
BS_ALPHA_PRIMAL:
	pause_cmd 0x20
	playanimation bank_attacker 0x1F 0
BS_PRIMAL:
	waitstate
	callasm_cmd 106
	callasm_cmd 89
	printstring 0x210
	waitmessage 0x40
	end3
	
.global BS_OMEGA_PRIMAL
BS_OMEGA_PRIMAL:
	pause_cmd 0x20
	playanimation bank_attacker 0x20 0
	goto_cmd BS_PRIMAL
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ telekinesis end
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_TELEKINESIS_ENDS_RET
BS_TELEKINESIS_ENDS_RET:
	printstring 0x1B9
	waitmessage 0x40
	return_cmd
	
.global BS_TELEKINESIS_ENDS_2
BS_TELEKINESIS_ENDS_2:
	call BS_TELEKINESIS_ENDS_RET
	end2
	