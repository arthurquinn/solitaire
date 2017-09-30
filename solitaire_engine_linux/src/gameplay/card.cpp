#include "stdafx.h"
#include "gameplay/card.h"

Card::Card(const suit_t suit, const rank_t rank, const color_t color) : suit(suit), rank(rank), color(color) {
  char * str = new char[4];
  str[2] = '\0';

  switch (suit) {
    case HEARTS:
      str[0] = 'h';
      break;
    case DIAMONDS:
      str[0] = 'd';
      break;
    case SPADES:
      str[0] = 's';
      break;
    case CLUBS:
      str[0] = 'c';
      break;
    default:
      str[0] = 'z';
  };

  switch (rank) {
    case 0:
      str[1] = 'a';
      break;
    case 9:
      str[1] = '1';
      str[2] = '0';
      str[3] = '\0';
      break;
    case 10:
      str[1] = 'j';
      break;
    case 11:
      str[1] = 'q';
      break;
    case 12:
      str[1] = 'k';
      break;
    default:
      str[1] = static_cast<char>(rank + 49);
      break;
  }

  to_str = str;
}

std::ostream& operator<<(std::ostream& stream, const Card& card) {
  return stream << card.to_str;
}

const char * Card::as_str() const {
  return to_str;
}

void Card::flip(const bool face_up) {
  visible = face_up;
}

const bool Card::is_visible() const {
  return visible;
}

const suit_t Card::get_suit() const {
  return suit;
}

const rank_t Card::get_rank() const {
  return rank;
}

const color_t Card::get_color() const {
  return color;
}

const bool Card::is_opposite_color(const Card& card) const {
  return color != card.get_color();
}

const bool Card::is_rank_lower(const Card& card) const {
  return rank == card.get_rank() + 1;
}

const bool Card::is_same_suit(const Card& card) const {
  return suit == card.get_suit();
}

Card::~Card() {
  delete to_str;
}
