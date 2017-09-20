#include "stock.h"


Stock::Stock() {

}

void Stock::push(Card* card) {
	card->flip(false);
	pile.push_back(card);
}

void Stock::shuffle() {
	std::shuffle(std::begin(pile), std::end(pile), rand_eng);
}

const bool Stock::draw_three(CardPile& target_pile) {
	if (pile.size() < 3)
		return false;
	for (int i = 0; i < 3; i++) {
		Card* card = pile.back();
		pile.pop_back();
		target_pile.push(card);
	}
	return true;
}

const bool Stock::draw(CardPile& target_pile, const bool face_up) {
	if (pile.size() < 1)
		return false;
	Card* card = pile.back();
	pile.pop_back();
	card->flip(face_up);
	target_pile.push(card);
	return true;
}

const int Stock::count() const {
	return pile.size();
}

void Stock::print() const {
	for (Card* card : pile) {
		std::cout << "Stock: " << *card << std::endl;
	}
}


Stock::~Stock() {

}
