/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include "./header.h"

extern const char* suits[SUITS];
extern const char* ranks[RANKS];

class Deck {
 public:
    std::vector<Card> cards;

    Deck();
    struct Card draw_card();
    void shuffle_deck();
    void print_deck() const;
};

#endif  // _DECK_H_
