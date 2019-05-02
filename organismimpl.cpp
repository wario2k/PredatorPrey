#include "organismimpl.hpp"

/**
 * Brief : Constructor that creates an organism with time for survival, type and location as parameters
 * @param :  int requiredSurvivalTime - survival time for organsim
 * @param :  char organismSymbol - type of organism
 * @param :  const Cell& cell - location of cell
 * */
OrganismImpl::OrganismImpl(
    int requiredSurvivalTime,
    char organismSymbol,
    const Cell& cell
) :
    Organism::Organism(requiredSurvivalTime, organismSymbol, cell)
{ }

OrganismImpl::~OrganismImpl() {}

/**
 * Brief: Determines if it is time for the agent to breed yet
 * @return : true if conditions are met
 * */

bool OrganismImpl::readyToBreed() const
{
    if (getTimeSurvived() == 0)
        return false;
    return ((getTimeSurvived() % required_survival_time_for_breeding) == 0);
}

void OrganismImpl::setCell(const Cell& cell)
{
    this->myCell = cell;
}

Cell OrganismImpl::getCell() const
{
    return myCell;
}

int OrganismImpl::getTimeSurvived() const
{
    return timeSurvived;
}

void OrganismImpl::incrementTimeSurvived()
{
    timeSurvived++;
}

/**
 * Brief : utility function to make agent move cells
 * @param : const Cell& newCell - cell to move to
 * */
void OrganismImpl::move(const Cell& newCell)
{
    setCell(newCell);
}
