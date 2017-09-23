#pragma once
#include "constants.h"

typedef unsigned short int rank_t;
typedef unsigned short int suit_t;
typedef bool color_t;

class Card
{
private:
	const suit_t suit;
	const rank_t rank;
  const color_t color;
	const char * to_str;
	bool visible = false;

	friend std::ostream& operator<<(std::ostream& stream, const Card& card);

public:
	Card(const suit_t suit, const rank_t rank, const color_t color);
	const char * as_str() const;
	void flip(const bool face_up);
	const bool is_visible() const;
  const suit_t get_suit() const;
  const rank_t get_rank() const;
  const color_t get_color() const;

  bool isOppositeColor(Card* card) const;
  bool isRankLower(Card* card) const;
  bool isSameSuit(Card* card) const;

	~Card();
};
