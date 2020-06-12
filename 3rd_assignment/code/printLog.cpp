//
// Created by seungsu on 20. 6. 6..
//

#include "printLog.h"

void printLog(FILE* fp, Task *currentCpuTask, list<Task*> run_queue, list<Task*> sleepList, list<Task*> ioWaitList, int currentCycle) {

    int cp_pid;
    const char* file_name;
    int line;
    int op;
    int arg;
    list<Task*>::iterator task_iter;

    cp_pid = currentCpuTask->pid;
    file_name = currentCpuTask->file_name.c_str();

    if(currentCpuTask->pid != -1){
        line = currentCpuTask->current_cmd_int;
        op = currentCpuTask->current_cmd.operator*()[0];
        arg = currentCpuTask->current_cmd.operator*()[1];
    }


    // line 1
    fprintf(fp, "[%d Cycle] Scheduled Process: ", currentCycle);
    if(currentCpuTask->runningTime == 0){
        fprintf(fp, "%d %s\n", cp_pid, file_name);
    }else{
        fprintf(fp, "None\n");
    }

    // line 2
    fprintf(fp, "Running Process: ");
    if(currentCpuTask->pid != -1){
        fprintf(fp, "Process#%d running code %s line %d(op %d, arg %d)\n", cp_pid, file_name, line, op, arg);
    }else{
        fprintf(fp, "None\n");
    }

    // line 3
    fprintf(fp, "RunQueue: ");
    if(run_queue.empty()){
        fprintf(fp, "Empty\n");
    }else{
        for(task_iter = run_queue.begin() ; task_iter != run_queue.end() ; task_iter++){
            fprintf(fp, "%d(%s)", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        fprintf(fp, "\n");
    }

    // line 4
    fprintf(fp, "SleepList: ");
    if(sleepList.empty()){
        fprintf(fp, "Empty\n");
    }else{
        for(task_iter = sleepList.begin() ; task_iter != sleepList.end() ; task_iter++){
            fprintf(fp, "%d(%s)", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        fprintf(fp, "\n");
    }

    // line 5
    fprintf(fp, "IOWait List: ");
    if(ioWaitList.empty()){
        fprintf(fp, "Empty\n");
    }else{
        for(task_iter = ioWaitList.begin() ; task_iter != ioWaitList.end() ; task_iter++){
            fprintf(fp, "%d(%s)", task_iter.operator*()->pid, task_iter.operator*()->file_name.c_str());
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "\n");

}
