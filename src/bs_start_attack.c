#include "defines.h"
#include "static_references.h"

enum drive_types
{
    DOUSE_DRIVE_EFFECT=1,
    BURN_DRIVE_EFFECT,
    CHILL_DRIVE_EFFECT,
    SHOCK_DRIVE_EFFECT
};

u32 get_item_extra_param(u16 item);
u16 get_mega_species(u8 bank, u8 chosen_method);
u8 weather_abilities_effect();
bool find_move_in_table(u16 move, const u16* table_ptr);
void setup_berry_consume_buffers(u8 bank);
u8 get_attacking_move_type();
u8 check_ability(u8 bank, u8 ability);
u16 get_speed(u8 bank);
u8 has_ability_effect(u8 bank, u8 mold_breaker);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 get_bank_side(u8 bank);
void bs_push_current(void* now);
void bs_execute(void* bs);
void call_bc_move_exec(void* bs_ptr);
void reset_multiple_turn_effects(u8 bank);

bool is_bank_present(u8 bank)
{
    if((absent_bank_flags & BIT_GET(bank)) || battle_participants[bank].current_hp == 0 || bank >= no_of_all_banks)
        return 0;
    return 1;
}

u8 get_target_of_move(u16 move, u8 target_given, u8 adjust)
{
    u8 target_case;
    u8 old_target = battle_stuff_ptr->move_target[bank_attacker];
    u8 result_target = old_target;
    u8 attacker_side = get_bank_side(bank_attacker);
    u8 target_side = attacker_side ^ 1;
    if (target_given)
        target_case = target_given;
    else
        target_case = move_table[move].target;
    if(battle_flags.double_battle)
    {
        switch (target_case)
        {
            case 4:
            case 0: //chosen target
                if (side_timers[target_side].followme_timer && battle_participants[side_timers[target_side].followme_target].current_hp)
                    result_target = side_timers[target_side].followme_target;
                else
                {
                    u8 ally_bank=bank_attacker^2;
                    u8 ally_alive=is_bank_present(ally_bank);
                    u8 target_alive=is_bank_present(target_side);
                    u8 target_partner=target_side^2;
                    u8 target_partner_alive=is_bank_present(target_partner);
                    if(adjust && target_case==0)
                    {
                        if(old_target==ally_bank && !is_bank_present(ally_bank))
                            result_target=target_side;
                        if(result_target==target_side && !is_bank_present(target_side))
                            result_target^=2;
                    }
                    else
                    {
                        if(target_alive && !target_partner_alive)
                            result_target=target_side;
                        else if (!target_alive && target_partner_alive)
                            result_target=target_partner;
                        else
                            result_target=COIN_FLIP(target_side,target_partner);
                    }
                    u16 move_type = get_attacking_move_type();
                    u8 ability = 0;
                    u8 redirect = 0;
                    u16 max_speed=0;
                    u8 redirect_candidate=0;
                    if (move_type == TYPE_ELECTRIC)
                        ability = ABILITY_LIGHTNING_ROD;
                    else if (move_type == TYPE_WATER)
                        ability = ABILITY_STORM_DRAIN;
                    u8 alive_candidates = target_alive+ally_alive+target_partner_alive;
                    if(ability && check_ability(target_side,ability) && target_alive && max_speed<get_speed(target_side))
                    {
                        redirect_candidate=target_side;
                        max_speed=get_speed(target_side);
                        redirect=1;
                    }
                    if(ability && check_ability(target_partner,ability) && target_partner_alive && max_speed<get_speed(target_partner))
                    {
                        redirect_candidate=target_partner;
                        max_speed=get_speed(target_partner);
                        redirect=1;
                    }
                    if(ability && check_ability(ally_bank,ability) && ally_alive && max_speed<get_speed(ally_bank))
                    {
                        redirect_candidate=ally_bank;
                        redirect=1;
                    }
                    if(redirect && alive_candidates>=2 && (!adjust || (old_target!=redirect_candidate)))
                    {
                        result_target=redirect_candidate;
                        record_usage_of_ability(result_target, ability);
                        special_statuses[result_target].lightning_rod_redirected = 1;
                        if (ability == ABILITY_STORM_DRAIN)
                            new_battlestruct->various.stormdrain = 1;
                    }
                }
                break;
            case 1:
            case 8:
            case 64:
                result_target = target_side;
                if (!is_bank_present(result_target))
                    result_target ^= 2;
                break;
            case 32:
                result_target=0;
                while((result_target==bank_attacker || !is_bank_present(result_target)) && result_target<no_of_all_banks)
                    result_target++;
                break;
            case 18: //acupressure
                if (!(old_target == (bank_attacker ^ 2) && !is_bank_present(bank_attacker ^ 2)))
                    break;
            case 2: //can be everyone
            case 16: //user
                result_target = bank_attacker;
                break;
        }
    }
    else
    {
        if(!adjust)
        {
            switch(target_case)
            {
                case 0:
                case 1:
                case 4:
                case 8:
                case 32:
                case 64:
                    result_target = target_side;
                    break;
                case 2:
                case 16:
                    result_target = bank_attacker;
                    break;
            }
        }
    }
    battle_stuff_ptr->move_target[bank_attacker] = result_target;
    return result_target;
}

