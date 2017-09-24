#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

Engine::~Engine() {

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

  /*std::cout << "Deal Result:" << std::endl;
  for (int i = 0; i < NUM_TABLEAU_PILES; i++) {
    tableau[i].print(i);
  }
  stock.print();*/

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

CommandResult* Engine::run(Command& cmd) {
  const std::string method = cmd.get_method();

  if (method == DRAW_ONE || method == DRAW_THREE) {
    return draw(method);
  }
  else if (method == MOVE) {
    return move(cmd);      
  }

  return get_command_result(NULL, NULL, ERROR_TAG + std::string("Invalid command"));
}

/*\ // =================================
|*|
|*|     Gameplay functions
|*|
\*/ // =================================

CommandResult* Engine::draw(const std::string method) {
  std::string response;

  if (method == DRAW_ONE) {
    response = stock.draw(talon, true);
  }
  else if (method == DRAW_THREE) {
    response = stock.draw_three(talon);
  }

  return get_command_result(TALON, STOCK, response);
}

CommandResult* Engine::move(Command& cmd) {
  const int src = cmd.get_src();
  const int dest = cmd.get_dest();
  std::string retval = ERROR_TAG;

  if (src != dest) {
    const int src_idx = cmd.get_src_idx();
    CardPile* dest_pile = get_dest_pile(dest);
    CardPile* src_pile = get_src_pile(src, src_idx);

    if (src_pile != NULL && dest_pile != NULL) {
      retval = dest_pile->push(src_pile);
    }
    else {
      retval += "Invalid source or destination.";
    }
  }
  else {
    retval += "Source and destination cannot be the same.";
  }

  return get_command_result(dest, src, retval);
}

/*\ // =================================
|*|
|*|     Helper functions
|*|
\*/ // =================================

CommandResult* Engine::get_command_result(const unsigned int dest_pile_num, const unsigned int src_pile_num, const std::string response) {
  const bool status = response.find(ERROR_TAG) == std::string::npos;
  std::string reason = status ? NO_REASON : response.substr(7);
  std::vector<const char*> push_items;

  std::cout << response << std::endl;

  // Create command result with fields
  CommandResult* cr = new CommandResult(status, reason);

  // Update the fields
  if (status) {
    // TODO: Fix this function returning garbage
    push_items = Utility::split(response, ',');

    for (const char* card : push_items) {
      cr->update_push(dest_pile_num, card);
    }

    cr->update_pop(src_pile_num, push_items.size());
  }

  return cr;
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
