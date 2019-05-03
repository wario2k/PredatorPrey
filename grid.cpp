/** @file grid.cpp
 *  @brief Implementation for the Grid Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */
#include "grid.hpp"

const int POSSIBLE_ADJACENT_CELL_COUNT = 4;

/**
 * Description : Get all x-y cords of matrix in cell vector
 * @params : int xMax - x value of grid provided by user
 * @params : int yMax - y value provided by user 
 * @return : vector of all cells in the grid
 * */
CellVector getCellSet(int xMax, int yMax)
{
    CellVector cellSet;
    for (int x = 0; x < xMax; x++) {
        for (int y = 0; y < yMax; y++) {
            cellSet.push_back(Cell(x, y));
        }
    }
    return cellSet;
}

/**
 * Description : Get 2D array of agents after creating it using the dimensions provided by user 
 * @params : int xMax - x value of grid provided by user
 * @params : int yMax - y value provided by user 
 * @return : 2D array of agents 
 * */

Organism*** get2dOrganismArray(int xMax, int yMax)
{
    Organism*** organismArray = 0;
    // create columns first
    organismArray = new Organism**[xMax];
    for (int x = 0; x < xMax; x++) {
        // create rows second
        organismArray[x] = new Organism*[yMax];
        for (int y = 0; y < yMax; y++) {
            organismArray[x][y] = NULL;
        }
    }
    return organismArray;
}

/**
 * Description : Constructor with x and y ranges provided
 *                  initalizes the vector with xMax and yMax which are the x and y dimensions of the grid the user wants to run the simulation for
 *                  sets the set as the vector of all possible cells in the vector
 *                  intializes 2D array of organisms.
 * @returns : nothing 
 * */
Grid::Grid(int x, int y) :
    xMax(x),
    yMax(y),
    cellSet(getCellSet(x, y)),
    organism2dArray(get2dOrganismArray(x, y))
{
    std::cout << "Grid created." << std::endl;
}

/**
 * Description : Clears contents of provided cell
 * @param : const Cell& cell - cell to delete from the grid
 * @returns : nothing
 * */
void Grid::clearCell(const Cell& cell)
{
    setCellValue(cell, NULL);
}

/**
 * Description : Sets cell value with organism provided in the grid
 * @param :const Cell& cell - reference to cell
 * @param : Organism* organism - organism to be loaded 
 * @returns : nothing
 * */
void Grid::setCellValue(const Cell& cell, Organism* organism)
{
    organism2dArray[cell.x][cell.y] = organism;
}

/**
 * Description : Utility function used to load organisms in the grid 
 * @returns : empty cell in the grid for an organism to occupy
 * */
Cell Grid::getRandomEmptyCellInGrid() const
{
    Cell cell;
    bool found = false;

    OrganismComparator comparator = OrganismComparator(EMPTY_SPACE_CHAR);
    cell = getRandomMatchingCell(
        cellSet, comparator, found);

    if (found)
        return cell;
    else 
    {
        // The user likely created too many organisms.
        std::cout << "ERROR: There are no remaining empty cells in grid.\n";
        std::cout << "INFO: Ensure # of organisms < # of cells in grid.\n";
        exit(1);
    }
}

/**
 * Description : Get organism contained at any given cell
 * @params: int x, int y - location of the organism in the array
 * @returns: reference to the organism 
 * */
Organism* Grid::getCellValue(int x, int y) const
{
    return organism2dArray[x][y];
}

/**
 * Description : utility function to get x and y location of organism in the array using the cell vector 
 * @returns : reference to organism contained 
 * */
Organism* Grid::getCellValue(const Cell& cell) const
{
    return getCellValue(cell.x, cell.y);
}

/**
 * Description : utility function to check if cell contains an organism 
 * @returns : true if match 
 * */
bool Grid::cellContains(const Cell& cell, OrganismComparator comparator) const
{
    return comparator.compare(getCellValue(cell));
}

/**
 * Description: utility function that checks if cell is in valid range of indices for the grid
 * @return : true if valid
 * */
bool Grid::isInRange(const Cell& cell) const
{
    bool aboveMin = ((cell.x >= 0) && (cell.y >= 0));  // must be positive
    bool belowMax = ((cell.x < xMax) && (cell.y < yMax));
    return (aboveMin && belowMax);
}

/**
 * Description : Gets adjascent cells that the agent could move to 
 * @return : vector of possible adjascent cells
 * */
CellVector Grid::getAdjacentCells(const Cell& cell) const
{
    CellVector actualAdjacentCells;

    int x = cell.x;
    int y = cell.y;

    Cell possibleAdjacentCells[POSSIBLE_ADJACENT_CELL_COUNT] = {
        Cell(x, y + 1),  // up
        Cell(x, y - 1),  // down
        Cell(x - 1, y),  // left
        Cell(x + 1, y)   // right
    };

    // if any location is off the grid, it's invalid.
    for (int i = 0; i < POSSIBLE_ADJACENT_CELL_COUNT; i++) {
        Cell possibleCell = possibleAdjacentCells[i];
        if (isInRange(possibleCell))
            actualAdjacentCells.push_back(possibleCell);
    }

    return actualAdjacentCells;
}

/**
 * Description : Utility function to select random adjascent cell to move to
 * @params : const Cell& cell - cell to check adjascents for
 * @return : adjascent cell to move to 
 * */

CellVector Grid::getRandomizedAdjacentCells(const Cell& cell) const
{
    CellVector adjacentCells = getAdjacentCells(cell);
    std::random_shuffle(adjacentCells.begin(), adjacentCells.end());
    return adjacentCells;
}

/**
 * Description : Utility function to find matching cell
 * @params : const CellVector& cellSet - vector of cells to scan
 * @params : OrganismComparator comparator - organism to find
 * @params : bool& found - true if found else false
 * @return : random matching cell
 * */
Cell Grid::getRandomMatchingCell(
    const CellVector& cellSet,
    OrganismComparator comparator,
    bool& found) const
{
    Cell cell;
    int cellsSearched = 0;
    int numCells = cellSet.size();

    while (cellsSearched < numCells && !found) {
        int randIndex = (std::rand() % numCells);  // one of [0, 1, 2, 3]
        cell = cellSet[randIndex];
        if (cellContains(cell, comparator)) {
            found = true;
        }
        cellsSearched++;
    }
    return cell;
}

/**
 * Description : Finds empty adjascent cell
 * @param : const CellVector& adjacentCells - vector of adjascent cells
 * @param : bool& found - true if found empty adjascent cell that can be moved to
 * */
Cell Grid::getEmptyCell(const CellVector& adjacentCells, bool& found) const
{
    OrganismComparator comparator = OrganismComparator(EMPTY_SPACE_CHAR);
    return getRandomMatchingCell(adjacentCells, comparator, found);
}

/**
 * Description : Utility function to display the grid
 * */
 
void Grid::display() const
{
    for (int x = 0; x < xMax; x++) {
        for (int y = 0; y < yMax; y++) {
            std::cout << getSymbolOrEmptyChar(getCellValue(x, y)) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
