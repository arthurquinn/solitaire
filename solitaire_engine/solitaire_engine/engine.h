#pragma once
#include "deck.h"

class Engine
{
private:
	Deck deck;
	pile_t draw_pile;
	pile_t suit_piles[4];
	pile_t board_piles[7];
public:
	Engine();
	void init();
	void print_pile(const pile_t& pile) const;
	~Engine();
};

