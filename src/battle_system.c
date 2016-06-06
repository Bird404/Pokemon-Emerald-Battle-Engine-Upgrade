#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "battlescripts.h"
#include "new_battle_struct.h"
#include "move_table.h"

u8 get_item_effect(u8 bank, u8 check_negating_effects)
{
    if (check_negating_effects)
    {
        if (battle_participants[bank].ability_id == ABILITY_KLUTZ || new_battlestruct.ptr->field_affecting.magic_room || new_battlestruct.ptr->bank_affecting[bank].embargo)
            return ITEM_EFFECT_NOEFFECT;
    }
    if (battle_participants[bank].held_item == ITEM_ENIGMABERRY)
    {
        return enigma_berry_battle[bank].battle_effect_x12;
    }
    else
    {
        return get_item_x12_battle_function(battle_participants[bank].held_item);
    }
    return 1;
}

u8 is_of_type(u8 bank, u8 type)
{
    if (battle_participants[bank].type1 == type || battle_participants[bank].type2 == type || new_battlestruct.ptr->bank_affecting[bank].type3 == type)
        return true;
    else
        return false;
}

void set_type(u8 bank, u8 type)
{
    battle_participants[bank].type1 = type;
    battle_participants[bank].type2 = type;
    new_battlestruct.ptr->bank_affecting[bank].type3 = type;
    return;
}

u32 two_options_rand(u32 option1, u32 option2)
{
    if (rng() & 1)
        return option1;
    return option2;
}

u8 weather_abilities_effect()
{
    if (ability_battle_effects(19, 0, ABILITY_AIR_LOCK, 0, 0) || ability_battle_effects(19, 0, ABILITY_CLOUD_NINE, 0, 0))
        return false;
    else
        return true;
}

u32 get_1_16_of_max_hp(u8 bank)
{
    u32 num = (battle_participants[bank].max_hp) >> 4;
    if (num < 1)
    {
        num = 1;
    }
    return num;
}

u32 get_1_8_of_max_hp(u8 bank)
{
    u32 num = (battle_participants[bank].max_hp) >> 3;
    if (num < 1)
    {
        num = 1;
    }
    return num;
}

u32 get_1_4_of_max_hp(u8 bank)
{
    u32 num = (battle_participants[bank].max_hp) >> 2;
    if (num < 1)
    {
        num = 1;
    }
    return num;
}

u8 percent_chance(u8 percent)
{
    u8 num = __umodsi3(rng(), 100) + 1;
    if (num <= percent)
        return true;
    else
        return false;
}

s8 get_move_position(u8 bank, u16 move)
{
    for (u8 i = 0; i < 4; i++)
    {
        if (battle_participants[bank].moves[i] == move)
            return i;
    }
    return -1;
}

u8 should_cherrim_change(u8 bank)
{
    u8 effect = false;
    if (!(battle_participants[bank].ability_id == ABILITY_FLOWER_GIFT && battle_participants[bank].poke_species == POKE_CHERRIM))
    {
        return effect;
    }
    if ((battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun) && weather_abilities_effect())
    {
        if (!new_battlestruct.ptr->bank_affecting[bank].sunshine_form)
        {
            effect = 2;
            new_battlestruct.ptr->bank_affecting[bank].sunshine_form = 1;
        }
    }
    else
    {
        if (new_battlestruct.ptr->bank_affecting[bank].sunshine_form)
        {
            effect = 1;
            new_battlestruct.ptr->bank_affecting[bank].sunshine_form = 0;
        }
    }
    return effect;
}

void copy_status_condition_text(u8 bank, u8 confusion)
{
    u32* status_flag;
    if (battle_participants[bank].status.flags.sleep)
    {
        status_flag = &sleep_status_flag;
    }
    else if (battle_participants[bank].status.flags.poison || battle_participants[bank].status.flags.toxic_poison)
    {
        status_flag = &poison_status_flag;
    }
    else if (battle_participants[bank].status.flags.freeze)
    {
        status_flag = &freeze_status_flag;
    }
    else if (battle_participants[bank].status.flags.paralysis)
    {
        status_flag = &paralysis_status_flag;
    }
    else if (battle_participants[bank].status.flags.burn)
    {
        status_flag = &burn_status_flag;
    }
    else if (confusion && battle_participants[bank].status2 & 7)
    {
        status_flag = (void*)0x0831BC98;
    }
    else
    {
        return;
    }
    strcpy_xFF_terminated_0(&battle_text_buff1, status_flag);
    return;
}

u8 type_effectiveness_table[TYPE_FAIRY-0x4][TYPE_FAIRY-0x4] = {
    {10,10,10,10,10,05,10,00,10,05,10,10,10,10,10,10,10,10,10}, //normal
    {20,10,05,05,10,20,05,00,10,20,10,10,10,10,05,20,10,20,05}, //fight
    {10,20,10,10,10,05,20,10,10,05,10,10,20,05,10,10,10,10,10}, //flying
    {10,10,10,05,05,05,10,05,10,00,10,10,20,10,10,10,10,10,20}, //poison
    {10,10,00,20,10,20,05,10,10,20,20,10,05,20,10,10,10,10,10}, //ground
    {10,05,20,10,05,10,20,10,10,05,20,10,10,10,10,20,10,10,10}, //rock
    {10,05,05,05,10,10,10,05,10,05,05,10,20,10,20,10,10,20,05}, //bug
    {00,10,10,10,10,10,10,20,10,10,10,10,10,10,20,10,10,05,10}, //ghost
    {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}, //egg
    {10,10,10,10,10,20,10,10,10,05,05,05,10,05,10,20,10,10,20}, //steel
    {10,10,10,10,10,05,20,10,10,20,05,05,20,10,10,20,05,10,10}, //fire
    {10,10,10,10,20,20,10,10,10,10,20,05,05,10,10,10,05,10,10}, //water
    {10,10,05,05,20,20,05,10,10,05,05,20,05,10,10,10,05,10,10}, //grass
    {10,10,20,10,00,10,10,10,10,10,10,20,05,05,10,10,05,10,10}, //electric
    {10,20,10,20,10,10,10,10,10,05,10,10,10,10,05,10,10,00,10}, //psychic
    {10,10,20,10,20,10,10,10,10,05,05,05,20,10,10,05,20,10,10}, //ice
    {10,10,10,10,10,10,10,10,10,05,10,10,10,10,10,10,20,10,00}, //dragon
    {10,05,10,10,10,10,10,20,10,10,10,10,10,10,20,10,10,05,05}, //dark
    {10,20,10,05,10,10,10,10,10,05,05,10,10,10,10,10,20,20,10}  //fairy
};

