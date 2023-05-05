#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "headersRTOS/StepCounter.h"

using namespace std;


int steps;
int lastReading;
int threshold = 20;
int latency = 100; 
// Simulate sensor readings
int random(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int readStepSensor()
{
    int randInt = random(1, 100);
    return randInt;
}

int countSteps(int reset) {
    if(reset==0)
    {
        steps = 0;
        lastReading = 0; 
    }
    int reading = readStepSensor();
    this_thread::sleep_for(std::chrono::milliseconds(latency));
    if (reading > lastReading + threshold)steps++;
    lastReading = reading;
    return steps;
}

// int main() {
//     cout<<countSteps(0)<<'\n';
//     for (int i=0;i<10;i++)
//     {
//         cout<<countSteps(1)<<'\n';
//         this_thread::sleep_for(std::chrono::seconds(2));
//     }


//     return 0;
// }
