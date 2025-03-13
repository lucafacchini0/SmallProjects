#include <iostream>
#include "include/queue.h"
#include "include/colors.h"

Queue::Queue() : head(nullptr) {}

void Queue::enqueueHead(const std::string& name, const std::string& surname, int ticketNumber) {
    Node* newNode = new Node(name, surname, ticketNumber);
    newNode->next = head;
    head = newNode;
}

void Queue::enqueueTail(const std::string& name, const std::string& surname, int ticketNumber) {
    Node* newNode = new Node(name, surname, ticketNumber);
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;

    std::cout << Color::BLUE << name << " si è messo in coda!" << std::endl;
}

void Queue::removeHead() {
    if (head == nullptr) {
        std::cout << Color::BOLDRED << "Non c'è nessuno in coda!" << Color::RESET << std::endl;
        return;
    }

    Node* temp = head;
    head = head->next;

    delete temp;
}

void Queue::removeTail() {
    if (head == nullptr) {
        std::cout << Color::BOLDRED << "Non c'è nessuno in coda!" << Color::RESET << std::endl;
        return;
    }
    
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* temp = head;

    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    
    delete temp->next;
    temp->next = nullptr;
}

void Queue::print() const {
    if (head == nullptr) {
        std::cout << Color::BOLDRED << "Non c'è nessuno in coda!" << Color::RESET << std::endl;
        return;
    }

    Node* temp = head;

    std::cout << Color::BOLDYELLOW << "Numero\t\tNome\t\tCognome" << Color::RESET << std::endl;

    while (temp != nullptr) {
        std::cout << "   " << temp->ticketNumber << "\t\t" << temp->name << "\t\t" << temp->surname << std::endl;
        temp = temp->next;
    }
    std::cout << std::endl;
}
