/** @file coyote.hpp
 *  @brief Header for the Coyote Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */

#ifndef COYOTE_H
#define COYOTE_H

#include "cell.hpp"
#include "organismcreator.hpp"
#include "organismimpl.hpp"
#include <vector>

class Coyote : public OrganismImpl
{
public:
    Coyote(const Cell& cell);
    ~Coyote();
    void incrementTimeWithoutEating();
    bool isStarving() const;
    void eat();
private:
    int timeWithoutEating;
    const int max_time_without_eating;
};

typedef std::vector<Coyote*> CoyoteVector;

/**
 * Brief : Factory to create Coyotes
 * */
class CoyoteCreator : public OrganismCreator
{
public:
    Coyote* create(const Cell& cell);
};

#endif /* COYOTE_H */
