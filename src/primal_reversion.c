#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "static_references.h"
#include "new_battle_struct.h"

u16 get_mega_species(u8 bank, u8 chosen_method);

u8 primal_reversion_script[] = {0x39, 0x20, 0x0, 0x45, 1, 0x1E, 0, 0, 0, 0, 0x3A, 0x83, 89, 0, 0x10, 0x10, 0x02, 0x12, 0x40, 0x0, 0x3F};

bool handle_primal_reversion(u8 bank)
{
    bool perform_reversion = false;
    u16 primal_species = get_mega_species(bank,0xFD);

    if(primal_species)
    {
        perform_reversion = true;
        struct battle_participant* bank_struct = &battle_participants[bank];
        u8 banks_side = is_bank_from_opponent_side(bank);
        struct pokemon* poke_address;
        if (banks_side == 1)
        {
            poke_address = &party_opponent[battle_team_id_by_side[bank]];
        }
        else
        {
            poke_address = &party_player[battle_team_id_by_side[bank]];
        }
        set_attributes(poke_address, ATTR_SPECIES, &primal_species);
        calculate_stats_pokekmon(poke_address);
        bank_struct->atk = get_attributes(poke_address, ATTR_ATTACK, 0);
        bank_struct->def = get_attributes(poke_address, ATTR_DEFENCE, 0);
        bank_struct->spd = get_attributes(poke_address, ATTR_SPEED, 0);
        bank_struct->sp_atk = get_attributes(poke_address, ATTR_SPECIAL_ATTACK, 0);
        bank_struct->sp_def = get_attributes(poke_address, ATTR_SPECIAL_DEFENCE, 0);
        bank_struct->poke_species = primal_species;
        struct basestat_data *pokemon_table = (void *)(poke_stat_table_ptr_ptr);
        bank_struct->type1 = pokemon_table->poke_stats[primal_species].type1;
        bank_struct->type2 = pokemon_table->poke_stats[primal_species].type2;
        // The ability 1 and ability 2 of the primal species in the base stat table should both be set and
        // have the same value.
        bank_struct->ability_id = pokemon_table->poke_stats[primal_species].ability1;

        bank_struct->max_hp = get_attributes(poke_address, ATTR_TOTAL_HP, 0);
        bank_struct->current_hp = get_attributes(poke_address, ATTR_CURRENT_HP, 0);
        bank_struct->level = get_attributes(poke_address, ATTR_LEVEL, 0);

        execute_battle_script(&primal_reversion_script);
    }
    return perform_reversion;
}
