#include "stdafx.h"
#include "talon.h"


Talon::Talon() {
}

void Talon::push(Card* card) {
  card->flip(true);
  pile.push_back(card);
}

Talon::~Talon() {

}
