#include "cell.hpp"
/**
 * Brief: Default Constructor
 * Description: empty constructor to prevent default compiler generated constructur
 * */
Cell::Cell()
{ 
}

/**
 * Brief: Constructor with x and y co-ordinates provided 
 * Description : Initializes a cell with x and y co-ordinates
 * @param: int xVal - x co-ordinate
 * @param: int yVal - y co-ordinate
 * */
Cell::Cell(int xVal, int yVal) : x(xVal), y(yVal)
{ }

/**
 * Brief: Overladed equality operator
 * Description : Utility overload to compare to cells
 * @param: const Cell& a - first cell to be compared 
 * @param: const Cell& b - second cell to be compared 
 * @return : true if equal
 * */
bool operator ==(const Cell& a, const Cell& b)
{
    return ((a.x == b.x) && (a.y == b.y));
}

/**
 * Brief: Utility function to return string notation of cell
 * Description : Returns a string representation of the cell with its x and y co-ordinates
 * @return : string representation of cell
 * */
std::string Cell::str() const
{
    return '(' + std::to_string(x) + ',' + std::to_string(y) + ')';
}
