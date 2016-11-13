#include "defines.h"

u8 is_bank_present(u8 bank);
struct pokemon* get_party_ptr(u8 bank);
struct pokemon* get_bank_poke_ptr(u8 bank);
u8 is_poke_valid(struct pokemon* poke);
u8 count_party_pokemon(u8 bank);
void revert_form_change(u8 mega_revert, u8 teamID, u8 side, struct pokemon* poke);

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
        return 1;
    }
    return 0;
}

u16 get_transform_species(u8 bank)
{
    return battle_graphics.graphics_data->species_info[bank]->transformed_species;
}

void* get_poke_nick(u8 bank, void* dst)
{
    struct pokemon* illusion_to_happen_later = get_poke_to_illusion_into(get_bank_poke_ptr(bank), bank);
    if (new_battlestruct->bank_affecting[bank].illusion_on)
        strcpy_xFF_terminated_0(dst, &new_battlestruct->bank_affecting[bank].illusion_nick);
    else if (illusion_to_happen_later)
        get_attributes(illusion_to_happen_later, ATTR_NAME, dst);
    else
        get_attributes(get_bank_poke_ptr(bank), ATTR_NAME, dst);
    return shorten_str_to_10(dst);
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

void update_pokenick_in_healthbox(u8 objectID, struct pokemon* poke)
{
    void* string_loc = &displayed_string_in_battle;
    string_loc = strcpy_xFF_terminated_0(string_loc, (void*) 0x085ED228);
    u8 bank = objects[objectID].private[6];
    get_poke_nick2(poke, bank, string_loc);

    u16 species;
    enum poke_gender gender;
    u16 transform_species = get_transform_species(bank);
    if (transform_species)
    {
        species = transform_species;
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

u8 get_poke_nick_prefix(u8 bank, u8* prefix_dst, u8 adder)
{
    if (is_bank_from_opponent_side(bank))
    {
        u8* prefix;
        if (battle_flags.trainer)
            prefix = (u8*) &text_Foe_;
        else
            prefix = (u8*) &text_Wild_;
        do
        {
            *(prefix_dst + adder) = *prefix;
            prefix++;
            adder++;
        } while (*prefix != 0xFF);
    }
    return adder;
}

u8 get_poke_nick_with_prefix(u8 bank, void* nick_dst, void* prefix_dst, u8 adder)
{
    adder = get_poke_nick_prefix(bank, prefix_dst, adder);
    get_poke_nick(bank, nick_dst);
    return adder;
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
    sprite_load(&sprites->p_sprite[species].sprite, battle_graphics.graphics_loc->decompressed_sprite[bank], species, PiD, SPRITE_BACK);
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
