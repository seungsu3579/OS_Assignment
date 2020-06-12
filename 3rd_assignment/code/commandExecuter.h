//
// Created by seungsu on 20. 6. 5..
//
#include "cmd_ioWait.h"
#include "cmd_sleep.h"
#include "cmd_malloc.h"
#include "cmd_memFree.h"
#include "cmd_lock.h"
#include "cmd_unlock.h"
#include "cmd_memAccess.h"
#include "PageBundle.h"
#include "Task.h"
#include <list>

#ifndef PRACTICE1_COMMANDEXECUTER_H
#define PRACTICE1_COMMANDEXECUTER_H


void commandExecuter(Task* &currentCpuTask, list<Task*>* sleepList, list<Task*>* ioWaitList, list<int>* lockList, list<Task*>* runningTask, list<PageBundle*>* all_pages, PageBundle** physicalMem, string sched_opt, string page_opt, int &aid, int physicalNum, int currentCycle, int &page_fault);


#endif //PRACTICE1_COMMANDEXECUTER_H
