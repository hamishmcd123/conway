#include "cursor.hpp"

void Cursor::updateCursorPosition() {
	truePos = GetMousePosition();
	snappedPos.x = floor(truePos.x / 4.0f) * 4;
	snappedPos.y = floor(truePos.y / 4.0f) * 4;
}
void Cursor::drawCursor() {
	DrawRectangle(snappedPos.x, snappedPos.y, 4, 4, RED);
}

void Cursor::updateCell(std::vector<std::vector<Cell>>& cellVec) {
	int currentCol = snappedPos.x / 4;
	int currentRow= snappedPos.y / 4;
	//Check to see if cursor is in bounds...
	if (cellVec[currentRow][currentCol].alive == false) {
		cellVec[currentRow][currentCol].alive = true;
	}

}


