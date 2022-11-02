#ifndef STRUCT_H
#define STRUCT_H

#include <string.h>
#include <iostream>
using namespace std;

struct card {
    string name;
    string desc;
    char type;
    int immune = 0; // pathogen card only
    int target[10] = {0}; // human function cards only
    int id;
};

struct player {
    int type; // 0 for humans, 1 for microbes
    string name;
    short health = 3; // initialized to 3 HP
    card hand[10] = {};
    int handCount = 0;
};

#endif