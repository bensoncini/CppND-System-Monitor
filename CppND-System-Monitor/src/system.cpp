#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include "process.h"
#include "processor.h"
#include "system.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;

// DONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  	vector<int> pids = LinuxParser::Pids();
  	this->processes_.clear();
    for (int i : pids)
    { 
      	Process hold(i);
        processes_.push_back(hold);
    }
  	sort(processes_.begin(),processes_.end());
    return processes_; 
}

// DONE Return the system's kernel identifier (string)
std::string System::Kernel() { 
  //This is saved into a variable as this function does not require periodic updates as it will likely not change in one session.
    return kernal_name_;
};

// DONE: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization(); 
};

// DONE: Return the operating system name
std::string System::OperatingSystem() { 
    //This is saved into a variable as this function does not require periodic updates as it will likely not change in one session.
    return os_name_; 
};

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();  
};

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
};

// DONE: Return the number of seconds since the system started running
long int System::UpTime() {
    return (long int)LinuxParser::UpTime();
};