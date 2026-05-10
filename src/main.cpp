// main.cpp
#include "Controller.h"

int main() {
    Controller controller;

    //Preparing the files and starting the program
    controller.initializeSystem();
    controller.startSimulation();
    
    return 0;
}