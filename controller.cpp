#include "controller.hpp"
/**
 * Brief : Default Constructor
 * */

GridController::GridController() { }

/**
 * Brief : Constructor with pointer to a grid object
 * Description : initializes the controller with a grid object pointer
 *                  also initializes coyote and roadrunner factories.
 * */
GridController::GridController(Grid* gridPtr) : grid(gridPtr)
{
    this->roadrunnerCreator = new RoadrunnerCreator();
    this->coyoteCreator = new CoyoteCreator();
}

/**
 * Brief : Creates an organism
 * @param : OrganismCreator* creator -> Organism creator class
 * @param : Cell& cell -> cell containing organism.
 * */
void GridController::createOrganism(OrganismCreator* creator, const Cell& cell)
{
    Organism* organism = creator->create(cell);
    grid->setCellValue(cell, organism);
}
/**
 * Brief : Util function to create multiple organisms. 
 * @param: OrganismCreator* creator - Creator utility
 * @param : int count - number of organisms to create.
 * */
void GridController::createOrganisms(OrganismCreator* creator, int count)
{
    for (int i = 0; i < count; i++) {
        Cell cell = grid->getRandomEmptyCellInGrid();
        createOrganism(creator, cell);
    }
}

/**
 * Brief : creates road runners
 * @param : int count - number of road runners to create
 * */
void GridController::createRoadrunners(int count)
{
    createOrganisms(roadrunnerCreator, count);
}
/**
 * Brief : creates Coyotes
 * @param : int count - number of Coyotes to create
 * */

void GridController::createCoyotes(int count)
{
    createOrganisms(coyoteCreator, count);
}

/**
 * Brief : Move organism to a new cell
 * @param : Organism * organism - reference to organism
 * @param :const Cell& newCell - cell to move organism to
*/
void GridController::moveOrganism(Organism* organism, const Cell& newCell)
{
    grid->clearCell(organism->getCell());
    grid->setCellValue(newCell, organism);
    organism->move(newCell);
    organism->incrementTimeSurvived();
}
/**
 * Brief :  Kill Roadrunner
 * @param : Organism * organism - reference to organism
 * @param : OrganismCreator* creator - removes the roadrunner from the vector of organisms
 */

void GridController::killOrganism(Organism* organism, OrganismCreator* creator)
{
    creator->remove(organism->getCell());
    grid->clearCell(organism->getCell());
}
/**
 * Brief : Coyote will eat road runner - removing it from the grid
 * @param : Coyote* coyote - the coyote that is eating  
 * @param : Cell cell - the cell that the roadrunner is currently in
 * */
void GridController::makeCoyoteEatRoadrunner(Coyote* coyote, Cell cell)
{
    Organism* organism = grid->getCellValue(cell);
    //kill the road runner
    killOrganism(organism, roadrunnerCreator);
    coyote->eat();
}

/**
 * Brief : Tries to find a near by roadrunner for coyote to eat
 * @param : CellVector& nearbyCells - vector of cells near by
 * @param : bool& found - whether or not a road runner was found
 * @return : Cell location if match found
 * */
Cell GridController::findNearbyRoadrunner(const CellVector& nearbyCells, bool& found) const
{
    OrganismComparator comparator = OrganismComparator(ROADRUNNER_CHAR);
    return grid->getRandomMatchingCell(nearbyCells, comparator, found);
}
/**
 * Brief : Coyote controller
 * Description : gets the coyote cell and tries to find nearby 
 *                  roadrunners to eat, else decides to move to an empty cell
 * @param : Coyote* coyote - reference to coyote
 * @param : bool& found - if found valid cell
 * @returns : Cell to move to
 * */

Cell GridController::getNextCoyoteCell(Coyote* coyote, bool& found)
{
    Cell cell = coyote->getCell();
    CellVector adjacentCells = grid->getRandomizedAdjacentCells(cell);

    Cell nextCell = findNearbyRoadrunner(adjacentCells, found);

    if (found) 
    {
        makeCoyoteEatRoadrunner(coyote, nextCell);
        return nextCell;
    } else 
    {
        return grid->getEmptyCell(adjacentCells, found);
    }
}

/**
 * Brief : Moves Coyote to a valid cell
 * @param : Coyote* coyote - reference to coyote
 * */
void GridController::moveCoyote(Coyote* coyote)
{
    Cell newCell;
    bool canMove = false;
    
    newCell = getNextCoyoteCell(coyote, canMove);

    if (canMove) 
    {
        moveOrganism(coyote, newCell);
    }

    coyote->incrementTimeWithoutEating();
}

