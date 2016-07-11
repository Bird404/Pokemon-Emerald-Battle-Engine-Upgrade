.text
.thumb
.align 2

.include "asm_defines.s"
.include "defines/bs_commands.s"

@abilities
.equ ABILITY_OWNTEMPO, 0x14
.equ ABILITY_LIQUIDOOZE, 0x40

.equ MOVE_FAILED, 0x082D9F1A
.equ MOVE_MISSED, 0x082D8A5E
.equ ENDTURN, 0x82D8A4E
.equ STATE_TRACKER_ENDTURN, 0x202448A
.equ CURRENT_MOVE, 0x20241EA
.equ EffectChooser, 0x2024335
.equ MultiStringChooser, 0x2024337
.equ MoveOutcome, 0x202427C
.equ HitMarker, 0x2024280
.equ OutcomeMissed, 1
.equ OutcomeNotaffected, 8
.equ OutcomeFailed, 0x20
.equ HitMarkerNoAnimations, 0x80
.equ HitMarkerHitsSubstitute, 0x100

@status3
.equ status3_charged_up, 0x200

@@@macros for callasms
.macro jumpifsubstituteaffects jumpifsubstituteaffects_address
.byte 0x83
.hword 26
.word \jumpifsubstituteaffects_address
.endm

.macro jumpifcantchangetwostats jumpifcantchangetwostats_address
.byte 0x83
.hword 28
.word \jumpifcantchangetwostats_address
.endm

.macro doublestatchange
.byte 0x83
.hword 29
.endm

.macro jumpifcantconfuseandchangestats jumpifcantconfuseandchangestats_address
.byte 0x83
.hword 31
.word \jumpifcantconfuseandchangestats_address
.endm

.macro jumpifonlyonepokemoninteam jumpifonlyonepokemoninteam_address
.byte 0x83
.hword 38
.word \jumpifonlyonepokemoninteam_address
.endm

.macro weatherhpheal weatherhphealbank
.byte 0x83
.hword 40
.byte \weatherhphealbank
.endm

.macro jumpifnoally jumpifnoally_address
.byte 0x83
.hword 59
.word \jumpifnoally_address
.endm

