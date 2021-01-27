#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int seconds) { 
    std::string hour, min, sec;

    std::string formatted_string;
    sec = to_string(seconds%60);
    min = to_string((seconds/60)%60);
    hour = to_string(seconds/(60*60));

    if (stoi(hour) < 10)
        hour = "0" + hour;

    if (stoi(min) < 10)
        min = "0" + min;

    if (stoi(sec) < 10)
        sec = "0" + sec;

    formatted_string = hour + ":" + min + ":" + sec;
    return formatted_string; 
}