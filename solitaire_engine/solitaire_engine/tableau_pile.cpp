#include "stdafx.h"
#include "tableau_pile.h"

TableauPile::TableauPile() {

}

void TableauPile::push(Card* card) {
  if (is_active()) {
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool isEmptyAndKing = pile_card == NULL && card->get_rank() == 12;
    bool isValidMove = pile_card != NULL && pile_card->isOppositeColor(card) && pile_card->isRankLower(card);

    if (isEmptyAndKing || isValidMove) {
      pile.push_back(card);
    }
  } else {
    pile.push_back(card);
  }
}

void TableauPile::print(const int tableau_num) const {
	for (Card* card : pile) {
		std::cout << "Tableau" << tableau_num << ": " << *card << ", FaceUp: " << card->is_visible() << std::endl;
	}
}

TableauPile::~TableauPile() {

}
