//
// Created by seungsu on 20. 6. 6..
//
#include <list>
#include "Task.h"
#ifndef PRACTICE1_SCHEDULER_SJF_SIMPLE_H
#define PRACTICE1_SCHEDULER_SJF_SIMPLE_H


Task *scheduler_sjf_simple(Task* &currentCpuTask, Task* &nullTask, list<Task *> *run_queue, bool append);


#endif //PRACTICE1_SCHEDULER_SJF_SIMPLE_H
