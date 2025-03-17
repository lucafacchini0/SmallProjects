#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <string>

using namespace std;

void changeWeather(std::map<std::string, int> weather) {
    while(true) {
        for(auto& item : weather) {
            item.second++;

            cout << item.first << " - " << item.second << endl;
        }

    }
}

void destroyWeather() {
    while(true) {
        cout << "Thanos!!!"<<  endl;
    }
}

int main() {
    std::map<std::string, int> weather = {
        {"Milan", 20},
        {"Rome", 30},
        {"Catania", 35}
    };

    std::thread worker(changeWeather, weather);
    std::thread destroyer(destroyWeather);

    worker.join();
    // Warning, the code under will be executed only if `worker` is finished.
    // But since `worker` is an infinite loop, the code under will never be executed.

    
    // destroyer.join();  

    return 0;
}