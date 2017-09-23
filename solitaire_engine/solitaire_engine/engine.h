#pragma once
#include "stock.h"
#include "talon.h"
#include "foundation_pile.h"
#include "tableau_pile.h"

class Engine
{
private:
	Stock stock;
	Talon talon;
	FoundationPile foundation[NUM_FOUNDATION_PILES];
	TableauPile tableau[NUM_TABLEAU_PILES];
public:
	Engine();
	void init();
	void deal();
	~Engine();
};

