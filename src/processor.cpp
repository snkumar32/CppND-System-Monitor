#include "processor.h"
#include "linux_parser.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float prev_idle_time = 0;
    float prev_rem_time = 0;
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice, 
             idle_total, total;
    std::string line, key;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> user >> nice >> system >> idle >>iowait >> irq >> softirq >> steal >> guest >> guest_nice){
                if (key == "cpu") {
                    curr_idle_time = idle + iowait;
                    curr_total_time = curr_idle_time + user + nice + system + irq + softirq + steal;
                    idle_total = curr_idle_time - prev_idle_time;
                    total = curr_total_time - prev_rem_time;
                    utilization_percentage = (total - idle_total)/total;
                }
            } 
        }
    }    
   return utilization_percentage;
}

float Processor::getIdleTime() { 
    return curr_idle_time;
}
float Processor::getTotalTime() { 
    return curr_total_time;
}