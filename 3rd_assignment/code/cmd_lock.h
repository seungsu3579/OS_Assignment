//
// Created by seungsu on 20. 6. 8..
//
#include <list>
#include "Task.h"

#ifndef PRACTICE1_CMD_LOCK_H
#define PRACTICE1_CMD_LOCK_H

using namespace std;

void cmd_lock(Task* &currentCpuTask, list<int>* lockList, int lockId);

#endif //PRACTICE1_CMD_LOCK_H
