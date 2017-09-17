#pragma once
#include "card.h"

typedef std::vector<Card*> pile_t;

class CardPile
{
private:
	pile_t pile;
public:
	CardPile();
	~CardPile();
};

