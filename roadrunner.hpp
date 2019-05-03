
/** @file roadrunner.hpp
 *  @brief Header for the Roadrunner Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */
#ifndef ROADRUNNER_H
#define ROADRUNNER_H

#include "cell.hpp"
#include "organismcreator.hpp"
#include "organismimpl.hpp"


class Roadrunner : public OrganismImpl
{
public:
    Roadrunner(const Cell& cell);
    ~Roadrunner();
};

/**
 * Brief : Roadrunner factory
 * */
class RoadrunnerCreator : public OrganismCreator
{
public:
    Roadrunner* create(const Cell& cell);
};

#endif /* ROADRUNNER_H */
