#pragma once
#include "raylib.h"
#include "raymath.h"
#include "cell.hpp"
#include <vector>
class Cursor{
public:
	Vector2 truePos;
	Vector2 snappedPos;
	void drawCursor(); 
	void updateCursorPosition();
	void updateCell(std::vector<std::vector<Cell>>& cellVec);
};