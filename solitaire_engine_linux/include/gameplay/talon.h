#pragma once
#include "card_pile.h"

class Talon : public CardPile
{
public:
  Talon();
  ~Talon();

  // push a card onto the talon and flip it face up
  const void push(Card* card) override;
};
