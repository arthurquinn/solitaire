#pragma once
#include "card_pile.h"

class Talon : public CardPile
{
public:
  Talon();

  // push a card onto the talon and flip it face up
  const std::string push(Card* card) override;

  // push a card pile to the talon pile
  const std::string push(CardPile* card_pile) override;

  ~Talon();
};
