#include "defines.h"

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
