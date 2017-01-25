#include "defines.h"
#include "static_references.h"

u8 is_bank_present(u8 bank);
struct pokemon* get_party_ptr(u8 bank);
struct pokemon* get_bank_poke_ptr(u8 bank);
u8 is_poke_valid(struct pokemon* poke);
u8 count_party_pokemon(u8 bank);
void revert_form_change(u8 mega_revert, u8 teamID, u8 side, struct pokemon* poke);
u8 check_ability(u8 bank, u8 ability);
void copy_status_condition_text(u8 bank, u8 confusion);
void setup_berry_consume_buffers(u8 bank);
u16 get_item_extra_param(u16 item);
void b_load_sprite_player(struct pokemon* poke, u8 bank);

extern u8 ability_names_table[250][13];

bool load_weather_from_overworld()
{
    bool is_weather_loaded = false;
    if(true)
    {
        u8 ow_weather = get_overworld_weather();
        switch(ow_weather)
        {
        case 3:
        case 5:
        case 13:
            if(!battle_weather.flags.downpour && !battle_weather.flags.rain && !battle_weather.flags.permament_rain)
            {
                battle_weather.int_bw = (weather_permament_rain | weather_rain);
                battle_scripting.field10 = 0xA;
                is_weather_loaded = true;
            }
            break;
        case 8:
            if(!battle_weather.flags.permament_sandstorm && !battle_weather.flags.sandstorm)
            {
                battle_weather.int_bw = (weather_permament_sandstorm | weather_sandstorm);
                battle_scripting.field10 = 0xC;
                is_weather_loaded = true;
            }
            break;
        case 12:
            if(!battle_weather.flags.permament_sun && !battle_weather.flags.sun)
            {
                battle_weather.int_bw = (weather_permament_sun | weather_sun);
                battle_scripting.field10 = 0xB;
                is_weather_loaded = true;
            }
            break;
        }
        if(is_weather_loaded)
        {
            battle_scripting.active_bank = 0;
            battle_communication_struct.multistring_chooser = ow_weather;
            execute_battle_script((void *)0x82DACE7);
        }
    }
    return is_weather_loaded;
}

struct pokemon* get_poke_to_illusion_into(struct pokemon* poke, u8 bank)
{
    if (!new_battlestruct->bank_affecting[bank].illusion_on && !new_battlestruct->bank_affecting[bank].illusion_hit && get_poke_ability(poke) == ABILITY_ILLUSION)
    {
        u8 usable_pokemon = count_party_pokemon(bank);
        u8 min_to_have = 2;
        if (battle_flags.double_battle)
            min_to_have++;
        if (new_battlestruct->various.switch_in_cos_switch)
        {
            new_battlestruct->various.switch_in_cos_switch = 0;
            min_to_have++;
        }
        if (usable_pokemon >= min_to_have)
        {
            struct pokemon* partner = 0;
            u8 ally_bank = bank ^ 2;
            if (is_bank_present(ally_bank))
            {
                partner = get_bank_poke_ptr(ally_bank);
            }
            for (s8 i = 5; i >= 0; i--)
            {
                struct pokemon* masquerade_as = &get_party_ptr(bank)[i];
                if (poke != masquerade_as && poke != partner && is_poke_valid(masquerade_as) && get_attributes(masquerade_as, ATTR_CURRENT_HP, 0))
                {
                    return masquerade_as;
                }
            }
        }
    }
    return 0;
}

u8 try_illusion_change(struct pokemon* poke, u8 bank)
{
    struct pokemon* masquerade_as = get_poke_to_illusion_into(poke, bank);
    if (masquerade_as)
    {
        new_battlestruct->bank_affecting[bank].illusion_on = 1;
        battle_graphics.graphics_data->species_info[bank]->pal_change = 0;
        battle_graphics.graphics_data->species_info[bank]->transformed_species = get_attributes(masquerade_as, ATTR_SPECIES, 0);
        PiD_pbs[bank] = get_attributes(masquerade_as, ATTR_PID, 0);
        new_battlestruct->bank_affecting[bank].transform_tid = get_attributes(masquerade_as, ATTR_TID, 0);
        get_attributes(masquerade_as, ATTR_NAME, &new_battlestruct->bank_affecting[bank].illusion_nick);
        new_battlestruct->bank_affecting[bank].illusion_ball = get_attributes(masquerade_as, ATTR_POKEBALL, 0);
        battle_participants[bank].status2.transformed = 1;
        if (bank == 2) //for some reason it doesn't load correctly this sprite
            b_load_sprite_player(poke, bank);
        return 1;
    }
    return 0;
}

