#include <stdio.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>
#include <iostream>
#include <vector>
#include "card_pile.h"

class TableauPile : public CardPile
{
public:
	TableauPile();

	// push a single card onto the tableau pile (it is not flipped when pushed)
	void push(Card* card) override;

	~TableauPile();
};

