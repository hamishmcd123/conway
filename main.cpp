#include "raylib.h"
#include "cell.hpp"
#include <vector>
#include "cursor.hpp"
#include <iostream>
constexpr int CELL_SIZE = 4; 
constexpr int CELLROWS = 128;
constexpr int CELLCOLS = 128;


static void drawCells(std::vector<std::vector<Cell>>& cellVec);
static void runGeneration(std::vector<std::vector<Cell>>& cellVec);
static void clearAllCells(std::vector<std::vector<Cell>>& cellVec);

static enum class gameStates {
EDIT,
PLAY 
};


int main() {
    SetTargetFPS(30);
    Cursor cursor;
// 2D Vector for cells 
std::vector<std::vector<Cell>> cellVec(CELLROWS, std::vector<Cell>(CELLCOLS, Cell()));
enum gameStates currentState = gameStates::EDIT;
//Give Cells Positions...
for (int i = 0; i < CELLROWS; i ++) {
    for (int j = 0; j < CELLCOLS; j++) {
        cellVec[i][j].ROW = i;
        cellVec[i][j].COL = j;
    }    
}
InitWindow(CELL_SIZE * CELLCOLS, CELL_SIZE * CELLROWS, "Conway's Game of Life"); 
while(!WindowShouldClose()) {
    BeginDrawing(); 
    ClearBackground(RAYWHITE); 
    drawCells(cellVec);
    cursor.updateCursorPosition();
    cursor.drawCursor();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && currentState == gameStates::EDIT && 
        (cursor.truePos.x > 0 && cursor.truePos.x < CELLCOLS * CELL_SIZE) &&
        (cursor.truePos.y > 0 && cursor.truePos.y < CELLROWS * CELL_SIZE)) {
        cursor.updateCell(cellVec);
    }
    if (IsKeyPressed(KEY_G)) {
        currentState = gameStates::PLAY;
    }
    if (currentState == gameStates::PLAY) {
         runGeneration(cellVec);
    }
    if (IsKeyPressed(KEY_P)) {
        currentState = gameStates::EDIT;
    }
    if (IsKeyPressed(KEY_C)) {
        currentState = gameStates::EDIT;
        clearAllCells(cellVec);
    }
    EndDrawing();
}
    CloseWindow();
    return 0; 
}

static void drawCells(std::vector<std::vector<Cell>>& cellVec) {
for (int i = 0; i < CELLROWS; i++) {
    for (int j = 0; j < CELLCOLS; j++) {
        Cell currentCell = cellVec[i][j];
        if (!(currentCell.alive)) {
            DrawRectangle(currentCell.COL * CELL_SIZE, currentCell.ROW * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK); 
        }
        else if (currentCell.alive) {
            DrawRectangle(currentCell.COL * CELL_SIZE, currentCell.ROW * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE); 
        }
    }    
}
}


static void clearAllCells(std::vector<std::vector<Cell>>& cellVec) {
    for (int i = 0; i < CELLROWS; i++) {
        for (int j = 0; j < CELLCOLS; j++) {
            cellVec[i][j].alive = false;
        }
    }
}
static void runGeneration(std::vector<std::vector<Cell>>& cellVec) {
    //Create a copy of cellVec to apply changes to. 
    std::vector<std::vector<Cell>> tempCellVec = cellVec; 
    for (int i = 0; i < CELLROWS; i++) {
        for (int j = 0; j < CELLCOLS; j++) {
            // Check to see if cell is dead. If the cell is dead, we can continue and check the birth condition. 
            if (cellVec[i][j].alive == false) {
                // Check in the surrounding area of cell.
                int aliveNeighbours = 0; 
                for (int y = -1; y < 2; y++) {
                    if (i + y >= 0 && i + y < CELLROWS) {
						for (int x = -1; x < 2; x++) {
                            if (j + x >= 0 && j + x < CELLCOLS) {
                                if (cellVec[i + y][j + x].alive == true && (cellVec[i + y][j + x] != cellVec[i][j])) {
                                    aliveNeighbours++;
                                }
                            }
                            else {
                                continue;
                            }
                     }
                    }
                    else {
                        continue;
                    }
				   }
                //If 3 or more alive neighbours, then the cell becomes alive.
                if (aliveNeighbours == 3) {
                    tempCellVec[i][j].alive = true;
                }
            }
            else {
                //Check to see how many alive neighbours...
                int aliveNeighbours = 0;
                for (int y = -1; y < 2; y++) {
                    if (i + y >= 0 && i + y < CELLROWS) {
                        for (int x = -1; x < 2; x++) {
                            if (j + x >= 0 && j + x < CELLCOLS) {
                                if (cellVec[i + y][j + x].alive == true && (cellVec[i + y][j + x] != cellVec[i][j])) {
                                    aliveNeighbours++;
                                }
                            }
                            else {
                                continue;
                            }
                        }
                    }
                    else {
                        continue;
                    }
                }
                // Death by isolation -- A live cell dies if it has one or fewer live neighbours
                if (aliveNeighbours <= 1) {
                    tempCellVec[i][j].alive = false;    
                }
                // Death by overcrowding -- A live cell dies if it has four or more live neighbours
                else if (aliveNeighbours >= 4) {
                    tempCellVec[i][j].alive = false;
                }
                else {
                    continue;
                }
            }
            
        }
    }
    cellVec = tempCellVec;
}

