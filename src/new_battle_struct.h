#ifndef NEW_STRUCT
#define NEW_STRUCT

#include "types.h"

struct bank_affecting{
    u8 embargo : 3;
    u8 electrify : 1;
    u8 telekinesis: 3;
    u8 magnet_rise : 3;
    u8 heal_block : 3;
    u8 aqua_ring : 1;
    u8 powder : 1;
    u8 smacked_down : 1;
    u8 quashed : 1;
    u8 just_switched_in : 1;
    u8 miracle_eyed : 1;
    u8 eaten_berry : 1;
    u8 sunshine_form : 1;
    u8 cherrim_transformed : 1;
    u8 gastro_acided : 1;
    u8 spiky_shield : 1;
    u8 kings_shield : 1;
    u8 sky_drop_attacker : 1;
    u8 sky_drop_target : 1;
    u8 me_first : 1;
    u8 weakness2 : 1;
    u8 entry_message : 1;
    u8 powertrick : 1;
    u8 kingsshield_damage : 1;
    u8 spikyshield_damage : 1;
    u8 grassyterrain_heal : 1;
    u8 slowstart_duration : 3;
    u8 aegislash_form : 2; //0 = not aegi, 1 = defensive, 2 = attacking
    u8 killer_bank : 2;
    u8 same_move_used : 3;
    u8 wrap_bank : 2;
    u8 move_failed : 1;
    u8 type3 : 5;
    u8 stat_lowered : 1;
    u8 roost : 3;
    u8 usedmoves : 4;
    s8 stockpile_def_changes;
    s8 stockpile_sp_def_changes;
    u8 autonomize_uses;
    u8 lastmove_type;
    u16 wish_hp;
    u32 transform_tid;
    u8 illusion_on : 1;
    u8 illusion_hit : 1;
    u8 illusion_ball : 6;
    u8 illusion_nick[10];
    u8 transform_pal_changed : 1;
    u8 skips_turn : 1;
    u8 caught : 1;
};

struct side_affecting{
    u8 sticky_web : 1;
    u8 sticky_web_done : 1;
    u8 toxic_spikes_psn : 1;
    u8 toxic_spikes_badpsn : 1;
    u8 toxic_spikes_done : 1;
    u8 stealthrock : 1;
    u8 stealthrock_done : 1;
    u8 lucky_chant : 3;
    u8 lucky_chant_bank : 2;
    u8 tailwind : 3;
    u8 tailwind_bank : 2;
    u8 wide_guard : 1;
    u8 quick_guard : 1;
    u8 crafty_shield : 1;
    u8 swamp_spd_reduce : 3;
    u8 sea_of_fire : 3;
    u8 rainbow : 3;
    u8 mat_block : 1;
    u8 lunardance : 1;
    u8 lunardance_done : 1;
    u8 ally_fainted_last_turn : 2;
    u8 pledge_effect : 2; //1 for grass, 2 for fire , 3 for water
};

struct field_affecting{
    u32 trick_room : 3;
    u32 wonder_room : 3;
    u32 magic_room : 3;
    u32 grassy_terrain : 3;
    u32 electic_terrain : 3;
    u32 misty_terrain : 3;
    u32 ion_deluge : 3;
    u32 gravity : 3;
    u32 echo_voice_counter : 3;
    u32 round_chosen : 1;
    u32 fairy_lock : 2;
};

struct various{
    u8 eaten_berry_player : 6;
    u8 eaten_berry_opponent : 6;
    u8 active_bank : 2;
    u8 cmd49_safeattacker_bank: 2;
    u8 inverse_battle : 1;
    u8 fishing_battle : 1;
    u8 magicbounce : 1;
    u8 stormdrain : 1;
    u16 var1;
    u16 var2;
    u16 recently_used_item;
    u16 previous_move;
    u16 accumulated_damage;
    u8 move_primary_effect;
    u8 parental_bond_mode: 2;
    u8 life_orbed : 1;
    u8 sheerforce_bonus : 1;
    u8 ate_bonus : 1;
    u8 gem_boost : 1;
    u8 happyhour_bonus : 1;
    u8 berry_damage_redux : 1;
    u8 trigger_symbiosis: 1;
    u8 switch_in_cos_switch : 1; //and not because a poke fainted or it is the first one
    u8 protean_msg : 1;
    u8 recorded_mega : 1;
    u8 sent_in_player : 6;
    u8 returns_item : 6;
    u8 gravity_levitate : 1;
    #if ITEM_SWAP == false
    u16 original_held_item[6];
    u8 returns_swap : 6;
    #endif // ITEMS_SWAP
};

#define PBOND_PARENT 2
#define PBOND_CHILD 1
#define PBOND_DONT_SET 3

struct mega_related
{
    u32 user_trigger: 2; // 0x0 for not set, //0x1 for stone, //0x2 for wish
    u32 ally_trigger: 2;
    u32 evo_happened_pbs: 4;
    u32 party_mega_check: 6;
    u32 ai_party_mega_check: 6;
    u32 trigger_id : 8;
    u8 indicator_id_pbs[4];
    u8 link_indicator[4];
};

struct tai_related{
    u16 saved_species;
    u16 saved_item;
    u8 saved_ability;
    u16 var2;
};

struct new_battle_struct{
    struct bank_affecting bank_affecting[4];
    struct side_affecting side_affecting[2];
    struct field_affecting field_affecting;
    struct various various;
    struct mega_related mega_related;
    struct tai_related trainer_AI;
};

extern struct new_battle_struct* new_battlestruct;

#endif /* NEW_STRUCT */
