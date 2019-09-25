#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

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
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>  version >> kernel;
  }
  return kernel;
}

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
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::string MemTotal1,MemTotal2, MemFree1,MemFree2;
  float memtotal,memfree;
  std::string line;
  int count = 0;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
  while(count < 2){    
    std::getline(stream, line);
    std::istringstream linestream(line);
    if (count == 0 )
    linestream >> MemTotal1 >> MemTotal2;
    else 
    linestream >> MemFree1 >> MemFree2;
    count++;
  }
  }
  memtotal = stoi(MemTotal2);
  memfree = stoi(MemFree2);
  return ((memtotal - memfree)/memtotal);  
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::string uptime,line;
  long uptime_val;
  std::ifstream fstream(kProcDirectory + kUptimeFilename);
  std::getline(fstream, line);
  std::istringstream linestream(line);
  linestream >> uptime;
  uptime_val = stoi(uptime);
  return uptime_val;
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  std::string line,key,cpu_stat;
  //std::string User,Nice,System,Idle,IOwait,IRQ,SoftIRQ,Steal,Guest,GuestNice; 
  std::vector<std::string> cpustat;
  std::ifstream filestream(kProcDirectory + kStatFilename); 
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);  
      linestream >>  cpu_stat;   
      while(linestream >> key){
       cpustat.push_back(key);
      }      
  }   
  return cpustat; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string totalProcess1,totalProcess2;
  std::string line,key,value;
  //int totalprocessP_val = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        if (linestream >> key) {
          if (key == "processes") {
            linestream >> value;
            break;
            //return stoi(value);
          }
        }
      }
  }    
  return stoi(value);
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string totalProcess1,totalProcess2;
  std::string line,key,value;  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        if (linestream >> key) {
          if (key == "procs_running") {
            linestream >> value;
            break;
            //return stoi(value);
          }
        }
      }
  }    
  return stoi(value); 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string line;
  std::ifstream processStream(kProcDirectory + to_string(pid) + kCmdlineFilename);  
  if(processStream.is_open())
  {
    std::getline(processStream, line);    
  }  
  return line;
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::string line,key,value;
  long int ramSize = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open())
  {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      if (linestream >> key)
       {
          if (key == "VmSize:") {
            linestream >> value;
            break;
          }  
        }
      }
  }
  ramSize = stoi(value) / 1000;
  return to_string(ramSize);  
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
   std::string line,key,value,username,line2; 
     
   std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
   if (filestream.is_open()) {
   while (std::getline(filestream, line)) {
        std::istringstream linestream1(line);
        if (linestream1 >> key) {
          if (key == "Uid:") {
            linestream1 >> value;
            break;
          }
        }
      }   
    }
    return value;      
} 
    

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
    std::ostringstream pid_s;

    pid_s << pid;

    std::ifstream fstream(kPasswordPath);

    string line;

    string username,x,uid;

    string uid_s = LinuxParser::Uid(pid);

    bool found = false;

    if(fstream.is_open())
    {
      while(getline(fstream,line)){
        replace(line.begin(),line.end(),':',' ');
        std::istringstream linestream(line);
        while(linestream >> username >> x >> uid){
          if(uid == uid_s){
            found = true;
            break;
          }
          username.clear();
        }
        if(found){
          break;
        }
      }
    }
    return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {  
  std::string line,key,uptime;
  long uptimefloat;
  //unsigned int count = 0;
  //std::unordered_map <int,int> sTime = {{22,0}};
  std::ifstream fstream(kProcDirectory + to_string(pid) + kStatFilename);
  if(fstream.is_open())
  {
    while(getline(fstream,line)){
      std::istringstream linestream(line);
     /* for(int i = 1; count != sTime.size(); i++)  
      {
          linestream >> key;
          if(sTime.find(i) != sTime.end())
          {
             sTime[i] = std::atoi(key.c_str()); 
             count++;     
          }
      } */
      for(int i = 0 ; i < 21 ; i++)
      {
        linestream >> key;  
      } 
      linestream >> uptime;    
      break;
    }
  }
  uptimefloat = (stoi(uptime)/sysconf(_SC_CLK_TCK));
  return uptimefloat;  
 }
/*
  float LinuxParser::ProcessCpuUtilization(int pid)
  {
    std::string line,key,key2;
    std::string pUpTime,uTime,kTime,cuTime,csTime;
    float time[5];
    std::ifstream fstream(kProcDirectory + to_string(pid) + kStatFilename);
    if(fstream.is_open())
    {
    while(getline(fstream,line)){
      std::istringstream linestream(line);      
      for(int i = 0 ;i < 13 ;i++) linestream >> key;
      linestream >> uTime >> kTime >> cuTime >> csTime; 
      std::istringstream linestream2(line);
      for(int j = 0 ;j < 21 ;j++) linestream2 >> key2;
      linestream2 >> pUpTime;     
      break;
    }
  }
   time [0] = stof(pUpTime);
   time [1] = stof(uTime);
   time [2] = stof(kTime),
   time [3] = stof(cuTime);
   time [4] = stof(csTime);

   long uptime = LinuxParser::UpTime();
   long int hertz = sysconf(_SC_CLK_TCK);
   float totalTime = time[1] + time[2] + time[3] + time[4]; 
   float seconds = uptime - (time[0] / hertz);
   float cpuUsage = ((totalTime/hertz)/seconds);
   return cpuUsage;
  }*/