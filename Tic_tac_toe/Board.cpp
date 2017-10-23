#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Board.h"
#include "Field.h"

extern size_t MAX_BOARD_SIZE = 9;

Board::Board(width w, height h)
{
	board.resize(h);
	for (size_t i = 0; i < board.size(); ++i) {
		board[i].resize(w);
	}
}

void Board::Draw() const noexcept {
	std::cout << '\n';
	for (size_t i = 0; i < board[0].size(); ++i) {
		std::cout << "--";
	}
	std::cout << "-\n";
	for (size_t y = 0; y < board.size(); ++y) {
		std::cout << '|';
		for (size_t x = 0; x < board[0].size(); ++x) {
			std::cout << board[y][x] << '|';
		}
		std::cout << '\n';
		for (size_t x = 0; x < board[0].size(); ++x) {
			std::cout << "--";
		}
		std::cout << "-\n";
	}
}

bool Board::Move() noexcept {
	std::cout << "\nPlayer " << player << '\n';
	
	size_t x{ get_coord('X') }, y{ get_coord('Y') };
	if (--x > MAX_BOARD_SIZE || --y > MAX_BOARD_SIZE || x >= board[0].size() || y >= board.size()) return false;

	if (board[y][x] == ' ')	{
		board[y][x] = player == '1' ? 'X' : 'O';
		player = player == '1' ? '2' : '1';

		if (check(x, y)) {
			end = true;
			winner = player;
		}
		return true;
	}
	return false;
}

bool Board::check(width w, height h) const {
	size_t x{ w }, y{ h };
	//diagonal
	// top-left
	if (x > 1 && y > 1) {
		if (board[y][x] != ' ' && board[y - 2][x - 2] == board[y - 1][x - 1]
			&& board[y - 1][x - 1] == board[y][x]) {
			return true;
		}
	}
	// top-right
	if (x < board[0].size() - 2 && y > 1) {
		if (board[y][x] != ' ' && board[y - 2][x + 2] == board[y - 1][x + 1]
			&& board[y - 1][x + 1] == board[y][x]) {
			return true;
		}
	}
	// bottom-left
	if (x > 1 && y < board.size() - 2) {
		if (board[y][x] != ' ' && board[y + 2][x - 2] == board[y + 1][x - 1]
			&& board[y + 1][x - 1] == board[y][x]) {
			return true;
		}
	}
	// bottom-right
	if (x < board[0].size() - 2 && y < board.size() - 2) {
		if (board[y][x] != ' ' && board[y + 2][x + 2] == board[y + 1][x + 1]
			&& board[y + 1][x + 1] == board[y][x]) {
			return true;
		}
	}

	//straight
	// top-mid
	if (y > 1) {
		if (board[y][x] != ' ' && board[y - 2][x] == board[y - 1][x]
			&& board[y - 1][x] == board[y][x]) {
			return true;
		}
	}
	// mid-left
	if (x > 1) {
		if (board[y][x] != ' ' && board[y][x - 2] == board[y][x - 1]
			&& board[y][x - 1] == board[y][x]) {
			return true;
		}
	}
	// mid-right
	if (x < board[0].size() - 2) {
		if (board[y][x] != ' ' && board[y][x + 2] == board[y][x + 1]
			&& board[y][x + 1] == board[y][x]) {
			return true;
		}
	}
	// bottom-mid
	if (y < board.size() - 2) {
		if (board[y][x] != ' ' && board[y + 2][x] == board[y + 1][x]
			&& board[y + 1][x] == board[y][x]) {
			return true;
		}
	}
	

	//around point
	if (x > 0 && x < board[0].size() - 1
		&& y > 0 && y < board.size() - 1) {
		// diagonal top-left to bottom-right
		if (board[y][x] != ' ' && board[y - 1][x - 1] == board[y][x]
			&& board[y][x] == board[y + 1][x + 1]) {
			return true;
		}
		// diagonal bottom-left to top-right
		if (board[y][x] != ' ' && board[y + 1][x - 1] == board[y][x]
			&& board[y][x] == board[y - 1][x + 1]) {
			return true;
		}
		// straight top to bottom
		if (board[y][x] != ' ' && board[y - 1][x] == board[y][x]
			&& board[y][x] == board[y + 1][x]) {
			return true;
		}
		// straight left to right
		if (board[y][x] != ' ' && board[y][x - 1] == board[y][x]
			&& board[y][x] == board[y][x + 1]) {
			return true;
		}
	}
	return false;
}

size_t Board::get_coord(const char c) const {
	std::string temp;
	std::cout << c << ": "; std::getline(std::cin, temp);
	std::stringstream ss{ temp };
	size_t size = -1;
	ss >> size;
	return size;
}