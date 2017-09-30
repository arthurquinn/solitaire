#pragma once
#include "card_pile.h"

class FoundationPile : public CardPile
{
public:
  FoundationPile();
  ~FoundationPile();

  const void push(Card* card) override;
  const std::string push(const pile_t cards) override;
  const std::string is_valid(const pile_t cards) const override;
  const int count() const;
};
