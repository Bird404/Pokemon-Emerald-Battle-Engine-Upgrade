.text
.thumb
.align 2

.include "defines/bs_commands.s"

.global frisk_bs

frisk_bs:
	pause_cmd 0x20
	setbyte 0x202420C 0x0
frisk_bs_main:
	cmde1 0x82DB4BD @@ pointer to end3 command
	jumpifsecondarystatus 0x0 0x100000 frisk_bs_iter
	callasm_cmd 0x7 @@callasm from table
	waitmessage 0x40
frisk_bs_iter:
	addbyte 0x202420C 0x1
	goto_cmd frisk_bs_main
