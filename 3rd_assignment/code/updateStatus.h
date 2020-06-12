//
// Created by seungsu on 20. 6. 6..
//
#include <list>
#include "Task.h"
#include "PageBundle.h"

#ifndef PRACTICE1_UPDATESTATUS_H
#define PRACTICE1_UPDATESTATUS_H


void updateStatus(Task* &currentCpuTask, Task* nullTask, list<Task*>* run_queue, list<Task*>* runningTask, list<Task*>* sleepList, list<Task*>* ioWaitList, list<Task*>* endProcess, PageBundle** physicalMem, int physicalNum, int currentCycle, int &timeInterval);


#endif //PRACTICE1_UPDATESTATUS_H
