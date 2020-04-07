#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp
  	
  // DONE: Declare any necessary private members
 private:
  	vector<string> core_ = LinuxParser::CpuUtilization();
};

#endif