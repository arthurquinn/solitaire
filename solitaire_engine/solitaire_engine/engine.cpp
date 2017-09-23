#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
  for (int i = 0; i < NUM_CARDS; i++) {
    rank_t rank = i % NUM_CARDS_IN_SUIT;
    suit_t suit = i / NUM_CARDS_IN_SUIT;
    color_t color = RED;

    if ((i >= 13 && i <= 25) || (i >= 39 && i <= 51)) {
      color = BLACK;
    }

    stock.push(new Card(suit, rank, color));
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

Engine::~Engine() {

}
