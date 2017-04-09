#!/usr/bin/env python3

rom_name = "test.gba"		#Name of your rom
done_scripts = [0] * 950

import sys
import linecache
import os

def read_byte(rom, offset):
	rom.seek(offset)
	return int.from_bytes(rom.read(1), 'little')
	
def read_hword(rom, offset):
	rom.seek(offset)
	return int.from_bytes(rom.read(2), 'little')
	
def read_word(rom, offset):
	rom.seek(offset)
	return int.from_bytes(rom.read(4), 'little')
	
def read_ptr(rom, offset):
	rom.seek(offset)
	ptr = int.from_bytes(rom.read(4), 'little')
	if ptr > 0x08000000 and ptr < 0x0A000000:
		ptr -= 0x08000000
	else:
		ptr = 0x0
	return ptr
	
command_names = ["loadparticle", "unloadparticle", "launchtemplate", "launchtask", "pause", "waitanimation", "nop06", "nop07", "endanimation", "playsound1", "pokespritetoBG", "pokespritefromBG", "setblends", "resetblends", "call", "return", "setarg", "choosetwoturnanim", "jumpifmoveturnEQ", "goto", "loadBG1", "loaddefaultBG", "waitforBG", "waitfortransparentBG", "loadBG2", "playsound2", "pancontrol", "playsoundpanchange", "soundcomplex", "playsound3", "set_BLDCNT", "launchsoundtask" ,"waitforsound", "jumpifargmatches", "anim22", "anim23", "jumpifnotinbattle", "chooseBG", "playsoundpanchange2", "playsoundpanchange3", "leftbankBG_over_partnerBG", "bankBG_over_partnerBG", "leftopponentbankBG_over_partnerBG", "makebankinvisible", "makebankvisible", "anim2D", "anim2E", "stopmusic"]		
#B = byte, H = halfword, W = word, O = objtemplate ptr, T = task ptr, S = script ptr, A = args, b = backgrouund ID, s = poke sprite in commands 0xA and 0xB, a - poke bank
command_args = ["H", "H", "OBA", "TBA", "B", "", "", "", "", "H", "s", "s", "H", "", "S", "", "BH", "SS", "BS", "S", "b", "", "", "", "b", "HB", "B", "HBBBB", "HBBB", "HBB", "H", "TA", "", "BHS", "s", "s", "S", "bbb", "HBBBB", "HBBBB", "a", "", "B", "B", "B", "B", "B", ""]

def is_already_done(offset):
	if offset > 0x08000000:
		offset -= 0x08000000
	for i in range(0, len(done_scripts)):
		if done_scripts[i] == offset:
			return 1
		if done_scripts[i] == 0x0:
			done_scripts[i] = offset
			return 0
	print("OUT OF DONE SCRIPTS RANGE!")
	sys.exit(1)
	
