.text
.thumb

.include "defines/anim_locations.s"
.include "anim_particle/particle_ids.s"
.include "defines/anim_macros.s"

.align 2
NewPlayAnimationTable:
.word CASTFORM_CHANGE_ANIM
.word StatChangeAnimation
.word SUBSTITUTE_DESTROYED_ANIM
.word CREATE_SUBSTITUTE_ANIM
.word anim_table4
.word ITEM_KNOCKEDOFF_ANIM
.word TURN_TRAP_ANIM
.word ITEM_EFFECT_ANIM
.word SMOKEBALL_ESCAPE_ANIM
.word HANGED_ON_FOCUSBAND_ANIM
.word RAIN_CONTINUES_ANIM
.word SUN_CONTINUES_ANIM
.word SANDSTORM_CONTINUES_ANIM
.word HAIL_CONTINUES_ANIM
.word LEECH_SEED_HEAL_ANIM
.word POKE_HIT_ANIM
.word ITEM_STOLEN_ANIM
.word SNATCHED_MOVE_ANIM
.word FUTURE_SIGHT_ATTACK_ANIM
.word anim_table_x13
.word anim_table_x14
.word INGRAIN_HEAL_ANIM
.word WISH_HEAL_ANIM
.word anim_table_x17
.word RETURN_TO_BALL_ANIM
.word RETURN_TO_BALL2_ANIM
.word anim_table_x1a
.word anim_table_x1b
.word anim_table_x1c
.word anim_table_x1d
.word MegaEvoAnimation		@0x1e
.word AlphaPrimalAnimation	@0x1f
.word OmegaPrimalAnimation	@0x20
.word SpriteChangeAnimation	@0x21
.word TargetStealsAttackersItemAnimation	@0x22
.word PartnerAtkStealsPartnerDefItemAnimation	@0x23

PartnerAtkStealsPartnerDefItemAnimation:
	loadparticle 0x27f0 
	launchtask AnimTask_banks_to_partnerbanks +1 0x2 0x0
	goto 0x082D834D @goto ITEM_STOLEN_ANIM with changed banks

TargetStealsAttackersItemAnimation:
	loadparticle 0x27f0 
	launchtask AnimTask_target_attacks +1 0x2 0x0
	goto 0x082D834D @goto ITEM_STOLEN_ANIM with changed banks

StatChangeAnimation:
	launchtask ANIMTASK_prepare_statargs + 1 0x5 0x0  
	waitanimation 
	endanimation 

SpriteChangeAnimation:
	pokespritetoBG bank_target
	playsound2 0xCB 0xC0
	playsound3 0xCC 0xC0 0x30
	launchtask AnimTask_sprite_transform 2 0x1 0x0
	waitanimation
	pokespritefromBG bank_target
	endanimation

MegaEvoAnimation:
	loadparticle MEGAEVORAINBOW_particle
	loadparticle MEGAEVOSTONE_particle
	loadparticle MEGAEVOSYMBOL_particle 
	pokespritetoBG side_attacker 
	setblends 0x80c 
	soundcomplex 0x8c 0xc0 0xd 0x3 
	launchtask AnimTask_pal_fade_complex 0x2 0x6 PAL_ATK 0x0 0x6 0x0 0xb 0x2fff  
	call MegaEvo_build_rainbow 
	call MegaEvo_build_rainbow 
	call MegaEvo_build_rainbow 
	waitanimation 
	pokespritefromBG side_attacker 
	resetblends 
	pause 0x0 
	waitfortransparentBG 
	pokespritetoBG side_attacker 
	setblends 0x80c 
	playsound2 0xc9 0xc0 
	launchtemplate M_EVO_STONE_TEMPL 0x29 0x4 0x0 0x0 0x0 0x0  
	pause 0x14 
	launchtask 0x8116665 0x5 0x5 0x5 0x2 0x0 0x10 0xffff  
	launchtask AnimTask_pal_fade_particle 0x5 0x5 MEGAEVORAINBOW_particle 0x2 0x0 0x10 0xffff  
	waitanimation 
	launchtask AnimTask_pal_fade_particle 0x5 0x0  
	launchtask AnimTask_megaevo_swap_sprite +1 0x2 0x0  
	loadparticle 0x272d 
	launchtask 0x8116665 0x5 0x5 0x5 0x2 0x10 0x0 0xffff  
	launchtask AnimTask_screen_shake 0x5 0x3 0x1 0x5 0xe  
	waitanimation 
	launchtemplate M_EVO_SYMBOL_TEMPL 0x82 0x0  
	waitanimation 
	pokespritefromBG side_attacker
	launchtask AnimTask_animate_pokemon + 1 0x5 0x1 bank_attacker
	waitanimation
	endanimation 
