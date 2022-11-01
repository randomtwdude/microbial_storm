#include <string.h>
#include <iostream>
#include <cstdio>
#include <random>
#include <chrono>
#include <thread>
#include <assert.h>

#include "struct.h"
#include "functions.h"
using namespace std;

// Change this to reflect changes to cards.def
#define CARD_COUNT 11
card deck[CARD_COUNT];

// insert card into deck, called by createCards()
void insertCard(card c, int &n) {
    deck[n] = c;
    n++;
}

/* All microbe cards have ODD ids */
void createCards() {
    cout << "Creating cards!\n";
    #include "cards.def"
}

void createPlayer(player &player1, player &player2) {
    cout << "Please enter a name for player 1: " << endl;
    cin >> player1.name;

    cout << "Please enter a name for player 2: " << endl;
    cin >> player2.name;

    srand(time(NULL));
    player1.type = rand() % 2;
    player2.type = player1.type ? 0 : 1;

    // using printf here so I can put ternaries in it
    printf("%s is playing as %s!\n", player1.name.c_str(), player1.type ? "the microbes" : "the human");
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void addCard(player &p, card c) {
    assert(p.handCount < 6);
    p.hand[p.handCount] = c;
    p.handCount++;
}

/* num: number of cards to deal */
void dealCard(player &p, int num) {
    cout << "Dealing " << num << " cards to " << p.name << endl;
    assert(p.handCount + num <= 6);

    srand(time(NULL));

    for(int i=0; i<num; i++) {
        int sel;

        do sel = rand() % CARD_COUNT;
        while(deck[sel].id % 2 != p.type);

        addCard(p, deck[sel]);
    }
}

/* GameLoop function declerations */
void showCard(card c);
void showHand(player p);

void gameLoop(player &player1, player &player2) {
    dealCard(player1, 5);
    dealCard(player2, 5);
    cout << "Game has started!\n";

    player cur = player1.type == 0 ? player1 : player2;
    int curPlayerID = player1.type == 0 ? 1 : 2;
    int roundCounter = 1;

    string input;
    while(1) {
        cout << "It's " << cur.name << "'s turn." << endl;
        showHand(cur);

        cout << "Waiting for your actions...\n";
        cin >> input;

        if(curPlayerID == 1) {
            player1 = cur;
            curPlayerID = 2;
            cur = player2;
        }else {
            player2 = cur;
            curPlayerID = 1;
            cur = player1;
        }
        cout << "Round " << roundCounter << " finished.\n";
        roundCounter++;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }// while
}

/* GameLoop specific functions */

// prints information about a card
#include <sstream>
void showCard(card c) {
    stringstream buffer;
    buffer << c.name << " (" << c.id << ")";
    string out = buffer.str();
    out.append(40 - out.length(), ' ');
    cout << out << "| " << c.desc << endl;
}

// prints a player's hand
void showHand(player p) {
    for(int i=0; i<p.handCount; i++)
        showCard(p.hand[i]);
}