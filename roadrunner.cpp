#include "roadrunner.hpp"

Roadrunner::~Roadrunner() {}
/**
 * Brief : Initializes a road runner with its cell location 
 * */

Roadrunner::Roadrunner(const Cell& cell) :
    OrganismImpl::OrganismImpl(3, ROADRUNNER_CHAR, cell)
{ }

/**
 * Brief : Creates a new road runner at cell specified.
 * @return: a reference to a road runer returned by the factory
 * */
Roadrunner* RoadrunnerCreator::create(const Cell& cell)
{
    Roadrunner* newRoadrunner = new Roadrunner(cell);
    addOrganism(newRoadrunner);
    return newRoadrunner;
}
