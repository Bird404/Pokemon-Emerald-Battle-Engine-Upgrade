#include "defines.h"
#include "static_references.h"

bool load_weather_from_overworld();
bool handle_primal_reversion(u8 bank);
bool check_ability(u8 bank, u8 ability);
bool find_move_in_table(u16 move, const u16* table_ptr);
u8 healblock_forbidden_moves(u16 move, u8 with_leechseed);
u8 gravity_forbidden_move(u16 move);
u8 embargo_forbidden_move(u16 move);
u16 get_item_extra_param(u16 item);
u16 get_mega_species(u8 bank, u8 chosen_method);
struct pokemon* get_party_ptr(u8 bank);
u8 is_poke_valid(struct pokemon* poke);
bool is_bank_present(u8 bank);
u8 handle_leppa(u8 bank, u8 quality, enum call_mode calling_mode);
u8 ability_battle_effects(u8 switch_id, u8 bank, u8 ability_to_check, u8 special_cases_argument, u16 move);
u8 count_party_pokemon(u8 bank);
u8* get_slide_msg(u16 trainerID, u8 caseID);
u8 not_magicguard(u8 bank);
bool does_move_make_contact(u16 move, u8 atk_bank);
void reset_terrains(struct field_affecting* field);
u8 terrains_get_turns(u8 bank);
s8 get_priority(u16 move, u8 bank);
u8 cant_fall_asleep(u8 bank, u8 self_inflicted);
u8 cant_become_burned(u8 bank, u8 self_inflicted);
u8 cant_become_freezed(u8 bank, u8 self_inflicted);
u8 cant_become_paralyzed(u8 bank, u8 self_inflicted);
u8 cant_poison(u8 atk_bank, u8 def_bank, u8 self_inflicted);
void move_to_buff1(u16 move);
u8 change_stats(u8 bank, u8 bits, void* bs_unable);
u8 item_battle_effects(u8 switchid, u8 bank, u8 move_turn);
u8 cant_become_confused(u8 bank);
u8 get_item_effect(u8 bank, bool check_negating_effects);
bool has_ability_effect(u8 bank, u8 mold_breaker);
bool weather_abilities_effect(void);

u8 get_battle_bank(u8 to_get)
{
    switch (to_get)
    {
    case 0: //target
        return bank_target;
    case 1: //attacker
        return bank_attacker;
    case 2: //target partner
        return bank_partner_def;
    case 3: //attacker partner
    case 5:
        return bank_partner_atk;
    case 10: //scripting active
        return battle_scripting.active_bank;
    case 4: case 6: case 8: case 9:
    case 11:
        return get_bank_by_player_ai(0);
    case 12:
        return get_bank_by_player_ai(1);
    case 13:
        return get_bank_by_player_ai(2);
    case 14:
        return get_bank_by_player_ai(3);
    case 15: //bank in the newbattlestruct
        return new_battlestruct->various.active_bank;
    case 7:
    default:
        return 0;
    }
}

u8 get_attacking_move_type(void)
{
    u8 move_type=battle_stuff_ptr->dynamic_move_type&0x3F;
    if(!move_type)
    {
        if(check_ability(bank_attacker,ABILITY_NORMALIZE))
            move_type = TYPE_NORMAL;
        else
            move_type = move_table[current_move].type;
    }
    return move_type;
}

bool is_of_type(u8 bank, u8 type)
{
    if (battle_participants[bank].type1 == type || battle_participants[bank].type2 == type || new_battlestruct->bank_affecting[bank].type3 == type)
        return true;
    else
        return false;
}

void set_type(u8 bank, u8 type)
{
    battle_participants[bank].type1 = type;
    battle_participants[bank].type2 = type;
    new_battlestruct->bank_affecting[bank].type3 = type;
}

bool percent_chance(u8 percent)
{
    if (__umodsi3(rng(), 100) + 1 <= percent) {return true;}
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

void copy_status_condition_text(u8 bank, u8 confusion)
{
    const u8* status_flag = NULL;
    if (battle_participants[bank].status.flags.sleep)
    {
        status_flag = sleep_status_flag;
    }
    else if (BANK_PSN(bank))
    {
        status_flag = poison_status_flag;
    }
    else if (battle_participants[bank].status.flags.freeze)
    {
        status_flag = freeze_status_flag;
    }
    else if (battle_participants[bank].status.flags.paralysis)
    {
        status_flag = paralysis_status_flag;
    }
    else if (battle_participants[bank].status.flags.burn)
    {
        status_flag = burn_status_flag;
    }
    else if (confusion && battle_participants[bank].status2.confusion)
    {
        status_flag = (void*)0x0831BC98;
    }
    else
        return;
    strcpy_xFF_terminated_0(battle_text_buff1, status_flag);
}

const u8 type_effectiveness_table[TYPE_FAIRY-0x4][TYPE_FAIRY-0x4] = {
    {10,10,10,10,10,05,10,00,05,10,10,10,10,10,10,10,10,10,10}, //normal
    {20,10,05,05,10,20,05,00,20,10,10,10,10,10,05,20,10,20,05}, //fight
    {10,20,10,10,10,05,20,10,05,10,10,10,20,05,10,10,10,10,10}, //flying
    {10,10,10,05,05,05,10,05,00,10,10,10,20,10,10,10,10,10,20}, //poison
    {10,10,00,20,10,20,05,10,20,10,20,10,05,20,10,10,10,10,10}, //ground
    {10,05,20,10,05,10,20,10,05,10,20,10,10,10,10,20,10,10,10}, //rock
    {10,05,05,05,10,10,10,05,05,10,05,10,20,10,20,10,10,20,05}, //bug
    {00,10,10,10,10,10,10,20,10,10,10,10,10,10,20,10,10,05,10}, //ghost
    {10,10,10,10,10,20,10,10,05,10,05,05,10,05,10,20,10,10,20}, //steel
    {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}, //egg
    {10,10,10,10,10,05,20,10,20,10,05,05,20,10,10,20,05,10,10}, //fire
    {10,10,10,10,20,20,10,10,10,10,20,05,05,10,10,10,05,10,10}, //water
    {10,10,05,05,20,20,05,10,05,10,05,20,05,10,10,10,05,10,10}, //grass
    {10,10,20,10,00,10,10,10,10,10,10,20,05,05,10,10,05,10,10}, //electric
    {10,20,10,20,10,10,10,10,05,10,10,10,10,10,05,10,10,00,10}, //psychic
    {10,10,20,10,20,10,10,10,05,10,05,05,20,10,10,05,20,10,10}, //ice
    {10,10,10,10,10,10,10,10,05,10,10,10,10,10,10,10,20,10,00}, //dragon
    {10,05,10,10,10,10,10,20,10,10,10,10,10,10,20,10,10,05,05}, //dark
    {10,20,10,05,10,10,10,10,05,10,05,10,10,10,10,10,20,20,10}  //fairy
};

u16 get_airborne_state(u8 bank, u8 mode, u8 check_levitate)
{
    // return 0 grounded due to gravity
    // return 1 grounded due to iron ball or smack down or ingrain
    // return 2 for not grounded nor airborne
    // return 3 airborne due to flying type or telekinesis
    // return 4 airborne due to levitate
    // mode 1 for damage calc && 0 for hazards etc.
    if (new_battlestruct->field_affecting.gravity)
        return 0;
    if (get_item_effect(bank, true) == ITEM_EFFECT_IRONBALL
        || new_battlestruct->bank_affecting[bank].smacked_down
        || status3[bank].rooted)
        return 1;
    if (check_levitate && battle_participants[bank].ability_id == ABILITY_LEVITATE && has_ability_effect(bank,mode))
        return 4;
    if ((mode==0 && is_of_type(bank,TYPE_FLYING)) || get_item_effect(bank, true) == ITEM_EFFECT_AIRBALLOON ||
        new_battlestruct->bank_affecting[bank].magnet_rise || new_battlestruct->bank_affecting[bank].telekinesis)
        return 3;
    return 2;
}

void handle_type_immune_ability(u8 def_bank, u8 string_chooser, u8 ability)
{
    move_outcome.missed=1;
    move_outcome.failed=1;
    move_outcome.not_affected=1;
    last_used_ability=ability;
    move_hit_with_pbs[def_bank]=0;
    move_type_hit_with_pbs[def_bank]=0;
    record_usage_of_ability(def_bank,ability);
    battle_communication_struct.field6=string_chooser;
}

u16 damage_type_effectiveness_update(u16 move, u8 attacking_type, u8 defending_type, u8 atk_bank, u8 def_bank, u16 chained_effect, u8 airstatus)
{
    u8 effect,atype=attacking_type,dtype=defending_type;
    if(!chained_effect || atype==TYPE_EGG || dtype==TYPE_EGG)
        return chained_effect;

    if(atype>=TYPE_FAIRY)
        atype=atype-5;

    if(dtype>=TYPE_FAIRY)
        dtype=dtype-5;

    effect=type_effectiveness_table[atype][dtype];

    if (new_battlestruct->various.inverse_battle)
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

    if ((((attacking_type == TYPE_NORMAL || attacking_type == TYPE_FIGHTING) && defending_type == TYPE_GHOST && ((battle_participants[def_bank].status2.foresight))) || battle_participants[atk_bank].ability_id == ABILITY_SCRAPPY) && effect == 0)
    {
        effect = 10;
    }

    else if ((attacking_type == TYPE_PSYCHIC) && defending_type == TYPE_DARK && new_battlestruct->bank_affecting[def_bank].miracle_eyed && effect == 0)
    {
        effect = 10;
    }

    else if (effect == 0 && (get_item_effect(def_bank, true) == ITEM_EFFECT_RINGTARGET))
    {
        effect = 10;
    }
    else if (battle_weather.flags.air_current && defending_type == TYPE_FLYING && effect == 20 && weather_abilities_effect())
    {
        effect = 10;
    }
    else if (attacking_type == TYPE_GROUND)
    {
        if(effect == 0 && (airstatus<2 || move==MOVE_THOUSAND_ARROWS)) // grounded pokemon
            effect = 10;
        else if(airstatus>2 && move!=MOVE_THOUSAND_ARROWS)
            effect = 0;
    }
    else if (move == MOVE_FREEZEDRY && defending_type == TYPE_WATER)
    {
        effect = 20;
    }
    switch(effect)
    {
        case 0:
            chained_effect = 0;
            break;
        case 5:
            chained_effect = chained_effect>>1;
            break;
        case 20:
            chained_effect = chained_effect<<1;
            break;
    }
    return chained_effect;
}

u16 apply_type_effectiveness(u16 move, u16 chained_effect, u8 move_type, u8 target_bank, u8 atk_bank, u8 airstatus)
{
    u8 defender_type1 = battle_participants[target_bank].type1;
    u8 defender_type2 = battle_participants[target_bank].type2;
    u8 defender_type3 = new_battlestruct->bank_affecting[target_bank].type3;
    //set different types
    if (defender_type2 == defender_type1)
        defender_type2 = TYPE_EGG;
    if (defender_type3 == defender_type1 || defender_type3 == defender_type2)
        defender_type3 = TYPE_EGG;
    chained_effect = damage_type_effectiveness_update(move, move_type, defender_type1, atk_bank, target_bank, chained_effect, airstatus);
    chained_effect = damage_type_effectiveness_update(move, move_type, defender_type2, atk_bank, target_bank, chained_effect, airstatus);
    chained_effect = damage_type_effectiveness_update(move, move_type, defender_type3, atk_bank, target_bank, chained_effect, airstatus);
    return chained_effect;
}

u16 type_effectiveness_calc(u16 move, u8 move_type, u8 atk_bank, u8 def_bank, u8 effects_handling_and_recording)
{
    u8 airstatus = get_airborne_state(def_bank,1,effects_handling_and_recording);
    u16 chained_effect = 64;
    if (find_move_in_table(move, dual_type_moves))
    {
        chained_effect = apply_type_effectiveness(move, chained_effect, move_table[move].arg2,
                                                  def_bank, atk_bank, airstatus);
    }
    chained_effect = apply_type_effectiveness(move, chained_effect, move_type, def_bank, atk_bank, airstatus);
    if(chained_effect>64)
        move_outcome.super_effective=1;
    else if (chained_effect==0)
        move_outcome.not_affected=1;
    else if (chained_effect<64)
        move_outcome.not_very_effective=1;
    if(effects_handling_and_recording)
    {
        if(!move_outcome.super_effective && check_ability(def_bank,ABILITY_WONDER_GUARD))
        {
            chained_effect = 0;
            handle_type_immune_ability(def_bank,3,ABILITY_WONDER_GUARD);
        }
        else if(airstatus == 4 && chained_effect == 0 && move_type == TYPE_GROUND)
            handle_type_immune_ability(def_bank,4,ABILITY_LEVITATE);
        if(move_outcome.not_affected)
            protect_structs[atk_bank].flag1_noteffective=1;
    }
    return chained_effect;
}

void record_usage_of_move(u8 bank, u16 move)
{
    u16 *slot = &battle_resources->battle_history->used_moves[bank].moves[0];
    for (u8 i = 0; i < 4; i++)
    {
        u16* slot_move = &slot[i];
        if (*slot_move == move) {break;} //move is already recorded
        if (*slot_move == 0)
        {
            *slot_move = move;
            break;
        }
    }
}

void steal_bank_item(u8 thief_bank, u8 victim_bank)
{
    u16 item = battle_participants[victim_bank].held_item;
    //remove victim's item
    battle_participants[victim_bank].held_item = 0;
    active_bank = victim_bank;
    bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, &battle_participants[victim_bank].held_item);
    mark_buffer_bank_for_execution(victim_bank);

    //set item to the thief
    battle_participants[thief_bank].held_item = item;
    active_bank = thief_bank;
    bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, &battle_participants[thief_bank].held_item);
    mark_buffer_bank_for_execution(thief_bank);

    //set the item to the global variable
    last_used_item = item;
}

