/** @file organism.hpp
 *  @brief Header for the Organism Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */
#ifndef ORGANISM_H
#define ORGANISM_H

#include "cell.hpp"
#include <vector>

const char ROADRUNNER_CHAR = 'o';
const char COYOTE_CHAR = 'X';
const char EMPTY_SPACE_CHAR = '-';

class Organism
{
public:
    Organism(int requiredSurvivalTime, char organismSymbol, const Cell& cell);
    ///destructor
    virtual ~Organism() = 0;
    //virtual functions to be implemented in base classes 
    virtual void move(const Cell& newCell) = 0;
    virtual Cell getCell() const = 0;
    virtual void setCell(const Cell& cell) = 0;
    virtual int getTimeSurvived() const = 0;
    virtual void incrementTimeSurvived() = 0;
    virtual bool readyToBreed() const = 0;
    const char symbol;
    //gets type of organism 
    friend char getSymbolOrEmptyChar(Organism* organism);
protected:
    const int required_survival_time_for_breeding;
    int timeSurvived;
    Cell myCell;
};

///vector of organism pointers
typedef std::vector<Organism*> OrganismVector;

/**
 * Utility class to compare organisms 
 * */
class OrganismComparator
{
public:
    OrganismComparator(char value);
    OrganismComparator(Organism* organism);
    bool compare(Organism* organism);
private:
    const char compareValue;
};

#endif /* ORGANISM_H */
