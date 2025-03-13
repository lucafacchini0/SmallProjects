#pragma once

#include <string>

class Node {
    public:
        std::string name;
        std::string surname;

        int ticketNumber;

        Node* next;

        Node(std::string name, std::string surname, int ticketNumber)
        : name(name), surname(surname), ticketNumber(ticketNumber) {}
};

class Queue {
    private:
        Node* head;

    public:
        Queue(); 
        //~Queue();

        void enqueueHead(const std::string&, const std::string&, int ticketNumber);
        void enqueueTail(const std::string&, const std::string&, int ticketNumber);

        void removeHead();
        void removeTail();

        void print() const;
};