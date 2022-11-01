#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "struct.h"

void createPlayer(player &player1, player &player2);

void addCard(player &p, card c);

void dealCard(player &p, int num);

void gameLoop(player &player1, player &player2);

void createCards();

#endif