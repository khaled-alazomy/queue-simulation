// Simulation.cpp
#include "Simulation.h"

// Constructor
Simulation::Simulation() {
    this->currentTime = 0;
    this->maxSimulationTime = 0;
    this->totalCustomersArrived = 0;
    this->totalCustomersServed = 0;
    this->nextArrivalTime = 0;
    this->isRunning = false;
    this->isPaused = false;

    // Initialize random number generator with a random seed
    rng.seed(std::random_device{}());
}

// Returns a random integer between min and max inclusive
int Simulation::getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Randomly decides if a customer is VIP with a 20% chance
bool Simulation::getRandomVIP() {
    std::uniform_int_distribution<int> dist(1, 100);
    return dist(rng) <= 20; // 20% chance of being VIP
}

// Initializes the simulation settings
// This function should be called before running the simulation
void Simulation::initializeSimulation() {
    currentTime = 0;
    maxSimulationTime = 80; // Default max simulation time

    totalCustomersArrived = 0;
    totalCustomersServed = 0;
    nextArrivalTime = 0;

    isRunning = true;
    isPaused = false;

    customerQueue.clearQueue(); // Clear the queue directly using the new public function
    queueHistory.clear();       // Clear old queue history

    int numServers = 3;         // Default number of servers
    servers.clear();
    servers.resize(numServers);

    // Set the first customer arrival time after 1 or 2 time ticks
    nextArrivalTime = currentTime + getRandomInt(1, 2);
}

// Updates the whole simulation by one time tick
// This function is usually called repeatedly by the GUI or main loop
void Simulation::updateSimulation() {
    if (!isRunning || isPaused) {
        return; // Do nothing if the simulation is not running or is paused
    }

    // Stop the simulation when the maximum simulation time is reached
    if (currentTime >= maxSimulationTime) {
        isRunning = false;
        return;
    }

    updateServers();                // Update the status of all servers
    processArrival();               // Handle new customer arrivals
    assignCustomersToServers();     // Assign waiting customers to free servers

    // Save the current queue size for graph drawing
    queueHistory.push_back(customerQueue.getQueueSize());

    currentTime++; // Move to the next time tick
}

// Handles new customer arrival
// A new customer is created when currentTime reaches nextArrivalTime
void Simulation::processArrival() {
    if (currentTime == nextArrivalTime) {
        totalCustomersArrived++; // Increment total customers arrived

        // Create a new customer with random service time and VIP status
        int serviceTime = getRandomInt(5, 10); // Random service time between 5 and 10
        bool isVip = getRandomVIP();           // Randomly determine if the customer is VIP

        // Create a new customer with ID, arrival time, service time, and VIP status
        Customer newCustomer(
            totalCustomersArrived,
            currentTime,
            serviceTime,
            isVip
        );

        // Add the new customer to the queue
        customerQueue.enqueueCustomer(newCustomer);

        // Schedule the next customer arrival after 1 or 2 time ticks
        nextArrivalTime = currentTime + getRandomInt(1, 2);
    }
}

// Updates all servers by one time tick
void Simulation::updateServers() {
    for (int i = 0; i < servers.size(); i++) {
        bool wasBusy = servers[i].isBusy();

        servers[i].updateTime();

        // If the server was busy and became free, then one customer has finished service
        if (wasBusy && servers[i].isFree()) {
            totalCustomersServed++;
        }
    }
}

// Assigns customers from the queue to free servers
void Simulation::assignCustomersToServers() {
    for (int i = 0; i < servers.size(); i++) {
        if (servers[i].isFree() && !customerQueue.isQueueEmpty()) {
            Customer nextCustomer = customerQueue.dequeueCustomer();
            servers[i].assignCustomer(nextCustomer);
        }
    }
}

// Returns the current simulation time
int Simulation::getCurrentTime() const {
    return currentTime;
}

// Returns the maximum simulation time
int Simulation::getMaxTime() const {
    return maxSimulationTime;
}

// Returns the total number of customers that arrived
int Simulation::getArrivedCount() const {
    return totalCustomersArrived;
}

// Returns the total number of customers that finished service
int Simulation::getServedCount() const {
    return totalCustomersServed;
}

// Returns whether the simulation is still running
bool Simulation::getIsRunning() const {
    return isRunning;
}

// Returns all servers for GUI display
const std::vector<Server>& Simulation::getServers() const {
    return servers;
}

// Returns the customer queue for GUI display
const CustomerQueue& Simulation::getQueue() const {
    return customerQueue;
}

// Returns queue size history for drawing the graph
const std::vector<int>& Simulation::getQueueHistory() const {
    return queueHistory;
}

// Switches the pause state between paused and not paused
void Simulation::togglePause() {
    isPaused = !isPaused;
}

// Returns whether the simulation is paused
bool Simulation::getIsPaused() const {
    return isPaused;
}