
#include <iostream>
#include <ctime>
#include "headersRTOS/UpdateTime.h"
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

vector<int> Time(3,0);
int seconds;
time_t now ;
int init_cycles;

void convert(int sec)
{

     time_t cur_time = now + sec;
     tm *ltm = localtime(&cur_time);
     Time[0]=ltm->tm_hour;
     Time[1]=ltm->tm_min;
     Time[2]=ltm->tm_sec;
    
}



vector<int>  updateTime(int reset,int cycles) {
     if(reset==0)
     {
          init_cycles = 0;
          seconds = 0;
          now= time(0);
          tm *ltm = localtime(&now);
          Time[0]=ltm->tm_hour;
          Time[1]=ltm->tm_min;
          Time[2]=ltm->tm_sec;
     }
     else
     {
          seconds = (cycles-1)/5;
     }
     convert(seconds);
     
     return Time;


}
// int main()
// {
//     UpdateTime(0);
//     for(int i=0;i<10;i++)
//     {
//           UpdateTime(1);
//           std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }
