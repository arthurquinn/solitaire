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
}

void Engine::deal() {
	for (int i = 0; i < NUM_TABLEAU_PILES; i++) {
		for (int j = i; j < NUM_TABLEAU_PILES; j++) {
			stock.draw(tableau[j], i == j);
		}
	}

	std::cout << "Deal Result:" << std::endl;

	for (int i = 0; i < NUM_TABLEAU_PILES; i++) {
		tableau[i].print(i);
	}

	stock.print();
}


Engine::~Engine() {

}
