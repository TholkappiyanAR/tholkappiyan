#include<string>
#include<iostream>

#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpustat; 
    int i = 0; 
    float cpuTimeSinceBoot,cpuIdleTime,cpuUsageSinceBoot;
    cpustat = LinuxParser::CpuUtilization(); 
    for(std::vector<std::string>::iterator itr = cpustat.begin();itr != cpustat.end(); itr++)
    {
        cpu_stat[i] = stoi(*itr);
        i++;
    }
    for(i = 0 ;i < 8;i++)
    {
       cpuTimeSinceBoot += (float)cpu_stat[i];
    }
    cpuIdleTime = (float)cpu_stat[3] + cpu_stat[4];
    cpuUsageSinceBoot = (float)(cpuTimeSinceBoot - cpuIdleTime);

    return (cpuUsageSinceBoot/cpuTimeSinceBoot);    
}