#include <iostream>
#include <thread>
#include<bits/stdc++.h>
#include <chrono>
using namespace std;


int CpuCycle=0;

struct Task {
    string name;
    const int CpuCyclesRequired;
    void(*func)();
    int CpuCyclesDone=CpuCyclesRequired;
    unordered_map<string,int>variables;
    
};

Task CountTime={"Count Time",4};
Task StepCount={"Step Count",3};

void CountTimer(){
    if(CountTime.variables.find("time")==CountTime.variables.end())
    CountTime.variables["time"]=1;
    else CountTime.variables["time"]+=1;

    cout<<"runiing count timer"<<'\n';
    // std::chrono::seconds(5);
    
}
void StepCounter(){
    if(StepCount.variables.find("step")==StepCount.variables.end())
    StepCount.variables["step"]=1;
    else StepCount.variables["step"]+=1;
    cout<<"runiing Step timer"<<'\n';
    // std::chrono::seconds(5);

    
}




// priority_queue<pair<int,Task>> tasklist;
queue<pair<int,Task>> tasklist;

void Schedule()
{
    while (true)
    {
        while (!tasklist.empty()) {
            cout<<"current cpu cycle :"<<CpuCycle<<'\n';
            auto  currenttask = tasklist.front();tasklist.pop();
            if(currenttask.second.CpuCyclesDone==0)
            {
                currenttask.second.func();
                currenttask.second.CpuCyclesDone=currenttask.second.CpuCyclesRequired;
            }
            else currenttask.second.CpuCyclesDone--;
            CpuCycle += 1;
            tasklist.push(currenttask);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }   
    

}
int main() {
    CountTime.func=CountTimer;
    StepCount.func=StepCounter;
    tasklist.push({1,StepCount});
    tasklist.push({2,CountTime});
    cout<<"basic step done now scheduling"<<'\n';
    Schedule();
}
