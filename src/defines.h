#include "./Defines/poke_types.h"
#include "./Defines/abilities.h"
#include "./Defines/moves.h"
#include "./Defines/get_attr.h"
#include "./Defines/items.h"
#include "./Defines/item_effects.h"
#include "./Defines/pokes.h"
#include "./Defines/flavours.h"
#include "battle_structs.h"
#include "battle_locations.h"

#define NUM_OF_EVOS 5
#define EVOTABLE_POINTER 0x0832531C

struct evolution{
    struct evolution_sub evos[NUM_OF_EVOS];
};

struct evolution* evolution_table = (void*) EVOTABLE_POINTER;

//Pokemon Basestats table

#define POKEBASESTATS_POINTER 0x083203CC

struct poke_basestats* pokemon_table = (void*) POKEBASESTATS_POINTER;

//mega item that the player has to posses in order to mega evolve

#define KEYSTONE 0x28


#define MOVE_WORKED !(move_outcome.failed || move_outcome.missed || move_outcome.not_affected)
#define TARGET_TURN_DAMAGED (special_statuses[bank_target].moveturn_losthp)
#define DAMAGING_MOVE move_table[current_move].base_power
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
