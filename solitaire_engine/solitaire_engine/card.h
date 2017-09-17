#pragma once
#include "constants.h"

typedef unsigned short int rank_t;
typedef unsigned short int suit_t;

class Card
{
private:
	const suit_t suit;
	const rank_t rank;
	const char * to_str;

	friend std::ostream& operator<<(std::ostream& stream, const Card& card);

public:
	Card(const suit_t suit, const rank_t rank);
	~Card();
};

