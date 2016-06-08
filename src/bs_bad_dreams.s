.text
.thumb
.align 2

.include "defines/bs_commands.s"

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global bad_dreams_bs
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bad_dreams_bs:	
	pause_cmd 0x20
	setbyte 0x202420C 0x0
bad_dreams_bs_main:
	cmde1 bad_dreams_bs_end
	jumpifstatus 0x0 0x7 bad_dreams_bs_damage
	goto_cmd bad_dreams_bs_iter

bad_dreams_bs_damage:
	jumpifsecondarystatus 0x0 0x100000 bad_dreams_bs_iter
	jumpifability 0x0 0x62 bad_dreams_bs_iter
	callasm_cmd 0xB @@callasm from table
	@@ playanimation
	printstring 0x1A2
	waitmessage 0x40
	graphicalhpupdate 0
	datahpupdate 0
	faintpokemon 0 0 0

bad_dreams_bs_iter:
	addbyte 0x202420C 0x1
	goto_cmd bad_dreams_bs_main
bad_dreams_bs_end:
	end3