u8 calculate_move_type(u8 bank, u16 move, u8 set_bonus)
{
    u8 ability=battle_participants[bank].ability_id;
    u8 move_type = TYPE_EGG;
    if(new_battlestruct->bank_affecting[bank].electrify)
        move_type=TYPE_ELECTRIC;
    else
    {
        switch(move)
        {
        case MOVE_WEATHER_BALL:
            if(weather_abilities_effect())
            {
                if (battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun)
                {
                    move_type=TYPE_FIRE;
                }
                else if (battle_weather.flags.rain || battle_weather.flags.permament_rain ||
                          battle_weather.flags.heavy_rain || battle_weather.flags.downpour)
                {
                    move_type=TYPE_WATER;
                }
                else if (battle_weather.flags.hail || battle_weather.flags.permament_hail)
                {
                    move_type=TYPE_ICE;
                }
                else if (battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm)
                {
                    move_type=TYPE_ROCK;
                }
                if (move_type != TYPE_EGG && move_type != TYPE_ELECTRIC && set_bonus)
                    battle_scripting.damage_multiplier=2;
            }
            break;
        case MOVE_HIDDEN_POWER:
            {
                struct iv_set *ivs= &battle_participants[bank].ivs;
                u32 sum=((ivs->iv_hp)&1)+(((ivs->iv_atk)&1)<<1)+(((ivs->iv_def)&1)<<2)+(((ivs->iv_spd)&1)<<3)
                       +(((ivs->iv_sp_atk)&1)<<4)+(((ivs->iv_sp_def)&1)<<5);
                move_type=__udivsi3(sum*15,63);
            }
            break;
        case MOVE_JUDGMENT:
            {
                if(get_item_effect(bank,1) == ITEM_EFFECT_PLATES)
                {
                    move_type=(u16)get_item_extra_param(battle_participants[bank].held_item);
                }
		    }
            break;
        case MOVE_TECHNO_BLAST:
            {
                if(get_item_effect(bank,1) == ITEM_EFFECT_DRIVES)
                {
                	switch ((u16)get_item_extra_param(battle_participants[bank].held_item))
                    {
                    case DOUSE_DRIVE_EFFECT://DOUSEDRIVE
                        move_type=TYPE_WATER;
                        break;

                    case BURN_DRIVE_EFFECT://BURNDRIVE
                        move_type=TYPE_FIRE;
                        break;

                    case CHILL_DRIVE_EFFECT://CHILLDRIVE
                        move_type=TYPE_ICE;
                        break;

                    case SHOCK_DRIVE_EFFECT://SHOCKDRIVE
                        move_type=TYPE_ELECTRIC;
                        break;
                    }
                }
            }
            break;
        }
        u8 ate=0;
        if(move_type == TYPE_EGG && (DAMAGING_MOVE(move)) && has_ability_effect(bank,0) && move_table[move].type==TYPE_NORMAL)
        {
            switch(ability)
            {
            case ABILITY_AERILATE:
                move_type=TYPE_FLYING;
                ate=1;
                break;
            case ABILITY_PIXILATE:
                move_type=TYPE_FAIRY;
                ate=1;
                break;
            case ABILITY_REFRIGERATE:
                move_type=TYPE_ICE;
                ate=1;
                break;
            case ABILITY_GALVANIZE:
                move_type=TYPE_ELECTRIC;
                ate=1;
                break;
            }
        }

        if (ate && set_bonus)
            new_battlestruct->various.ate_bonus=1;

        if (find_move_in_table(move, sound_moves) && check_ability(bank,ABILITY_LIQUID_VOICE) && move_type == TYPE_EGG)
        {
            move_type = TYPE_WATER;
        }
    }
    if((new_battlestruct->field_affecting.ion_deluge)
       && (move_table[move].type==TYPE_NORMAL || check_ability(bank,ABILITY_NORMALIZE)))
        move_type = TYPE_ELECTRIC;
    return move_type;
}