bool try_stealing_bank_item(u8 thief_bank, u8 victim_bank)
{
    if (battle_participants[victim_bank].held_item && !battle_participants[thief_bank].held_item)
    {
        steal_bank_item(thief_bank, victim_bank);
        return 1;
    }
    return 0;
}

u8 cant_poison(u8 atk_bank, u8 def_bank, u8 self_inflicted)
{   //0 == can poison
    //1 == is already poisoned
    //2 == has other major condition
    //3 == type doesn't allow it
    //4 == ability doesn't allow it
    //5 == safeguard protection
    //8 == misty terrain doesn't allow it
    if (battle_participants[def_bank].status.flags.poison || battle_participants[def_bank].status.flags.toxic_poison)
        return 1;
    if (battle_participants[def_bank].status.int_status)
        return 2;
    if ((is_of_type(def_bank, TYPE_POISON) || is_of_type(def_bank, TYPE_STEEL)) && atk_bank != def_bank && !self_inflicted && !check_ability(atk_bank, ABILITY_CORROSION))
        return 3;
    if ((has_ability_effect(def_bank, 0) && (battle_participants[def_bank].ability_id == ABILITY_IMMUNITY || (battle_participants[def_bank].ability_id == ABILITY_LEAF_GUARD && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)))))
        return 4;
    if (side_affecting_halfword[is_bank_from_opponent_side(def_bank)].safeguard_on && !self_inflicted)
        return 5;
    if (new_battlestruct->field_affecting.misty_terrain && get_airborne_state(def_bank, 1, 1) <= 2 && !self_inflicted)
        return 8;
    return 0;
}

u8 cant_fall_asleep(u8 bank, u8 self_inflicted)
{
    //0 == can fall asleep
    //1 == can't because it's already asleep
    //2 == can't because it has other major status condition
    //3 == can't because type doesn't allow it, currently doesn't exist
    //4 == can't because an ability protects it
    //5 == can't because it's protected by safeguard
    //6 == can't because there's an uproar
    //8 == misty terrain doesn't allow it
    //9 == electric terrain doesn't allow it
    if (battle_participants[bank].status.flags.sleep)
        return 1;
    if (battle_participants[bank].status.int_status)
        return 2;
    if ((has_ability_effect(bank, 0) && (battle_participants[bank].ability_id == ABILITY_VITAL_SPIRIT || battle_participants[bank].ability_id == ABILITY_INSOMNIA || (battle_participants[bank].ability_id == ABILITY_LEAF_GUARD && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)))))
        return 4;
    if (side_affecting_halfword[is_bank_from_opponent_side(bank)].safeguard_on && !self_inflicted)
        return 5;
    if (!check_ability(bank, ABILITY_SOUNDPROOF))
    {
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (battle_participants[bank].status2.uproar)
                return 6;
        }
    }
    if (new_battlestruct->field_affecting.misty_terrain && get_airborne_state(bank, 1, 1) <= 2 && !self_inflicted)
        return 8;
    if (new_battlestruct->field_affecting.electic_terrain && get_airborne_state(bank, 1, 1) <= 2 && !self_inflicted)
        return 9;
    return 0;
}

u8 cant_become_paralyzed(u8 bank, u8 self_inflicted)
{   //0 == can paralyze
    //1 == is already paralyzed
    //2 == has other major condition
    //3 == type doesn't allow it
    //4 == ability doesn't allow it
    //5 == safeguard protection
    //8 == misty terrain protection
    if (battle_participants[bank].status.flags.paralysis)
        return 1;
    if (battle_participants[bank].status.int_status)
        return 2;
    if (is_of_type(bank, TYPE_ELECTRIC))
        return 3;
    if ((has_ability_effect(bank, 0) && (battle_participants[bank].ability_id == ABILITY_LIMBER || (battle_participants[bank].ability_id == ABILITY_LEAF_GUARD && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)))))
        return 4;
    if (side_affecting_halfword[is_bank_from_opponent_side(bank)].safeguard_on && !self_inflicted)
        return 5;
    if (new_battlestruct->field_affecting.misty_terrain && get_airborne_state(bank, 1, 1) <= 2 && !self_inflicted)
        return 8;
    return 0;
}

u8 cant_become_burned(u8 bank, u8 self_inflicted)
{   //0 == can burn
    //1 == is already burned
    //2 == has other major condition
    //3 == type doesn't allow it
    //4 == ability doesn't allow it
    //5 == safeguard protection
    //8 == misty terrain protection
    if (battle_participants[bank].status.flags.burn)
        return 1;
    if (battle_participants[bank].status.int_status)
        return 2;
    if (is_of_type(bank, TYPE_FIRE))
        return 3;
    if ((has_ability_effect(bank, 0) && (battle_participants[bank].ability_id == ABILITY_WATER_VEIL || (battle_participants[bank].ability_id == ABILITY_LEAF_GUARD && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)))))
        return 4;
    if (side_affecting_halfword[is_bank_from_opponent_side(bank)].safeguard_on && !self_inflicted)
        return 5;
    if (new_battlestruct->field_affecting.misty_terrain && get_airborne_state(bank, 1, 1) <= 2 && !self_inflicted)
        return 8;
    return 0;
}

