#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <queue>
#include <semaphore.h>

// #include "headersRTOS/temp.h"


bool interrupt_flag = 0;
std::priority_queue<int> que;
sem_t *sem;
void task1(){
    while(true){
        std::cout<<"hi\n";
        sem_wait(sem);
        if(!que.empty()){
            int top = que.top();
            que.pop();
            std::cout<<"Current Task :"<<top<<'\n';
            que.push(top);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        sem_post(sem);
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
}


int main() {
    int iters = 0;
    que.push(1);
    sem_unlink("/my_semaphore");
    std::thread Scheduler(task1);
    std::string input;
    sem = sem_open("/my_semaphore", O_CREAT, 0644, 1);
    while(true){
        // std::cout<<"hello\n";
        if(!interrupt_flag){
            if(std::cin.peek()!=EOF){
                // std::cin>>input;
                std::getline(std::cin,input);
                std::cout<<input<<"\n";
                sem_wait(sem);
                if(input == "H"){
                    std::cout<<"in\n";
                    interrupt_flag = 0;
                    que.push(2);
                }
                sem_post(sem);
            }
        }
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }
    sem_close(sem);
    sem_unlink("/my_semaphore");

    std::cin.get();

    return 0;
}