u16 get_transform_species(u8 bank)
{
    return battle_graphics.graphics_data->species_info[bank]->transformed_species;
}

void* get_poke_nick2(struct pokemon* poke, u8 bank, void* dst)
{
    struct pokemon* illusion_to_happen_later = get_poke_to_illusion_into(poke, bank);
    if (new_battlestruct->bank_affecting[bank].illusion_on)
        strcpy_xFF_terminated_0(dst, &new_battlestruct->bank_affecting[bank].illusion_nick);
    else if (illusion_to_happen_later)
        get_attributes(illusion_to_happen_later, ATTR_NAME, dst);
    else
        get_attributes(poke, ATTR_NAME, dst);
    return shorten_str_to_10(dst);
}

void* get_poke_nick(u8 bank, void* dst)
{
    struct pokemon* poke = get_bank_poke_ptr(bank);
    return get_poke_nick2(poke, bank, dst);
}

void* get_poke_nick_link(u8 linkID, u8 to_xor, void* dst)
{
    u8 bank = battle_link_pbs[linkID].bank_id ^ to_xor;
    struct pokemon* poke;
    if (to_xor & 1)
        poke = party_opponent;
    else
        poke = party_player;
    return get_poke_nick2(&poke[battle_team_id_by_side[bank]], bank, dst);
}

void update_pokenick_in_healthbox(u8 objectID, struct pokemon* poke)
{
    void* string_loc = &displayed_string_in_battle;
    string_loc = strcpy_xFF_terminated_0(string_loc, (void*) 0x085ED228);
    u8 bank = objects[objectID].private[6];
    get_poke_nick2(poke, bank, string_loc);

    u16 species;
    enum poke_gender gender;
    if (new_battlestruct->bank_affecting[bank].illusion_on)
    {
        species = get_transform_species(bank);
        gender = gender_from_pid(species, PiD_pbs[bank]);
    }
    else
    {
        species = get_attributes(poke, ATTR_SPECIES, 0);
        gender = poke_get_gender(poke);
    }
    //append gender sign unless it's already there
    if ((species == POKE_NIDORANM || species == POKE_NIDORANF) && compare_two_strings(string_loc, &poke_name_table->pokename[species].letter) == 0)
    {
        gender = POKE_GENDERLESS;
    }
    void* gender_sign = 0;
    switch (gender)
    {
    case POKE_MALE:
        gender_sign = &nick_male_sign;
        break;
    case POKE_FEMALE:
        gender_sign = &nick_female_sign;
        break;
    case POKE_GENDERLESS:
        gender_sign = &nick_genderless_sign;
        break;
    }
    str_append(string_loc, gender_sign);
}

u8 b_get_ball_to_throw(struct pokemon* poke, u8 bank)
{
    if (new_battlestruct->bank_affecting[bank].illusion_on)
        return new_battlestruct->bank_affecting[bank].illusion_ball;
    return get_attributes(poke, ATTR_POKEBALL, 0);
}

void* get_poke_nick_prefix(u8 bank, u8* dst)
{
    u8 i = 0;
    if (is_bank_from_opponent_side(bank))
    {
        u8* prefix;
        if (battle_flags.trainer)
            prefix = (u8*) &text_Foe_;
        else
            prefix = (u8*) &text_Wild_;
        while (prefix[i] != 0xFF)
        {
            dst[i] = prefix[i];
            i++;
        }
    }
    return &dst[i];
}

void* get_poke_nick_with_prefix(u8 bank, void* dst)
{
    return get_poke_nick(bank, get_poke_nick_prefix(bank, dst));
}

void* get_ability_name_ptr(enum poke_abilities ability)
{
    return ability_names_table[ability];
}

void* get_trainerclass_ptr(u8 classID)
{
    return trainerclass_names[classID];
}

void* get_link_trainername(u8 linkID, u8 to_xor)
{
    u8 bank = battle_link_pbs[linkID].bank_id ^ to_xor;
    return battle_link_pbs[get_linkpbs_id(bank)].trainer_name;
}

