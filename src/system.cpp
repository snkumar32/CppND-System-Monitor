#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> process_ids = LinuxParser::Pids();
    std::set<int> seen = {};
    for (auto proc: processes_){
        seen.insert(proc.Pid());
    }
    for (int proc_id: process_ids){
        if (seen.find(proc_id) == seen.end())
            processes_.emplace_back(proc_id);
    }

     for (auto process_cpu: processes_){
        process_cpu.CpuUtilization();
    }

    std::sort(processes_.begin(), processes_.end(), [] (Process & a, Process & b) -> bool
    {
        return a.CpuUtilization() > b.CpuUtilization();
    });
        
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
  std::string os, kernel, vnumber;
  std::string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> vnumber;
  }
  return (vnumber);
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
   return LinuxParser::UpTime();
 }