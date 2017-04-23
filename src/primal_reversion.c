#include "defines.h"
#include "static_references.h"

#define ALPHA_REVERSION 1
#define OMEGA_REVERSION 2

u16 get_mega_species(u8 bank, u8 chosen_method);

u8 get_reversion_type(u8 bank, u16 target_species)
{
    u16 species = battle_participants[bank].poke_species;
    u8 reversion_type = 0;
    const struct evolution_sub* evos = GET_EVO_TABLE(species);
    for(u8 i=0; i<NUM_OF_EVOS; i++)
    {
        if (evos[i].method==0xFD && evos[i].poke==target_species)
        {
            reversion_type=evos[i].paramter;
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
            u8 objid = new_battlestruct->mega_related.indicator_id_pbs[bank];
            if(reversion_mode==ALPHA_REVERSION)
            {
                objects[objid].final_oam.attr2+=2;
                execute_battle_script(BS_ALPHA_PRIMAL);
            }
            else if(reversion_mode==OMEGA_REVERSION)
            {
                objects[objid].final_oam.attr2+=1;
                execute_battle_script(BS_OMEGA_PRIMAL);
            }
            struct pokemon* poke_address;
            if (banks_side == 1)
            {
                poke_address = &party_opponent[battle_team_id_by_side[bank]];
                new_battlestruct->mega_related.ai_party_mega_check|=bits_table[battle_team_id_by_side[bank]];
            }
            else
            {
                poke_address = &party_player[battle_team_id_by_side[bank]];
                new_battlestruct->mega_related.party_mega_check|=bits_table[battle_team_id_by_side[bank]];
            }
            objects[objid].private[PRIMAL_CHECK_COMPLETE]=true;
            set_attributes(poke_address, ATTR_SPECIES, &primal_species);
            calculate_stats_pokekmon(poke_address);
            bank_struct->atk = get_attributes(poke_address, ATTR_ATTACK, 0);
            bank_struct->def = get_attributes(poke_address, ATTR_DEFENCE, 0);
            bank_struct->spd = get_attributes(poke_address, ATTR_SPEED, 0);
            bank_struct->sp_atk = get_attributes(poke_address, ATTR_SPECIAL_ATTACK, 0);
            bank_struct->sp_def = get_attributes(poke_address, ATTR_SPECIAL_DEFENCE, 0);
            bank_struct->poke_species = primal_species;
            const struct poke_basestats* PokeStats = &((*basestat_table)[primal_species]);
            bank_struct->type1 = PokeStats->type1;
            bank_struct->type2 = PokeStats->type2;
            // The ability 1 and ability 2 of the primal species in the base stat table should both be set and
            // have the same value.
            bank_struct->ability_id = PokeStats->ability1;

            bank_struct->max_hp = get_attributes(poke_address, ATTR_TOTAL_HP, 0);
            bank_struct->current_hp = get_attributes(poke_address, ATTR_CURRENT_HP, 0);
            bank_struct->level = get_attributes(poke_address, ATTR_LEVEL, 0);

            new_battlestruct->various.active_bank = bank;
            bank_attacker = bank;

        }
    }
    return perform_reversion;
}
