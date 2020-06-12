//
// Created by seungsu on 20. 6. 11..
//

#include "report_criteria.h"

void report_criteria(Task* &currentCpuTask, list<Task *> *run_queue, int currentCycle) {

    if(currentCpuTask->pid != -1){
        // check response time
        if(currentCpuTask->responseTime == -1){
            currentCpuTask->responseTime = currentCycle - currentCpuTask->startCycle;
        }

        // count waiting time
        list<Task*>::iterator task_iter;
        for(task_iter = run_queue->begin(); task_iter != run_queue->end() ; task_iter++){
            task_iter.operator*()->waitingTime++;
        }
    }

}
