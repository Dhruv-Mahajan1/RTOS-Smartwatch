
#include <iostream>
#include <ctime>
#include "./headers/DisplayTime.h"
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

vector<int>Time(3,0);
int seconds=0;
time_t now ;
void convert(int seconds)
{

     now += seconds;
     tm *ltm = localtime(&now);
     Time[0]=ltm->tm_hour;
     Time[1]=ltm->tm_min;
     Time[2]=ltm->tm_sec;
    
}



vector<int> DisplayTime(int reset) {
     if(reset==0)
     {
          now= time(0);
          tm *ltm = localtime(&now);
          Time[0]=ltm->tm_hour;
          Time[1]=ltm->tm_min;
          Time[2]=ltm->tm_sec;
     }
     else
     {
          seconds++;
     }
     convert(seconds);
     
     return Time;


}
// int main()
// {
//     DisplayTime(0);
//     for(int i=0;i<10;i++)
//     {
//           DisplayTime(1);
//           std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }
