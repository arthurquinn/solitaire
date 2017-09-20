#pragma once
#include "card.h"

typedef std::vector<Card*> pile_t;

class CardPile
{
protected:
	CardPile();
	~CardPile();
	pile_t pile;
public:
	virtual void push(Card* card) = 0;
};