u16 battle_string_decoder(u8* src, u8* dst)
{
    u8 link_id = link_get_multiplayer_id();
    if (battle_flags.flag_x2000000)
        link_id = battle_some_link_id;
    u32 dst_id = 0;
    u32 src_id = 0;
    while(src[src_id] != 0xFF)
    {
        u8 curr_char = src[src_id];
        src_id++;
        if (curr_char == 0xFD) //decode string
        {
            u8 text[20];
            u8* string = NULL;
            curr_char = src[src_id];
            src_id++;
            switch (curr_char) //fd char decoding
            {
            case 0:
                if (battle_text_buff1[0] == 0xFD)
                {
                    fdecoder_for_battle_strings(battle_text_buff1, text);
                    string = text;
                }
                else
                {
                   string = get_status_text(battle_text_buff1);
                    if (!string)
                        string = battle_text_buff1;
                }
                break;
            case 1:
                if (battle_text_buff2[0] == 0xFD)
                {
                    fdecoder_for_battle_strings(battle_text_buff2, text);
                    string = text;
                }
                else
                    string = battle_text_buff2;
                break;
            case 52:
                if (battle_text_buff3[0] == 0xFD)
                {
                    fdecoder_for_battle_strings(battle_text_buff3, text);
                    string = text;
                }
                else
                    string = battle_text_buff3;
                break;
            case 2: //copy script text buffer1
                string = script_text_buffer1;
                break;
            case 3: //copy script text buffer2
                string = script_text_buffer2;
                break;
            case 4: //copy script text buffer3
                string = script_text_buffer3;
                break;
            case 5: //player first poke name
                get_poke_nick(get_bank_by_player_ai(0), text);
                string = text;
                break;
            case 6: //opponent first poke name
                get_poke_nick(get_bank_by_player_ai(1), text);
                string = text;
                break;
            case 7: //player second poke name
                get_poke_nick(get_bank_by_player_ai(2), text);
                string = text;
                break;
            case 8: //opponent second poke name
                get_poke_nick(get_bank_by_player_ai(3), text);
                string = text;
                break;
            case 9: //link first player pokemon
                get_poke_nick_link(link_id, 0, text);
                string = text;
                break;
            case 10: //link first opponent pokemon
                get_poke_nick_link(link_id, 1, text);
                string = text;
                break;
            case 11: //link second player pokemon
                get_poke_nick_link(link_id, 2, text);
                string = text;
                break;
            case 12: //link opponent player pokemon
                get_poke_nick_link(link_id, 3, text);
                string = text;
                break;
            case 13: //todo
                break;
            case 14: //attacker name
                get_poke_nick(bank_attacker, text);
                string = text;
                break;
            case 15: //attacker name with prefix
                get_poke_nick_with_prefix(bank_attacker, text);
                string = text;
                break;
            case 53: //target name
                get_poke_nick(bank_target, text);
                string = text;
                break;
            case 16: //target name with prefix
                get_poke_nick_with_prefix(bank_target, text);
                string = text;
                break;
            case 17: //target partner name with prefix
                get_poke_nick_with_prefix(bank_partner_def, text);
                string = text;
                break;
            case 18: //active name with prefix
                get_poke_nick_with_prefix(active_bank, text);
                string = text;
                break;
            case 19: //scripting active name with prefix
                get_poke_nick_with_prefix(battle_scripting.active_bank, text);
                string = text;
                break;
            case 20: //todo
                break;
            case 21: //todo
                break;
            case 22: //get last used item
                if ((battle_flags.link || battle_flags.flag_x2000000) && last_used_item == ITEM_ENIGMABERRY)
                {
                    u8 field25 = battle_scripting.field25;
                    u8 enigma = 1;
                    if (battle_flags.player_partner)
                    {
                        if (battle_link_pbs[field25].bank_id == another_active_bank)
                            enigma = 0;
                    }
                    else if (field25 == 0)
                    {
                        if (!(another_active_bank & 1))
                            enigma = 0;
                    }
                    else if (another_active_bank & 1)
                        enigma = 0;
                    if (enigma)
                        string = text_ENIGMA_BERRY;
                    else
                    {
                        strcpy_xFF_terminated_0(text, enigma_berry_battle[another_active_bank].berry_name);
                        str_append(text, text__BERRY);
                        string = text;
                    }
                }
                else
                {
                    buffer_item(last_used_item, text);
                    string = text;
                }
                break;
            case 23: //last used ability
                string = get_ability_name_ptr(last_used_ability);
                break;
            case 24: //attackers ability
                string = get_ability_name_ptr(abilities_by_banks[bank_attacker]);
                break;
            case 25: //targets ability
                string = get_ability_name_ptr(abilities_by_banks[bank_target]);
                break;
            case 26: //scripting actives ability
                string = get_ability_name_ptr(abilities_by_banks[battle_scripting.active_bank]);
                break;
            case 27: //def partners ability
                string = get_ability_name_ptr(abilities_by_banks[bank_partner_def]);
                break;
            case 28: //trainer A class
                {
                    u8 classID;
                    u16 trainerA = var_8015_trainer_opponent_A;
                    if (battle_flags.secret_base)
                        classID = get_secretbase_trainerclass();
                    else if (trainerA == 0xC00)
                        classID = get_trainerxC00_trainerclass();
                    else if (BATTLE_FRONTIER_BATTLE)
                        classID = get_frontier_opponent_class(trainerA);
                    else if (battle_flags.flag_x4000000)
                        classID = get_x4000000_trainerclass(trainerA);
                    else if (battle_flags.flagx800)
                        classID = get_x800_trainerclass();
                    else
                        classID = trainer_table[trainerA].class;
                    string = get_trainerclass_ptr(classID);
                }
                break;
            case 29: //trainer A name
                if (battle_flags.secret_base)
                    string = battle_resources->secretbase_opponent->trainer_name;
                else if (var_8015_trainer_opponent_A == 0xC00)
                    string = battle_link_pbs[link_id ^ 1].trainer_name;
                else if (BATTLE_FRONTIER_BATTLE)
                {
                    get_frontier_trainer_name(text, var_8015_trainer_opponent_A);
                    string = text;
                }
                else if (battle_flags.flag_x4000000)
                {
                    get_x4000000_trainername(text, var_8015_trainer_opponent_A);
                    string = text;
                }
                else if (battle_flags.flagx800)
                {
                    get_x800_trainername(text);
                    string = text;
                }
                else
                    string = trainer_table[var_8015_trainer_opponent_A].name;
                break;
            case 30: //link player 1 name
                string = get_link_trainername(link_id, 0);
                break;
            case 31: //link player 2 name
                string = get_link_trainername(link_id, 2);
                break;
            case 32: //link player 3 name
                string = get_link_trainername(link_id, 1);
                break;
            case 33: //link player 4 name
                string = get_link_trainername(link_id, 3);
                break;
            case 34: //scripting active link name
                string = battle_link_pbs[get_linkpbs_id(battle_scripting.active_bank)].trainer_name;
                break;
            case 35: //players name
                string = sav2->name;
                break;
            case 36: //trainer A lose text
                if (BATTLE_FRONTIER_BATTLE)
                    get_frontier_opponent_battleend_text(var_8015_trainer_opponent_A, 2);
                else if (battle_flags.flag_x4000000)
                    x4000000_get_battle_text(var_8015_trainer_opponent_A, 4);
                else
                    copy_opponent_a_lose_text();
                string = displayed_string_ov;
                break;
            case 37: //trainer A win text
                if (BATTLE_FRONTIER_BATTLE)
                {
                    get_frontier_opponent_battleend_text(var_8015_trainer_opponent_A, 1);
                    string = displayed_string_ov;
                }
                else if (battle_flags.flag_x4000000)
                {
                    x4000000_get_battle_text(var_8015_trainer_opponent_A, 3);
                    string = displayed_string_ov;
                }
                break;
            case 38: //todo
                break;
            case 39: //PC system creator's name
                string = text_someones;
                if (getflag(0x8AB))
                    string = text_LANETTES;
                break;
            case 40: //attacker foe/ally
                string = text_Ally;
                if (is_bank_from_opponent_side(bank_attacker))
                    string = text_Foe;
                break;
            case 41: //target foe/ally
                string = text_Ally;
                if (is_bank_from_opponent_side(bank_target))
                    string = text_Foe;
                break;
            case 42: //attacker foe_/ally_
            case 44:
                string = text_Ally_;
                if (is_bank_from_opponent_side(bank_attacker))
                    string = text_Foe_;
                break;
            case 43: //target foe_/ally_
            case 45:
                string = text_Ally_;
                if (is_bank_from_opponent_side(bank_target))
                    string = text_Foe_;
                break;
            case 46: //trainer B class
                {
                    u8 class_id;
                    if (BATTLE_FRONTIER_BATTLE)
                        class_id = get_frontier_opponent_class(trainer_opponent_B);
                    else if (battle_flags.flag_x4000000)
                        class_id = get_x4000000_trainerclass(trainer_opponent_B);
                    else
                        class_id = trainer_table[trainer_opponent_B].class;
                    string = get_trainerclass_ptr(class_id);
                }
                break;
            case 47: //trainer B name
                if (BATTLE_FRONTIER_BATTLE)
                {
                    get_frontier_trainer_name(text, trainer_opponent_B);
                    string = text;
                }
                else if (battle_flags.flag_x4000000)
                {
                    get_x4000000_trainername(text, trainer_opponent_B);
                    string = text;
                }
                else
                    string = trainer_table[trainer_opponent_B].name;
                break;
            case 48: //trainer B lose text
                if (BATTLE_FRONTIER_BATTLE)
                    get_frontier_opponent_battleend_text(trainer_opponent_B, 2);
                else if (battle_flags.flag_x4000000)
                    x4000000_get_battle_text(trainer_opponent_B, 4);
                else
                    copy_opponent_b_lose_text();
                string = displayed_string_ov;
                break;
            case 49: //trainer B win text
                if (BATTLE_FRONTIER_BATTLE)
                {
                    get_frontier_opponent_battleend_text(trainer_opponent_B, 1);
                    string = displayed_string_ov;
                }
                else if (battle_flags.flag_x4000000)
                {
                    x4000000_get_battle_text(trainer_opponent_B, 3);
                    string = displayed_string_ov;
                }
                break;
            case 50: //partner trainer class
                string = get_trainerclass_ptr(get_frontier_opponent_class(partner_trainer));
                break;
            case 51: //partner trainer name
                get_frontier_trainer_name(text, partner_trainer);
                string = text;
                break;
            }
            if (string) //copy decoded string
            {
                for (u32 i = 0; string[i] != 0xFF; i++)
                {
                    dst[dst_id] = string[i];
                    dst_id++;
                }
                if (curr_char == 36 || curr_char == 37 || curr_char == 48 || curr_char == 49) //slow win/lose text down
                {
                    dst[dst_id] = 0xFC;
                    dst[dst_id + 1] = 9;
                    dst_id += 2;
                }
            }
        }
        else //just copy character
        {
            dst[dst_id] = curr_char;
            dst_id++;
        }
    }
    dst[dst_id] = 0xFF;
    dst_id++;
    return dst_id;
}

