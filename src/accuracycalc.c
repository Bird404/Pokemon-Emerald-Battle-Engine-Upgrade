#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"

extern struct move_info move_table[1024];
u8 is_of_type(u8 bank, u8 type);
u32 percent_boost(u32 number, u16 percent);
u32 percent_lose(u32 number, u16 percent);
#define MOVE_PHYSICAL 0
#define MOVE_SPECIAL 1
#define MOVE_STATUS 2

u8 accuracy_helper_replacement(u16 move)
{
    u8 done_status = 0;
    if ((status3[bank_target].always_hits && disable_structs[bank_target].always_hits_bank == bank_attacker)
        || (has_ability_effect(bank_attacker, 0, 1) && battle_participants[bank_attacker].ability_id == ABILITY_NO_GUARD) || (has_ability_effect(bank_target, 0, 1) && battle_participants[bank_target].ability_id == ABILITY_NO_GUARD)
        || (current_move == MOVE_TOXIC && is_of_type(bank_attacker, TYPE_POISON))
        || (new_battlestruct.ptr->bank_affecting[bank_target].telekinesis && move_table[current_move].script_id != 70)) //lock-on/mind reader checked, then no guard, always hiting toxic on poison types, then always hitting telekinesis except OHKO moves
    {
        jump_if_move_has_no_effect(7, move);
        done_status = 1;
    }
    else if (((status3[bank_target].on_air || new_battlestruct.ptr->bank_affecting[bank_target].sky_drop_attacker || new_battlestruct.ptr->bank_affecting[bank_target].sky_drop_target) && !(hitmarker & HITMARKER_IGNORE_ON_AIR))
             || (status3[bank_target].underground && !(hitmarker & HITMERKER_IGNORE_UNDERGROUND))
             || (status3[bank_target].underwater && !(hitmarker & HITMARKER_IGNORE_UNDERWATER))
             || status3[bank_target].phantomforce)
    {
        move_outcome.missed = 1;
        jump_if_move_has_no_effect(7, move);
        done_status = 1;
    }
    else if ((weather_abilities_effect() && (battle_weather.flags.heavy_rain || battle_weather.flags.downpour || battle_weather.flags.rain || battle_weather.flags.permament_rain) && (current_move == MOVE_THUNDER || current_move == MOVE_HURRICANE))
             || (move_table[move].accuracy == 0))
    {
        jump_if_move_has_no_effect(7, move);
        done_status = 1;
    }
    hitmarker &= 0xFFF8FFFF; //clearing all above hitmarer flags
    return done_status;
}