MegaEvo_build_rainbow:
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0x28 0xfff6 0xd  
	pause 0x3 
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0xffdd 0xfff6 0xd  
	pause 0x3 
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0xf 0xffd8 0xd  
	pause 0x3 
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0xfff6 0xffe0 0xd  
	pause 0x3 
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0x19 0xffec 0xd  
	pause 0x3 
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0xffd8 0xffec 0xd  
	pause 0x3 
	launchtemplate M_EVO_RAINBOW_TEMPL 0x2 0x3 0x5 0xffd8 0xd  
	pause 0x3 
	return 

.align 2
M_EVO_STONE_TEMPL:
objtemplate MEGAEVOSTONE_particle MEGAEVOSTONE_particle 0x8524afc 0x82ec69c 0x0 0x8596894 0x80a77c9

M_EVO_SYMBOL_TEMPL:
objtemplate MEGAEVOSYMBOL_particle MEGAEVOSYMBOL_particle 0x8524a34 0x82ec69c 0x0 0x82ec6a8 0x8112b79

M_EVO_RAINBOW_TEMPL:
objtemplate MEGAEVORAINBOW_particle MEGAEVORAINBOW_particle 0x8524a8c 0x85921c8 0x0 0x85921dc 0x80fe8e1

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

AlphaPrimalAnimation:
	loadparticle ALPHAEVO_CHARGE_particle 
	loadparticle ALPHAEVO_STONE_particle 
	loadparticle ALPHAEVO_SYMBOL_particle 
	pokespritetoBG side_attacker 
	setblends 0x80c 
	soundcomplex 0x8c 0xc0 0xd 0x3 
	launchtask AnimTask_pal_fade_complex 0x2 0x6 PAL_ATK 0x0 0x6 0x0 0xb 0x2fff  
	call AlphaPrimal_build_rainbow 
	call AlphaPrimal_build_rainbow 
	call AlphaPrimal_build_rainbow 
	waitanimation 
	pokespritefromBG side_attacker 
	resetblends 
	pause 0x0 
	waitfortransparentBG 
	pokespritetoBG side_attacker 
	setblends 0x80c 
	playsound2 0xc9 0xc0 
	launchtemplate A_PRIMAL_STONE_TEMPL 0x29 0x4 0x0 0x0 0x0 0x0  
	pause 0x14 
	launchtask 0x8116665 0x5 0x5 0x5 0x2 0x0 0x10 0xffff  
	launchtask AnimTask_pal_fade_particle 0x5 0x5 ALPHAEVO_CHARGE_particle 0x2 0x0 0x10 0xffff  
	waitanimation 
	launchtask AnimTask_pal_fade_particle 0x5 0x0  
	launchtask AnimTask_megaevo_swap_sprite + 1 0x2 0x0  
	loadparticle 0x272d 
	launchtask 0x8116665 0x5 0x5 0x5 0x2 0x10 0x0 0xffff  
	launchtask AnimTask_screen_shake 0x5 0x3 0x1 0x5 0xe  
	waitanimation 
	launchtemplate A_PRIMAL_SYMBOL_TEMPL 0x82 0x0  
	waitanimation 
	pokespritefromBG side_attacker
	launchtask AnimTask_animate_pokemon + 1 0x5 0x1 bank_attacker
	waitanimation
	endanimation 
AlphaPrimal_build_rainbow:
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0x28 0xfff6 0xd  
	pause 0x3 
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0xffdd 0xfff6 0xd  
	pause 0x3 
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0xf 0xffd8 0xd  
	pause 0x3 
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0xfff6 0xffe0 0xd  
	pause 0x3 
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0x19 0xffec 0xd  
	pause 0x3 
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0xffd8 0xffec 0xd  
	pause 0x3 
	launchtemplate A_PRIMAL_RAINBOW_TEMPL 0x2 0x3 0x5 0xffd8 0xd  
	pause 0x3 
	return 

