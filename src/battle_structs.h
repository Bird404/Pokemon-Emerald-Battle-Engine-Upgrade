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

struct battle_participant {
    u16 poke_species;
    u16 atk;
    u16 def;
    u16 spd;
    u16 sp_atk;
    u16 sp_def;
    u16 moves[4];
    u32 iv_word;
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
    u32 status2;
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
    u16 field29;
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
    u8 field0[14];
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

struct battle_stuff{
    u8 field0[19];
    u8 dynamic_move_type;
    u8 field_14[54];
    u8 money_multiplier;
    u8 field_4B[9];
    u8 field_54;
    u8 field_55[42];
    u8 castform_switch_form;
    u8 chosen_move_position[4];
    u8 field_84[52];
    u16 used_held_items[4];
};

struct battle_stuff_ptr{
    struct battle_stuff *ptr;
};

extern struct battle_stuff_ptr battle_stuff_ptr;

struct special_status{
    u8 statloweringflag : 1;
    u8 lightning_rod_redirected : 1;
    u8 flag4: 1;
    u8 intimidated_a_poke : 1;
    u8 traced : 1;
    u8 flag20 : 1;
    u8 flag40 : 1;
    u8 focus_banded : 1;
    u8 field1[7];
    u32 moveturn_losthp_physical;
    u32 moveturn_losthp_special;
    u8 moveturn_physical_bank;
    u8 moveturn_special_bank;
    u8 field12;
    u8 field13;
};

extern struct special_status special_statuses[4];

struct status_3{
    u32 bit0 : 1; //1
    u32 bit2 : 1; //2
    u32 leech_seed : 1; //4
    u32 always_hits_unkown : 1; //x8
    u32 always_hits : 1; //x10
    u32 perish_song : 1; //x20
    u32 on_air : 1; //x40
    u32 underground : 1;//80
    u32 minimized : 1; //x100
    u32 charged_up : 1; //x200
    u32 rooted : 1; //x400
    u32 yawn_sleep : 1; //x800
    u32 yawn_next_turn : 1; //x1000
    u32 imprision : 1; //x2000
    u32 grudge : 1; //x4000
    u32 unkown_no_crit : 1; //x8000
    u32 mud_sport : 1; //x10 000
    u32 watersport : 1; //x20 000
    u32 underwater : 1; //x40 000
    u32 intimidated_a_poke : 1;
    u32 traced : 1;
};

extern struct status_3 status3[4];

struct disable_struct{
    u8 field1 [3];
    u16 disabled_move;
    u16 encored_move;
    u8 protect_endure_effect;
    u8 stockpile_counter;
    u8 fieldA;
    u8 disable_timer;
    u8 fieldC;
    u8 fieldD;
    u8 encore_timer;
    u8 perishsong_timer;
    u8 fury_cutter_timer;
    u8 rollout_timer;
    u8 charge_timer;
    u8 taunt_timer;
    u8 field14;
    u8 always_hits_bank;
    u8 is_first_turn;
    u8 field17;
    s8 truant_counter;
    u8 field19[3];
};

extern struct disable_struct disable_structs[4];

struct protect_struct{
    u8 flag1_protect : 1;
    u8 flag1_endure : 1;
    u8 flag1_onlystruggle : 1;
    u8 flag1_helpinghand : 1;
    u8 flag1_bouncemove : 1;
    u8 flag1_stealmove : 1;
    u8 field1;
    u8 flag2_notfirststrike : 1;
    u8 field3;
    u32 physical_damage;
    u32 special_damage;
    u32 fieldC;
};

extern struct protect_struct protect_structs[4];

struct flags_ability{
    u32 flag1_flashfire : 1;
};

struct ability_flags{
    struct flags_ability flags_ability[4];
};

struct b_resources_field0{
    u32 field0;
    struct ability_flags *ability_flags_ptr;
};

struct battle_resources{
    struct b_resources_field0 *field0_ptr;
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
};

extern struct move_outcome move_outcome;

//temp
u32 hitmarker;
#define HITMAKRER_IGNORE_SAFEGUARD 0x2000

struct side_affecting_hword{
    u16 reflect_on : 1;
    u16 light_screen_on : 1;
    u16 unkown1 : 2;
    u16 spikes_on : 1;
    u16 safeguard_on : 1;
    u16 unkown2 : 2;
    u16 mist_on : 1;
};

extern struct side_affecting_hword side_affecting_halfword[2];

#endif /* B_STRUCTS */
