#include <string.h>
#include <iostream>
#include <cstdio>
#include <random>
#include <assert.h>

#include "struct.h"
#include "cards.cpp"
using namespace std;

void createPlayer() {
    cout << "Please enter a name for player 1: " << endl;
    static player player1;
    cin >> player1.name;

    cout << "Please enter a name for player 2: " << endl;
    static player player2;
    cin >> player2.name;

    srand(time(NULL));
    player1.type = rand() % 2;
    player2.type = player1.type ? 0 : 1;

    // using printf here so I can put ternaries in it
    printf("%s is playing as %s!", player1.name.c_str(), player1.type ? "the microbes" : "the human");

    // create the cards
    createCards();
}

void addCard(player p, card c) {
    assert(p.handCount < 6);
    p.hand[p.handCount] = c;
    p.handCount++;
}

/* num: number of cards to deal */
void dealCard(player p, int num) {
    assert(p.handCount + num <= 6);
    for(int i=0; i<num; i++) {
        srand(time(NULL));
        int sel = rand() % CARD_COUNT + 1;
        for(int j=0; j<CARD_COUNT; j++)
            if(deck[j].id == sel)
                addCard(p, deck[j]);

    }
}

void gameLoop() {
    string input;
    while(cin >> input) {
        if(input == "quit") {
            return;
        }
    }
}