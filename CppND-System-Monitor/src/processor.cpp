#include "processor.h"
#include <string>
using std::stoi;

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
    int iuser, inice, isystem, iidle, iiowait, iirq, isoftirq, isteal;
    float Idle, NonIdle, Total;

    iuser = stoi(core_[0]);
    inice = stoi(core_[1]);
    isystem = stoi(core_[2]);
    iidle = stoi(core_[3]);
    iiowait = stoi(core_[4]);
    iirq = stoi(core_[5]);
    isoftirq = stoi(core_[6]);
    isteal = stoi(core_[7]);

    NonIdle = float(iuser + inice + isystem + iirq + isoftirq + isteal);
    Idle = float(iidle + iiowait);
    Total = float(NonIdle + Idle);
 
    return  (Total - Idle) / Total; 
};