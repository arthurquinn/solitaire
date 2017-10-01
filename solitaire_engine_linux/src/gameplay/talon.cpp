#include "stdafx.h"
#include "gameplay/talon.h"

Talon::Talon() {}

const void Talon::push(Card* card) {
  card->flip(true);
  pile.push_back(card);
}

Talon::~Talon() {}
