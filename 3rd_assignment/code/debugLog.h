//
// Created by seungsu on 20. 6. 6..
//
#include <list>
#include "Task.h"
#include "InputIO.h"

#ifndef PRACTICE1_DEBUGLOG_H
#define PRACTICE1_DEBUGLOG_H


void debugLog(list<Task*> run_queue, list<Task *> endProcess, list<Task*> all_task, list<Task*> sleepList, list<Task*> ioWaitList, list<InputIO*> all_input, Task* currentCpuTask);


#endif //PRACTICE1_DEBUGLOG_H
