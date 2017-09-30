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
  const void push(Card* card) override;

  // push a card pile (not flipped)
  const std::string push(const pile_t cards) override;

  // pop cards and flip
  const std::string pop(const size_t amount) override;

  // check if cards are valid
  const std::string is_valid(const pile_t cards) const override;

  // Get pile starting from an index number
  pile_t get_sub_pile();

  // Update source index for tableau
  const void update_src_idx(const size_t idx);

  // Get the source index
  const size_t get_src_idx();

  // print a tableau
  const void print(const size_t tableau_num) const;
};
