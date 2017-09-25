#include "stdafx.h"
#include "tableau_pile.h"

TableauPile::TableauPile() {
  src_idx = 0;
}

TableauPile::~TableauPile() {

}

const std::string TableauPile::push(Card* card) {
  std::string response = NO_REASON;

  if (is_active()) {
    Card* pile_card = (pile.size() > 0) ? pile.back() : NULL;
    bool isEmptyAndKing = pile_card == NULL && card->get_rank() == 12;
    bool isValidMove = pile_card != NULL && pile_card->is_opposite_color(*card) && pile_card->is_rank_lower(*card);

    if (isEmptyAndKing || isValidMove) {
      pile.push_back(card);
      response = std::string(card->as_str());
    }
    else if (pile_card == NULL) {
      response = ERROR_TAG + std::string("You can only place a King in an empty position.");
    }
    else {
      response = ERROR_TAG + std::string(card->as_str()) + " is not the opposite color or rank is higher.";
    }
   } else {
    pile.push_back(card);
  }

  return response;
}

const std::string TableauPile::push(CardPile* card_pile) {
  std::string response = "";
  pile_t cards = get_cards(card_pile);
  const unsigned int size = cards.size();

  if (size == 0) {
    response = ERROR_TAG + std::string("No cards selected.");
  }

  // Push the cards
  for (unsigned int i = 0; i < size; i++) {
    response += push(cards.at(i));

    if (response.find(ERROR_TAG) != std::string::npos) {
      break;
    }

    if (i != size - 1) {
      response += ",";
    }
  }

  // Pop the cards if no error and flip
  if (response.find(ERROR_TAG) == std::string::npos) {
    pop(*card_pile, cards.size());

    if (card_pile->get_pile_size() > 0) {
      card_pile->get_pile().back()->flip(true);
    }
  }

  return response;
}

pile_t TableauPile::get_cards(CardPile* card_pile) {
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


pile_t TableauPile::get_sub_pile() {
  pile_t cards = this->pile;

  if (this->src_idx > 0) {
    pile_t sub_pile;
    unsigned int size = cards.size();

    for (unsigned int i = this->src_idx; i < size; i++) {
      sub_pile.push_back(cards.at(i));
    }

    return sub_pile;
  }

  return cards;
}

const void TableauPile::update_src_idx(const unsigned int idx) {
  src_idx = idx;
}

const unsigned int TableauPile::get_src_idx() {
  return src_idx;
}

void TableauPile::print(const int tableau_num) const {
  for (Card* card : pile) {
    std::cout << "Tableau" << tableau_num << ": " << *card << ", FaceUp: " << card->is_visible() << std::endl;
  }
}
