#include "battle_structs.h"
#include "battle_locations.h"
#include "vanilla_functions.h"
#include "types.h"
#include "new_battle_struct.h"
#include "defines.h"
#include "megaimages/indicators.h"
#include "megaimages/mega_trigger.h"

//resource gfx_healthbar = {0x083EF524, 0x80, 0x1234};
struct image_resource gfx_indicator = {indicatorsTiles, 0x80, 0x1234};
struct image_resource pal_indicator = {indicatorsPal, 0x1234};
struct image_resource gfx_trigger = {mega_triggerTiles, 0x1000, 0x1235};
struct image_resource gfx_trigger_dbl = {mega_triggerTilesDbl, 0x1000, 0x1235};
struct image_resource pal_trigger = {mega_triggerPal, 0x1235};
struct image_resource pal_trigger_dbl = {mega_triggerPalDbl, 0x1235};
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

struct template template_trigger = {0x1235, 0x1235, &mega_trigger, (struct frame **)0x82EC69C, &empty, (struct rotscale_frame**)0x82EC6A8,
                                        healthbar_trigger_callback};


u8 is_in_triggering_state(u8 bank);

u8 is_multi_battle();

/* Declare the colors the trigger button ignores */
u16 ignored_cols[TRIGGER_NUM_IGNORED_COLORS] = {0x2147, 0x424F, 0x31AA, 0x00E4};

u8 ignored_trigger_color(u16 color) {
  u8 i;
  for (i = 0; i < TRIGGER_NUM_IGNORED_COLORS; ++i) {
    if (ignored_cols[i] == color)
        return 1;
  }
  return 0;
}

u16 calcEnabled(u16 clra)
{
    u16 clrb = 0x7FFF;

    u32 currentAlpha  = 20;

    u32 rbmask= ((0x1F)|(0x1F << 10)), gmask= 0x1F << 5;
    u32 rbhalf= 0x4010, ghalf= 0x0200;

    // Red and blue
    u32 parta = clra & rbmask;
    u32 partb = clrb & rbmask;
    u32 part = (partb-parta) * (32 - ((currentAlpha < 0x100) ? currentAlpha : currentAlpha >> 12)) + parta*32 + rbhalf;
    u16 clr = (part >> 5) & rbmask;

    // Green
    parta = clra & gmask;
    partb = clrb & gmask;
    part = (partb-parta) * (32 - ((currentAlpha < 0x100) ? currentAlpha : currentAlpha >> 12)) + parta*32 + ghalf;
    clr |= (part >> 5) & gmask;

    return clr;
}

