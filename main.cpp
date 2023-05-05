#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <unordered_map>
#include "headersRTOS/DisplayTime.h"
#include "headersRTOS/StepCounter.h"
#include "headersRTOS/Task.h"
#include "headersRTOS/Create_Task.h"

using namespace std;


int CpuCycle=0;
Task CountTime=create_task("T");
Task StepCount=create_task("S");

void CountTimer(){
    cout<<"Current Time : ";
    if(CountTime.variables.find("time")==CountTime.variables.end()){
        CountTime.variables["time"]=1;
        for(auto v : DisplayTime(0)) cout<<v<<" ";
        cout<<"\n";
    }else{
        CountTime.variables["time"]+=1;
        for(auto v : DisplayTime(1)) cout<<v<<" ";
        cout<<"\n";
    }
    // cout<<"running count timer"<<'\n';
    // std::chrono::seconds(5);
    
}
void StepCounter(){
    if(StepCount.variables.find("step")==StepCount.variables.end()){
        StepCount.variables["step"]=1;
    }else StepCount.variables["step"]+=1;
    cout<<"Current Steps: "<<countSteps(1)<<"\n";
}
priority_queue<Task> tasklist;

void Schedule()
{
    while (true)
    {
        while (!tasklist.empty()) {
            cout<<"current cpu cycle :"<<CpuCycle<<'\n';
            auto currentTask = tasklist.top();tasklist.pop();
            if(currentTask.CpuCyclesDone==0)
            {
                currentTask.func();
                currentTask.CpuCyclesDone=currentTask.CpuCyclesRequired;
            }
            else currentTask.CpuCyclesDone--;
            CpuCycle += 1;
            tasklist.push(currentTask);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }   
    

}
int main() {
    vector<int> a = DisplayTime(0);
    countSteps(0);
    CountTime.func=CountTimer;
    StepCount.func=StepCounter;
    tasklist.push(StepCount);
    tasklist.push(CountTime);
    cout<<"basic step done now scheduling"<<'\n';
    Schedule();
}
