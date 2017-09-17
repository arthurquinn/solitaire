#pragma once
#include "card.h"
#include "constants.h"

class Deck
{
private:
	decltype(std::default_random_engine()) rand_eng;
	std::vector<Card*> cards;
public:
	Deck();
	void shuffle();
	void print();
	~Deck();
};

