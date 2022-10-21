#include <iostream>
#include <string.h>
using namespace std;

#define CMDCOUNT 3

string cmds[CMDCOUNT][2] = {{"quit", "Quits the game.\n"},
                            {"help", "Displays the help message.\n"},
                            {"start", "Starts the game.\n"}};

void greeter() {
    cout << "Welcome to Microbial Storm, the two-player adversarial strategy card game based on the microbial world!\nTo start the game, type \"start\" and hit enter, or type \"help\" for more commands.\n";
}

void quit() {
    cout << "Thanks for playing!\n";
}

void help() {
    for(int i=0; i<CMDCOUNT; i++) cout << cmds[i][0] << " - " << cmds[i][1];
}

void start() {
    cout << "Starting!";
    
}

int main() {
    string input;
    greeter();
    while(cin >> input) {
        if(input == "quit") {
            quit();
            return 0;
        }else if(input == "help") {
            help();
        }else if(input == "start") {
            start();
        }else {
            cout << "Command not recognised, type \"help\" for a list of commands.\n";
        }
    }
    return 0;
}