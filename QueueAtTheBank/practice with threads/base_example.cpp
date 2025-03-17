/**
 * @file ex1.cpp
 * @author Luca Facchini
 * @brief Print 1-10 numbers with a thread
 * @version 0.1
 * @date 2025-03-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <thread>

void printNumbers();

int main() {
    std::thread t(printNumbers); // Creates a thread that executes printNumbers.
    t.join(); // Wait for the thread to finish.
    return 0;
}

void printNumbers() {
    for(int i = 0; i < 10; i++) {
        std::cout << i+1;
    }
}

/*

Time line

1. Program joins main()
2. std::thread is called, this created a second thread that calls printNumbers. 
    it starts working in parallel with main(). 
3. the thread starts printing the numbers. this happens in parallel with the main 
    functions, but in this case there are no conflicts because the console is not
    being used by both threads.
4. when the main thread reaches t.join(), it MUST wait the second thread to finish. 
*/