void set_attacking_move_type(void)
{
    u8 move_type = calculate_move_type(bank_attacker, current_move, 1);
    if (move_type != TYPE_EGG)
    {
        battle_stuff_ptr->dynamic_move_type=move_type + 0x80;
    }
    else
        battle_stuff_ptr->dynamic_move_type = 0;
}

inline void clear_move_outcome(void)
{
    memset(&move_outcome, 0, sizeof(struct move_outcome));
}

void* get_move_battlescript_ptr(u16 move)
{
    return battlescripts_table[move_table[move].script_id];
}

void reset_indicators_height(void)
{
    struct mega_related* mega = &new_battlestruct->mega_related;
    for(u8 i = 0; i<no_of_all_banks ;i++)
    {
        objects[mega->indicator_id_pbs[i]].pos2.y=0;
    }
}

u8 check_mega_evo(u8 bank)
{
    struct battle_participant* attacker_struct = &battle_participants[bank];
    u8 ai_mega_mode=0;
    u16 mega_species = get_mega_species(bank,0xFB);
    if (mega_species)
    {
        ai_mega_mode=1;
    }
    else
    {
        mega_species = get_mega_species(bank,0xFC);
        if(mega_species)
        {
            ai_mega_mode = 2;
        }
    }
    u8 banks_side = get_bank_side(bank);
    u8 bank_mega_mode=0;
    if(mega_species)
    {
        if (battle_flags.link && !new_battlestruct->mega_related.link_indicator[bank])
            return 0;
        if(bank==0)
        {
            bank_mega_mode=new_battlestruct->mega_related.user_trigger;
            if(bank_mega_mode)
            {
                if(!battle_flags.multibattle)
                {
                    new_battlestruct->mega_related.evo_happened_pbs|=0x5;
                }
                else
                {
                    new_battlestruct->mega_related.evo_happened_pbs|=0x1;
                }
                objects[new_battlestruct->mega_related.trigger_id].private[ANIM_STATE]=DISABLE;
            }
        }
        else if(bank==2 && !battle_flags.multibattle)
        {
            bank_mega_mode=new_battlestruct->mega_related.ally_trigger;
            if(bank_mega_mode)
            {
                new_battlestruct->mega_related.evo_happened_pbs|=0x5;
                objects[new_battlestruct->mega_related.trigger_id].private[ANIM_STATE]=DISABLE;
            }
        }
        else if(!(new_battlestruct->mega_related.evo_happened_pbs & (BIT_GET(bank) | BIT_GET(bank ^ 2))))
        {
            bank_mega_mode=ai_mega_mode;
            if(bank_mega_mode)
            {
                new_battlestruct->mega_related.evo_happened_pbs |= BIT_GET(bank);
            }
        }
    }
    if(mega_species && bank_mega_mode)
    {
        struct pokemon* poke_address;
        if (banks_side == 1)
        {
            poke_address = &party_opponent[battle_team_id_by_side[bank]];
            new_battlestruct->mega_related.ai_party_mega_check|=BIT_GET(battle_team_id_by_side[bank]);
        }
        else
        {
            poke_address = &party_player[battle_team_id_by_side[bank]];
            new_battlestruct->mega_related.party_mega_check|=BIT_GET(battle_team_id_by_side[bank]);
        }
        set_attributes(poke_address, ATTR_SPECIES, &mega_species);
        calculate_stats_pokekmon(poke_address);
        attacker_struct->atk = get_attributes(poke_address, ATTR_ATTACK, 0);
        attacker_struct->def = get_attributes(poke_address, ATTR_DEFENCE, 0);
        attacker_struct->spd = get_attributes(poke_address, ATTR_SPEED, 0);
        attacker_struct->sp_atk = get_attributes(poke_address, ATTR_SPECIAL_ATTACK, 0);
        attacker_struct->sp_def = get_attributes(poke_address, ATTR_SPECIAL_DEFENCE, 0);
        attacker_struct->species = mega_species;
        const struct poke_basestats* PokeStats = &((*basestat_table)[mega_species]);
        attacker_struct->type1 = PokeStats->type1;
        attacker_struct->type2 = PokeStats->type2;
        // The ability 1 and ability 2 of the mega species in the base stat table should both be set and
        // have the same value.
        attacker_struct->ability_id = PokeStats->ability1;

        attacker_struct->max_hp = get_attributes(poke_address, ATTR_TOTAL_HP, 0);
        attacker_struct->current_hp = get_attributes(poke_address, ATTR_CURRENT_HP, 0);
        attacker_struct->level = get_attributes(poke_address, ATTR_LEVEL, 0);

        //set buffer for new species and item used
        battle_text_buff1[0] = 0xFD;
        battle_text_buff1[1] = 6;
        battle_text_buff1[2] = mega_species;
        battle_text_buff1[3] = mega_species >> 8;
        battle_text_buff1[4] = 0xFF;
        status3[bank].switchinlock=0;

        if(bank_mega_mode==2)
        {
            bs_execute(BS_FERVENT_EVO);
        }
        else
        {
            //buffer for mega ring
            last_used_item = attacker_struct->held_item;
            u16 MEGA_RING = KEYSTONE;
            battle_text_buff2[0] = 0xFD;
            battle_text_buff2[1] = 10;
            battle_text_buff2[2] = MEGA_RING;
            battle_text_buff2[3] = MEGA_RING >> 8;
            battle_text_buff2[4] = 0xFF;
            bs_execute(BS_MEGA_EVO);
        }

        new_battlestruct->various.active_bank = bank;
        return 1;
    }
    else
        return 0;
}

