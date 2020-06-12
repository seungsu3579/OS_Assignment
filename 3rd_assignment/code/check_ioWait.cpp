//
// Created by seungsu on 20. 6. 4..
//

#include "check_ioWait.h"

bool check_ioWait(list<Task*>* run_queue, list<Task*>* ioWaitList, list<InputIO*>* all_input, int currentCycle) {
    list<Task*>::iterator task_iter;
    list<InputIO*>::iterator io_iter;

    list<InputIO*> tmpIO;
    list<Task*> tmpTask;

    bool returnValue = false;

    // find input fitted current cycle
    for(io_iter = all_input->begin() ; io_iter != all_input->end() ; io_iter++){
        InputIO* input = *io_iter;

        if(input->startCycle <= currentCycle){
            // find task fitted pid
            for(task_iter = ioWaitList->begin() ; task_iter != ioWaitList->end() ; task_iter++){
                Task* task = *task_iter;

                if(task->pid == input->target_pid){
                    if(task->memoryCursor != 10){
                        tmpTask.push_back(task);        // append for delete
                        run_queue->push_back(task);      // append for run
                        task->runningTime = 0;
                        returnValue = true;
                    }else{
                        tmpTask.push_back(task);
                        task->runningTime = 0;
                        returnValue = false;
                    }

                }

            }
            tmpIO.push_back(input);                 // append for delete

        }
    }

    // remove input allocated already
    for(io_iter = tmpIO.begin() ; io_iter != tmpIO.end() ; io_iter++){
        InputIO* input = *io_iter;
        all_input->remove(input);
    }

    // remove task which receive IO
    for(task_iter = tmpTask.begin() ; task_iter != tmpTask.end() ; task_iter++){
        Task* task = *task_iter;
        ioWaitList->remove(task);
    }

    return returnValue;

}
