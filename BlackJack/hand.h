/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#ifndef _HAND_H_
#define _HAND_H_
#include <vector>
#include "./header.h"
#include "./deck.h"

class Hand {
 public:
    std::vector<Card> cards;
    int value;
    bool bust;
    bool aceLow = false;

    void draw_from_deck(Deck& deck);
    void sum_hand();
    bool check_for_ace();
    void dealer_hit(Deck& deck, Hand& dealerHand);
    void print_hand();
    void ace_high_or_low();
    int get_value() const;
};

#endif  // _HAND_H_
