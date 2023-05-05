#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
// #include "headersRTOS/temp.h"


bool interrupt_flag = 0;
void task1(){
    for(int i = 0;i<10;i++){
        std::cout<<i+1<<" : counter\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    interrupt_flag = 0;
}

int main() {
    int iters = 0;
    std::thread current_taskthread;
    std::string input;
    while(true){
        std::cout<<"hello\n";
        if(!interrupt_flag){
            if(std::cin.peek()!=EOF){
                // std::cin>>input;
                std::getline(std::cin,input);
                std::cout<<input<<"\n";
               
                if(input == "H"){
                    interrupt_flag = 1;
                    current_taskthread = std::thread(task1);
                    current_taskthread.join();
                }
                
            }
        }
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }

    std::cin.get();

    return 0;
}
