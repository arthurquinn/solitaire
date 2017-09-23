#pragma once
#include "card_pile.h"

class Stock : public CardPile
{
private:
  decltype(std::default_random_engine()) rand_eng;
public:
  Stock();

  // push a card to the stock and flip it face down
  const bool push(Card* card) override;

  // shuffle all cards in the stock
  void shuffle();

  // returns false if there were not enough cards in the deck to successfully draw_three, true if draw_three succeeded
  const bool draw_three(CardPile& target_pile);

  // draw a single card from the stock and specify whether or not it is a face_up or face_down draw
  // returns true if the stock has a card and the draw succeeds, false otherwise 
  const bool draw(CardPile& target_pile, const bool face_up);

  // returns the number of cards in the stock
  const int count() const;

  // print all cards in the stock (debugging purposes only)
  void print() const;

  ~Stock();
};

