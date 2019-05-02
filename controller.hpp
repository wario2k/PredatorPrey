#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "roadrunner.hpp"
#include "coyotee.hpp"
#include "organismcreator.hpp"
#include "cell.hpp"
#include "grid.hpp"
#include "organism.hpp"
#include <fstream>
#include <iostream>


class GridController
{
public:
    GridController();
    GridController(Grid* gridPtr);
    void createRoadrunners(int count);
    void createCoyotes(int count);
    void display() const;
    void writeDataToCsv(std::ostream& csvFileStream, int iteration) const;
    void step();
private:
    Grid* grid;
    RoadrunnerCreator* roadrunnerCreator;
    CoyoteCreator* coyoteCreator;
    void moveRoadrunners();
    void moveCoyotes();
    void createOrganism(OrganismCreator* creator, const Cell& cell);
    void createOrganisms(OrganismCreator* creator, int count);
    void moveOrganism(Organism* organism, const Cell& newCell);
    void killOrganism(Organism* organism, OrganismCreator* creator);
    void makeCoyoteEatRoadrunner(Coyote* coyote, Cell cell);
    void breedOrganism(Organism* organism, OrganismCreator* creator);
    Cell findNearbyRoadrunner(const CellVector& nearbyCells, bool& found) const;
    Cell getNextCoyoteCell(Coyote* coyote, bool& found);
    Cell getNextAdjacentCell(Organism* organism, bool& found);
    void moveCoyote(Coyote* coyote);
    void moveRoadrunner(Organism* organism);
    void checkGameState();
};


#endif