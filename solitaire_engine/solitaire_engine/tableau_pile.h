#pragma once
#include "card_pile.h"

class TableauPile : public CardPile
{
public:
  TableauPile();

  // push a single card onto the tableau pile (it is not flipped when pushed)
  void push(Card* card) override;

  // print a tableau
  void print(const int tableau_num) const;

  ~TableauPile();
};
