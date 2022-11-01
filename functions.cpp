#include <string.h>
#include <iostream>
#include <cstdio>
#include <random>
#include <assert.h>

#include "struct.h"
#include "functions.h"
using namespace std;

#define CARD_COUNT 2
card deck[CARD_COUNT];

/* All microbe cards have ODD ids */
 void createCards() {
    cout << "Creating cards!\n";
    static card test;
    test.id = 0;
    test.name = "TESTCARD";
    test.desc = "Testing";
    deck[0] = test;

    static card test2;
    test2.id = 1;
    test.name = "TESTCARD2";
    test.desc = "Testing2";
    deck[1] = test2;
}

void createPlayer(player player1, player player2) {
    cout << "Please enter a name for player 1: " << endl;
    cin >> player1.name;

    cout << "Please enter a name for player 2: " << endl;
    cin >> player2.name;

    srand(time(NULL));
    player1.type = rand() % 2;
    player2.type = player1.type ? 0 : 1;

    // using printf here so I can put ternaries in it
    printf("%s is playing as %s!", player1.name.c_str(), player1.type ? "the microbes" : "the human");
}

void addCard(player p, card c) {
    assert(p.handCount < 6);
    p.hand[p.handCount] = c;
    p.handCount++;
    cout << "Dealt card " << c.name << " (" << c.id << ") to player " << p.name << endl;
}

/* num: number of cards to deal */
void dealCard(player p, int num) {
    assert(p.handCount + num <= 6);
    for(int i=0; i<num; i++) {
        srand(time(NULL));
        int sel;

        do sel = rand() % CARD_COUNT;
        while(sel % 2 != p.type);

        for(int j=0; j<CARD_COUNT; j++)
            if(deck[j].id == sel)
                addCard(p, deck[j]);
    }
}

void gameLoop(player player1, player player2) {
    cout << "HIHI";
    string input;
    cout << "hi";
    dealCard(player1, 5);
    dealCard(player2, 5);
    while(cin >> input) {
        if(input == "quit") {
            return;
        }
    }
}