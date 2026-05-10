// Server.h
#pragma once
#include "Customer.h"

class Server {
private:
    bool freeStatus;
    int remainingTime;
    int totalServedCount;
    Customer currentCustomer;

public:
    Server();

    bool isFree() const;
    bool isBusy() const;
    int getRemainingTime() const;
    int getTotalServedCount() const;

    void assignCustomer(const Customer& customer);
    void updateTime();
    Customer getCurrentCustomer() const;
    void finishService();
};