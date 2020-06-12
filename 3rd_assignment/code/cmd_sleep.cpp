//
// Created by seungsu on 20. 6. 4..
//

#include "cmd_sleep.h"

void cmd_sleep(Task* currentCpuTask, int sleepCycle, list<Task*>* sleepList, string sched){
    currentCpuTask->sleepTime = sleepCycle;
    if(currentCpuTask->current_cmd_int < currentCpuTask->cmd_list.size()) {
        sleepList->push_back(currentCpuTask);
    }


    // update burst time of task
    if(strcmp(sched.c_str(), "sjf-simple") == 0){
        currentCpuTask->calcSimple();
    }else if(strcmp(sched.c_str(), "sjf-exponential") == 0){
        currentCpuTask->calcExponential();
    }

    currentCpuTask->flagToEmpty = true;
    currentCpuTask->flagToComplete = true;
}