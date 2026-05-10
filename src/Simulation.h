// Simulation.h
#pragma once
#include <vector>
#include <random>
#include "Server.h"
#include "CustomerQueue.h"

class Simulation {
private:
    int currentTime;
    int maxSimulationTime;
    int totalCustomersArrived;
    int totalCustomersServed;
    int nextArrivalTime;

    std::vector<Server> servers;
    CustomerQueue customerQueue;
    std::vector<int> queueHistory;

    bool isRunning;
    bool isPaused;

    std::mt19937 rng;

    int getRandomInt(int min, int max);
    bool getRandomVIP();

public:
    Simulation();

    void initializeSimulation();
    void updateSimulation();
    void processArrival();
    void updateServers();
    void assignCustomersToServers();

    int getCurrentTime() const;
    int getMaxTime() const;
    int getArrivedCount() const;
    int getServedCount() const;
    bool getIsRunning() const;

    const std::vector<Server>& getServers() const;
    const CustomerQueue& getQueue() const;
    const std::vector<int>& getQueueHistory() const;

    void togglePause();
    bool getIsPaused() const;
};