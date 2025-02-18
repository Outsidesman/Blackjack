/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#ifndef _HEADER_H_
#define _HEADER_H_

#include<string>

#define SUITS 4
#define RANKS 13
#define BUST  22

struct Card{
    std::string suit;
    std::string rank;
    int value;
};

#endif  // _HEADER_H_