u8 cant_become_freezed(u8 bank, u8 self_inflicted)
{   //0 == can freeze
    //1 == is already freezed
    //2 == has other major condition
    //3 == type doesn't allow it
    //4 == ability doesn't allow it
    //5 == safeguard protection
    //7 == weather doesn't allow it
    //8 == misty terrain doesn't allow it
    if (battle_participants[bank].status.flags.freeze)
        return 1;
    if (battle_participants[bank].status.int_status)
        return 2;
    if (is_of_type(bank, TYPE_ICE))
        return 3;
    if ((has_ability_effect(bank, 0) && (battle_participants[bank].ability_id == ABILITY_MAGMA_ARMOR || (battle_participants[bank].ability_id == ABILITY_LEAF_GUARD && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)))))
        return 4;
    if (side_affecting_halfword[is_bank_from_opponent_side(bank)].safeguard_on && !self_inflicted)
        return 5;
    if (weather_abilities_effect() && battle_weather.int_bw & (weather_harsh_sun || weather_permament_sun || weather_sun))
        return 7;
    if (new_battlestruct->field_affecting.misty_terrain && get_airborne_state(bank, 1, 1) <= 2 && !self_inflicted)
        return 8;
    return 0;
}

bool poison_heal_check(void)
{
    if (check_ability(active_bank, ABILITY_POISON_HEAL))
    {
        if (!new_battlestruct->bank_affecting[active_bank].heal_block && !FULL_HP(active_bank))
        {
            damage_loc = get_1_8_of_max_hp(active_bank) * -1;
            call_bc_move_exec(BS_ABILITYHPCHANGE_END2);
            record_usage_of_ability(active_bank, ABILITY_POISON_HEAL);
        }
        return 1;
    }
    return 0;
}

u8 check_if_move_failed(u8 bank)
{
    struct protect_struct* failed = &protect_structs[bank];
    if (failed->flag1_confusion_self_damage)
        return 1;
    if (failed->flag1_love_immobility)
        return 1;
    if (failed->flag1_used_disabled_move)
        return 1;
    if (failed->flag1_used_imprisoned_move)
        return 1;
    if (failed->flag2_used_taunted_move)
        return 1;
    if (failed->flag2_flinch_immobility)
        return 1;
    if (failed->flag1_noteffective)
        return 1;
    if (new_battlestruct->bank_affecting[bank].move_failed)
        return 1;
    return 0;
}

u8 affected_by_substitute(u8 substitute_bank);

u8 canlose_megastone(u8 bank, u16 item)
{
    if (get_item_battle_function(item) == ITEM_EFFECT_MEGASTONE)
    {
        u16* item_ptr = &battle_participants[bank].held_item;
        u16 holding_item = *item_ptr;
        *item_ptr = item;
        u8 ret = 1;
        u8 evo_byte;
        if (is_bank_from_opponent_side(bank))
            evo_byte = new_battlestruct->mega_related.ai_party_mega_check;
        else
            evo_byte = new_battlestruct->mega_related.party_mega_check;
        if (get_mega_species(bank, 0xFB) || evo_byte & bits_table[battle_team_id_by_side[bank]])
        {
            ret = 0;
        }
        *item_ptr = holding_item;
        return ret;
    }
    return 1;
}

bool is_item_a_plate(u16 item)
{
    if (get_item_battle_function(item) == ITEM_EFFECT_PLATES)
        return 1;
    return 0;
}

u8 can_lose_item(u8 bank, u8 stickyhold_check, u8 sticky_message)
{
    u8 can_lose = 1;
    u16 item = battle_participants[bank].held_item;
    u8 item_effect = get_item_effect(bank, 0);
    u16 species = battle_participants[bank].species;
    if (stickyhold_check && battle_participants[bank].ability_id == ABILITY_STICKY_HOLD && has_ability_effect(bank, 1))
    {
        can_lose = 0;
        if (sticky_message)
        {
            battlescript_push();
            battlescripts_curr_instruction = (void*) 0x82DB682;
            last_used_ability = ABILITY_STICKY_HOLD;
            record_usage_of_ability(bank_target, ABILITY_STICKY_HOLD);
        }
    }
    else if (item == ITEM_ENIGMABERRY || item_is_mail(item))
        can_lose = 0;
    else if (!canlose_megastone(bank, item))
        can_lose = 0;
    else if (item_effect == ITEM_EFFECT_GRISEOUSORB && species == POKE_GIRATINA)
        can_lose = 0;
    else if ((item_effect == ITEM_EFFECT_DRIVES) && species == POKE_GENESECT)
        can_lose = 0;
    else if (species == POKE_ARCEUS && is_item_a_plate(item))
        can_lose = 0;
    return can_lose;
}

u8 calculate_effect_chance(u8 bank, u16 move)
{
    u8 effect = move_table[move].effect_chance;
    if (check_ability(bank, ABILITY_SERENE_GRACE) || new_battlestruct->side_affecting[bank&1].rainbow)
        effect *= 2;
    if (effect >= 100 || move == MOVE_SECRET_POWER)
        return 1;
    return percent_chance(effect);
}

