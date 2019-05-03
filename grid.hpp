/** @file grid.hpp
 *  @brief Header for the Grid Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */

#ifndef GRID_H
#define GRID_H

#include "cell.hpp"
#include "organism.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

class Grid
{
public:
    //Constructing the grid with x and y values 
    Grid(int x, int y);
    //displays the grid 
    void display() const;
    //used to place agents into the cell
    Cell getRandomEmptyCellInGrid() const;
    //removing the agent from the cell
    void clearCell(const Cell& cell);
    //assign agent to cell
    void setCellValue(const Cell& cell, Organism* organism);
    //get what agent is residing in cell
    Organism* getCellValue(const Cell& cell) const;
    //Overriden to get cell from x,y co-ordinates 
    Organism* getCellValue(int x, int y) const;
    //util function to scan adjascent cells 
    CellVector getAdjacentCells(const Cell& cell) const;
    //placing agent in random valid cell
    CellVector getRandomizedAdjacentCells(const Cell& cell) const;
    //scan and find empty adjascent cells 
    Cell getEmptyCell(const CellVector& adjacentCells, bool& found) const;
    //used to check if there are either empty / agent contained cells 
    Cell getRandomMatchingCell(
        const CellVector& cellSet,
        OrganismComparator comparator,
        bool& found) const;
private:
    
    //uses the comparator to check what agent occupies the cell
    bool cellContains(const Cell& cell, OrganismComparator comparator) const;
    bool isInRange(const Cell& cell) const;
    //main array
    Organism*** organism2dArray;

    const CellVector cellSet;
    //x and y range of grid
    const int xMax;
    const int yMax;
};

#endif /* GRID_H */
