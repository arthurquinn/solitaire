#pragma once
#include "card_pile.h"

class TableauPile : public CardPile
{
public:
  TableauPile();

  // push a single card onto the tableau pile (it is not flipped when pushed)
  const bool push(Card* card) override;

  // Get pile starting from an index number
  pile_t get_pile(const unsigned short index);

  // print a tableau
  void print(const int tableau_num) const;

  ~TableauPile();
};
