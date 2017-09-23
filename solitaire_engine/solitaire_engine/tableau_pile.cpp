#include "stdafx.h"
#include "tableau_pile.h"

TableauPile::TableauPile() {

}

const bool TableauPile::push(Card* card) {
  bool is_valid = false;

  if (is_active()) {
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool isEmptyAndKing = pile_card == NULL && card->get_rank() == 12;
    bool isValidMove = pile_card != NULL && pile_card->is_opposite_color(card) && pile_card->is_rank_lower(card);

    if (isEmptyAndKing || isValidMove) {
      pile.push_back(card);
      is_valid = true;
    }
   } else {
    pile.push_back(card);
    is_valid = true;
  }

  return is_valid;
}

pile_t TableauPile::get_pile(const unsigned short start_index) {
  pile_t sub_vector;
  size_t last_index = pile.size();

  if (start_index < last_index) {
    sub_vector = pile_t(&pile[start_index], &pile[last_index]);
  }

  return sub_vector;
}

void TableauPile::print(const int tableau_num) const {
  for (Card* card : pile) {
    std::cout << "Tableau" << tableau_num << ": " << *card << ", FaceUp: " << card->is_visible() << std::endl;
  }
}

TableauPile::~TableauPile() {

}
