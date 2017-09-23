#pragma once
#include "card_pile.h"

class FoundationPile : public CardPile
{
public:
  FoundationPile();
  ~FoundationPile();

  const bool push(Card* card) override;
};
