#include "defines.h"
#include "static_references.h"

void handle_outcome_trainerbattle(void)
{
    bool loss = 0;
    if (battle_outcome == OUTCOME_DRAW || battle_outcome == OUTCOME_LOSS) {loss = 1;}

    bool pyramid = is_in_battle_pyramid();
    bool frontier = frontier_sth();

    //lost in the battle frontier
    if (var_8015_trainer_opponent_A == 0x400 || (loss && (pyramid || frontier)))
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
    //lost normal battle
    else if (loss && !GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
        set_callback2(c2_whiteout);
    else //battle won or lost but the allow lose flag is set
    {
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
        if (!pyramid && !frontier)
        {
            rematch_trainer_flag_set();
            set_battled_trainers_flags();
        }
    }
}

void handle_outcome_rematchbattle(void)
{
    bool loss = 0;
    if (battle_outcome == OUTCOME_DRAW || battle_outcome == OUTCOME_LOSS) {loss = 1;}

    if (var_8015_trainer_opponent_A == 0x400)
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
    //won or lost but the custom flag is set
    else if (!loss || GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
    {
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
        rematch_trainer_flag_set();
        set_rematched_trainer_as_defeated();
    }
    //lost
    else
    {
        set_callback2(c2_whiteout);
    }
}

void battle_lost_set_script(void)
{
    battle_state_mode = 0;
    bool outcome_sth = battle_outcome & 0x80;
    battle_outcome &= 0x7F;
    if (!(battle_flags.link || battle_flags.flag_x2000000))
    {
        if (battle_flags.trainer && GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
            battlescripts_curr_instruction = &BS_CUSTOM_LOSS;
        else
            battlescripts_curr_instruction = (void*)(0x82DA96D);
    }
    else if (!(BATTLE_FRONTIER_BATTLE))
    {
        battle_text_buff1[0] = battle_outcome;
        bank_attacker = get_bank_by_player_ai(0);
        battlescripts_curr_instruction = (void*)(0x82DAA35);
    }
    else if (!outcome_sth)
    {
        battlescripts_curr_instruction = (void*)(0x82DAA0B);
    }
    else
    {
        battlescripts_curr_instruction = (void*)(0x82DB9C8);
        u8* byte = (u8*)(&(*sav2)) + 0xCA9;
        *byte |= 8;
    }
    battle_executed_routine = end_battle;
}
