#include "stdafx.h"
#include "talon.h"


Talon::Talon() {
}

const bool Talon::push(Card* card) {
  card->flip(true);
  pile.push_back(card);
  return true;
}

Talon::~Talon() {

}
