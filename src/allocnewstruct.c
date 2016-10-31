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

void free_new_struct()
{
    //revert forms to default ones
    for (u8 i = 0; i < 6; i++)
    {
        revert_form_change(1, i, 0, &party_player[i]);
    }
    free(battle_stuff_ptr);
    free(new_battlestruct);
}
