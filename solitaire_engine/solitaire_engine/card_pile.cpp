#include "stdafx.h"
#include "card_pile.h"


CardPile::CardPile() {

}

const bool CardPile::push(Card* card) {
  throw new std::exception("CardPile.push() not implemented");
}

void CardPile::set_active(const bool value) {
  active = value;
}

const bool CardPile::is_active() {
  return active;
}

pile_t CardPile::get_pile() {
  return pile;
}

CardPile::~CardPile() {

}
