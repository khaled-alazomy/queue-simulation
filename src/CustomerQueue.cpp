// CustomerQueue.cpp
#include "CustomerQueue.h"

// Node constructor
CustomerQueue::Node::Node(Customer c) {
    data = c;
    next = nullptr;
}

// Helper function to append a node at the end (used in copy operations)
void CustomerQueue::appendNode(Customer c) {
    Node* newNode = new Node(c);

    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    count++;
}

// Default Constructor
CustomerQueue::CustomerQueue() {
    front = nullptr;
    rear = nullptr;
    count = 0;
}

// Copy Constructor (Deep Copy)
CustomerQueue::CustomerQueue(const CustomerQueue& other) {
    front = nullptr;
    rear = nullptr;
    count = 0;

    Node* temp = other.front;

    while (temp != nullptr) {
        appendNode(temp->data);
        temp = temp->next;
    }
}

// Copy Assignment Operator (Deep Copy)
CustomerQueue& CustomerQueue::operator=(const CustomerQueue& other) {
    if (this != &other) {
        clearQueue();

        Node* temp = other.front;

        while (temp != nullptr) {
            appendNode(temp->data);
            temp = temp->next;
        }
    }

    return *this;
}

// Destructor
CustomerQueue::~CustomerQueue() {
    clearQueue();
}

// Helper function to clear the queue
void CustomerQueue::clearQueue() {
    Node* temp = front;

    while (temp != nullptr) {
        Node* delptr = temp;
        temp = temp->next;
        delete delptr;
    }

    front = nullptr;
    rear = nullptr;
    count = 0;
}

// Enqueue customer, maintaining VIP priority
void CustomerQueue::enqueueCustomer(Customer c) {
    Node* newNode = new Node(c);

    // Case 1: If the queue is empty
    if (isQueueEmpty()) {
        front = rear = newNode;
        count++;
        return;
    }

    // Case 2: If the customer is normal, add to the rear of the queue
    if (!c.getIsVIP()) {
        rear->next = newNode;
        rear = newNode;
        count++;
        return;
    }

    // --- VIP Customer Handling ---
    // From here on, we know the new customer is a VIP

    // Case 3: If the front customer is normal, the VIP jumps to the front
    if (!front->data.getIsVIP()) {
        newNode->next = front;
        front = newNode;
        count++;
        return;
    }

    // Case 4: Find the last VIP in the queue to insert the new VIP after them
    Node* temp = front;

    // Traverse as long as the next node exists AND the next node is also a VIP
    while (temp->next != nullptr && temp->next->data.getIsVIP()) {
        temp = temp->next;
    }

    // Insert the new VIP customer in the correct position
    newNode->next = temp->next;
    temp->next = newNode;

    // If the new VIP was inserted at the very end of the queue, update the rear pointer
    if (newNode->next == nullptr) {
        rear = newNode;
    }

    count++;
}

// Dequeue the front customer and return it
Customer CustomerQueue::dequeueCustomer() {
    if (isQueueEmpty()) {
        return Customer();
    }

    Node* temp = front;
    Customer frontCustomer = temp->data;

    front = front->next;
    delete temp;
    count--;

    // If the queue becomes empty after dequeuing, reset the rear pointer as well
    if (front == nullptr) {
        rear = nullptr;
    }

    return frontCustomer;
}

// Check if the queue is empty
bool CustomerQueue::isQueueEmpty() const {
    return count == 0;
}

// Get the current size of the queue
int CustomerQueue::getQueueSize() const {
    return count;
}

// Get customer data at a specific index
Customer CustomerQueue::getCustomerAtIndex(int index) const {
    if (index < 0 || index >= count) {
        return Customer();
    }

    Node* temp = front;

    // Traverse the linked list until the desired index is reached
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp->data;
}