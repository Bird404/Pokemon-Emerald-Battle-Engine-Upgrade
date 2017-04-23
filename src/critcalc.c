#include "defines.h"
#include "static_references.h"

u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 has_ability_effect(u8 bank, u8 mold_breaker, u8 gastro);
bool check_ability(u8 bank, u8 ability);

void critcalc_cmd4(void)
{
    u8 crit_chance = 0;
    crit_loc = 1;
    u8 atk_ability = battle_participants[bank_target].ability_id;
    if (!(has_ability_effect(bank_target, 1, 1) && (atk_ability == ABILITY_SHELL_ARMOR || atk_ability == ABILITY_BATTLE_ARMOR))
         && !status3[bank_attacker].atk_cant_crt && !battle_flags.wally && !(battle_flags.save_birch && is_bank_from_opponent_side(bank_attacker))
        && !new_battlestruct->side_affecting[is_bank_from_opponent_side(bank_target)].lucky_chant)
    {
        if (current_move == MOVE_FROST_BREATH || current_move == MOVE_STORM_THROW)
            crit_loc = 2;
        else
        {
            if (battle_participants[bank_attacker].status2.focus_energy)
                crit_chance += 2;
            if (move_table[current_move].move_flags.flags.raised_crit_ratio)
                crit_chance++;
            if (check_ability(bank_attacker, ABILITY_SUPER_LUCK))
                crit_chance++;
            switch (get_item_effect(bank_attacker, 1))
            {
            case ITEM_EFFECT_SCOPELENS:
                crit_chance++;
                break;
            case ITEM_EFFECT_STICK:
                if (battle_participants[bank_attacker].poke_species == POKE_FARFETCHED)
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
                const static u16 crit_table[] = {4096, 8192, 32768};
                if (rng() < crit_table[crit_chance])
                    crit_loc = 2;
            }
        }
    }
    battlescripts_curr_instruction++;
}