u32 damage_type_effectiveness_update (u8 attacking_type, u8 defending_type, u8 atk_bank, u8 def_bank, u32 damage)
{
    u8 effect,atype=attacking_type,dtype=defending_type;

    if(atype==TYPE_EGG || dtype==TYPE_EGG)
        return damage;

    if(atype>=TYPE_FAIRY)
        atype=atype-5;

    if(dtype>=TYPE_FAIRY)
        dtype=dtype-5;

    effect=type_effectiveness_table[atype][dtype];

    if (new_battlestruct.ptr->various.inverse_battle)
    {
        if (effect == 20)
        {
            effect = 5;
        }
        else if (effect == 5 || effect == 0)
        {
            effect = 20;
        }
    }

    if ((((attacking_type == TYPE_NORMAL || attacking_type == TYPE_FIGHTING) && defending_type == TYPE_GHOST && ((battle_participants[atk_bank].status2 & 0x20000000))) || battle_participants[atk_bank].ability_id == ABILITY_SCRAPPY) && effect == 0)
    {
        effect = 10;
    }

    else if ((attacking_type == TYPE_PSYCHIC) && defending_type == TYPE_DARK && new_battlestruct.ptr->bank_affecting[atk_bank].miracle_eyed && effect == 0)
    {
        effect = 10;
    }

    else if (effect == 0 && (get_item_effect(def_bank, true) == ITEM_EFFECT_RINGTARGET))
    {
        effect = 10;
    }
    else if (battle_weather.flags.air_current && defending_type == TYPE_FLYING && effect == 20)
    {
        effect = 10;
    }
    else if (attacking_type == TYPE_GROUND)
    {
        if ((new_battlestruct.ptr->field_affecting.gravity || get_item_effect(def_bank, true) == ITEM_EFFECT_IRONBALL) && effect == 0)
        {
            effect = 10;
        }
        else if ((defending_type == TYPE_FLYING && effect == 0) || battle_participants[def_bank].ability_id == ABILITY_LEVITATE || (get_item_effect(def_bank, true) == ITEM_EFFECT_AIRBALLOON && !new_battlestruct.ptr->bank_affecting[def_bank].popped_air_balloon) || new_battlestruct.ptr->bank_affecting[def_bank].magnet_rise || new_battlestruct.ptr->bank_affecting[def_bank].telekinesis)
        {
            if (new_battlestruct.ptr->bank_affecting[def_bank].smacked_down)
            {
                effect = 10;
            }
            else
            {
                effect = 10;
            }
        }
    }
    else if (current_move == MOVE_FREEZEDRY && defending_type == TYPE_WATER)
    {
        effect = 20;
    }

    damage_loc = damage;
    damage_modulate_by_type_effectivity(effect);
    damage = damage_loc;

    return damage;
}

u32 apply_type_effectiveness(u32 damage, u8 move_type, u8 target_bank, u8 atk_bank)
{
    u8 defender_type1 = battle_participants[target_bank].type1;
    u8 defender_type2 = battle_participants[target_bank].type2;
    u8 defender_type3 = new_battlestruct.ptr->bank_affecting[target_bank].type3;

    //set different types

    if (defender_type2 == defender_type1)
        defender_type2 = TYPE_EGG;
    if (defender_type3 == defender_type1 || defender_type3 == defender_type2)
        defender_type3 = TYPE_EGG;

    damage = damage_type_effectiveness_update(move_type, defender_type1, atk_bank, target_bank, damage);
    damage = damage_type_effectiveness_update(move_type, defender_type2, atk_bank, target_bank, damage);
    damage = damage_type_effectiveness_update(move_type, defender_type3, atk_bank, target_bank, damage);
    return damage;
}

u16 get_forewarn_move(u8 bank)
{
    u16 most_powerful_move = 0;
    s16 best_power = - 1;
    u8 banks_side = is_bank_from_opponent_side(bank);
    for (u8 i2 = 0; i2 < no_of_all_banks; i2++)
    {
        if (banks_side != is_bank_from_opponent_side(i2) && battle_participants[i2].current_hp)
        {
            for (u8 i = 0; i < 4; i++)
            {
                u16 curr_move = battle_participants[i2].moves[i];
                if (move_table[curr_move].base_power > best_power)
                {
                    most_powerful_move = curr_move;
                    best_power = move_table[curr_move].base_power;
                }
                else if (move_table[curr_move].base_power == best_power)
                {
                    most_powerful_move = two_options_rand(most_powerful_move, curr_move);
                }
                else if (move_table[curr_move].base_power == 1)
                {
                        u16 curr_power;
                        if (move_table[curr_move].script_id == 38) //one hit ko moves
                            curr_power = 160;
                        else if (curr_move == MOVE_COUNTER || curr_move == MOVE_METAL_BURST || curr_move == MOVE_MIRROR_COAT)
                            curr_power = 120;
                        else
                        {
                            u8 j = 0;
                            while (true)
                            {
                                if (forewarn_moves[j] == curr_move)
                                {
                                    curr_power = 80;
                                    break;
                                }
                                else if (forewarn_moves[j] == 0xFFFF)
                                {
                                    curr_power = 1;
                                    break;
                                }
                                j++;
                            }
                        }
                        if (curr_power > best_power)
                        {
                            most_powerful_move = curr_move;
                            best_power = curr_power;
                        }
                        else if (curr_power == best_power)
                        {
                            most_powerful_move = two_options_rand(most_powerful_move, curr_move);
                        }
                    }
            }
        }
    }
    return most_powerful_move;
}

