// Controller.cpp
#include "Controller.h"

// Sets the simulation to update once every 1 second
// 1 second = 1 simulation tick
Controller::Controller() : timePerTick(1.0f) {}

void Controller::initializeSystem() {
    // The settings configuration and connecting the controller to the simulation
    sim.initializeSimulation();
    gui.initializeWindow();
    gui.connectToSimulation(&sim);
}

void Controller::startSimulation() {
    // When the app is running the system is updated using the function updateSystem
    while (gui.isOpen()) {
        gui.handleEvents(); // Handle keyboard, mouse, and window events
        updateSystem();     // Update simulation based on time
        gui.updateGUI();    // Redraw the GUI every frame
    }
}

// Updates the simulation based on the tick clock
// The simulation updates only after timePerTick seconds have passed
void Controller::updateSystem() {
    if (tickClock.getElapsedTime().asSeconds() >= timePerTick) {

        // Update simulation only if it is running and not paused
        if (sim.getIsRunning() && !sim.getIsPaused()) {
            sim.updateSimulation();
        }

        // Restart the clock to begin counting for the next tick
        tickClock.restart();
    }
}