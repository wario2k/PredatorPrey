/*
@file : main.cpp
*/

#include "controller.hpp"
#include "grid.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ofstream out_stream;
    std::string temp;
    int count = 0;
    bool interactive_mode = false;

    out_stream.open("out/simulation.csv");
    if (out_stream.fail())
    {
        std::cout << "Output file in out/ failed to open.\n";
        exit(1);
    }
    out_stream << "iteration,coyotes,roadrunners\n";  // csv header

    std::srand(std::time(NULL));  // required for random function usage
    int num = 0, xVal = 0, yVal = 0;
        std::cout<<"Enter Number Of Rows in Grid [X] :";
        
        std::cin >>xVal;
        Grid* grid = new Grid(xVal, xVal);
        GridController controller = GridController(grid);
        std::cout<<std::endl;

    
    std::cout << "Creating organisms..." << std::endl;
    std::cout<<"Enter Number of Roadrunners: ";
    std::cin>>num;

    controller.createRoadrunners(num);

    std::cout<<"Number of Coyotes: ";
    std::cin>>num;

    controller.createCoyotes(num);
    controller.writeDataToCsv(out_stream, count);
    controller.display();

    // After each time step, prompt the user to press
    // Enter to move to the next time step.

    std::cout <<"Please enter the number of steps you would like to simulate: ";
    int simSteps = -1;
    std::cin>>simSteps;
    if(simSteps > 0)
    {
        while (count < num) 
        {
            controller.step();
            count++;
            controller.writeDataToCsv(out_stream, count);
        }
        std::cout << "completed iterations: " << count << std::endl;
    }
    else
    {
        std::cout<<"out of bounds!";
        out_stream.close();
        exit(0);
    }

    out_stream.close();
    std::cout<<"Please use make run chart to view results."<<std::endl;
    return 0;

}