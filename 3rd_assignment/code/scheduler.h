//
// Created by seungsu on 20. 6. 4..
//
#include <list>
#include <string>
#include <string.h>
#include "Task.h"
#include "scheduler_fcfs.h"
#include "scheduler_rr.h"
#include "scheduler_sjf_simple.h"
#include "scheduler_sjf_exponential.h"

#ifndef PRACTICE1_SCHEDULER_H
#define PRACTICE1_SCHEDULER_H


class scheduler {
public:
    string option;
    list<Task*>* run_queue;
    Task* nullTask;

    scheduler(string sched, list<Task*>* runQueue, Task* nullT){
        option = sched;
        run_queue = runQueue;
        nullTask = nullT;
    }

    Task* schedule(Task* currentCpuTask, bool append);

};


#endif //PRACTICE1_SCHEDULER_H
