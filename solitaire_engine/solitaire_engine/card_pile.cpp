#include "stdafx.h"
#include "card_pile.h"


CardPile::CardPile() {

}

void CardPile::push(Card* card) {
  throw new std::exception("CardPile.push() not implemented");
}

void CardPile::set_active(const bool value) {
  active = value;
}

bool CardPile::is_active() const {
  return active;
}

CardPile::~CardPile() {

}
