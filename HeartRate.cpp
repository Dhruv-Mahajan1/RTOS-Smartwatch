
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "headersRTOS/HeartRate.h"

using namespace std;


int randv(int a ,int b){
    return a + rand()%(b-a+1);
}

void heartRate(){
    cout<<"Gathering Data : ";
    int total = 0;
    for(int i = 0;i<10;i+=1){
        int cur = randv(60,90);
        cout<<cur<<" ";
        total+=cur;
        cout.flush();
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    cout<<"\n";
    cout<<"Heart Rate : "<<total/10<<'\n';
}