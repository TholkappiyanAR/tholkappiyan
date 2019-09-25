#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  Process(int Pid){
    mPid = Pid;
    mCpuUtilization = CpuUtilization();
  }                                         // TODO: See src/process.cpp
  /*void setUser(std::string);                      // TODO: See src/process.cpp
  void setCommand();                   // TODO: See src/process.cpp
  void setCpuUtilization(float);                  // TODO: See src/process.cpp
  void setRam(std::string);                       // TODO: See src/process.cpp
  void setUpTime(long int);     */

  // TODO: Declare any necessary private members
 private:
    int mPid; 
    float mCpuUtilization;
    /*std::string mUser;
    std::string mCommand;    
    std::string mRam;
    long int mUpTime;*/
};

#endif