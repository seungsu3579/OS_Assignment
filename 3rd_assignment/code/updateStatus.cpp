//
// Created by seungsu on 20. 6. 6..
//

#include "updateStatus.h"


void updateStatus(Task* &currentCpuTask, Task* nullTask, list<Task*>* run_queue, list<Task*>* runningTask, list<Task*>* sleepList, list<Task*>* ioWaitList, list<Task*>* endProcess, PageBundle** physicalMem, int physicalNum, int currentCycle, int &timeInterval){

    if(currentCpuTask->pid != -1){
        // for all task
        currentCpuTask->runningTime++;
    }

    // command success
    if(currentCpuTask->flagToComplete){
        // check it was end
        if(currentCpuTask->current_cmd_int >= currentCpuTask->cmd_list.size()) {
            endProcess->push_back(currentCpuTask);

            // release memory from physical memory of end process
            for(int i = 0 ; i < currentCpuTask->pageTableSize ; i++){
                if(currentCpuTask->pageTable_aid[i] != nullptr && currentCpuTask->pageTable_aid[i]->aid != -1){
                    for(int j = 0 ; j < physicalNum ; j++){
                        if(physicalMem[j] != nullptr && physicalMem[j]->aid == currentCpuTask->pageTable_aid[i]->aid){
                            PageBundle* pb = physicalMem[j];
                            physicalMem[j] = new PageBundle(pb->pageNum, -1, j);
                            physicalMem[j]->buddyPageNum = pb->buddyPageNum;
                            physicalMem[j]->pbId = pb->pbId;
                            physicalMem[j]->parentId = pb->parentId;
                            break;
                        }
                    }
                }
            }

            // buddy system merge
            for(int k = 0 ; k < physicalNum ; k++){
                if(physicalMem[k] != nullptr && physicalMem[k]->aid == -1){

                    // check around page bundle to conquer ( Buddy System )
                    // right
                    bool flag = false;
                    for(int i = k ; i < physicalNum ; i++){
                        if(i == k){
                            continue;
                        }
                        if(physicalMem[i] != nullptr){
                            if(physicalMem[i]->aid == -1){
                                if(physicalMem[i]->parentId == physicalMem[k]->parentId){
                                    int tmp = physicalMem[i]->parentId;
                                    int pageNum = physicalMem[k]->pageNum*2;
                                    physicalMem[k] = new PageBundle(pageNum , -1, k);
                                    physicalMem[k]->buddyPageNum = pageNum;
                                    physicalMem[k]->pbId = tmp;
                                    if(tmp%2 == 0){
                                        tmp = (tmp - 2)/2;
                                    }else{
                                        tmp = (tmp - 1)/2;
                                    }
                                    physicalMem[k]->parentId = tmp;
                                    flag = true;

                                    physicalMem[i] = nullptr;
                                }
                            }
                            break;
                        }
                    }

                    // left
                    for(int i = k ; i >= 0 ; i--){
                        if(i == k){
                            continue;
                        }
                        if(physicalMem[i] != nullptr){
                            if(physicalMem[i]->aid == -1){
                                if(physicalMem[i]->parentId == physicalMem[k]->parentId){
                                    int tmp = physicalMem[i]->parentId;
                                    int pageNum = physicalMem[k]->pageNum*2;
                                    physicalMem[i] = new PageBundle(pageNum , -1, i);
                                    physicalMem[i]->pbId = tmp;
                                    physicalMem[i]->buddyPageNum = pageNum;
                                    if(tmp%2 == 0){
                                        tmp = (tmp - 2)/2;
                                    }else{
                                        tmp = (tmp - 1)/2;
                                    }
                                    physicalMem[i]->parentId = tmp;
                                    flag = true;
                                    physicalMem[k] = nullptr;
                                }
                            }
                            break;
                        }
                    }
                    if(flag){
                        k--;
                    }
                }
            }


            list<Task*>::iterator task_iter;
            for(task_iter = runningTask->begin() ; task_iter != runningTask->end() ; task_iter++){
                if(task_iter.operator*()->pid == currentCpuTask->pid){
                    runningTask->remove(*task_iter);
                    break;
                }
            }

            currentCpuTask->flagToEmpty = true;
        }else{
            timeInterval++;
            currentCpuTask->current_cmd.operator++();
            currentCpuTask->current_cmd_int++;
            currentCpuTask->flagToComplete = false;
        }
    }

    if(timeInterval % 8 == 0){
        // update physical memory page's reference byte
        // initialize physical memory page's reference bit
        for(int i = 0 ; i < physicalNum ; i++){
            if(physicalMem[i] != nullptr && physicalMem[i]->aid != -1){
                physicalMem[i]->reference_byte.push_front(physicalMem[i]->reference_bit);
                physicalMem[i]->reference_byte.remove(physicalMem[i]->reference_byte.back());
                physicalMem[i]->reference_bit = 0;
            }
        }
    }

    // cpu was empty
    if(currentCpuTask->flagToEmpty){
        currentCpuTask->flagToEmpty = false;
        currentCpuTask = nullTask;
    }
    currentCycle++;
}
