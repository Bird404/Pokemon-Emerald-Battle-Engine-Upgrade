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
