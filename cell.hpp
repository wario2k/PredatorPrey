///implementation of cell class 
#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>

class Cell
{
public:
    ///default constructor 
    Cell();
    //initialize cell with x and y chords 
    Cell(int xVal, int yVal);
    //overladed operator to check for equality 
    friend bool operator ==(const Cell& cell1, const Cell& cell2);
    int x;
    int y;
    std::string str() const;
};
///vector to hold cells
typedef std::vector<Cell> CellVector;

#endif /* CELL_H */
