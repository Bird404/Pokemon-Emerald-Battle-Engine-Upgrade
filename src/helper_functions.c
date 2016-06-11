#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"

extern struct move_info move_table[1024];
extern void *changetargetstat_bs;
extern void *healblock_end_bs;
extern void *encore_end_bs;
extern void *disable_end_bs;
extern void *weaknesspolicyspattack;
extern void *weaknesspolicyattack;

u8 sample_text[] = {0xDD, 0xFF};
u8 snowwarning_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0, 0xFD, 0x1A, 0xFE, 0xEB, 0xDC, 0xDD, 0xE4, 0xE4, 0xD9, 0xD8, 0x00, 0xE9, 0xE4, 0x00, 0xD5, 0x00, 0xDC, 0xD5, 0xDD, 0xE0, 0xE7, 0xE8, 0xE3, 0xE6, 0xE1, 0xAB, 0xFF};
u8 extreme_sun_activation_text[] = {0xCE, 0xDC, 0xD9, 0x00, 0xE7, 0xE9, 0xE2, 0xE0, 0xDD, 0xDB, 0xDC, 0xE8, 0x00, 0xE8, 0xE9, 0xE6, 0xE2, 0xD9, 0xD8, 0xFE, 0xD9, 0xEC, 0xE8, 0xE6, 0xD9, 0xE1, 0xD9, 0xE0, 0xED, 0x00, 0xDC, 0xD5, 0xE6, 0xE7, 0xDC, 0xAB, 0xFF};
u8 heavyrain_activation_text[] = {0xBB, 0x00, 0xDC, 0xD9, 0xD5, 0xEA, 0xED, 0x00, 0xE6, 0xD5, 0xDD, 0xE2, 0x00, 0xD6, 0xD9, 0xDB, 0xD5, 0xE2, 0x00, 0xE8, 0xE3, 0x00, 0xDA, 0xD5, 0xE0, 0xE0, 0xAB, 0xFF};
u8 mysticalaircurrent_activation_text[] = {0xBB, 0x00, 0xE1, 0xED, 0xE7, 0xE8, 0xD9, 0xE6, 0xDD, 0xE3, 0xE9, 0xE7, 0x00, 0xD5, 0xDD, 0xE6, 0x00, 0xD7, 0xE9, 0xE6, 0xE6, 0xD9, 0xE2, 0xE8, 0xFE, 0xDD, 0xE7, 0x00, 0xE4, 0xE6, 0xE3, 0xE8, 0xD9, 0xD7, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xC0, 0xE0, 0xED, 0xDD, 0xE2, 0xDB, 0xAE, 0xE8, 0xED, 0xE4, 0xD9, 0x00, 0xCA, 0xE3, 0xDF, 0x1B, 0xE1, 0xE3, 0xE2, 0xAB, 0xFF};
u8 forewarn_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0, 0xFD, 0x1A, 0xFE, 0xD5, 0xE0, 0xD9, 0xE6, 0xE8, 0xD9, 0xD8, 0, 0xDD, 0xE8, 0, 0xE8, 0xE3, 0x0, 0xFD, 0, 0xAB, 0xFF};
u8 slowstart_text[] = {0xFD, 0x13, 0x0, 0xD7, 0xD5, 0xE2, 0xB4, 0xE8, 0x00, 0xDB, 0xD9, 0xE8, 0x00, 0xDD, 0xE8, 0x00, 0xDB, 0xE3, 0xDD, 0xE2, 0xDB, 0xAB, 0xFF};
u8 anticipation_text[] = {0xFD, 0x13, 0, 0xE7, 0xDC, 0xE9, 0xD8, 0xD8, 0xD9, 0xE6, 0xD9, 0xD8, 0x00, 0xEB, 0xDD, 0xE8, 0xDC, 0x00, 0xD5, 0xE2, 0xE8, 0xDD, 0xD7, 0xDD, 0xE4, 0xD5, 0xE8, 0xDD, 0xE3, 0xE2, 0xAB ,0xFF};
u8 dryskin_damage_text[] = {0xFD, 15, 0xB4, 0xE7, 0, 0xFD, 24, 0x0, 0xE1, 0xD5, 0xDF, 0xD9, 0xE7, 0x00, 0xDD, 0xE7, 0xFE, 0xEA, 0xE9, 0xE0, 0xE2, 0xD9, 0xE6, 0xD5, 0xD6, 0xE0, 0xD9, 0x00, 0xE8, 0xE3, 0x00, 0xE7, 0xE9, 0xE2, 0xAB, 0xFF};
u8 solarpower_text[] = {0xFD, 15, 0xB4, 0xE7, 0, 0xFD, 24, 0x0, 0xE1, 0xD5, 0xDF, 0xD9, 0xE7, 0x0, 0xDD, 0xE8, 0x0, 0xD8, 0xE6, 0xD5, 0xEB, 0x0, 0xE4, 0xE3, 0xEB, 0xD9, 0xE6, 0xFE, 0xDA, 0xE6, 0xE3, 0xE1, 0x0, 0xE8, 0xDC, 0xD9, 0x0, 0xE7, 0xE9, 0xE2, 0x0, 0xDD, 0xE2, 0x00, 0xD9, 0xEC, 0xD7, 0xDC, 0xD5, 0xE2, 0xDB, 0xD9, 0x00, 0xDA, 0xE3, 0xE6, 0x00, 0xE0, 0xDD, 0xDA, 0xD9, 0xAB, 0xFF};
u8 harvest_text[] = {0xFD, 15, 0, 0xDC, 0xD5, 0xE6, 0xEA, 0xD9, 0xE7, 0xE8, 0xD9, 0xD8, 0x00, 0xE3, 0xE2, 0xD9, 0, 0xFD, 22, 0xAB, 0xFF};
u8 healer_text[] = {0xFD, 15, 0, 0xB4, 0xE7, 0, 0xFD, 24, 0, 0xD7, 0xE9, 0xE6, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0x00, 0xE4, 0xD5, 0xE6, 0xE8, 0xE2, 0xD9, 0xE6, 0xB4, 0xE7, 0xFE, 0xFD, 0x0, 0xAB, 0xFF};
u8 pickup_text[] = {0xFD, 15, 0, 0xDA, 0xE3, 0xE9, 0xE2, 0xD8, 0x00, 0xE3, 0xE2, 0xD9, 0x00, 0xFD, 22, 0xAB, 0xFF};
u8 moldbreaker_text[] = {0xFD, 0x13, 0, 0xD6, 0xE6, 0xD9, 0xD5, 0xDF, 0xE7, 0x00, 0xE8, 0xDC, 0xD9, 0x00, 0xE1, 0xE3, 0xE0, 0xD8, 0xAB, 0xFF};
u8 turboblaze_text[] = {0xFD, 0x13, 0, 0xDD, 0xE7, 0x00, 0xE6, 0xD5, 0xD8, 0xDD, 0xD5, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0x00, 0xD6, 0xE0, 0xD5, 0xEE, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0xE9, 0xE6, 0xD5, 0xAB, 0xFF};
u8 terravolt_text[] = {0xFD, 0x13, 0, 0xDD, 0xE7, 0x00, 0xE6, 0xD5, 0xD8, 0xDD, 0xD5, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0x00, 0xD6, 0xE9, 0xE6, 0xE7, 0xE8, 0xDD, 0xE2, 0xDB, 0x00, 0xD5, 0xE9, 0xE6, 0xD5, 0xAB, 0xFF};
u8 downloadatk_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0x0, 0xFD, 0x1A, 0, 0xE6, 0xD5, 0xDD, 0xE7, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0xFE, 0xBB, 0xE8, 0xE8, 0xD5, 0xD7, 0xDF, 0xAB, 0xFF};
u8 downloadspatk_text[] = {0xFD, 0x13, 0xB4, 0xE7, 0x0, 0xFD, 0x1A, 0, 0xE6, 0xD5, 0xDD, 0xE7, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0xFE, 0xCD, 0xE4, 0xAD, 0, 0xBB, 0xE8, 0xE8, 0xD5, 0xD7, 0xDF, 0xAB, 0xFF};
u8 absorbabilityboost_text[] = {0xFD, 0x10, 0xB4, 0xE7, 0, 0xFD, 0x19, 0, 0xE6, 0xD5, 0xDD, 0xE7, 0xD9, 0xD8, 0x00, 0xDD, 0xE8, 0xE7, 0xFE, 0xFD, 0x0, 0xAB ,0xFF};
u8 absorbabilityimmune_text[] = {0xFD, 0x10, 0xB4, 0xE7, 0, 0xFD, 0x19, 0, 0xE1, 0xD5, 0xDF, 0xD9, 0xE7, 0x00, 0xDD, 0xE8, 0xFE, 0xDD, 0xE1, 0xE1, 0xE9, 0xE2, 0xD9, 0x00, 0xE8, 0xE3, 0x00, 0xFD, 0x00, 0xAE, 0xE8, 0xED, 0xE4, 0xD9, 0x00, 0xE1, 0xE3, 0xEA, 0xD9, 0xE7, 0xAB, 0xFF};
u8 userteam_text[] = {Y_, o_, u_, r_, 0, t_, e_, a_, m_, Termin};
u8 foeteam_text[] = {T_, h_, e_, 0, f_, o_, e_, Apos, s_, 0, t_, e_, a_, m_, Termin};
//u8 userteam_lc_text[] = {y_, o_, u_, r_, 0, t_, e_, a_, m_, Termin};
//u8 foeteam_lc_text[] = {t_, h_, e_, 0, f_, o_, e_, Apos, s_, 0, t_, e_, a_, m_, Termin};
u8 aftermath_text[] = {0xFD, 15, 0, 0xDD, 0xE7, 0x0, 0xDC, 0xE9, 0xE6, 0xE8, 0x00, 0xD6, 0xED, 0xFE, 0xFD, 16, 0xB4, 0xE7, 0, 0xFD, 25, 0xAB, 0xFF};
u8 pickpocket_text[] = {0xFD, 16, 0, 0xE7, 0xE8, 0xE3, 0xE0, 0xD9, 0, 0xFD, 15, 0xB4, 0xE7, 0xFE, 0xFD, 22, 0xAB, 0xFF};
u8 mummy_text[] = {0xFD, 15, 0xB4, 0xE7, 0, 0xD5, 0xD6, 0xDD, 0xE0, 0xDD, 0xE8, 0xED, 0xFE, 0xD6, 0xD9, 0xD7, 0xD5, 0xE1, 0xD9, 0, 0xFD, 24, 0xAB, 0xFF};
u8 target_ability[] = {0xFD, 16, 0xB4, 0xE7, 0, 0xFD, 25, 0xAB, 0xFF};
u8 cursedbody_text[] = {0xFD, 16, 0xB4, 0xE7, 0, 0xFD, 25, 0, 0xD8, 0xDD, 0xE7, 0xD5, 0xD6, 0xE0, 0xD9, 0xD8, 0xFE, 0xFD, 15, 0xB4, 0xE7, 0, 0xFD, 0, 0xAB, 0xFF};
u8 drastically_text[] = {0xD8, 0xE6, 0xD5, 0xE7, 0xE8, 0xDD, 0xD7, 0xD5, 0xE0, 0xE0, 0xED, 0x0, 0xFF};
u8 pressure_text[] = {BuffCharac, 0xF, Space, i_, s_, Space, e_, x_, e_, r_, t_, i_, n_, g_, JumpLine, i_, t_, s_, Space, P_, r_, e_, s_, s_, u_, r_, e_, Exclam, Termin};
u8 unnerve_text[] = {0xFD, 0x0, 0, i_, s_, 0, t_, o_, o_, 0, n_, e_, r_, v_, o_, u_, s_, 0xFE, t_, o_, 0, e_, a_, t_, 0, B_, e_, r_, r_, i_, e_, s_, Exclam, Termin};
u8 aurabreak_text[] = {0xFD, 0xF, 0, r_, e_, v_, e_, r_, s_, e_, d_, 0, a_, l_, l_, 0, o_, t_, h_, e_, r_, 0xFE, P_, o_, k_, Poke_e, m_, o_, n_, Apos, s_, 0, a_, u_, r_, a_, s_, Exclam, 0xFF};
u8 fairyaura_text[] = {BuffCharac, 0xF, Space, i_, s_, Space, r_, a_, d_, i_, a_, t_, i_, n_, g_, JumpLine, a_, Space, F_, a_, i_, r_, y_, Space, A_, u_, r_, a_, Exclam, Termin};
u8 darkaura_text[] = {BuffCharac, 0xF, Space, i_, s_, Space, r_, a_, d_, i_, a_, t_, i_, n_, g_, JumpLine, a_, Space, D_, a_, r_, k_, Space, A_, u_, r_, a_, Exclam, Termin};
u8 frisk_text[] = {BuffCharac, 0x13, Space, f_, r_, i_, s_, k_, e_, d_, Space, BuffCharac, 0x10, JumpLine, a_, n_, d_, Space,
                   f_, o_, u_, n_, d_, Space, i_, t_, s_, Space, BuffCharac, 0x16, Exclam, Termin};
