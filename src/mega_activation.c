#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"
#include "static_references.h"

u16 get_mega_species(u16 species);

u8 can_set_mega_trigger(u8 bank)
{
    struct bank_affecting *trigger = &(new_battlestruct.ptr->bank_affecting[bank]);
    return (!(trigger->stone_mega) && !(trigger->wish_mega) && !(trigger->mega_transformed));
}

void clear_mega_triggers(u8 bank)
{
    struct bank_affecting *trigger = &(new_battlestruct.ptr->bank_affecting[bank]);
    (trigger->stone_mega)=0;
    (trigger->wish_mega)=0;
    //(*trigger.transformed)=0;
}

u8 check_mega_conditions_and_set_triggers(u8 bank)
{
    struct bank_affecting *trigger = &(new_battlestruct.ptr->bank_affecting[bank]);
    // add mega stone condition here
    (trigger->stone_mega)=1;
    return 1;
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

void set_mega_triggers_for_user_team(u8 bank)
{
    if(check_megastone(bank) && checkitem(KEYSTONE, 1) && can_set_mega_trigger(0) && (is_multi_battle() || can_set_mega_trigger(2)))
    {
        check_mega_conditions_and_set_triggers(bank);
        play_sound(5);
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
        new_battlestruct.ptr->side_affecting[opponent_side].mega_evolved = 0;
        set_attributes(poke_address, ATTR_SPECIES, &species_to_revert);
        calculate_stats_pokekmon(poke_address);
    }
    return;
}
