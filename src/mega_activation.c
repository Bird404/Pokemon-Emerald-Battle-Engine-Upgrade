#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"
#include "static_references.h"

void reset_indicators_height_except_bank(u8  bank)
{
    struct mega_related* mega = &new_battlestruct.ptr->mega_related;
    for(u8 i = 0; i<no_of_all_banks ;i++)
    {
        if(i!=bank)
        {
            objects[mega->indicator_id_pbs[i]].pos2.y=0;
        }
    }
}

void clear_mega_triggers(u8 bank)
{
    struct object *trigger=&objects[new_battlestruct.ptr->mega_related.trigger_id];
    if(trigger->private[PALLET_STATE]==TRIGGER_ON)
    {
        trigger->private[PALLET_STATE]=REVERT_COLORS;
    }
    reset_indicators_height_except_bank(bank);
    if(bank==0)
        new_battlestruct.ptr->mega_related.user_trigger=0;
    else if(bank==2)
        new_battlestruct.ptr->mega_related.ally_trigger=0;
}

void set_mega_triggers(u8 bank,u8 set_mode)
{
    if(bank==0)
        new_battlestruct.ptr->mega_related.user_trigger=set_mode;
    else if(bank==2)
        new_battlestruct.ptr->mega_related.ally_trigger=set_mode;
}

u8 is_multi_battle()
{
    return 0;
}

u32 get_item_extra_param(u16 item)
{
    struct item_data *item_set= (void *) (item_data_ptr_ptr);
    return item_set->items[item].extra_param;
}

u16 get_mega_species(u8 bank, u8 chosen_method)
{
    u16 species = battle_participants[bank].poke_species;
    u16 target_species=0;
    struct evolution_data *evolution_table= (void *)(evo_table_ptr_ptr);
    for (u8 i = 0; i < NUM_OF_EVOS; i++)
    {
        u8 method = evolution_table->poke_evolutions[species].evos[i].method;
        if (method == chosen_method)
        {
            switch(method)
            {
            case 0xFB: // regular mega
                {
                    if(get_item_effect(bank, 0) == ITEM_EFFECT_MEGASTONE)
                    {
                        u16 stone_target_species = (u16) get_item_extra_param(battle_participants[bank].held_item);
                        if(evolution_table->poke_evolutions[species].evos[i].poke==stone_target_species)
                        {
                            target_species = stone_target_species;
                        }
                    }
                }
                break;
            case 0xFD: //primal
                target_species = evolution_table->poke_evolutions[species].evos[i].poke;
                break;
            case 0xFC: //fervent wish mega
                {
                    u8 fervent_move = evolution_table->poke_evolutions[species].evos[i].paramter;
                    if (fervent_move)
                    {
                        for(u8 j=0; j<4; j++)
                        {
                            if(battle_participants[bank].moves[j]==fervent_move)
                            {
                                target_species = evolution_table->poke_evolutions[species].evos[i].poke;
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
        if(target_species)
            break;
    }
    return target_species;
}

u8 can_set_mega_trigger(u8 bank)
{
    struct mega_related* mega=&new_battlestruct.ptr->mega_related;
    bool res=0;
    int mega_mode=0;
    if(bank==0 && !(mega->user_trigger) &&
       ((is_multi_battle() && !(mega->evo_happened_pbs&0x1)) || !(mega->evo_happened_pbs&0x5)))
    {
        res=true;
    }
    else if(bank==2 && !(mega->user_trigger) && !(mega->ally_trigger) && !(mega->evo_happened_pbs&0x5))
    {
        res=true;
    }
    if(res &&/*checkitem(KEYSTONE, 1) &&*/ (get_mega_species(bank,0xFB) || get_mega_species(bank,0xFC)))
    {
        if (get_mega_species(bank,0xFB))
        {
            mega_mode=1;
        }
        else if (get_mega_species(bank,0xFC))
        {
            mega_mode=2;
        }
    }
    return mega_mode;
}

void set_mega_triggers_for_user_team(u8 bank)
{
    u8 set_mode=can_set_mega_trigger(bank);
    if(set_mode)
    {
        set_mega_triggers(bank,set_mode);
        objects[new_battlestruct.ptr->mega_related.trigger_id].private[PALLET_STATE]=LIGHT_UP_TRIGGER;
        play_sound(2);
    }
}


void revert_mega_to_normalform(u8 teamID, u8 opponent_side)
{
    struct pokemon* poke_address;
    if (opponent_side)
        poke_address = &party_opponent[teamID];
    else
        poke_address = &party_player[teamID];
    u16 mega_current_species = get_attributes(poke_address, ATTR_SPECIES, 0);
    u8 can_revert = 0;
    u16 species_to_revert = 0;

    struct evolution_data *evolution_table= (void *)(evo_table_ptr_ptr);
    for (u8 i = 0; i < NUM_OF_EVOS; i++)
    {
        if (evolution_table->poke_evolutions[mega_current_species].evos[i].method == 0xFF)
        {
            can_revert = 1;
            species_to_revert = evolution_table->poke_evolutions[mega_current_species].evos[i].poke;
        }
    }
    if (can_revert && species_to_revert)
    {
        set_attributes(poke_address, ATTR_SPECIES, &species_to_revert);
        calculate_stats_pokekmon(poke_address);
    }
    return;
}

