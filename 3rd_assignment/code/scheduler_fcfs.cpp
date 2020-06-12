//
// Created by seungsu on 20. 6. 4..
//

#include "scheduler_fcfs.h"

Task* scheduler_fcfs(Task* &currentCpuTask, Task* &nullTask, list<Task*>* run_queue) {
    Task* task;
    if(currentCpuTask->pid == -1){
        if(run_queue->size() != 0){
            // allocate process to cpu
	    list<Task*>::iterator task_iter;
            task_iter = run_queue->begin();

            task = *task_iter;
            run_queue->remove(task);

            // initialize running time
            task->runningTime = 0;
            return task;
        }else{
            // run_queue is empty
            return nullTask;
        }
    }else{
        // already process allocated
        task = currentCpuTask;
        return task;
    }
}
