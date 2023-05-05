#include <string>
#include "headersRTOS/Task.h"
#include "headersRTOS/Create_Task.h"

// Task Name/ Priority/ Cycles
Task create_task(std::string type){
    //Create heart rate monitoring Task
    Task ret = Task{};
    if(type == "H"){
        ret = Task{"Heart Rate Monitoring",1,1};
    }
    // Create Step Counter Task
    else if(type == "S"){
        ret = Task{"Step Count",1,3};
    }
    // Create Time Task
    else if(type == "T"){
        ret = Task{"Show Time",1 ,4};
    }
    // Throw Error 
    else{
        ret =  Task{"Problem",100,1};
    }
    return ret;
}


