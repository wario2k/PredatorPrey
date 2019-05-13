/** @file simulation.hpp
 *  @brief Header for the Simulation Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */
#include <iostream>
#include "controller.hpp"
#include "grid.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

class Simulation
{
    private:
        /* Here will be the instance stored. */
        static Simulation* instance;
        int xSize, ySize, numRoadrunners, numCoyotes, numSteps, count; 
        /* Private constructor to prevent instancing. */
        Simulation();
        void getBoardSize();
        void getRoadrunners();
        void getCoyotes();
        void getSteps();
        
    protected:
        std::ofstream out_stream;
        std::string temp;

    public:
        /* Static access method. */
        static Simulation* getInstance();
        void runSimulation();
        

};