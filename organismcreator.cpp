#include "organismcreator.hpp"

/**
 * Brief : Default Constructor
 * */
OrganismCreator::OrganismCreator() { }


OrganismVector OrganismCreator::getOrganisms()
{
    return organisms;
}

/**
 * Brief : Add organism to our organisms vector
 * @param : Organism* organismPtr organism to be added
 * */
void OrganismCreator::addOrganism(Organism* organismPtr)
{
    organisms.push_back(organismPtr);
}

int OrganismCreator::count() const
{
    return organisms.size();
}

/**
 * Brief : gets index of organism we're trying to find
 * @param : const Cell& cell -> cell where the org resides
 * @returns : index of cell
 * */
int OrganismCreator::findIndex(const Cell& cell)
{
    for (int i = 0; i < organisms.size(); i++) {
        Cell orgCell = organisms[i]->getCell();
        if (orgCell == cell)
            return i;
    }

    std::cout << "Unable to find index of cell that should exist: " << cell.str() << std::endl;
    exit(1);
}

/**
 * Brief : Removes the organism from the vector
 * */
void OrganismCreator::remove(const Cell& cell)
{
    int index = findIndex(cell);
    Organism* ptr = organisms[index];
    organisms.erase(organisms.begin() + index);
    delete ptr;
    ptr = nullptr;
}
