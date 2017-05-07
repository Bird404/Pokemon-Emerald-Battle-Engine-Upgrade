#include "defines.h"
#include "static_references.h"

bool load_weather_from_overworld();
bool handle_primal_reversion(u8 bank);
u8 check_ability(u8 bank, u8 ability);
void statustoeffect();
u8 find_move_in_table(u16 move, const u16* table_ptr);
u8 healblock_forbidden_moves(u16 move, u8 with_leechseed);
u8 gravity_forbidden_move(u16 move);
u8 embargo_forbidden_move(u16 move);
u16 get_item_extra_param(u16 item);
u16 get_mega_species(u8 bank, u8 chosen_method);
struct pokemon* get_party_ptr(u8 bank);
u8 is_poke_valid(struct pokemon* poke);
u8 is_bank_present(u8 bank);
u8 handle_leppa(u8 bank, u8 quality, enum call_mode calling_mode);
u8 has_ability_effect(u8 bank, u8 mold_breaker);
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

u8 check_field_for_ability(enum poke_abilities ability, u8 side_to_ignore, u8 mold)
{
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (is_bank_present(i) && is_bank_from_opponent_side(i) != side_to_ignore && battle_participants[i].ability_id == ability && has_ability_effect(i, mold))
            return i + 1;
    }
    return 0;
}

enum poke_abilities get_ally_ability(u8 bank, u8 mold)
{
    u8 ally = bank ^ 2;
    if (is_bank_present(ally) && has_ability_effect(ally, mold))
        return battle_participants[ally].ability_id;
    return 0;
}

u8 get_item_effect(u8 bank, bool check_negating_effects)
{
    u16 held_item = battle_participants[bank].held_item;
    if (check_negating_effects)
    {
        if (check_ability(bank, ABILITY_KLUTZ) || new_battlestruct->field_affecting.magic_room || new_battlestruct->bank_affecting[bank].embargo)
            return ITEM_EFFECT_NOEFFECT;
        if (get_item_pocket_id(held_item)==4 && check_field_for_ability(ABILITY_UNNERVE, is_bank_from_opponent_side(bank), 0))
            return ITEM_EFFECT_NOEFFECT;
    }
    if (held_item == ITEM_ENIGMABERRY)
    {
        return enigma_berry_battle[bank].battle_effect_x12;
    }
    else
    {
        return get_item_battle_function(held_item);
    }
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

bool weather_abilities_effect(void)
{
    if (check_field_for_ability(ABILITY_CLOUD_NINE, 3, 0) || check_field_for_ability(ABILITY_AIR_LOCK, 3, 0))
        return false;
    else
        return true;
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

u8 try_cherrim_change(u8 bank)
{
    u16 species_to_change = 0;
    if (battle_participants[bank].ability_id == ABILITY_FLOWER_GIFT && CHERRIM_ID(battle_participants[bank].poke_species))
    {
        if ((battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun) && weather_abilities_effect())
        {
            if (!new_battlestruct->bank_affecting[bank].sunshine_form)
            {
                species_to_change = POKE_CHERRIM_SUNSHINE;
                new_battlestruct->bank_affecting[bank].sunshine_form = 1;
            }
        }
        else
        {
            if (new_battlestruct->bank_affecting[bank].sunshine_form)
            {
                species_to_change = POKE_CHERRIM;
                new_battlestruct->bank_affecting[bank].sunshine_form = 0;
            }
        }
    }
    if (species_to_change)
    {
        battle_participants[bank].poke_species = species_to_change;
        active_bank = bank;
        bb2_setattributes_in_battle(0, REQUEST_SPECIES_BATTLE, 0, 2, &battle_participants[bank].poke_species);
        mark_buffer_bank_for_execution(bank);
        return 1;
    }
    return 0;
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
                    most_powerful_move = COIN_FLIP(most_powerful_move, curr_move);
                }
                else if (move_table[curr_move].base_power == 1)
                {
                        u16 curr_power;
                        if (move_table[curr_move].script_id == 70) //one hit ko moves
                            curr_power = 160;
                        else if (curr_move == MOVE_COUNTER || curr_move == MOVE_METAL_BURST || curr_move == MOVE_MIRROR_COAT)
                            curr_power = 120;
                        else
                        {
                            if (find_move_in_table(curr_move, forewarn_moves))
                                curr_power = 80;
                            else
                                curr_power = 1;
                        }
                        if (curr_power > best_power)
                        {
                            most_powerful_move = curr_move;
                            best_power = curr_power;
                        }
                        else if (curr_power == best_power)
                        {
                            most_powerful_move = COIN_FLIP(most_powerful_move, curr_move);
                        }
                    }
            }
        }
    }
    if (best_power == 0)
        return 0;
    else
        return most_powerful_move;
}

