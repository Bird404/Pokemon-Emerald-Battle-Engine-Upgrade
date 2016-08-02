#ifndef B_STRUCTS
#define B_STRUCTS

#include "types.h"

struct status_main{
    u32 sleep : 3;
    u32 poison : 1;
    u32 burn : 1;
    u32 freeze : 1;
    u32 paralysis: 1;
    u32 toxic_poison : 1;
    u32 poison_counter : 4;
};

union main_status{
    u32 int_status;
    struct status_main flags;
};

#define STATUS_SLEEP 0x7
#define STATUS_POISON 0x8
#define STATUS_BURN 0x10
#define STATUS_FREEZE 0x20
#define STATUS_PARALYSIS 0x40
#define STATUS_TOXIC_POISON 0x80

struct flags2{
    u32 confusion : 3; //0x1 | 0x2 | 0x4
    u32 flinched : 1; //0x8
    u32 uproar : 3; //0x10 | 0x20 | 0x40
    u32 flag_x80 : 1; //0x80
    u32 bide : 2; //0x100 | 0x200
    u32 locked_and_confuse : 2; //0x400 | 0x800
    u32 multiple_turn_move : 1; //0x1000
    u32 trapped_in_wrap : 3; //0x2000 | 0x4000 | 0x8000
    u32 in_love : 4; //each bit for bank 0x10 000 | 0x20 000 | 0x40 0000 | 0x80 000
    u32 focus_energy : 1; //0x100 000
    u32 transformed : 1; //0x200 000
    u32 recharge : 1; //0x400 000
    u32 raged : 1; //0x800 000
    u32 substitute : 1;// 0x1 000 000
    u32 destinny_bond : 1; //0x2 000 000
    u32 cant_escape : 1; //0x4 000 000
    u32 nightmare : 1; //0x8 000 000
    u32 cursed : 1; //0x10 000 000
    u32 foresight : 1; //0x20 000 000
    u32 defense_curled : 1; //0x40 000 000
    u32 tormented : 1; //0x80 000 000
};

struct iv_set
{
    u32 iv_hp: 5;
    u32 iv_atk: 5;
    u32 iv_def: 5;
    u32 iv_spd: 5;
    u32 iv_sp_atk: 5;
    u32 iv_sp_def: 5;
};

struct battle_participant {
    u16 poke_species;
    u16 atk;
    u16 def;
    u16 spd;
    u16 sp_atk;
    u16 sp_def;
    u16 moves[4];
    struct iv_set ivs;
    u8 hp_buff;
    u8 atk_buff;
    u8 def_buff;
    u8 spd_buff;
    u8 sp_atk_buff;
    u8 sp_def_buff;
    u8 acc_buff;
    u8 evasion_buff;
    u8 ability_id;
    u8 type1;
    u8 type2;
    u8 padd;
    u8 current_pp[4];
    u16 current_hp;
    u8 level;
    u8 happiness;
    u16 max_hp;
    u16 held_item;
    u8 poke_name[12];
    u8 trainer_name[8];
    u32 padd2;
    u32 pid;
    union main_status status;
    struct flags2 status2;
    u32 otid;
};

extern struct battle_participant battle_participants[4];

struct evolution_sub{
    u16 method;
    u16 paramter;
    u16 poke;
    u16 padding;
};

struct evolution{
    struct evolution_sub evos[5];
};

extern struct evolution evolution_table[700];

struct in_battle_weather{
    u32 rain : 1;
    u32 downpour : 1;
    u32 permament_rain : 1;
    u32 sandstorm : 1;
    u32 permament_sandstorm : 1;
    u32 sun : 1;
    u32 permament_sun : 1;
    u32 hail : 1;
    //custom flags
    u32 permament_hail : 1;
    u32 fog : 1;
    u32 permament_fog : 1;
    u32 harsh_sun : 1;
    u32 heavy_rain : 1;
    u32 air_current : 1;
};