void update_transform_sprite_pal(u8 bank, u16 pal_arg1)
{
    if (battle_graphics.graphics_data->species_info[bank]->pal_change)
    {
        pal_fade_1(pal_arg1, 0x10, 6, 0x7FFF);
        u32 to_add = (pal_arg1) * 2;
        CpuSet((void*) (0x02037B14 + to_add), (void*) (0x02037714 + to_add), 0x4000008);
    }
}

void b_load_sprite(struct pokemon* poke, u8 bank, struct sprite_table* sprites)
{
    u16 species;
    u32 PiD;
    u32 TiD;
    u16 transform_species = get_transform_species(bank);
    void (*sprite_load) (void* sprite_ptr, void* dst, u16 species_no, u32 PiD, enum poke_sprite);
    if (transform_species)
    {
        species = transform_species;
        PiD = PiD_pbs[bank];
        sprite_load = &load_poke_sprite_deoxys_form;
        TiD = new_battlestruct->bank_affecting[bank].transform_tid;
    }
    else
    {
        species = get_attributes(poke, ATTR_SPECIES, 0);
        PiD = get_attributes(poke, ATTR_PID, 0);
        if (b_link_related(1, bank))
            sprite_load = &load_poke_sprite_deoxys_form;
        else
            sprite_load = &load_poke_sprite;
        TiD = get_attributes(poke, ATTR_TID, 0);
    }
    enum poke_sprite sprite = SPRITE_BACK;
    if (sprites == front_sprites)
        sprite = SPRITE_FRONT;
    sprite_load(&sprites->p_sprite[species].sprite, battle_graphics.graphics_loc->decompressed_sprite[get_bank_identity(bank)], species, PiD, sprite);
    void* poke_pal = poke_get_pal(species, TiD, PiD);
    LZ77UnCompWram(poke_pal, &decompression_buffer[0]);
    u16 pal_adder = 256 + bank * 16;
    gpu_pal_apply((struct palette*) (&decompression_buffer), pal_adder, 0x20);
    gpu_pal_apply((struct palette*) (&decompression_buffer), 0x80 + bank * 16, 0x20);
    if (species == POKE_CASTFORM)
    {
        LZ77UnCompWram(poke_pal, &battle_stuff_ptr->castform_pal);
        gpu_pal_apply(&battle_stuff_ptr->castform_pal[castform_form[bank]], pal_adder, 0x20);
    }
    if (transform_species)
    {
        update_transform_sprite_pal(bank,  pal_adder);
    }
}

