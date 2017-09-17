#pragma once
#include "card.h"
#include "card_pile.h"
#include "constants.h"

class Deck
{
private:
	decltype(std::default_random_engine()) rand_eng;
	std::vector<Card*> cards;
public:
	Deck();
	void shuffle();
	void draw_three(pile_t& target_pile);
	void print() const;
	~Deck();
};