#define weather_rain 1
#define weather_downpour 2
#define weather_permament_rain 4
#define weather_sandstorm 8
#define weather_permament_sandstorm 0x10
#define weather_sun 0x20
#define weather_permament_sun 0x40
#define weather_hail 0x80
#define weather_permament_hail 0x100
#define weather_fog 0x200
#define weather_permament_fog 0x400
#define weather_harsh_sun 0x800
#define weather_heavy_rain 0x1000
#define weather_air_current 0x2000


union battle_weather{
    u32 int_bw;
    struct in_battle_weather flags;
};

extern union battle_weather battle_weather;

struct b_stuff_duration{
    u8 field0[32];
    u8 wish_duration[4];
    u8 id_of_wish_user[4];
    u8 weather_dur;
    u8 knocked_off_pokes[2];
};

extern struct b_stuff_duration battle_effects_duration;

struct b_enigma_berry{
    u8 field0[7];
    u8 battle_effect_x12;
    u8 field8[18];
    u8 quality;
    u8 field1B;
};

extern struct b_enigma_berry enigma_berry_battle[4];

struct b_scripting{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
    u32 bide_damage;
    u8 field_8;
    u8 field_9;
    u8 field_A;
    u8 field_B;
    u8 field_C;
    u8 field_D;
    u8 damage_multiplier;
    u8 fieldF;
    u8 field10;
    u8 field11;
    u8 field12;
    u8 field13;
    u8 cmd49_state_tracker;
    u8 field15;
    u8 field16;
    u8 active_bank;
    u8 field18;
    u8 field19;
    u8 stat_changer;
    u8 field1B;
    u8 cmd23_state_tracker;
};

extern struct b_scripting battle_scripting;

struct mirror_move_set_per_bank
{
    u16 moves_per_target[4];
};

extern struct mirror_move_set_per_bank mirror_move_set_pbs;

struct battle_stuff{
    u8 end_turn_statetracker1; //0x0
    u8 end_turn_checked_bank; //0x1
    u8 field_2; //0x2
    u8 end_turn_statetracker2; //0x3
    u16 trapped_move[4]; //0x4 - 0xB
    u8 move_target[4]; //0xC - 0xF
    u8 field_10; //0x10
    u8 field_11; //0x11
    u8 field_12; //0x12
    u8 dynamic_move_type; //0x13
    u8 trapper[4];//0x14-0x17
    u8 field_18[48]; //0x18-0x47
    u8 pre_attacks_bank_counter; //0x48
    u8 field_49; //0x49
    u8 money_multiplier; //0x4A
    u8 field_4B; //0x4B
    u8 switch_in_ability_bank_counter; //0x4C
    u8 field_4D[7]; //0x4D-0x53
    u8 field_54; //0x54
    u8 field_55; //0x55
    u8 field_56; //0x56
    u8 field_57; //0x57
    u8 field_58[4];
    u8 field_5C[35];
    u8 castform_switch_form; //0x7F
    u8 chosen_move_position[4]; //0x80
    u8 field_84[13]; //0x84-0x90
    u8 absent_bank_flags_prev_turn; //0x91
    u8 field_92[6]; //0x92-0x97
    u16 mirror_moves_pbs[4]; //0x98-0x9F
    u8 field_A0[18]; //0xA0-0xB1
    u8 synchronize_effect_chooser; //0xB2
    u8 field_B3[5];
    u16 used_held_items[4]; //0xB8-0xBF
    u8 field_C0[8]; //0xC0-0xC7
    u16 choiced_move[4]; //0xC8-0xCF (checked in cmd49)
    u16 changed_held_items[4]; //0xD0-0xD8 (later written to battlestruct in cmd49)
    u8 intimidate_user; //0xD8
    u8 switch_in_item_bank_counter; //0xD9
    u8 field_DA; //0xDA
    u8 field_DB; //0xDB
    u8 field_DC; //0xDC
    u8 field_DD; //0xDD
    u8 field_DE; //0xDE
    u8 field_DF; //0xDF
    struct mirror_move_set_per_bank mirror_move_set_pbs[4]; //0xE0-0xFF
    u8 field_100[162]; //0x100-0x1A1
    u8 battle_load_weather_from_map_flag; //0x1A2
    u8 atk_canceller_state_tracker; //0x1A3
    u8 field_1A4[240]; //0x1A4-0x293
    u8 switchout_index[4]; //0x294-0x297
    u8 field_298[11];
    u8 field_2A3;
};

