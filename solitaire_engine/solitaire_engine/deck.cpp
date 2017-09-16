#include "stdafx.h"
#include "deck.h"


Deck::Deck() {
	rand_eng.seed(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < NUM_CARDS; i++) {
		cards[i] = new Card();
	}
}

void Deck::shuffle() {
	std::shuffle(std::begin(cards), std::end(cards), rand_eng);
}

Deck::~Deck() {
	for (int i = 0; i < NUM_CARDS; i++) {
		delete cards[i];
	}
}
