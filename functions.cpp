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
    //assert(p.handCount < 6);
    p.hand[p.handCount] = c;
    p.handCount++;
}

/* num: number of cards to deal */
void dealCard(player &p, int num) {
    cout << "Dealing " << num << " cards to " << p.name << endl;
    //assert(p.handCount + num <= 6);

    srand(time(NULL));

    for(int i=0; i<num; i++) {
        int sel;

        do sel = rand() % CARD_COUNT;
        while(deck[sel].id % 2 != p.type);

        addCard(p, deck[sel]);
    }
}

/* GameLoop function declerations */
void showCard(card c, int n);
void showHand(player p);
void playCard(player &p, int cc, card t[], int &tc);

// Main game loop
void gameLoop(player &player1, player &player2) {
    dealCard(player1, 5);
    dealCard(player2, 5);
    cout << "Game has started!\n";

    player microbe;
    player human;
    int roundCounter = 1;

    string input;
    while(1) {
        // End game conditions
        if(player1.health == 0) {
            cout << "===== Game over! =====\n" << player2.name << " wins!\n";
            cout << "Type \"start\" for a new game.\n";
            break;
        }else if(player2.health == 0) {
            cout << "===== Game over! =====\n" << player1.name << " wins!\n";
            cout << "Type \"start\" for a new game.\n";
            break;
        }

        microbe = player1.type == 1 ? player1 : player2;
        human = player1.type == 1 ? player2 : player1;

        // ===Phase 1: microbes===
        // Draw cards to 5
        if(microbe.handCount < 5) dealCard(microbe, 5 - microbe.handCount);

        // announcer
        cout << "It's " << microbe.name << "'s turn." << endl;
        showHand(microbe);

        bool pass = 0;

        // check for playable cards
        bool has_playable_cards = false;
        for(int i=0; i<microbe.handCount; i++)
            if(microbe.hand[i].immune == 0 || microbe.hand[i].type == 'f') has_playable_cards = true;
        if(!has_playable_cards) {
            cout << "You have no playable cards!\n";
            dealCard(microbe, 1);
            pass = 1;
        }

        cout << "Waiting for your actions... to see what is available, type \"help\"\n";
        int m_played_cards_p = 0;
        int m_played_cards_f = 0;
        card m_table[3];
        int m_table_count = 0;

        while(!pass) {
            cin >> input;
            //quit the game
            if(input == "quit") break;

            if(input == "help") {
                cout << "hand - see your hand\nplay [number] - play a card\nviewTable - see what you've played\ndone - finish your turn\n";
            }else if(input == "hand") {
                showHand(microbe);
            }else if(input == "play") {
                int param;
                cin >> param;
                if(param > microbe.handCount - 1 || param < 0) {
                    cout << "Invalid card number, try again.\n";
                    continue;
                }
                if(microbe.hand[param].type == 'p' && m_played_cards_p == 0) {
                    playCard(microbe, param, m_table, m_table_count);
                    m_played_cards_p++;
                    showHand(microbe);
                }else if(microbe.hand[param].type == 'p' && m_played_cards_p > 0) {
                    cout << "You have already played a pathogen card!\n";
                }else if(microbe.hand[param].type == 'f' && m_played_cards_f < 2) {
                    playCard(microbe, param, m_table, m_table_count);
                    m_played_cards_f++;
                    showHand(microbe);
                }else {
                    cout << "You have already played 2 function cards!\n";
                }
            }else if(input == "viewTable") {
                if(m_table_count == 0) cout << "You haven't played any cards yet!\n";
                for(int i=0; i<m_table_count; i++)
                    showCard(m_table[i], i);
            }else if(input == "done") {
                pass = 1;
            }else {
                cout << "Command not recognised, type \"help\" for a list of commands.\n";
            }
        }// while
        if(input == "quit") break;

        this_thread::sleep_for(chrono::milliseconds(500));

        // ===Phase 2: humans===
        // Draw to 5
        if(human.handCount < 5) dealCard(human, 5-human.handCount);

        // announcer
        cout << "It's " << human.name << "'s turn." << endl;
        showHand(human);

        cout << "Waiting for your actions... to see what is available, type \"help\"\n";
        int h_played_cards_a = 0;
        bool h_pass = 0;
        card h_table[10];
        int h_table_count = 0;

        while(!h_pass) {
            cin >> input;
            //quit the game
            if(input == "quit") break;

            if(input == "help") {
                cout << "hand - see your hand\nplay [number] - play a card\nviewTable - see what you've played\nviewOtherTable - see what your opponent has played\ndone - finish your turn\n";
            }else if(input == "hand") {
                showHand(human);
            }else if(input == "play") {
                int param;
                cin >> param;
                if(param > human.handCount - 1 || param < 0) {
                    cout << "Invalid card number, try again.\n";
                    continue;
                }
                if(human.hand[param].type == 'a' && h_played_cards_a == 0) {
                    playCard(human, param, h_table, h_table_count);
                    h_played_cards_a++;
                    showHand(human);
                }else if(human.hand[param].type == 'a' && h_played_cards_a > 0) {
                    cout << "You have already played an offense card!\n";
                }else {
                    playCard(human, param, h_table, h_table_count);
                    showHand(human);
                }
            }else if(input == "viewTable") {
                if(h_table_count == 0) cout << "You haven't played any cards yet!\n";
                for(int i=0; i<h_table_count; i++)
                    showCard(h_table[i], i);
            }else if(input == "viewOtherTable") {
                if(m_table_count == 0) cout << "Your opponent hasn't played any cards!\n";
                for(int i=0; i<m_table_count; i++)
                    showCard(m_table[i], i);
            }else if(input == "done") {
                h_pass = 1;
            }else {
                cout << "Command not recognised, type \"help\" for a list of commands.\n";
            }
        }// while
        if(input == "quit") break;

        this_thread::sleep_for(chrono::milliseconds(500));

        // ===Phase 3: tally===
        cout << "==========MICROBES PLAYED==========\n";
        if(m_table_count == 0) cout << "Nothing.\n";
        for(int i=0; i<m_table_count; i++)
            showCard(m_table[i], i);
        cout << "==========HUMANS PLAYED==========\n";
        if(h_table_count == 0) cout << "Nothing.\n";
        for(int i=0; i<h_table_count; i++)
            showCard(h_table[i], i);

        card pathogen_of_the_round;

        bool canMutate = false;
        float mutateChance = 0;
        for(int i=0; i<m_table_count; i++) {
            if(m_table[i].type == 'p') { // pathogen
                pathogen_of_the_round = m_table[i];
            }else { // function
                switch(m_table[i].id) {
                    case 21:
                        microbe.health++;
                        mutateChance += 1.0 / 6.0;
                        break;
                    case 23:
                        microbe.health++;
                        mutateChance += 1.0 / 3.0;
                        break;
                    case 25:
                        mutateChance += (4.0 - microbe.health) * (1.0 / 3.0);
                        canMutate = true;
                        break;
                }
            }
        }

        // microbes passive
        if(m_played_cards_p + m_played_cards_f == 0) microbe.health--;

        // apply changes and advance
        if(player1.type == 1) {
            player1 = microbe;
            player2 = human;
        }else {
            player1 = human;
            player2 = microbe;
        }
        cout << "Round " << roundCounter << " finished.\n";
        roundCounter++;
        this_thread::sleep_for(chrono::milliseconds(5000));
    }// while
}

/* GameLoop specific functions */

// prints information about a card
#include <sstream>
void showCard(card c, int n) {
    cout << "#" << n << endl;
    stringstream buffer;
    buffer << c.name << " (" << c.id << ")";
    string out = buffer.str();
    out.append(40 - out.length(), ' ');
    cout << out << "| " << c.desc << endl;
}

// prints a player's hand
void showHand(player p) {
    cout << "===========================HANDS============================\n";

    for(int i=0; i<p.handCount; i++)
        showCard(p.hand[i], i);

    // TODO: show if none of the cards can be played.
    cout << "============================================================\n";
}

// plays a card
void playCard(player &p, int cc, card t[], int &tc) {
    t[tc] = p.hand[cc];
    tc++;

    cout << "Played card " << p.hand[cc].name << "!\n";

    for(int i=cc; i<p.handCount - 1; i++)
        p.hand[i] = p.hand[i+1];

    p.handCount--;

    this_thread::sleep_for(chrono::milliseconds(1000));
}