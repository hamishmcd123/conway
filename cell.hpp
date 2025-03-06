#pragma once
class Cell{
public:
bool alive; 
int ROW;
int COL;
Cell();
bool operator==(const Cell& lhs) const; 
bool operator!=(const Cell& lhs) const;
};