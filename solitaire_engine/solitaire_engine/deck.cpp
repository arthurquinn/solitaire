#include "stdafx.h"
#include "deck.h"


Deck::Deck() {
	rand_eng.seed(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < NUM_CARDS; i++) {
		rank_t rank = i % NUM_CARDS_IN_SUIT;
		suit_t suit = i / NUM_CARDS_IN_SUIT;
		cards.push_back(new Card(suit, rank));
	}
}

void Deck::shuffle() {
	std::shuffle(std::begin(cards), std::end(cards), rand_eng);
}

void Deck::draw_three(pile_t& target_pile) {
	if (cards.size() >= 3) {
		for (int i = 0; i < 3; i++) {
			target_pile.push_back(cards.back());
			cards.pop_back();
		}
	} else {
		throw std::length_error("draw three: there are less than three cards remaining in the deck");
	}
}

const int Deck::count() const {
	return cards.size();
}

void Deck::print() const {
	for (Card * card : cards) {
		std::cout << *card << std::endl;
	}
}

Deck::~Deck() {
	for (Card * card : cards) {
		delete card;
	}
}
