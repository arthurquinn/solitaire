#include "stdafx.h"
#include "card_pile.h"


CardPile::CardPile() {

}

const std::string CardPile::push(Card* card) {
  throw new std::exception("CardPile.push() not implemented");
}

const std::string CardPile::push(CardPile* card_pile) {
  throw new std::exception("CardPile.push() not implemented");
}

const std::vector<Card*> CardPile::pop(CardPile& card_pile, const unsigned int amount) {
  std::vector<Card*> cards;

  for (unsigned int i = 0; i < amount; i++) {
    cards.push_back(card_pile.pile.back());
    card_pile.pile.pop_back();
  }

  return cards;
}

const unsigned int CardPile::pile_size() {
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
