// Server.cpp
#include "Server.h"

Server::Server() {
    this->freeStatus = true;
    this->remainingTime = 0;
    this->totalServedCount = 0;
}

// Getters
bool Server::isFree() const {
    return freeStatus;
}

bool Server::isBusy() const {
    return !freeStatus;
}

int Server::getRemainingTime() const {
    return remainingTime;
}

int Server::getTotalServedCount() const {
    return totalServedCount;
}

// Assigns a customer to the server
// The server becomes busy and starts serving the customer
void Server::assignCustomer(const Customer& customer) {
    this->currentCustomer = customer;
    this->freeStatus = false;
    this->remainingTime = customer.getServiceTime(); // Set service time based on the customer
}

// Decreases the remaining service time if the server is busy
void Server::updateTime() {
    if (remainingTime > 0) {
        remainingTime--;

        if (remainingTime == 0) {
            finishService();
        }
    }
}

// Returns the customer currently being served
Customer Server::getCurrentCustomer() const {
    return currentCustomer;
}

void Server::finishService() {
    freeStatus = true;
    totalServedCount++;
    currentCustomer = Customer(); // Reset current customer to an empty/default customer
}