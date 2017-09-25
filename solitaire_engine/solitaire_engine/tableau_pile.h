#pragma once
#include "card_pile.h"

class TableauPile : public CardPile
{
private:
  unsigned int src_idx;

public:
  TableauPile();
  ~TableauPile();

  // push a single card onto the tableau pile (it is not flipped when pushed)
  const std::string push(Card* card) override;

  // push a card pile (not flipped)
  const std::string push(pile_t cards) override;

  // pop cards and flip
  const std::string pop(const unsigned int amount) override;

  // Get pile starting from an index number
  pile_t get_sub_pile();

  // Update source index for tableau
  const void update_src_idx(const unsigned int idx);

  // Get the source index
  const unsigned int get_src_idx();

  // print a tableau
  void print(const int tableau_num) const;
};