script_queue = [0] * 50
labels = {0x82cdc76 : "HAIL_ANIM" ,0x82d2707 : "SUNNY_DAY_ANIM", 0x82d050a : "RAIN_DANCE_ANIM",  0x82d1e7b : "SANDSTORM_ANIM",0x82caf09 : "SLAM_ANIM", 0x82cbf5f : "ROCK_THROW_ANIM", 0x82cc173 : "BUBBLE_BEAM_ANIM", 0x82c9862 : "STRENGTH_ANIM", 0x82d0555 : "BITE_ANIM", 0x82d1dca : "SURF_ANIM", 0x82cb021 : "WATERFALL_ANIM", 0x82d0f9a : "ABSORB_ANIM", 0x82D79DF : "HEALING_ANIM", 0x82d7a28 : "HEALING_ANIM2", 0x82d7a71 : "POISON_BUBBLES" ,0x82d7cd1 : "SET_PSYCHIC_BG", 0x82d7cdd : "UNSET_SCROLLING_BG", 0x82d398c : "RAZORWIND_PREP", 0x82d39dc : "RAZORWIND_ATTACK", 0x82d398a : "RAZORWIND_WAIT_END", 0x82d08e6 : "SOLARBEAM_PREP", 0x82d09e3 : "SOLARBEAM_ATTACK", 0x82d08e4 : "SOLARBEAM_WAIT_END", 0x82ccf99 : "SKULLBASH_PREP", 0x82ccfe6 : "SKULLBASH_ATTACK", 0x82ccf98 : "SKULLBASH_END", 0x82cd185 : "SKYATTACK_PREP", 0x82cd28e : "SKYATTACK_ATTACK", 0x82cd184 : "SKYATTACK_END", 0x82d654c : "DIVE_PREP", 0x82d65a1 : "DIVE_ATTACK", 0x82d1ff7 : "FLY_PREP", 0x82d200f : "FLY_ATTACK", 0x82d1ff5 : "FLY_WAIT_END", 0x82cccab : "DIG_PREP", 0x82ccd06 : "DIG_ATTACK", 0x82cccaa : "DIG_END", 0x82d3719 : "BIDE_PREP", 0x82d3745 : "BIDE_ATTACK", 0x82c93f4 : "DOUBLESLAP_RIGHT", 0x82c9408 : "DOUBLESLAP_LEFT", 0x82c93da : "DOUBLESLAP_HIT", 0x82ca2f1 : "COMETPUNCH_RIGHT", 0x82ca316 : "COMETPUNCH_LEFT", 0x82ca2d7 : "COMETPUNCH_HIT", 0x82d52d4 : "ARMTHRUST_RIGHT", 0x82d52e8 : "ARMTHRUST_LEFT", 0x82d52c0 : "ARMTHRUST_HIT", 0x82d2060 : "BOUNCE_PREP", 0x82d2074 : "BOUNCE_ATTACK", 0x82d205f : "BOUNCE_END", 0x82cc7b8 : "FURYATTACK_RIGHT", 0x82cc7de : "FURYATTACK_LEFT", 0x82cc7a5 : "FURYATTACK_HIT", 0x82d751b : "WEATHERBALL_FIRE", 0x82d757f : "WEATHERBALL_WATER", 0x82d75e3 : "WEATHERBALL_SANDSTORM", 0x82d7683 : "WEATHERBALL_ICE", 0x82d74de : "WEATHERBALL_NORMAL", 0x82d41d4 : "PRESENT_DMG", 0x82d423f : "PRESENT_HEAL", 0x82cd8c8 : "MAGNITUDE_END", 0x82cd8c9 : "MAGNITUDE_4_TO_8", 0x82cd8ee : "MAGNITUDE_9_TO_10", 0x82d5b04 : "RETURN_WEAK", 0x82d5b56 : "RETURN_NOMRAL", 0x82d5bb6 : "RETURN_STRONG", 0x82d5cd1 : "RETURN_STRONGEST", 0x82d5aff : "RETURN_FINISHED", 0x82cb464 : "FRUSTATION_STRONGEST", 0x82cb56a : "FRUSTATION_STRONG", 0x82cb637 : "FRUSTATION_NORMAL", 0x82cb6b3 : "FRUSTATION_WEAK", 0x82cb45f : "FRUSTATION_FINISHED", 0x82d7720 : "FREEZE_CHANCE_ANIM", 0x82d2d18 : "BURN_CHANCE_ANIM", 0x82d7bea : "PARALYZE_CHANCE_ANIM", 0x82d3bfb : "GHOST_CURSE_ANIM", 0x82d3c78 : "STATS_CURSE_ANIM", 0x82d4c78 : "MORNINGSUN_CREATE_STAR", 0x82d0014 : "SHINING_SCREEN_EFFECT", 0x82d79b4 : "HEALING_STARS", 0x82cfecb : "CREATE_GROWLING_PARTICLES", 0x82ca1e9 : "LOAD_BG_IMPACT", 0x82ca212 : "LOAD_BG_IMPACT_ON_OPPONENT", 0x82ca211 : "LOAD_BG_IMPACT_RETURN", 0x82ca219 : "LOAD_BG_IMPACT_ON_PLAYER", 0x82ca220: "LOAD_BG_IMPACT_CONTESTS", 0x82d5a0e: "FOCUS_PUNCH_ACTUAL_ANIM", 0x82d5ac7 : "FOCUS_PUNCH_BG_IMPACT_CONTESTS", 0x82d5ab9 : "FOCUS_PUNCH_BG_IMPACT_ON_OPPONENT", 0x82d5ac0 : "FOCUS_PUNCH_BG_IMPACT_ON_PLAYER", 0x82d5a3c : "FOCUS_PUNCH_HIT" , 0x82d5a0c : "FOCUS_PUNCH_WAIT_END", 0x82d458e : "HYPERFANG_BG_IMPACT_CONTESTS", 0x82d4580 : "HYPERFANG_BG_IMPACT_ON_OPPONENT", 0x82d4587 : "HYPERFANG_BG_IMPACT_ON_PLAYER", 0x82d455c : "HYPERFANG_HIT", 0x82cf8f6  : "FUTURESIGHT_ACTUAL_ANIM", 0x82cf8ed : "FUTURESIGHT_FINISH_ANIM", 0x82d4bc1 : "SWALLOW_ONE_MORE", 0x82d4b7f : "SWALLOWING_ANIM", 0x82d4bcb : "SWALLOW_TWO_MORE", 0x82d4b78 : "SWALLOW_HEALING_ANIM", 0x82ce0a7 : "BRICKBREAK_NORMAL_ANIM", 0x82ce154 : "BRICKBREAK_SCREEN_DESTROY_ANIM", 0x82cd5e6 : "MACHPUNCH_LOAD_BG_ON_PLAYER", 0x82d650c : "SILVERWIND_BG_ON_PLAYER", 0x82d6352 : "SILVERWIND_HIT", 0x82cd57e : "MACHPUNCH_HIT", 0x82d0cb2 : "BLIZZARD_LOAD_BG_ON_PLAYER", 0x82d0b43 : "BLIZZARD_HIT", 0x82cda55 : "EXTREMESPEED_HIT", 0x82cdaf5 : "EXTREMESPEED_LOAD_BG_ON_PLAYER", 0x82d731b : "ICEBALL_LOAD_ICE_BG", 0x82d72bb : "ICEBALL_CONTINUE", 0x82d732c : "ICEBALL_FIRST", 0x82d735b : "ICEBALL_SECOND", 0x82d7394 : "ICEBALL_THIRD", 0x82d73d7 : "ICEBALL_FOURTH", 0x82d741f : "ICEBALL_MOST_POWERFUL", 0x82d731a : "ICEBALL_END", 0x82d7322 : "ICEBALL_RESTORE_BG", 0x82d7309 : "ICEBALL_ANIM_DONE", 0x82d7467 : "ICEBALL_LITTLE_ICE_SHARD", 0x82d22b8 : "TRIPLEKICK_FIRST", 0x82d22ee : "TRIPLEKICK_SECOND", 0x82d2324 : "TRIPLEKICK_THIRD", 0x82d22b3 : "TRIPLEKICK_FINISH", 0x82cd4cf : "NIGHTMARE_IN_CONTESTS", 0x82d1947 : "MEGAHORN_HIT", 0x82d19fa : "MEGAHORN_CONTEST_BG", 0x82d0f79 : "SINGALBEAM_BEAM_PARTICLES", 0x82d0337 : "SANDATTACK_SAND_PARTICLES", 0x82cc96a : "HORNDRILL_CONTESTS_BG", 0x82cc821 : "HORNDRILL_HIT", 0x82d3718 : "BIDE_END", 0x82ca135 : "EMBER_LOAD_FLAME", 0x82d1e58 : "FLAMETHROWER_LOAD_FLAME", 0x82d7ce5 : "SET_SCROLLING_FLYING_BG", 0x82d7cfe : "SET_SCROLLING_FLYING_BG_CONTESTS", 0x82d7cfc : "WAITFOR_FLYING_BG_CONTESTS", 0x82d7d15 : "UNSET_SCROLLING_BG2", 0x82cd1a0 : "SKYATTACK_PREP_ON_OPPONENT", 0x82cd217 : "SKYATTACK_PREP_ON_PARTNER", 0x82d396d : "SPIDERWEB_LOAD_PARTICLE", 0x82d38cc : "STRINGSHOT_LOAD_PARTICLE", 0x82d7d42 : "SOLARBEAM_LOAD_BG_CONTESTS",  0x82d7d1d : "SOLARBEAM_CHOOSE_BG",  0x82d7d50 : "SOLARBEAM_LOAD_BG_ON_OPPONENT",  0x82d7d49 : "SOLARBEAM_LOAD_BG_ON_PLAYER", 0x82d7d40 : "SOLARBEAM_WAIT_FOR_BG", 0x82d7d57 : "SOLARBEAM_LOAD_DEAFULT_BG", 0x82ca643 : "BEATUP_FINISH",  0x82ca648 : "BEATUP_RIGHT_HIT", 0x82ca6b9 : "BEATUP_LEFT_HIT", 0x82cada7 : "FURYCUTTER_CUT_TO_LEFT",  0x82cadb9 : "FURYCUTTER_CUT_TO_RIGHT", 0x82cad6a : "FURYCUTTER_GET_POWER",  0x82cad8e : "FURYCUTTER_HIT",  0x82cadcb : "FURYCUTTER_SECOND_STRIKE",  0x82cade5 : "FURYCUTTER_THIRD_STRIKE",  0x82cadff : "FURYCUTTER_MOST_POWERFUL_STRIKE", 0x82d4ab8 : "SPITUP_POWER2", 0x82d4ae1 : "SPITUP_POWER3", 0x82d4a7b : "SPITUP_HIT", 0x82ca99f : "PURSUIT_NORMAL", 0x82ca9c8 : "PURSUIT_SWITCHOUT",  0x82ca996 : "PURSUIT_HIT", 0x82d59ea : "METALSOUND_PARTICLE_LOAD_AND_PLAY", 0x82d2c34 : "MIST_LOAD_PARTICLE",  0x82c99ff : "SUPERSONIC_PARTICLE_LOAD_PLAY", 0x82d7183 : "MAGICAL_LEAF_ANIM", 0x82d319c : "PSYBEAM_LOAD_PARTICLE", 0x82d4ea1 : "HYPERBEAM_LOAD_PARTICLE", 0x82d6b48 : "SEISMICTOSS_FINISH", 0x82d6b53 : "SEISMICTOSS_WEAK",  0x82d6b64 : "SEISMICTOSS_NORMAL", 0x82d6b7c : "SEISMICTOSS_STRONG", 0x82cbdc0 : "GROWTH_EFFECT", 0x82cacbf : "FIRE_SPIN_TRAP_PARTICLES", 0x82d1f5b : "WHIRPOOL_TRAP_PARTICLES", 0x82d51b7 : "SANDTOMB_TRAP_PARTICLES", 0x82d7fe9 : "TURN_TRAP_FIRESPIN",  0x82d800e : "TURN_TRAP_WHIRLPOOL",  0x82d80bf : "TURN_TRAP_SANDTOMB", 0x82d8062 : "TURN_TRAP_CLAMP", 0x82d7fa1 : "TURN_TRAP_BIND", 0x82d30de : "WRAP_BIND_EFFECT_ANIM", 0x82d4f9b : "FLATTER_LOAD_PARTICLES", 0x82d2753 : "SUNNYDAY_LOAD_SUN_RAY", 0x82d16bc : "SLUDGEBOMB_PLAY_LOAD_PARTICLE", 0x82d03d5 : "MUDSLAP_LOAD_PARTICLE", 0x82cd6c7 : "BUFF_EFFECT", 0x82d3ad5 : "RECOVED_LOAD_PARTICLES", 0x82c9a4c : "SCREECH_PLAY_LOAD_PARTICLE", 0x82d31e5 : "HYPNOSIS_PLAY_LOAD_PARTICLES", 0x82d6bfc : "SEISMICTOSS_HIT_EFFECT",  0x82d26d3 : "SUBMISSION_LOAD_PARTICLES", 0x82d088b : "AURORABEAM_LOAD_PARTICLES", 0x82d07c1 : "ICEBEAM_LOAD_PARTICLES", 0x82ce92f : "NEEDLE_ARM_ANIM", 0x82d560d : "MUD_SHOT_ANIM", 0x82d5687 : "SECRETPOWER_SAND_LOAD_PARTICLES", 0x82d024a : "SMOG_LOAD_PARTICLE", 0x82ccfa9 : "SKULLBASH_PREP_ANIM", 0x82cb102 : "WATER_DIVE_ATTACK", 0x82c9fe9 : "FLAME_CIRCLE_FROM_ATTACKER_TO_TARGET",  0x82ca02d : "FLAMES_FROM_TARGET", 0x82cae9f : "EXPLODING_ATTACKER",  0x82cb312 : "EXPLODING_ATTACKER2", 0x82ccd6a : "GROUND_DIGGING", 0x82d30ee : "WRAP_BIND_EFFECT_TASK", 0x82ca372 : "SONICBOOM_LAUNCH_TEMPLATE", 0x82ca38a : "SONICBOOM_LAUNCH_TEMPLATE2", 0x82d0e52 : "HYDROPUMP_LAUNCH_PARTICLES", 0x82d0e93 : "HYDROPUMP_SOMETHING",  0x82d0b7d : "BLIZZARD_LAUNCH_PARTICLES", 0x82d77a4 : "FREEZE_CHANCE_ANIM2", }
task_names = {0x08117E60 : "AnimTask_arg7_is_in_contests", 0x0815A8C8 : "AnimTask_arg7_is_target_player", 0x8117780 : "AnimTask_arg7_is_target_opponent", 0x8117754 : "AnimTask_arg7_is_attacker_opponent", 0x81604f0 : "AnimTask_arg7_weather_case", 0x8107954 : "AnimTask_surf_wave", 0x8117c24 : "AnimTask_arg0_to_background", 0x81036a0 : "AnimTask_withdraw", 0x81152DC : "AnimTask_screen_shake", 0x8115600 : "AnimTask_argF_is_power_above_99", 0x8104938 : "AnimTask_splash_down", 0x8117660 : "AnimTask_scroll_background", 0x815a504 : "AnimTask_prepare_moving_psychicBG", 0x815a5c8 : "AnimTask_prepare_moving_psychicBG2", 0x810cdfc : "AnimTask_get_rollout_timer", 0x8107168 : "AnimTask_arg7_to_furycutter_timer", 0x08107144 : "AnimTask_arg7_is_furycutter_hit_even", 0x815b7d0 : "AnimTask_sprite_transform", 0x81177ac : "AnimTask_arg7_is_target_partner", 0x8117494 : "AnimTask_flash_anim", 0x80d51ac : "AnimTask_move_bank", 0x810c0a0 : "AnimTask_create_haze", 0x8116620 : "AnimTask_pal_fade" , 0x811675c : "AnimTask_pal_fade_depending_on_BG", 0x8117610 : "AnimTask_pal_fade_banks_except_attacker", 0x8116848 : "AnimTask_pal_fade_particle", 0x8158e9c : "AnimTask_play_growling_cry", 0x8158D8C : "AnimTask_play_howl_cry", 0x81177e4 : "AnimTask_set_invisibility_bit_to_all_except_attacker", 0x8115a04 : "AnimTask_pal_fade_complex", 0x8160544 : "AnimTask_SlackOff", 0x8104ab4 : "AnimTask_SwaggerBulkUP", 0x815f8a0 : "AnimTask_arg7_to_return_case",  0x080A8140 : "AnimTask_arg7_to_frustration_case", 0x815a904 : "AnimTask_arg7_is_move_healing", 0x81144f8 : "AnimTask_steel_sprite", 0x81114EC : "AnimTask_arg7_to_power_case", 0x81734b4 : "AnimTask_arg0_to_trapped_move_case", 0x8170CFC : "AnimTask_load_ball_tile", 0x8170D24 : "AnimTask_free_ball_tile"}