u8 anticipation_shudder(u8 bank)
{
    u8 shudder = false;
    u8 banks_side = is_bank_from_opponent_side(bank);
    for (u8 i2 = 0; i2 < no_of_all_banks; i2++)
    {
        if (banks_side != is_bank_from_opponent_side(i2) && battle_participants[i2].current_hp)
        {
            for (u8 i = 0; i < 4; i++)
            {
                if (move_table[battle_participants[i2].moves[i]].script_id == 38) //one hit ko move check
                {
                    shudder = true;
                    break;
                }
                else
                {
                    if (move_table[battle_participants[i2].moves[i]].base_power)
                    {
                        u16 move_now = current_move;
                        current_move = battle_participants[i2].moves[i];
                        u32 damage = apply_type_effectiveness(1, move_table[battle_participants[i2].moves[i]].type, bank, i2);
                        current_move = move_now;
                        if (damage > 1)
                        {
                            shudder = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return shudder;
}

u8 prepare_castform_switch(u8 effect, u8 bank)
{
    if (effect)
    {
        void* bs_castform = (void*) 0x082DB4A9;
        execute_battle_script(bs_castform);
        battle_scripting.active_bank = bank;
        battle_stuff_ptr.ptr->castform_switch_form = effect - 1;
    }
    return effect;
}

u8 has_ability_effect(u8 bank, u8 mold_breaker, u8 gastro)
{
    u8 attacker_ability;
    if (gastro && new_battlestruct.ptr->bank_affecting[bank].gastro_acided)
        return false;
    if (mold_breaker)
    {   attacker_ability=battle_participants[bank_attacker].ability_id;
        if(has_ability_effect(bank_attacker,0,1) && (attacker_ability==ABILITY_MOLD_BREAKER
               || attacker_ability==ABILITY_TERAVOLT || attacker_ability==ABILITY_TURBOBLAZE))
            return false;
    }
    return true;
}

u8 ability_battle_effects(u8 switch_id, u8 bank, u8 ability_to_check, u8 special_cases_argument, u16 move)
{
    u8 effect = false;
    u16 curr_move;
    if (move)
        curr_move = move;
    else
        curr_move = current_move;
    u8 move_type;
    if (battle_stuff_ptr.ptr->dynamic_move_type)
        move_type = battle_stuff_ptr.ptr->dynamic_move_type & 0x3F;
    else
        move_type = move_table[curr_move].type;

    if (special_cases_argument)
        last_used_ability = special_cases_argument;
    else
        last_used_ability = battle_participants[bank].ability_id;

    u8 bank_side = is_bank_from_opponent_side(bank);
    u8 common_effect=0;
    void* script_ptr;
    u8 adder=0;
    u8 move_effect=0;
    u8 contact =move_table[curr_move].move_flags.flags.makes_contact;
    switch (switch_id)
    {
    case 0: //switch-in abilities

        switch (last_used_ability)
        {
        case ABILITY_MOLD_BREAKER:
            script_ptr = &moldbreaker_message_bs;
            common_effect=1;
            break;
        case ABILITY_TURBOBLAZE:
            script_ptr = &turboblaze_bs;
            common_effect=1;
            break;
        case ABILITY_TERAVOLT:
            script_ptr = &terravolt_bs;
            common_effect=1;
            break;
        case ABILITY_PRESSURE:
            script_ptr = &pressure_bs;
            common_effect=1;
            break;
        case ABILITY_UNNERVE:
            script_ptr = &unnerve_bs;
            common_effect=1;
            break;
        case ABILITY_AURA_BREAK:
            script_ptr = &aurabreak_bs;
            common_effect=1;
            break;
        case ABILITY_FAIRY_AURA:
            script_ptr = &fairyaura_bs;
            common_effect=1;
            break;
        case ABILITY_DARK_AURA:
            script_ptr = &darkaura_bs;
            common_effect=1;
            break;
        case ABILITY_DOWNLOAD:
            {
                u16 def_sum = 0;
                u16 spdef_sum = 0;
                u8 banks_side = is_bank_from_opponent_side(bank);
                for (u8 i = 0; i < no_of_all_banks; i++)
                {
                    if (i != bank && banks_side!= is_bank_from_opponent_side(i))
                    {
                        def_sum += battle_participants[i].def;
                        spdef_sum += battle_participants[i].sp_def;
                    }
                }
                if ((def_sum == spdef_sum && two_options_rand(0, 1)) || (spdef_sum < def_sum))
                {
                    battle_participants[bank].sp_atk_buff++;
                    script_ptr = &downloadspatk_bs;
                }
                else
                {
                    battle_participants[bank].atk_buff++;
                    script_ptr = &downloadatk_bs;
                }
                    effect = 1;
                    battle_scripting.active_bank = bank;
                    execute_battle_script(script_ptr);
                    break;
            }
        case ABILITY_DROUGHT:
            if (!(battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain || battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_sun;

                if (get_item_effect(bank, true) == ITEM_EFFECT_HEATROCK)
                    battle_effects_duration.weather_dur = 8;
                else
                    battle_effects_duration.weather_dur = 5;

                script_ptr = (void*) 0x082DB52A;
                execute_battle_script(script_ptr);
                battle_scripting.active_bank = bank;
            }
        break;
        case ABILITY_DRIZZLE:
            if (!(battle_weather.flags.rain || battle_weather.flags.permament_rain || battle_weather.flags.downpour || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain || battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_rain;
                if (get_item_effect(bank, true) == ITEM_EFFECT_DAMPROCK)
                    battle_effects_duration.weather_dur = 8;
                else
                    battle_effects_duration.weather_dur = 5;

                script_ptr = (void*) 0x082DB430;
                execute_battle_script(script_ptr);
                battle_scripting.active_bank = bank;
            }
            break;
        case ABILITY_SAND_STREAM:
            if (!(battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain || battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_sandstorm;
                if (get_item_effect(bank, true) == ITEM_EFFECT_SMOOTHROCK)
                    battle_effects_duration.weather_dur = 8;
                else
                    battle_effects_duration.weather_dur = 5;

                script_ptr = (void*) 0x082DB470;
                execute_battle_script(script_ptr);
                battle_scripting.active_bank = bank;
            }
            break;
        case ABILITY_SNOW_WARNING:
            if (!(battle_weather.flags.hail || battle_weather.flags.permament_hail || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain || battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_hail;
                if (get_item_effect(bank, true) == ITEM_EFFECT_ICYROCK)
                    battle_effects_duration.weather_dur = 8;
                else
                    battle_effects_duration.weather_dur = 5;

                execute_battle_script(&snow_warning_bs);
                battle_scripting.active_bank = bank;
            }
            break;
        case ABILITY_DESOLATE_LAND:
            if (!(battle_weather.flags.harsh_sun))
            {
                effect = true;
                battle_weather.int_bw = weather_harsh_sun | weather_permament_sun;
                execute_battle_script(&desolateland_bs);
            }
            break;
        case ABILITY_PRIMORDIA_SEA:
            if (!(battle_weather.flags.heavy_rain))
            {
                effect = true;
                battle_weather.int_bw = weather_heavy_rain | weather_permament_rain;
                execute_battle_script(&primoridalsea_bs);
                battle_scripting.active_bank = bank;
            }
            break;
        case ABILITY_DELTA_STREAM:
            if (!(battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_air_current;
                execute_battle_script(&deltastream_bs);
            }
            break;
        case ABILITY_FRISK:
            {
                effect = true;
                battle_stuff_ptr.ptr->intimidate_user=bank;
                execute_battle_script(frisk_bs);
            }
            break;
        case ABILITY_FOREWARN:
            {
                effect = true;
                battle_scripting.active_bank = bank;
                execute_battle_script(&forewarn_bs);
                battle_text_buff1[0] = 0xFD;
                battle_text_buff1[1] = 0x2;
                u16 best_move = get_forewarn_move(bank);
                battle_text_buff1[2] = best_move;
                battle_text_buff1[3] = (best_move >> 8);
                battle_text_buff1[4] = 0xFF;
            }
            break;
        case ABILITY_ANTICIPATION:
            {
                if (anticipation_shudder(bank))
                {
                    effect = true;
                    battle_scripting.active_bank = bank;
                    execute_battle_script(&anticipation_bs);
                }
            }
            break;
        case ABILITY_IMPOSTER:
            if (battle_participants[(bank ^ 1)].current_hp && (bank ^ 1) < no_of_all_banks && !(battle_participants[bank].status2 & 0x200000) && !(battle_participants[(bank ^1)].status2 & 0x200000))
            {
                effect = true;
                execute_battle_script(&transform_bs);
                current_move = MOVE_TRANSFORM;
                bank_attacker = bank;
                bank_target = (bank ^ 1);
                battle_scripting.active_bank = bank;
                new_battlestruct.ptr->various.active_bank = bank;
            }
            break;
        case ABILITY_INTIMIDATE:
            {
                script_ptr = (void*) 0x082DB4B8;
                execute_battle_script(script_ptr);
                battle_stuff_ptr.ptr->intimidate_user=bank;
                effect=true;
            }
            break;
        case ABILITY_TRACE:
            {
                active_bank=bank^1;
                u16 hp1=battle_participants[active_bank].current_hp;
                if (battle_flags&1)
                {
                    u16 hp2=battle_participants[active_bank^2].current_hp;
                    if(hp1==0 && hp2==0)
                        break;
                    if(hp1==0 || (hp2!=0 && two_options_rand(0,1)))
                        active_bank=active_bank^2;
                }
                else if (hp1==0)
                        break;
                last_used_ability=battle_participants[active_bank].ability_id;
                if (!last_used_ability)
                    break;
                if (last_used_ability!=ABILITY_TRACE) //If trace copies another switch-in ability. This fragment enables to activate that ability immediately after tracing.
                    battle_stuff_ptr.ptr->switch_in_ability_bank_counter--;
                script_ptr = (void*) 0x082DB452;
                execute_battle_script(script_ptr);
                battle_participants[bank].ability_id=last_used_ability;
                battle_scripting.active_bank = bank;
                battle_stuff_ptr.ptr->intimidate_user=bank;
                battle_text_buff1[0]=0xFD;
                battle_text_buff1[1]=0x4;
                battle_text_buff1[2]=active_bank;
                battle_text_buff1[3]=battle_team_id_by_side[active_bank];
                battle_text_buff1[4]=0xFF;
                battle_text_buff2[0]=0xFD;
                battle_text_buff2[1]=0x9;
                battle_text_buff2[2]=last_used_ability;
                battle_text_buff2[3]=0xFF;
                effect=true;
            }
            break;
        case ABILITY_AIR_LOCK:
        case ABILITY_CLOUD_NINE:
            for (u8 j = 0; j < no_of_all_banks; j++)
            {
                effect = castform_switch(j);
                effect = prepare_castform_switch(effect, j);
                if (effect)
                {
                    break;
                }
                effect = should_cherrim_change(j);
                if (effect)
                {
                    execute_battle_script(&cherrimswitch_bs);
                    battle_scripting.active_bank = j;
                    battle_stuff_ptr.ptr->castform_switch_form = effect - 1;
                    break;
                }
            }
            break;
        case ABILITY_FLOWER_GIFT:
            if (!(new_battlestruct.ptr->bank_affecting[bank].cherrim_transformed))
            {
                effect = should_cherrim_change(bank);
                if (effect)
                {
                    execute_battle_script(&cherrimswitch_bs);
                    battle_scripting.active_bank = bank;
                    battle_stuff_ptr.ptr->castform_switch_form = effect - 1;
                    new_battlestruct.ptr->bank_affecting[bank].cherrim_transformed = 1;
                }
            }
            break;
        case ABILITY_FORECAST:
            effect = castform_switch(bank);
            prepare_castform_switch(effect, bank);
            break;
        case ABILITY_SLOW_START:
            {
                new_battlestruct.ptr->bank_affecting[bank].slowstart_duration = 5;
                effect = true;
                battle_scripting.active_bank = bank;
                execute_battle_script(&slowstart_bs);
                battle_scripting.active_bank = bank;
            }
            break;
        }
        if (common_effect)
        {
            effect = true;
            battle_scripting.active_bank = bank;
            execute_battle_script(script_ptr);
        }
        break;
    case 1: //end turn abilities
        if (!(battle_participants[bank].current_hp && has_ability_effect(bank, 0, 1)))
            break;
        bank_attacker = bank;
        switch (last_used_ability)
        {
            case ABILITY_RAIN_DISH:
                if (weather_abilities_effect() && (battle_weather.flags.downpour || battle_weather.flags.rain || battle_weather.flags.permament_rain || battle_weather.flags.heavy_rain))
                {
                    if (battle_participants[bank].current_hp < battle_participants[bank].max_hp)
                    {
                        script_ptr = (void*) 0x082DB45C;
                        execute_battle_script(script_ptr);
                        damage_loc = get_1_16_of_max_hp(bank) * (-1);
                        effect = true;
                    }
                }
                break;
            case ABILITY_DRY_SKIN:
                if (weather_abilities_effect())
                {
                    if (battle_weather.flags.downpour || battle_weather.flags.rain || battle_weather.flags.permament_rain || battle_weather.flags.heavy_rain)
                    {
                        if (battle_participants[bank].current_hp < battle_participants[bank].max_hp)
                        {
                            script_ptr = (void*) 0x082DB45C;
                            execute_battle_script(script_ptr);
                            damage_loc = get_1_8_of_max_hp(bank) * (-1);
                            effect = true;
                        }
                    }
                    else if (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)
                    {
                        damage_loc = get_1_8_of_max_hp(bank);
                        execute_battle_script(&dryskindamage_bs);
                        effect = true;
                    }
                }
                break;
            case ABILITY_SOLAR_POWER:
                if (weather_abilities_effect() && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun))
                {
                    damage_loc = get_1_8_of_max_hp(bank);
                    execute_battle_script(&solarpower_bs);
                    effect = true;
                }
                break;
            case ABILITY_HARVEST:
                if (get_item_pocket_id(battle_stuff_ptr.ptr->used_held_items[bank]) == 4 && !battle_participants[bank].held_item)
                {
                    if ((weather_abilities_effect() && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)) || two_options_rand(0, 1) == 0)
                    {
                        effect = true;
                        execute_battle_script(&harvest_bs);
                    }
                }
                break;
            case ABILITY_HEALER:
                {
                    u8 friendly_bank = bank ^ 2;
                    if (friendly_bank < no_of_all_banks && battle_participants[friendly_bank].status.int_status & battle_participants[friendly_bank].current_hp)
                    {
                        if (__umodsi3(rng(), 100) + 1 <= 30)
                        {   battle_participants[friendly_bank].status2 &= 0xF7FFFFFF;
                            effect = true;
                            copy_status_condition_text(friendly_bank);
                            execute_battle_script(&healer_bs);
                            battle_scripting.active_bank = friendly_bank;
                            active_bank = friendly_bank;
                            battle_participants[friendly_bank].status.int_status = 0;
                            prepare_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[friendly_bank].status);
                            mark_buffer_bank_for_execution(friendly_bank);
                        }
                    }
                    break;
                }
            case ABILITY_HYDRATION:
                    if (((battle_weather.flags.downpour || battle_weather.flags.rain || battle_weather.flags.permament_rain || battle_weather.flags.heavy_rain) && weather_abilities_effect()))
                        common_effect=1;
                    break;
            case ABILITY_SHED_SKIN:
                    if (__umodsi3(rng(), 3) == 0)
                        common_effect=1;
                    break;
            case ABILITY_PICKUP:
                if (!battle_participants[bank].held_item)
                {
                    for (u8 i = 0; i < no_of_all_banks; i++)
                    {
                        if (new_battlestruct.ptr->various.recently_used_item == battle_stuff_ptr.ptr->used_held_items[i])
                        {
                            effect = true;
                            battle_stuff_ptr.ptr->used_held_items[i] = 0;
                            execute_battle_script(&pickup_bs);
                            battle_participants[bank].held_item = battle_stuff_ptr.ptr->used_held_items[i];
                            active_bank = bank;
                            prepare_setattributes_in_battle(0, 2, 0, 4, &battle_participants[bank].held_item);
                            mark_buffer_bank_for_execution(bank);
                            break;
                        }
                    }
                }
                break;
            case ABILITY_BAD_DREAMS: //to do
                break;
            case ABILITY_SPEED_BOOST:
                if (battle_participants[bank].spd_buff != 0xC && disable_structs[bank].is_first_turn != 2)
                {
                    battle_participants[bank].spd_buff ++;
                    battle_scripting.active_bank = bank;
                    battle_scripting.field10 = 0x11;
                    battle_scripting.field11 = 0x11;
                    script_ptr = (void*) 0x082DB444;
                    execute_battle_script(script_ptr);
                }
                break;
            case ABILITY_TRUANT:
                {
                    disable_structs[bank].truant_counter = truant_hook(disable_structs[bank].truant_counter);
                    break;
                }
            case ABILITY_MOODY:
                {
                    u8 raiseable_stats = 0;
                    u8 lowerable_stats = 0;
                    u8* stat_ptr = &battle_participants[bank].atk_buff;
                    for (u8 i = 0; i < 7; i ++)
                    {
                        if (*(stat_ptr + i) != 0xC)
                        {
                            raiseable_stats |= bits_table[i];
                        }
                        if (*(stat_ptr + i) != 0)
                        {
                            lowerable_stats |= bits_table[i];
                        }
                    }
                    if (raiseable_stats || lowerable_stats)
                    {
                        effect = true;
                        execute_battle_script(&moody_bs);
                        new_battlestruct.ptr->various.var1 = 0;
                        new_battlestruct.ptr->various.var2 = 0;
                        battle_scripting.active_bank = bank;
                        bank_target = bank;
                        while (raiseable_stats != 0)
                        {
                            u8 rand_stat = __umodsi3(rng(), 7);
                            if (raiseable_stats & bits_table[rand_stat])
                            {
                                new_battlestruct.ptr->various.var1 = 0x21 + rand_stat;
                                if (lowerable_stats & bits_table[rand_stat])
                                    lowerable_stats ^= bits_table[rand_stat];
                                break;
                            }
                        }
                        while (lowerable_stats != 0)
                        {
                            u8 rand_stat = __umodsi3(rng(), 7);
                            if (lowerable_stats & bits_table[rand_stat])
                            {
                                new_battlestruct.ptr->various.var2 = 0x91 + rand_stat;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
       if (common_effect && battle_participants[bank].status.int_status)
        {
            battle_participants[bank].status2 &= 0xF7FFFFFF;
            effect = true;
            copy_status_condition_text(bank);
            script_ptr = (void*) 0x082DB484;
            execute_battle_script(script_ptr);
            active_bank = bank;
            battle_scripting.active_bank = bank;
            battle_participants[bank].status.int_status = 0;
            prepare_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[bank].status);
            mark_buffer_bank_for_execution(bank);
        }
        break;
    case 2: //abilities that affect certain moves
        if (!has_ability_effect(bank, 1, 1))
            break;
        u16* table_ptr;
        switch (last_used_ability)
        {
        case ABILITY_SOUNDPROOF:
            table_ptr = &sound_moves[0];
            common_effect=1;
            break;
        case ABILITY_BULLETPROOF:
            table_ptr = &ball_bomb_moves[0];
            common_effect=1;
            break;
        case ABILITY_OVERCOAT:
            table_ptr = &powder_moves[0];
            common_effect=1;
            break;
        }
        if(common_effect)
        {
            for (u8 i = 0; table_ptr[i]!= 0xFFFF; i++)
            {
                if (current_move == table_ptr[i])
                {
                    effect = true;
                    battlescripts_curr_instruction = (void*) 0x082DB61F;
                    if (battle_participants[bank_attacker].status2 & 0x1000)
                    {
                        hitmarker |= 0x800;
                    }
                    break;
                }
            }
        }
        break;

    case 3: //abilities that affect type

            if (curr_move && has_ability_effect(bank, 1, 1))
            {
                if (protect_structs[bank_attacker].flag2_notfirststrike)
                    adder = 1;
                switch (last_used_ability)
                {
                case ABILITY_WATER_ABSORB:
                case ABILITY_DRY_SKIN:
                    if (move_type == TYPE_WATER)
                        common_effect=1;
                    break;
                case ABILITY_VOLT_ABSORB:
                    if (move_type == TYPE_ELECTRIC)
                        common_effect=1;
                    break;
                case ABILITY_FLASH_FIRE:
                    if (move_type == TYPE_FIRE)
                    {
                        effect = 1;
                        battle_resources_ptr.ptr->field0_ptr->ability_flags_ptr->flags_ability[bank].flag1_flashfire = 1;
                        script_ptr = (void*) 0x082DB5A7;
                        script_ptr += adder;
                        battlescripts_curr_instruction = script_ptr;
                    }
                    break;
                case ABILITY_SAP_SIPPER:
                    if (move_type == TYPE_GRASS)
                    {
                        if (battle_participants[bank].atk_buff != 0xC)
                        {
                            script_ptr = &sapsipperboost_bs;
                            battle_participants[bank].atk_buff++;
                        }
                        else
                        {
                            script_ptr = &sapsipperimmunity_bs;
                        }
                        script_ptr += adder;
                        effect = 1;
                        battlescripts_curr_instruction = script_ptr;
                    }
                    break;
                case ABILITY_MOTOR_DRIVE:
                    if (move_type == TYPE_ELECTRIC)
                    {
                        if (battle_participants[bank].spd_buff != 0xC)
                        {
                            script_ptr = &motordriveboost_bs;
                            battle_participants[bank].spd_buff++;
                        }
                        else
                        {
                            script_ptr = &motordriveimmunity_bs;
                        }
                        script_ptr += adder;
                        effect = 1;
                        battlescripts_curr_instruction = script_ptr;
                    }
                    break;
                }
            }
            if(common_effect)
            {
                if (battle_participants[bank].max_hp == battle_participants[bank].current_hp)
                    script_ptr = (void*) 0x082DB591;
                else
                {
                    script_ptr = (void*) 0x082DB56E;
                    damage_loc = get_1_4_of_max_hp(bank) * (-1);
                }
                script_ptr += adder;
                battlescripts_curr_instruction = script_ptr;
                effect = true;
            }
            break;
    case 4: //move end turn abilities
        {
            if (has_ability_effect(bank, 0, 1) && !(move_outcome.not_affected || move_outcome.failed || move_outcome.missed) && battle_participants[bank_attacker].current_hp && (special_statuses[bank_target].moveturn_losthp_physical || special_statuses[bank_target].moveturn_losthp_special || last_used_ability == ABILITY_DEFIANT || last_used_ability ==  ABILITY_COMPETITIVE))
            {
                u8* stat_pointer;
                switch (last_used_ability)
                {
                case ABILITY_STATIC:
                    move_effect = 0x45;
                    common_effect=1;
                    break;
                case ABILITY_FLAME_BODY:
                    move_effect = 0x43;
                    common_effect=1;
                    break;
                case ABILITY_POISON_POINT:
                    move_effect = 0x42;
                    common_effect=1;
                    break;
                case ABILITY_EFFECT_SPORE:
                    if(!(has_ability_effect(bank_attacker, 0, 1) &&
                         (battle_participants[bank_attacker].ability_id==ABILITY_OVERCOAT))) //add safety goggles check
                    {
                        move_effect=(rng()&3);
                        if(move_effect==0)
                            move_effect=0x41;
                        else if(move_effect==1)
                            move_effect=0x42;
                        else
                            move_effect=0x45;
                        common_effect=1;
                    }
                    break;
                case ABILITY_AFTERMATH:
                    if (battle_participants[bank].current_hp == 0 && contact) //checkdamp
                    {
                        damage_loc = get_1_4_of_max_hp(bank_attacker);
                        effect = true;
                        battlescript_push();
                        battlescripts_curr_instruction = &aftermath_bs;
                    }
                    break;
                case ABILITY_PICKPOCKET: //magician will need to be hooked at atk49 move end turn, the function that calls this case
                    if (battle_participants[bank_attacker].held_item && contact && (!battle_participants[bank].held_item) && (!new_battlestruct.ptr->bank_affecting[bank_attacker].sheerforce_bonus) && (multihit_counter == 1 || multihit_counter == 0) && battle_participants[bank_attacker].ability_id != ABILITY_SUCTION_CUPS)
                    {
                        last_used_item = battle_participants[bank_attacker].held_item;
                        battle_participants[bank].held_item = battle_participants[bank_attacker].held_item;
                        battle_participants[bank_attacker].held_item = 0;
                        battlescript_push();
                        battlescripts_curr_instruction = &pickpocket_bs;
                        effect = true;
                        active_bank = bank;
                        prepare_setattributes_in_battle(0, 2, 0, 4, &battle_participants[bank].held_item);
                        mark_buffer_bank_for_execution(bank);
                    }
                    break;
                case ABILITY_MUMMY:
                    if (contact && battle_participants[bank_attacker].ability_id != ABILITY_MUMMY && battle_participants[bank_attacker].ability_id != ABILITY_STANCE_CHANGE && battle_participants[bank_attacker].ability_id != ABILITY_MULTITYPE)
                    {
                        effect = true;
                        battle_participants[bank_attacker].ability_id = battle_participants[bank].ability_id;
                        battlescript_push();
                        battlescripts_curr_instruction = &mummy_bs;
                    }
                    break;
                case ABILITY_GOOEY:
                    if (contact && battle_participants[bank_attacker].spd_buff > 0)
                    {
                        effect = true;
                        battle_scripting.stat_changer = 0x93;
                        battlescript_push();
                        battlescripts_curr_instruction = &gooey_bs;
                    }
                    break;
                case ABILITY_CURSED_BODY:
                    if (!disable_structs[bank_attacker].disabled_move && percent_chance(30))
                    {
                        disable_structs[bank_attacker].disabled_move = curr_move;
                        disable_structs[bank_attacker].disable_timer = 3;
                        battlescript_push();
                        battlescripts_curr_instruction = &cursedbody_bs;
                        effect = true;
                        battle_text_buff1[0] = 0xFD;
                        battle_text_buff1[1] = 0x2;
                        battle_text_buff1[2] = curr_move;
                        battle_text_buff1[3] = (curr_move >> 8);
                        battle_text_buff1[4] = 0xFF;
                    }
                    break;
                case ABILITY_ROUGH_SKIN:
                case ABILITY_IRON_BARBS:
                    if (contact)
                    {
                        damage_loc = get_1_8_of_max_hp(bank_attacker);
                        effect = true;
                        battlescript_push();
                        void* roughskin_bs = (void*) 0x082DB654;
                        battlescripts_curr_instruction = roughskin_bs;
                    }
                    break;
                case ABILITY_RATTLED:
                    if (battle_participants[bank].spd_buff != 0xC && (move_type == TYPE_BUG || move_type == TYPE_DARK || move_type == TYPE_GHOST))
                    {
                        effect = true;
                        battlescript_push();
                        battlescripts_curr_instruction = &rattled_bs;
                        battle_scripting.stat_changer = 0x13;
                    }
                    break;
                case ABILITY_JUSTIFIED:
                    if (battle_participants[bank].atk_buff != 0xC && move_type == TYPE_DARK)
                    {
                        effect = true;
                        battlescript_push();
                        battlescripts_curr_instruction = &rattled_bs;
                        battle_scripting.stat_changer = 0x11;
                    }
                    break;
                case ABILITY_COLOR_CHANGE:
                    if (curr_move != MOVE_STRUGGLE && (!new_battlestruct.ptr->bank_affecting[bank_attacker].sheerforce_bonus) && (!is_of_type(bank, move_type)) && (multihit_counter == 1 || multihit_counter == 0))
                    {
                        battle_text_buff1[0] = 0xFD;
                        battle_text_buff1[1] = 0x3;
                        battle_text_buff1[2] = move_type;
                        battle_text_buff1[3] = 0xFF;
                        effect = true;
                        battlescript_push();
                        void* colorchange_bs = (void*) 0x082DB64D;
                        battlescripts_curr_instruction = colorchange_bs;
                        set_type(bank, move_type);
                    }
                    break;
                case ABILITY_WEAK_ARMOR:
                    if (battle_participants[bank].def_buff > 0 || battle_participants[bank].spd_buff != 0xC)
                    {
                        effect = true;
                        battlescript_push();
                        battlescripts_curr_instruction = &weakarmor_bs;
                        new_battlestruct.ptr->various.active_bank = bank;
                    }
                    break;
                case ABILITY_CUTE_CHARM:
                    if (battle_participants[bank_attacker].ability_id != ABILITY_OBLIVIOUS && percent_chance(100) && contact)
                    {
                        u8 target_gender = gender_from_pid(battle_participants[bank].poke_species, battle_participants[bank].pid);
                        u8 attacker_gender = gender_from_pid(battle_participants[bank_attacker].poke_species, battle_participants[bank_attacker].pid);
                        if (target_gender != attacker_gender && target_gender != 0xFF && attacker_gender != 0xFF && !(battle_participants[bank_attacker].status2 & 0xF0000))
                        {
                            effect = true;
                            battle_participants[bank_attacker].status2 |= bits_table[bank] << 0x10;
                            battlescript_push();
                            battlescripts_curr_instruction = (void*) 0x082DB66F;
                        }
                    }
                    break;
                case ABILITY_DEFIANT:
                    battle_scripting.stat_changer = 0x21;
                    stat_pointer = &battle_participants[bank].atk_buff;
                    goto STAT_CHANGE;
                case ABILITY_COMPETITIVE:
                    battle_scripting.stat_changer = 0x24;
                    stat_pointer = &battle_participants[bank].sp_atk_buff;
                STAT_CHANGE:
                    if (get_battle_side(bank) != get_battle_side(new_battlestruct.ptr->bank_affecting[bank].bank_that_lowered_stats) && new_battlestruct.ptr->bank_affecting[bank].lowered_stats)
                    {
                        u8* stat_ptr = &battle_participants[bank].atk_buff;
                        for (u8 i = 0; i < 7; i++)
                        {
                            if (*(stat_ptr + i) < 6 && *stat_pointer != 0xC)
                            {
                                effect = true;
                                battlescript_push();
                                battlescripts_curr_instruction = &defiant_bs;
                                new_battlestruct.ptr->bank_affecting[bank].lowered_stats = 0;
                                break;
                            }
                        }
                    }
                    break;


                }
            }
            if (common_effect && contact && percent_chance(30))
            {
                battle_communication_struct.move_effect = move_effect;
                battlescript_push();
                script_ptr = (void*) 0x082DB67C;
                battlescripts_curr_instruction = script_ptr;
                hitmarker |= HITMAKRER_IGNORE_SAFEGUARD;
                effect = true;
            }
            break;
        }
    case 5: //status immunities
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (has_ability_effect(i, 0, 1))
            {
                switch (battle_participants[i].ability_id)
                {
                case ABILITY_LIMBER:
                    if (battle_participants[i].status.flags.paralysis)
                        common_effect=1;
                    break;
                case ABILITY_MAGMA_ARMOR:
                    if (battle_participants[i].status.flags.freeze)
                        common_effect=1;
                    break;
                case ABILITY_IMMUNITY:
                    if (battle_participants[i].status.flags.poison || battle_participants[i].status.flags.toxic_poison)
                        common_effect=1;
                    break;
                case ABILITY_WATER_VEIL:
                    if (battle_participants[i].status.flags.burn)
                        common_effect=1;
                    break;
                case ABILITY_INSOMNIA:
                case ABILITY_VITAL_SPIRIT:
                    if (battle_participants[i].status.flags.sleep)
                    {
                        common_effect=1;
                        battle_participants[i].status2 &= 0xF7FFFFFF; //remove nightmare
                    }
                    break;
                case ABILITY_OBLIVIOUS:
                    if (battle_participants[i].status2 & 0xF0000)
                    {
                        battle_participants[i].status2 ^= 0xF0000;
                        strcpy_xFF_terminated_0(&battle_text_buff1, (void*) 0x0831BCA0);
                        effect = true;
                    }
                    break;
                case ABILITY_OWN_TEMPO:
                    if (battle_participants[i].status2 & 7)
                    {
                        battle_participants[i].status2 ^= 7;
                        strcpy_xFF_terminated_0(&battle_text_buff1, (void*) 0x0831BC98);
                        effect = true;
                    }
                    break;
                }
                if (common_effect==1)
                {
                    copy_status_condition_text(i);
                    battle_participants[i].status.int_status = 0;
                    effect=true;
                    battlescript_push();
                    battlescripts_curr_instruction = (void*) 0x082DB68C;
                    active_bank = i;
                    battle_scripting.active_bank = i;
                    prepare_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[i].status);
                    mark_buffer_bank_for_execution(active_bank);
                    break;
                }
                if (effect)
                    break;
            }
        }
        break;
    case 6: //check castform and cherrim
        {
            break;
        }
    case 12: //check opposing field for ability
    {
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (is_bank_from_opponent_side(i) != bank_side && battle_participants[i].ability_id == ability_to_check)
            {
                last_used_ability = ability_to_check;
                effect = i + 1;
                break;
            }
        }
        break;
    }
    case 13: //check bank field for ability
    {
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (is_bank_from_opponent_side(i) == bank_side && battle_participants[i].ability_id == ability_to_check)
            {
                last_used_ability = ability_to_check;
                effect = i + 1;
                break;
            }
        }
        break;
    }
    case 14: //check field affecting; mud, water sport and whole field for ability
        {
            for (u8 i = 0; i < no_of_all_banks; i++)
            {
                if ((status3[i].mud_sport && special_cases_argument == 0xFD) || (status3[i].watersport && special_cases_argument == 0xFE))
                {
                    effect = i + 1;
                    break;
                }
                else if (battle_participants[i].ability_id == ability_to_check && special_cases_argument == 0xFF)
                {
                    effect = i + 1;
                    last_used_ability = ability_to_check;
                    break;
                }
            }
            break;
        }
    case 15: //check field except the bank
        {
            for (u8 i = 0; i < no_of_all_banks; i++)
            {
                if (battle_participants[i].ability_id == ability_to_check && i != bank)
                {
                    effect = i + 1;
                    last_used_ability = ability_to_check;
                    break;
                }
            }
            break;
        }
    case 16: //count instances of ability in the opponent field
        {
            for (u8 i = 0; i < no_of_all_banks; i++)
            {
                if (is_bank_from_opponent_side(i) != bank_side && battle_participants[i].ability_id == ability_to_check)
                {
                    effect++;
                    last_used_ability = ability_to_check;
                }
            }
            break;
        }
    case 17: //count instances of ability in the banks field
        {
            for (u8 i = 0; i < no_of_all_banks; i++)
            {
                if (is_bank_from_opponent_side(i) == bank_side && battle_participants[i].ability_id == ability_to_check)
                {
                    effect++;
                    last_used_ability = ability_to_check;
                }
            }
            break;
        }
    case 18: //count instances of ability except bank
        {
            for (u8 i = 0; i < no_of_all_banks; i++)
            {
                if ( i != bank_side && battle_participants[i].ability_id == ability_to_check)
                {
                    effect++;
                    last_used_ability = ability_to_check;
                }
            }
            break;
        }
    case 19: //check whole field for ability with a hp check
        {
            for (u8 i = 0; i < no_of_all_banks; i ++)
            {
                if (battle_participants[i].ability_id == ability_to_check && battle_participants[i].current_hp)
                {
                    effect = i + 1;
                    last_used_ability = ability_to_check;
                    break;
                }
            }
            break;
        }
    case 20: //check ally
        {
            u8 ally = bank ^ 2;
            for (u8 i = 0; i < no_of_all_banks; i ++)
            {
                if (battle_participants[i].ability_id == ability_to_check && i == ally)
                {
                    effect = i + 1;
                    last_used_ability = ability_to_check;
                    break;
                }
            }
            break;
        }
    }

    if (effect && last_used_ability != 0xFF && switch_id < 0xB)
        record_usage_of_ability(bank, last_used_ability);
    return effect;
}

void call_ability_effects()
{
    ability_battle_effects(0, new_battlestruct.ptr->various.active_bank, 0, 0, 0);
    return;
}
