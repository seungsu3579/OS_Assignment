//
// Created by seungsu on 20. 6. 4..
//

#include <list>
#include "Task.h"
#include "InputIO.h"

#ifndef PRACTICE1_CHECK_IOWAIT_H
#define PRACTICE1_CHECK_IOWAIT_H


bool check_ioWait(list<Task*>* run_queue, list<Task*>* ioWaitList, list<InputIO*>* all_input, int currentCycle);


#endif //PRACTICE1_CHECK_IOWAIT_H
