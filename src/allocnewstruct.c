#include "defines.h"

void revert_form_change(u8 mega_revert, u8 teamID, u8 side, struct pokemon* poke);
u16 try_illusion_change(u8 bank, struct pokemon* poke);
struct pokemon* get_party_ptr(u8 bank);

void alloc_new_struct()
{
    battle_stuff_ptr = (struct battle_stuff*) malloc_and_clear(0x2A4);
    new_battlestruct = (struct new_battle_struct*) malloc_and_clear(sizeof(struct new_battle_struct));
    //apply Egg Type
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        new_battlestruct->bank_affecting[i].type3 = TYPE_EGG;
    }
}

void try_burmy_change(u8 id, struct pokemon* poke)
{
    if (new_battlestruct->various.sent_in_player & bits_table[id])
    {
        u16 species = get_attributes(poke, ATTR_SPECIES, 0);
        if (POKE_BURMY(species))
        {
            u16 to_change;
            if (battle_background >= 8)
                to_change = POKE_BURMY_TRASH;
            else if (battle_background == BACKGROUND_SAND || battle_background >= BACKGROUND_ROCK)
                to_change = POKE_BURMY_SAND;
            else
                to_change = POKE_BURMY_PLANT;
            if (species != to_change)
            {
                set_attributes(poke, ATTR_SPECIES, &to_change);
                calculate_stats_pokekmon(poke);
            }
        }
    }
    return;
}

void free_new_struct()
{
    //revert forms to default ones
    for (u8 i = 0; i < 6; i++)
    {
        struct pokemon* poke = &party_player[i];
        revert_form_change(1, i, 0, poke);
        revert_form_change(0, i, 0, poke);
        try_burmy_change(i, poke);
        #if STAT_RECALC == true
            calculate_stats_pokekmon(poke);
        #endif // STAT_RECALC
    }
    free(battle_stuff_ptr);
    free(new_battlestruct);
}
