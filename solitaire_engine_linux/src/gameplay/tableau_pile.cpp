#include "stdafx.h"
#include "gameplay/tableau_pile.h"

TableauPile::TableauPile() { 
  src_idx = 0; 
}

TableauPile::~TableauPile() {

}

const void TableauPile::push(Card* card) {
  pile.push_back(card);
}

const std::string TableauPile::push(const pile_t cards) {
  std::string response = is_valid(cards);
  const size_t size = cards.size();

  if(response.find(ERROR_TAG) == std::string::npos) {
    for(size_t i = 0; i < size; i++) {
      push(cards.at(i));
    }
  }

  return response;
}

const std::string TableauPile::is_valid(const pile_t cards) const {
  std::string response = EMPTY_RESPONSE;
  const size_t size = cards.size();

  if (size == 0) {
    response = ERROR_TAG + std::string("No cards selected.");
  }

  for (size_t i = 0; i < size; i++) {
    Card* card = cards.at(i);
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool isEmptyAndKing = pile_card == NULL && card->get_rank() == 12;
    bool isValidMove = pile_card != NULL && pile_card->is_opposite_color(*card) && pile_card->is_rank_lower(*card);

    if (isEmptyAndKing || isValidMove) {
      response += std::string(card->as_str());
      response += (i != size-1) ? "," : "";
    }
    else if (pile_card == NULL) {
      response = ERROR_TAG + std::string("You can only place a King in an empty position.");
    }
    else {
      response = ERROR_TAG + std::string(card->as_str()) + " is not the opposite color or rank is higher.";
    }
  }

  return response;
}

const std::string TableauPile::pop(const size_t amount) {
  std::string response = CardPile::pop(amount);

  if (this->pile.size() > 0) {
    Card* card = this->pile.back();
    card->flip(true);
    response = std::string(card->as_str());
  }

  return response;
}

pile_t TableauPile::get_sub_pile() {
  pile_t cards = this->pile;

  if (this->src_idx > 0) {
    pile_t sub_pile;
    size_t size = cards.size();

    for (size_t i = this->src_idx; i < size; i++) {
      sub_pile.push_back(cards.at(i));
    }

    return sub_pile;
  }

  return cards;
}

const void TableauPile::update_src_idx(const size_t idx) {
  src_idx = idx;
}

const size_t TableauPile::get_src_idx() {
  return src_idx;
}

const void TableauPile::print(const size_t tableau_num) const {
  for (Card* card : pile) {
    std::cout << "Tableau" << tableau_num << ": " << *card << ", FaceUp: " << card->is_visible() << std::endl;
  }
}
