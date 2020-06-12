//
// Created by seungsu on 20. 6. 4..
//
#include "Task.h"
#include <list>
#include <string>
#include <string.h>

#ifndef PRACTICE1_CMD_IOWAIT_H
#define PRACTICE1_CMD_IOWAIT_H


void cmd_ioWait(Task* currentTask, list<Task*>* ioWaitList, string sched);


#endif //PRACTICE1_CMD_IOWAIT_H
