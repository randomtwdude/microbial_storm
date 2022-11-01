#ifndef STRUCT_H
#define STRUCT_H

#include <string.h>
#include <iostream>
using namespace std;

struct card {
    string name;
    string desc;
    int id;
};

struct player {
    int type; // 0 for humans, 1 for microbes
    string name;
    short health = 3; // initialized to 3 HP
    card hand[6] = {};
    int handCount = 0;
};

#endif