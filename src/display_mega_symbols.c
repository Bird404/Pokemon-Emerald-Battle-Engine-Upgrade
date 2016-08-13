#include "battle_structs.h"
#include "battle_locations.h"
#include "vanilla_functions.h"
#include "types.h"
#include "new_battle_struct.h"

#include "megaimages/indicators.h"
#include "megaimages/mega_trigger.h"

//resource gfx_healthbar = {0x083EF524, 0x80, 0x1234};
struct image_resource gfx_indicator = {indicatorsTiles, 0x80, 0x1234};
struct image_resource pal_indicator = {indicatorsPal, 0x1234};
struct image_resource gfx_trigger = {mega_triggerTiles, 0x1C00, 0x2345};
struct image_resource gfx_trigger_dbl = {mega_triggerTilesDbl, 0x1C00, 0x2345};
struct image_resource pal_trigger = {mega_triggerPal, 0x2345};
struct image_resource pal_trigger_dbl = {mega_triggerPalDbl, 0x2345};
// 083F6CBO - 32x32?

struct sprite mega_indicator = {0, 0x0, 0x0, 0x00, 0x0};
//sprite mega_icon = {0x0, 0x4000, 0x000, 0x0};
struct sprite mega_trigger = {0, 0x0, 0x8000, 0x800, 0};

u8 can_set_mega_trigger(u8 bank);
void healthbar_trigger_callback(struct object *self);
void healthbar_indicator_callback(struct object *self);

u32 empty=0x0;
struct template template_indicator = {0x1234, 0x1234, &mega_indicator, (struct frame **)0x82EC69C, (u32 *) &empty,
                                        (struct rotscale_frame**) 0x82EC6A8, healthbar_indicator_callback};

struct template template_trigger = {0x2345, 0x2345, &mega_trigger, (struct frame **)0x82EC69C, &empty, (struct rotscale_frame**)0x82EC6A8,
                                        healthbar_trigger_callback};


u8 is_in_triggering_state(u8 bank);
#define BANK_TO_ATTACH_TRIGGER 0

#define ANIM_STATE 1
#define HIDE 0
#define POS_BEHIND_HPBAR 1
#define SLIDE_OUT 2
#define SLIDE_IN 3
#define DISABLE 4
#define SLIDED_OUT 5
#define HIDDEN 6
#define DISABLED 7

#define PALLET_STATE 2

#define RELATIVE_X 3
#define BASE_X 4
#define SINGLES_HEALTHBOX_X 120
#define DBL_HB_0_X 121
#define DBL_HB_2_X 132
#define SINGLES_HEALTHBOX_Y 90
#define DBL_HB_0_Y 75
#define DBL_HB_2_Y 100

u8 is_multi_battle();

void healthbar_trigger_callback(struct object *self)
{
    switch(self->private[ANIM_STATE])
    {
    case HIDE:
        self->pos1.x=-32;
        self->pos1.y=0;
        if(!(new_battlestruct.ptr->mega_related.evo_happened_pbs&0x5) ||
           (is_multi_battle() && !(new_battlestruct.ptr->mega_related.evo_happened_pbs&0x1)))
            self->private[ANIM_STATE]=HIDDEN;
        break;

    case POS_BEHIND_HPBAR:
        self->private[RELATIVE_X]=16;
        if(!battle_flags.double_battle)
        {
            self->private[BASE_X]=SINGLES_HEALTHBOX_X;
            self->pos1.y=SINGLES_HEALTHBOX_Y;
        }
        else
        {
            if(self->private[BANK_TO_ATTACH_TRIGGER]==0)
            {
                self->private[BASE_X]=DBL_HB_0_X;
                self->pos1.y=DBL_HB_0_Y;
            }
            else
            {
                self->private[BASE_X]=DBL_HB_2_X;
                self->pos1.y=DBL_HB_2_Y;
            }
        }
        self->private[ANIM_STATE]=SLIDE_OUT;
        break;

    case SLIDE_OUT:
        {
            if(self->private[RELATIVE_X]>0)
            {
                self->pos1.x=self->private[BASE_X]+self->private[RELATIVE_X];
                self->private[RELATIVE_X]-=2;
            }
            else
            {
                self->private[ANIM_STATE]=SLIDED_OUT;
            }
        }
        break;

    case SLIDE_IN:
        {
            if(self->private[RELATIVE_X]<=16)
            {
                self->pos1.x=self->private[BASE_X]+self->private[RELATIVE_X];
                self->private[RELATIVE_X]+=2;
            }
            else
            {
                self->private[ANIM_STATE]=HIDE;
            }
        }
        break;

    case DISABLE:
        self->pos1.x=-32;
        self->pos1.y=0;
        self->private[ANIM_STATE]=DISABLED;
        break;
    case SLIDED_OUT:
    case HIDDEN:
    case DISABLED:
        break;
    }
}

u8 can_set_mega_trigger(u8 bank);

void position_trigger()
{
    u8 trigger_id=new_battlestruct.ptr->mega_related.trigger_id;
    if(objects[trigger_id].private[ANIM_STATE]==HIDDEN && can_set_mega_trigger(active_bank))
    {
        objects[trigger_id].private[BANK_TO_ATTACH_TRIGGER]=active_bank;
        objects[trigger_id].private[ANIM_STATE]=POS_BEHIND_HPBAR;
    }
}

