//
// Created by seungsu on 20. 6. 7..
//

#include "scheduler_sjf_exponential.h"

Task *scheduler_sjf_exponential(Task *&currentCpuTask, Task *&nullTask, list<Task *> *run_queue, bool append) {

    Task* task = currentCpuTask;
    double smallBurstTime = currentCpuTask->burstTime_exp;
    list<Task*>::iterator task_iter;

    if(currentCpuTask->pid == -1 || append){
        if(currentCpuTask->pid != -1){
            run_queue->push_back(currentCpuTask);
            smallBurstTime = currentCpuTask->burstTime_exp - (double)currentCpuTask->runningTime;
            currentCpuTask = nullTask;
        }
        if(run_queue->size() != 0){
            // compare burst time
            printf("\nburst Time(e): ");
            for(task_iter = run_queue->begin() ; task_iter != run_queue->end() ; task_iter++){
                printf("%s(%f)  ", task_iter.operator*()->file_name.c_str(), task_iter.operator*()->burstTime);
                if(task_iter.operator*()->burstTime_exp < smallBurstTime){
                    smallBurstTime = task_iter.operator*()->burstTime_exp;
                    task = task_iter.operator*();
                }
            }
            printf("\n");

            printf("Choosed Task : %s(%f)\n", task->file_name.c_str(), smallBurstTime);
            // delete job at run queue
            run_queue->remove(task);
        }else{
            // run_queue is empty
            task = nullTask;
        }
    }else{
        task = currentCpuTask;
    }
    return task;

}