def get_label(label, if_not_in):
	if label in labels:
		return labels[label]
	return if_not_in
		
global last_task
global exit_script
last_task = 0x0
	
def get_task_name(task, if_not_in):
	task &= 0xFFFFFFFE #get rid of thumb last bit set
	global last_task
	last_task = task
	if task in task_names:
		return task_names[task]
	return if_not_in
	
def add_to_script_queue(offset):
	if offset > 0x08000000:
		offset -= 0x08000000
	for i in range(0, len(script_queue)):
		if script_queue[i] == 0x0:
			script_queue[i] = offset
			return
	print("OUT OF QUEUE RANGE!")
	sys.exit(1)
			
def do_in_queue(rom, file):
	for i in range(0, len(script_queue)):
		if script_queue[i] != 0x0:
			name = get_label(script_queue[i] + 0x08000000, "")
			read_script(rom, script_queue[i], file, name)
			script_queue[i] = 0x0

previous_command = [0xFD, 0xFE, 0xFF, 0xFF, 0xFF]

def put_in_previous(command_id):
	#print("Command = " + hex(command_id))
	#print("Before = " + hex(previous_command[0]) + " " + hex(previous_command[1]) + " " + hex(previous_command[2]))
	counter = len(previous_command) - 1
	while counter >= 0:
		if counter - 1 >= 0:
			previous_command[counter] = previous_command[counter - 1]
		else:
			previous_command[0] = command_id
		counter -= 1
	#print("After = " + hex(previous_command[0]) + " " + hex(previous_command[1]) + " " + hex(previous_command[2]))
			
def should_script_exit():
	should = False
	global last_task
	if last_task in task_names:
		#check if there was 'arg7' bool launchtask and two 'jumpifargmatches'
		if previous_command[2] == 0x3 and previous_command[1] == 0x21 and previous_command[0] == 0x21:
			if "arg7_is_" in task_names[last_task]:
				should = True
		#check weather ball task
		elif task_names[last_task] == "AnimTask_arg7_weather_case" and previous_command[4] == 0x21 and previous_command[3] == 0x21 and previous_command[2] == 0x21 and previous_command[1] == 0x21 and previous_command[0] == 0x21 :
			should = True
	return should

def get_arg_bank_name(bank, to_return):
	if bank == 0x0:
		to_return = "bank_attacker "
	elif bank == 0x1:
		to_return = "bank_target "
	elif bank == 0x2:
		to_return = "attacker_partner "
	elif bank == 0x3:
		to_return = "target_partner "
	return to_return
	
def palfade_append_arg_name(name, to_append):
	if name == "":
		return to_append
	return name + " | " + to_append
	
def get_arg_bank_pal_fading(value, to_return):
	val_name = ""
	if value & 1:
		val_name = palfade_append_arg_name(val_name, "PAL_BG")
	if value & 2:
		val_name = palfade_append_arg_name(val_name, "PAL_ATK")
	if value & 4:
		val_name = palfade_append_arg_name(val_name, "PAL_DEF")
	if value & 8:
		val_name = palfade_append_arg_name(val_name, "PAL_ATK_PARTNER")
	if value & 0x10:
		val_name = palfade_append_arg_name(val_name, "PAL_DEF_PARTNER")
	if value & 0x20:
		val_name = palfade_append_arg_name(val_name, "PAL_BIT_X20")
	if value & 0x40:
		val_name = palfade_append_arg_name(val_name, "PAL_BIT_X40")
	if value & 0x780:
		val_name = palfade_append_arg_name(val_name, "PAL_ALL_BANKS")
	else:
		if value & 0x80:
			val_name = palfade_append_arg_name(val_name, "PAL_PLAYER1")
		if value & 0x100:
			val_name = palfade_append_arg_name(val_name, "PAL_PLAYER2")
		if value & 0x200:
			val_name = palfade_append_arg_name(val_name, "PAL_OPPONENT1")
		if value & 0x400:
			val_name = palfade_append_arg_name(val_name, "PAL_OPPONENT2")
	if val_name == "":
		val_name = to_return
	else:
		val_name += " "
	return val_name
	
def get_argument_name(arg, pos, to_return):
	if previous_command[0] == 0x3: #last command was a task
		global last_task
		if ((last_task == 0x80d51ac or last_task == 0x8158e9c or last_task == 0x8158D8C or last_task == 0x8104938 or last_task == 0x8160544) and pos == 0x0) or (last_task == 0x80d622c and pos == 0x2):
			to_return = get_arg_bank_name(arg, to_return)
		elif ((last_task == 0x8116620 or last_task == 0x811675c or last_task == 0x8115a04) and pos == 0x0):
			to_return = get_arg_bank_pal_fading(arg, to_return)
	return to_return
	
def read_command(rom, offset, file, command_id):
	put_in_previous(command_id)
	global exit_script
	exit_script = should_script_exit()
	file.write("\n\t" + command_names[command_id] + ' ')
	counter = 0x0
	arg = command_args[command_id]
	for i in range(0, len(arg)):
		char = arg[i]
		if char == 'B':
			file.write(hex(read_byte(rom, offset + counter)))
			counter += 1
		elif char == 's':
			bank = read_byte(rom, offset + counter)
			bank_name = ""
			if bank == 0x0:
				bank_name = "bank_attacker"
			elif bank == 0x1:
				bank_name = "bank_target"
			elif bank == 0x2:
				bank_name = "side_attacker"
			elif bank == 0x3:
				bank_name = "side_target"
			file.write(bank_name)
			counter += 1
		elif char == 'b':
			BG_ID = read_byte(rom, offset + counter)
			bg_name = ""
			if BG_ID == 0x0 or BG_ID == 0x1:
				bg_name = "BG_DARK"
			elif BG_ID == 0x2:
				bg_name = "BG_GHOST"
			elif BG_ID == 0x3:
				bg_name = "BG_PSYCHIC"
			elif BG_ID == 0x4:
				bg_name = "BG_IMPACT_ON_OPPONENT"
			elif BG_ID == 0x5:
				bg_name = "BG_IMPACT_ON_PLAYER"
			elif BG_ID == 0x6:
				bg_name = "BG_IMPACT_CONTESTS"
			elif BG_ID == 0x7:
				bg_name = "BG_DRILL_BATTLE"
			elif BG_ID == 0x8:
				bg_name = "BG_DRILL_CONTESTS"
			elif BG_ID == 0x9:
				bg_name = "BG_HIGHSPEED_ON_OPPONENT"
			elif BG_ID == 0xA:
				bg_name = "BG_HIGHSPEED_ON_PLAYER"
			elif BG_ID == 0xB:
				bg_name = "BG_THUNDER"
			elif BG_ID == 0xC:
				bg_name = "BG_GUILLOTINE_ON_OPPONENT"
			elif BG_ID == 0xD:
				bg_name = "BG_GUILLOTINE_ON_PLAYER"
			elif BG_ID == 0xE:
				bg_name = "BG_GUILLOTINE_CONTESTS"
			elif BG_ID == 0xF:
				bg_name = "BG_ICE"
			elif BG_ID == 0x10:
				bg_name = "BG_COSMIC"
			elif BG_ID == 0x11:
				bg_name = "BG_SEISMICTOSS_SKUUPPERCUT"
			elif BG_ID == 0x12:
				bg_name = "BG_FLYING_BATTLE"
			elif BG_ID == 0x13:
				bg_name = "BG_FLYING_CONTESTS"
			elif BG_ID == 0x14:
				bg_name = "BG_AURORABEAM"
			elif BG_ID == 0x15:
				bg_name = "BG_FISSURE"
			elif BG_ID == 0x16:
				bg_name = "BG_BUG_ON_OPPONENT"
			elif BG_ID == 0x17:
				bg_name = "BG_BUG_ON_PLAYER"
			elif BG_ID == 0x18:
				bg_name = "BG_SOLARBEAM_ON_OPPONENT"
			elif BG_ID == 0x19:
				bg_name = "BG_SOLARBEAM_ON_PLAYER"
			elif BG_ID == 0x1A:
				bg_name = "BG_SOLARBEAM_CONTESTS"
			else:
				print("ERROR! WRONG BG ID!")
				#sys.exit(1)
				bg_name = hex(BG_ID)
			file.write(bg_name)
			counter += 1
		elif char == 'H':
			file.write(hex(read_hword(rom, offset + counter)))
			counter += 2
		elif char == 'O':
			template_ptr = (read_word(rom, offset + counter))
			file.write("TEMPL_" + hex(template_ptr).lstrip("x"))
			if template_ptr not in templates:
				global template_id
				templates[template_id] = template_ptr
				template_id += 1
			counter += 4
		elif char == 'T':
			task_ptr = read_word(rom, offset + counter)
			file.write(get_task_name(task_ptr, hex(task_ptr)))
			counter += 4
		elif char == 'A':
			no_of_args = read_byte(rom, offset + counter)
			counter += 1
			file.write(hex(no_of_args) + ' ')
			for j in range(0, no_of_args):
				argument = read_hword(rom, offset + counter)
				file.write(get_argument_name(argument, j, hex(argument) + ' '))
				counter += 2
		elif char == 'S':
			script_ptr = read_word(rom, offset + counter)
			file.write(get_label(script_ptr, "UNK_" + hex(script_ptr)))
			#file.write(get_label(script_ptr,  hex(script_ptr)))
			counter += 4
			add_to_script_queue(script_ptr)
		elif char == 'a':
			bank = read_byte(rom, offset + counter)
			file.write(get_arg_bank_name(bank, hex(bank)))
			counter += 1
		else:
			print("UNSUPPORTED COMMAND ARGUMENT!")
			sys.exit(1)
		file.write(' ')
	return counter
	
equ_mode = False
offsets_mode = True

def read_script(rom, offset, file, name):
	if offset == 0x0 or is_already_done(offset):
		return
	temp = open("./scripts/temp" + str(offset) + ".txt", 'w+')
	label_name = ""
	if name == "":
		label_name = "UNK_" + hex(offset + 0x08000000)
		#label_name = "UNK_" + hex(offset + 0x08000000)
	else:
		name = name.replace('\n', '')
		if offsets_mode == True:
			label_name = hex(offset + 0x08000000) + ' ' + name
		else:
			label_name = name
	temp.write(label_name + ':')
	counter = 0x0
	while True:
		command_id = read_byte(rom, offset + counter)
		counter += 1
		if command_id > 0x2F:
			print("Wrong command! Script at " + hex(offset) + " Offset at " + hex(offset + counter))
			sys.exit(1)
		counter += read_command(rom, offset + counter, temp, command_id)
		if command_id == 0xF or command_id == 0x8 or command_id == 0x13: #return, end, goto
			break
		global exit_script
		if exit_script == True:
			exit_script = False
			print("Custom exit at " + hex(offset) + " Offset at " + hex(offset + counter))
			break
		#make decompiled scripts prettier
		curr_offset = offset + counter + 0x08000000
		if command_id == 0x11 or curr_offset == 0x82d6352 or curr_offset == 0x82cd57e or curr_offset == 0x82d6b48 or curr_offset == 0x82d0b43 or curr_offset == 0x82cda55 or curr_offset == 0x82d72bb or curr_offset == 0x82d7309 or curr_offset == 0x82d731a or curr_offset == 0x82cd8c8 or curr_offset == 0x82d1947 or curr_offset == 0x82cc821 or curr_offset == 0x82d4a7b or curr_offset == 0x82d5aff:
			temp.write('\n' + hex(curr_offset) + ' ' + get_label(curr_offset, "") + ':')
			if equ_mode == True:
				file.write(".equ " + get_label(curr_offset, "") + ", " + hex(curr_offset) + '\n')
			is_already_done(curr_offset)
	temp.write('\n')
	temp.seek(0x0)
	if equ_mode == True:
		file.write(".equ " + label_name + ", " + hex(offset + 0x08000000) + '\n')
	else:
		file.write(temp.read())
	temp.close()
	os.remove("./scripts/temp" + str(offset) + ".txt")
	do_in_queue(rom, file)
	
