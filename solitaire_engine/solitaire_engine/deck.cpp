#include "stdafx.h"
#include "deck.h"


Deck::Deck() {
	for (int i = 0; i < NUM_CARDS; i++) {
		cards[i] = new Card();
	}
}

void Deck::shuffle() {

}

Deck::~Deck() {
	for (int i = 0; i < NUM_CARDS; i++) {
		delete cards[i];
	}
}
