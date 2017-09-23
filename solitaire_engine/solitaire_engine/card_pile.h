#pragma once
#include "card.h"

typedef std::vector<Card*> pile_t;
enum class PileType { stock = 0, talon = 1, foundation = 3, tableau = 7 };

class CardPile
{
private:
  bool active;

protected:
  CardPile();
  ~CardPile();
  pile_t pile;

public:
  virtual const bool push(Card* card);
  const bool is_active();
  void set_active(const bool value);
  pile_t get_pile();
};
