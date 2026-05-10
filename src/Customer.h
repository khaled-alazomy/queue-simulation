// Customer.h
#pragma once

class Customer {
private:
    int id;
    int arrivalTime;
    int serviceTime;
    bool isVip;

public:
    Customer();
    Customer(int id, int arrivalTime, int serviceTime, bool isVip);

    // Getters
    int getId() const;
    int getArrivalTime() const;
    int getServiceTime() const;
    bool getIsVIP() const;
};