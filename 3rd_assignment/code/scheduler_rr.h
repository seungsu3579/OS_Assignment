//
// Created by seungsu on 20. 6. 6..
//

#include <list>
#include "Task.h"
#ifndef PRACTICE1_SCHEDULER_RR_H
#define PRACTICE1_SCHEDULER_RR_H


Task* scheduler_rr(Task* &currentCpuTask, Task* &nullTask, list<Task*>* run_queue);


#endif //PRACTICE1_SCHEDULER_RR_H
