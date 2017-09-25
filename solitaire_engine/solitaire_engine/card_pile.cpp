#include "stdafx.h"
#include "card_pile.h"

CardPile::CardPile() {

}

const std::string CardPile::push(Card* card) {
  throw new std::exception("CardPile.push() not implemented");
}

const std::string CardPile::push(pile_t cards) {
  throw new std::exception("CardPile.push() not implemented");
}

const std::string CardPile::pop(const unsigned int amount) {
  std::vector<Card*> cards;
  std::string response = EMPTY_LIST;

  for (unsigned int i = 0; i < amount; i++) {
    Card* card = this->pile.back();
    cards.push_back(card);
    this->pile.pop_back();
  }

  return response;
}

const pile_t CardPile::get_pile() {
  return pile;
}

const unsigned int CardPile::get_pile_size() {
  return pile.size();
}

void CardPile::set_active(const bool value) {
  active = value;
}

const bool CardPile::is_active() {
  return active;
}

CardPile::~CardPile() {

}
