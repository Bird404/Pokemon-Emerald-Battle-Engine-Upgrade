#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"
#include "static_resources.h"

u8 get_all_item_quality(u8 bank);
u8 find_move_in_table(u16 move, u16 table_ptr[]);

u8 affected_by_substitute(u8 substitute_bank)
{
    if (battle_participants[substitute_bank].status2.substitute)
    {
        if (!(hitmarker & HITMARKER_IGNORE_SUBSTITUTE || disable_structs[substitute_bank].substitute_hp
              || (has_ability_effect(bank_attacker, 0, 1) && battle_participants[bank_attacker].ability_id == ABILITY_INFILTRATOR && bank_attacker != substitute_bank)
              || find_move_in_table(current_move, &sound_moves[0])))
        {
            return true;
        }
    }
    return false;;
}

void final_damagecalc_cmd7()
{
    battlescripts_curr_instruction++;
    if (damage_loc == 0)
        damage_loc = 1;

    if (!affected_by_substitute(bank_target))
    {
        u16 target_hp = battle_participants[bank_target].current_hp;
        if ((current_move == MOVE_FALSE_SWIPE || current_move == MOVE_HOLD_BACK) && damage_loc > target_hp && !(move_outcome.failed || move_outcome.missed || move_outcome.not_affected))
        {
            damage_loc = target_hp - 1;
        }
        else if (battle_participants[bank_target].ability_id == ABILITY_STURDY && has_ability_effect(bank_target, 1, 1) && damage_loc > target_hp && target_hp == battle_participants[bank_target].max_hp)
        {
            damage_loc = target_hp - 1;
            move_outcome.endured = 1;
        }
        else
        {
            switch (get_item_effect(bank_target, 1))
            {
            case ITEM_EFFECT_FOCUSSASH:
                if (damage_loc > target_hp && target_hp == battle_participants[bank_target].max_hp)
                {
                    damage_loc = target_hp - 1;
                    move_outcome.hanged_on_using_item = 1;
                    last_used_item = battle_participants[bank_target].held_item;
                    battle_participants[bank_target].held_item = 0;
                    active_bank = bank_target;
                    prepare_setattributes_in_battle(0, 2, 0, 2, &battle_participants[bank_target].held_item);
                    mark_buffer_bank_for_execution(bank_target);
                }
                break;
            case ITEM_EFFECT_FOCUSBAND:
                if (damage_loc > target_hp && (__umodsi3(rng(), 100) + 1) < get_all_item_quality(bank_target))
                {
                    damage_loc = target_hp - 1;
                    move_outcome.hanged_on_using_item = 1;
                    last_used_item = battle_participants[bank_target].held_item;
                }
                break;
            }
        }
    }
    return;
}
