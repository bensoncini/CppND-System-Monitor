#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h" 

#include <iostream>
using std::cout;

using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid) {
  pid_ = pid;
  user_ = LinuxParser::User(pid);
  util_ = LinuxParser::ActiveJiffies(pid);
  command_ = LinuxParser::Command(pid);
  age_ = LinuxParser::UpTime(pid);
  ram_ = LinuxParser::Ram(pid);
  
};

// DONE: Return this process's ID
int Process::Pid() { 
  return pid_; 
};

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  return util_; 
}

// DONE: Return the command that generated this process
string Process::Command() { 
  return command_; 
};

// TODO: Return this process's memory utilization
string Process::Ram() { 
  return ram_; 
};

// DONE: Return the user (name) that generated this process
string Process::User() {
  //cout << Process::pid_ + " " + Process::user_ << "\n";
  return user_; 
};

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() {
  return age_; 
};

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->CpuUtilization() > a.CpuUtilization(); 
};