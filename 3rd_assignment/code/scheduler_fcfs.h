//
// Created by seungsu on 20. 6. 4..
//

#include <list>
#include "Task.h"

#ifndef PRACTICE1_SCHEDULER_FCFS_H
#define PRACTICE1_SCHEDULER_FCFS_H


Task* scheduler_fcfs(Task* &currentCpuTask, Task* &nullTask, list<Task*>* run_queue);


#endif //PRACTICE1_SCHEDULER_FCFS_H
