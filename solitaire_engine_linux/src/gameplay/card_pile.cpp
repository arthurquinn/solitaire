#include "stdafx.h"
#include "gameplay/card_pile.h"

// Unimplemented methods
CardPile::CardPile() {}
CardPile::~CardPile() {}
const void CardPile::push(Card* card) {}
const std::string CardPile::push(const pile_t cards) {}
const std::string CardPile::is_valid(const pile_t cards) const {}

// Implemented methods
const std::string CardPile::pop(const size_t amount) {
  std::string response = EMPTY_RESPONSE;

  for (unsigned int i = 0; i < amount; i++) {
    this->pile.pop_back();
  }

  return response;
}

const pile_t CardPile::get_pile() const {
  return pile;
}

const size_t CardPile::get_pile_size() const {
  return pile.size();
}