void b_load_sprite_player(struct pokemon* poke, u8 bank)
{
    b_load_sprite(poke, bank, back_sprites);
    new_battlestruct->various.sent_in_player |= (bits_table[battle_team_id_by_side[bank]]);
}

void b_load_sprite_opponent(struct pokemon* poke, u8 bank)
{
    b_load_sprite(poke, bank, front_sprites);
}

void bbp05_send_out_poke_new()
{
    bbp05_send_out_poke();
    b_load_sprite_player(get_bank_poke_ptr(active_bank), active_bank);
}

void bbp06_return_poke_to_pokeball_new()
{
    new_battlestruct->various.switch_in_cos_switch = 1;
    revert_form_change(0, 0, 0, &party_player[0]);
    bbp06_return_poke_to_pokeball();
}

void bbo_06_return_poke_to_ball_new()
{
    new_battlestruct->various.switch_in_cos_switch = 1;
    revert_form_change(0, 0, 1, &party_opponent[0]);
    bbo_06_return_poke_to_ball();
}

void bbp15_open_bag_new()
{
    bbp15_open_bag();
}

void bbp16_open_poke_menu_new()
{
    bbp16_open_poke_menu();
}

void bbp2F_trainer_ball_throw_new()
{
    bbp2F_trainer_ball_throw();
}

