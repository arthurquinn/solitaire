#include "stdafx.h"
#include "deck.h"


Deck::Deck() {
	rand_eng.seed(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < NUM_CARDS; i++) {
		rank_t rank = i % NUM_CARDS_IN_SUIT;
		suit_t suit = i / NUM_CARDS_IN_SUIT;
		cards[i] = new Card(suit, rank);
	}
}

void Deck::shuffle() {
	std::shuffle(std::begin(cards), std::end(cards), rand_eng);
}

void Deck::print() {
	for (int i = 0; i < NUM_CARDS; i++) {
		Card card = *cards[i];
		std::cout << card << std::endl;
	}
}

Deck::~Deck() {
	for (int i = 0; i < NUM_CARDS; i++) {
		delete cards[i];
	}
}
