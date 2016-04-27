#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "battlescripts.h"
#include "new_battle_struct.h"

struct natural_gift{
    u8 move_power;
    u8 move_type;
};

struct natural_gift natural_gift_table[] = { {0xFF, 0} ,{80, TYPE_FIRE}, {80, TYPE_WATER}, {80, TYPE_ELECTRIC}, {80, TYPE_GRASS}, {80, TYPE_ICE}, {80, TYPE_FIGHTING}, {80, TYPE_POISON}, {80, TYPE_GROUND}, {80, TYPE_FLYING}, {80, TYPE_PSYCHIC}, {80, TYPE_BUG}, {80, TYPE_ROCK}, {80, TYPE_GHOST}, {80, TYPE_DRAGON}, {80, TYPE_DARK}, {80, TYPE_STEEL}, {90, TYPE_FIRE}, {90, TYPE_WATER}, {90, TYPE_ELECTRIC}, {90, TYPE_GRASS}, {90, TYPE_ICE}, {90, TYPE_FIGHTING}, {90, TYPE_POISON}, {90, TYPE_GROUND}, {90, TYPE_FLYING}, {90, TYPE_PSYCHIC}, {90, TYPE_BUG}, {90, TYPE_ROCK}, {90, TYPE_GHOST}, {90, TYPE_DRAGON}, {90, TYPE_DARK}, {90, TYPE_STEEL}, {100, TYPE_FIRE}, {100, TYPE_WATER}, {100, TYPE_ELECTRIC}, {100, TYPE_FIGHTING}, {100, TYPE_POISON}, {100, TYPE_GROUND}, {100, TYPE_FLYING}, {100, TYPE_PSYCHIC}, {100, TYPE_BUG} };;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


u16 chain_modifier(u16 curr_modifier, u16 new_modifier)
{
    u16 updated_modifier;
    if (curr_modifier == 0)
    {
        updated_modifier = new_modifier;
    }
    else
    {
        u32 calculations = (curr_modifier * new_modifier + 0x800) >> 12;
        updated_modifier = calculations;
    }
    return updated_modifier;
}

u32 apply_modifier(u16 modifier, u32 value)
{
    u32 multiplication = modifier * value;
    u32 anding_result = 0xFFF & multiplication;
    u32 new_value = multiplication >> 0xC;
    if (anding_result > 0x800)
    {
        new_value++;
    }
    return new_value;
}

u16 get_poke_weight(u8 bank)
{
    u16 poke_weight = get_height_or_weight(species_to_national_dex(battle_participants[bank].poke_species), 1);
    if (has_ability_effect(bank, 1, 1))
    {
        switch (battle_participants[bank].ability_id)
        {
            case ABILITY_HEAVY_METAL:
                poke_weight *= 2;
                break;
            case ABILITY_LIGHT_METAL:
                poke_weight >>= 1;
                break;
        }
    }
    if (get_item_effect(bank, 1) == ITEM_EFFECT_FLOATSTONE)
    {
        poke_weight *= 2;
    }

    poke_weight -= 1000 * new_battlestruct.ptr->bank_affecting[bank].autonomize_uses;
    if (poke_weight < 1)
        poke_weight = 1;

    return poke_weight;
}

u8 can_consume_item(u8 bank)
{
    if (battle_participants[bank].ability_id == ABILITY_KLUTZ || battle_participants[bank].ability_id == ABILITY_KLUTZ || new_battlestruct.ptr->field_affecting.magic_room || new_battlestruct.ptr->bank_affecting[bank].embargo || (get_item_pocket_id(battle_participants[bank].held_item) == 4 && ability_battle_effects(12, 0, ABILITY_UNNERVE, 0, 0)))
     {
        return false;
    }
    else
    {
        return true;
    }
}

u16 get_base_power(u16 move, u8 atk_bank, u8 def_bank)
{
    u16 base_power = move_table[move].base_power;
    //u8 banks_side = get_battle_side(bank) & 1;
    u8 atk_ally_bank = atk_bank ^ 2;
    switch (move)
    {
        case MOVE_GRASS_PLEDGE:
            if (chosen_move_by_banks[atk_ally_bank] == MOVE_FIRE_PLEDGE || chosen_move_by_banks[atk_ally_bank] == MOVE_WATER_PLEDGE)
            {
                base_power = 150;
            }
            break;
        case MOVE_FIRE_PLEDGE:
            if (chosen_move_by_banks[atk_ally_bank] == MOVE_GRASS_PLEDGE || chosen_move_by_banks[atk_ally_bank] == MOVE_WATER_PLEDGE)
            {
                base_power = 150;
            }
            break;
        case MOVE_WATER_PLEDGE:
            if (chosen_move_by_banks[atk_ally_bank] == MOVE_FIRE_PLEDGE || chosen_move_by_banks[atk_ally_bank] == MOVE_GRASS_PLEDGE)
            {
                base_power = 150;
            }
            break;
        case MOVE_FLING:
            {
                //TO DO
                break;
            }
        case MOVE_ROLLOUT:
        case MOVE_MAGNITUDE:
        case MOVE_PRESENT:
        case MOVE_FURY_CUTTER:
        case MOVE_FLAIL:
        case MOVE_REVERSAL:
        case MOVE_ERUPTION:
        case MOVE_WATER_SPOUT:
        case MOVE_RETURN:
        case MOVE_FRUSTRATION:
        case MOVE_SPIT_UP:
            base_power = dynamic_base_power;
            break;
        case MOVE_REVENGE:
        case MOVE_AVALANCHE:
            base_power *= battle_scripting.damage_multiplier;
            break;
        case MOVE_NATURAL_GIFT:
            if (can_consume_item(atk_bank))
            {
                u8 berryID = itemid_to_berryid(battle_participants[atk_bank].held_item);
                base_power = natural_gift_table[berryID].move_power;
                battle_stuff_ptr.ptr->dynamic_move_type = natural_gift_table[berryID].move_type;
            }
            break;
        case MOVE_BRINE:
            if (battle_participants[def_bank].current_hp >= (battle_participants[def_bank].max_hp >> 1))
            {
                base_power <<= 1;
            }
            break;
        case MOVE_VENOSHOCK:
            if (battle_participants[def_bank].status.flags.poison || battle_participants[def_bank].status.flags.toxic_poison)
            {
                base_power <<= 1;
            }
            break;
        case MOVE_WAKEUP_SLAP:
            if (battle_participants[def_bank].status.flags.sleep)
            {
                base_power *= 2;
            }
            break;
        case MOVE_WRING_OUT:
        case MOVE_CRUSH_GRIP:
            {
                u16 wringout_power = __udivsi3(battle_participants[def_bank].current_hp, battle_participants[def_bank].max_hp);
                wringout_power = 120 * wringout_power;
                if (wringout_power < 1)
                {
                    wringout_power = 1;
                }
                base_power = wringout_power;
                break;
            }
        case MOVE_HEX:
            if (battle_participants[def_bank].status.int_status)
            {
                base_power *= 2;
            }
            break;
        case MOVE_ASSURANCE:
            if (special_statuses[def_bank].moveturn_losthp_physical || special_statuses[def_bank].moveturn_losthp_special)
            {
                base_power *= 2;
            }
            break;
        case MOVE_TRUMP_CARD:
            {
                s8 pp_slot = get_move_position(atk_bank, MOVE_TRUMP_CARD);
                u8 pp;
                if (pp_slot == -1)
                {
                    pp = 4;
                }
                else
                {
                    pp = battle_participants[atk_bank].current_pp[pp_slot];
                }
                switch (pp)
                {
                case 0:
                    base_power = 200;
                    break;
                case 1:
                    base_power = 80;
                    break;
                case 2:
                    base_power = 60;
                    break;
                case 3:
                    base_power = 50;
                    break;
                default:
                    base_power = 40;
                    break;
                }
                break;
            }
        case MOVE_ACROBATICS:
            if (!battle_participants[atk_bank].held_item)
            {
                base_power *= 2;
            }
            break;
        case MOVE_LOW_KICK:
        case MOVE_GRASS_KNOT:
            {
                u16 defender_weight = get_poke_weight(def_bank);
                if (defender_weight < 100)
                    base_power = 20;
                else if (defender_weight < 250)
                    base_power = 40;
                else if (defender_weight < 500)
                    base_power = 60;
                else if (defender_weight < 1000)
                    base_power = 80;
                else if (defender_weight < 2000)
                    base_power = 100;
                else
                    base_power = 120;
                break;
            }
        case MOVE_HEAT_CRASH:
        case MOVE_HEAVY_SLAM:
            {
                u16 weight_difference = __udivsi3(get_poke_weight(atk_bank), get_poke_weight(def_bank));
                break;
            }

    }
    return base_power;
}