u8 hurtbyitem_text[] = {BuffCharac, 15, Space, i_,s_, Space, h_, u_, r_, t_, Space, b_, y_, Space, BuffCharac, 22, Exclam,0xFF};
u8 got_burned_text[] = {BuffCharac, 15, Space, g_, o_, t_, Space, b_, u_, r_, n_, e_, d_, Exclam, 0xFF};
u8 got_badlypoisoned_text[] = {BuffCharac, 15, Space, g_, o_, t_, Space, b_, a_, d_, l_, y_, 0xFE, p_, o_, i_, s_, o_, n_, e_, d_, Exclam, 0xFF};
u8 airballoon_text[] = {BuffCharac, 18, Space, i_, s_, Space, f_, l_, o_, a_, t_, i_, n_, g_, Exclam, 0xFF};
u8 bad_dreams_text[] = {BuffCharac, 0x10, Space, i_, s_, Space, t_, o_, r_, m_, e_, n_, t_, e_, d_, Space, b_, y_, JumpLine, b_, a_, d_, Space, d_, r_, e_, a_, m_, s_, Exclam, Termin};
u8 item_text[] = {BuffCharac, 16, Apos, Space, BuffCharac, 22, Exclam, 0xFF};
u8 rockyhelmet_text[] = {BuffCharac, 15, Space, i_, s_, Space, h_, u_, r_, t_, Space, b_, y_, JumpLine, BuffCharac, 16, Apos, Space, BuffCharac, 22, Exclam, 0xFF};
u8 popped_text[] = {BuffCharac, 16, Apos, Space, BuffCharac, 22, Space, p_, o_, p_, p_, e_, d_, Exclam, 0xFF};
u8 fellinlove_text[] = {BuffCharac, 15, Space, f_,e_,l_,l_, Space, i_, n_, Space, l_, o_, v_, e_, JumpLine, w_, i_, t_, h_, Space, BuffCharac, 16, Exclam, 0xFF};
u8 healblockend_text[] = {H_, e_, a_, l_, Space, B_, l_, o_, c_, k_, Space, f_, o_, r_, BuffCharac, 18, JumpLine, h_, a_, s_, Space, e_, n_, d_, e_, d_, Exclam, 0xFF};

