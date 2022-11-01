#include "struct.h"

void createCards() {
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