#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "static_resources.h"
#include "new_battle_struct.h"
#include <string.h>

void atk7D_set_rain()
{
    battlescripts_curr_instruction++;
    if (battle_weather.flags.air_current || battle_weather.flags.harsh_sun)
    {
        battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
    }
    else if (battle_weather.flags.downpour || battle_weather.flags.permament_rain || battle_weather.flags.rain || battle_weather.flags.heavy_rain)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 2;
    }
    else
    {
        battle_weather.flags.rain = 1;
        battle_communication_struct.multistring_chooser = 1;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_DAMPROCK)
            battle_effects_duration.weather_dur = 8;
        else
            battle_effects_duration.weather_dur = 5;
    }
    return;
}

void atk95_set_sandstorm()
{
    battlescripts_curr_instruction++;
    if (battle_weather.flags.air_current || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain)
    {
        battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
    }
    else if (battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 2;
    }
    else
    {
        battle_weather.flags.sandstorm = 1;
        battle_communication_struct.multistring_chooser = 3;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_SMOOTHROCK)
            battle_effects_duration.weather_dur = 8;
        else
            battle_effects_duration.weather_dur = 5;
    }
    return;
}

void atkBB_set_sunny()
{
    battlescripts_curr_instruction++;
    if (battle_weather.flags.air_current || battle_weather.flags.heavy_rain)
    {
        battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
    }
    else if (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 2;
    }
    else
    {
        battle_weather.flags.sun = 1;
        battle_communication_struct.multistring_chooser = 4;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_HEATROCK)
            battle_effects_duration.weather_dur = 8;
        else
            battle_effects_duration.weather_dur = 5;
    }
    return;
}

void atkC8_set_hail()
{
    battlescripts_curr_instruction++;
    if (battle_weather.flags.air_current || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain)
    {
        battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
    }
    else if (battle_weather.flags.hail || battle_weather.flags.permament_hail)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 2;
    }
    else
    {
        battle_weather.flags.hail = 1;
        battle_communication_struct.multistring_chooser = 5;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_ICYROCK)
            battle_effects_duration.weather_dur = 8;
        else
            battle_effects_duration.weather_dur = 5;
    }
    return;
}

void atk7E_set_reflect()
{
    battlescripts_curr_instruction++;
    u8 side = is_bank_from_opponent_side(bank_attacker);
    if (side_affecting_halfword[side].reflect_on)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 0;
    }
    else
    {
        side_affecting_halfword[side].reflect_on = 1;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_LIGHTCLAY)
            side_timers[side].reflect_timer = 8;
        else
            side_timers[side].reflect_timer = 5;
        side_timers[side].reflect_bank = bank_attacker;
        if (battle_flags.double_battle && count_alive_pokes_on_side(1) == 2)
            battle_communication_struct.multistring_chooser = 2;
        else
            battle_communication_struct.multistring_chooser = 1;
    }
    return;
}

void atk92_set_lightscreen()
{
    battlescripts_curr_instruction++;
    u8 side = is_bank_from_opponent_side(bank_attacker);
    if (side_affecting_halfword[side].light_screen_on)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 0;
    }
    else
    {
        side_affecting_halfword[side].light_screen_on = 1;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_LIGHTCLAY)
            side_timers[side].lightscreen_timer = 8;
        else
            side_timers[side].lightscreen_timer = 5;
        side_timers[side].lightscreen_bank = bank_attacker;
        if (battle_flags.double_battle && count_alive_pokes_on_side(1) == 2)
            battle_communication_struct.multistring_chooser = 4;
        else
            battle_communication_struct.multistring_chooser = 3;
    }
    return;
}

u8 is_of_type(u8 bank, u8 type);