void* new_strings_table[] = {&sample_text, &snowwarning_text, &extreme_sun_activation_text, &heavyrain_activation_text, &mysticalaircurrent_activation_text, &forewarn_text, &slowstart_text, &anticipation_text, &dryskin_damage_text, &solarpower_text, &harvest_text, &healer_text, &pickup_text, &moldbreaker_text, &turboblaze_text, &terravolt_text, &downloadatk_text,
&downloadspatk_text, &absorbabilityboost_text , &absorbabilityimmune_text, &userteam_text/*0x190*/, &foeteam_text/*0x191*/,
&aftermath_text, &pickpocket_text, &mummy_text, &target_ability, &cursedbody_text, &drastically_text, &pressure_text, &unnerve_text, &aurabreak_text, &fairyaura_text, &darkaura_text, &frisk_text, //0x19D
&hurtbyitem_text, &got_burned_text, &got_badlypoisoned_text, &airballoon_text, &bad_dreams_text, &item_text, &rockyhelmet_text, &popped_text, &fellinlove_text, &healblockend_text};

void battle_string_loader(u16 string_id)
{
    string_id -= 0x17C;
    display_string_in_battle(new_strings_table[string_id]);
    return;
}

extern void call_ability_effects();

void apply_burn_animation()
{
    u8 active = active_bank;
    active_bank = bank_attacker;
    new_battlestruct.ptr->various.var1 = 0x10;
    new_battlestruct.ptr->various.var2 = 0;
    prepare_status_animation(0, 0, new_battlestruct.ptr->various.var1);
    mark_buffer_bank_for_execution(bank_attacker);
    active_bank = active;
    return;
}