Cell GridController::getNextAdjacentCell(Organism* organism, bool& found)
{
    Cell cell = organism->getCell();
    CellVector adjacentCells = grid->getRandomizedAdjacentCells(cell);
    return grid->getEmptyCell(adjacentCells, found);
}

/**
 * Brief : Moves roadrunner if valid cell found
 * @param : Organism * organism - reference to organism
 * */
void GridController::moveRoadrunner(Organism* organism)
{
    Cell newCell;
    bool canMove = false;
    //find valid cell 
    newCell = getNextAdjacentCell(organism, canMove);

    if (canMove) 
    {
        moveOrganism(organism, newCell);
    }
}

/**
 * Brief : Tries to get organisms to breed
 * Description : Finds all agents in cells and finds if they can breed and performs action if true
 *              calls organism factory to create an organism in a new cell
 * @param : Organism* organism - reference to organism trying to breed
 * @param : OrganismCreator* creator - organism factory reference
 * */
void GridController::breedOrganism(Organism* organism, OrganismCreator* creator)
{
    Cell breedCell;
    bool canBreed = false;

    Cell cell = organism->getCell();
    CellVector adjacentCells = grid->getRandomizedAdjacentCells(cell);

    breedCell = grid->getEmptyCell(adjacentCells, canBreed);

    if (canBreed) 
    {
        createOrganism(creator, breedCell);
    }
}
/**
 * Brief : Over arching controller for coyotes 
 * Description : Checks the grid for all coyotes and gets their stats - whether they are starving or ready to breed 
 *                  and performs necessary actions according to those stats.
 * */

void GridController::moveCoyotes()
{
    CoyoteVector breedingCoyotes;
    CoyoteVector starvingCoyotes;

    OrganismVector coyotes = coyoteCreator->getOrganisms();

    for (int i = 0; i < coyotes.size(); i++) 
    {
        Coyote* coyote = dynamic_cast<Coyote*>(coyotes[i]);

        moveCoyote(coyote);

        if (coyote->readyToBreed())
            breedingCoyotes.push_back(coyote);

        // If a coyote has not eaten a roadrunner within the last three time steps,
        // then at the end of the third time step it will starve and die.
        // The coyote should then be removed from the grid of cells.
        if (coyote->isStarving())
            starvingCoyotes.push_back(coyote);
    }

    for (int i = 0; i < breedingCoyotes.size(); i++) 
    {
        Coyote* coyote = breedingCoyotes[i];
        breedOrganism(coyote, coyoteCreator);
    }

    for (int i = 0; i < starvingCoyotes.size(); i++) 
    {
        Coyote* coyote = starvingCoyotes[i];
        killOrganism(coyote, coyoteCreator);
    }
}

/**
 * Brief : Gets roadrunners ready to breed and also moves them.
 * Description : Goes through grid and checks if road runners 
 *               are ready to breed after they have been moved to a new cell.
 * */
void GridController::moveRoadrunners()
{
    OrganismVector roadrunners = roadrunnerCreator->getOrganisms();

    OrganismVector roadrunnersToBreed;

    for (int i = 0; i < roadrunners.size(); i++) 
    {
        Organism* roadrunner = roadrunners[i];
        
        moveRoadrunner(roadrunner);

        if (roadrunner->readyToBreed())
            roadrunnersToBreed.push_back(roadrunner);
    }

    //check for breeding
    for (int i = 0; i < roadrunnersToBreed.size(); i++) 
    {
        Organism* roadrunner = roadrunners[i];
        breedOrganism(roadrunner, roadrunnerCreator);
    }
}
/**
 * Brief : Moves road runners and coyotes.
 * */

void GridController::step()
{
    moveCoyotes();
    moveRoadrunners();
}

void GridController::display() const
{
    std::cout << "total # of coyotes: ";
    std::cout << coyoteCreator->count() << std::endl;
    std::cout << "total # of roadRunners: ";
    std::cout << roadrunnerCreator->count() << std::endl;
    grid->display();
}

/**
 * Brief : CSV writer for data visualization
 * @param : ostream& csvFileStream - stream to write to
 * @param int iterations - number of iterations of simulation 
 * */
void GridController::writeDataToCsv(std::ostream& csvFileStream, int iteration) const
{
    csvFileStream << iteration << ",";
    csvFileStream << coyoteCreator->count() << ",";
    csvFileStream << roadrunnerCreator->count() << std::endl;
}
