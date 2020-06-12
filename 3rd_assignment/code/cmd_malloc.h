//
// Created by seungsu on 20. 6. 8..
//
#include "Task.h"
#include <list>
#include "PageBundle.h"
#ifndef PRACTICE1_CMD_MALLOC_H
#define PRACTICE1_CMD_MALLOC_H


void cmd_malloc(Task* &currentCpuTask, list<PageBundle*>* all_pages, int memorySize, int &aid);


#endif //PRACTICE1_CMD_MALLOC_H
