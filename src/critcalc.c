#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "new_battle_struct.h"

extern struct move_info move_table[1024];

u16 crit_table[] = {4096, 8192, 32768};

void critcalc_cmd4()
{
    u8 crit_chance = 0;
    crit_loc = 1;
    if (!(has_ability_effect(bank_target, 1, 1) && (battle_participants[bank_target].ability_id == ABILITY_SHELL_ARMOR || battle_participants[bank_target].ability_id == ABILITY_BATTLE_ARMOR)))
    {
        if (current_move == MOVE_FROST_BREATH || current_move == MOVE_STORM_THROW)
            crit_loc = 2;
        else
        {
            if (!(new_battlestruct.ptr->side_affecting[is_bank_from_opponent_side(bank_target)].lucky_chant || status3[bank_target].unkown_no_crit))
            {
                if (battle_participants[bank_attacker].status2.focus_energy)
                    crit_chance += 2;
                if (move_table[current_move].move_flags.flags.raised_crit_ratio)
                    crit_chance++;
                if (has_ability_effect(bank_attacker, 0, 1) && battle_participants[bank_attacker].ability_id == ABILITY_SUPER_LUCK)
                    crit_chance++;
                switch (get_item_effect(bank_attacker, 1))
                {
                case ITEM_EFFECT_SCOPELENS:
                    crit_chance++;
                    break;
                case ITEM_EFFECT_STICK:
                    if (battle_participants[bank_attacker].poke_species == POKE_FARFETCHD)
                        crit_chance += 2;
                    break;
                case ITEM_EFFECT_LUCKYPUNCH:
                    if (battle_participants[bank_attacker].poke_species == POKE_CHANSEY)
                        crit_chance += 2;
                    break;
                }
                if (crit_chance >= 3)
                    crit_loc = 2;
                else
                {
                    if (rng() < crit_table[crit_chance])
                        crit_loc = 2;
                }
            }
        }
    }
    battlescripts_curr_instruction++;
    return;
}
