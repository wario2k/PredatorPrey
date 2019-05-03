/** @file coyote.cpp
 *  @brief Implementation of the Coyote class which inherits from Organismimpl
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */

#include "coyotee.hpp"

Coyote::~Coyote() {}

/**
 * Brief : Coyote Constructor
 * Description : Creates a Coyote object using OrganismImplementor
 *               and sets its properties as per the spec
 * */
Coyote::Coyote(const Cell& cell) :
    OrganismImpl::OrganismImpl(8, COYOTE_CHAR, cell),
    timeWithoutEating(0),
    max_time_without_eating(3)
{ }

bool Coyote::isStarving() const
{
    return (timeWithoutEating >= max_time_without_eating);
}
/**
 * Brief : Increment time without eating for each step coyote goes without eating a roadrunner
 * */
void Coyote::incrementTimeWithoutEating()
{
    timeWithoutEating++;
}

/**
 * Brief : update time without eating if just ate something
 * */
void Coyote::eat()
{
    timeWithoutEating = 0;  // reset time without eating, since doodlebug just ate
}

/**
 * Brief : Coyote factory
 * @param : const Cell& cell - location of coyote
 * @returns : pointer to coyote.
 * */
Coyote* CoyoteCreator::create(const Cell& cell)
{
    Coyote* newCoyote = new Coyote(cell);
    addOrganism(newCoyote);
    return newCoyote;
}
