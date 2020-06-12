//
// Created by seungsu on 20. 6. 4..
//

#include "cmd_ioWait.h"

void cmd_ioWait(Task* currentCpuTask, list<Task*>* ioWaitList, string sched) {



    if(currentCpuTask->current_cmd_int < currentCpuTask->cmd_list.size()) {
        ioWaitList->push_back(currentCpuTask);
    }else{
        currentCpuTask->memoryCursor = 10;
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