bool battle_turn_move_effects(void)
{
    u8 effect = 0;
    hitmarker |= 0x1000020;
    u8* bank = &battle_stuff_ptr->end_turn_checked_bank;
    u8* tracker = &battle_stuff_ptr->end_turn_statetracker1;
    while (*bank < no_of_all_banks)
    {
        active_bank = bank_attacker = turn_order[*bank];
        if (absent_bank_flags & bits_table[active_bank])
        {
            *bank +=1;
        }
        else
        {
            struct bank_affecting* ptr_to_struct = &new_battlestruct->bank_affecting[active_bank];
            u16 current_hp = battle_participants[active_bank].current_hp;
            struct battle_participant* attacker_struct = &battle_participants[active_bank];
            switch (*tracker)
            {
                case 0: //clear new turn stuff for banks
                    ptr_to_struct->electrify = 0;
                    ptr_to_struct->just_switched_in = 0;
                    ptr_to_struct->kings_shield = 0;
                    ptr_to_struct->me_first = 0;
                    ptr_to_struct->powder = 0;
                    ptr_to_struct->quashed = 0;
                    ptr_to_struct->spiky_shield = 0;
                    ptr_to_struct->baneful_bunker = 0;
                    break;
                case 1: //ingrain
                    if (current_hp && current_hp < attacker_struct->max_hp && status3[active_bank].rooted && !ptr_to_struct->heal_block)
                    {
                        damage_loc = get_1_16_of_max_hp(active_bank) * -1;
                        effect = 1;
                        call_bc_move_exec((void*) 0x082DB0EE);
                    }
                    break;
                case 2: //aqua ring
                    if (current_hp && current_hp < attacker_struct->max_hp && ptr_to_struct->aqua_ring && !ptr_to_struct->heal_block)
                    {
                        damage_loc = get_1_16_of_max_hp(active_bank) * -1;
                        effect = 1;
                        hitmarker |= HITMARKER_IGNORE_SUBSTITUTE;
                        call_bc_move_exec(BS_AQUARING);
                    }
                    break;
                case 3: //end turn ability effects
                    if (ability_battle_effects(1, active_bank, 0, 0, 0))
                        effect = 1;
                    break;
                case 4: //item effects
                    if (item_battle_effects(1, active_bank, 0))
                        effect = 1;
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7: //check leech seed
                    if (not_magicguard(active_bank) && status3[active_bank].leech_seed && current_hp && battle_participants[status3[active_bank].leech_seed_hp_receiver].current_hp)
                    {
                        effect = 1;
                        bank_target = status3[active_bank].leech_seed_hp_receiver; //funny this bank is a 'target' of receiving hp and the one losing it is the 'attacker'
                        damage_loc = get_1_8_of_max_hp(bank_attacker);
                        battle_scripting.AnimInfo1 = bank_target;
                        battle_scripting.AnimInfo2 = bank_attacker;
                        call_bc_move_exec(BS_LEECHSEED);
                    }
                    break;
                case 8: //poison
                    if (attacker_struct->status.flags.poison && current_hp && not_magicguard(active_bank))
                    {
                        if (!poison_heal_check())
                        {
                            damage_loc = get_1_8_of_max_hp(active_bank);
                            call_bc_move_exec((void*)0x82DB23D);
                        }
                        effect = 1;
                    }
                    break;
                case 9: //bad poison
                    if (attacker_struct->status.flags.toxic_poison && current_hp && not_magicguard(active_bank))
                    {
                        if (!poison_heal_check())
                        {
                            if (attacker_struct->status.flags.poison_counter != 15)
                                attacker_struct->status.flags.poison_counter++;
                            u32 damage = attacker_struct->max_hp >> 4;
                            if (damage == 0)
                                damage = 1;
                            damage_loc = damage * attacker_struct->status.flags.poison_counter;
                            call_bc_move_exec((void*)0x82DB23D);
                        }
                        effect = 1;
                    }
                    break;
                case 10: //burn
                    if (attacker_struct->status.flags.burn && current_hp && not_magicguard(active_bank))
                    {
                        effect = 1;
                        damage_loc = get_1_8_of_max_hp(active_bank);
                        call_bc_move_exec((void*)0x082DB25F);
                    }
                    break;
                case 11: //check nightmare
                    if (current_hp && attacker_struct->status2.nightmare && not_magicguard(active_bank))
                    {
                        if (attacker_struct->status.flags.sleep)
                        {
                            effect = 1;
                            damage_loc = get_1_4_of_max_hp(active_bank);
                            call_bc_move_exec((void*)0x082DB33F);
                        }
                        else
                        {
                            attacker_struct->status2.nightmare = 0;
                        }
                    }
                    break;
                case 12: //check if cursed
                    if (current_hp && attacker_struct->status2.cursed && not_magicguard(active_bank))
                    {
                        effect = 1;
                        damage_loc = get_1_4_of_max_hp(active_bank);
                        call_bc_move_exec((void*)0x82DB350);
                    }
                    break;
                case 13: //check being trapped in a multiturn attack like wrap or whirpool
                    if (current_hp && attacker_struct->status2.trapped_in_wrap)
                    {
                        u16 trapped_move = battle_stuff_ptr->binding_move[active_bank];
                        move_to_buff1(trapped_move);
                        attacker_struct->status2.trapped_in_wrap--;
                        if (attacker_struct->status2.trapped_in_wrap && not_magicguard(active_bank)) //we're doing damage
                        {
                            battle_scripting.AnimInfo1 = trapped_move;
                            battle_scripting.AnimInfo2 = trapped_move >> 8;
                            if (get_item_effect(battle_stuff_ptr->binded_by[active_bank], 1) == ITEM_EFFECT_BINDINGBAND)
                                damage_loc = ATLEAST_ONE(attacker_struct->max_hp / 6);
                            else
                                damage_loc = get_1_8_of_max_hp(active_bank);

                            call_bc_move_exec((void*) 0x82DB30E);
                        }
                        else if (attacker_struct->status2.trapped_in_wrap == 0) //broke free
                        {
                            call_bc_move_exec((void*)0x82DB320);
                        }
                        effect = 1;
                    }
                    break;
                case 14: //uproar
                    if (attacker_struct->status2.uproar)
                    {
                        for (u8 i = 0; i < no_of_all_banks; i++)
                        {
                            bank_attacker = i;
                            if (battle_participants[i].status.flags.sleep && !(battle_participants[i].ability_id == ABILITY_SOUNDPROOF && has_ability_effect(i, 0)))
                            {
                                battle_participants[i].status.flags.sleep = 0;
                                battle_participants[i].status2.nightmare = 0;
                                battle_communication_struct.multistring_chooser = 1;
                                call_bc_move_exec((void*)0x82DB234);
                                active_bank = i;
                                bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[i].status);
                                mark_buffer_bank_for_execution(active_bank);
                                effect = 5;
                                break;
                            }
                        }
                        if (effect != 5)
                        {
                            bank_attacker = active_bank;
                            attacker_struct->status2.uproar--;
                            if (check_if_move_failed(active_bank) || attacker_struct->status2.uproar == 0)
                            {
                                reset_several_turns_stuff(active_bank);
                                battle_communication_struct.multistring_chooser = 1;
                            }
                            else
                            {
                                battle_communication_struct.multistring_chooser = 0;
                                attacker_struct->status2.multiple_turn_move = 1;
                            }
                            effect = 1;
                            call_bc_move_exec((void*)0x82DB2A6);
                        }
                    }
                    break;
                case 15: //thrash aka lock and confuse
                    if (attacker_struct->status2.locked_and_confuse)
                    {
                        attacker_struct->status2.locked_and_confuse--;
                        if (check_if_move_failed(active_bank))
                            reset_several_turns_stuff(active_bank);
                        else if (attacker_struct->status2.locked_and_confuse == 0 && attacker_struct->status2.multiple_turn_move)
                        {
                            attacker_struct->status2.multiple_turn_move = 0;
                            switch (cant_become_confused(active_bank))
                            {
                            case 0: //can become confused
                                effect = 1;
                                attacker_struct->status2.confusion = 2 + __umodsi3(rng(), 4);
                                call_bc_move_exec((void*)(0x082DB2AF));
                                break;
                            case 4: //poke's ability doesn't allow it
                                effect = 1;
                                bank_target = active_bank;
                                call_bc_move_exec(CANT_CONFUSE_DUETOABILITY_PRINT_END2);
                                break;
                            }
                        }
                    }
                    break;
                case 16: //disable
                    if (current_hp && disable_structs[active_bank].disable_timer)
                    {
                        s8 position = get_move_position(active_bank, disable_structs[active_bank].disabled_move);
                        if (position == -1)
                        {
                            disable_structs[active_bank].disabled_move = 0;
                            disable_structs[active_bank].disable_timer = 0;
                        }
                        else
                        {
                            disable_structs[active_bank].disable_timer--;
                            if (disable_structs[active_bank].disable_timer == 0)
                            {
                                effect = 1;
                                disable_structs[active_bank].disabled_move = 0;
                                call_bc_move_exec((void*)0x082DAE23);
                            }
                        }
                    }
                    break;
                case 17: //encore
                    if (disable_structs[active_bank].encore_timer)
                    {
                        s8 position = get_move_position(active_bank, disable_structs[active_bank].encored_move);
                        if (position == -1)
                        {
                            disable_structs[active_bank].encored_move = 0;
                            disable_structs[active_bank].encore_timer = 0;
                        }
                        else
                        {
                            disable_structs[active_bank].encore_timer--;
                            if (disable_structs[active_bank].encore_timer == 0)
                            {
                                effect = 1;
                                disable_structs[active_bank].encored_move = 0;
                                call_bc_move_exec((void*)0x082DAE37);
                            }
                        }
                    }
                    break;
                case 18: //embargo
                    if (ptr_to_struct->embargo)
                    {
                        ptr_to_struct->embargo--;
                        if (ptr_to_struct->embargo == 0)
                        {
                            effect = 1;
                            call_bc_move_exec(BS_EMBARGOEND);
                        }
                    }
                    break;
                case 19: //telekinesis
                    if (ptr_to_struct->telekinesis)
                    {
                        ptr_to_struct->telekinesis--;
                        if (ptr_to_struct->telekinesis == 0)
                        {
                            effect = 1;
                            call_bc_move_exec(BS_TELEKINESIS_ENDS_2);
                        }
                    }
                    break;
                case 20: //heal block
                    if (ptr_to_struct->heal_block)
                    {
                        ptr_to_struct->heal_block--;
                        if (ptr_to_struct->heal_block == 0)
                        {
                            effect = 1;
                            call_bc_move_exec(BS_HEALBLOCKEND_END2);
                        }
                    }
                    break;
                case 21: //magnet rise
                    if (ptr_to_struct->magnet_rise)
                    {
                        ptr_to_struct->magnet_rise--;
                        if (ptr_to_struct->magnet_rise == 0)
                        {
                            effect = 1;
                            call_bc_move_exec(BS_MAGNETRISEEND_END2);
                        }
                    }
                    break;
                case 22: //clear always hits flag and always crit flag
                    if (status3[active_bank].always_hits)
                        status3[active_bank].always_hits--;
                    if (new_battlestruct->bank_affecting[active_bank].always_crit)
                        new_battlestruct->bank_affecting[active_bank].always_crit--;
                    break;
                case 23: //charge timer decrement
                    if (disable_structs[active_bank].charge_timer)
                    {
                        disable_structs[active_bank].charge_timer--;
                        if (disable_structs[active_bank].charge_timer == 0)
                            status3[active_bank].charged_up = 0;
                    }
                    break;
                case 24: //taunt
                    if (disable_structs[active_bank].taunt_timer)
                    {
                        disable_structs[active_bank].taunt_timer--;
                        if (disable_structs[active_bank].taunt_timer == 0)
                        {
                            effect = 1;
                            call_bc_move_exec(BS_TAUNTEND_END2);
                        }
                    }
                    break;
                case 25: //yawn
                    if (status3[active_bank].yawn)
                    {
                        status3[active_bank].yawn--;
                        if (status3[active_bank].yawn == 0 && !cant_fall_asleep(active_bank,1) && uproar_wakeup_check(active_bank) == 0)
                        {
                            reset_several_turns_stuff(active_bank);
                            effect = 1;
                            battle_participants[active_bank].status.flags.sleep = 2 + __umodsi3(rng(), 4); //2 + 0/1/2/3
                            bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[active_bank].status);
                            mark_buffer_bank_for_execution(active_bank);
                            bank_partner_def = active_bank;
                            call_bc_move_exec((void*) 0x082DB378);
                        }
                    }
                    break;
                case 26: //item effects again
                    if (item_battle_effects(1, active_bank, 1))
                        effect = 1;
                    break;
                case 27: //cheeck pouch again
                    break;
                case 28: //toxic/flame orb
                    if (item_battle_effects(5, active_bank, 0))
                        effect = 1;
                    break;
                case 29: //change roost type
                    switch (new_battlestruct->bank_affecting[active_bank].roost)
                    {
                    case 1:
                        battle_participants[active_bank].type1 = TYPE_FLYING;
                        break;
                    case 2:
                        battle_participants[active_bank].type2 = TYPE_FLYING;
                        break;
                    case 3:
                        new_battlestruct->bank_affecting[active_bank].type3 = TYPE_FLYING;
                        break;
                    case 4:
                        set_type(active_bank, TYPE_FLYING);
                        break;
                    }
                    break;
               case 30: //forms changes based on HP
                    {
                        u16 species =  battle_participants[active_bank].species;
                        u8 bank = active_bank;
                        switch(species)
                        {
                        case POKE_DARMANITAN:
                            if((battle_participants[bank].current_hp < (battle_participants[bank].max_hp >> 1)) && check_ability(bank,ABILITY_ZEN_MODE))
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_ZEN_MODE;
                                new_battlestruct->various.var2 = 0x21C;
                                battle_scripting.active_bank = bank;
                                call_bc_move_exec(BS_FORMCHANGE_WITH_TYPE_CHANGE);
                            }
                        break;
                        case POKE_ZEN_MODE:
                            if((battle_participants[bank].current_hp >= (battle_participants[bank].max_hp >> 1)) || !check_ability(bank,ABILITY_ZEN_MODE))
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_DARMANITAN;
                                battle_scripting.active_bank = bank;
                                new_battlestruct->various.var2 = 0x21D;
                                call_bc_move_exec(BS_FORMCHANGE_WITH_TYPE_CHANGE);
                            }
                            break;
                        case POKE_WISHIWASHI:
                            if((battle_participants[bank].current_hp >= (battle_participants[bank].max_hp >> 2)) && check_ability(bank,ABILITY_SCHOOLING) && battle_participants[bank].level >=SCHOOLING_LEVEL)
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_WISHIWASHI_SCHOOL;
                                new_battlestruct->various.var2 = 0x244;
                                battle_scripting.active_bank=bank;
                                call_bc_move_exec(BS_STAT_ONLY_FORMCHANGE);
                            }
                            break;
                        case POKE_WISHIWASHI_SCHOOL:
                            if((battle_participants[bank].current_hp < (battle_participants[bank].max_hp >> 2)) || !check_ability(bank,ABILITY_SCHOOLING))
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_WISHIWASHI;
                                battle_scripting.active_bank=bank;
                                new_battlestruct->various.var2 = 0x245;
                                call_bc_move_exec(BS_STAT_ONLY_FORMCHANGE);
                            }
                            break;
                        case POKE_MINIOR_CORE:
                            if((battle_participants[bank].current_hp >= (battle_participants[bank].max_hp >> 1)) && check_ability(bank,ABILITY_SHIELDS_DOWN))
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_MINIOR_METEOR;
                                new_battlestruct->various.var2 = 0x242;
                                battle_scripting.active_bank=bank;
                                call_bc_move_exec(BS_STAT_ONLY_FORMCHANGE);
                            }
                            break;
                        case POKE_MINIOR_METEOR:
                            if((battle_participants[bank].current_hp < (battle_participants[bank].max_hp >> 1)) || !check_ability(bank,ABILITY_SHIELDS_DOWN))
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_MINIOR_CORE;
                                battle_scripting.active_bank=bank;
                                new_battlestruct->various.var2 = 0x243;
                                call_bc_move_exec(BS_STAT_ONLY_FORMCHANGE);
                            }
                            break;
                        case POKE_ZYGARDE_10:
                        case POKE_ZYGARDE_50:
                            if((battle_participants[bank].current_hp < (battle_participants[bank].max_hp >> 1)) && check_ability(bank,ABILITY_POWER_CONSTRUCT))
                            {
                                effect = 1;
                                new_battlestruct->various.var1 = POKE_ZYGARDE_100;
                                if(species==POKE_ZYGARDE_50)
                                {
                                    if(is_bank_from_opponent_side(bank))
                                    {
                                        new_battlestruct->party_bit.is_base_z50_ai |= bits_table[battle_team_id_by_side[bank]];
                                    }
                                    else
                                    {
                                        new_battlestruct->party_bit.is_base_z50_user |= bits_table[battle_team_id_by_side[bank]];
                                    }
                                }
                                battle_scripting.active_bank=bank;
                                new_battlestruct->various.var2 = 0x24A;
                                call_bc_move_exec(BS_ZYGARDE_FORM_CHANGE);
                            }
                            break;
                        }
                    }
            }
            if (effect != 5) //check for uproar
                 *tracker += 1;
            #define TRACKER_MAX 31
            if (*tracker >= TRACKER_MAX)
            {
                *tracker = 0;
                *bank +=1;
            }
            if (effect)
                return effect;
        }
    }

    hitmarker &= 0xFEFFFFDF;

    return effect;
}

