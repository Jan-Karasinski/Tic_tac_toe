#pragma once
#include <iostream>

struct Field {
	char c{ ' ' };

	bool operator!=(const char x) const {
		return !operator==(x);
	}

	void operator=(const char x) {
		c = x;
	}
	
	bool operator==(const char x) const {
		return c == x ? true : false;
	}

	bool operator==(const Field f) const {
		return c == f.c ? true : false;
	}

	friend std::ostream& operator<<(std::ostream& str, const Field& f) {
		return str << f.c;
	}
};