bool anticipation_shudder(u8 bank)
{
    u8 banks_side = is_bank_from_opponent_side(bank);
    for (u8 opposing = 0; opposing < no_of_all_banks; opposing++)
    {
        if (banks_side != is_bank_from_opponent_side(opposing) && is_bank_present(opposing))
        {
            for (u8 i = 0; i < 4; i++)
            {
                u16 move = battle_participants[opposing].moves[i];
                if (move_table[move].script_id == 70) //one hit ko move check
                    return 1;
                if (move_table[move].base_power)
                {
                    if (apply_type_effectiveness(move, 64, move_table[move].type, bank, opposing, 0) > 64)
                        return 1;
                }
            }
        }
    }
    return 0;
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

u8 prepare_castform_switch(u8 effect, u8 bank)
{
    if (effect)
    {
        void* bs_castform = (void*) 0x082DB4A9;
        execute_battle_script(bs_castform);
        battle_scripting.active_bank = bank;
        battle_stuff_ptr->castform_switch_form = effect - 1;
    }
    return effect;
}

u8 has_ability_effect(u8 bank, u8 mold_breaker)
{
    if (new_battlestruct->bank_affecting[bank].gastro_acided)
        return false;

    u8 bank_ability = battle_participants[bank].ability_id;
    if (mold_breaker && bank != bank_attacker && bank_ability != ABILITY_SHADOW_SHIELD && bank_ability != ABILITY_PRISM_ARMOR && bank_ability != ABILITY_FULL_METAL_BODY)
    {
        u8 attacker_ability = battle_participants[bank_attacker].ability_id;
        if(!new_battlestruct->bank_affecting[bank_attacker].gastro_acided && (attacker_ability==ABILITY_MOLD_BREAKER
               || attacker_ability==ABILITY_TERAVOLT || attacker_ability==ABILITY_TURBOBLAZE))
            return false;
    }
    return true;
}

bool can_berserk_activate(u8 bank)
{
    struct battle_participant* berserker = &battle_participants[bank];
    u16 max_hp = berserker->max_hp;
    u16 curr_hp = berserker->current_hp;
    //curr hp must be less than 50%
    if (curr_hp < (max_hp / 2))
    {
        //poke had to have more than 50% of hp before taking the hit
        if ((hp_dealt + curr_hp) > (max_hp / 2))
            return 1;
    }
    return 0;
}

bool ability_try_status_effect(u16 move_effect, bool contact)
{
    if (contact && percent_chance(30))
    {
        new_battlestruct->move_effect.effect1 = move_effect;
        battlescript_push();
        battlescripts_curr_instruction = BS_DEF_ABILITY_STATUS;
        hitmarker |= HITMAKRER_IGNORE_SAFEGUARD;
        return 1;
    }
    return 0;
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

u8 ability_battle_effects(u8 switch_id, u8 bank, u8 ability_to_check, u8 special_cases_argument, u16 move)
{
    u8 effect = false;
    u16 curr_move;
    if (move > 0 && move < 622)
        curr_move = move;
    else
        curr_move = current_move;
    u8 move_type = get_attacking_move_type();

    if (special_cases_argument)
        last_used_ability = special_cases_argument;
    else
        last_used_ability = battle_participants[bank].ability_id;

    u8 bank_side = is_bank_from_opponent_side(bank);
    u8 common_effect=0;
    void* script_ptr;
    u8 adder=0;
    switch (switch_id)
    {
    case 0: //switch-in abilities
        if(special_cases_argument == 0xFF && !battle_flags.recorded_battle)
        {
            effect=load_weather_from_overworld();
            break;
        }
        if(status3[bank].switchinlock)
            break;
        if(handle_primal_reversion(bank))
        {
            battle_stuff_ptr->switch_in_ability_bank_counter--;
            effect=1;
            break;
        }
        u8 dontlock=0;
        switch (last_used_ability)
        {
        case ABILITY_MOLD_BREAKER:
            battle_communication_struct.multistring_chooser = 0;
        MOLDBREAKER_MSG:
            script_ptr = BS_MOLDBREAKER;
            common_effect=1;
            break;
        case ABILITY_TURBOBLAZE:
            battle_communication_struct.multistring_chooser = 1;
            goto MOLDBREAKER_MSG;
        case ABILITY_TERAVOLT:
            battle_communication_struct.multistring_chooser = 2;
            goto MOLDBREAKER_MSG;
        case ABILITY_PRESSURE:
            script_ptr = BS_PRESSURE;
            common_effect=1;
            break;
        case ABILITY_AURA_BREAK:
            script_ptr = BS_AURABREAK;
            common_effect=1;
            break;
        case ABILITY_FAIRY_AURA:
            script_ptr = BS_FAIRYAURA;
            common_effect=1;
            break;
        case ABILITY_DARK_AURA:
            script_ptr = BS_DARKAURA;
            common_effect=1;
            break;
        case ABILITY_UNNERVE:
            bank_attacker = bank;
            bank_target = bank ^ 1;
            execute_battle_script(BS_UNNERVE);
            effect = 1;
            break;
        case ABILITY_DOWNLOAD:
            {
                u16 def_sum = 0;
                u16 spdef_sum = 0;
                for (u8 i = 0; i < no_of_all_banks; i++)
                {
                    if (i != bank && bank_side!= is_bank_from_opponent_side(i))
                    {
                        def_sum += battle_participants[i].def;
                        spdef_sum += battle_participants[i].sp_def;
                    }
                }
                if (spdef_sum >= def_sum)
                    battle_scripting.stat_changer = 0x24;
                else
                    battle_scripting.stat_changer = 0x21;
                effect = 1;
                bank_attacker = bank;
                execute_battle_script(BS_DOWNLOAD);
            }
            break;
        case ABILITY_DROUGHT:
            if (!(battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain || battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_sun;

                if (get_item_effect(bank, true) == ITEM_EFFECT_HEATROCK)
                    battle_effects_duration.weather_dur = 8;
                else
                    battle_effects_duration.weather_dur = 5;

                execute_battle_script((void*) 0x082DB52A);
                battle_scripting.active_bank = bank;
                dontlock=1;
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

                execute_battle_script((void*) 0x082DB430);
                battle_scripting.active_bank = bank;
                dontlock=1;
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

                execute_battle_script((void*) 0x082DB470);
                battle_scripting.active_bank = bank;
                dontlock=1;
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

                execute_battle_script(BS_SNOWWARNING);
                battle_scripting.active_bank = bank;
                dontlock=1;
            }
            break;
        case ABILITY_DESOLATE_LAND:
            if (!(battle_weather.flags.harsh_sun))
            {
                effect = true;
                battle_weather.int_bw = weather_harsh_sun | weather_permament_sun;
                execute_battle_script(BS_DESOLATELAND);
                battle_scripting.active_bank = bank;
                dontlock=1;
            }
            break;
        case ABILITY_PRIMORDIAL_SEA:
            if (!(battle_weather.flags.heavy_rain))
            {
                effect = true;
                battle_weather.int_bw = weather_heavy_rain | weather_permament_rain;
                execute_battle_script(BS_PRIMORDIALSEA);
                battle_scripting.active_bank = bank;
                dontlock=1;
            }
            break;
        case ABILITY_DELTA_STREAM:
            if (!(battle_weather.flags.air_current))
            {
                effect = true;
                battle_weather.int_bw = weather_air_current;
                execute_battle_script(BS_DELTASTREAM);
                battle_scripting.active_bank = bank;
                dontlock=1;
            }
            break;
        case ABILITY_FRISK:
            {
                effect = true;
                battle_stuff_ptr->intimidate_user=bank;
                execute_battle_script(FRISK_BS);
            }
            break;
        case ABILITY_FOREWARN:
            {
                u16 best_move = get_forewarn_move(bank);
                if (best_move)
                {
                    effect = true;
                    u8 forewarn_bank = bank ^ 1;
                    if (get_move_position(forewarn_bank, best_move) == -1)
                        forewarn_bank ^= 2;
                    record_usage_of_move(forewarn_bank, best_move);
                    battle_scripting.active_bank = bank;
                    bank_partner_def = forewarn_bank;
                    execute_battle_script(BS_FOREWARN);
                    move_to_buff1(best_move);
                }
            }
            break;
        case ABILITY_ANTICIPATION:
            if (anticipation_shudder(bank))
            {
                effect = true;
                battle_scripting.active_bank = bank;
                execute_battle_script(BS_ANTICIPATION);
            }
            break;
        case ABILITY_IMPOSTER:
            {
                u8 opposing_bank = bank ^ 1;
                if (is_bank_present(opposing_bank) && !battle_participants[opposing_bank].status2.transformed && !battle_participants[bank].status2.transformed)
                {
                    effect = 1;
                    execute_battle_script(BS_IMPOSTER);
                    current_move = MOVE_TRANSFORM;
                    bank_attacker = bank;
                    bank_target = opposing_bank;
                    dontlock=1;
                }
            }
            break;
        case ABILITY_INTIMIDATE:
            execute_battle_script(BS_INTIMIDATE);
            battle_stuff_ptr->intimidate_user=bank;
            bank_attacker = bank;
            effect=true;
            break;
        case ABILITY_TRACE:
            {
                active_bank=bank^1;
                u16 hp1=battle_participants[active_bank].current_hp;
                if (battle_flags.double_battle)
                {
                    u16 hp2=battle_participants[active_bank^2].current_hp;
                    if(hp1==0 && hp2==0)
                        break;
                    if(hp1==0 || (hp2!=0 && COIN_FLIP(0,1)))
                        active_bank=active_bank^2;
                }
                else if (hp1==0)
                        break;
                last_used_ability=battle_participants[active_bank].ability_id;
                if (!last_used_ability)
                    break;
                if (last_used_ability!=ABILITY_TRACE) //If trace copies another switch-in ability. This fragment enables to activate that ability immediately after tracing.
                {
                    battle_stuff_ptr->switch_in_ability_bank_counter--;
                    dontlock=1;
                }
                script_ptr = (void*) 0x082DB452;
                execute_battle_script(script_ptr);
                battle_participants[bank].ability_id=last_used_ability;
                battle_scripting.active_bank = bank;
                battle_stuff_ptr->intimidate_user=bank;
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
            dontlock=1;
            for (u8 j = 0; j < no_of_all_banks; j++)
            {
                effect = castform_switch(j);
                effect = prepare_castform_switch(effect, j);
                if (effect)
                {
                    break;
                }
                effect = try_cherrim_change(j);
                if (effect)
                {
                    execute_battle_script(&cherrimswitch_bs);
                    battle_scripting.active_bank = j;
                    break;
                }
            }
            break;
        case ABILITY_FLOWER_GIFT:
            if (!(new_battlestruct->bank_affecting[bank].cherrim_transformed))
            {
                effect = try_cherrim_change(bank);
                if (effect)
                {
                    execute_battle_script(&cherrimswitch_bs);
                    battle_scripting.active_bank = bank;
                    new_battlestruct->bank_affecting[bank].cherrim_transformed = 1;
                    dontlock=1;
                }
            }
            break;
        case ABILITY_FORECAST:
            effect = castform_switch(bank);
            prepare_castform_switch(effect, bank);
            dontlock=1;
            break;
        case ABILITY_SLOW_START:
            new_battlestruct->bank_affecting[bank].slowstart_duration = 5;
            common_effect = 1;
            script_ptr = BS_SLOWSTART_MSG1;
            break;
        case ABILITY_ELECTRIC_SURGE:
            if (!new_battlestruct->field_affecting.electic_terrain)
            {
                common_effect = 1;
                reset_terrains(&new_battlestruct->field_affecting);
                new_battlestruct->field_affecting.electic_terrain = terrains_get_turns(bank);
                script_ptr = BS_ELECTRIC_SURGE;
            }
            break;
        case ABILITY_MISTY_SURGE:
            if (!new_battlestruct->field_affecting.misty_terrain)
            {
                common_effect = 1;
                reset_terrains(&new_battlestruct->field_affecting);
                new_battlestruct->field_affecting.misty_terrain = terrains_get_turns(bank);
                script_ptr = BS_MISTY_SURGE;
            }
            break;
        case ABILITY_GRASSY_SURGE:
            if (!new_battlestruct->field_affecting.grassy_terrain)
            {
                common_effect = 1;
                reset_terrains(&new_battlestruct->field_affecting);
                new_battlestruct->field_affecting.grassy_terrain = terrains_get_turns(bank);
                script_ptr = BS_GRASSY_SURGE;
            }
            break;
        case ABILITY_PSYCHIC_SURGE:
            if (!new_battlestruct->field_affecting.psychic_terrain)
            {
                common_effect = 1;
                reset_terrains(&new_battlestruct->field_affecting);
                new_battlestruct->field_affecting.psychic_terrain = terrains_get_turns(bank);
                script_ptr = BS_PSYCHIC_SURGE;
            }
            break;
        }
        if (common_effect)
        {
            effect = true;
            battle_scripting.active_bank = bank;
            execute_battle_script(script_ptr);
        }
        if(effect && !dontlock)
            status3[bank].switchinlock=1;
        break;
    case 1: //end turn abilities
        if (!(battle_participants[bank].current_hp && has_ability_effect(bank, 0)))
            break;
        bank_attacker = bank;
        switch (last_used_ability)
        {
            case ABILITY_RAIN_DISH:
                if (weather_abilities_effect() && (battle_weather.flags.downpour || battle_weather.flags.rain || battle_weather.flags.permament_rain || battle_weather.flags.heavy_rain))
                {
                    if (battle_participants[bank].current_hp < battle_participants[bank].max_hp && !new_battlestruct->bank_affecting[bank].heal_block)
                    {
                        execute_battle_script(BS_ABILITYHPCHANGE_END3);
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
                        if (battle_participants[bank].current_hp < battle_participants[bank].max_hp && !new_battlestruct->bank_affecting[bank].heal_block)
                        {
                            execute_battle_script(BS_ABILITYHPCHANGE_END3);
                            damage_loc = get_1_8_of_max_hp(bank) * (-1);
                            effect = true;
                        }
                    }
                    else if (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)
                    {
                        damage_loc = get_1_8_of_max_hp(bank);
                        execute_battle_script(BS_ABILITYHPCHANGE_END3);
                        effect = true;
                    }
                }
                break;
            case ABILITY_SOLAR_POWER:
                if (weather_abilities_effect() && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun))
                {
                    damage_loc = get_1_8_of_max_hp(bank);
                    execute_battle_script(BS_ABILITYHPCHANGE_END3);
                    effect = true;
                }
                break;
            case ABILITY_HARVEST:
                if (get_item_pocket_id(battle_stuff_ptr->used_held_items[bank]) == 4 && !battle_participants[bank].held_item)
                {
                    if ((weather_abilities_effect() && (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)) || (rng() & 1))
                    {
                        effect = true;
                        execute_battle_script(BS_HARVEST);
                    }
                }
                break;
            case ABILITY_HEALER:
                {
                    u8 friendly_bank = bank ^ 2;
                    if (friendly_bank < no_of_all_banks && battle_participants[friendly_bank].status.int_status & battle_participants[friendly_bank].current_hp)
                    {
                        if (__umodsi3(rng(), 100) + 1 <= 30)
                        {   battle_participants[friendly_bank].status2.nightmare = 0;
                            effect = true;
                            copy_status_condition_text(friendly_bank,0);
                            execute_battle_script(&healer_bs);
                            battle_scripting.active_bank = friendly_bank;
                            active_bank = friendly_bank;
                            battle_participants[friendly_bank].status.int_status = 0;
                            bb2_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[friendly_bank].status);
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
                        u16* used_held_item = &battle_stuff_ptr->used_held_items[i];
                        if (i != bank && *used_held_item && new_battlestruct->various.recently_used_item == *used_held_item)
                        {
                            effect = true;
                            execute_battle_script(BS_PICKUP);
                            battle_participants[bank].held_item = *used_held_item;
                            last_used_item = *used_held_item;
                            active_bank = bank;
                            bb2_setattributes_in_battle(0, 2, 0, 2,&battle_participants[bank].held_item);
                            mark_buffer_bank_for_execution(bank);
                            new_battlestruct->various.recently_used_item = 0;
                            *used_held_item = 0;
                            break;
                        }
                    }
                }
                break;
            case ABILITY_BAD_DREAMS:
                effect = true;
                battle_stuff_ptr->intimidate_user=bank;
                execute_battle_script(BAD_DREAMS_BS);
                break;
            case ABILITY_SPEED_BOOST:
                if (battle_participants[bank].spd_buff != 0xC && disable_structs[bank].is_first_turn != 2)
                {
                    effect = 1;
                    battle_scripting.stat_changer = 0x10 | STAT_SPD;
                    execute_battle_script(BS_ATK_ABILITY_CHANGES_ATK_STAT_END3);
                }
                break;
            case ABILITY_TRUANT:
                disable_structs[bank].truant_counter ^= 0x80;
                break;
            case ABILITY_MOODY:
                {
                    u8 raiseable_stats = 0;
                    u8 lowerable_stats = 0;
                    u8* stat_ptr = &battle_participants[bank].atk_buff;
                    for (u8 i = 0; i < 7; i ++)
                    {
                        if (*(stat_ptr + i) != 0xC)
                            raiseable_stats |= bits_table[i];
                        if (*(stat_ptr + i) != 0)
                            lowerable_stats |= bits_table[i];
                    }
                    if (raiseable_stats || lowerable_stats)
                    {
                        effect = true;
                        execute_battle_script(BS_MOODY);
                        new_battlestruct->various.var1 = 0;
                        new_battlestruct->various.var2 = 0;
                        while (raiseable_stats != 0)
                        {
                            u8 rand_stat = __umodsi3(rng(), 7);
                            if (raiseable_stats & bits_table[rand_stat])
                            {
                                new_battlestruct->various.var1 = 0x21 + rand_stat;
                                lowerable_stats = BIC(lowerable_stats, bits_table[rand_stat]);
                                break;
                            }
                        }
                        while (lowerable_stats != 0)
                        {
                            u8 rand_stat = __umodsi3(rng(), 7);
                            if (lowerable_stats & bits_table[rand_stat])
                            {
                                new_battlestruct->various.var2 = 0x91 + rand_stat;
                                break;
                            }
                        }
                    }
                }
                break;
            }
       if (common_effect && battle_participants[bank].status.int_status)
        {
            battle_participants[bank].status2.nightmare = 0;
            effect = true;
            copy_status_condition_text(bank,0);
            script_ptr = (void*) 0x082DB484;
            execute_battle_script(script_ptr);
            active_bank = bank;
            battle_scripting.active_bank = bank;
            battle_participants[bank].status.int_status = 0;
            bb2_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[bank].status);
            mark_buffer_bank_for_execution(bank);
        }
        break;
    case 2: //abilities that affect certain moves
        if (!has_ability_effect(bank, 1))
            break;
        const u16* table_ptr = NULL;
        switch (last_used_ability)
        {
        case ABILITY_SOUNDPROOF:
            table_ptr = sound_moves;
            break;
        case ABILITY_BULLETPROOF:
            table_ptr = ball_bomb_moves;
            break;
        case ABILITY_OVERCOAT:
            table_ptr = powder_moves;
            break;
        case ABILITY_DAZZLING:
        case ABILITY_QUEENLY_MAJESTY:
            if (get_priority(curr_move, bank_attacker) >= 1)
            {
                effect = 1;
                battlescripts_curr_instruction = BS_CANTUSE_PRIORITY;
            }
            break;
        }
        if (table_ptr != NULL && find_move_in_table(current_move, table_ptr))
        {
            effect = true;
            battlescripts_curr_instruction = (void*) 0x082DB61F;
            if (battle_participants[bank_attacker].status2.multiple_turn_move)
            {
                hitmarker |= 0x800;
            }
        }
        break;
    case 3: //abilities that affect type except telepathy
        if (curr_move && has_ability_effect(bank, 1))
        {
            if (protect_structs[bank_attacker].flag2_notfirststrike)
                adder = 1;
            u8 stat=0;

            switch (last_used_ability)
            {
            case ABILITY_TELEPATHY:
                if((bank == (bank_attacker^2)) && is_bank_present(bank) && DAMAGING_MOVE(curr_move))
                {
                    effect=true;
                    battlescripts_curr_instruction = (BS_TELEPATHY)+adder;
                }
                break;
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
                    battle_resources->ability_flags_ptr->flags_ability[bank].flag1_flashfire = 1;
                    script_ptr = (void*) 0x082DB5A7;
                    script_ptr += adder;
                    battlescripts_curr_instruction = script_ptr;
                }
                break;
            case ABILITY_LIGHTNING_ROD:
                if (move_type == TYPE_ELECTRIC && (!is_of_type(bank,TYPE_GROUND) || get_item_effect(bank,1)==ITEM_EFFECT_RINGTARGET))
                {
                    common_effect=2;
                    stat=4;
                }
                break;
            case ABILITY_STORM_DRAIN:
                if (move_type == TYPE_WATER)
                {
                    common_effect=2;
                    stat=4;
                }
                break;
            case ABILITY_SAP_SIPPER:
                if (move_type == TYPE_GRASS)
                {
                    common_effect=2;
                    stat=1;
                }
                break;
            case ABILITY_MOTOR_DRIVE:
                if (move_type == TYPE_ELECTRIC)
                {
                    common_effect=2;
                    stat=3;
                }
                break;
            }
            if(common_effect==1)
            {
                if (battle_participants[bank].max_hp == battle_participants[bank].current_hp || new_battlestruct->bank_affecting[bank].heal_block)
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
            else if(common_effect==2)
            {
                u8* stat_ptr = &battle_participants[bank].hp_buff;
                stat_ptr += stat;

                if((*stat_ptr)!=0xC)
                {
                    battle_scripting.stat_changer=0x20+stat;
                    *stat_ptr +=1 ;
                    script_ptr = &absorb_ability_boost_bs;
                }
                else
                    script_ptr = &absorb_ability_immune_bs;
                script_ptr += adder;
                effect = true;
                battlescripts_curr_instruction = script_ptr;
            }
        }
        break;
    case 4: //move end turn abilities
        if (has_ability_effect(bank, 0) && MOVE_WORKED && (special_statuses[bank_target].moveturn_losthp) && battle_participants[bank_attacker].current_hp)
        {
            u16 curr_hp = battle_participants[bank].current_hp;
            u8 contact = does_move_make_contact(curr_move, bank_attacker);
            switch (last_used_ability)
            {
            case ABILITY_STATIC:
            ENDTURN_PARALYZE:
                if (!cant_become_paralyzed(bank_attacker, 0))
                    effect = ability_try_status_effect(MOVEEFFECT_PRLZ | MOVEEFFECT_AFFECTSUSER, contact);
                break;
            case ABILITY_FLAME_BODY:
                if (!cant_become_burned(bank_attacker, 0))
                    effect = ability_try_status_effect(MOVEEFFECT_BRN | MOVEEFFECT_AFFECTSUSER, contact);
                break;
            case ABILITY_POISON_POINT:
            ENDTURN_PSN:
                if (!cant_poison(bank_target, bank_attacker, 0))
                    effect = ability_try_status_effect(MOVEEFFECT_PSN | MOVEEFFECT_AFFECTSUSER, contact);
                break;
            case ABILITY_EFFECT_SPORE:
                if(!is_of_type(bank_attacker, TYPE_GRASS) && !check_ability(bank_attacker, ABILITY_OVERCOAT) && get_item_effect(bank_attacker, 1) != ITEM_EFFECT_SAFETYGOOGLES) //add safety goggles check
                {
                    switch(__umodsi3(rng(), 3))
                    {
                    case 0:
                        goto ENDTURN_PARALYZE;
                    case 1:
                        goto ENDTURN_PSN;
                    default:
                        if (!cant_fall_asleep(bank_attacker, 0))
                            effect = ability_try_status_effect(MOVEEFFECT_SLP | MOVEEFFECT_AFFECTSUSER, contact);
                    }
                }
                break;
            case ABILITY_AFTERMATH:
                if (battle_participants[bank_attacker].current_hp && curr_hp == 0 && contact && !(ability_battle_effects(0x13, 0, ABILITY_DAMP, 0, 0)) && !(has_ability_effect(bank_attacker, 0) && battle_participants[bank_attacker].ability_id == ABILITY_MAGIC_GUARD))
                {
                    damage_loc = get_1_4_of_max_hp(bank_attacker);
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_AFTERMATH;
                }
                break;
            case ABILITY_INNARDS_OUT:
                if (curr_hp == 0 && not_magicguard(bank_attacker))
                {
                    damage_loc = hp_dealt;
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_AFTERMATH;
                }
                break;
            case ABILITY_MUMMY:
                if (contact && battle_participants[bank_attacker].ability_id != ABILITY_MUMMY && battle_participants[bank_attacker].ability_id != ABILITY_STANCE_CHANGE && battle_participants[bank_attacker].ability_id != ABILITY_MULTITYPE)
                {
                    effect = true;
                    battle_participants[bank_attacker].ability_id = ABILITY_MUMMY;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_MUMMY;
                }
                break;
            case ABILITY_CURSED_BODY:
                if (!disable_structs[bank_attacker].disabled_move && percent_chance(30) && !check_field_for_ability(ABILITY_AROMA_VEIL, bank_side, 0))
                {
                    disable_structs[bank_attacker].disabled_move = curr_move;
                    disable_structs[bank_attacker].disable_timer = 3;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_CURSEDBODY;
                    effect = true;
                }
                break;
            case ABILITY_ROUGH_SKIN:
            case ABILITY_IRON_BARBS:
                if (contact && not_magicguard(bank_attacker))
                {
                    damage_loc = get_1_8_of_max_hp(bank_attacker);
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_ROUGHSKIN;
                }
                break;
            case ABILITY_GOOEY:
            case ABILITY_TANGLING_HAIR:
                if (contact && battle_participants[bank_attacker].spd_buff != 0)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_ATK_STAT;
                    battle_scripting.stat_changer = 0x93;
                }
                break;
            case ABILITY_RATTLED:
                if (curr_hp && battle_participants[bank].spd_buff != 0xC && (move_type == TYPE_BUG || move_type == TYPE_DARK || move_type == TYPE_GHOST))
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_DEF_STAT;
                    battle_scripting.stat_changer = 0x13;
                }
                break;
            case ABILITY_JUSTIFIED:
                if (curr_hp && battle_participants[bank].atk_buff != 0xC && move_type == TYPE_DARK)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_DEF_STAT;
                    battle_scripting.stat_changer = 0x11;
                }
                break;
            case ABILITY_STEADFAST:
                if (curr_hp && battle_participants[bank].spd_buff != 0xC && battle_participants[bank].status2.flinched)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_DEF_STAT;
                    battle_scripting.stat_changer = 0x13;
                }
                break;
            case ABILITY_ANGER_POINT:
                if (curr_hp && crit_loc==2 && special_statuses[bank].moveturn_losthp && battle_participants[bank].atk_buff != 0xC)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_ANGERPOINT;;
                    battle_participants[bank].atk_buff=0xC;
                }
                break;
            case ABILITY_WEAK_ARMOR:
                if (curr_hp && special_statuses[bank].moveturn_losthp_physical && (battle_participants[bank].def_buff > 0 || battle_participants[bank].spd_buff != 0xC))
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_WEAK_ARMOR;
                    new_battlestruct->various.active_bank = bank;
                }
                break;
            case ABILITY_CUTE_CHARM:
                if (!check_ability(bank_attacker, ABILITY_OBLIVIOUS) && percent_chance(30) && contact && !check_field_for_ability(ABILITY_AROMA_VEIL, bank_side, 0))
                {
                    u8 target_gender = gender_from_pid(battle_participants[bank].poke_species, battle_participants[bank].pid);
                    u8 attacker_gender = gender_from_pid(battle_participants[bank_attacker].poke_species, battle_participants[bank_attacker].pid);
                    if (target_gender != attacker_gender && target_gender != 0xFF && attacker_gender != 0xFF && ((battle_participants[bank_attacker].status2.in_love & bits_table[bank_target]) == 0))
                    {
                        effect = true;
                        battle_participants[bank_attacker].status2.in_love |= bits_table[bank];
                        battlescript_push();
                        battlescripts_curr_instruction = BS_CUTECHARM;
                    }
                }
                break;
            case ABILITY_STAMINA:
                if (curr_hp && battle_participants[bank].def_buff != 0xC)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_DEF_STAT;
                    battle_scripting.stat_changer = 0x12;
                }
                break;
            case ABILITY_WATER_COMPACTION:
                if (curr_hp && battle_participants[bank].def_buff != 0xC && move_type == TYPE_WATER)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_DEF_STAT;
                    battle_scripting.stat_changer = 0x22;
                }
                break;
            case ABILITY_BERSERK:
                if (curr_hp && battle_participants[bank].sp_atk_buff != 0xC && can_berserk_activate(bank) && !new_battlestruct->various.sheerforce_bonus
                    && multihit_counter <= 1)
                {
                    effect = true;
                    battlescript_push();
                    battlescripts_curr_instruction = BS_DEF_ABILITY_CHANGES_DEF_STAT;
                    battle_scripting.stat_changer = 0x14;
                }
                break;
            }
        }
        break;
    case 5: //status immunities
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (has_ability_effect(i, 0))
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
                case ABILITY_WATER_BUBBLE:
                    if (battle_participants[i].status.flags.burn)
                        common_effect=1;
                    break;
                case ABILITY_INSOMNIA:
                case ABILITY_VITAL_SPIRIT:
                    if (battle_participants[i].status.flags.sleep)
                    {
                        common_effect=1;
                        battle_participants[i].status2.nightmare = 0;
                    }
                    break;
                case ABILITY_OBLIVIOUS:
                    if (battle_participants[i].status2.in_love)
                    {
                        battle_participants[i].status2.in_love = 0;
                        strcpy_xFF_terminated_0(battle_text_buff1, (const u8*) 0x0831BCA0);
                        effect = true;
                    }
                    break;
                case ABILITY_OWN_TEMPO:
                    if (battle_participants[i].status2.confusion)
                    {
                        battle_participants[i].status2.confusion = 0;
                        strcpy_xFF_terminated_0(battle_text_buff1, (const u8*) 0x0831BC98);
                        effect = true;
                    }
                    break;
                }
                if (common_effect)
                {
                    copy_status_condition_text(i,0);
                    battle_participants[i].status.int_status = 0;
                    effect=true;
                    battlescript_push();
                    battlescripts_curr_instruction = (void*) 0x082DB68C;
                    battle_scripting.active_bank = active_bank = i;
                    bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[i].status);
                    mark_buffer_bank_for_execution(active_bank);
                    break;
                }
                if (effect)
                    break;
            }
        }
        break;
    case 6: //check castform and cherrim
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (check_ability(i, ABILITY_FORECAST))
            {
                effect = prepare_castform_switch(castform_switch(i), i);
                if (effect == true)
                    break;
            }
            else if (check_ability(i, ABILITY_FLOWER_GIFT))
            {
                if (try_cherrim_change(i))
                {
                    effect = 1;
                    execute_battle_script(&cherrimswitch_bs);
                    battle_scripting.active_bank = i;
                    break;
                }
            }
        }
        break;
     case 7: //user's synchronize
        adder=0x40;
    case 8: //target's synchronize after static etc.
        if(battle_participants[bank].ability_id==ABILITY_SYNCHRONIZE && has_ability_effect(bank,0) && battle_stuff_ptr->synchronize_effect_chooser)
        {
            effect=true;
            hitmarker &= 0xFFFFBFFF;
            battle_stuff_ptr->synchronize_effect_chooser &= 0x3F;
            battle_communication_struct.move_effect=adder+battle_stuff_ptr->synchronize_effect_chooser;
            battle_scripting.active_bank=bank;
            battlescript_push();
            battlescripts_curr_instruction=(void *)(0x82DB680);
            hitmarker |= 0x2000;
        }
        break;
    case 10:
        if (has_ability_effect(bank, 0) && MOVE_WORKED
                && battle_participants[bank_attacker].current_hp && (special_statuses[bank_target].moveturn_losthp))
        {
            u8 contact = does_move_make_contact(curr_move, bank_attacker);
            switch(last_used_ability)
            {
                case ABILITY_MAGICIAN:
                    if (current_move==MOVE_DOOM_DESIRE || current_move==MOVE_FUTURE_SIGHT
                        || check_ability(bank_target, ABILITY_STICKY_HOLD))
                        break;
                    if (try_stealing_bank_item(bank_attacker, bank_target))
                    {
                        battlescript_push();
                        battlescripts_curr_instruction = BS_MAGICIAN;
                        effect = true;
                        bank_partner_def = bank_target; //for animation
                    }
                    break;
                case ABILITY_POISON_TOUCH:
                    if (battle_participants[bank_target].current_hp && contact && !cant_poison(bank, bank_target, 0) && percent_chance(30))
                    {
                        new_battlestruct->move_effect.effect1 = MOVEEFFECT_PSN;
                        battlescript_push();
                        battlescripts_curr_instruction = BS_ATK_ABILITY_STATUS;
                        effect=true;
                    }
                    break;
                case ABILITY_STENCH:
                    if (contact && percent_chance(10)) //todo later
                    {

                    }
                    break;
            }
        }
        break;
    case 12: //check opposing field for ability
        effect = check_field_for_ability(ability_to_check, bank_side, special_cases_argument);
        break;
    case 13: //check bank field for ability
        effect = check_field_for_ability(ability_to_check, bank_side ^ 1, special_cases_argument);
        break;
    case 14: //check whole field for ability
    case 19:
        effect = check_field_for_ability(ability_to_check, 3, special_cases_argument);
        break;
    case 15: //check field except the bank
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (battle_participants[i].ability_id == ability_to_check && i != bank && has_ability_effect(i, special_cases_argument))
            {
                effect = i + 1;
                last_used_ability = ability_to_check;
                break;
            }
        }
        break;
    case 16: //count instances of ability in the opponent field
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (is_bank_from_opponent_side(i) != bank_side && battle_participants[i].ability_id == ability_to_check && has_ability_effect(i, special_cases_argument))
            {
                effect++;
                last_used_ability = ability_to_check;
            }
        }
        break;
    case 17: //count instances of ability in the banks field
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if (is_bank_from_opponent_side(i) == bank_side && battle_participants[i].ability_id == ability_to_check && has_ability_effect(i, special_cases_argument))
            {
                effect++;
                last_used_ability = ability_to_check;
            }
        }
        break;
    case 18: //count instances of ability except bank
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            if ( i != bank_side && battle_participants[i].ability_id == ability_to_check && has_ability_effect(i, special_cases_argument))
            {
                effect++;
                last_used_ability = ability_to_check;
            }
        }
        break;
    case 20: //check ally
        if (get_ally_ability(bank, special_cases_argument) == ability_to_check)
        {
            effect = (bank ^ 2);
            last_used_ability = ability_to_check;
        }
        break;
    case 21: // color change
        if (check_ability(bank,ABILITY_COLOR_CHANGE) && curr_move != MOVE_STRUGGLE &&
            battle_participants[bank].current_hp && MOVE_WORKED && TARGET_TURN_DAMAGED &&
            !new_battlestruct->various.sheerforce_bonus && !is_of_type(bank, move_type))
        {
            battle_text_buff1[0] = 0xFD;
            battle_text_buff1[1] = 0x3;
            battle_text_buff1[2] = move_type;
            battle_text_buff1[3] = 0xFF;
            effect = true;
            battlescript_push();
            battlescripts_curr_instruction = (void*) 0x082DB64D;
            set_type(bank, move_type);
        }
        break;
    case 22:
        if (check_ability(bank,ABILITY_PICKPOCKET) && MOVE_WORKED && TARGET_TURN_DAMAGED && battle_participants[bank].current_hp)
        {
            if (!does_move_make_contact(curr_move, bank_attacker)
                || (new_battlestruct->various.sheerforce_bonus)
                || (check_ability(bank_attacker, ABILITY_STICKY_HOLD)))
                break;
            if (try_stealing_bank_item(bank, bank_attacker))
            {
                battlescript_push();
                battlescripts_curr_instruction = BS_PICKPOCKET;
                effect = true;
            }
        }
        break;
    }
    if (effect && last_used_ability != 0xFF && (switch_id <= 12 || switch_id >= 21))
        record_usage_of_ability(bank, last_used_ability);
    return effect;
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
    u16 species = battle_participants[bank].poke_species;
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
                        u16 trapped_move = battle_stuff_ptr->trapped_move[active_bank];
                        move_to_buff1(trapped_move);
                        attacker_struct->status2.trapped_in_wrap--;
                        if (attacker_struct->status2.trapped_in_wrap && not_magicguard(active_bank)) //we're doing damage
                        {
                            battle_scripting.AnimInfo1 = trapped_move;
                            battle_scripting.AnimInfo2 = trapped_move >> 8;
                            if (get_item_effect(new_battlestruct->bank_affecting[active_bank].wrap_bank, 1) == ITEM_EFFECT_BINDINGBAND)
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
                            if (!attacker_struct->status2.confusion)
                            {
                                effect = 1;
                                battle_communication_struct.move_effect = 0x47;
                                set_move_effect(1, 0);
                                if (attacker_struct->status2.confusion)
                                    call_bc_move_exec((void*)0x82DB2AF);
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

            }
            if (effect != 5) //check for uproar
                 *tracker += 1;
            #define TRACKER_MAX 30
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
                    call_bc_move_exec(&grassyterrain_hpheal);
                    for (u8 i = 0; i < no_of_all_banks; i++)
                    {
                        new_battlestruct->bank_affecting[i].grassyterrain_heal = 0;
                    }
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
    if (battle_flags.multibattle)
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

