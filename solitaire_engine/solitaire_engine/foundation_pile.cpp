#include "stdafx.h"
#include "foundation_pile.h"


FoundationPile::FoundationPile() {

}

const bool FoundationPile::push(Card* card) {
  bool is_valid = false;

  if (is_active()) {
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool is_empty_and_ace = pile_card == NULL && card->get_rank() == 0;
    bool is_valid_move = pile_card != NULL && pile_card->is_same_suit(card) && !pile_card->is_opposite_color(card) && !pile_card->is_rank_lower(card);

    if (is_empty_and_ace || is_valid_move) {
      pile.push_back(card);
      is_valid = true;
    }
  } else {
    pile.push_back(card);
    is_valid = true;
  }

  return is_valid;
}

FoundationPile::~FoundationPile() {

}
