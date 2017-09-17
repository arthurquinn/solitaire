#include "stdafx.h"
#include "card.h"


Card::Card(const suit_t suit, const rank_t rank) : suit(suit), rank(rank) {
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

Card::~Card() {
	delete to_str;
}
