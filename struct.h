#ifndef STRUCT_H
#define STRUCT_H

#include <string.h>
#include <iostream>
using namespace std;

#define CARD_COUNT 2

struct card {
    string name;
    string desc;
    int id;
};

extern card deck[CARD_COUNT];

struct player {
    int type; // 0 for humans, 1 for microbes
    string name;
    short health = 3; // initialized to 3 HP
    card hand[6] = {};
    int handCount = 0;
};

#endif