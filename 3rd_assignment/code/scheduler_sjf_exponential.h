//
// Created by seungsu on 20. 6. 7..
//
#include <list>
#include "Task.h"
#ifndef PRACTICE1_SCHEDULER_SJF_EXPONENTIAL_H
#define PRACTICE1_SCHEDULER_SJF_EXPONENTIAL_H


Task *scheduler_sjf_exponential(Task* &currentCpuTask, Task* &nullTask, list<Task *> *run_queue, bool append);


#endif //PRACTICE1_SCHEDULER_SJF_EXPONENTIAL_H
