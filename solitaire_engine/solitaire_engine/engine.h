#pragma once
#include "stock.h"
#include "talon.h"
#include "foundation_pile.h"
#include "tableau_pile.h"

class Engine
{
private:
	CardPile card_piles[13];
public:
	Engine();
	void init();
	void deal();
	~Engine();
};

