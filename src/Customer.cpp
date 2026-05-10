// Customer.cpp
#include "Customer.h"

Customer::Customer() {
    this->id = 0;
    this->arrivalTime = 0;
    this->serviceTime = 0;
    this->isVip = false;
}

Customer::Customer(int id, int arrivalTime, int serviceTime, bool isVip) {
    this->id = id;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->isVip = isVip;
}

// Getters
int Customer::getId() const {
    return id;
}

int Customer::getArrivalTime() const {
    return arrivalTime;
}

int Customer::getServiceTime() const {
    return serviceTime;
}

bool Customer::getIsVIP() const {
    return isVip;
}