battlescripts_table:
.word ATTACKING_MOVE	@ 0	Just attacks target(Tackle)
.word FIXED_DAMAGE		@1 Sonicboom, Dragon Rage, etc.
.word ONE_STAT_USER		@2 Swords Dance, Double Team, etc. ;arg1 = statchanger value
.word ONE_STAT_TARGET	@3 stuff like tail whip, growl and such ;arg1 = statchanger value
.word ATTACK_USERSTAT_CHANCE	@4 Metal Claw, Steel Wing, etc. ;arg1 = statchanger value
.word ATTACK_TARGETSTAT_CHANCE	@5 Mud Slap, Mud Shot and such ;arg1 = statchanger values
.word MULTIPLE_STAT_CHANGE_USER	@6 Dragon Dance, Bulk Up, etc. ;arg1 is a bitfield with which stats to raise, arg2 is a signed value for how much to add
.word MULTIPLE_STAT_CHANGE_TARGET	@7 Tickle, etc. ;arg1 is a bitfield with which stats to raise, arg2 is a signed value for how much to add
.word ATTACK_MULTIPLESTAT_CHANCE_USER	@8 Ancientpower, Close Combat, etc. ;arg1 is a bitfield with which stats to raise, arg2 is a signed value for how much to add
.word CONFUSE_TARGET	@9 Confuse Ray, Swagger; arg1 = statchanger value, if 0 only confuses
.word ATTACK_CONFUSION_CHANCE	@10 simply can confuse the target after the move
.word ATTACK_FLINCH_CHANCE		@11 simply can flinch the target after the move; arg1 is a status flag that can be applied, similarly to elemental fangs effect
.word PUT_TARGET_TO_SLEEP	@12	Sing, etc. tries to puts the target to sleep
.word POISON_TARGET		@13 poison gas, poisonspore, etc.
.word BADLY_POISON_TARGET	@14 Toxic is the only move that can do that
.word PARALYZE_TARGET	@15 Thunder Wave, Glare
.word BURN_TARGET		@16 Will-o-wisp
.word FREEZE_TARGET		@17 currently no move can do that
.word ATTACK_STATUS_CHANCE	@18 arg1 is status(poison, burn, etc.) flag
.word RECOIL_ATTACK		@19 arg1 is status(poison, burn, etc.) flag that can be applied; default recoil is 1/3
.word CRASH_ATTACK		@20 Jump Kick and such
.word FAINT_HEAL	@21 user heals, replacement is healed
.word FAINTSTATCHANGE	@22 user faints, but lowers target's stats; arg1 is bitfield for stats, arg2 is value for raising/lowering
.word EXPLODE			@23 Selfdestruct and explosion
.word DRAINDAMAGE		@24 moves that drain damage, arg1 is percent of the damage to be applied to HP(note: don't try values higher than 100), if arg2 isn't 0 we round up, else round down
.word HPHEAL_user		@25 heals user by 50% of its HP; arg1 is weather that gets 2/3 of HP, arg2 is weather that gets 1/4 of HP
.word HPHEAL_target		@26 heals target by 50% of its HP; bitfield for weather: 1 - rain, 2 - sun, 4 - sandstorm, 8 - hail, 0x10 - fog, 0x20 - air current
.word CHARGE			@27 arg1 is statvalue to be applied
.word TRANSFER_CONDITION	@28 Psycho Shift
.word ROOST				@29 Roost, heals 1/2 rounded up, loses flying type for remainder of the turn
.word GRAVITY			@30 sets Gravity, brings airborne Pokemon down
.word IDENTIFIER		@31 if arg1 is 0 = Foresight/Odor Sleught, else MiracleEye
.word ATTACK_HEAL_TARGET_STATUS	@32 arg1 is status flag, BP doubled is done in damage calc function
.word ATTACK_PROTECTION_BREAK	@33 if move is succesfull, it breaks protection for the turn; arg1 if 0 = broke through protect message, else feint message
.word PROTECT_LIKE_MOVE		@34 protect, shields, endure, all that stuff goes here
.word ATTACK_SWITCH		@35 Volt Tackle basically; arg1 is a status flag that can be applied coz why not
.word ATTACK_ONLYIF_TARGET_ATTACKS	@36 Sucker Punch; arg1 is a status flag that can be applied
.word ATTRACT			@37 just attract
.word LOWERSTAT_IFOPPOSITEGENDER	@38 Captivate basically; arg1 is statvalue
.word RECHARGE_NEEDED	@39 hyper beam, giga impacts, shit like that
.word ATTACK_AND_TRAP	@40 Wrap and stuff
.word ADD_THIRD_TYPE	@41 sets a third type to target; fails if user's already that type; arg1 is type to be changed into
.word ABILITY_CHANGE	@42 arg1 if 0 = we swap abilities, if 1 attacker's ability becomes target, if 2 target's ability becomes attacker, if 3 target's ability becomes ability in arg2
.word ROOMS				@43 no args, moves are read from IDs
.word COUNTER			@44 Counter, Mirror Coat and Metal Burst, moves read from IDs
.word GASTROACID		@45 makes target's ability ineffective
.word EMBARGO			@46 makes target's item useless
.word NATURALGIFT		@47 natural gift
.word AFTERYOU			@48 target moves right after the user
.word POWDER			@49 set powder bit
.word CHANGEALLYSTAT	@50 Aromatic-Mist like arg1 is statvalue
.word ATTACKCLEARSTATCHANGES	@51 Clears target's stat changes

ATTACKCLEARSTATCHANGES:
	setbyte EffectChooser 12
	attackcanceler
	accuracycheck MOVE_FAILED 0xFFFF
	critcalc
	damagecalc
	goto_cmd SUCCESS_MOVE_ATTACK

CHANGEALLYSTAT:
	attackcanceler
	jumpifnoally MOVE_FAILED
	jumpifsubstituteaffects MOVE_FAILED
	accuracycheck MOVE_FAILED 0xFFFF
	goto_cmd ONE_STAT_TARGET_WORKED

POWDER:
	attackcanceler
	accuracycheck MOVE_MISSED 0x0
	callasm_cmd 58 @sets powder
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring 0x1E0
	waitmessage 0x40
	goto_cmd ENDTURN

AFTERYOU:
	attackcanceler
	accuracycheck MOVE_FAILED 0xFFFF
	callasm_cmd 57 @after you check
	.word MOVE_FAILED
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring 0x1DF
	waitmessage 0x40
	goto_cmd ENDTURN

NATURALGIFT:
	attackcanceler
	accuracycheck MOVE_FAILED 0x0
	callasm_cmd 56 @checks if can attack
	.word MOVE_FAILED
	critcalc
	damagecalc
	removeitem bank_attacker
	goto_cmd SUCCESS_MOVE_ATTACK
	
EMBARGO:
	attackcanceler
	accuracycheck MOVE_FAILED 0x0
	callasm_cmd 55 @sets the bit
	.word MOVE_FAILED
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring 0x1DE
	waitmessage 0x40
	goto_cmd ENDTURN

GASTROACID:
	attackcanceler
	accuracycheck MOVE_FAILED 0x0
	callasm_cmd 54 @sets the bit
	.word MOVE_FAILED
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring 0x1DD
	waitmessage 0x38
	goto_cmd ENDTURN

COUNTER:
	attackcanceler
	callasm_cmd 53 @sets damage
	.word MOVE_FAILED
	accuracycheck MOVE_FAILED 0x0
	goto_cmd SUCCESS_MOVE_ATTACK

ROOMS:
	attackcanceler
	attackstring
	ppreduce
	attackanimation
	waitanimation
	callasm_cmd 52 @sets bit, chooses string
	printfromtable rooms_strings
	waitmessage 0x40
	goto_cmd ENDTURN

ABILITY_CHANGE:
	attackcanceler
	callasm_cmd 51 @changes abilities
	.word MOVE_FAILED
	accuracycheck MOVE_MISSED 0xFFFF
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printfromtable abilitychange_strings
	waitmessage 0x40
	goto_cmd ENDTURN

ADD_THIRD_TYPE:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	attackstring
	ppreduce
	callasm_cmd 50 @sets type
	.word (MOVE_FAILED + 2)
	accuracycheck MOVE_MISSED + 2 0x0
	attackanimation
	waitanimation
	printstring 0x1DB
	waitmessage 0x40
	goto_cmd ENDTURN

ATTACK_AND_TRAP:
	setbyte EffectChooser 11
	goto_cmd ATTACKING_MOVE

RECHARGE_NEEDED:
	setbyte EffectChooser 0x31 | 0x40
	goto_cmd ATTACKING_MOVE

LOWERSTAT_IFOPPOSITEGENDER:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	accuracycheck MOVE_MISSED 0x0
	callasm_cmd 49 @chcecks if opposite gender
	.word MOVE_FAILED
	goto_cmd ONE_STAT_TARGET_WORKED

ATTRACT:
	attackanimation
	accuracycheck MOVE_FAILED 0x0
	tryinfatuatetarget MOVE_FAILED
	attackanimation
	waitanimation
	printstring 0x45
	waitmessage 0x40
	goto_cmd ENDTURN

ATTACK_ONLYIF_TARGET_ATTACKS:
	attackcanceler
	callasm_cmd 36 @changes status flag in arg1 to correct effect chooser value
	callasm_cmd 48 @checks if target chose an attacking move
	.word MOVE_FAILED
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	critcalc
	damagecalc
	goto_cmd SUCCESS_MOVE_ATTACK

ATTACK_SWITCH:
	attackcanceler
	callasm_cmd 36 @changes status flag in arg1 to correct effect chooser value
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	critcalc
	damagecalc
	damageadjustment
	attackanimation
	waitanimation
	missmessage
	hitanim bank_target
	waitstate
	graphicalhpupdate bank_target
	datahpupdate bank_target
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	seteffectwithchance
	faintpokemon bank_target 0x0 0x0
	setbyte STATE_TRACKER_ENDTURN 0x0
	cmd49 0x0 0x0
	jumpifonlyonepokemoninteam JUSTEND
	openpartyscreen bank_attacker JUSTEND
	swithchoutabilities bank_attacker
	waitstate
	switch_handle_order bank_attacker 0x2
	cmd58 0x1
	switch1 0x1
	switch2 0x1
	cmd73 0x1
	printstring 0x3
	switch3 0x1 0x1
	waitstate
	switchineffects bank_attacker
	end_cmd

PROTECT_LIKE_MOVE:
	attackcanceler
	attackstring
	ppreduce
	setprotect
	attackanimation
	waitanimation
	printfromtable protect_moves_strings
	waitmessage 0x40
	goto_cmd ENDTURN

ATTACK_PROTECTION_BREAK:
	attackcanceler
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	callasm_cmd 47 @breaks protection
	call PROTECTION_BROKEN_MESSAGE
	critcalc
	damagecalc
	damageadjustment
	goto_cmd SUCCESS_MOVE_ATTACK
	
PROTECTION_BROKEN_MESSAGE:
	jumpifbyte Equals MultiStringChooser 0x2 JUSTRETURN
	pause_cmd 0x30
	printfromtable protection_broken_strings
	waitmessage 0x40
JUSTRETURN:
	return_cmd

ATTACK_HEAL_TARGET_STATUS:
	setbyte EffectChooser 10
	goto_cmd ATTACKING_MOVE

IDENTIFIER:
	attackcanceler
	accuracycheck MOVE_MISSED 0x0
	callasm_cmd 46 @sets identyfier bits
	.word MOVE_FAILED
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring 0x96
	waitmessage 0x40
	goto_cmd ENDTURN

GRAVITY:
	attackcanceler
	callasm_cmd 44 @sets gravity
	.word MOVE_FAILED
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring 0x1D0
	waitmessage 0x40
	callasm_cmd 45 @bring everyone down
	goto_cmd ENDTURN
	
ROOST:
	attackcanceler
	callasm_cmd 43 @prepare roost
	.word MOVE_FAILED
	attackstring
	ppreduce
	goto_cmd 0x82D8ED7 @hp healing script for attacker

TRANSFER_CONDITION:
	attackcanceler
	callasm_cmd 41 @jump if can't transfer condition
	.word MOVE_FAILED
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	attackanimation
	waitanimation
	callasm_cmd 42 @choose correct text: poke became paralyzed, etc.
	setbyte STATE_TRACKER_ENDTURN 0x0
	cmd49 0x0 0x0
	cureifburnedparalysedorpoisoned JUSTEND
	statusiconeupdate bank_attacker
	printstring 0xA7
	waitmessage 0x40
JUSTEND:
	end_cmd
	
CHARGE:
	attackcanceler
	attackstring
	ppreduce
	setcharge
	attackanimation
	waitanimation
	printstring 0xA5
	waitmessage 0x40
	callasm_cmd 25 @sets stat to change based on arg1
	statbuffchange 0x41 0x82D8CC7 @won't grow any higher
	jumpifbyte 0x1 0x2024337 0x2 0x82D8CBF @worked
	goto_cmd 0x82D8CC7

HPHEAL_target:
	attackcanceler
	setdamageasrestorehalfmaxhp ALREADY_FULLHP bank_target
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	weatherhpheal bank_target
	goto_cmd 0x82D9EE1 @hp healing script for target

HPHEAL_user:
	attackcanceler
	setdamageasrestorehalfmaxhp ALREADY_FULLHP bank_attacker
	attackstring
	ppreduce
	weatherhpheal bank_attacker
	goto_cmd 0x82D8ED7 @hp healing script for attacker
	
ALREADY_FULLHP:
	orbyte MoveOutcome OutcomeFailed
	attackstring
	ppreduce
	goto_cmd 0x82D9EFB @already has full hp

DRAINDAMAGE:
	goto_cmd 0x82D8AEA

EXPLODE:
	goto_cmd 0x82D8B79 @doesnt work at all
	
FAINTSTATCHANGE:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	attackstring
	ppreduce
	accuracycheck MOVE_MISSED 0x0
	setuserhptozero
	attackanimation
	waitanimation
	datahpupdate bank_attacker
	graphicalhpupdate bank_attacker
	doublestatchange
	faintpokemon bank_attacker 0x0 0x0
	goto_cmd ENDTURN

FAINT_HEAL:
	attackcanceler
	jumpifonlyonepokemoninteam MOVE_FAILED
	callasm_cmd 39 @sets lunar dance effect
	attackstring
	ppreduce
	attackanimation
	waitanimation
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	faintpokemon 0x1 0x0 0x0
	goto_cmd ENDTURN

CRASH_ATTACK:
	attackcanceler
	accuracycheck CRASHED 0x0
	critcalc
	damagecalc
	jumpiftypenotaffected CRASHED
	goto_cmd SUCCESS_MOVE_ATTACK
	
CRASHED:
	orbyte MoveOutcome OutcomeFailed
	attackstring
	ppreduce
	pause_cmd 0x20
	resultmessage
	waitmessage 0x40
	printstring 0x60
	waitmessage 0x40
	callasm_cmd 37 @half hp damage getter, takes one argument for bank
	.byte bank_attacker
	bicword MoveOutcome OutcomeFailed | OutcomeMissed | OutcomeNotaffected
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	faintpokemon bank_attacker 0x0 0x0
	orbyte MoveOutcome OutcomeMissed
	goto_cmd ENDTURN

ATTACK_FLINCH_CHANCE:
	setbyte EffectChooser 8
	attackcanceler
	accuracycheck MOVE_MISSED 0x0
	critcalc
	damagecalc
	damageadjustment
	attackstring
	ppreduce
	attackanimation
	waitanimation
	hitanim bank_target
	waitstate
	graphicalhpupdate bank_target
	datahpupdate bank_target
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	seteffectsecondary @calculation for both flinch and status effect are done in the function
	faintpokemon 0x0 0x0 0x0 @faint target
	goto_cmd ENDTURN

RECOIL_ATTACK:
	setbyte EffectChooser 0x30
	goto_cmd ATTACKING_MOVE

ATTACK_STATUS_CHANCE:
	callasm_cmd 36 @changes status flag in arg1 to correct effect chooser value
	goto_cmd ATTACKING_MOVE

FREEZE_TARGET:
	goto_cmd ENDTURN

BURN_TARGET:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	attackstring
	ppreduce
	callasm_cmd 35 @jumpifcantburn
	accuracycheck MOVE_MISSED 0x0
	jumpifhalverset 0x0 0x20 0x82DAD01
	attackanimation
	waitanimation
	setbyte EffectChooser 3
	seteffectprimary
	goto_cmd ENDTURN

PARALYZE_TARGET:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	attackstring
	ppreduce
	jumpiftypenotaffected MOVE_FAILED
	callasm_cmd 34 @similar to jumpifcannotsleep
	accuracycheck MOVE_MISSED 0x0
	jumpifhalverset 0x0 0x20 0x82DAD01
	attackanimation
	waitanimation
	setbyte EffectChooser 5
	seteffectprimary
	goto_cmd ENDTURN

BADLY_POISON_TARGET:
	setbyte EffectChooser 6
	goto_cmd TRY_POISONING
POISON_TARGET:
	setbyte EffectChooser 2
TRY_POISONING:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	attackstring
	ppreduce
	callasm_cmd 33 @similar to jumpifcannot sleep
	accuracycheck MOVE_MISSED 0x0
	jumpifhalverset 0x0 0x20 0x82DAD01
	attackanimation
	waitanimation
	seteffectprimary
	goto_cmd ENDTURN

PUT_TARGET_TO_SLEEP:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	attackstring
	ppreduce
	jumpifstatus 0x0 0x7 0x82D8AB0 @already asleep
	jumpifcannotsleep 0x82D8ACF @uproar, abiliy
	jumpifstatus 0x0 0xFF MOVE_FAILED
	accuracycheck MOVE_FAILED 0x0
	jumpifhalverset 0x0 0x20 0x82DAD01
	attackanimation
	waitanimation
	setbyte EffectChooser 0x1
	seteffectprimary
	goto_cmd ENDTURN

ATTACK_CONFUSION_CHANCE:
	setbyte EffectChooser 7
	goto_cmd ATTACKING_MOVE

CONFUSE_TARGET:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	jumpifcantconfuseandchangestats MOVE_FAILED
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	attackanimation
	waitanimation
	callasm_cmd 32 @this will try to change stats
	jumpifsecondarystatus bank_target 7 CANTCONFUSE
	jumpifhalverset 0x0 0x20 CANTCONFUSE
	jumpifability bank_target ABILITY_OWNTEMPO CANT_CONFUSE_DUETOABILITY
	setbyte EffectChooser 7
	seteffectprimary
	goto_cmd ENDTURN
	
CANT_CONFUSE_DUETOABILITY:
	recordability bank_target
	printstring 0xCA
	waitmessage 0x40
	goto_cmd ENDTURN
	
CANTCONFUSE:
	printstring 0x44
	waitmessage 0x40
	goto_cmd ENDTURN

ATTACK_MULTIPLESTAT_CHANCE_USER:
	setbyte EffectChooser 0x2F
	orbyte EffectChooser 0x40
	goto_cmd ATTACKING_MOVE

MULTIPLE_STAT_CHANGE_TARGET:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	jumpifcantchangetwostats MOVE_FAILED
	accuracycheck MOVE_MISSED 0x0
	attackstring
	ppreduce
	attackanimation
	waitanimation
	callasm_cmd 29 @do all stat changes that are possible
	goto_cmd ENDTURN

MULTIPLE_STAT_CHANGE_USER:
	attackcanceler
	jumpifcantchangetwostats MOVE_FAILED
	attackstring
	ppreduce
	attackanimation
	waitanimation
	callasm_cmd 29 @do all stat changes that are possible
	goto_cmd ENDTURN

ATTACK_TARGETSTAT_CHANCE:
	callasm_cmd 27
	goto_cmd ATTACKING_MOVE

ATTACK_USERSTAT_CHANCE:
	callasm_cmd 27 @converts arg1 stat to correct effect
	orbyte EffectChooser 0x40
	goto_cmd ATTACKING_MOVE

ONE_STAT_TARGET:
	attackcanceler
	jumpifsubstituteaffects MOVE_FAILED
	accuracycheck MOVE_MISSED 0x0
ONE_STAT_TARGET_WORKED:
	attackstring
	ppreduce
	callasm_cmd 25 @sets stat to change based on arg1
	statbuffchange 0x1 0x82D8D60
	jumpifbyte 0x3 0x2024337 0x2 0x82D8D4E
	jumpifbyte 0x0 0x2024337 0x3 0x82D8D60
	pause_cmd 0x20
	goto_cmd 0x82D8D58

ONE_STAT_USER:
	attackcanceler
	attackstring
	ppreduce
	callasm_cmd 25 @sets stat to change based on arg1
	statbuffchange 0x41 0x82D8CC7 @won't grow any higher
	jumpifbyte 0x1 0x2024337 0x2 0x82D8CBD @worked
	pause_cmd 0x20
	goto_cmd 0x82D8CC7 @failed

FIXED_DAMAGE:
	attackcanceler
	accuracycheck MOVE_MISSED 0x0
	callasm_cmd 24 @damage calc2
	goto_cmd SUCCESS_MOVE_ATTACK

ATTACKING_MOVE:
	attackcanceler
	accuracycheck MOVE_MISSED 0x0
	critcalc
	damagecalc
SUCCESS_MOVE_ATTACK:
	damageadjustment
	attackstring
	ppreduce
ATTACK_ANIM:
	attackanimation
	waitanimation
	hitanim bank_target
	waitstate
	graphicalhpupdate bank_target
	datahpupdate bank_target
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	seteffectwithchance
	faintpokemon bank_target 0x0 0x0 @faint target
	goto_cmd ENDTURN
	