u8 return_0_nop()
{
    return 0;
}

u8 heal_and_confuse_berry_bug_bite(u8 bank, u8 item_effect, u8 quality)
{
    u8 effect = 0;
    //This assumes that the effect ids of these berries are contiguous.
    if(!new_battlestruct->bank_affecting[bank].heal_block && battle_participants[bank].max_hp > battle_participants[bank].current_hp)
    {
        s32 max_hp = battle_participants[bank].max_hp;
        s32 current_hp = battle_participants[bank].current_hp;
        u8 flavour = item_effect - ITEM_EFFECT_FIGYBERRY;
        s32 damage = (max_hp / quality);
        if (damage == 0)
            damage = 1;
        if (damage > (max_hp - current_hp))
            damage = (max_hp - current_hp);
        damage_loc = damage * -1;
        effect = 4;
        if (get_poke_flavour_relation(battle_participants[bank].pid, flavour) == FLAVOUR_DISLIKED)
        {
            battlescript_push();
            battlescripts_curr_instruction=&healandconfuse_bugbite_bs;
        }
        else
        {
            battlescript_push();
            battlescripts_curr_instruction=&healberry_bugbite_bs;
        }
        battle_text_buff1[0] = 0xFD;
        battle_text_buff1[1] = 8;
        battle_text_buff1[2] = 1;
        battle_text_buff1[3] = 0xFF;
    }
    return effect;

}

u8 stat_raise_berry_bug_bite(u8 bank, u8 item_effect)
{
    u8 effect = 0;
    u8 stat_to_check = 0xC;
    u8 stat_to_raise = item_effect - ITEM_EFFECT_LIECHIBERRY;
    if(check_ability(bank,ABILITY_CONTRARY))
    {
        stat_to_check = 0;
    }
    if(item_effect == ITEM_EFFECT_STARFBERRY)
    {
        u8 doable = 0;
        for (u8 i = 0; i < 5; i++)
        {
            if (*(&battle_participants[bank].atk_buff + i) != stat_to_raise)
                doable |= bits_table[i];
        }
        while (doable)
        {
            u8 rand = __umodsi3(rng(), 5);
            if (doable & bits_table[rand])
            {
                effect = 5;
                battle_scripting.stat_changer = 0x21 + rand;
                battle_scripting.field10 = 0xF + rand;
                battle_scripting.field11 = 0;
                break;
            }
        }
    }
    else
    {
        if (*(&battle_participants[bank].atk_buff + stat_to_raise) != stat_to_check)
        {
            effect = 5;
            battle_text_buff1[0] = 0xFD;
            battle_text_buff1[1] = 0x5;
            battle_text_buff1[2] = stat_to_raise + 1;
            battle_text_buff1[3] = 0xFF;
            bank_partner_def = bank;
            battle_scripting.stat_changer = 0x11 + stat_to_raise;
            battle_scripting.field10 = 0xF + stat_to_raise;
            battle_scripting.field11 = 0;
        }
    }
    if(effect)
    {
        battlescript_push();
        battlescripts_curr_instruction=&statraise_berry_bugbite_bs;
    }
    return effect;
}