u8 get_first_to_strike(u8 bank1, u8 bank2, u8 ignore_priority);

void move_to_buff1(u16 move)
{
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 2;
    battle_text_buff1[2] = move;
    battle_text_buff1[3] = move >> 8;
    battle_text_buff1[4] = 0xFF;
}

bool update_turn_counters(void)
{
    #define TURN_LAST_CASE 29
    bool effect = 0;
    for (bank_attacker = 0; bank_attacker < no_of_all_banks; bank_attacker++)
    {
        if (!(absent_bank_flags & bits_table[bank_attacker]))
            break;
    }
    for (bank_target = 0; bank_target < no_of_all_banks; bank_target++)
    {
        if (!(absent_bank_flags & bits_table[bank_target]))
            break;
    }
    u8* statetracker = &battle_stuff_ptr->end_turn_statetracker2;
    u8* sidebank = &battle_stuff_ptr->field_DB;
    while (effect == 0 && *statetracker <= TURN_LAST_CASE)
    {
        switch (*statetracker)
        {
        case 0: //trick room
            new_battlestruct->side_affecting[0].pledge_effect=0;
            new_battlestruct->side_affecting[1].pledge_effect=0;
            if (new_battlestruct->field_affecting.trick_room)
            {
                new_battlestruct->field_affecting.trick_room--;
                if (new_battlestruct->field_affecting.trick_room == 0)
                {
                    battle_communication_struct.multistring_chooser = 0;
                    effect = 1;
                    call_bc_move_exec(BS_ROOMEND);
                }
            }
            *statetracker +=1;
            break;
        case 1: //magic room
            if (new_battlestruct->field_affecting.magic_room)
            {
                new_battlestruct->field_affecting.magic_room--;
                if (new_battlestruct->field_affecting.magic_room == 0)
                {
                    battle_communication_struct.multistring_chooser = 4;
                    effect = 1;
                    call_bc_move_exec(BS_ROOMEND);
                }
            }
            *statetracker +=1;
            break;
        case 2: //wonder room
            if (new_battlestruct->field_affecting.wonder_room)
            {
                new_battlestruct->field_affecting.wonder_room--;
                if (new_battlestruct->field_affecting.wonder_room == 0)
                {
                    battle_communication_struct.multistring_chooser = 2;
                    effect = 1;
                    call_bc_move_exec(BS_ROOMEND);
                }
            }
            *statetracker +=1;
            break;
        case 3: //gravity
            if (new_battlestruct->field_affecting.gravity)
            {
                new_battlestruct->field_affecting.gravity--;
                if (new_battlestruct->field_affecting.gravity == 0)
                {
                    effect = 1;
                    call_bc_move_exec(BS_GRAVITYEND);
                }
            }
            *statetracker +=1;
            break;
        case 4: //grassy terrain
            if (new_battlestruct->field_affecting.grassy_terrain)
            {
                new_battlestruct->field_affecting.grassy_terrain--;
                if (new_battlestruct->field_affecting.grassy_terrain == 0)
                {
                    battle_communication_struct.multistring_chooser = 0;
                    effect = 1;
                    call_bc_move_exec(BS_TERRAINEND);
                }
                else
                {
                    effect = 1;
                    call_bc_move_exec(BS_GRASSYTERRAIN_HEAL);
                    for (u8 i = 0; i < no_of_all_banks; i++)
                    {   new_battlestruct->bank_affecting[i].grassyterrain_heal = 0;  }

                }
            }
            *statetracker +=1;
            break;
        case 5: //misty terrain
            if (new_battlestruct->field_affecting.misty_terrain)
            {
                new_battlestruct->field_affecting.misty_terrain--;
                if (new_battlestruct->field_affecting.misty_terrain == 0)
                {
                    battle_communication_struct.multistring_chooser = 1;
                    effect = 1;
                    call_bc_move_exec(BS_TERRAINEND);
                }

            }
            *statetracker +=1;
            break;
        case 6: //electric terrain
            if (new_battlestruct->field_affecting.electic_terrain)
            {
                new_battlestruct->field_affecting.electic_terrain--;
                if (new_battlestruct->field_affecting.electic_terrain == 0)
                {
                    battle_communication_struct.multistring_chooser = 2;
                    effect = 1;
                    call_bc_move_exec(BS_TERRAINEND);
                }
            }
            *statetracker +=1;
            break;
        case 7: //mud sport
            if (new_battlestruct->field_affecting.mudsport)
            {
                new_battlestruct->field_affecting.mudsport--;
                if (new_battlestruct->field_affecting.mudsport == 0)
                {
                    effect = 1;
                    call_bc_move_exec(BS_PRINT_SPORT_FADED);
                    move_to_buff1(MOVE_MUD_SPORT);
                }
            }
            *statetracker +=1;
            break;
        case 8: //water sport
            if (new_battlestruct->field_affecting.watersport)
            {
                new_battlestruct->field_affecting.watersport--;
                if (new_battlestruct->field_affecting.watersport == 0)
                {
                    effect = 1;
                    call_bc_move_exec(BS_PRINT_SPORT_FADED);
                    move_to_buff1(MOVE_WATER_SPORT);
                }
            }
            *statetracker +=1;
            break;
        case 9: //ion deluge and fairy lock
            if (new_battlestruct->field_affecting.ion_deluge)
                new_battlestruct->field_affecting.ion_deluge--;
            if (new_battlestruct->field_affecting.fairy_lock)
                new_battlestruct->field_affecting.fairy_lock--;
            *statetracker +=1;
        case 10: //something with turn order
            for (u8 i = 0; i < no_of_all_banks; i++)
            {
                turn_order[i] = i;
            }
            u8 all_banks = no_of_all_banks - 1;
            for (s8 i2 = 0; i2 > all_banks; all_banks--)
            {
                s8 i3 = i2 + 1;
                while (i3 < no_of_all_banks)
                {
                    if (get_first_to_strike(turn_order[i2], turn_order[i3], 0))
                    {
                        sub_803CEDC(i2, i3);
                    }
                    i3++;
                }
            }
            *statetracker +=1;
            *sidebank = 0;
        case 11: //reflect
            while (*sidebank <= 1 && effect == 0)
            {
                if (side_affecting_halfword[*sidebank].reflect_on)
                {
                    side_timers[*sidebank].reflect_timer--;
                    if (side_timers[*sidebank].reflect_timer == 0)
                    {
                        side_affecting_halfword[*sidebank].reflect_on = 0;
                        bank_attacker = side_timers[*sidebank].reflect_bank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DACFA);
                        move_to_buff1(MOVE_REFLECT);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 12: //light screen
            while (*sidebank <= 1 && effect == 0)
            {
                if (side_affecting_halfword[*sidebank].light_screen_on)
                {
                    side_timers[*sidebank].lightscreen_timer--;
                    if (side_timers[*sidebank].lightscreen_timer == 0)
                    {
                        side_affecting_halfword[*sidebank].light_screen_on = 0;
                        bank_attacker = side_timers[*sidebank].lightscreen_bank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DACFA);
                        battle_communication_struct.multistring_chooser = *sidebank;
                        move_to_buff1(MOVE_LIGHT_SCREEN);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 13: //aurora veil
            while (*sidebank <= 1 && effect == 0)
            {
                if (new_battlestruct->side_affecting[*sidebank].aurora_veil)
                {
                    new_battlestruct->side_affecting[*sidebank].aurora_veil--;
                    if (new_battlestruct->side_affecting[*sidebank].aurora_veil == 0)
                    {
                        bank_attacker = *sidebank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DACFA);
                        battle_communication_struct.multistring_chooser = *sidebank;
                        move_to_buff1(MOVE_AURORA_VEIL);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 14: //mist
            while (*sidebank <= 1 && effect == 0)
            {
                if (side_affecting_halfword[*sidebank].mist_on)
                {
                    side_timers[*sidebank].mist_timer--;
                    if (side_timers[*sidebank].mist_timer == 0)
                    {
                        side_affecting_halfword[*sidebank].mist_on = 0;
                        bank_attacker = active_bank = side_timers[*sidebank].mist_bank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DACFA);
                        battle_communication_struct.multistring_chooser = *sidebank;
                        move_to_buff1(MOVE_MIST);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 15: //safeguard
            while (*sidebank <= 1 && effect == 0)
            {
                if (side_affecting_halfword[*sidebank].safeguard_on)
                {
                    side_timers[*sidebank].safeguard_timer--;
                    if (side_timers[*sidebank].safeguard_timer == 0)
                    {
                        side_affecting_halfword[*sidebank].safeguard_on = 0;
                        bank_attacker = active_bank = side_timers[*sidebank].safeguard_bank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DAD0B);
                        battle_communication_struct.multistring_chooser = *sidebank;
                        move_to_buff1(MOVE_SAFEGUARD);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 16: //lucky chant
            while (*sidebank <= 1 && effect == 0)
            {
                if (new_battlestruct->side_affecting[*sidebank].lucky_chant)
                {
                    new_battlestruct->side_affecting[*sidebank].lucky_chant--;
                    if (new_battlestruct->side_affecting[*sidebank].lucky_chant == 0)
                    {
                        bank_attacker = active_bank = new_battlestruct->side_affecting[*sidebank].lucky_chant_bank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DACFA);
                        battle_communication_struct.multistring_chooser = *sidebank;
                        move_to_buff1(MOVE_LUCKY_CHANT);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 17: //tailwind
            while (*sidebank <= 1 && effect == 0)
            {
                if (new_battlestruct->side_affecting[*sidebank].tailwind)
                {
                    new_battlestruct->side_affecting[*sidebank].tailwind--;
                    if (new_battlestruct->side_affecting[*sidebank].tailwind == 0)
                    {
                        bank_attacker = active_bank = new_battlestruct->side_affecting[*sidebank].tailwind_bank;
                        effect = 1;
                        call_bc_move_exec((void*)0x82DACFA);
                        battle_communication_struct.multistring_chooser = *sidebank;
                        move_to_buff1(MOVE_TAILWIND);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 18: //swamp
            while (*sidebank <= 1 && effect == 0)
            {
                if (new_battlestruct->side_affecting[*sidebank].swamp_spd_reduce)
                {
                    new_battlestruct->side_affecting[*sidebank].swamp_spd_reduce--;
                    if (new_battlestruct->side_affecting[*sidebank].swamp_spd_reduce == 0)
                    {
                        battle_scripting.active_bank = *sidebank;
                        effect = 1;
                        call_bc_move_exec(&end_pledge_effect_bs);
                        new_battlestruct->various.var2=0x227;
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 19: //sea of fire
            while (*sidebank <= 5 && effect == 0)
            {
                u8 side = (*sidebank)&1;
                if (new_battlestruct->side_affecting[side].sea_of_fire)
                {
                    if((*sidebank)<=3)
                    {
                        if((!battle_weather.flags.downpour && !battle_weather.flags.permament_rain && !battle_weather.flags.heavy_rain && !battle_weather.flags.rain)
                           && is_bank_present(*sidebank) && !is_of_type(*sidebank,TYPE_FIRE))
                        {
                            effect=1;
                            active_bank = bank_attacker = *sidebank;
                            damage_loc = get_1_8_of_max_hp(active_bank);
                            hitmarker |= HITMARKER_IGNORE_SUBSTITUTE;
                            call_bc_move_exec(&sea_of_fire_hurt_bs);
                        }
                    }
                    else
                    {
                        new_battlestruct->side_affecting[side].sea_of_fire--;
                        if (new_battlestruct->side_affecting[side].sea_of_fire == 0)
                        {
                            battle_scripting.active_bank = side;
                            effect = 1;
                            call_bc_move_exec(&end_pledge_effect_bs);
                            new_battlestruct->various.var2=0x228;
                        }
                    }
                }
                switch(*sidebank)
                {
                case 0:
                    *sidebank=2;
                    break;
                case 1:
                    *sidebank=3;
                    break;
                case 2:
                    *sidebank=4;
                    break;
                case 3:
                    *sidebank=5;
                    break;
                case 4:
                    *sidebank=1;
                    break;
                default:
                    (*sidebank)=(*sidebank)+1;
                    break;
                }
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 20: //rainbow
            while (*sidebank <= 1 && effect == 0)
            {
                if (new_battlestruct->side_affecting[*sidebank].rainbow)
                {
                    new_battlestruct->side_affecting[*sidebank].rainbow--;
                    if (new_battlestruct->side_affecting[*sidebank].rainbow == 0)
                    {
                       battle_scripting.active_bank = *sidebank;
                        effect = 1;
                        call_bc_move_exec(&end_pledge_effect_bs);
                        new_battlestruct->various.var2=0x229;
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 21: //wish
            while (*sidebank < no_of_all_banks && effect == 0)
            {
                if (battle_effects_duration.wish_duration[*sidebank])
                {
                    battle_effects_duration.wish_duration[*sidebank]--;
                    if (battle_effects_duration.wish_duration[*sidebank] == 0 && battle_participants[*sidebank].current_hp)
                    {
                        effect = 1;
                        bank_target = *sidebank;
                        call_bc_move_exec((void*)0x82DB0B7);
                    }
                }
                *sidebank+=1;
            }
            if (effect == 0)
            {
                *sidebank = 0;
                *statetracker +=1;
            }
            break;
        case 22: //new struct
            while (*sidebank <= 1)
            {
                if (new_battlestruct->side_affecting[*sidebank].ally_fainted_last_turn)
                {
                    new_battlestruct->side_affecting[*sidebank].ally_fainted_last_turn--;
                }
                //clear protect-like moves
                new_battlestruct->side_affecting[*sidebank].wide_guard = 0;
                new_battlestruct->side_affecting[*sidebank].quick_guard = 0;
                new_battlestruct->side_affecting[*sidebank].crafty_shield = 0;
                new_battlestruct->side_affecting[*sidebank].mat_block = 0;

                *sidebank += 1;
            }
            *sidebank = 0;
            *statetracker += 1;
        case 23: //echo voice
            {
                bool echo_used = 0;
                for (u8 i = 0; i < no_of_all_banks; i++)
                {
                    if (last_used_moves[i] == MOVE_ECHOED_VOICE)
                    {
                        echo_used = 1;
                        break;
                    }
                }
                if (!echo_used)
                    new_battlestruct->field_affecting.echo_voice_counter = 0;
                else
                {
                    if (new_battlestruct->field_affecting.echo_voice_counter <= 5)
                        new_battlestruct->field_affecting.echo_voice_counter++;
                }
                *statetracker += 1;
            }
        case 24: //rain
            if (battle_weather.flags.rain || battle_weather.flags.downpour || battle_weather.flags.heavy_rain || battle_weather.flags.permament_rain)
            {
                effect = 1;
                battle_effects_duration.weather_dur--;
                if (battle_weather.flags.heavy_rain || battle_weather.flags.permament_rain || battle_effects_duration.weather_dur)
                {
                    if (battle_weather.flags.downpour)
                        *sidebank = 1;
                    else
                        *sidebank = 0;
                }
                else
                {
                    *sidebank = 2;
                    battle_weather.flags.downpour = 0;
                    battle_weather.flags.rain = 0;
                }

                call_bc_move_exec((void*)0x082DAC2C);
                battle_communication_struct.multistring_chooser = *sidebank;
            }
            *sidebank = 0;
            *statetracker += 1;
            break;
        case 25: //sun
            if (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)
            {
                effect = 1;
                battle_effects_duration.weather_dur--;
                if (battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun || battle_effects_duration.weather_dur)
                    call_bc_move_exec((void*)0x82DACD2);
                else
                {
                    battle_weather.flags.sun = 0;
                    call_bc_move_exec((void*)0x82DACE0);
                }
            }
            *statetracker += 1;
            break;
        case 26: //darude
            if (battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm)
            {
                effect = 1;
                battle_effects_duration.weather_dur--;
                if (battle_weather.flags.permament_sandstorm || battle_effects_duration.weather_dur)
                    call_bc_move_exec((void*)0x82DAC47);
                else
                {
                    battle_weather.flags.sandstorm = 0;
                    call_bc_move_exec((void*)0x82DACC9);
                }
                battle_scripting.AnimInfo1 = 0xC;
                battle_communication_struct.multistring_chooser = 0;
            }
            *statetracker += 1;
            break;
        case 27: //hail
            if (battle_weather.flags.hail || battle_weather.flags.permament_hail)
            {
                effect = 1;
                battle_effects_duration.weather_dur--;
                if (battle_weather.flags.permament_hail || battle_effects_duration.weather_dur)
                    call_bc_move_exec((void*)0x82DAC47);
                else
                {
                    battle_weather.flags.hail = 0;
                    call_bc_move_exec((void*)0x82DACC9);
                }
                battle_scripting.AnimInfo1 = 0xD;
                battle_communication_struct.multistring_chooser = 1;
            }
            *statetracker += 1;
            break;
        case 28: //fog
            if (battle_weather.flags.fog || battle_weather.flags.permament_fog)
            {
                effect = 1;
                battle_effects_duration.weather_dur--;
                if (battle_weather.flags.permament_fog || battle_effects_duration.weather_dur)
                {
                    call_bc_move_exec(&fogcontinues_bs);
                    current_move = MOVE_HAZE;
                }
                else
                {
                    battle_weather.flags.fog = 0;
                    call_bc_move_exec(&fogends_bs);
                }
            }
            *statetracker += 1;
            break;
        default:
            *statetracker += 1;
        }
    }
    return effect;
}

bool consider_sliding_msg(void)
{
    bool effect = 0;
    if (battle_flags.trainer && !battle_flags.multibattle)
    {
        //check if only one poke alive
        u8 bank = get_bank_by_player_ai(1);
        if (count_party_pokemon(bank) == 1 && battle_participants[bank].current_hp)
        {
            //check switch-in last poke
            if ((new_battlestruct->various.trainer_slide_msg = get_slide_msg(var_8015_trainer_opponent_A, 0))
                 && !new_battlestruct->various.trainer_msg_on_switch_in_done)
            {
                new_battlestruct->various.trainer_msg_on_switch_in_done = 1;
                call_bc_move_exec(&BS_TRAINER_SLIDE_MSG_END2);
                effect = 1;
            }
            //check last poke low health
            else if (((battle_participants[bank].current_hp * 100 / battle_participants[bank].max_hp) < 27)
                 && ((new_battlestruct->various.trainer_slide_msg = get_slide_msg(var_8015_trainer_opponent_A, 1)))
                 && !new_battlestruct->various.trainer_msg_on_low_health_done)
            {
                new_battlestruct->various.trainer_msg_on_low_health_done = 1;
                call_bc_move_exec(&BS_TRAINER_SLIDE_MSG_END2);
                effect = 1;
            }
        }
    }
    return effect;
}

void battle_turn_passed(void)
{
    turn_values_cleanup(1);
    if (battle_outcome == 0)
    {
        if (update_turn_counters()) {return;}
        if (battle_turn_move_effects()) {return;}
    }
    if (sub_8041728()) {return;}
    battle_stuff_ptr->field_4D = 0;
    if (sub_8041364()) {return;} //perish song/future sight is done there
    if (consider_sliding_msg()) {return;}

    turn_values_cleanup(0);
    hitmarker = BIC(hitmarker, 0x100000 | 0x400000 | 0x80000 | 0x200);
    battle_scripting.cmd49_state_tracker = 0;
    battle_scripting.field19 = 0;
    battle_scripting.field18 = 0;
    damage_loc = 0;
    *(u8*)(&move_outcome) = 0;

    battle_communication_struct.field0 = 0;
    battle_communication_struct.field1 = 0;
    battle_communication_struct.field2 = 0;
    battle_communication_struct.field4 = 0;
    battle_communication_struct.move_effect = 0;
    memset(&new_battlestruct->move_effect, 0, sizeof(struct move_effects));

    if (battle_outcome)
    {
        battle_state_mode = 0xC;
        battle_executed_routine = bc_bs_executer;
    }
    else
    {
        u8* turn_counter = &battle_trace.battle_turn_counter;
        if (*turn_counter < 254)
        {
            (*turn_counter)++;
            battle_stuff_ptr->field_DA++;
        }
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            chosen_move_by_banks[i] = 0;
            menu_choice_pbs[i] = 0xFF;
        }
        battle_stuff_ptr->field_5C[0] = 6;
        battle_stuff_ptr->field_5C[1] = 6;
        battle_stuff_ptr->field_5C[2] = 6;
        battle_stuff_ptr->field_5C[3] = 6;

        battle_stuff_ptr->absent_bank_flags_prev_turn = absent_bank_flags;

        battle_display_rbox((void*) 0x085CC23E, 0);
        battle_executed_routine = fighting_mode_off;
        battle_turn_random_no = rng();

        if (battle_flags.battle_palace)
            call_bc_move_exec((void*)(0x82DB881));
        else if (battle_flags.battle_arena && !battle_stuff_ptr->field_DA)
            call_bc_move_exec((void*)(0x82DB8BE));
    }
}

struct move_limitation{
    u8 limitation_no_move : 1; //0x1
    u8 limitation_no_pp : 1; //0x2
    u8 limitation_disabled : 1; //0x4
    u8 limitation_x8 : 1; //0x8
    u8 limitation_taunt : 1; //0x10
    u8 limitation_imprision : 1; //0x20
};

u8 check_move_limitations(u8 bank, u8 not_usable_moves, struct move_limitation limitations)
{
    struct battle_participant* checking_bank = &battle_participants[bank];
    u8 item_effect = get_item_effect(bank, 1);
    for (u8 i = 0; i < 4; i++)
    {
        u16 move_to_check = checking_bank->moves[i];
        if (move_to_check == 0 && limitations.limitation_no_move)
            not_usable_moves |= bits_table[i];
        else if (checking_bank->current_pp[i] == 0 && limitations.limitation_no_pp)
            not_usable_moves |= bits_table[i];
        else if (disable_structs[bank].disabled_move == move_to_check && limitations.limitation_disabled)
            not_usable_moves |= bits_table[i];
        else if (disable_structs[bank].taunt_timer && move_table[move_to_check].base_power == 0 && limitations.limitation_taunt)
            not_usable_moves |= bits_table[i];
        else if (status3[bank].imprision && check_if_imprisioned(bank, move_to_check) && limitations.limitation_imprision)
            not_usable_moves |= bits_table[i];
        else if (CHOICE_ITEM(item_effect) && battle_stuff_ptr->choiced_move[bank] && battle_stuff_ptr->choiced_move[bank] != 0xFFFF && battle_stuff_ptr->choiced_move[bank] != move_to_check)
            not_usable_moves |= bits_table[i];
        else if (item_effect == ITEM_EFFECT_ASSAULTVEST && move_table[move_to_check].split == 2)
            not_usable_moves |= bits_table[i];
        else if (disable_structs[bank].encore_timer && disable_structs[bank].encored_move != move_to_check)
            not_usable_moves |= bits_table[i];
        else if (checking_bank->status2.tormented && last_used_moves[bank] == move_to_check)
            not_usable_moves |= bits_table[i];
        else if (new_battlestruct->field_affecting.gravity && gravity_forbidden_move(move_to_check))
            not_usable_moves |= bits_table[i];
        else if (new_battlestruct->bank_affecting[bank].heal_block && healblock_forbidden_moves(move_to_check, 0))
            not_usable_moves |= bits_table[i];
        else if (new_battlestruct->bank_affecting[bank].embargo && embargo_forbidden_move(move_to_check))
            not_usable_moves |= bits_table[i];
    }
    return not_usable_moves;
}

bool message_cant_choose_move(void)
{
    u8 bank = another_active_bank = active_bank;
    struct battle_participant* checking_bank = &battle_participants[bank];
    u8 move_index = battle_bufferB[bank].args[1];
    u16 checking_move = checking_bank->moves[move_index];
    void** loc_to_store_bs = (void*) 0x2024220 + bank * 4;
    bool cant = 0;
    u8 item_effect = get_item_effect(bank, 1);
    if (checking_bank->current_pp[move_index] == 0)
    {
        cant = 1;
        *loc_to_store_bs = (void*) 0x82DB076;
    }
    else if (CHOICE_ITEM(item_effect) && battle_stuff_ptr->choiced_move[bank] && battle_stuff_ptr->choiced_move[bank] != 0xFFFF && battle_stuff_ptr->choiced_move[bank] != checking_move)
    {
        current_move = battle_stuff_ptr->choiced_move[bank];
        cant = 1;
        *loc_to_store_bs = (void*) 0x82DB812;
        last_used_item = checking_bank->held_item;
    }
    else if (item_effect == ITEM_EFFECT_ASSAULTVEST && move_table[checking_move].split == 2)
    {
        cant = 1;
        last_used_item = checking_bank->held_item;
        *loc_to_store_bs = BS_CANTSELECT_ASSAULTVEST;
    }
    else if (status3[bank].imprision && check_if_imprisioned(bank, checking_move))
    {
        cant = 1;
        *loc_to_store_bs = (void*) 0x82DB181;
    }
    else if (disable_structs[bank].taunt_timer && move_table[checking_move].base_power == 0)
    {
        cant = 1;
        *loc_to_store_bs = (void*) 0x82DB0A0;
    }
    else if (checking_bank->status2.tormented && last_used_moves[bank] == checking_move && checking_move != MOVE_STRUGGLE)
    {
        cant = 1;
        reset_several_turns_stuff(bank);
        *loc_to_store_bs = (void*) 0x82DB089;
    }
    else if (disable_structs[bank].disabled_move == checking_move && disable_structs[bank].disable_timer)
    {
        cant = 1;
        current_move = checking_move;
        *loc_to_store_bs = (void*) 0x82DAE1F;
    }
    else if (new_battlestruct->field_affecting.gravity && gravity_forbidden_move(checking_move))
    {
        cant = 1;
        current_move = checking_move;
        *loc_to_store_bs = BS_CANTSELECT_GRAVITY;
    }
    else if (new_battlestruct->bank_affecting[bank].heal_block && healblock_forbidden_moves(checking_move, 0))
    {
        cant = 1;
        current_move = checking_move;
        *loc_to_store_bs = BS_CANTSELECT_HEALBLOCK;
    }
    return cant;
}

s8 can_switch(u8 bank) //1 - can; 0 - can't; -1 can't due to abilities
{
    if (battle_flags.battle_arena || new_battlestruct->bank_affecting[bank].sky_drop_target)
        return 0;
    if (get_item_effect(bank, 1) == ITEM_EFFECT_SHEDSHELL)
        return 1;
    if (battle_participants[bank].status2.trapped_in_wrap || battle_participants[bank].status2.cant_escape || status3[bank].rooted || new_battlestruct->field_affecting.fairy_lock)
        return 0;
    u8 ability_bank = ability_battle_effects(12, bank, ABILITY_SHADOW_TAG, 1, 0);
    if (ability_bank && !check_ability(bank, ABILITY_SHADOW_TAG) && !is_of_type(bank, TYPE_GHOST))
    {
        another_active_bank = ability_bank - 1;
        return -1;
    }
    ability_bank = ability_battle_effects(12, bank, ABILITY_MAGNET_PULL, 1, 0);
    if (ability_bank && is_of_type(bank, TYPE_STEEL))
    {
        another_active_bank = ability_bank - 1;
        return -1;
    }
    ability_bank = ability_battle_effects(12, bank, ABILITY_ARENA_TRAP, 1, 0);
    if (ability_bank && GROUNDED(bank))
    {
        another_active_bank = ability_bank - 1;
        return - 1;
    }
    return 1;
}

bool wonderguard_good_move(u8 wonder_bank, u8 bank, u16 move, u8 check_status)
{
    u16 effectiveness = type_effectiveness_calc(move, move_table[move].type, bank, wonder_bank, 0);
    if (DAMAGING_MOVE(move) && effectiveness > 64) //move is super effective
        return 1;
    if (check_status)
    {
        u8 movescript = move_table[move].script_id;
        if (movescript == 13 || movescript == 14) //if we can poison the bank, switch isn't necessary
        {
            if (!cant_poison(bank, wonder_bank, 0))
                return 1;
        }
        else if (movescript == 16) //if we can burn the bank, switch isn't necessary
        {
            if (!cant_become_burned(wonder_bank, 0))
                return 1;
        }
        else if (movescript == 78) //if the move can seed the bank, switch isn't necessary
        {
            if (!is_of_type(wonder_bank, TYPE_GRASS) && !status3[wonder_bank].leech_seed)
                return 1;
        }
    }
    return 0;
}

bool can_poke_be_switched_into(u8 index, u8 bank)
{
    u8 bank_to_ignore = bank;
    if (battle_flags.double_battle && is_bank_present(bank ^ 2))
        bank_to_ignore = bank ^ 2;
    u8 from = 0;
    u8 to = 6;
    //todo support for link multi battles
    if ((battle_flags.multibattle && is_bank_from_opponent_side(bank)) || (battle_flags.player_ingame_partner && !is_bank_from_opponent_side(bank)))
    {
        if (bank <= 1) //indices 0, 1, 2 are from this bank's party
            to = 2;
        else //indices 3, 4, 5 are from this bank's party
            from = 3;
    }
    struct pokemon* poke = &get_party_ptr(bank)[index];
    if (is_poke_valid(poke) && get_attributes(poke, ATTR_CURRENT_HP, 0) && battle_team_id_by_side[bank] != index && battle_team_id_by_side[bank_to_ignore] != index && index >= from && index <= to)
        return 1;
    return 0;
}

bool ai_switch_wonderguard(void)
{
    u8 worth = 0;
    u8 wonder_bank = 0;
    u8 self = active_bank;
    u8 ally = self ^ 2;
    if (!is_bank_present(ally))
        ally = self;
    u8 enemy1 = self ^ 1;
    u8 enemy2 = ally ^ 1;
    if (!is_bank_present(enemy2))
        enemy2 = enemy1;
    if (check_ability(enemy1, ABILITY_WONDER_GUARD))
    {
        worth = 1;
        wonder_bank = enemy1;
    }
    else if (check_ability(enemy2, ABILITY_WONDER_GUARD))
    {
        worth = 1;
        wonder_bank = enemy2;
    }
    if (worth)
    {
        //check if has a move that's effective against wonder guard bank
        for (u8 bank = 0; bank < no_of_all_banks; bank++)
        {
            if (bank == self || bank == ally)
            {
                for (u8 i = 0; i < 4; i ++)
                {
                    u16 move = battle_participants[bank].moves[i];
                    if (move && wonderguard_good_move(wonder_bank, bank, move, 1))
                        return 0;
                }
            }
        }
        //at this point we've searched for all moves and bank can't damage a poke with wonder guard, we need to search for a poke in party that can do it
        struct pokemon* poke = get_party_ptr(self);
        for (u8 i = 0; i < 6; i++)
        {
            if (can_poke_be_switched_into(i, self))
            {
                for (u8 j = 0; j < 4; j++)
                {
                    u16 move = get_attributes(&poke[i], ATTR_ATTACK_1 + j, 0);
                    if (move && wonderguard_good_move(wonder_bank, self, move, 0))
                    {
                        battle_stuff_ptr->switchout_index[self] = j;
                        prepare_chosen_option(1, 2, 0);
                        return 1;
                    }
                }
            }
        }
        //if we get here nothing was found, too bad :(
    }
    return 0;
}

bool ai_ability_switch(void)
{
    if (check_ability(active_bank, ABILITY_NATURAL_CURE))
    {

    }
    else if (check_ability(active_bank, ABILITY_REGENERATOR))
    {

    }
    return 0;
}

bool tai_should_switch(void)
{
    if (!can_switch(active_bank))
        return 0;
    u8 available_to_switch = 0;
    for (u8 i = 0; i < 6; i++)
    {
        if (can_poke_be_switched_into(i, active_bank))
            available_to_switch++;
    }
    if (available_to_switch)
    {
        if (ai_switch_perish_song())
            return 1;
        if (ai_switch_wonderguard())
            return 1;
        if (ai_switch_sth1())
            return 1;
        if (ai_ability_switch())
            return 1;
        if (ai_switch_sth2())
            return 0;
        if (ai_is_statbuffed())
            return 0;
        if (ai_switch_sth3(8, 2) || ai_switch_sth3(4, 3))
            return 1;
    }
    return 0;
}

