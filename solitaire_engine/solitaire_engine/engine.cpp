#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
  for (int i = 0; i < NUM_CARDS; i++) {
    rank_t rank = i % NUM_CARDS_IN_SUIT;
    suit_t suit = i / NUM_CARDS_IN_SUIT;
    stock.push(new Card(suit, rank, suit == CLUBS || suit == SPADES));
  }
  stock.shuffle();
}

void Engine::deal() {
  activate_piles(false);

  for (int i = 0; i < NUM_TABLEAU_PILES; i++) {
    for (int j = i; j < NUM_TABLEAU_PILES; j++) {
      stock.draw(tableau[j], i == j);
    }
  }

  std::cout << "Deal Result:" << std::endl;

  for (int i = 0; i < NUM_TABLEAU_PILES; i++) {
    tableau[i].print(i);
  }

  stock.print();
  activate_piles(true);
}

void Engine::activate_piles(const bool active) {
  for (int i = 0; i < NUM_TABLEAU_PILES; i++) {
    tableau[i].set_active(active);
  }

  for (int i = 0; i < NUM_FOUNDATION_PILES; i++) {
    foundation[i].set_active(active);
  }
}

/*void Engine::move(Command& cmd) {
  std::string action = cmd.get_command();

  if (action == DRAW_ONE) {
    stock.draw(talon, true);
  } 
  else if(action == DRAW_THREE) {
    stock.draw_three(talon);
  } 
  else if(action == MOVE) {
    // Get command details
    PileType src = cmd.get_source();
    PileType dest = cmd.get_destination();

    if(src != dest) {
      // Get index of card in tableau pile (as it can be a group of cards)
      unsigned short tcard_index = cmd.get_tcard_index();

      // Get the source cards
      pile_t source_cards = get_source_cards(src, tcard_index);

      // Attempt to move to correct destination
      if (dest >= PileType::foundation && dest < PileType::tableau) {
        move_to_foundation(source_cards, dest);
      }
      else if (dest >= PileType::tableau && static_cast<int>(dest) < LAST_PILE_INDEX) {
        move_to_tableau(source_cards, dest);
      }
    }
  }
}*/

/*\ // =================================
|*|
|*|     A beautiful comment
|*|
\*/ // =================================

const pile_t Engine::get_source_cards(PileType& src, unsigned short tcard_index) {
  pile_t cards;

  switch (src) {
    case PileType::talon: {
      pile_t& pile = talon.get_pile();
      if (talon.get_pile().size() > 0) {
        cards.push_back(pile.back());
      }
    }
    break;

    case PileType::foundation: {
      pile_t& pile = foundation[static_cast<int>(src)].get_pile();
      if (pile.size() > 0) {
        cards.push_back(pile.back());
      }
    }
    break;

    case PileType::tableau: {
      pile_t& pile = tableau[static_cast<int>(src)].get_pile(tcard_index);
    }
    break;
  }

  return cards;
}

const bool Engine::move_to_foundation(pile_t& src, PileType& dest) {
  CardPile& dest_pile = foundation[static_cast<int>(dest)];
  bool is_valid_move = src.size() == 1 && dest_pile.push(src.back());

  if (is_valid_move) {
    src.pop_back();

    if (src.size() > 0 && !src.back()->is_visible()) {
      src.back()->flip(true);
    }
  }

  return is_valid_move;
}

const bool Engine::move_to_tableau(pile_t& src, PileType& dest) {
  bool is_valid_move = true;
  CardPile& dest_pile = tableau[static_cast<int>(dest)];

  // Add group of cards from tableau pile to destination pile
  for(unsigned int i = 0; i < src.size() && is_valid_move; i++) {
    is_valid_move &= dest_pile.push(src.at(i));
  }

  if (is_valid_move) {
    // Pop all the cards from source pile
    for (unsigned int i = 0; i < src.size(); i++) {
      src.pop_back();
    }

    // Flip last card in source pile, if possible
    if (src.size() > 0 && !src.back()->is_visible()) {
      src.back()->flip(true);
    }
  }

  return is_valid_move;
}

Engine::~Engine() {

}
