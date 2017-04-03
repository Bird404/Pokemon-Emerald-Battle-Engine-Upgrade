#include "defines.h"

void AnimTask_megaevo_swap_sprite(u8 taskID)
{
    struct task* curr_task = &tasks[taskID];
    u8 objID = objID_pbs_moveanimations[animation_bank_attacker];
    struct object* poke_obj = &objects[objID];
    u16* state_tracker = &curr_task->private[10];
    switch (*state_tracker)
    {
    case 0: //hide sprite
        curr_task->private[11] = poke_obj->pos1.x;
        poke_obj->pos1.x = -64;
        (*state_tracker)++;
        break;
    case 1: //refresh graphics
        battle_anim_refresh_graphics_maybe(animation_bank_attacker, 1, objID);
        (*state_tracker)++;
        break;
    case 2: //add a task
        poke_obj->invisible = 0;
        u8 added_task_id = task_add(sub_80A4980, 5);
        curr_task->private[1] = added_task_id;
        tasks[added_task_id].private[0] = 0;
        tasks[added_task_id].private[2] = animation_bank_attacker;
        (*state_tracker)++;
        break;
    case 3: //wait for added task
        if (!task_is_running(curr_task->private[1]))
            (*state_tracker)++;
        break;
    default: //restore position, update altitude
        poke_obj->pos1.x = curr_task->private[11];
        poke_update_altitude(animation_bank_attacker, battle_participants[animation_bank_attacker].poke_species);
        move_anim_task_del(taskID);
        break;
    }
}

void AnimTask_animate_pokemon(u8 taskID) //argument is bank
{
    u8 bank = animation_bank_attacker;
    if (anim_arguments[0] == 1) {bank = animation_bank_target;}
    u16* first_call = &tasks[taskID].private[0];
    struct object* poke_obj = &objects[objID_pbs_moveanimations[bank]];
    if (*first_call == 0)
    {
        task_set_priv_u32(taskID, 2, (u32) poke_obj->callback);
        u16 species = battle_participants[bank].poke_species;
        if (is_bank_from_opponent_side(bank))
            b_animate_opponent_poke(poke_obj, species, 0, 1);
        else
            b_animate_player_poke(poke_obj, species);
        *first_call = 1;
    }
    else
    {
        if (task_find_id_by_funcptr(task_do_poke_animation) == 0xFF &&
            task_find_id_by_funcptr(task_animate_poke_after_delay) == 0xFF)
        {
            poke_obj->callback = (void*)(task_get_priv_u32(taskID, 2));
            move_anim_task_del(taskID);
        }
    }
}