.align 2
A_PRIMAL_STONE_TEMPL:
objtemplate ALPHAEVO_STONE_particle ALPHAEVO_STONE_particle 0x8524afc 0x82ec69c 0x0 0x8596894 0x80a77c9

A_PRIMAL_SYMBOL_TEMPL:
objtemplate ALPHAEVO_SYMBOL_particle ALPHAEVO_SYMBOL_particle 0x8524a34 0x82ec69c 0x0 0x82ec6a8 0x8112b79

A_PRIMAL_RAINBOW_TEMPL:
objtemplate ALPHAEVO_CHARGE_particle ALPHAEVO_CHARGE_particle 0x8524a8c 0x85921c8 0x0 0x85921dc 0x80fe8e1

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

OmegaPrimalAnimation:
	loadparticle OMEGAEVO_CHARGE_particle 
	loadparticle OMEGAEVO_STONE_particle 
	loadparticle OMEGAEVO_SYMBOL_particle 
	pokespritetoBG side_attacker 
	setblends 0x80c 
	soundcomplex 0x8c 0xc0 0xd 0x3 
	launchtask AnimTask_pal_fade_complex 0x2 0x6 PAL_ATK 0x0 0x6 0x0 0xb 0x2fff  
	call OmegaPrimal_build_rainbow 
	call OmegaPrimal_build_rainbow 
	call OmegaPrimal_build_rainbow 
	waitanimation 
	pokespritefromBG side_attacker 
	resetblends 
	pause 0x0 
	waitfortransparentBG 
	pokespritetoBG side_attacker 
	setblends 0x80c 
	playsound2 0xc9 0xc0 
	launchtemplate O_PRIMAL_STONE_TEMPL 0x29 0x4 0x0 0x0 0x0 0x0  
	pause 0x14 
	launchtask 0x8116665 0x5 0x5 0x5 0x2 0x0 0x10 0xffff  
	launchtask AnimTask_pal_fade_particle 0x5 0x5 OMEGAEVO_CHARGE_particle 0x2 0x0 0x10 0xffff  
	waitanimation 
	launchtask AnimTask_pal_fade_particle 0x5 0x0  
	launchtask AnimTask_megaevo_swap_sprite + 1 0x2 0x0  
	loadparticle 0x272d 
	launchtask 0x8116665 0x5 0x5 0x5 0x2 0x10 0x0 0xffff  
	launchtask AnimTask_screen_shake 0x5 0x3 0x1 0x5 0xe  
	waitanimation 
	launchtemplate O_PRIMAL_SYMBOL_TEMPL 0x82 0x0  
	waitanimation 
	pokespritefromBG side_attacker
	launchtask AnimTask_animate_pokemon + 1 0x5 0x1 bank_attacker
	waitanimation
	endanimation 
OmegaPrimal_build_rainbow:
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0x28 0xfff6 0xd  
	pause 0x3 
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0xffdd 0xfff6 0xd  
	pause 0x3 
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0xf 0xffd8 0xd  
	pause 0x3 
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0xfff6 0xffe0 0xd  
	pause 0x3 
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0x19 0xffec 0xd  
	pause 0x3 
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0xffd8 0xffec 0xd  
	pause 0x3 
	launchtemplate O_PRIMAL_CHARGE_TEMPL 0x2 0x3 0x5 0xffd8 0xd  
	pause 0x3 
	return
	
.align 2
O_PRIMAL_STONE_TEMPL:
objtemplate OMEGAEVO_STONE_particle OMEGAEVO_STONE_particle 0x8524afc 0x82ec69c 0x0 0x8596894 0x80a77c9

O_PRIMAL_SYMBOL_TEMPL:
objtemplate OMEGAEVO_SYMBOL_particle OMEGAEVO_SYMBOL_particle 0x8524a34 0x82ec69c 0x0 0x82ec6a8 0x8112b79

O_PRIMAL_CHARGE_TEMPL:
objtemplate OMEGAEVO_CHARGE_particle OMEGAEVO_CHARGE_particle 0x8524a8c 0x85921c8 0x0 0x85921dc 0x80fe8e1

