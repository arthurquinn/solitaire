#pragma once
#include "card_pile.h"
#include "talon.h"
#include "tableau_pile.h"

class FoundationPile : public CardPile
{
public:
  FoundationPile();
  ~FoundationPile();

  const std::string push(Card* card) override;
  const std::string push(CardPile* card_pile) override;
  pile_t get_cards(CardPile* card_pile);
};
