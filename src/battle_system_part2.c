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
bool stat_raise_berry(u8 bank, bool checkHP, u8 item_effect, enum call_mode calling_mode);

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
                battle_scripting.AnimInfo1 = 0xA;
                is_weather_loaded = true;
            }
            break;
        case 8:
            if(!battle_weather.flags.permament_sandstorm && !battle_weather.flags.sandstorm)
            {
                battle_weather.int_bw = (weather_permament_sandstorm | weather_sandstorm);
                battle_scripting.AnimInfo1 = 0xC;
                is_weather_loaded = true;
            }
            break;
        case 12:
            if(!battle_weather.flags.permament_sun && !battle_weather.flags.sun)
            {
                battle_weather.int_bw = (weather_permament_sun | weather_sun);
                battle_scripting.AnimInfo1 = 0xB;
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

bool try_illusion_change(struct pokemon* poke, u8 bank)
{
    struct pokemon* masquerade_as = get_poke_to_illusion_into(poke, bank);
    if (masquerade_as)
    {
        new_battlestruct->bank_affecting[bank].illusion_on = 1;
        (*battle_graphics.graphics_data->species_info)[bank].pal_change = 0;
        (*battle_graphics.graphics_data->species_info)[bank].transformed_species = get_attributes(masquerade_as, ATTR_SPECIES, 0);
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
    return (*battle_graphics.graphics_data->species_info)[bank].transformed_species;
}

u8* get_poke_nick2(struct pokemon* poke, u8 bank, u8* dst)
{
    struct pokemon* illusion_to_happen_later = get_poke_to_illusion_into(poke, bank);
    if (new_battlestruct->bank_affecting[bank].illusion_on)
        strcpy_xFF_terminated_0(dst, new_battlestruct->bank_affecting[bank].illusion_nick);
    else if (illusion_to_happen_later)
        get_attributes(illusion_to_happen_later, ATTR_NAME, dst);
    else
        get_attributes(poke, ATTR_NAME, dst);
    return shorten_str_to_10(dst);
}

u8* get_poke_nick(u8 bank, u8* dst)
{
    struct pokemon* poke = get_bank_poke_ptr(bank);
    return get_poke_nick2(poke, bank, dst);
}

u8* get_poke_nick_link(u8 linkID, u8 to_xor, u8* dst)
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
    u8* string_loc = displayed_string_in_battle;
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
    if ((species == POKE_NIDORANM || species == POKE_NIDORANF) && compare_two_strings(string_loc, (*poke_name_table)[species]) == 0)
    {
        gender = POKE_GENDERLESS;
    }
    const u8* gender_sign = NULL;
    switch (gender)
    {
    case POKE_MALE:
        gender_sign = nick_male_sign;
        break;
    case POKE_FEMALE:
        gender_sign = nick_female_sign;
        break;
    case POKE_GENDERLESS:
        gender_sign = nick_genderless_sign;
        break;
    }
    str_append(string_loc, gender_sign);
}

u16 b_get_ball_to_throw(u8 bank)
{
    u8 pokeball;
    if (new_battlestruct->bank_affecting[bank].illusion_on)
        pokeball = new_battlestruct->bank_affecting[bank].illusion_ball;
    else
        pokeball = get_attributes(get_bank_poke_ptr(bank), ATTR_POKEBALL, 0);
    if (!EXPANDED_POKEBALLS)
        return itemID_to_ballID(pokeball);
    else
        return pokeball;
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

const u8* get_ability_name_ptr(enum poke_abilities ability)
{
    return ability_names_table[ability];
}

const u8* get_trainerclass_ptr(u8 classID)
{
    return trainerclass_names[classID];
}

u8* get_link_trainername(u8 linkID, u8 to_xor)
{
    u8 bank = battle_link_pbs[linkID].bank_id ^ to_xor;
    return battle_link_pbs[get_linkpbs_id(bank)].trainer_name;
}

const u8* get_partner_name(void)
{
    const u8* string_ptr = NULL;
    if (battle_flags.player_ingame_partner)
    {
        if (partner_trainer & PARTNER_CUSTOM)
            string_ptr = (*trainer_table)[BIC(partner_trainer, PARTNER_ANIMATES | PARTNER_CUSTOM)].name;
        else
        {
            get_frontier_trainer_name(script_text_buffer1, partner_trainer);
            string_ptr = script_text_buffer1;
        }
    }
    else
    {
        u8 linkID = link_get_multiplayer_id();
        linkID = battle_link_pbs[linkID].bank_id;
        linkID = get_linkpbs_id(linkID ^ 2);
        string_ptr = battle_link_pbs[linkID].trainer_name;
    }
    return string_ptr;
}

extern const u8 userteam_text[];
extern const u8 userteam_uc_text[];
extern const u8 foeteam_text[];
extern const u8 foeteam_uc_text[];

u16 battle_string_decoder(const u8* const src, u8* const dst)
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
            const u8* string = NULL;
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
            case 62: //new battlestruct bank with prefix
                get_poke_nick_with_prefix(new_battlestruct->various.active_bank, text);
                string = text;
                break;
            case 20: //move1 in buffer pointer
                string = move_names_table[(*buffer_moves)[0]];
                break;
            case 21: //move2 in buffer pointer
                string = move_names_table[(*buffer_moves)[1]];
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
                        classID = (*trainer_table)[trainerA].class;
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
                    string = (*trainer_table)[var_8015_trainer_opponent_A].name;
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
                else if (GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
                {
                    string = opponentwon_text;
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
                        class_id = (*trainer_table)[trainer_opponent_B].class;
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
                    string = (*trainer_table)[trainer_opponent_B].name;
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
                if (partner_trainer & PARTNER_CUSTOM)
                    string = get_trainerclass_ptr((*trainer_table)[BIC(partner_trainer, PARTNER_ANIMATES | PARTNER_CUSTOM)].class);
                else
                    string = get_trainerclass_ptr(get_frontier_opponent_class(partner_trainer));
                break;
            case 51: //partner trainer name
                string = get_partner_name();
                break;
            case 54: //current move
                string = move_names_table[current_move];
                break;
            case 55: //lost/drew/won
                if (battle_outcome == OUTCOME_LOSS)
                {
                    static const u8 lost[] = {l_, o_, s_, t_, Space, a_, g_, a_, i_, n_, s_, t_, 0xFF};
                    strcpy_xFF_terminated_0(text, lost);
                }
                else if (battle_outcome == OUTCOME_WIN)
                {
                    static const u8 won[] = {w_, o_, n_, Space, a_, g_, a_, i_, n_, s_, t_, 0xFF};
                    strcpy_xFF_terminated_0(text, won);
                }
                else if (battle_outcome == OUTCOME_DRAW)
                {
                    static const u8 drew[] = {d_, r_, e_, w_, Space, w_, i_, t_, h_, 0xFF};
                    strcpy_xFF_terminated_0(text, drew);
                }
                string = text;
                break;
            case 56: //trainer sliding msg
                string = new_battlestruct->various.trainer_slide_msg;
                break;
            case 57: //bank attacker, your team or foe's team - lowercase first letter
                if (is_bank_from_opponent_side(bank_attacker))
                    string = foeteam_text;
                else
                    string = userteam_text;
                break;
            case 63: //bank target, your team or foe's team - lowercase first letter
                if (is_bank_from_opponent_side(bank_target))
                    string = foeteam_text;
                else
                    string = userteam_text;
                break;
            case 64: //bank target, your team or foe's team - uppercase first letter
                if (is_bank_from_opponent_side(bank_target))
                    string = foeteam_uc_text;
                else
                    string = userteam_uc_text;
                break;
            case 58: //sharply/harshly, drastically, severally
                {
                    u8 stat_val = battle_scripting.stat_changer & STAT_STAGES;
                    if (stat_val == 0x20)
                        string = text_sharply_;
                    else if (stat_val == 0xA0)
                        string = text_harshly_;
                    else if (stat_val >= 0xB0)
                    {
                        static const u8 text_severely_[] = {s_, e_, v_, e_, r_, e_, l_, y_, Space, 0xFF};
                        string = text_severely_;
                    }
                    else if (stat_val >= 0x30 && stat_val < 0x70)
                    {
                        static const u8 text_drastically_[] = {d_, r_, a_, s_, t_, i_, c_, a_, l_, l_, y_, Space, 0xFF};
                        string = text_drastically_;
                    }
                }
                break;
            case 59: //rose/fell
                if (battle_scripting.stat_changer & STAT_NEGATIVE)
                    string = text_fell;
                else
                    string = text_rose;
                break;
            case 60: //lower/higher
                if (battle_scripting.stat_changer & STAT_NEGATIVE)
                    string = text_lower;
                else
                {
                    static const u8 text_higher[] = {h_, i_, g_, h_, e_, r_, 0xFF};
                    string = text_higher;
                }
                break;
            case 61: //raised, lowered
                if (battle_scripting.stat_changer & STAT_NEGATIVE)
                {
                    static const u8 text_lowered[] = {l_, o_, w_, e_, r_, e_, d_, 0xFF};
                    string = text_lowered;
                }
                else
                {
                    static const u8 text_raised[] = {r_, a_, i_, s_, e_, d_, 0xFF};
                    string = text_raised;
                }
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
    if ((*battle_graphics.graphics_data->species_info)[bank].pal_change)
    {
        pal_fade_1(pal_arg1, 0x10, 6, 0x7FFF);
        u32 to_add = (pal_arg1) * 2;
        CpuSet((void*) (0x02037B14 + to_add), (void*) (0x02037714 + to_add), 0x4000008);
    }
}

void b_load_sprite(struct pokemon* poke, u8 bank, const struct sprite_poke (*sprites)[ALL_POKES])
{
    //load actual sprite
    if (!new_battlestruct->bank_affecting[bank].caught)
    {
        u16 species;
        u32 PiD, TiD;
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
        sprite_load((void*) &(*sprites)[species].sprite, battle_graphics.graphics_loc->decompressed_sprite[get_bank_identity(bank)], species, PiD, sprite);
        void* poke_pal = poke_get_pal(species, TiD, PiD);
        LZ77UnCompWram(poke_pal, decompression_buffer);
        u16 pal_adder = 256 + bank * 16;
        gpu_pal_apply((struct palette*) (decompression_buffer), pal_adder, 0x20);
        gpu_pal_apply((struct palette*) (decompression_buffer), 0x80 + bank * 16, 0x20);
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
    else
    {
        //pokemon is caught, set invisibility bit
        (*battle_graphics.graphics_data->species_info)[bank].invisible = 1;
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

u8 return_0_nop(void)
{
    return 0;
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