bool handle_leppa(u8 bank, u8 quality, enum call_mode calling_mode)
{
    u8 i=0;
    u8 pp_to_set=0;
    bool effect = false;
    struct pokemon *poke_data;
    u8 poke_slot_id = battle_team_id_by_side[bank];
    u16 chosen_move;
    poke_data = is_bank_from_opponent_side(bank)?&party_opponent[poke_slot_id]:&party_player[poke_slot_id];
    for (i = 0; i < 4; i++)
    {
        chosen_move = get_attributes(poke_data,ATTR_ATTACK_1+i,0);
        if (chosen_move && get_attributes(poke_data,ATTR_PP_1+i,0)==0)
        {
            effect = true;
            break;
        }
    }
    if(effect)
    {
        u8 total_pp=calc_total_move_pp(chosen_move,get_attributes(poke_data,ATTR_PP_BONUS,0),i);
        if(total_pp<quality)
        {
            pp_to_set=total_pp;
        }
        else
        {
            pp_to_set=quality;
        }
        battle_text_buff1[0]=0xFD;
        battle_text_buff1[1]=0x2;
        battle_text_buff1[2]=(u8)chosen_move;
        battle_text_buff1[3]=chosen_move>>8;
        battle_text_buff1[4]=0xFF;

        bank_attacker=bank;
        active_bank=bank;
        if(calling_mode==BATTLE_TURN)
        {
            call_bc_move_exec((void *)0x82DB7E1);
        }
        else
        {
            battlescript_push();
            battlescripts_curr_instruction = &leppa_endmove_bs;
        }
        prepare_setattributes_in_battle(0,i+10,0,1,&pp_to_set);
        mark_buffer_bank_for_execution(bank);

        if(!battle_participants[bank].status2.transformed && !((disable_structs[bank].truant_counter>>4)&bits_table[i]))
        {
            battle_participants[bank].current_pp[i]=pp_to_set;
        }
    }
    return effect;
}

bool handle_leppa_bugbite(u8 bank, u8 quality)
{
    u8 i=0,j;
    u8 pp_to_set=0;
    bool effect = false;
    struct pokemon *poke_data;
    u8 poke_slot_id = battle_team_id_by_side[bank];
    u16 chosen_move=0;
    u16 min_pp_ratio=0x7FFF;
    u16 curr_pp=0;
    u8 total_pp=0;
    poke_data = is_bank_from_opponent_side(bank)?&party_opponent[poke_slot_id]:&party_player[poke_slot_id];
    for (j = 0; j < 4; j++)
    {
        u16 candidate_move = get_attributes(poke_data,ATTR_ATTACK_1+j,0);
        if(candidate_move)
        {
            u8 cand_curr_pp = get_attributes(poke_data,ATTR_PP_1+j,0);
            u8 cand_tot_pp = calc_total_move_pp(candidate_move,get_attributes(poke_data,ATTR_PP_BONUS,0),j);
            u16 pp_ratio = __udivsi3(cand_curr_pp<<7,cand_tot_pp);
            if (cand_curr_pp!=cand_tot_pp && pp_ratio<min_pp_ratio)
            {
                min_pp_ratio = pp_ratio;
                chosen_move = candidate_move;
                total_pp = cand_tot_pp;
                curr_pp = cand_curr_pp;
                i=j;
                effect = 2;
            }
        }

    }
    if(effect)
    {
        if(total_pp<(quality+curr_pp))
        {
            pp_to_set=total_pp;
        }
        else
        {
            pp_to_set=(quality+curr_pp);
        }
        battle_text_buff1[0]=0xFD;
        battle_text_buff1[1]=0x2;
        battle_text_buff1[2]=(u8)chosen_move;
        battle_text_buff1[3]=chosen_move>>8;
        battle_text_buff1[4]=0xFF;

        bank_attacker=bank;
        active_bank=bank;
        battlescript_push();
        battlescripts_curr_instruction = &leppa_bugbite_bs;

        prepare_setattributes_in_battle(0,i+10,0,1,&pp_to_set);
        mark_buffer_bank_for_execution(bank);

        if(!battle_participants[bank].status2.transformed && !((disable_structs[bank].truant_counter>>4)&bits_table[i]))
        {
            battle_participants[bank].current_pp[i]=pp_to_set;
        }
    }
    return effect;
}

