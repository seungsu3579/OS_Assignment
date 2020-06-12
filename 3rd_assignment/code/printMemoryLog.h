//
// Created by seungsu on 20. 6. 8..
//
#include <stdio.h>
#include <list>
#include "Task.h"
#include "PageBundle.h"
#ifndef PRACTICE1_PRINTMEMORYLOG_H
#define PRACTICE1_PRINTMEMORYLOG_H


void printMemoryLog(FILE* fp, Task* currentCpuTask, list<PageBundle*>* all_pages, PageBundle** physicalMem, int physicalNum, list<Task*>* runningProcess, int currentCycle, int page_fault);

#endif //PRACTICE1_PRINTMEMORYLOG_H