void hide_trigger_on_pressing_A()
{
    u8 trigger_id=new_battlestruct.ptr->mega_related.trigger_id;
    if(objects[trigger_id].private[ANIM_STATE]==SLIDE_OUT || objects[trigger_id].private[ANIM_STATE]==SLIDED_OUT)
        objects[trigger_id].private[ANIM_STATE]=SLIDE_IN;
}

u8 hide_trigger()
{
    u8 trigger_id=new_battlestruct.ptr->mega_related.trigger_id;
    u8 can_b_button_work=0;
    if(objects[trigger_id].private[ANIM_STATE]==SLIDED_OUT)
        objects[trigger_id].private[ANIM_STATE]=SLIDE_IN;
    if(objects[trigger_id].private[ANIM_STATE]==HIDDEN || objects[trigger_id].private[RELATIVE_X]==0)
        can_b_button_work=1;
    return can_b_button_work;
}

#define DISABLED_INDICATOR 1
#define UNHIDE_INDICATOR 2
void healthbar_indicator_callback(struct object *self)
{
    if(!self->private[DISABLED_INDICATOR])
    {
        u8 bank=self->private[0];
        struct object healthbox = objects[healthbox_obj_id_pbs[bank]];
        u16 slide_dist=healthbox.pos2.x;
        if(slide_dist!=0)
        {
            self->private[UNHIDE_INDICATOR]=1;
        }
        if(!self->private[UNHIDE_INDICATOR] || ((bank&1) && !(new_battlestruct.ptr->mega_related.ai_party_mega_check&bits_table[battle_team_id_by_side[bank]]))
           || (!(bank&1) && !(new_battlestruct.ptr->mega_related.party_mega_check&bits_table[battle_team_id_by_side[bank]])))
        {
            self->pos1.x=-8;
            return;
        }
        if(battle_participants[bank].current_hp==0)
        {
            self->private[DISABLED_INDICATOR]=1; //Kill this indicator for the whole battle.
            self->pos1.x=-8;
            return;
        }

        if(bank&1)
        {
            self->pos1.x=healthbox.pos1.x+36;
        }
        else
        {
            self->pos1.x=healthbox.pos1.x+44;
        }
        self->pos2.x=slide_dist;

        self->pos1.y=healthbox.pos1.y-5;

        // Mirror healthbox priority
        u8 priority = ((healthbox.final_oam.attr2 >> 10) & 3);
        self->final_oam.attr2 = (self->final_oam.attr2 & ~0xC00) | (priority << 10);
    }
}

void dp11_objects_pingpong(struct object *param_object)
{
    u8 some_other_object_id=param_object->private[3];
    s16 pong=get_pingpong((s16)param_object->private[0],(s16)param_object->private[2]);
    u16 ychange=param_object->private[2]+pong;
    objects[some_other_object_id].pos2.y=ychange;
    if(some_other_object_id==healthbox_obj_id_pbs[0])
    {
        u8 trigger_id=new_battlestruct.ptr->mega_related.trigger_id;
        u8 indi_id=new_battlestruct.ptr->mega_related.indicator_id_pbs[0];
        if(objects[trigger_id].private[ANIM_STATE]!=DISABLED && objects[trigger_id].private[BANK_TO_ATTACH_TRIGGER]==0)
        {
            objects[trigger_id].pos2.y=ychange;
        }
        if(!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y=ychange;
        }
    }
    else if(some_other_object_id==healthbox_obj_id_pbs[2])
    {
        u8 trigger_id=new_battlestruct.ptr->mega_related.trigger_id;
        u8 indi_id=new_battlestruct.ptr->mega_related.indicator_id_pbs[2];
        if(objects[trigger_id].private[ANIM_STATE]!=DISABLED && objects[trigger_id].private[BANK_TO_ATTACH_TRIGGER]==2)
        {
            objects[trigger_id].pos2.y=ychange;
        }
        if(!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y=ychange;
        }
    }
    param_object->private[0]=(param_object->private[0]+param_object->private[1])&0xFF;
}

void gpu_pal_obj_alloc_tag_and_apply(void *);
void gpu_tile_obj_decompress_alloc_tag_and_upload(void *);
u8 template_instanciate_forward_search(struct template *template, u16 x, u8 y, u8 derp);


void healthbar_load_graphics(u8 state)
{
  u8 objid;

  if (state == 2)
    {
    gpu_pal_obj_alloc_tag_and_apply(&pal_indicator);


    gpu_tile_obj_decompress_alloc_tag_and_upload(&gfx_indicator);
    if(battle_flags.double_battle)
    {
        gpu_pal_obj_alloc_tag_and_apply(&pal_trigger_dbl);
        gpu_tile_obj_decompress_alloc_tag_and_upload(&gfx_trigger_dbl);
    }
    else
    {
        gpu_pal_obj_alloc_tag_and_apply(&pal_trigger);
        gpu_tile_obj_decompress_alloc_tag_and_upload(&gfx_trigger);
    }


    // Create a Mega Indicator for every bank
    u8 bank;
    for (bank = 0; bank < no_of_all_banks; ++bank) {
        objid = template_instanciate_forward_search(&template_indicator, -32, 0, 1);
      objects[objid].private[0] = bank;
      new_battlestruct.ptr->mega_related.indicator_id_pbs[bank]=objid;
    }

    objid=template_instanciate_forward_search(&template_trigger, 140, 90, 1);
    new_battlestruct.ptr->mega_related.trigger_id=objid;
  }

}

