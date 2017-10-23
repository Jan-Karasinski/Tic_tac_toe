#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Board.h"

namespace {
	size_t get_size(const char c[]) {
		std::string temp;
		std::cout << c << ": "; std::getline(std::cin, temp);
		std::stringstream ss{ temp };
		size_t size = -1;
		ss >> size;
		return size;
	}

	bool play_again() {
		std::string temp;
		std::cout << "Play again? (y/n): "; std::getline(std::cin, temp);
		std::cout << '\n';
		std::stringstream ss{ temp };
		char d = 'n';
		ss >> d;
		return d == 'Y' || d == 'y' ? true : false;
	}
}

int main() {
	do {
		size_t x{ get_size("Width") }, y{ get_size("Height") };
		if (x > MAX_BOARD_SIZE || y > MAX_BOARD_SIZE || x < 3 || y < 3) continue;
		
		size_t move_count = 0;

		Board game{ x, y };
		while (move_count < x*y && !game.end) {
			game.Draw();
			if (game.Move()) {
				move_count++;
			}
		}

		if (game.winner == ' ') {
			std::cout << "\nDraw!\n";
		}
		else {
			std::cout << "\nPlayer " << game.winner << " won!\n";
		}
		
	} while (play_again());
	
    return 0;
}

