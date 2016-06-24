#ifndef B_LOCATIONS
#define B_LOCATIONS

#include "types.h"

u8 last_used_ability;
u16 last_used_item;
u8 bank_attacker;
u8 bank_target;
u8 bank_partner_atk;
u8 bank_partner_def;
u8 crit_loc;
u8 abilities_by_banks[4];
u16 move_power;
u16 current_move;
u16 last_used_move;
s32 damage_loc;
u8 no_of_all_banks;
u8 battle_text_buff1[0x10];
u8 battle_text_buff2[0x10];
u8 active_bank;
void* battlescripts_curr_instruction;
void* move_anim_cursor;
u8 multihit_counter;
u16 chosen_move_by_banks[4];
u16 dynamic_base_power;
u8 animation_bank_attacker;
u8 animation_bank_target;
u8 turn_order[4];
u16 battle_team_id_by_side[4];
u16 previously_used_move[4];
u16 calling_move_used[4];
u16 current_move_used[4];
u8 attacked_by[4];
u8 another_active_bank;
u8 absent_bank_flags;
u8 battle_outcome;
u8 current_move_position;
u16 move_hit_with_pbs[4];
u16 move_type_hit_with_pbs[4];
u16 locked_move[4];
u16 payday_money;
u32 status_flags_for_move_effects[0x3F];
void* battlescripts_for_moveeffects[0x3F];
u32 hp_dealt;

u32 poison_status_flag;
u32 sleep_status_flag;
u32 paralysis_status_flag;
u32 burn_status_flag;
u32 freeze_status_flag;

#endif /* B_LOCATIONS */
