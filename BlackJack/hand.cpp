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
#include "./hand.h"
#include "./header.h"
#include "./deck.h"

void Hand::draw_from_deck(Deck& deck) {
    cards.push_back(deck.draw_card());
    sum_hand();
}

int Hand::get_value() const {
    return value;
}

void Hand::sum_hand() {
    value = 0;
    for (Card c : cards) {
        value += c.value;
    }
    if (aceLow == true) {
        value -= 10;
    }
    bust = (value >= BUST);
}

bool Hand::check_for_ace() {
    for (Card c : cards) {
        if (c.rank == "Ace") {
            return true;
        }
    }
    return false;
}

/*
    -If the dealer's hand has value 16 or less --> HIT
    -If the Dealer's hand value is 17 and they have an ace --> HIT
*/
void Hand::dealer_hit(Deck& deck, Hand& dealerHand) {
    if (dealerHand.value <= 16) {
        dealerHand.draw_from_deck(deck);
        std:: cout << "-->Dealer hit." << std::endl;
    }
    if (dealerHand.value == 17) {
        dealerHand.aceLow = true;
        dealerHand.draw_from_deck(deck);
        std:: cout << "-->Dealer hit on soft 17." << std::endl;
    }
}

void Hand::print_hand() {
    for (Card c : cards) {
        std::cout << "  -" << c.rank << " of " << c.suit << std::endl;
    }
}

void Hand::ace_high_or_low() {
    char choice;
    while(1) {
        std::cout << "Ace [H]igh or [L]ow?" << std::endl;
        std::cout << ">";
        std::cin >> choice;
        choice = toupper(choice);
        if (choice == 'H'){
            break;
        } else if (choice == 'L') {
            aceLow = true;
            break;
        }
    }
}