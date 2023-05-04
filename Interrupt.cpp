#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "headersRTOS/temp.h"


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
    // std::thread interrupt_thread(interrupt_handler);
    // while(true){
    //     current_taskthread.join();
    //     iters=(iters+1)%2;

    // }
    func1();
    std::string input;
    while(true){
        std::cout<<"hello\n";
        if(!interrupt_flag){
            if(std::cin.peek()==EOF){
                std::cin>>input;
                interrupt_flag = 1;
                if(input == "H"){
                    current_taskthread = std::thread(task1);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

    std::cin.get();

    return 0;
}
