#pragma once
#include "card_pile.h"

class Talon : public CardPile
{
public:
	Talon();

	// push a card onto the talon and flip it face up
	void push(Card* card) override;

	~Talon();
};

