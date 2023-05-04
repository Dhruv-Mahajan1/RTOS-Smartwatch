#include <iostream>
#include <thread>
#include <chrono>
int time = 0;
int cpu_clock= 0;
void clock_counter(){
    time++;
    // for(int i = 0i<10;i++){
    //     cout<<" "
    // }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void cpu_counter(){
    cpu_clock++;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}


int main() {
    std:: thread worker2[2];
    worker
    worker.join();    
    std::cin.get();

    return 0;
}
