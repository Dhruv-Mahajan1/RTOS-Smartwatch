#include <string>
#include "headersRTOS/Task.h"
#include "headersRTOS/Create_Task.h"

// Task Name/ Priority/ Cycles
Task create_task(std::string type){
    //Create heart rate monitoring Task
    Task ret = Task{};
    if(type == "H"){
        ret = Task{"Heart Rate Monitoring",3,1,0};
    }
    // Create Step Counter Task
    else if(type == "S"){
        ret = Task{"Step Count",1,3,1};
    }
    // Create Time Task
    else if(type == "T"){
        ret = Task{"Show Time",1 ,4,1};
    }
    // Set Alarm
    else if(type == "A"){
        ret = Task{"Alarm Task",2,1,0};
    }
    // Throw Error 
    else{
        ret =  Task{"Problem",100,1,1};
    }
    return ret;
}


