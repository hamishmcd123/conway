#include "cell.hpp"

Cell::Cell() {
	alive = false;
}

bool Cell::operator==(const Cell& lhs) const {
	if (ROW == lhs.ROW && COL == lhs.COL) {
		return true;
	}
	else {
		return false;
	}
}

bool Cell::operator!=(const Cell& lhs) const {
	return !(*this == lhs);
}