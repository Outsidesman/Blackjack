/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "./deck.h"
#include "./header.h"

const char* suits[4] = {
    "Clubs",
    "Diamonds",
    "Hearts",
    "Spades"
};

const char* ranks[13] = {
    "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King", "Ace"
};

Deck::Deck() {
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            struct Card newCard;
            newCard.suit = suits[suit];
            newCard.rank = ranks[rank];
            if (rank <= 7) {
                newCard.value = rank+2;
            } else if (rank >= 8 && rank <=  11) {
                newCard.value = 10;
            } else {
                newCard.value = 11;
            }
            cards.push_back(newCard);
        }
    }
}

Card Deck::draw_card() {
    struct Card drawn_card = cards.back();
    cards.pop_back();

    return drawn_card;
}

void Deck::shuffle_deck() {
    // Seed random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // Shuffle vector
    shuffle(cards.begin(), cards.end(), gen);
}

void Deck::print_deck() const{
    for (size_t i = 0; i < cards.size(); i++){
        printf("%2zu - ", i+1);
        std::cout << cards[i].rank << " of " << cards[i].suit
        << "\t - " << cards[i].value << std::endl;
    }
}
