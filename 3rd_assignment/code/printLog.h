//
// Created by seungsu on 20. 6. 6..
//

#include <list>
#include <stdio.h>
#include "Task.h"

#ifndef PRACTICE1_PRINTLOG_H
#define PRACTICE1_PRINTLOG_H

void printLog(FILE* fp, Task *currentCpuTask, list<Task*> run_queue, list<Task*> sleepList, list<Task*> ioWaitList, int currentCycle);


#endif //PRACTICE1_PRINTLOG_H