struct battle_stuff_ptr{
    struct battle_stuff *ptr;
};

extern struct battle_stuff_ptr battle_stuff_ptr;

struct special_status{
    u8 statloweringflag : 1;
    u8 lightning_rod_redirected : 1;
    u8 restored_bank_sprite: 1;
    u8 intimidated_a_poke : 1;
    u8 traced : 1;
    u8 flag20 : 1;
    u8 flag40 : 1;
    u8 focus_banded : 1;
    u8 field1[3];
    u32 moveturn_losthp;
    u32 moveturn_losthp_physical;
    u32 moveturn_losthp_special;
    u8 moveturn_physical_bank;
    u8 moveturn_special_bank;
    u8 field12;
    u8 field13;
};

extern struct special_status special_statuses[4];

struct status_3{
    u32 leech_seed_hp_receiver : 2; // 2 bits
    u32 leech_seed : 1; //4
    u32 always_hits : 2; //x8 | x10
    u32 perish_song : 1; //x20
    u32 on_air : 1; //x40
    u32 underground : 1;//80
    u32 minimized : 1; //x100
    u32 charged_up : 1; //x200
    u32 rooted : 1; //x400
    u32 yawn : 2; //x800 || x1000
    u32 imprision : 1; //x2000
    u32 grudge : 1; //x4000
    u32 unkown_no_crit : 1; //x8000
    u32 mud_sport : 1; //x10 000
    u32 watersport : 1; //x20 000
    u32 underwater : 1; //x40 000
    u32 switchinlock : 1; //x80 000
    u32 unburden : 1; //x100 000 (previously trace)
    u32 phantomforce : 1; //x200 000
};

extern struct status_3 status3[4];

struct disable_struct{
    u8 field1 [4];
    u16 disabled_move;
    u16 encored_move;
    u8 protect_endure_effect;
    u8 stockpile_counter;
    u8 substitute_hp;
    u8 disable_timer;
    u8 encored_index;
    u8 fieldD;
    u8 encore_timer;
    u8 perishsong_timer;
    u8 fury_cutter_timer;
    u8 rollout_timer;
    u8 charge_timer;
    u8 taunt_timer;
    u8 bank_preventing_escape;
    u8 always_hits_bank;
    u8 is_first_turn;
    u8 field17;
    s8 truant_counter;
    u8 recharge_counter;
    u8 field1A;
    u8 field1B;
};

extern struct disable_struct disable_structs[4];

struct protect_struct{
    u8 flag0_protect : 1;
    u8 flag0_endure : 1;
    u8 flag0_onlystruggle : 1;
    u8 flag0_helpinghand : 1;
    u8 flag0_bouncemove : 1;
    u8 flag0_stealmove : 1;
    u8 flag0_unknown: 1;
    u8 flag0_prlz_immobility: 1;
    u8 flag1_confusion_self_damage: 1;
    u8 flag1_noteffective: 1;
    u8 flag1_chargingturn: 1; //dive, dig etc.
    u8 flag1_smokeballflee: 1;
    u8 flag1_runaway_flee: 1;
    u8 flag1_used_imprisoned_move: 1;
    u8 flag1_love_immobility: 1;
    u8 flag1_used_disabled_move: 1;
    u8 flag2_used_taunted_move: 1;
    u8 flag2_unknown: 1;
    u8 flag2_flinch_immobility : 1;
    u8 flag2_notfirststrike : 1;
    u8 flag2_free: 4;
    u8 field3;
    u32 physical_damage;
    u32 special_damage;
    u8 counter_target;
    u8 mirrorcoat_target;
    u16 fieldE;
};

extern struct protect_struct protect_structs[4];

struct flags_ability{
    u32 flag1_flashfire : 1;
};

