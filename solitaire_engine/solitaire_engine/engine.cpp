#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
	for (int i = 0; i < NUM_CARDS; i++) {
		rank_t rank = i % NUM_CARDS_IN_SUIT;
		suit_t suit = i / NUM_CARDS_IN_SUIT;
		stock.push(new Card(suit, rank));
	}
	stock.shuffle();
	stock.print();
}


Engine::~Engine() {

}
