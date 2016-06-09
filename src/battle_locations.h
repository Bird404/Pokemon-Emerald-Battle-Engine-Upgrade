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
u8 turn_order;
u8 battle_flags;
u16 battle_team_id_by_side[4];
u16 previously_used_move[4];
u8 another_active_bank;

u32 poison_status_flag;
u32 sleep_status_flag;
u32 paralysis_status_flag;
u32 burn_status_flag;
u32 freeze_status_flag;

#endif /* B_LOCATIONS */
