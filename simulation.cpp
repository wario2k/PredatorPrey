
/** @file simulation.cpp
 *  @brief Implementation for the Simulation Class
 *
 *  @author Aayush B Shrestha 
 *  @bug No known bugs.
 *  
 */
#include "simulation.hpp"
/* Null, because instance will be initialized on demand. */
Simulation* Simulation::instance = 0;

Simulation* Simulation::getInstance()
{
    if (instance == 0)
    {
        instance = new Simulation();
    }

    return instance;
}
/**
 * Brief : Default constructor initalizaing negative values for error checking
 * */
Simulation::Simulation()
{
    xSize = -1, ySize = -1, numRoadrunners = -1, numCoyotes = -1, numSteps = -1 , count = 0;
}

/**
 * Brief : Get board size and validate if valid range.
 * */
void Simulation::getBoardSize()
{
    try
    {
        std::cout<<"Please enter number of rows : ";
        std::cin>>xSize;
        if(xSize < 0 || xSize  > INT_MAX)
        {
            throw "Invalid value provided! Program will exit";
        }
        std::cout<<std::endl<<"Please enter number of cols : ";
        std::cin>>ySize;
        if(ySize < 0 || ySize > INT_MAX)
        {
            throw "Invalid value provided! Program will exit";
        }
        
    }
    catch(...)
    {
        std::cerr<<"Exiting program because provided invalid board size.!";
        exit(1);
    }
}
        
/**
 * Description : Get number of roadrunners and validate if in range
 * */
void Simulation::getRoadrunners()
{
    try
    {
        std::cout<<"Please enter number of Roadrunners : ";
        std::cin>>numRoadrunners;
        if(numRoadrunners < 0 || numRoadrunners  > INT_MAX)
        {
            throw "Invalid value provided! Program will exit";
        }
    }
    catch(...)
    {
        std::cerr<<"Exiting program because provided invalid number of roadrunners!";
        exit(1);
    }
}

/**
 * Description : Get number of Coyotes and validate if in range
 * */
void Simulation::getCoyotes()
{
     try
    {
        std::cout<<"Please enter number of Coyotes : ";
        std::cin>>numCoyotes;
        if(numCoyotes < 0 || numCoyotes  > INT_MAX)
        {
            throw "Invalid value provided! Program will exit";
        }
    }
    catch(...)
    {
        std::cerr<<"Exiting program because provided invalid number of coyotes!";
        exit(1);
    }
}

/**
 * Brief : Get number of steps user wants to run the simulation for
 *
 * */

void Simulation::getSteps()
{
    try
    {
        std::cout<<"Please Enter number of times you would like to run the simulation : ";
        std::cin>>numSteps;
        if(numSteps < 0)
        {
            throw "Out of range exception!";
        }
    }
    catch(...)
    {
        std::cerr <<"User provided in valid number of steps to run the program. Terminating the application!";
        exit(1);
    }
}

/**
 * Brief : Collect data and start the simulation
 * Description : Collects all necessary information instantiates the board and the agents and begins running simulations for steps specified.
 *                  if all agents die -> simulation is stopped
 *                  if board is filled with roadrunners -> simulation is stopped.
 * @output - writes information about number of agents alive at each step to a csv. 
 *         - this csv is then used by graph.py to plot the information
 *         - in order to make the graph use the make graph command
 * */

void Simulation::runSimulation()
{
    out_stream.open("out/simulation.csv");
    if (out_stream.fail())
    {
        std::cout << "Output file in out/ failed to open.\n";
        exit(1);
    }
    out_stream << "iteration,coyotes,roadrunners\n";  // csv header

    std::srand(std::time(NULL));  // required for random function usage
    Simulation::getBoardSize();
    //Create grid and controller
    Grid* grid = new Grid(xSize, ySize);
    GridController controller = GridController(grid);

    //get organisms
    Simulation::getRoadrunners();
    controller.createRoadrunners(numRoadrunners);

    Simulation::getCoyotes();
    controller.createCoyotes(numCoyotes);

    controller.writeDataToCsv(out_stream, count);
    //initial board set up display board to user and ask for number of steps next
    controller.display();

    Simulation::getSteps();

    while (count < numSteps) 
    {
        controller.step();
        if(numRoadrunners == 0 && numCoyotes == 0)
        {
            std::cout<<"Exiting simulation since no more agents are alive."<<std::endl; 
            break;
        }
        else if(numRoadrunners == xSize * ySize)
        {
             std::cout<<"Exiting simulation since no more agents can be created."<<std::endl;
             break;
        }
        count++;
        controller.writeDataToCsv(out_stream, count);
    }
    std::cout << "completed iterations: " << count << std::endl;
    std::cout<< "Displaying final board: " <<std::endl;

    controller.display();
    out_stream.close();

}
