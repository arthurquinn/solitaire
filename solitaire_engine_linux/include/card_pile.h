#include <stdio.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>
#include <iostream>
#include <vector>
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

