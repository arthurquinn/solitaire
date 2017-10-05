#include "stdafx.h"
#include "gameplay/stock.h"

Stock::Stock() {}

const void Stock::push(Card* card) {
  card->flip(false);
  pile.push_back(card);
}

const void Stock::shuffle() {
  size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(pile.begin(), pile.end(), std::default_random_engine(seed));
}

const std::vector<std::string> Stock::draw_three(CardPile& target_pile) {
  pile_reset = false;
  std::vector<std::string> responses;
  std::string dest_response = "";
  std::string src_response = EMPTY_RESPONSE;
  const size_t size = pile.size();

  if (size >= 3) {
    for (size_t i = 0; i < 3; i++) {
      Card* card = pile.back();
      card->flip(true);
      pile.pop_back();
      target_pile.push(card);

      dest_response += std::string(card->as_str());
      dest_response += (i != size-1) ? "," : "";
    }
  }
  else if(size == 0 && target_pile.get_pile_size() > 0) {
    pile_reset = true;
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
  pile_reset = false;
  std::vector<std::string> responses;
  std::string dest_response = EMPTY_RESPONSE;
  std::string src_response = EMPTY_RESPONSE;
  const size_t size = pile.size();

  if (size > 0) {
    Card* card = pile.back();
    pile.pop_back();
    card->flip(face_up);
    target_pile.push(card);
    dest_response = std::string(face_up ? card->as_str() : INVISIBLE_CARD);
  }
  else if (size == 0 && target_pile.get_pile_size() > 0) {
    pile_reset = true;
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
  std::string dest_response = EMPTY_RESPONSE;
  std::string src_response = EMPTY_RESPONSE;

  Talon& talon = static_cast<Talon&>(target_pile);
  pile_t cards = talon.get_pile();
  src_response = talon.pop(talon.get_pile_size());
  const size_t size = cards.size();

  for (signed int i = size-1; i >= 0; i--) {
    Card* card = cards.at(i);
    card->flip(false);
    pile.push_back(card);

    dest_response += INVISIBLE_CARD;
    dest_response += (i != 0) ? "," : "";
  }

  responses.push_back(dest_response);
  responses.push_back(src_response);

  return responses;
}

const bool Stock::is_reset() const {
  return pile_reset;
}

const int Stock::count() const {
  return pile.size();
}

const void Stock::print() const {
  for (Card* card : pile) {
    std::cout << "Stock: " << *card << std::endl;
  }
}

Stock::~Stock() {}
