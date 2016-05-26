#ifndef VANILLA_FUNCTIONS
#define VANILLA_FUNCTIONS

#include "types.h"
#include "battle_structs.h"

u8 get_item_x12_battle_function(u16 item_id);
u8 get_item_quality(u16 item_id);
void execute_battle_script(void* ptr_to_battlescript);
void record_usage_of_ability(u8 bank, u8 ability);
u8 castform_switch(u8 bank);
u8 is_bank_from_opponent_side(u8 bank);
void* display_string_in_battle(void*);
u8 read_byte(void*);
u16 rng();
void damage_modulate_by_type_effectivity(u8 effect);
void prepare_status_animation(u8 buffer, u8 unkown, u32 status);
void mark_buffer_bank_for_execution(u8 bank);
u8 get_item_pocket_id(u16 itemID);
void* strcpy_xFF_terminated_0(void* destination, void* text_to_copy);
void prepare_setattributes_in_battle(u8 buffer, u8 data_request, u8 unkown, u8 data_to_add, void* ptr_to_attribute);
void battlescript_push();
void battlescript_custom_push(void* ptr_to_push);
u8 gender_from_pid(u16 species, u32 PID);
u8 get_battle_side(u8 bank);
u8 does_protect_affect_move(u16 move);
u8 itemid_to_berryid(u16 itemID);
u16 species_to_national_dex(u16 species);
u16 get_height_or_weight(u16 national_dex_index, u8 which_one);
u8 get_bank_turn_order(u8 bank);
u8 count_alive_pokes_on_side(u8 side);

u32 __udivsi3(u32 numerator, u32 denumerator);
u32 __umodsi3(u32 numerator, u32 denumerator);
u32 bits_table[32];

//not really a vanilla function but w/e
u8 truant_hook(u8 truant_value);

#endif /* VANILLA_FUNCTIONS */
