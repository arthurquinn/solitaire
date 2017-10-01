#pragma once
#include "stock.h"
#include "talon.h"
#include "foundation_pile.h"
#include "tableau_pile.h"
#include "communication/command_result.h"
#include "communication/command.h"
#include "utilities/utility.h"

#define _foundation_full(x) foundation[x].count() == 13
#define _is_win _foundation_full(SPADES) && \
                _foundation_full(CLUBS) && \
                _foundation_full(HEARTS) && \
                _foundation_full(DIAMONDS)

template<typename T, std::size_t N>
constexpr std::size_t size(T(&)[N]) { return N; }

class Engine
{
private:
  Stock stock;
  Talon talon;
  FoundationPile foundation[NUM_FOUNDATION_PILES];
  TableauPile tableau[NUM_TABLEAU_PILES];

  CommandResult draw(const std::string method);
  CommandResult move(const Command& cmd);
  CardPile* get_src_pile(const size_t src, const size_t src_idx);
  CardPile* get_dest_pile(const size_t dest);
  pile_t get_cards(CardPile* card_pile) const;
  CommandResult get_command_result(const size_t dest_pile_num, const std::string dest_response, const size_t src_pile_num, const std::string src_response) const;
  CommandResult get_deal_command_result() const;

public:
  Engine();
  ~Engine();
  const void init();
  CommandResult deal();

  CommandResult run(const Command& cmd);
  const bool check() const;
};
