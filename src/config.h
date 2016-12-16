#ifndef CONFIG_H
#define CONFIG_H

#include "types.h"

#define ALL_POKES       412     //number of all pokemon
#define ALL_ITEMS       377     //number of all items
#define NUM_OF_EVOS     5       //number of evolutions per pokemon
#define KEYSTONE        0x4     //mega item that the player has to posses in order to mega evolve

#define EXP_CAPTURE     true    //set to false if you don't want to receive exp from catching pokes
#define STAT_RECALC     false   //set to true if you want all pokemon having their stats recalculated at the end of the battle

//form indexes
#define POKE_CHERRIM                1000
#define POKE_CHERRIM_SUNSHINE       1001
#define POKE_DARMANITAN             1002
#define POKE_ZEN_MODE               1003
#define POKE_AEGISLASH_BLADE        1004
#define POKE_AEGISLASH_SHIELD       1005
#define POKE_MELOETTA_ARIA          1006
#define POKE_MELOETTA_PIROUETTE     1007
#define POKE_BURMY_PLANT            1008
#define POKE_BURMY_SAND             1009
#define POKE_BURMY_TRASH            1010

//mega primal species
#define POKE_MEGA_RAYQUAZA          1011

//only change these if you want to adjust the position of mega icons or if you want to change the HP bars
#define SINGLES_HEALTHBOX_X 120
#define DBL_HB_0_X 120
#define DBL_HB_2_X 132
#define SINGLES_HEALTHBOX_Y 90
#define DBL_HB_0_Y 75
#define DBL_HB_2_Y 100

#endif /* CONFIG_H */