void healthbar_trigger_callback(struct object *self)
{
    switch(self->private[ANIM_STATE])
    {
    case HIDE:
        self->pos1.x=-32;
        self->pos1.y=0;
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

    switch(self->private[PALLET_STATE])
    {
    case LIGHT_UP_TRIGGER:
    {
        struct palette* pal = &palette_obj_faded[gpu_pal_tags_index_of(0x2345)];
        if(battle_flags.double_battle)
        {
            for(u8 i = 1; i < 16; i++)
            {
                if (ignored_trigger_color(mega_triggerPalDbl[i]))
                    continue;
                pal->c[i] = calcEnabled(mega_triggerPalDbl[i]);
            }
        }
        else
        {
            for(u8 i = 1; i < 16; i++)
            {
                if (ignored_trigger_color(mega_triggerPal[i]))
                    continue;
                pal->c[i] = calcEnabled(mega_triggerPal[i]);
            }
        }
        self->private[PALLET_STATE]=TRIGGER_ON;
        break;
    }
    case REVERT_COLORS:
    {
        struct palette* pal = &palette_obj_faded[gpu_pal_tags_index_of(0x2345)];
        if(battle_flags.double_battle)
        {
            for(u8 i = 1; i < 16; i++)
            {
                pal->c[i] = mega_triggerPalDbl[i];
            }
        }
        else
        {
            for(u8 i = 1; i < 16; i++)
            {
                pal->c[i] = mega_triggerPal[i];
            }
        }
        self->private[PALLET_STATE]=REGULAR;
        break;
    }
    case REGULAR:
    case TRIGGER_ON:
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
    {
        objects[trigger_id].private[ANIM_STATE]=SLIDE_IN;
    }
    if(objects[trigger_id].private[ANIM_STATE]==DISABLED ||
       objects[trigger_id].private[ANIM_STATE]==HIDDEN || objects[trigger_id].private[RELATIVE_X]==0)
    {
        can_b_button_work=1;
    }
    return can_b_button_work;
}

void healthbar_indicator_callback(struct object *self)
{
    if(!self->private[DISABLED_INDICATOR])
    {
        u8 bank=self->private[0];
        struct object healthbox = objects[healthbox_obj_id_pbs[bank]];

        if((healthbox.invisible) || ((bank&1) && !(new_battlestruct.ptr->mega_related.ai_party_mega_check&bits_table[battle_team_id_by_side[bank]]))
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
        self->pos2.x=healthbox.pos2.x;
        self->pos1.y=healthbox.pos1.y-5;
        // Mirror healthbox priority
        u8 priority = ((healthbox.final_oam.attr2 >> 10) & 3);
        self->final_oam.attr2 = (self->final_oam.attr2 & ~0xC00) | (priority << 10);
    }
}

void dp11_objects_pingpong(struct object *parent_object)
{
    u8 child_object_id=parent_object->private[3];
    s16 pong=get_pingpong((s16)parent_object->private[0],(s16)parent_object->private[2]);
    u16 ychange=parent_object->private[2]+pong;
    objects[child_object_id].pos2.y=ychange;
    if(child_object_id==healthbox_obj_id_pbs[0])
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
    else if(child_object_id==healthbox_obj_id_pbs[2])
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
    else if(child_object_id==healthbox_obj_id_pbs[1])
    {
        u8 indi_id=new_battlestruct.ptr->mega_related.indicator_id_pbs[1];
        if(!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y=ychange;
        }
    }
    else if(child_object_id==healthbox_obj_id_pbs[3])
    {
        u8 indi_id=new_battlestruct.ptr->mega_related.indicator_id_pbs[3];
        if(!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y=ychange;
        }
    }
    parent_object->private[0]=(parent_object->private[0]+parent_object->private[1])&0xFF;
}

void obj_delete_and_free_tiles(struct object *parent_object);

void healthbar_shake(struct object *parent_object)
{
    u8 child_object_id=parent_object->private[1];
    u16 ychange = parent_object->private[0];
    objects[child_object_id].pos2.y=ychange;
    parent_object->private[0] = -parent_object->private[0];
    u16 *reps = &parent_object->private[2];
    bool is_hbar=true;
    struct mega_related* mega = &new_battlestruct.ptr->mega_related;
    struct object *indi_obj;

    if (child_object_id==healthbox_obj_id_pbs[0])
    {
        indi_obj=&objects[mega->indicator_id_pbs[0]];
    }
    else if (child_object_id==healthbox_obj_id_pbs[1])
    {
        indi_obj=&objects[mega->indicator_id_pbs[1]];
    }
    else if (child_object_id==healthbox_obj_id_pbs[2])
    {
        indi_obj=&objects[mega->indicator_id_pbs[2]];
    }
    else if (child_object_id==healthbox_obj_id_pbs[3])
    {
        indi_obj=&objects[mega->indicator_id_pbs[3]];
    }
    else
    {
        is_hbar=false;
    }

    if(is_hbar)
    {
        is_hbar=(is_hbar)&&(!indi_obj->private[DISABLED_INDICATOR]);
    }
    if(is_hbar)
    {
        indi_obj->pos2.y=ychange;
    }
    (*reps)++;
    if(*reps==0x15)
    {
        if(is_hbar)
        {
            indi_obj->pos2.x=0;
            indi_obj->pos2.y=0;
        }
        objects[child_object_id].pos2.x=0;
        objects[child_object_id].pos2.y=0;
        obj_delete_and_free_tiles(parent_object);
    }
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
        objid = template_instanciate_forward_search(&template_indicator, 1, 0, 1);
      objects[objid].private[0] = bank;
      new_battlestruct.ptr->mega_related.indicator_id_pbs[bank]=objid;
    }


    objid=template_instanciate_forward_search(&template_trigger, 10, 0, 1);
    new_battlestruct.ptr->mega_related.trigger_id=objid;


    }
}

