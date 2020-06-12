//
// Created by seungsu on 20. 6. 9..
//
#include "PageBundle.h"
#include "Task.h"
#ifndef PRACTICE1_PAGECHANGE_FIFO_H
#define PRACTICE1_PAGECHANGE_FIFO_H


int pageChange_fifo(Task *&currentCpuTask, PageBundle **physicalMem, int physicalNum, int aid);

#endif //PRACTICE1_PAGECHANGE_FIFO_H
