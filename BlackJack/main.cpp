/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <fstream>
#include "./header.h"
#include "./deck.h"
#include "./hand.h"

void determine_winner(const Hand& dealerHand, const Hand& playerHand, int bet, int& playerCash) {
    if (playerHand.bust) {
        std::cout << (dealerHand.bust ?
            "No winner - both bust." :
            "You lose due to busting.") << std::endl;
        playerCash -= bet;
    } else if (dealerHand.bust) {
        std::cout << "You win - dealer busted." << std::endl;
        playerCash += bet;
    } else if (dealerHand.get_value() > playerHand.get_value()) {
        std::cout << "Dealer wins." << std::endl;
        playerCash -= bet;
    } else if (dealerHand.get_value() < playerHand.get_value()) {
        std::cout << "You win." << std::endl;
        playerCash += bet;
    } else {
        std::cout << "Tie." << std::endl;
    }
}

void deal_initial_cards(Deck& deck, Hand& playerHand, Hand& dealerHand) {
        playerHand.draw_from_deck(deck);
        dealerHand.draw_from_deck(deck);
        playerHand.draw_from_deck(deck);
}

void hit_or_stay(Deck& deck, Hand& playerHand) {
    char choice;
    while (playerHand.value <= 21) {
        std::cout << std::endl;
        std::cout << "[H]it or [S]tay?" << std::endl;
        std::cout << ">";
        std::cin >> choice;
        choice = toupper(choice);
        if (choice == 'H') {
            playerHand.draw_from_deck(deck);
            std::cout << "Your Hand: " << playerHand.value << std::endl;
            playerHand.print_hand();
            std::cout << std::endl;
        } else if (choice == 'S') {
            std::cout << std::endl;
            return;
        }
    }
}

bool keep_playing() {
    char choice;
    std::cout << "Keep playing? [Y]es or [N]o" << std::endl;
    std::cout << ">";
    std::cin >> choice;
    std::cout << std::endl;
    choice = toupper(choice);
    if (choice == 'Y') {
        return true;
    } else if (choice == 'N') {
        return false;
    }
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear"); // Linux/macOS
    #endif
}

int get_hiscore() {
    std::ifstream file;
    file.open("hiscore.txt");
    if (!file) {
        std::cerr << "Unable to access hiscores." << std::endl;
        exit(1);
    }
    int hiscore;
    file >> hiscore;
    file.close();
    return hiscore;
}

void set_new_hiscore(int hiscore) {
    std::ofstream file;
    file.open("hiscore.txt");
    if (!file) {
        std::cerr << "Unable to access hiscores." << std::endl;
        exit(1);
    }
    file << hiscore;
    file.close();
}

void show_title(int hiscore) {
    clear_screen();
    std::cout << "*********************"  << std::endl;
    std::cout << "*|_ | _  _| . _  _| *" << std::endl;
    std::cout << "*|_)|(_|(_|<|(_|(_|<*" << std::endl;
    std::cout << "*          L|       *" << std::endl;
    std::cout << "*********************" << std::endl << std::endl;
    std::cout << "The current hiscore is $" << hiscore << std::endl;
    std::cout << "Can you beat it?" << std::endl;
    std::cout << "Enter key to continue..." << std::endl;
    system("read");    
}


int main() {
    const int blindBet = 100;
    int playerCash = 1000;
    int bet = 0;
    int hiscore = get_hiscore();

    show_title(hiscore);

    while (1){
        // Instantiate deck and hands
        Deck myDeck;
        Hand playerHand, dealerHand;
        bool dealerHit = false;

        // Clear the previous game and tell the player how much money they have
        clear_screen();
        std::cout << "You have $" << playerCash << std::endl;
        std::cout << "The blind bet is $" << blindBet << std::endl;

        // Deal initial cards
        myDeck.shuffle_deck();
        deal_initial_cards(myDeck, playerHand, dealerHand);

        // Print the player's hand
        std::cout << "Your Hand: " << playerHand.get_value() << std::endl;
        playerHand.print_hand();

        // Show the dealer's up card
        std::cout << "Dealer's Up Card: " << std::endl;
        dealerHand.print_hand();

        // Do ace-related checks
        if (playerHand.check_for_ace()) {
            playerHand.ace_high_or_low();
            playerHand.sum_hand();
            std::cout << "Your Hand: " << playerHand.get_value() << std::endl;
        }

        // Ask the player if they want to hit or stay.
        if (playerHand.get_value() < 21) {
            hit_or_stay(myDeck, playerHand);
        }

        // Ask the player how much they want to bet
        std::cout << "How much do you to bet?" << std::endl;
        std::cout << ">$";
        std::cin >> bet;
        bet += blindBet;
        std::cout << "total bet $" << bet << std::endl;

        // Print the dealer's hand
        std::cout << "Dealer's Hand: " << dealerHand.get_value() << std::endl;
        dealerHand.print_hand();

        // Determine if the dealer will hit
        while (dealerHand.get_value() < 17 ||
               (dealerHand.get_value() == 17 && dealerHand.check_for_ace())) {
        dealerHand.dealer_hit(myDeck, dealerHand);
        dealerHit = true;
        }

        // Re-print the dealer's hand if they hit at least once.
        if(dealerHit) {
            std::cout << "Dealer's Hand: " << dealerHand.get_value() << std::endl;
            dealerHand.print_hand();
            std::cout << std::endl;
        }

        // Determine winner
        determine_winner(dealerHand, playerHand, bet, playerCash);

        // If they are out of money, end the game
        if (playerCash <= 50) {
            std::cout << "You can't make the blind bet." << std::endl;
            break;
        }
        // Ask the player if they want to keep playing
         else if (!keep_playing()) {
            std::cout << "You left with $" << playerCash << std::endl;
            if (playerCash > hiscore) {
                std::cout << "New high score!" << std::endl;
                set_new_hiscore(playerCash);
            }
            break;
        }
    }
    return 0;
}
