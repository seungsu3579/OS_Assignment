//
// Created by seungsu on 20. 6. 4..
//

#include "scheduler.h"

Task* scheduler::schedule(Task* currentCpuTask, bool append) {

    Task* task;

    if(strcmp(option.c_str(), "fcfs") == 0){
        task = scheduler_fcfs(currentCpuTask, nullTask, run_queue);
    }else if(strcmp(option.c_str(), "rr") == 0){
        task = scheduler_rr(currentCpuTask, nullTask, run_queue);
    }else if(strcmp(option.c_str(), "sjf-simple") == 0){
        task = scheduler_sjf_simple(currentCpuTask, nullTask, run_queue, append);
    }else if(strcmp(option.c_str(), "sjf-exponential") == 0){
        task = scheduler_sjf_exponential(currentCpuTask, nullTask, run_queue, append);
    }else{
        printf("%s\n", "Error : cpu scheduler option was wrong!");
    }

    return task;

}