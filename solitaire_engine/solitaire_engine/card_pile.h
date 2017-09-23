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
	virtual void push(Card* card);
  bool is_active() const;
  void set_active(const bool value);
};
