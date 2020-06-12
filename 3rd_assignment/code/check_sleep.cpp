//
// Created by seungsu on 20. 6. 4..
//

#include "check_sleep.h"


bool check_sleep(list<Task*>* run_queue, list<Task*>* sleepList){
    list<Task*>::iterator task_iter;
    list<Task*> tmp;

    bool returnValue = false;

    for(task_iter = sleepList->begin() ; task_iter != sleepList->end() ; task_iter++){
        Task* task = *task_iter;
        task->sleepTime--;
        if(task->sleepTime == 0){
            tmp.push_back(task);
            run_queue->push_back(task);         // append for run
            task->runningTime = 0;
            returnValue = true;
        }
    }

    for(task_iter = tmp.begin() ; task_iter != tmp.end() ; task_iter++){
        Task* task = *task_iter;
        sleepList->remove(task);
    }

    return returnValue;

};