bool check_focus(u8 bank)
{
    bool is_bank_focusing = false;
    if(status3[bank].focus_punch_charge)
    {
        is_bank_focusing = true;
        status3[bank].focus_punch_charge = 0;
        bs_execute((void *)0x82DB1FF);
    }
    return is_bank_focusing;
}

u16 get_move_from_pledge(u8 bank);

void bs_start_attack(void)
{
    u8 mode=0;  //mode 0 - get type with adjusting chosen target
                //mode 1 - get type with calculating target from scratch
                //mode 2 - don't get type and calculating target from scratch

    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        bank_attacker = i;
        if (menu_choice_pbs[i] == ACTION_MOVE)
        {
            if (check_mega_evo(i) || check_focus(i))
                return;
        }
    }
    bank_attacker=turn_order[current_move_turn];
    if (new_battlestruct->bank_affecting[bank_attacker].sky_drop_target && is_bank_present(bank_attacker))
    {
        reset_multiple_turn_effects(bank_attacker);
        battle_state_mode = 0xB;
    }
    else if(!(bits_table[bank_attacker]&battle_stuff_ptr->absent_bank_flags_prev_turn))
    {
        struct battle_participant *attacker_struct = &battle_participants[bank_attacker];
        crit_loc=1;
        battle_scripting.damage_multiplier=0;
        battle_stuff_ptr->atk_canceller_state_tracker=0;
        clear_move_outcome();
        multihit_counter=0;
        battle_communication_struct.multistring_chooser=0;
        current_move_position=battle_stuff_ptr->chosen_move_position[bank_attacker];
        if(protect_structs[bank_attacker].flag0_onlystruggle)
        {
            protect_structs[bank_attacker].flag0_onlystruggle=0;
            current_move=MOVE_STRUGGLE;
            last_used_move=MOVE_STRUGGLE;
            hitmarker|=HITMARKER_NO_PPDEDUCT;
            mode=2;
        }
        else
        {
            if(attacker_struct->status2.multiple_turn_move || attacker_struct->status2.recharge)
            {
                current_move=locked_move[bank_attacker];
                last_used_move=locked_move[bank_attacker];
            }
            else
            {
                u16 *enc_move=&disable_structs[bank_attacker].encored_move;
                u8* enc_idx=&disable_structs[bank_attacker].encored_index;
                u16 *atk_enc_move=&(attacker_struct->moves[*enc_idx]);
                if(*enc_move)
                {
                    if(*atk_enc_move==*enc_move)
                    {
                        current_move=*enc_move;
                        last_used_move=*enc_move;
                        current_move_position=*enc_idx;
                        mode=1;
                    }
                    else
                    {
                        current_move_position=*enc_idx;
                        current_move=*atk_enc_move;
                        last_used_move=*atk_enc_move;
                        *enc_move=0;
                        *enc_idx=0;
                        disable_structs[bank_attacker].encore_timer&=0xF0;
                        mode=1;
                    }
                }
                else
                {
                    u16 pledge_move=get_move_from_pledge(bank_attacker);
                    if(pledge_move)
                    {
                        current_move=pledge_move;
                    }
                    else
                    {
                        current_move=chosen_move_by_banks[bank_attacker];
                    }
                    last_used_move=chosen_move_by_banks[bank_attacker];
                    if(chosen_move_by_banks[bank_attacker]!=attacker_struct->moves[current_move_position])
                        mode=1;
                }
            }
        }
        if (mode==0)
        {
            set_attacking_move_type();
            bank_target=get_target_of_move(current_move,0,1);
        }
        else
        {
            if (mode==1)
            {
                set_attacking_move_type();
            }
            bank_target=get_target_of_move(current_move,0,0);
        }
        if(!get_bank_side(bank_attacker))
        {
            battle_trace.user_team_move = current_move;
        }
        else
        {
            battle_trace.ai_team_move = current_move;
        }
        battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
        battle_state_mode=0xA;
        if (current_move == last_used_moves[bank_attacker])
        {
            if (new_battlestruct->bank_affecting[bank_attacker].same_move_used < 5)
                new_battlestruct->bank_affecting[bank_attacker].same_move_used++;
        }
        else
            new_battlestruct->bank_affecting[bank_attacker].same_move_used = 0;

        u8 move_target = move_table[current_move].target;
        if ((battle_flags.double_battle && !is_bank_present(bank_target)) || (bank_attacker == bank_target && move_target != move_target_user && move_target != 12 && move_target != 2)) //fix correct targeting
            bank_target = get_target_of_move(current_move, 0, 0);

        if (find_move_in_table(current_move, &moveshitting_onair[0]))
            hitmarker |= HITMARKER_IGNORE_ON_AIR;
        else if (find_move_in_table(current_move, &moveshitting_underground[0]))
            hitmarker |= HITMERKER_IGNORE_UNDERGROUND;
        else if (find_move_in_table(current_move, &moveshitting_underwater[0]))
            hitmarker |= HITMARKER_IGNORE_UNDERWATER;
        if (battle_participants[bank_attacker].ability_id == ABILITY_STANCE_CHANGE && !battle_participants[bank_attacker].status2.transformed)
        {
            u16* species = &battle_participants[bank_attacker].species;
            u8 change = 0;
            if (*species == POKE_AEGISLASH_BLADE && current_move == MOVE_KINGS_SHIELD)
            {
                *species = POKE_AEGISLASH_SHIELD;
                change = 1;
            }
            else if (*species == POKE_AEGISLASH_SHIELD && DAMAGING_MOVE(current_move))
            {
                *species = POKE_AEGISLASH_BLADE;
                change = 1;
            }
            if (change)
            {
                battle_scripting.active_bank = active_bank = bank_attacker;
                bb2_setattributes_in_battle(0, REQUEST_SPECIES_BATTLE, 0, 2, species);
                mark_buffer_bank_for_execution(active_bank);
                bs_push_current(&aegislash_change_bs);
            }
        }
    }
    else
        battle_state_mode = 0xC;
}

