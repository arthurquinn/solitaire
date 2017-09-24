#include "stdafx.h"
#include "talon.h"


Talon::Talon() {
}

const std::string Talon::push(Card* card) {
  card->flip(true);
  pile.push_back(card);
  return NO_REASON;
}

const std::string Talon::push(CardPile* card_pile) {
  return ERROR_TAG + std::string("Cannot push to the talon pile.");
}

Talon::~Talon() {

}
