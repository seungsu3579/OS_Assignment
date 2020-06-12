//
// Created by seungsu on 20. 6. 5..
//

#include "commandExecuter.h"

void commandExecuter(Task* &currentCpuTask, list<Task*>* sleepList, list<Task*>* ioWaitList, list<int>* lockList, list<Task*>* runningTask, list<PageBundle*>* all_pages, PageBundle** physicalMem, string sched_opt, string page_opt, int &aid, int physicalNum , int currentCycle, int &page_fault) {
    // cpu has process
    if(currentCpuTask->pid != -1){

        int* runCmd = currentCpuTask->current_cmd.operator*();

        // execute command
        if(runCmd[0] == 0){
            // memory allocate
            cmd_malloc(currentCpuTask, all_pages, runCmd[1], aid);

        }else if(runCmd[0] == 1){
            // memory access
            cmd_memAccess(currentCpuTask, runningTask, physicalMem, physicalNum, runCmd[1], currentCycle, page_opt, page_fault);

        }else if(runCmd[0] == 2){
            // memory release
            cmd_memFree(currentCpuTask, runCmd[1], physicalMem, physicalNum);

        }else if(runCmd[0] == 3){
            // Non-memory instruction
            currentCpuTask->flagToEmpty = false;
            currentCpuTask->flagToComplete = true;

        }else if(runCmd[0] == 4){
            // Sleep
            cmd_sleep(currentCpuTask, runCmd[1], sleepList, sched_opt);

        }else if(runCmd[0] == 5){
            // IO Wait
            cmd_ioWait(currentCpuTask, ioWaitList, sched_opt);

        }else if(runCmd[0] == 6){
            // Lock
            cmd_lock(currentCpuTask, lockList, runCmd[1]);

        }else if(runCmd[0] == 7){
            // Unlock
            cmd_unlock(currentCpuTask, lockList, runCmd[1]);

        }
    }

}
