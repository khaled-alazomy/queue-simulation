// Controller.h
#pragma once
#include <SFML/System.hpp>
#include "Simulation.h"
#include "GUI.h"

class Controller {
private:
    Simulation sim;
    GUI gui;

    sf::Clock tickClock;
    float timePerTick;

public:
    Controller();

    void initializeSystem();
    void startSimulation();
    void updateSystem();
};