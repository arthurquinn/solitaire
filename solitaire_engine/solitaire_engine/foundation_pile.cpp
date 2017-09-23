#include "stdafx.h"
#include "foundation_pile.h"


FoundationPile::FoundationPile() {

}

void FoundationPile::push(Card* card) {
  if (is_active()) {
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool isEmptyAndAce = pile_card == NULL && card->get_rank() == 0;
    bool isValidMove = pile_card != NULL && pile_card->isSameSuit(card) && !pile_card->isOppositeColor(card) && !pile_card->isRankLower(card);

    if (isEmptyAndAce || isValidMove) {
      pile.push_back(card);
    }
  } else {
    pile.push_back(card);
  }
}

FoundationPile::~FoundationPile() {

}
