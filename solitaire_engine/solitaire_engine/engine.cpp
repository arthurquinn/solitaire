#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
	deck.shuffle();
	deck.draw_three(draw_pile);
	deck.print();
	print_pile(draw_pile);
}

void Engine::print_pile(const pile_t& pile) const {
	for (Card * card : pile) {
		std::cout << "Draw: " << *card << std::endl;
	}
}


Engine::~Engine() {

}
