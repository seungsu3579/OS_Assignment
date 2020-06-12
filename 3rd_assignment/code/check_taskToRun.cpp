//
// Created by seungsu on 20. 6. 4..
//

#include "check_taskToRun.h"

bool check_taskToRun(list<Task*>* run_queue, list<Task*>* runningTask, list<Task*>* all_task, int currentCycle) {
    list<Task*>::iterator task_iter;
    list<Task*> tmp;

    bool returnValue = false;

    for(task_iter = all_task->begin() ; task_iter != all_task->end() ; task_iter++){
        if(task_iter.operator*()->startCycle == currentCycle){
            run_queue->push_back(*task_iter);              // allocate task in run_queue
            runningTask->push_back(*task_iter);
            tmp.push_back(*task_iter);
            returnValue = true;
        }
    }
    for(task_iter = tmp.begin() ; task_iter != tmp.end() ; task_iter++){
        all_task->remove(*task_iter);
    }

    return returnValue;
}