struct ability_flags{
    struct flags_ability flags_ability[4];
};

struct tai_state{
    u8 phase;
    u8 moveset_index;
    u16 curr_move;
    s8 score[4];
    u32 var;
    u32 scripts_to_run;
    u8 move_state_flags;
    u8 curr_script;
};

struct battle_history{
    u16 poke1_used_moves[4];
    u8 field_8[24];
    u16 poke2_used_moves[4];
    u8 field_28[24];
    u8 ability[4];
    u8 item[4];
};

struct b_resources_field0{
    u32 field0;
    struct ability_flags *ability_flags_ptr;
    u32 battlescript_stack;
    u32 battlescript_execute_stack;
    u32 field10;
    struct tai_state *tai_state;
    struct battle_history *battle_history;
};

struct battlescript_stack{
    u8 stack_data[32];
    u8 stack_height;
    u8 undefined[3];
};

struct battle_resources{
    struct b_resources_field0 *field0_ptr;
    u32 field4;
    struct battlescript_stack *battlescript_stack;
};

struct b_resources_ptr{
    struct battle_resources *ptr;
};

extern struct b_resources_ptr battle_resources_ptr;

struct b_communication{
    u8 field0;
    u8 field1;
    u8 field2;
    u8 move_effect;
    u8 field4;
    u8 multistring_chooser;
    u8 field6;
    u8 is_message_displayed;
};

extern struct b_communication battle_communication_struct;

struct move_outcome{
    u8 missed : 1;
    u8 super_effective : 1;
    u8 not_very_effective : 1;
    u8 not_affected : 1;
    u8 one_hit_ko : 1;
    u8 failed : 1;
    u8 endured : 1;
    u8 hanged_on_using_item : 1;
    u8 sturdied : 1;
};

extern struct move_outcome move_outcome;

//temp
u32 hitmarker;
#define HITMARKER_NO_ANIMATIONS 0x80
#define HITMARKER_IGNORE_SUBSTITUTE 0x100
#define HITMARKER_NO_ATTACKSTRING 0x200 //used in dual foe and user defrosting moves
#define HITMARKER_NO_ATTACKSTRING2 0x400
#define HITMARKER_NO_PPDEDUCT 0x800
#define HITMARKER_PURSUIT_TRAP 0x1000
#define HITMAKRER_IGNORE_SAFEGUARD 0x2000
#define HITMARKER_FLEE 0x8000
#define HITMARKER_IGNORE_ON_AIR 0x10000
#define HITMERKER_IGNORE_UNDERGROUND 0x20000
#define HITMARKER_IGNORE_UNDERWATER 0x40000
#define HITMARKER_IMMOBILE_DUE_TO_STATUS 0x80000
#define HITMARKER_OBEYS 0x2000000
#define HITMARKER_FAINTED(bank) (bits_table[bank]>>0x1C)

struct side_affecting_hword{
    u16 reflect_on : 1;
    u16 light_screen_on : 1;
    u16 unkown1 : 2;
    u16 spikes_on : 1;
    u16 safeguard_on : 1;
    u16 unkown2 : 2;
    u16 mist_on : 1;
    u16 spikes_damage_done : 1;
};

extern struct side_affecting_hword side_affecting_halfword[2];

struct prop_flags{
    u8 makes_contact : 1;//1
    u8 affected_by_protect : 1;//2
    u8 affected_by_magic_coat : 1;//4
    u8 affected_by_snatch : 1;//8
    u8 affected_by_mirrormove :1;//x10
    u8 affected_by_kingsrock :1;//x20
    u8 raised_crit_ratio :1;//x40
    u8 unused_bit : 1;//x80
};

union move_flags{
    u8 int_flag;
    struct prop_flags flags;
};

struct move_info{
    u8 script_id;
    u8 base_power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 effect_chance;
    u8 target;
    s8 priority;
    union move_flags move_flags;
    u8 arg1;
    u8 split;
    u8 arg2;
};

//extern struct move_info move_info;

struct fraction_buff2{
    u8 numerator;
    u8 denumenator;
    u16 padding;
};

