#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <unordered_map>
#include <semaphore.h>
#include "headersRTOS/DisplayTime.h"
#include "headersRTOS/StepCounter.h"
#include "headersRTOS/Task.h"
#include "headersRTOS/Create_Task.h"
#include "headersRTOS/HeartRate.h"

using namespace std;
#define O_CREAT 0x00000200

int CpuCycle=0;
Task CountTime=create_task("T");
Task StepCount=create_task("S");
priority_queue<Task> tasklist;
sem_t *sem;

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

void Schedule()
{
    while (true)
    {   
        sem_wait(sem);
        if(!tasklist.empty()) {
            // cout<<"current cpu cycle :"<<CpuCycle<<'\n';
            auto currentTask = tasklist.top();tasklist.pop();
            bool done = 0;
            if(currentTask.CpuCyclesDone==0)
            {
                currentTask.func();
                currentTask.CpuCyclesDone=currentTask.CpuCyclesRequired;
                done = 1;
            }
            else currentTask.CpuCyclesDone--;
            CpuCycle += 1;
            if(!done) tasklist.push(currentTask);
            else{
                if(currentTask.periodic) tasklist.push(currentTask);
            }
        }
        sem_post(sem);
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }   
    

}
int main() {
    
    CountTime.func=CountTimer;
    StepCount.func=StepCounter;
    tasklist.push(StepCount);
    tasklist.push(CountTime);
    cout<<"Basic Setup Done...\n";
    thread Scheduler(Schedule);
    string input;
    sem_unlink("/my_semaphore");
    sem = sem_open("/my_semaphore", O_CREAT, 0644, 1);
    
    // cout<<"basic step done now scheduling"<<'\n';
    
    while(true){
        if(std::cin.peek()!=EOF){
            // std::cin>>input;
            std::getline(std::cin,input);
            // std::cout<<input<<"\n";
            sem_wait(sem);
            if(input == "H"){
                Task temp = create_task("H");
                cout<<temp.CpuCyclesRequired<<'\n';
                temp.func = heartRate;
                tasklist.push(temp);
            }
            sem_post(sem);
            // cout<<"out\n";
        }
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }
    sem_close(sem);
    sem_unlink("/my_semaphore");
}
