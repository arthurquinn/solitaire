#include "stdafx.h"
#include "gameplay/card_pile.h"

CardPile::CardPile() {}

const void CardPile::push(Card* card) {}

const std::string CardPile::push(const pile_t cards) {}

const std::string CardPile::is_valid(const pile_t cards) const {}

const std::string CardPile::pop(const size_t amount) {
  for (unsigned int i = 0; i < amount; i++) {
    this->pile.pop_back();
  }

  return EMPTY_RESPONSE;
}

const pile_t CardPile::get_pile() const {
  return pile;
}

const size_t CardPile::get_pile_size() const {
  return pile.size();
}

CardPile::~CardPile() {}
