#include "stdafx.h"
#include "engine.h"

Engine::Engine() {}
Engine::~Engine() {}

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

CommandResult Engine::run(Command& cmd) {
  const std::string method = cmd.get_method();

  if (method == DRAW) {
    return draw(method);
  }
  else if (method == MOVE) {
    return move(cmd);      
  }

  return CommandResult(false, ERROR_TAG + std::string("Invalid command"));
}

const bool Engine::check() const {
  return _is_win;
}

/*\ // =================================
|*|
|*|     Gameplay functions
|*|
\*/ // =================================

CommandResult Engine::draw(const std::string method) {
  std::vector<std::string> responses = stock.draw_three(talon);

  return get_command_result(TALON, responses.at(0), STOCK, responses.at(1));
}

CommandResult Engine::move(Command& cmd) {
  const int src_pile_num = cmd.get_src();
  const int dest_pile_num = cmd.get_dest();
  std::string dest_response = ERROR_TAG;
  std::string src_response = ERROR_TAG;

  if (src_pile_num != dest_pile_num) {
    const int src_idx = cmd.get_src_idx();
    CardPile* dest_pile = get_dest_pile(dest_pile_num);
    CardPile* src_pile = get_src_pile(src_pile_num, src_idx);

    if (src_pile != NULL && dest_pile != NULL) {
      pile_t src_cards = get_cards(src_pile);
      dest_response = dest_pile->push(src_cards);

      if (dest_response.find(ERROR_TAG) == std::string::npos) {
        src_response = src_pile->pop(src_cards.size());
      }
    }
    else {
      dest_response += "Invalid source or destination.";
    }
  }
  else {
    dest_response += "Source and destination cannot be the same.";
  }

  return get_command_result(dest_pile_num, dest_response, src_pile_num, src_response);
}

/*\ // =================================
|*|
|*|     Helper functions
|*|
\*/ // =================================

CommandResult Engine::get_command_result(const unsigned int dest_pile_num, const std::string dest_response, const unsigned int src_pile_num, const std::string src_response) {
  std::vector<std::string> dest_items;
  std::vector<std::string> src_items;
  const bool status = dest_response.find(ERROR_TAG) == std::string::npos;
  std::string reason = status ? NO_REASON : dest_response.substr(7);
  
  // Create command result with fields
  CommandResult cr(status, reason);

  // Update the fields
  if (status) {
    src_items = Utility::split(src_response, ',');
    dest_items = Utility::split(dest_response, ',');

    for (std::string card : src_items) {
      cr.update_push(src_pile_num, card);
    }
    cr.update_pop(src_pile_num, dest_items.size());

    for (std::string card : dest_items) {
      cr.update_push(dest_pile_num, card);
    }
    cr.update_pop(dest_pile_num, 0);
  }

  return cr;
}

pile_t Engine::get_cards(CardPile* card_pile) {
  pile_t src_pile;

  if (card_pile->get_pile_size() > 0) {
    if (Talon* talon = dynamic_cast<Talon*>(card_pile)) {
      src_pile.push_back(static_cast<Talon*>(card_pile)->get_pile().back());
    }
    else if (TableauPile* tableau = dynamic_cast<TableauPile*>(card_pile)) {
      src_pile = tableau->get_sub_pile();
    }
    else if (FoundationPile* tableau = dynamic_cast<FoundationPile*>(card_pile)) {
      src_pile.push_back(static_cast<FoundationPile*>(card_pile)->get_pile().back());
    }
  }

  return src_pile;
}

CardPile* Engine::get_src_pile(const int src, const int src_idx) {
  if (src == TALON) {
    return &talon;
  }
  else if (src >= FOUNDATION && src <= FOUNDATION_LAST) {
    return &foundation[src - FOUNDATION];
  }
  else if (src >= TABLEAU && src <= TABLEAU_LAST) {
    tableau[src - TABLEAU].update_src_idx(src_idx);
    return &tableau[src - TABLEAU];
  }

  return NULL;
}

CardPile* Engine::get_dest_pile(const int dest) {
  if (dest >= FOUNDATION && dest <= FOUNDATION_LAST) {
    return &foundation[dest - FOUNDATION];
  }
  else if (dest >= TABLEAU && dest <= TABLEAU_LAST) {
    return &tableau[dest - TABLEAU];
  }

  return NULL;
}