void atk96_weather_damage()
{
    battlescripts_curr_instruction++;
    s32 damage = 0;
    u8 ability = battle_participants[bank_attacker].ability_id;
    u8 ability_effect = has_ability_effect(bank_attacker, 0, 1);
    if (weather_abilities_effect() && !(get_item_effect(bank_attacker, 1) == ITEM_EFFECT_SAFETYGOOGLES) && !(ability_effect && ability == ABILITY_MAGIC_GUARD) &&!(hit_flags_for_banks & bits_table[bank_attacker]))
    {
        if (battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm)
        {
            if (!(is_of_type(bank_attacker, TYPE_GROUND) && is_of_type(bank_attacker, TYPE_STEEL) && is_of_type(bank_attacker, TYPE_ROCK)) && !(ability_effect && (ability == ABILITY_SAND_FORCE || ability == ABILITY_SAND_RUSH)))
            {
                if (!(status3[bank_attacker].underground || status3[bank_attacker].underwater))
                {
                    damage = battle_participants[bank_attacker].max_hp >> 4;
                    if (damage == 0)
                        damage = 1;
                }
            }
        }
        else if (battle_weather.flags.hail || battle_weather.flags.permament_hail)
        {
            if (!(is_of_type(bank_attacker, TYPE_ICE)) && !(ability_effect && (ability == ABILITY_SNOW_CLOAK)))
            {
                if (!(status3[bank_attacker].underground || status3[bank_attacker].underwater))
                {
                    damage = battle_participants[bank_attacker].max_hp >> 4;
                    if (damage == 0)
                        damage = 1;

                    if (ability_effect && ability == ABILITY_ICE_BODY)
                        damage *= -1;
                }
            }
        }
    }
    damage_loc = damage;
    return;
}

void atkE2_switchout_abilities()
{
    active_bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
    if (has_ability_effect(active_bank, 0, 1))
    {
        u8 second_arg = bits_table[battle_stuff_ptr.ptr->field_58[active_bank]];
        switch (battle_participants[active_bank].ability_id)
        {
        case ABILITY_NATURAL_CURE:
            battle_participants[active_bank].status.int_status = 0;
            prepare_setattributes_in_battle(0, 0x28, second_arg, 4, &battle_participants[active_bank].status);
            mark_buffer_bank_for_execution(active_bank);
            break;
        case ABILITY_REGENERATOR:
            {
                u16 *current_hp = &battle_participants[active_bank].current_hp;
                u16 *max_hp = &battle_participants[active_bank].max_hp;
                if (current_hp)
                {
                    u8 added_hp = __udivsi3(*max_hp, 3);
                    if (*current_hp + added_hp > *max_hp)
                    {
                        added_hp = *max_hp - *current_hp;
                    }
                    *current_hp += added_hp;
                    prepare_setattributes_in_battle(0, 0x2A, second_arg, 4, current_hp);
                    mark_buffer_bank_for_execution(active_bank);
                }
                break;
            }
        }
    }
    battlescripts_curr_instruction += 2;
    return;
}

void atk8D_multihit_move_loop_counter()
{
    if (read_byte(battlescripts_curr_instruction + 1) == 0)
        multihit_counter = 0;
    else
    {
        if (has_ability_effect(bank_attacker, 0, 1) && battle_participants[bank_attacker].ability_id == ABILITY_SKILL_LINK)
            multihit_counter = 5;
        else
            multihit_counter = __umodsi3(rng(), 4) + 2;
    }
    battlescripts_curr_instruction += 2;
    return;
}

void atk42_jump_if_type()
{
    if (is_of_type(get_battle_bank(read_byte(battlescripts_curr_instruction + 1)), read_byte(battlescripts_curr_instruction + 2)))
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction + 3);
    else
        battlescripts_curr_instruction += 7;
    return;
}

void atk7F_set_leech_seed()
{
    if (move_outcome.missed || move_outcome.not_affected || move_outcome.failed || status3[bank_target].leech_seed)
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 1;
    }
    else if (is_of_type(bank_target, TYPE_GRASS))
    {
        move_outcome.missed = 1;
        battle_communication_struct.multistring_chooser = 2;
    }
    else
    {
        status3[bank_target].leech_seed_hp_receiver |= bank_attacker;
        status3[bank_target].leech_seed = 1;
        battle_communication_struct.multistring_chooser = 0;
    }
    return;
}

u16 get_airborne_state(u8 bank, u8 mode, u8 check_levitate);
u16 apply_type_effectiveness(u16 chained_effect, u8 move_type, u8 target_bank, u8 atk_bank, u8 airstatus);
u16 get_1_8_of_max_hp(u8 bank);
u8 can_poison(u8 bank, u8 self_inflicted);

