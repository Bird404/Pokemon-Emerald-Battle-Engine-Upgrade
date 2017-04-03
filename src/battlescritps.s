.text
.thumb

.include "asm_defines.s"
.include "defines/bs_commands.s"

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
	