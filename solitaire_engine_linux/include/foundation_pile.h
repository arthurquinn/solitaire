#pragma once
#include "card_pile.h"

class FoundationPile : public CardPile
{
public:
  FoundationPile();
  ~FoundationPile();

  const std::string push(Card* card) override;
  const std::string push(pile_t cards) override;
  const int count() const;
};
