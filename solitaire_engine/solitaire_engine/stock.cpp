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

const std::string Stock::push(pile_t cards) {
  return ERROR_TAG + std::string("Cannot push to the stock pile.");
}

void Stock::shuffle() {
  std::shuffle(std::begin(pile), std::end(pile), rand_eng);
}

const std::vector<std::string> Stock::draw_three(CardPile& target_pile) {
  std::vector<std::string> responses;
  std::string dest_response = "";
  std::string src_response = EMPTY_LIST;
  const unsigned int size = pile.size();

  if (size >= 3) {
    for (unsigned int i = 0; i < 3; i++) {
      Card* card = pile.back();
      card->flip(true);
      pile.pop_back();
      target_pile.push(card);

      dest_response += std::string(card->as_str());
      if (i != size - 1) {
        dest_response += ",";
      }
    }
  }
  else if(size == 0 && target_pile.get_pile_size() > 0) {
    responses = reset(target_pile);
  }
  else {
    dest_response = ERROR_TAG + std::string("No cards left to draw.");
  }

  if (responses.size() == 0) {
    responses.push_back(dest_response);
    responses.push_back(src_response);
  }

  return responses;
}

const std::vector<std::string> Stock::draw(CardPile& target_pile, const bool face_up) {
  std::vector<std::string> responses;
  std::string dest_response = EMPTY_LIST;
  std::string src_response = EMPTY_LIST;
  const unsigned int size = pile.size();

  if (size > 0) {
    Card* card = pile.back();
    pile.pop_back();
    card->flip(face_up);
    target_pile.push(card);
    dest_response = std::string(face_up ? card->as_str() : "xx");
  }
  else if (size == 0 && target_pile.get_pile_size() > 0) {
    responses = reset(target_pile);
  }
  else {
    dest_response = ERROR_TAG + std::string("No cards left to draw.");
  }

  if (responses.size() == 0) {
    responses.push_back(dest_response);
    responses.push_back(src_response);
  }

  return responses;
}

const std::vector<std::string> Stock::reset(CardPile& target_pile) {
  std::vector<std::string> responses;
  std::string dest_response = EMPTY_LIST;
  std::string src_response = EMPTY_LIST;

  Talon& talon = static_cast<Talon&>(target_pile);
  pile_t cards = talon.get_pile();
  src_response = talon.pop(talon.get_pile_size());
  const unsigned int size = cards.size();

  for (unsigned int i = 0; i < size; i++) {
    Card* card = cards.at(i);
    card->flip(false);
    pile.push_back(card);

    dest_response += std::string(card->as_str());
    if (i != size - 1) {
      dest_response += ",";
    }
  }

  responses.push_back(dest_response);
  responses.push_back(src_response);

  return responses;
}

const int Stock::count() const {
  return pile.size();
}

void Stock::print() const {
  for (Card* card : pile) {
    std::cout << "Stock: " << *card << std::endl;
  }
}
