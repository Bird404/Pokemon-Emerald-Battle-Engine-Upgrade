#ifndef DEFINES_H
#define DEFINES_H

#include "./defines/poke_types.h"
#include "./defines/abilities.h"
#include "./defines/moves.h"
#include "./defines/get_attr.h"
#include "./defines/items.h"
#include "./defines/item_effects.h"
#include "./defines/pokes.h"
#include "./defines/flavours.h"
#include "battle_structs.h"
#include "battle_locations.h"

//mega item that the player has to posses in order to mega evolve

#define KEYSTONE 0x28

#define MOVE_WORKED !(move_outcome.failed || move_outcome.missed || move_outcome.not_affected)
#define TARGET_TURN_DAMAGED (special_statuses[bank_target].moveturn_losthp)
#define DAMAGING_MOVE (move_table[current_move].split!=2)
#define CHOICE_ITEM(effect) (effect == ITEM_EFFECT_CHOICEBAND || effect == ITEM_EFFECT_CHOICESCARF || effect == ITEM_EFFECT_CHOICESPECS)
#define SEMI_INVULNERABLE(bank) (status3[bank].underground || status3[bank].underwater || status3[bank].on_air || status3[bank].phantomforce)

#define REQUEST_HELDITEM_BATTLE 0x2
#define REQUEST_STATUS_BATTLE 0x28

#define Space 0x00
#define JumpLine 0xFE
#define BuffCharac 0xFD
#define Apos 0xB4
#define Comma 0xB8
#define Dot 0xAD
#define Exclam 0xAB
#define Interro 0xAC
#define Termin 0xFF
#define Dash 0xAE
#define Slash 0xBA

#define Poke_e 0x1B

#define A_ 0xBB
#define B_ 0xBC
#define C_ 0xBD
#define D_ 0xBE
#define E_ 0xBF
#define F_ 0xC0
#define G_ 0xC1
#define H_ 0xC2
#define I_ 0xC3
#define J_ 0xC4
#define K_ 0xC5
#define L_ 0xC6
#define M_ 0xC7
#define N_ 0xC8
#define O_ 0xC9
#define P_ 0xCA
#define Q_ 0xCB
#define R_ 0xCC
#define S_ 0xCD
#define T_ 0xCE
#define U_ 0xCF
#define V_ 0xD0
#define W_ 0xD1
#define X_ 0xD2
#define Y_ 0xD3
#define Z_ 0xD4

#define a_ 0xD5
#define b_ 0xD6
#define c_ 0xD7
#define d_ 0xD8
#define e_ 0xD9
#define f_ 0xDA
#define g_ 0xDB
#define h_ 0xDC
#define i_ 0xDD
#define j_ 0xDE
#define k_ 0xDF
#define l_ 0xE0
#define m_ 0xE1
#define n_ 0xE2
#define o_ 0xE3
#define p_ 0xE4
#define q_ 0xE5
#define r_ 0xE6
#define s_ 0xE7
#define t_ 0xE8
#define u_ 0xE9
#define v_ 0xEA
#define w_ 0xEB
#define x_ 0xEC
#define y_ 0xED
#define z_ 0xEE

//Mega icons related
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
#define REGULAR 0
#define LIGHT_UP_TRIGGER 1
#define TRIGGER_ON 2
#define REVERT_COLORS 3

#define RELATIVE_X 3
#define BASE_X 4
#define SINGLES_HEALTHBOX_X 120
#define DBL_HB_0_X 120
#define DBL_HB_2_X 132
#define SINGLES_HEALTHBOX_Y 90
#define DBL_HB_0_Y 75
#define DBL_HB_2_Y 100
#define TRIGGER_NUM_IGNORED_COLORS 4

#define DISABLED_INDICATOR 1

enum call_mode
{
    BATTLE_TURN,
    MOVE_TURN
};

#endif /* DEFINES_H */
