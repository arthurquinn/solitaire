#include "stdafx.h"
#include "card.h"


Card::Card(const suit_t suit, const rank_t rank) : suit(suit), rank(rank) {
	to_str = "hello";

}

std::ostream& operator<<(std::ostream& stream, const Card& card) {
	return stream << static_cast<int>(card.suit) << card.rank;
}

Card::~Card() {

}