u8 entry_hazards_hook()
{
    u8 effect = 0;
    u8 banks_side = is_bank_from_opponent_side(active_bank);
    struct side_affecting* ptr_to_struct = &new_battlestruct.ptr->side_affecting[banks_side];
    if (side_affecting_halfword[banks_side].spikes_on && !(side_affecting_halfword[banks_side].spikes_damage_done) && get_airborne_state(active_bank, 0, 1) <= 2)
    {
        side_affecting_halfword[banks_side].spikes_damage_done = 1;
        if (has_ability_effect(active_bank, 0, 1) && battle_participants[active_bank].ability_id == ABILITY_MAGIC_GUARD)
        {
            damage_loc = 0;
        }
        else
        {
            u32 damage = __udivsi3(battle_participants[active_bank].max_hp, 5 - side_timers[banks_side].spikes_amount);
            if (damage == 0)
                damage = 1;
            damage_loc = damage;
        }
        battlescript_push();
        battlescripts_curr_instruction = &spikes_bs;
        effect = 1;
    }
    else if (ptr_to_struct->stealthrock && !ptr_to_struct->stealthrock_done)
    {
        ptr_to_struct->stealthrock_done = 1;
        if (has_ability_effect(active_bank, 0, 1) && battle_participants[active_bank].ability_id == ABILITY_MAGIC_GUARD)
        {
            damage_loc = 0;
        }
        else
        {
            u32 damage = get_1_8_of_max_hp(active_bank);
            damage = (damage * apply_type_effectiveness(64, TYPE_ROCK, active_bank, active_bank ^1, get_airborne_state(active_bank, 1, 0))) >> 6;
            if (damage == 0)
                damage = 1;
            damage_loc = damage;
        }
        battlescript_push();
        battlescripts_curr_instruction = &stealhrock_bs;
        effect = 1;
    }
    else if (ptr_to_struct->sticky_web && !ptr_to_struct->sticky_web_done && battle_participants[active_bank].spd_buff != 0 && get_airborne_state(active_bank, 0, 1) <= 2)
    {
        ptr_to_struct->sticky_web_done = 1;
        battlescript_push();
        battlescripts_curr_instruction = &stickyweb_bs;
        battle_scripting.stat_changer = 0x93;
        effect = 1;
    }
    else if (ptr_to_struct->toxic_spikes_psn && !ptr_to_struct->toxic_spikes_done && get_airborne_state(active_bank, 0, 1) <= 2)
    {
        ptr_to_struct->toxic_spikes_done = 1;
        if (is_of_type(active_bank, TYPE_POISON))
        {
            effect = 1;
            ptr_to_struct->toxic_spikes_psn = 0;
            battlescript_push();
            battlescripts_curr_instruction = &toxicpikes_absorbed;
        }
        else if (can_poison(active_bank, 0))
        {
            if (ptr_to_struct->toxic_spikes_badpsn)
                battle_participants[active_bank].status.flags.toxic_poison = 1;
            else
                battle_participants[active_bank].status.flags.poison = 1;
            battlescript_push();
            battlescripts_curr_instruction = &toxicspikes_bs;
            effect = 1;
            prepare_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[active_bank].status.flags);
            mark_buffer_bank_for_execution(active_bank);
        }
    }
    if (effect)
    {
       new_battlestruct.ptr->various.var1 = active_bank;
       battle_participants[active_bank].status2.destinny_bond = 0;
       hitmarker &= 0xFFFFFFBF; //same as above
    }
    return effect;
}

void switchin_newstruct_update()
{
    struct bank_affecting* ptr_to_struct = &new_battlestruct.ptr->bank_affecting[active_bank];
    struct bank_affecting previous_struct = new_battlestruct.ptr->bank_affecting[active_bank];
    memset(ptr_to_struct, 0, sizeof(struct bank_affecting));
    ptr_to_struct->type3 = TYPE_EGG;
    ptr_to_struct->just_switched_in = 1;
    if (current_move == MOVE_BATON_PASS)
    {
        ptr_to_struct->aqua_ring = previous_struct.aqua_ring;
        ptr_to_struct->embargo = previous_struct.embargo;
        ptr_to_struct->powertrick = previous_struct.powertrick;
        ptr_to_struct->gastro_acided = previous_struct.gastro_acided;
    }
    struct side_affecting* side_ptr = &new_battlestruct.ptr->side_affecting[is_bank_from_opponent_side(active_bank)];
    side_ptr->stealthrock_done = 0;
    side_ptr->sticky_web_done = 0;
    side_ptr->toxic_spikes_done = 0;
    return;
}
