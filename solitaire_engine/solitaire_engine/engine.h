#pragma once
#include "stock.h"
#include "talon.h"
#include "foundation_pile.h"
#include "tableau_pile.h"

class Engine
{
private:
  Stock stock;
  Talon talon;
  FoundationPile foundation[NUM_FOUNDATION_PILES];
  TableauPile tableau[NUM_TABLEAU_PILES];

public:
  Engine();
  ~Engine();
  void init();
  void deal();
  void activate_piles(const bool active);

  // TODO: Uncomment once Command class is implemented
  //void move(Command cmd);
};
