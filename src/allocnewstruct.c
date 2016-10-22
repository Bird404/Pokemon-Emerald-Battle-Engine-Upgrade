#include "defines.h"

void revert_mega_to_normalform(u8 teamID, u8 opponent_side);

void alloc_new_struct()
{
    battle_stuff_ptr = (struct battle_stuff*) malloc_and_clear(0x2A4);
    new_battlestruct = (struct new_battle_struct*) malloc_and_clear(sizeof(struct new_battle_struct));
    for (u8 i = 0; i < 4; i++)
    {
        new_battlestruct->bank_affecting[i].type3 = TYPE_EGG;
    }
}

void free_new_struct()
{
    //revert player's megas to normal form
    for (u8 i = 0; i < 6; i++)
    {
        revert_mega_to_normalform(i, 0);
    }
    free(battle_stuff_ptr);
    free(new_battlestruct);
}
