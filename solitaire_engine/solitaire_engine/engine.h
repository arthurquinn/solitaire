#pragma once
#include "stock.h"
#include "talon.h"
#include "foundation_pile.h"
#include "tableau_pile.h"
#include "command_result.h"
#include "command.h"
#include "utility.h"

#define _foundation_full(x) foundation[x].count() == 13
#define _is_win _foundation_full(SPADES) && \
                _foundation_full(CLUBS) && \
                _foundation_full(HEARTS) && \
                _foundation_full(DIAMONDS)

class Engine
{
private:
  Stock stock;
  Talon talon;
  FoundationPile foundation[NUM_FOUNDATION_PILES];
  TableauPile tableau[NUM_TABLEAU_PILES];

  CommandResult draw(const std::string method);
  CommandResult move(Command& cmd);
  CardPile* get_src_pile(const int src, const int src_idx);
  CardPile* get_dest_pile(const int dest);
  CommandResult get_command_result(const unsigned int dest_pile_num, const unsigned int src_pile_num, const std::string retval);

public:
  Engine();
  ~Engine();
  void init();
  void deal();
  void activate_piles(const bool active);
  CommandResult run(Command& cmd);
  const bool check() const;
};
