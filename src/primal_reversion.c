#include "types.h"
#include "defines.h"
#include "battle_locations.h"
#include "battle_structs.h"
#include "vanilla_functions.h"
#include "static_references.h"
#include "new_battle_struct.h"

#define ALPHA_REVERSION 1
#define OMEGA_REVERSION 2

u16 get_mega_species(u8 bank, u8 chosen_method);

u8 alpha_primal_reversion_bs[] = {0x39, 0x20, 0x0, 0x45, 1, 0x1F, 0, 0, 0, 0, 0x3A, 0x83, 106, 0, 0x83, 89, 0, 0x10, 0x10, 0x02, 0x12, 0x40, 0x0, 0x3F};
u8 omega_primal_reversion_bs[] = {0x39, 0x20, 0x0, 0x45, 1, 0x20, 0, 0, 0, 0, 0x3A, 0x83, 106, 0, 0x83, 89, 0, 0x10, 0x10, 0x02, 0x12, 0x40, 0x0, 0x3F};

u8 get_reversion_type(u8 bank, u16 target_species)
{
    u16 species = battle_participants[bank].poke_species;
    u8 reversion_type = 0;
    struct evolution_data *evolution_table= (void *)(evo_table_ptr_ptr);
    for(u8 i=0; i<NUM_OF_EVOS; i++)
    {
        if (evolution_table->poke_evolutions[species].evos[i].method==0xFD && evolution_table->poke_evolutions[species].evos[i].poke==target_species)
        {
            reversion_type=evolution_table->poke_evolutions[species].evos[i].paramter;
            break;
        }
    }
    return reversion_type;
}

bool handle_primal_reversion(u8 bank)
{
    bool perform_reversion = false;
    u16 primal_species = get_mega_species(bank,0xFD);

    if(primal_species)
    {
        u8 reversion_mode=get_reversion_type(bank,primal_species);
        if(reversion_mode!=0)
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

            new_battlestruct.ptr->various.active_bank = bank;
            bank_attacker = bank;
            if(reversion_mode==ALPHA_REVERSION)
            {
                execute_battle_script(&alpha_primal_reversion_bs);
            }
            else if(reversion_mode==OMEGA_REVERSION)
            {
                execute_battle_script(&omega_primal_reversion_bs);
            }

        }
    }
    return perform_reversion;
}
