#pragma once
#include "stock.h"
#include "talon.h"
#include "foundation_pile.h"
#include "tableau_pile.h"
#include "command_result.h"
#include "command.h"

class Engine
{
private:
  Stock stock;
  Talon talon;
  FoundationPile foundation[NUM_FOUNDATION_PILES];
  TableauPile tableau[NUM_TABLEAU_PILES];

  const pile_t get_source_cards(PileType& src, unsigned short tcard_index);
  const bool move_to_foundation(pile_t& src, PileType& dest);
  const bool move_to_tableau(pile_t& src, PileType& dest);

public:
  Engine();
  ~Engine();
  void init();
  void deal();
  void activate_piles(const bool active);
  const CommandResult run(const Command& cmd);
};
