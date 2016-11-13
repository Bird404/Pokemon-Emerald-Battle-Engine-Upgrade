#include "defines.h"

u8 is_of_type(u8 bank, u8 type);
u8 protect_affecting_moves(u16 move);
u8 weather_abilities_effect();

void ability_affects_stat_reduction(u8 bank, void* battlescript_to_set, void* battlescript_to_push, u8 ability_record)
{
    if (battlescript_to_push && battlescript_to_set)
    {
        battlescript_custom_push(battlescript_to_push);
        battlescripts_curr_instruction = battlescript_to_set;
        battle_scripting.active_bank = bank;
        if (ability_record)
        {
            last_used_ability = battle_participants[bank].ability_id;
            record_usage_of_ability(bank, last_used_ability);
        }
    }
    return;
}

struct stat{
    u8 unused_bits : 4;
    u8 how_much : 3;
    u8 decrement : 1;
};

struct failbank{
    u8 failsth : 1;
    u8 field : 4;
    u8 ignore_opponent_protect : 1;
    u8 attacker : 1;
    u8 cannotfail : 1;
};

u8 change_stats(struct stat stat_change, u8 stat, struct failbank bank, void* battlescript_if_fails)
{
    if (stat_change.decrement)
        battle_scripting.stat_changer |= 0x80;
    else
        battle_scripting.stat_changer &= 0x7F;
    u8 fail = 0;
    if (bank.attacker)
    {
        active_bank = bank_attacker;
        battle_scripting.active_bank = bank_attacker;
    }
    else
    {
        active_bank = bank_target;
        battle_scripting.active_bank = bank_target;
    }
    if (current_move == MOVE_GROWTH && (battle_weather.flags.harsh_sun || battle_weather.flags.sun || battle_weather.flags.permament_sun) && weather_abilities_effect())
        stat_change.how_much *= 2;

    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 5;
    battle_text_buff1[2] = stat;
    battle_text_buff1[3] = 0xFF;
    u8 has_ability=has_ability_effect(active_bank, !bank.attacker, 1);
    if (has_ability)
    {
        if (battle_participants[active_bank].ability_id == ABILITY_CONTRARY)
        {
            stat_change.decrement ^= 1;
            battle_scripting.stat_changer ^= 0x80;
            record_usage_of_ability(active_bank, ABILITY_CONTRARY);
        }
        else if (battle_participants[active_bank].ability_id == ABILITY_SIMPLE)
        {
             if ((stat_change.how_much * 2) > 7)
             {
                 stat_change.how_much = 7;
             }
             else
             {
                 stat_change.how_much *= 2;
             }
             record_usage_of_ability(active_bank, ABILITY_SIMPLE);
        }
    }

    u8* stat_ptr = &battle_participants[active_bank].hp_buff;
    stat_ptr += stat;

    if (stat_change.decrement) //we're lowering stats
    {
        if (side_affecting_halfword[get_battle_side(active_bank) & 1].mist_on && current_move != MOVE_CURSE && bank.cannotfail == 0)
        {
            if (special_statuses[active_bank].statloweringflag)
            {
                battlescripts_curr_instruction = battlescript_if_fails;
            }
            else
            {
                ability_affects_stat_reduction(active_bank,(void*) 0x082DAE03, battlescript_if_fails, 0);
                special_statuses[active_bank].statloweringflag = 1;
            }
            return 1;
        }
        else if (protect_affecting_moves(0) && current_move != MOVE_CURSE && bank.ignore_opponent_protect == 0)
        {
            battlescripts_curr_instruction = (void*) 0x082D9F1C;
            return 1;
        }
        else if (has_ability && (battle_participants[active_bank].ability_id == ABILITY_WHITE_SMOKE || battle_participants[active_bank].ability_id == ABILITY_CLEAR_BODY) && current_move != MOVE_CURSE && bank.cannotfail == 0)
        {
            if (special_statuses[active_bank].statloweringflag)
            {
                battlescripts_curr_instruction = battlescript_if_fails;
            }
            else
            {
                ability_affects_stat_reduction(active_bank, (void*) 0x082DB5C7, battlescript_if_fails, 1);
                special_statuses[active_bank].statloweringflag = 1;
            }
            return 1;
        }
        if (current_move != MOVE_CURSE && bank.cannotfail == 0 && is_of_type(active_bank, TYPE_GRASS))
        {
            u8 flower = ability_battle_effects(13, active_bank, ABILITY_FLOWER_VEIL, 1, 0);
            if (flower)
            {
                if (special_statuses[active_bank].statloweringflag && battlescript_if_fails)
                    battlescripts_curr_instruction = battlescript_if_fails;
                else
                {
                    ability_affects_stat_reduction(flower - 1, (void*) 0x082DB5C7, battlescript_if_fails, 1);
                    special_statuses[active_bank].statloweringflag = 1;
                }
            }
        }
        if (has_ability && battle_participants[active_bank].ability_id == ABILITY_KEEN_EYE && stat == STAT_ACCURACY && bank.cannotfail == 0)
        {
            if (!bank.failsth)
            {

            }
            else
            {
                ability_affects_stat_reduction(active_bank, (void*)0x082DB62F, battlescript_if_fails, 1);
            }
            return 1;
        }
        else if (has_ability && battle_participants[active_bank].ability_id == ABILITY_HYPER_CUTTER && stat == STAT_ATTACK && bank.cannotfail == 0)
        {
            if (!bank.failsth)
            {

            }
            else
            {
                ability_affects_stat_reduction(active_bank,(void*) 0x082DB62F, battlescript_if_fails, 1);
            }
            return 1;
        }
        else if (has_ability && battle_participants[active_bank].ability_id == ABILITY_BIG_PECKS && stat == STAT_DEFENCE && bank.cannotfail == 0)
        {
            if (!bank.failsth)
            {

            }
            else
            {
                ability_affects_stat_reduction(active_bank,(void*) 0x082DB62F, battlescript_if_fails, 1);
            }
            return 1;
        }
        else if (has_ability && battle_participants[active_bank].ability_id == ABILITY_SHIELD_DUST && bank.failsth == 0)
        {
            return 1;
        }
        else
        {
            if (*stat_ptr == 0)
            {
                battle_communication_struct.multistring_chooser = 2;
                if (bank.failsth)
                {
                    move_outcome.missed = 1;
                    fail = 0;
                }
                else
                {
                    fail = 1;
                }
            }
            else
            {
                if (active_bank == bank_target)
                {
                    battle_communication_struct.multistring_chooser = 1;
                }
                else
                {
                    battle_communication_struct.multistring_chooser = 0;
                }

                u8 lowered_stats = 0;
                u8 amount = 0;
                battle_scripting.stat_changer &= 0x8F;
                while (stat_change.how_much != 0)
                {
                    stat_change.how_much--;
                    *stat_ptr -= 1;
                    lowered_stats++;
                    amount += 0x10;
                    if (*stat_ptr == 0)
                        break;
                }
                battle_scripting.stat_changer ^= amount;

                u8 i = 2;
                battle_text_buff2[0] = 0xFD;
                battle_text_buff2[1] = 0;
                if (lowered_stats == 2)
                {
                    battle_text_buff2[2] = 0xD3;
                    battle_text_buff2[3] = 0;
                    battle_text_buff2[4] = 0;
                    i += 3;
                }
                else if (lowered_stats >= 3)
                {
                    battle_text_buff2[2] = 0x97;
                    battle_text_buff2[3] = 1;
                    battle_text_buff2[4] = 0;
                    i += 3;
                }
                battle_text_buff2[i] = 0xD4;
                battle_text_buff2[i + 1] = 0;
                battle_text_buff2[i + 2] = 0xFF;
            }
        }
    }
    else    // we're raising stats
    {
        if (*stat_ptr == 0xC)
        {
            battle_communication_struct.multistring_chooser = 2;
            if (bank.failsth)
            {
                move_outcome.missed = 1;
                fail = 0;
            }
            else
            {
                fail = 1;
            }
        }
        else
        {
            if (active_bank == bank_target)
            {
                battle_communication_struct.multistring_chooser = 1;
            }
            else
            {
                battle_communication_struct.multistring_chooser = 0;
            }

            u8 raised_stats = 0;
            u8 amount = 0;
            battle_scripting.stat_changer &= 0x8F;
            while (stat_change.how_much != 0)
            {
                stat_change.how_much--;
                *stat_ptr += 1;
                raised_stats++;
                amount += 0x10;
                if (*stat_ptr == 0xC)
                    break;
            }
            battle_scripting.stat_changer ^= amount;

            u8 i = 2;
            battle_text_buff2[0] = 0xFD;
            battle_text_buff2[1] = 0;
            if (raised_stats == 2)
            {
                battle_text_buff2[2] = 0xD1;
                battle_text_buff2[3] = 0;
                battle_text_buff2[4] = 0;
                i += 3;
            }
            else if (raised_stats >= 3)
            {
                battle_text_buff2[2] = 0x97;
                battle_text_buff2[3] = 1;
                battle_text_buff2[4] = 0;
                i += 3;
            }
            battle_text_buff2[i] = 0xD2;
            battle_text_buff2[i + 1] = 0;
            battle_text_buff2[i + 2] = 0xFF;
        }
    }
    if (fail == 0 && battle_communication_struct.multistring_chooser != 2 && stat_change.decrement && has_ability && active_bank != bank_attacker)
        new_battlestruct->bank_affecting[active_bank].stat_lowered = 1;
    return fail;
}
