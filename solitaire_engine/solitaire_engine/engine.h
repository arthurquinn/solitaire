#pragma once
#include "deck.h"

class Engine
{
private:
	Deck deck;
	pile_t draw_pile;
public:
	Engine();
	void init();
	void print_pile(const pile_t& pile) const;
	~Engine();
};

