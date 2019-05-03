/*
@file : main.cpp - driver program
*/

#include "controller.hpp"
#include "grid.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "simulation.hpp"

int main()
{
    Simulation* simInstance = Simulation::getInstance(); 
    simInstance->runSimulation();
    return 0;

}