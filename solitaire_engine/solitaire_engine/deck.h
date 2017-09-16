#pragma once
#include "card.h"

#define NUM_CARDS 52

class Deck
{
private:
	Card * cards[NUM_CARDS];
public:
	Deck();
	void shuffle();
	~Deck();
};

