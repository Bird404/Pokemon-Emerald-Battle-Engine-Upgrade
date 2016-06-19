#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "static_resources.h"
#include "new_battle_struct.h"

u16 get_speed(u8 bank);
u8 percent_chance(u8 percent);
u32 two_options_rand(u32 option1, u32 option2);

u8 check_ability(u8 bank, u8 ability)
{
    if (has_ability_effect(bank, 0, 1) && battle_participants[bank].ability_id == ability)
        return 1;
    return 0;
}

s8 get_priority(u16 move, u8 bank)
{
    s8 priority = move_table[move].priority;
    if (check_ability(bank, ABILITY_GALE_WINGS) && move_table[move].type == TYPE_FLYING)
        priority++;
    else if (check_ability(bank, ABILITY_PRANKSTER) && move_table[move].split == 2)
        priority++;
    return priority;
}

u8 get_first_to_strike(u8 bank1, u8 bank2, u8 ignore_priority)
{
    u16 speed1 = get_speed(bank1);
    u16 speed2 = get_speed(bank2);
    s8 priority1 = 0;
    s8 priority2 = 0;
    u8 faster_bank;

    if (new_battlestruct.ptr->bank_affecting[bank1].quashed)
        return 1;
    else if (new_battlestruct.ptr->bank_affecting[bank2].quashed)
        return 0;
    else if (!ignore_priority)
    {
        u8 move1 = battle_participants[bank1].moves[battle_stuff_ptr.ptr->chosen_move_position[bank1]];
        u8 move2 = battle_participants[bank2].moves[battle_stuff_ptr.ptr->chosen_move_position[bank2]];
        priority1 = get_priority(move1, bank1);
        priority2 = get_priority(move2, bank2);
    }
    if (priority1 > priority2)
        faster_bank = bank1;
    else if (priority2 > priority1)
        faster_bank = bank2;
    else //priorities are equal; quick claw moves first
    {
        u8 item1 = get_item_effect(bank1, 1);
        u8 item2 = get_item_effect(bank2, 1);
        u16 quickclaw1 = 0;
        u16 quickclaw2 = 0;
        if (item1 == ITEM_EFFECT_QUICKCLAW && percent_chance(20))
            quickclaw1 = rng();
        if (item2 == ITEM_EFFECT_QUICKCLAW && percent_chance(20))
            quickclaw2 = rng();
        if (quickclaw1 > quickclaw2)
            faster_bank = bank1;
        else if (quickclaw2 > quickclaw1)
            faster_bank = bank2;
        else //lagging tail moves last
        {
            if (item1 == ITEM_EFFECT_LAGGINGTAIL)
                quickclaw1 = rng();
            if (item2 == ITEM_EFFECT_LAGGINGTAIL)
                quickclaw2 = rng();
            if (quickclaw1 > quickclaw2)
                faster_bank = bank2;
            else if (quickclaw2 > quickclaw1)
                faster_bank = bank1;
            else //stall moves last
            {
                if (check_ability(bank1, ABILITY_STALL))
                    quickclaw1 = speed1;
                if (check_ability(bank2, ABILITY_STALL))
                    quickclaw2 = speed2;
                if (quickclaw1 > quickclaw2)
                    faster_bank = bank2;
                else if (quickclaw2 > quickclaw1)
                    faster_bank = bank1;
                else
                { //faster moves first unless trick room is active
                    if (new_battlestruct.ptr->field_affecting.trick_room) //swapping speeds will do the job
                    {
                        u16 placeholder = speed1;
                        speed1 = speed2;
                        speed2 = placeholder;
                    }
                    if (speed1 > speed2)
                        faster_bank = bank1;
                    else if (speed2 > speed1)
                        faster_bank = bank2;
                    else //speed are equal
                    {
                        faster_bank = two_options_rand(bank1, bank2);
                    }
                }
            }
        }
    }
    if (faster_bank == bank1)
        return 0;
    else
        return 1;
}
