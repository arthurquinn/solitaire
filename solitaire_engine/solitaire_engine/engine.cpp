#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
	deck.shuffle();
	deck.draw_three(draw_pile);
	deck.print();
	for (Card * card : draw_pile) {
		std::cout << "Draw: " << *card << std::endl;
	}
}


Engine::~Engine() {

}
