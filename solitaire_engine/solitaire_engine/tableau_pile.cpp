#include "stdafx.h"
#include "tableau_pile.h"


TableauPile::TableauPile() {

}

void TableauPile::push(Card* card) {
	pile.push_back(card);
}

void TableauPile::print(const int tableau_num) const {
	for (Card* card : pile) {
		std::cout << "Tableau" << tableau_num << ": " << *card << ", FaceUp: " << card->is_visible() << std::endl;
	}
}


TableauPile::~TableauPile() {

}