extern struct fraction_buff2 fraction_stat_buffs2[0xC];

struct side_timer{
    u8 reflect_timer;
    u8 reflect_bank;
    u8 lightscreen_timer;
    u8 lightscreen_bank;
    u8 mist_timer;
    u8 mist_bank;
    u8 safeguard_timer;
    u8 safeguard_bank;
    u8 followme_timer;
    u8 followme_target;
    u8 spikes_amount;
    u8 fieldB;
};

extern struct side_timer side_timers[2];

struct battle_flags{
    u32 double_battle : 1; //1
    u32 link : 1; //2
    u32 wild : 1; //4
    u32 trainer : 1; //8
    u32 save_birch : 1; //0x10
    u32 flagx20 : 1; //0x20
    u32 flagx40 : 1; //0x40
    u32 safari : 1; //0x80
    u32 flagx100 : 1; //0x100
    u32 wally : 1; //0x200
    u32 roaming : 1; //0x400
    //more to come if needed
};

extern struct battle_flags battle_flags;

struct pokemon{
	u32 PID;
	u32 OTID;
	char name[10];
	u16 language;
	u8 OT_name[7];
	u8 markings;
	u16 checksum;
	u16 padding_maybe;
	u8 data[48];
	u32 ailment;
	u8 level;
	u8 pokerus;
	u16 current_hp;
	u16 total_hp;
	u16 attack;
	u16 defense;
	u16 speed;
	u16 sp_attack;
	u16 sp_defense;
};

extern struct pokemon party_opponent[6];
extern struct pokemon party_player[6];

struct battle_buffer{
    u8 command_id;
    u8 args[511];
};

extern struct battle_buffer battle_bufferA[4];
extern struct battle_buffer battle_bufferB[4];

struct task{
    void* function;
    u8 id;
    u8 previous;
    u8 next;
    u8 priority;
    u16 private[16];
};

extern struct task tasks[16];

struct sprite{
    u8 y;
    u8 flags1;
    u8 x;
    u8 msb_of_x_and_flags2;
    u16 attr2;
    u16 rotscaleinfo;
};

struct coords16{
    u16 x;
    u16 y;
};

struct coords8{
    u8 x;
    u8 y;
};

struct moveanim_priv{
    u16 private[8];
};

union obj_privates{
    struct moveanim_priv moveanim_priv;
};

struct object{
    struct sprite final_oam;
    void* anim_table;
    void* gfx_table;
    void* rotscale_table;
    void* template;
    u32 field_18;
    void* callback;
    struct coords16 pos1;
    struct coords16 pos2;
    struct coords8 pos_neg_center;
    u8 anim_number;
    u8 anim_frame;
    u8 anim_delay_countdown;
    u8 anim_unkown_counter;
    union obj_privates privates;
    u8 in_use : 1;
    u8 flag2 : 1;
    u8 invisible : 1;
    u8 flags : 5;
    u8 bitfield2;
    u16 anim_data_offset;
    u8 field_42;
    u8 y_height_related;
};

extern struct object objects[64];

struct poke_basestats{
    u8 base_hp;
    u8 base_atk;
    u8 base_def;
    u8 base_spd;
    u8 base_spatk;
    u8 base_spdef;
    u8 type1;
    u8 type2;
    u8 catch_rate;
    u8 exp_yield;
    u16 evs_hp : 2;
    u16 evs_atk : 2;
    u16 evs_def : 2;
    u16 evs_spd : 2;
    u16 evs_spatk : 2;
    u16 evs_spdef : 2;
    u16 unused : 4;
    u16 item1;
    u16 item2;
    u8 gender_ratio;
    u8 hatching;
    u8 friendship;
    u8 exp_curve;
    u8 egg_group1;
    u8 egg_group2;
    u8 ability1;
    u8 ability2;
    u8 safari_flee_rate;
    u8 dex_colour;
    u8 padding1;
    u8 padding2;
};

extern struct poke_basestats pokemon_table[412];

#endif /* B_STRUCTS */
