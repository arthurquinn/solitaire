#pragma once
#include "card_pile.h"

class FoundationPile : public CardPile
{
public:
  FoundationPile();
  ~FoundationPile();

  void push(Card* card) override;
};
