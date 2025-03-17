#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <algorithm> 
#include <cctype>    
#include <cstdlib>
#include <ctime>
#include <future>
#include <mutex>
#include <limits>
#include "include/queue.h"
#include "include/colors.h"

using namespace std;

void welcome();
void cs();
void freeze(int);
bool isYes(const string&);
void start();
int getUserInputWithTimeout(int timeout);

// Queue management
Queue queue;
int ticketNumber = 0;

// Points management
int points = 0;

mutex cout_mutex;

int main() {
    welcome();
}

int getUserInputWithTimeout(int timeout) {
    promise<int> prom;
    future<int> fut = prom.get_future();
    
    thread inputThread([&prom]() {
        int answer;
        cin >> answer;
        prom.set_value(answer);
    });
    
    if (fut.wait_for(chrono::seconds(timeout)) == future_status::timeout) {
        inputThread.detach();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    } else {
        inputThread.join();
        return fut.get();
    }
}

void start() {
    cs(); // Pulisce lo schermo
    srand(time(nullptr));

    while(true) {

        // Imposta i valori random
        int num1 = rand() % 25;
        int num2 = rand() % 53;
        int timeout = (rand() % 6) + 5; 

        // mt: fa in modo che 
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Quanto fa " << Color::YELLOW << num1 << Color::RESET << " + " << Color::YELLOW << num2 << Color::RESET << "? ";
        }

        int answer = getUserInputWithTimeout(timeout);

        cs();

        {
            lock_guard<mutex> lock(cout_mutex);
            if (answer == num1 + num2) {
                points++;
                cout << Color::GREEN << "Congratulazioni!" << Color::RESET << endl;
            } else {
                cout << Color::RED << "Il cliente si è spazientito ed è scappato." << Color::RESET << endl;
            }
        }
    }
}

void welcome() {
    cs();
    cout << endl;
    cout << Color::BOLDBLUE << "Benvenuti su Banchiere Simulator!" << Color::RESET << endl;
    cout << "Versione 0.1 | Creato da Luca Facchini, 4H" << endl;
    cout << endl;

    freeze(0);
    cout << "In questo gioco tu sarai un banchiere, e dovrai gestire la fila di persone" << endl;
    cout << "nel modo più efficiente possibile. " << endl;
    cout << endl;

    freeze(0);
    cout << "Per fare ciò, dovrai rispondere a dei " << Color::BOLDYELLOW << "quiz di aritmetica" << Color::RESET << " nel" << endl;
    cout << "minor tempo possibile, ma attento a non metterci troppo tempo," << endl;
    cout << "altrimenti... beh, il " << Color::RED << "cliente potrebbe spazientirsi!" << Color::RESET << endl;
    cout << endl;

    freeze(0);
    cout << "Se sei pronto, digita " << Color::BOLDGREEN << "yes" << Color::RESET << ": ";

    string choice;
    cin >> choice;

    if (isYes(choice)) {
        start();
    } else {
        exit(0);
    }
}

void cs() {
    cout << "\033[2J\033[H";
}

void freeze(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

bool isYes(const string& choice) {
    string lowerChoice = choice;
    transform(lowerChoice.begin(), lowerChoice.end(), lowerChoice.begin(), ::tolower);
    return lowerChoice == "yes" || lowerChoice == "y";
}