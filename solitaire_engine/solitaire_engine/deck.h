#pragma once
#include "card.h"
#include "constants.h"

class Deck
{
private:
	decltype(std::default_random_engine()) rand_eng;
	Card * cards[NUM_CARDS];
public:
	Deck();
	void shuffle();
	void print();
	~Deck();
};

