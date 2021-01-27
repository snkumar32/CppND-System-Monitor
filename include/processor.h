#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  float getIdleTime();
  float getTotalTime();

  // TODO: Declare any necessary private members
 private:
    float utilization_percentage = 0.0;
    float curr_idle_time, curr_total_time;
};

#endif