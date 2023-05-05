#ifndef Task_H
#define Task_H
#include <string>
#include <unordered_map>

struct Task {
    std::string name;
    int priority;
    int CpuCyclesRequired;
    int periodic;
    void(*func)();
    int CpuCyclesDone=CpuCyclesRequired;
    std::unordered_map<std::string,int>variables;

    bool operator<(const Task &y) const{
        return priority<y.priority;
    }
    
};
#endif