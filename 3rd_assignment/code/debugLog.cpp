//
// Created by seungsu on 20. 6. 6..
//

#include "debugLog.h"

void debugLog(list<Task *> run_queue, list<Task *> endProcess, list<Task *> all_task, list<Task *> sleepList, list<Task *> ioWaitList,
              list<InputIO *> all_input, Task* currentCpuTask) {
    list<Task*>::iterator task_iter;
    list<InputIO*>::iterator input_iter;

    printf("All Task   : ");
    if(all_task.empty()){
        printf("Empty\n");
    }else{
        for(task_iter = all_task.begin() ; task_iter != all_task.end() ; task_iter++){
            printf("%d(%s) ", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        printf("\n");
    }

//    printf("All Input  : ");
//    if(all_input.empty()){
//        printf("Empty\n");
//    }else{
//        for(input_iter = all_input.begin() ; input_iter != all_input.end() ; input_iter++){
//            printf("%d(%s) ", input_iter.operator*()->target_pid, input_iter.operator*()->file_name.c_str());
//        }
//        printf("\n");
//    }

    printf("End Process : ");
    if(endProcess.empty()){
        printf("Empty\n");
    }else{
        for(task_iter = endProcess.begin() ; task_iter != endProcess.end() ; task_iter++){
            printf("%d(%s) ", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        printf("\n");
    }

    printf("Running Job: ");
    printf("%d(%s)\n", currentCpuTask->pid, currentCpuTask->file_name.c_str());

    printf("Run Queue  : ");
    if(run_queue.empty()){
        printf("Empty\n");
    }else{
        for(task_iter = run_queue.begin() ; task_iter != run_queue.end() ; task_iter++){
            printf("%d(%s) ", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        printf("\n");
    }

    printf("SleepList  : ");
    if(sleepList.empty()){
        printf("Empty\n");
    }else{
        for(task_iter = sleepList.begin() ; task_iter != sleepList.end() ; task_iter++){
            printf("%d(%s) ", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        printf("\n");
    }

    printf("IOWait List: ");
    if(ioWaitList.empty()){
        printf("Empty\n");
    }else{
        for(task_iter = ioWaitList.begin() ; task_iter != ioWaitList.end() ; task_iter++){
            printf("%d(%s) ", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        printf("\n");
    }
    printf("\n");
}
