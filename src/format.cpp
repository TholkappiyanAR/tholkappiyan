#include <string>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hour,min,sec;
    string uptime;
    hour = seconds / 3600;
    min = (seconds % 3600) / 60;
    sec = seconds % 60;
    uptime = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);
    return uptime;     
}