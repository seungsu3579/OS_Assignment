//
// Created by seungsu on 20. 6. 8..
//

#include "printMemoryLog.h"

void printMemoryLog(FILE *fp, Task *currentCpuTask, list<PageBundle*>* all_pages, PageBundle** physicalMem, int physicalNum, list<Task*>* runningProcess, int currentCycle, int page_fault) {

    int cp_pid;
    const char* file_name;
    int line;
    int op;
    int arg;

    cp_pid = currentCpuTask->pid;
    file_name = currentCpuTask->file_name.c_str();

    if(currentCpuTask->pid != -1){
        line = currentCpuTask->current_cmd_int;
        op = currentCpuTask->current_cmd.operator*()[0];
        arg = currentCpuTask->current_cmd.operator*()[1];
    }

    // line 1
    if(currentCpuTask->pid == -1){
        fprintf(fp, "[%d Cycle] Input : Function [NO-OP]\n", currentCycle);
    }else{
        if(op == 0){
            // memory allocate
            int aid = currentCpuTask->recentAid;
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [ALLOCATION] Alloc ID [%d] Page Num[%d]\n", currentCycle, cp_pid, aid, arg);
        }else if(op == 1){
            // memory access
            int pNum;
            for(int i = 0 ; i < currentCpuTask->pageTableSize ; i++){
                if(currentCpuTask->pageTable_aid[i] != nullptr && currentCpuTask->pageTable_aid[i]->aid == arg){
                    pNum = currentCpuTask->pageTable_aid[i]->pageNum;
                }
            }
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [ACCESS] Alloc ID [%d] Page Num[%d]\n", currentCycle, cp_pid, arg, pNum);
        }else if(op == 2){
            // memory release
            int pNum;
            list<PageBundle*>::iterator page_iter;
            for(page_iter = all_pages->begin() ; page_iter != all_pages->end() ; page_iter++){
                if(page_iter.operator*()->aid == arg){
                    pNum = page_iter.operator*()->pageNum;
                }
            }
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [RELEASE] Alloc ID [%d] Page Num[%d]\n", currentCycle, cp_pid, arg, pNum);
        }else if(op == 3){
            // Non-memory instruction
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [NONMEMORY]\n", currentCycle, cp_pid);
        }else if(op == 4){
            // Sleep
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [SLEEP]\n", currentCycle, cp_pid);
        }else if(op == 5){
            // IO Wait
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [IOWAIT]\n", currentCycle, cp_pid);
        }else if(op == 6){
            // Lock
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [LOCK]\n", currentCycle, cp_pid);
        }else if(op == 7){
            // Unlock
            fprintf(fp, "[%d Cycle] Input : Pid [%d] Function [UNLOCK]\n", currentCycle, cp_pid);
        }
    }


    // line 2
    int counter = 0;
    fprintf(fp, "%-30s", ">> Physical Memory : ");
    for(int i = 0 ; i < physicalNum ; i++){
        if(physicalMem[i] != nullptr){
            PageBundle* pb = physicalMem[i];
            for(int j = 0 ; j < pb->pageNum ; j++){
                if(counter % 4 == 0){
                    fprintf(fp, "|");
                }
                counter++;
                if(pb->aid == -1){
                    fprintf(fp, "%s", "-");
                }else {
                    fprintf(fp, "%d", pb->aid);
                }
            }
        }
    }
    fprintf(fp, "|\n");

    // line 3~
    list<Task*>::iterator task_iter;
    for(task_iter = runningProcess->begin(); task_iter != runningProcess->end() ; task_iter++){

        // sub_line 1
        fprintf(fp, ">> pid(%d) %-20s", task_iter.operator*()->pid, "Page Table(AID) : ");
        counter = 0;
        for(int i = 0 ; i < task_iter.operator*()->pageTableSize ; i++){
            if(task_iter.operator*()->pageTable_aid[i] != nullptr){
                PageBundle* pb = task_iter.operator*()->pageTable_aid[i];
                for(int j = 0 ; j < pb->pageNum ; j++){
                    if(counter % 4 == 0){
                        fprintf(fp, "|");
                    }
                    counter++;
                    if(pb->aid == -1){
                        fprintf(fp, "%s", "-");
                    }else {
                        fprintf(fp, "%d", pb->aid);
                    }
                }
            }
        }
        fprintf(fp, "|\n");


        // sub_line 2
        fprintf(fp, ">> pid(%d) %-20s", task_iter.operator*()->pid, "Page Table(Valid) : ");
        counter = 0;
        for(int i = 0 ; i < task_iter.operator*()->pageTableSize ; i++){
            if(task_iter.operator*()->pageTable_valid[i] != nullptr){
                PageBundle* pb = task_iter.operator*()->pageTable_valid[i];
                for(int j = 0 ; j < pb->pageNum ; j++){
                    if(counter % 4 == 0){
                        fprintf(fp, "|");
                    }
                    counter++;
                    if(pb->aid == -1){
                        fprintf(fp, "%s", "-");
                    }else {
                        fprintf(fp, "%d", pb->aid);
                    }
                }
            }
        }
        fprintf(fp, "|\n");
    }
    fprintf(fp,"\n");

}
