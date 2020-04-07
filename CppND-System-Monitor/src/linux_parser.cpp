#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::cout;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        };
      };
    };
  };
  return value;
};

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  };
  return kernel;
};

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      };
    };
  };
  closedir(directory);
  return pids;
  
};

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string name;
  int MemTotal, MemFree, MemAvail, Buffers;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> name >> MemTotal;

    std::getline(stream, line);
    std::istringstream linestream2(line);
    linestream2 >> name >> MemFree;

    std::getline(stream, line);
    std::istringstream linestream3(line);
    linestream3 >> name >> MemAvail;
    
    std::getline(stream, line);
    std::istringstream linestream4(line);
    linestream4 >> name >> Buffers;
  };

  return (((float)MemTotal-(float)MemFree)/(float)MemTotal); 
};

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  float uptime1, uptime2;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime1 >> uptime2;
  };
  return (long)(uptime1); 
};

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; };

// DONE: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::ActiveJiffies(int pid) { 
  int Sys_time = (int)LinuxParser::UpTime();
  int utime, stime, cutime, cstime, starttime, total_time = 0,seconds = 0;
  string hold,line;
  int hertz = sysconf(_SC_CLK_TCK);
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatFilename);
  
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    for (int i=0; i < 22; i++)
    {
      linestream >> hold;
      if (i == 13) {
        utime = stoi(hold);
      };
      if (i == 14) {
        stime = stoi(hold);
      };
      if (i == 15) {
        cutime = stoi(hold);
      };
      if (i == 16) {
        cstime = stoi(hold);
      };
      if (i == 21) {
        starttime = stoi(hold);
      };
    };
    
    total_time = utime + stime + cutime + cstime;
    seconds = Sys_time - (int)((float)starttime/(float)hertz);
    
    return (((float)total_time/(float)hertz)/(float)seconds);
  }; 
  return 0;
};

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; };

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; };

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line,name = {"cpu"};
  vector<string> CPUs;
  string suser, snice, ssystem, sidle, siowait, sirq, ssoftirq, ssteal, sguest, sguest_nice;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> name >> suser >> snice >> ssystem >> sidle >> siowait >> sirq >> ssoftirq >> ssteal >> sguest >> sguest_nice;
  };
  
  CPUs.push_back(suser);
  CPUs.push_back(snice);
  CPUs.push_back(ssystem);
  CPUs.push_back(sidle);
  CPUs.push_back(siowait);
  CPUs.push_back(sirq);
  CPUs.push_back(ssoftirq);
  CPUs.push_back(ssteal);
  CPUs.push_back(sguest);
  CPUs.push_back(sguest_nice);
 
  return CPUs; 
};

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int value1;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (stream.eof() == false){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> key >> value1;
      if (key == "processes") {
          return value1;
      };
    };       
  };
  return 0;
};

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int value1;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (stream.eof() == false){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> key >> value1;
      if (key == "procs_running") {
          return value1;
      };
    };       
  };
  return 0; 
}

// DONE: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) +  kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
  };  
  return line; 
};

// DONE: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string hold,line;
  string name = "";
  long int iKB =0;
  int iMB =0;
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatusFilename);
  if (stream.is_open()) {
    while (name != "VmSize:"){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> name;
    };
    std::istringstream linestream2(line);
    linestream2 >> name >>iKB;
  };  
  
  iMB = (int)(iKB/1024);
  return to_string(iMB); 
};

// DONE: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, uid;
  string name = "";
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatusFilename);
  if (stream.is_open()) {
    
    while (name != "Uid:"){
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> name;
    };
    std::istringstream linestream2(line);
    linestream2 >> name >>uid;
  };  
  return uid; 
};

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, uid;
  string user;
  string user_id1, user_id2, c, name;

  uid = Uid(pid);
  user_id1 = uid + "1";
  user_id2 = uid + "2";

  
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while ((uid != user_id1) || (uid != user_id2)){
      std::getline(stream, line);
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
    
      linestream >> name >> c >> user_id1 >> user_id2;
      
      if ((uid == user_id1) && (uid == user_id2)){
        return name;
      };
    };  
  }; 
  return "BAD";
};

// DONE: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  int Sys_time = (int)LinuxParser::UpTime();
  int starttime, seconds = 0;
  string hold,line;
  int hertz = sysconf(_SC_CLK_TCK);
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatFilename);
  
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    for (int i=0; i < 22; i++)
    {
      linestream >> hold;
      if (i == 21) {
        starttime = stoi(hold);
      };
    };
    seconds = Sys_time - (int)((float)starttime/(float)hertz);
    
    return (long)seconds;
  }; 
  return 0;
};