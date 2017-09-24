#pragma once
#include "card_pile.h"
#include "talon.h"
#include "tableau_pile.h"

class Stock : public CardPile
{
private:
  decltype(std::default_random_engine()) rand_eng;
public:
  Stock();

  // push a card to the stock and flip it face down
  const std::string push(Card* card) override;

  // push a card pile to stock
  const std::string push(CardPile* card_pile) override;

  // shuffle all cards in the stock
  void shuffle();

  // returns false if there were not enough cards in the deck to successfully draw_three, true if draw_three succeeded
  const std::string draw_three(CardPile& target_pile);

  // draw a single card from the stock and specify whether or not it is a face_up or face_down draw
  // returns true if the stock has a card and the draw succeeds, false otherwise 
  const std::string draw(CardPile& target_pile, const bool face_up);

  // reset the stock pile when no cards left and cards in talon
  const std::string reset(CardPile& target_pile);

  // returns the number of cards in the stock
  const int count() const;

  // print all cards in the stock (debugging purposes only)
  void print() const;

  ~Stock();
};

