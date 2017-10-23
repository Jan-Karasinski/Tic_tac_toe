#pragma once
#include <vector>
#include "Field.h"

extern size_t MAX_BOARD_SIZE;

class Board {
	typedef size_t width;
	typedef size_t height;

	std::vector<std::vector<Field>> board;
public:
	bool end    = 0;
	char winner = ' ';
	char player = '1';

	Board(width, height);

	void Draw() const noexcept;

	// return true if move was valid
	bool Move() noexcept;

private:
	bool check(width, height) const;
	
	size_t get_coord(const char) const;

};

