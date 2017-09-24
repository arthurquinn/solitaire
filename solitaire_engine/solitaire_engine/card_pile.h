#pragma once
#include "card.h"

typedef std::vector<Card*> pile_t;

class CardPile
{
private:
  bool active;

protected:
  CardPile();
  ~CardPile();
  pile_t pile;

public:
  virtual const std::string push(Card* card);
  virtual const std::string push(CardPile* card_pile);

  const std::vector<Card*> pop(CardPile& card_pile, const unsigned int amount);
  const pile_t get_pile();
  const unsigned int get_pile_size();

  const bool is_active();
  void set_active(const bool value);
};