def commands_to_macros(file):
	file.seek(0x0)
	copy = file.read()
	copy = copy.replace("\n\tloaddefaultBG \n\twaitforBG \n\tsetarg 0x7 0xffff \n\twaitfortransparentBG ", "\n\tunsetscrollingBG ")
	file.seek(0x0)
	file.write(copy)

templates = [0] * 580
global template_id
template_id = 0

decompile_all_moves = False
decompile_from_table = False
write_new_table = False
	
with open(rom_name, 'rb') as rom:
	with open("./scripts/task_names.txt", 'r+') as tasks:
		for key, value in task_names.items():
			tasks.write(value  + " = " + hex(key) + " |1;\n")
	anims = open("./scripts/anim_scripts.txt", 'r+')
	anims.truncate()
	#read all moves
	if decompile_all_moves == True:
		move_anims = read_ptr(rom, 0x0A3A44)
		for i in range(0, 355):
			read_script(rom, read_ptr(rom, move_anims + (i * 4)), anims, linecache.getline("./scripts/move_list.txt", i + 1))
	#read animations from anim table
	if decompile_from_table == True:
		anim_tab = read_ptr(rom, 0x05DA3C)
		for i in range(0, 30):
			read_script(rom, read_ptr(rom, anim_tab + (i * 4)), anims, linecache.getline("./scripts/animstable_list.txt", i + 1))
	#read custom animations
	read_script(rom, 0xF20FB8, anims, "OmegaPrimalAnimation")
	read_script(rom, 0xF20E50, anims, "AlphaPrimalAnimation")
	#write objtemplates
	anims.write("\n.align 2\n")
	for i in range(0, template_id):
		if equ_mode == False:
			anims.write("TEMPL_" + hex(templates[i]) + ':\nobjtemplate ')
			rom.seek(templates[i] - 0x08000000)
			anims.write(hex(int.from_bytes(rom.read(2), 'little')) + ' ') #tiles tag
			anims.write(hex(int.from_bytes(rom.read(2), 'little')) + ' ') #tiles pal
			anims.write(hex(int.from_bytes(rom.read(4), 'little')) + ' ') #oam
			anims.write(hex(int.from_bytes(rom.read(4), 'little')) + ' ') #image anins
			anims.write(hex(int.from_bytes(rom.read(4), 'little')) + ' ') #gfx
			anims.write(hex(int.from_bytes(rom.read(4), 'little')) + ' ') #rotscale
			anims.write(hex(int.from_bytes(rom.read(4), 'little')) + '\n') #callback
		else:
			anims.write(".equ TEMPL_" + hex(templates[i]) + ", " + hex(templates[i]) + '\n')
		
	#write the new table
	if write_new_table == True:
		anims.write("\n.align 2\nmove_animations_table:\n")
		for i in range(0, 1025):
			anims.write(".word " + linecache.getline("./scripts/move_list.txt", i + 1))
		for i in range(0, 622):
			movename = linecache.getline("./scripts/move_list.txt", i + 1)
			movename = movename.replace("\n", "")
			anims.write(movename + ":\n" + "endanimation\n\n")
	#change repeated commands to shorter macros
	commands_to_macros(anims)
	anims.close()
	rom.close()
