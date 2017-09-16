#pragma once
#include "card.h"

#define NUM_CARDS 52

class Deck
{
private:
	decltype(std::default_random_engine()) rand_eng;
	Card * cards[NUM_CARDS];
public:
	Deck();
	void shuffle();
	~Deck();
};

