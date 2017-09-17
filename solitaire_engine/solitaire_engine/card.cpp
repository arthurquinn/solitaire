#include "stdafx.h"
#include "card.h"


Card::Card(const suit_t suit, const rank_t rank) : suit(suit), rank(rank) {
	switch (suit) {
	case HEARTS:
		to_str[0] = 'h';
		break;
	case DIAMONDS:
		to_str[0] = 'd';
		break;
	case SPADES:
		to_str[0] = 's';
		break;
	case CLUBS:
		to_str[0] = 'c';
		break;
	default:
		to_str[0] = 'z';
	};

	switch (rank) {
	case 0:
		to_str[1] = 'a';
		break;
	case 9:
		to_str[1] = '1';
		to_str[2] = '0';
		to_str[3] = '\0';
		break;
	case 10:
		to_str[1] = 'j';
		break;
	case 11:
		to_str[1] = 'q';
		break;
	case 12:
		to_str[1] = 'k';
		break;
	default:
		to_str[1] = static_cast<char>(rank + 49);
		break;
	}
}

std::ostream& operator<<(std::ostream& stream, const Card& card) {
	return stream << card.to_str;
}

const char * Card::as_str() const {
	return to_str;
}

Card::~Card() {

}
