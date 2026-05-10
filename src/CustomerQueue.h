// CustomerQueue.h
#pragma once
#include "Customer.h"

class CustomerQueue {
private:
    struct Node {
        Customer data;
        Node* next;

        // Node constructor
        Node(Customer c);
    };

    Node* front;
    Node* rear;
    int count;

    void appendNode(Customer c);

public:
    CustomerQueue();
    CustomerQueue(const CustomerQueue& other);
    CustomerQueue& operator=(const CustomerQueue& other);
    ~CustomerQueue();

    void clearQueue();
    void enqueueCustomer(Customer c);
    Customer dequeueCustomer();

    bool isQueueEmpty() const;
    int getQueueSize() const;
    Customer getCustomerAtIndex(int index) const;
};