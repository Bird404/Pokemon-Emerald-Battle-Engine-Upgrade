#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"
#include "static_references.h"

u16 get_mega_species(u16 species);

void clear_mega_triggers(u8 bank)
{
    if(bank==0)
        new_battlestruct.ptr->mega_related.user_trigger=0;
    else if(bank==2)
        new_battlestruct.ptr->mega_related.ally_trigger=0;
}

void check_mega_conditions_and_set_triggers(u8 bank)
{
    // add mega stone condition here
    if(bank==0)
        new_battlestruct.ptr->mega_related.user_trigger=1;
    else if(bank==2)
        new_battlestruct.ptr->mega_related.ally_trigger=1;
}

u8 is_multi_battle()
{
    // add multi battle_check here
    return 0;
}

u8 check_megastone(u8 bank)
{
    u16 mega_species = get_mega_species(battle_participants[bank].poke_species);
    if (get_item_effect(bank, 0) == ITEM_EFFECT_MEGASTONE && mega_species && get_item_lastword(battle_participants[bank].held_item) == mega_species)
        return 1;
    return 0;
}

u8 can_set_mega_trigger(u8 bank)
{
    struct mega_related* mega=&new_battlestruct.ptr->mega_related;
    u8 res=0;
    if(bank==0 && !(mega->user_trigger) &&
       ((is_multi_battle() && !(mega->evo_happened_pbs&0x1)) || !(mega->evo_happened_pbs&0x5)))
    {
        res=1;
    }
    else if(bank==2 && !(mega->user_trigger) && !(mega->ally_trigger) && !(mega->evo_happened_pbs&0x5))
    {
        res=1;
    }
    return (res && check_megastone(bank) && checkitem(KEYSTONE, 1));
}

void set_mega_triggers_for_user_team(u8 bank)
{
    if(can_set_mega_trigger(bank))
    {
        check_mega_conditions_and_set_triggers(bank);
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
    for (u8 i = 0; i < NUM_OF_EVOS; i++)
    {
        if (evolution_table[mega_current_species].evos[i].method == 0xFF)
        {
            can_revert = 1;
            species_to_revert = evolution_table[mega_current_species].evos[i].poke;
        }
    }
    if (can_revert)
    {
        set_attributes(poke_address, ATTR_SPECIES, &species_to_revert);
        calculate_stats_pokekmon(poke_address);
    }
    return;
}

