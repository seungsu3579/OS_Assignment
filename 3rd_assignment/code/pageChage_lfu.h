//
// Created by seungsu on 20. 6. 11..
//
#include <string>
#include "Task.h"
#include "PageBundle.h"
#ifndef PRACTICE1_PAGECHAGE_LFU_H
#define PRACTICE1_PAGECHAGE_LFU_H


int pageChange_lfu(Task *&currentCpuTask, PageBundle **physicalMem, int physicalNum, int aid);

#endif //PRACTICE1_PAGECHAGE_LFU_H
