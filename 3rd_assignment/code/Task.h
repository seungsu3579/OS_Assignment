//
// Created by seungsu on 20. 6. 4..
//
#include <string>
#include <fstream>
#include <list>
#include "PageBundle.h"

#ifndef PRACTICE1_TASK_H
#define PRACTICE1_TASK_H

using namespace std;

class Task{

public:
    int startCycle;                     // when process come in to run queue
    int cmd_num;                        // number of command in process
    int pid;                            // process id
    int sleepTime;                      // sleep time counter
    int runningTime;                    // for count running time in cpu
    double burstTime;                   // for sjf_simple
    double burstTime_exp;               // for sjf_exponential

    bool flagToEmpty;                   // flag of current cpu should be empty after print
    bool flagToComplete;                // flag of command completed

    int current_cmd_int;                // check which command's turn(int)
    list<int*>::iterator current_cmd;   // check which command's turn(iterator)
    list<int*> cmd_list;                // list of command
    list<int> usedCpuTime;              // to calc burst time

    int memoryCursor;                   // cursor of pageTable
    int pageTableSize;                  // size of pageTable
    PageBundle** pageTable_aid;         // page table (aid)
    PageBundle** pageTable_valid;       // page table (valid)
    int recentAid;                      // for print memory log
    int recentPageNum;                  // for print memory log

    string directory;                   // save directory
    string file_name;                   // process file name

    int waitingTime;                    // for evaluate
    int responseTime;                   // for evaluate


    Task(int startInput, string dir, string fn, int pid_num){
        startCycle = startInput;
        file_name = fn;
        pid = pid_num;
        directory = dir;
        flagToEmpty = false;
        flagToComplete = false;
        memoryCursor = 0;

        recentAid = -1;
        recentPageNum = -1;

        waitingTime = 0;
        responseTime = -1;
    }

    Task(){
    }

    void setData(int vmemSize, int pageSize);

    void printCmd();

    void calcSimple();

    void calcExponential();
};

#endif //PRACTICE1_TASK_H
