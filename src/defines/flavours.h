#ifndef FLAVOURS_H
#define FLAVOURS_H

enum poke_flavours
{
    SPICY_PREFERENCE, //0
    DRY_PREFERENCE, //1
    SWEET_PREFERENCE, //2
    BITTER_PREFERENCE, //3
    SOUR_PREFERENCE //4
};

enum poke_flavour_status
{
    FLAVOUR_NEUTRAL,
    FLAVOUR_LIKED,
    FLAVOUR_DISLIKED=0xFF
};
#endif /* FLAVOURS_H */
