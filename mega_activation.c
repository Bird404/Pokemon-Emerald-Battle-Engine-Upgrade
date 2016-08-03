#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"
#include "static_references.h"

u8 can_set_mega_trigger(u8 bank)
{
    struct mega_flags *trigger = &(new_battlestruct.ptr->mega_trigger[bank]);
    return (!(trigger->stone_mega) && !(trigger->wish_mega) && !(trigger->transformed));
}

void clear_mega_triggers(u8 bank)
{
    struct mega_flags *trigger = &(new_battlestruct.ptr->mega_trigger[bank]);
    (trigger->stone_mega)=0;
    (trigger->wish_mega)=0;
    //(*trigger.transformed)=0;
}

u8 check_mega_conditions_and_set_triggers(u8 bank)
{
    struct mega_flags *trigger = &(new_battlestruct.ptr->mega_trigger[bank]);
    // add mega stone condition here
    (trigger->stone_mega)=1;
    return 1;
}

u8 is_multi_battle()
{
    // add multi battle_check here
    return 0;
}

void set_mega_triggers_for_user_team(u8 bank)
{
    if(can_set_mega_trigger(0) && (is_multi_battle() || can_set_mega_trigger(2)))
    {
        check_mega_conditions_and_set_triggers(bank);
        play_sound(5);
    }
}


