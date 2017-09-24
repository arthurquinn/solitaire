#pragma once
#include "card_pile.h"

class FoundationPile : public CardPile
{
public:
  FoundationPile();
  ~FoundationPile();

  const std::string push(Card* card) override;
  const std::string push(CardPile* card_pile) override;
};