void change_attacker_item()
{
    active_bank = bank_attacker;
    prepare_setattributes_in_battle(0, 2, 0, 4, &battle_participants[bank_attacker].held_item);
    mark_buffer_bank_for_execution(bank_attacker);
}

void try_to_raise_spd()
{
    if (battle_participants[new_battlestruct.ptr->various.active_bank].spd_buff != 0xC)
    {
        battle_scripting.stat_changer = 0x13;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void try_to_lower_def()
{
    if (battle_participants[new_battlestruct.ptr->various.active_bank].def_buff > 0)
    {
        battle_scripting.stat_changer = 0x92;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void changestatvar1()
{
    if (new_battlestruct.ptr->various.var1)
    {
        battle_scripting.stat_changer = new_battlestruct.ptr->various.var1;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void changestatvar2()
{
    if (new_battlestruct.ptr->various.var2)
    {
        battle_scripting.stat_changer = new_battlestruct.ptr->various.var2;
        battlescript_push();
        battlescripts_curr_instruction = &changetargetstat_bs;
    }
    return;
}

void frisk_target_item()
{   u16 curr_item=battle_participants[bank_target].held_item;
    if (curr_item)
    {
        last_used_item=curr_item;
        b_std_message(0x19D,battle_scripting.active_bank);
        record_usage_of_item(bank, get_item_effect(bank_target, 0));
        battle_communication_struct.is_message_displayed=1;
    }
    else
        battle_communication_struct.is_message_displayed=0;

    return;
}

void set_stat_msg_buffer()
{
    u8 stat=battle_scripting.stat_changer&0xF;
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 5;
    battle_text_buff1[2] = stat;
    battle_text_buff1[3] = 0xFF;
}

void set_type_msg_buffer()
{
    u8 move_type=battle_stuff_ptr.ptr->dynamic_move_type&0x3F;
    if (!move_type)
        move_type = move_table[current_move].type;
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 3;
    battle_text_buff1[2] = move_type;
    battle_text_buff1[3] = 0xFF;
}

void set_team_msg_buffer()
{
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 0;
    if (is_bank_from_opponent_side(battle_scripting.active_bank))
        battle_text_buff1[2] = 0x90;
    else
        battle_text_buff1[2] = 0x91;
    battle_text_buff1[3] = 0x1;
    battle_text_buff1[4] = 0xFF;
}

u32 get_1_8_of_max_hp(u8 bank);

void bad_dreams_damage_calc()
{
    damage_loc=get_1_8_of_max_hp(bank_target);
}

void weaknesspolicy()
{
    if (battle_participants[battle_scripting.active_bank].sp_atk_buff != 0xC)
    {
        battlescript_push();
        battlescripts_curr_instruction = &weaknesspolicyspattack;
    }
    if (battle_participants[battle_scripting.active_bank].atk_buff != 0xC)
    {
        battlescript_push();
        battlescripts_curr_instruction = &weaknesspolicyattack;
    }
    return;
}

void mentalherb()
{
    u8 bank = battle_scripting.active_bank;
    if (disable_structs[bank].disable_timer)
    {
        disable_structs[bank].disable_timer = 0;
        disable_structs[bank].disabled_move = 0;
        battlescript_push();
        battlescripts_curr_instruction = &disable_end_bs;
    }
    if (disable_structs[bank].encore_timer)
    {
        disable_structs[bank].encore_timer = 0;
        disable_structs[bank].encored_move = 0;
        battlescript_push();
        battlescripts_curr_instruction = &encore_end_bs;
    }
    if (disable_structs[bank].taunt_timer)
    {
        disable_structs[bank].taunt_timer = 0;
        battlescript_push();
    }
    if (new_battlestruct.ptr->bank_affecting[bank].heal_block)
    {
        new_battlestruct.ptr->bank_affecting[bank].heal_block = 0;
        new_battlestruct.ptr->bank_affecting[bank].healblock_duration = 0;
        battlescript_push();
        battlescripts_curr_instruction = &healblock_end_bs;
    }
    return;
}

void* callasm_table[] = {&call_ability_effects, &apply_burn_animation, &change_attacker_item, &try_to_lower_def, &try_to_raise_spd,
&changestatvar1, &changestatvar2, &frisk_target_item, &set_stat_msg_buffer, &set_type_msg_buffer, &set_team_msg_buffer, &bad_dreams_damage_calc, &weaknesspolicy, &mentalherb};

void callasm_cmd()
{
    void (*command) (void);
    u8 command_id_ls = read_byte(battlescripts_curr_instruction + 1);
    u8 command_id_ms = read_byte(battlescripts_curr_instruction + 2);
    battlescripts_curr_instruction += 3;
    command = callasm_table[(command_id_ms<<8)+command_id_ls];
    command();
}
