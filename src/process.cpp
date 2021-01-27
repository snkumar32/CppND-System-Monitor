#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>

#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
    process_pid = pid;
}

// TODO: Return this process's ID
int Process::Pid() { return process_pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    float stime, utime, cutime, cstime, starttime, hertz, totaltime, sec;
    std::string line;
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        std::vector<std::string> result(std::istream_iterator<std::string>{linestream}, std::istream_iterator<std::string>());
        utime = stof(result[13]);
        stime = stof(result[14]);
        cutime = stof(result[15]);
        cstime = stof(result[16]);
        starttime = stof(result[21]);
        hertz = sysconf(_SC_CLK_TCK);

        totaltime = utime + stime + cutime + cstime;
        sec = LinuxParser::UpTime() - (starttime/hertz);
        cpu_utilization = (totaltime/hertz)/sec;
    }
    return cpu_utilization;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    std::string line, cmd;
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kCmdlineFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);;
        linestream >> cmd;
    }
    return cmd;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    std::string line, key;
    int value, ram;

    std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) +  LinuxParser::kStatusFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "VmSize"){
                    ram = value/1000;
                }
            }
        }
    }
    return to_string(ram);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    std::string line, key, value, 
    uid_num;
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) +  LinuxParser::kStatusFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "Uid"){
                    uid_num = value;
                }
            }
        }
    }
    return getUsername(uid_num);
}

std::string Process::getUsername(std::string uid_num){
    std::string username, perm, num, line, key, value;
    std::ifstream stream(LinuxParser::kPasswordPath);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> username >> perm >> num) {
                if (num == uid_num){
                    return username;
                }
            }
        }
    }
    return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    long int starttime, hertz, uptime = 0.0;
    std::string line;
    std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        std::vector<std::string> result(std::istream_iterator<std::string>{linestream}, std::istream_iterator<std::string>());
        starttime = stol(result[21]);
        hertz = sysconf(_SC_CLK_TCK);
        uptime = starttime/hertz;
    }
    return uptime;
 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }