//
// Created by seungsu on 20. 6. 9..
//

#include <list>
#include <string>
#include <string.h>
#include "Task.h"
#include "PageBundle.h"
#include "pageChange_fifo.h"
#include "pageChange_lru.h"
#include "pageChange_lru_sample.h"
#include "pageChage_lfu.h"
#include "pageChange_mfu.h"


#ifndef PRACTICE1_CMD_MEMACCESS_H
#define PRACTICE1_CMD_MEMACCESS_H


void cmd_memAccess(Task* &currentCpuTask, list<Task*>* runningTask, PageBundle** physicalMem, int physicalNum, int aid, int currentCycle, string page_opt, int &page_fault);

#endif //PRACTICE1_CMD_MEMACCESS_H
