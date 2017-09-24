#include "stdafx.h"
#include "stock.h"

Stock::Stock() {

}

Stock::~Stock() {

}

const std::string Stock::push(Card* card) {
  card->flip(false);
  pile.push_back(card);
  return NO_REASON;
}

const std::string Stock::push(CardPile* card_pile) {
  return ERROR_TAG + std::string("Cannot push to the stock pile.");
}

void Stock::shuffle() {
  std::shuffle(std::begin(pile), std::end(pile), rand_eng);
}

const std::string Stock::draw_three(CardPile& target_pile) {
  std::string response = "";
  const unsigned int size = pile.size();

  if (size >= 3) {
    for (unsigned int i = 0; i < 3; i++) {
      Card* card = pile.back();
      card->flip(true);
      pile.pop_back();
      target_pile.push(card);

      response += std::string(card->as_str());
      if (i != size - 1) {
        response += ",";
      }
    }
  }
  else if(size == 0 && target_pile.pile_size() > 0) {
    response = reset(target_pile);
  }
  else {
    response = ERROR_TAG + std::string("No cards left to draw.");
  }

  return response;
}

const std::string Stock::draw(CardPile& target_pile, const bool face_up) {
  std::string response = NO_REASON;
  const unsigned int size = pile.size();

  if (size > 0) {
    Card* card = pile.back();
    pile.pop_back();
    card->flip(face_up);
    target_pile.push(card);
    response = std::string(card->as_str());
  }
  else if (size == 0 && target_pile.pile_size() > 0) {
    response = reset(target_pile);
  }
  else {
    response = ERROR_TAG + std::string("No cards left to draw.");
  }

  return response;
}

const std::string Stock::reset(CardPile& target_pile) {
  std::string response = "";
  Talon& talon = static_cast<Talon&>(target_pile);
  std::vector<Card*> cards = pop(talon, talon.pile_size());
  const unsigned int size = cards.size();

  for (unsigned int i = 0; i < size; i++) {
    Card* card = cards.at(i);
    card->flip(false);
    pile.push_back(card);

    response += std::string(card->as_str());
    if (i != size - 1) {
      response += ",";
    }
  }

  return response;
}

const int Stock::count() const {
  return pile.size();
}

void Stock::print() const {
  for (Card* card : pile) {
    std::cout << "Stock: " << *card << std::endl;
  }
}
