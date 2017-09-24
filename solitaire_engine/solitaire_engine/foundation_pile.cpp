#include "stdafx.h"
#include "foundation_pile.h"


FoundationPile::FoundationPile() {

}

FoundationPile::~FoundationPile() {

}

const std::string FoundationPile::push(Card* card) {
  std::string response = NO_REASON;

  if (is_active()) {
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool is_empty_and_ace = pile_card == NULL && card->get_rank() == 0;
    bool is_valid_move = pile_card != NULL && pile_card->is_same_suit(card) && !pile_card->is_opposite_color(card) && !pile_card->is_rank_lower(card);

    if (is_empty_and_ace || is_valid_move) {
      pile.push_back(card);
      response = std::string(card->as_str());
    }
    else if (pile_card == NULL) {
      response = ERROR_TAG + std::string("You can only bring an Ace to an empty position.");
    }
    else {
      response = ERROR_TAG + std::string(card->as_str()) + " is not the same suit, is not the same color, or rank is lower.";
    }
  } else {
    pile.push_back(card);
  }

  return response;
}

const std::string FoundationPile::push(CardPile* card_pile) {
  std::string response = NO_REASON;
  pile_t src_pile = get_cards(card_pile);
  unsigned int size = src_pile.size();

  if (size == 1) {
    response = push(src_pile.back());
  }
  else if(size > 1) {
    response = ERROR_TAG + std::string("Cannot add a group of cards to a foundation pile.");
  }
  else {
    response = ERROR_TAG + std::string("No cards selected.");
  }

  // Pop the card if no error
  if (response.find(ERROR_TAG) == std::string::npos) {
    pop(*card_pile, 1);
  }

  return response;
}

pile_t FoundationPile::get_cards(CardPile* card_pile) {
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