void handle_bug_bite()
{
    u8 bank = bank_attacker;
    u8 effect= 0;
    u8 item_effect=get_item_battle_function(last_used_item);
    u8 quality=get_item_quality(last_used_item);
    switch(item_effect)
    {
        case ITEM_EFFECT_ORANBERRY:
            if (!new_battlestruct->bank_affecting[bank_target].heal_block && battle_participants[bank].max_hp > battle_participants[bank].current_hp)
            {
                effect = 4;
                if (quality > battle_participants[bank].max_hp - battle_participants[bank].current_hp)
                    quality = battle_participants[bank].max_hp - battle_participants[bank].current_hp;
                damage_loc = quality * -1;
                battlescript_push();
                battlescripts_curr_instruction=&healberry_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_SITRUSBERRY:
            if (!new_battlestruct->bank_affecting[bank_target].heal_block && battle_participants[bank].max_hp > battle_participants[bank].current_hp)
            {
                effect = 4;
                s32 damage = battle_participants[bank].max_hp >> 2;
                if (damage > battle_participants[bank].max_hp - battle_participants[bank].current_hp)
                    damage = battle_participants[bank].max_hp - battle_participants[bank].current_hp;
                damage_loc = damage * -1;
                battlescript_push();
                battlescripts_curr_instruction=&healberry_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_CHERIBERRY:
            if (battle_participants[bank].status.flags.paralysis)
            {
                effect = 1;
                battle_participants[bank].status.flags.paralysis = 0;
                battlescript_push();
                battlescripts_curr_instruction=&prlzcure_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_CHESTOBERRY:
            if (battle_participants[bank].status.flags.sleep)
            {
                effect = 1;
                battle_participants[bank].status.flags.sleep = 0;
                battlescript_push();
                battlescripts_curr_instruction=&slpcure_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_PECHABERRY:
            if (battle_participants[bank].status.flags.poison || battle_participants[bank].status.flags.toxic_poison)
            {
                effect = 1;
                battle_participants[bank].status.flags.poison = 0;
                battle_participants[bank].status.flags.toxic_poison = 0;
                battlescript_push();
                battlescripts_curr_instruction=&psncure_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_RAWSTBERRY:
            if (battle_participants[bank].status.flags.burn)
            {
                effect = 1;
                battle_participants[bank].status.flags.burn = 0;
                battlescript_push();
                battlescripts_curr_instruction=&brncure_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_ASPEARBERRY:
            if (battle_participants[bank].status.flags.freeze)
            {
                effect = 1;
                battle_participants[bank].status.flags.freeze = 0;
                battlescript_push();
                battlescripts_curr_instruction=&frzcure_bugbite_bs;
            }
            break;

        case ITEM_EFFECT_LEPPABERRY:
            effect = handle_leppa_bugbite(bank,quality);
            break;
        case ITEM_EFFECT_PERSIMBERRY:
            if (battle_participants[bank].status2.confusion)
            {
                battle_participants[bank].status2.confusion = 0;
                effect = 2;
                battlescript_push();
                battlescripts_curr_instruction=&confcure_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_LUMBERRY:
            if (battle_participants[bank].status.int_status || battle_participants[bank].status2.confusion)
            {
                copy_status_condition_text(bank, 1);
                battle_participants[bank].status2.confusion = 0;
                battle_participants[bank].status.int_status = 0;
                effect = 1;
                battlescript_push();
                battlescripts_curr_instruction=&lum_bugbite_bs;
            }
            break;
        case ITEM_EFFECT_FIGYBERRY:
        case ITEM_EFFECT_WIKIBERRY:
        case ITEM_EFFECT_MAGOBERRY:
        case ITEM_EFFECT_AGUAVBERRY:
        case ITEM_EFFECT_IAPAPABERRY:
            effect = heal_and_confuse_berry_bug_bite(bank, item_effect, quality);
            break;
        case ITEM_EFFECT_LIECHIBERRY:
        case ITEM_EFFECT_GANLONBERRY:
        case ITEM_EFFECT_SALACBERRY:
        case ITEM_EFFECT_PETAYABERRY:
        case ITEM_EFFECT_APICOTBERRY:
        case ITEM_EFFECT_STARFBERRY:
            effect = stat_raise_berry_bug_bite(bank, item_effect);
            break;
        case ITEM_EFFECT_LANSATBERRY:
            if (!(battle_participants[bank].status2.focus_energy))
            {
                battle_participants[bank].status2.focus_energy = 1;
                effect = 2;
                battlescript_push();
                battlescripts_curr_instruction=&lansat_bugbite_bs;
            }
            break;
    }
    if(effect==0)
    {
        battlescript_push();
        battlescripts_curr_instruction=&bugsteal_bs;
    }
    else
    {
        if (effect == 1)
        {
            active_bank = bank;
            prepare_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[bank].status.flags);
            mark_buffer_bank_for_execution(bank);
        }
    }
    setup_berry_consume_buffers(bank);
}

u8 count_alive_mons(u8 bank)
{
    struct pokemon* poke = get_party_ptr(bank);
    u8 pokes_amount = 0;
    for (u8 i = 0; i < 6; i++)
    {
        struct pokemon* checking_poke = &poke[i];
        if (is_poke_valid(checking_poke) && get_attributes(checking_poke, ATTR_CURRENT_HP, 0))
            pokes_amount++;
    }
    return pokes_amount;
}
