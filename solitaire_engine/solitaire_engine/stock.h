#pragma once
#include "card_pile.h"

class Stock : public CardPile
{
private:
	decltype(std::default_random_engine()) rand_eng;
public:
	Stock();

	// push a card to the stock and flip it face down
	void push(Card* card) override;

	// shuffle all cards in the stock
	void shuffle();

	// returns false if there were not enough cards in the deck to successfully draw_three, true if draw_three succeeded
	const bool draw_three(CardPile& target_pile);

	// returns the number of cards in the stock
	const int count() const;

	// print all cards in the stock (debugging purposes only)
	void print() const;

	~Stock();
};

