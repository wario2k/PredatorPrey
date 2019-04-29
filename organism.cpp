#include "organism.hpp"

/**
 * Description : Constructor to initialize an organism
 * @param : int requiredSurvivalTime - time before breed
 * @param : char organismSymbol - type of organism
 * @param : const Cell& cell - cell location 
 * */
Organism::Organism(
    int requiredSurvivalTime,
    char organismSymbol,
    const Cell& cell
) :
    myCell(cell),
    required_survival_time_for_breeding(requiredSurvivalTime),
    symbol(organismSymbol),
    timeSurvived(0)
{ }

/**
 * Default Destructor
 * */
Organism::~Organism() {}

/**
 * Description : Get what organism is residing in cell
 * @param  : Organism* organism - organism pointer to cell 
 * @return : Symbol of organism if present else empty space symbol
 * */
 
char getSymbolOrEmptyChar(Organism* organism)
{
    if (organism == NULL)
        return EMPTY_SPACE_CHAR;
    else
        return organism->symbol;
}

/**
 * Brief : compare cells to see what organism resides there
 * @param : char value - value to be compared
 * */
OrganismComparator::OrganismComparator(char value) :
    compareValue(value)
{ }
/**
 * Brief : compare cells to see what organism resides there
 * Description : Uses the organism object to compare value
 * @param : Organism* organism - pointer to organism in cell
 * 
 * */
OrganismComparator::OrganismComparator(Organism* organism) :
    compareValue(getSymbolOrEmptyChar(organism))
{ }

/**
 * Description : Overloaded operator to compare organism values 
 * @return : true if the match else false
 * */
bool OrganismComparator::compare(Organism* organism)
{
    return (compareValue == getSymbolOrEmptyChar(organism));
}
