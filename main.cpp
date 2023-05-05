#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <unordered_map>
#include <semaphore.h>
#include "headersRTOS/UpdateTime.h"
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
    if(CountTime.variables.find("time")==CountTime.variables.end()){
        vector<int>v=updateTime(0,CpuCycle);
        CountTime.variables["hour"]=v[0];
        CountTime.variables["minute"]=v[1];
        CountTime.variables["seconds"]=v[2];
        
    }else{
        vector<int>v=updateTime(1,CpuCycle);
        CountTime.variables["hour"]=v[0];
        CountTime.variables["minute"]=v[1];
        CountTime.variables["seconds"]=v[2];
    }
    
    
}
void StepCounter(){
    if(StepCount.variables.find("step")==StepCount.variables.end()){
        StepCount.variables["step"]=countSteps(0);
    }else StepCount.variables["step"]+=countSteps(1);
    
}

void Schedule()
{
    cout<<"Scheduling the two background tasks "<<endl;
    while (true)
    {   
        // cout<<"CpuCycle is "<< CpuCycle<<endl;
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
            if(currentTask.name=="Heart Rate Monitoring") CpuCycle+=10;
            else CpuCycle += 1;
            if(!done) tasklist.push(currentTask);
            else{
                if(currentTask.periodic) tasklist.push(currentTask);
            }
        }
        sem_post(sem);
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::seconds(1));
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
            if(input == "Show Heart Rate"){
                Task temp = create_task("H");
                cout<<temp.CpuCyclesRequired<<'\n';
                temp.func = heartRate;
                tasklist.push(temp);
            }
            if(input == "Show Steps"){
               cout<<"No of Steps : "<<StepCount.variables["step"]<<"\n";
            }
            if(input == "Show Time"){
               cout<<"Current Time : "<<CountTime.variables["hours"]<<" : "<<CountTime.variables["minute"]<<" : "<<CountTime.variables["seconds"]<<"\n";
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
