#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
	deck.shuffle();
	while (deck.count() >= 3) {
		deck.draw_three(draw_pile);
	}
	print_pile(draw_pile);
}

void Engine::print_pile(const pile_t& pile) const {
	for (Card * card : pile) {
		std::cout << "Draw: " << *card << std::endl;
	}
}


Engine::~Engine() {

}
