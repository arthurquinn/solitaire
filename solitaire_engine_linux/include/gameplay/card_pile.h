#pragma once
#include "card.h"

typedef std::vector<Card*> pile_t;

class CardPile
{
protected:
  CardPile();
  ~CardPile();
  pile_t pile;

public:
  virtual const void push(Card* card);
  virtual const std::string push(const pile_t cards);
  virtual const std::string pop(const size_t amount);
  virtual const std::string is_valid(const pile_t cards) const;

  const pile_t get_pile() const;
  const size_t get_pile_size() const;
};
