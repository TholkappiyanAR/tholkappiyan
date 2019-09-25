#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

// TODO: Return this process's ID
int Process::Pid() { return mPid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    //return LinuxParser::ProcessCpuUtilization(mPid);
    //return 0;

    std::string line,key;
    //std::string pUpTime,uTime,kTime,cuTime,csTime;
    unsigned int count = 0;
    std::unordered_map <int,int> ptime = {{14,0},{15,0},{16,0},{17,0},{22,0}};
    std::ifstream fstream(kProcDirectory + to_string(mPid) + kStatFilename);
    if(fstream.is_open())
    {
    while(getline(fstream,line)){
      std::istringstream linestream(line);
      for(int i = 1 ; count != ptime.size(); ++i)  
      {
          linestream >> key;
          if(ptime.find(i) != ptime.end())
          {
             ptime[i] = std::atoi(key.c_str()); 
             count++;     
          }
      }        
      break;
    }
  } 
   long uptime = LinuxParser::UpTime();
   long int hertz = sysconf(_SC_CLK_TCK);
   float totalTime = ptime.at(14) + ptime.at(15) + ptime.at(16) + ptime.at(17); 
   float seconds = uptime - (ptime.at(22)/hertz);
   float cpuUsage = (float)((totalTime/hertz)/seconds);
   return cpuUsage;
 }

// TODO: Return the command that generated this process
string Process::Command() {      
    return LinuxParser::Command(mPid);
    //return mCommand;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(mPid);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(mPid); 
 }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    long int uptime = LinuxParser::UpTime(mPid); 
    return uptime;   
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
   if(mCpuUtilization < a.mCpuUtilization)
   {
       return true;
   } else {
       return false;
   }      
  //  return 0;             
}