void accuracy_calc()
{
    u32 jump_loc = read_word(battlescripts_curr_instruction + 1);
    s16 arg = read_hword(battlescripts_curr_instruction + 5);

    if ((arg + 2) > 1)
    {
        if (!does_protect_affect_move(current_move) && !accuracy_helper_replacement(current_move))
        {
            u8 evs_buff = battle_participants[bank_target].evasion_buff;
            if (new_battlestruct.ptr->field_affecting.gravity)
                evs_buff -= 2;
            if (current_move == MOVE_SACRED_SWORD || current_move == MOVE_CHIP_AWAY || (battle_participants[bank_attacker].ability_id == ABILITY_UNAWARE && has_ability_effect(bank_attacker, 0, 1)))
                evs_buff = 6;
            else if (evs_buff > 6 && (battle_participants[bank_target].status2.foresight || new_battlestruct.ptr->bank_affecting[bank_target].miracle_eyed
                                      || (battle_participants[bank_attacker].ability_id == ABILITY_KEEN_EYE && has_ability_effect(bank_attacker, 0, 1))))
                evs_buff = 6;
            u8 accuracy_buff = battle_participants[bank_attacker].acc_buff;
            if (weather_abilities_effect() && (battle_weather.flags.fog || battle_weather.flags.permament_fog))
                accuracy_buff -= 2;
            if (battle_participants[bank_target].ability_id == ABILITY_UNAWARE && has_ability_effect(bank_target, 1, 1))
                accuracy_buff = 6;
            u8 move_accuracy = move_table[current_move].accuracy;
            if (has_ability_effect(bank_target, 1, 1) && battle_participants[bank_target].ability_id == ABILITY_WONDER_SKIN && move_accuracy > 50)
                move_accuracy = 50;
            else if ((current_move == MOVE_THUNDER || current_move == MOVE_HURRICANE) && weather_abilities_effect() && (battle_weather.flags.sun || battle_weather.flags.harsh_sun || battle_weather.flags.permament_sun))
                move_accuracy = 50;

            s8 buff = accuracy_buff + 6 - evs_buff;
            if (buff < 0)
                buff = 0;
            else if (buff > 0xC)
                buff = 0xC;

            u32 accuracy = __udivsi3(move_accuracy * fraction_stat_buffs2[buff].numerator, fraction_stat_buffs2[buff].denumenator);
            if (has_ability_effect(bank_attacker, 0, 1))
            {
                switch (battle_participants[bank_attacker].ability_id)
                {
                case ABILITY_COMPOUND_EYES:
                    accuracy = percent_boost(accuracy, 30);
                    break;
                case ABILITY_HUSTLE:
                    if (move_table[current_move].split == MOVE_PHYSICAL)
                    {
                        accuracy = percent_lose(accuracy, 20);
                    }
                    break;
                }
            }
            if (ability_battle_effects(13, bank_attacker, ABILITY_VICTORY_STAR, 0, 0))
            {
                accuracy = percent_boost(accuracy, 10);
            }
            if (has_ability_effect(bank_target, 1, 1))
            {
                switch (battle_participants[bank_target].ability_id)
                {
                case ABILITY_SAND_VEIL:
                    if (battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm)
                        accuracy = percent_lose(accuracy, 25);
                    break;
                case ABILITY_SNOW_CLOAK:
                    if (battle_weather.flags.hail || battle_weather.flags.permament_hail)
                        accuracy = percent_lose(accuracy, 25);
                    break;
                case ABILITY_TANGLED_FEET:
                    if (battle_participants[bank_target].status2.confusion)
                        accuracy = percent_lose(accuracy, 20);
                    break;
                }
            }
            if (get_item_effect(bank_target, 1) == ITEM_EFFECT_BRIGHTPOWDER)
                accuracy = percent_lose(accuracy, 10);
            switch (get_item_effect(bank_attacker, 1))
            {
            case ITEM_EFFECT_WIDELENS:
                accuracy = percent_boost(accuracy, 10);
                break;
            case ITEM_EFFECT_ZOOMLENS:
                if (get_bank_turn_order(bank_target) < get_bank_turn_order(bank_attacker))
                    accuracy = percent_boost(accuracy, 20);
                break;
            }

            if (__umodsi3(rng(), 100) + 1 > accuracy)
            {
                move_outcome.missed = 1;
                if (battle_flags.double_battle)
                {
                    if (move_table[current_move].target == 0x8 || move_table[current_move].target == 0x20)
                    {
                        battle_communication_struct.field6 = 2;
                    }
                    else
                    {
                        battle_communication_struct.field6 = 0;
                    }
                }
                check_wonderguard_levitate_damage();
            }
            jump_if_move_has_no_effect(7, current_move);
        }
    }
    else
    {
        if (status3[bank_target].always_hits && arg == 0xFFFF && disable_structs[bank_target].always_hits_bank == bank_attacker)
        {
            battlescripts_curr_instruction += 7;
        }
        else
        {
            if (status3[bank_target].on_air || status3[bank_target].underground || status3[bank_target].underwater || new_battlestruct.ptr->bank_affecting[bank_target].sky_drop_attacker || new_battlestruct.ptr->bank_affecting[bank_target].sky_drop_target)
            {
                battlescripts_curr_instruction = (void*)jump_loc;
            }
            else
            {
                if (!does_protect_affect_move(0))
                {
                    battlescripts_curr_instruction += 7;
                }
            }
        }
    }
    return;
}

s8 get_priority(u16 move, u8 bank);

u8 protect_affects(u16 move, u8 set)
{
    u8 effect = 0;
    u8 protect_flag = move_table[move].move_flags.flags.affected_by_protect;
    u8 split = move_table[move].split;
    u8 contact = move_table[move].move_flags.flags.makes_contact;
    u8 target = move_table[move].target;
    u8 targets_side = is_bank_from_opponent_side(bank_target);
    if (protect_structs[bank_target].flag0_protect && protect_flag)
        effect = 1;
    else if (new_battlestruct.ptr->bank_affecting[bank_target].kings_shield && protect_flag && split != 2)
    {
        effect = 1;
        if (contact && set)
            new_battlestruct.ptr->bank_affecting[bank_attacker].kingsshield_damage = 1;
    }
    else if (new_battlestruct.ptr->bank_affecting[bank_target].spiky_shield && protect_flag)
    {
        effect = 1;
        if (contact && set)
            new_battlestruct.ptr->bank_affecting[bank_attacker].spikyshield_damage = 1;
    }
    else if (new_battlestruct.ptr->side_affecting[targets_side].crafty_shield && protect_flag && split == 2)
        effect = 1;
    else if (new_battlestruct.ptr->side_affecting[targets_side].quick_guard && protect_flag && get_priority(current_move, bank_attacker) > 0)
        effect = 1;
    else if (new_battlestruct.ptr->side_affecting[targets_side].mat_block && protect_flag && split != 2)
        effect = 1;
    else if (new_battlestruct.ptr->side_affecting[targets_side].wide_guard && protect_flag && (target == 8 || target == 0x20))
        effect = 1;

    return effect;
}

u8 protect_affecting_moves(u16 move)
{
    u8 effect = protect_affects(move, 1);
    if (effect)
    {
        move_outcome.missed = 1;
        jump_if_move_has_no_effect(7, move);
        battle_communication_struct.field6 = 1;
    }
    return effect;
}
