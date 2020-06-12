//
// Created by seungsu on 20. 6. 9..
//

#include <string>
#include "Task.h"
#include "PageBundle.h"
#ifndef PRACTICE1_PAGECHANGE_LRU_H
#define PRACTICE1_PAGECHANGE_LRU_H

int pageChange_lru(Task *&currentCpuTask, PageBundle **physicalMem, int physicalNum, int aid);

#endif //PRACTICE1_PAGECHANGE_LRU_H
