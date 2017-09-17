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
	~Engine();
};