s8 get_bracket_alteration_factor(u8 bank, u8 item_effect);

void set_focus_charge(void)
{
    for(u8 i=0; i<4; i++)
    {
        if(menu_choice_pbs[i]==0 && chosen_move_by_banks[i]==MOVE_FOCUS_PUNCH && !battle_participants[i].status.flags.sleep
            && !(disable_structs[i].truant_counter & 1) && !(protect_structs[i].flag0_onlystruggle))
        {
            status3[i].focus_punch_charge = 1;
        }
    }
}

void bc_preattacks(void)
{
    u8 play_script=0;
    u8 *count = &(battle_stuff_ptr->pre_attacks_bank_counter);
    if(!(hitmarker&HITMARKER_FLEE))
    {
        reset_indicators_height();
        while(*count<no_of_all_banks)
        {
            bank_attacker=*count;
            (*count)++;
            if(menu_choice_pbs[bank_attacker]==0)
            {
                u8 item_effect=get_item_effect(bank_attacker,1);
                if(get_bracket_alteration_factor(bank_attacker,item_effect) == 1)
                {
                    if(item_effect==ITEM_EFFECT_QUICKCLAW)
                    {
                        call_bc_move_exec(BS_QUICKCLAW);
                    }
                    else if(item_effect==ITEM_EFFECT_CUSTAPBERRY)
                    {
                        call_bc_move_exec(BS_CUSTAPBERRY);
                        setup_berry_consume_buffers(bank_attacker);
                    }
                    play_script=1;
                    last_used_item=battle_participants[bank_attacker].held_item;
                    break;
                }
            }
        }
    }
    if(!play_script)
    {
        set_focus_charge();
        clear_atk_up_if_hit_flag_unless_enraged();
        current_move_turn=0;
        battle_state_mode=battle_state_mode_first_assigned;
        dynamic_base_power=0;
        battle_stuff_ptr->dynamic_move_type=0;
        b_c=&bc_bs_executer;
        battle_communication_struct.move_effect=0;
        battle_communication_struct.field4=0;
        battle_scripting.field16=0;
        battle_resources->battlescript_stack->stack_height=0;
    }
}
