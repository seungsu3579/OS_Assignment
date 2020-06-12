//
// Created by seungsu on 20. 6. 9..
//

#include "cmd_memAccess.h"

void cmd_memAccess(Task *&currentCpuTask, list<Task*>* runningTask, PageBundle **physicalMem, int physicalNum, int aid, int currentCycle, string page_opt, int &page_fault) {

    // find PageBundle in virtual memory
    bool accessFlag = false;
    int targetIndex;
    PageBundle* targetPb;
    for(int i = 0 ; i < currentCpuTask->pageTableSize ; i++){
        if(currentCpuTask->pageTable_aid[i] != nullptr){
            if(currentCpuTask->pageTable_aid[i]->aid == aid){
                targetPb = currentCpuTask->pageTable_aid[i];
                targetPb->calcBuddySize(physicalNum);
                targetIndex = i;
                break;
            }
        }
    }

    // check page bundle in physical memeory
    for(int i = 0 ; i < physicalNum ; i++){
        if(physicalMem[i] != nullptr){
            if(physicalMem[i]->aid == aid){
                physicalMem[i]->accessTime = currentCycle;
                physicalMem[i]->accessCount++;

                physicalMem[i]->reference_bit = 1;

                currentCpuTask->flagToEmpty = false;
                currentCpuTask->flagToComplete = true;
                return;
            }
        }
    }

    page_fault++;


    bool flag = true;
    // find empty space of physical memory to allocate memory(aid)
    for(int i = 0 ; i < physicalNum ; i++){
        if(physicalMem[i] != nullptr){
            PageBundle* pb = physicalMem[i];

            if(pb->aid == -1) {
                // check empty page bundle's size is equal to allocate memory buddy size / excess size then devide
                if (pb->pageNum == targetPb->buddyPageNum) {
                    // allocate physical Memory
                    physicalMem[i] = new PageBundle(pb->pageNum, targetPb->aid, i);
                    physicalMem[i]->buddyPageNum = targetPb->buddyPageNum;
                    physicalMem[i]->allocateTime = currentCycle;
                    physicalMem[i]->accessTime = currentCycle;
                    physicalMem[i]->accessCount = 1;
                    physicalMem[i]->pbId = pb->pbId;
                    physicalMem[i]->parentId = pb->parentId;
                    currentCpuTask->pageTable_valid[targetIndex]->aid = 1;

                    physicalMem[i]->reference_bit = 1;
                    for(int j = 0 ; j < 8 ; j++){
                        physicalMem[i]->reference_byte.push_front(0);
                    }

                    flag = false;
                    break;
                } else if (pb->pageNum > targetPb->buddyPageNum) {
                    // devide physical Memory by Buddy System
                    int childPbNum = pb->pageNum / 2;
                    int parentID = physicalMem[i]->pbId;

                    physicalMem[i] = new PageBundle(childPbNum, -1, i);
                    physicalMem[i]->parentId = parentID;
                    physicalMem[i]->pbId = parentID * 2 + 1;

                    physicalMem[i + childPbNum] = new PageBundle(childPbNum, -1, i + childPbNum);
                    physicalMem[i + childPbNum]->parentId = parentID;
                    physicalMem[i + childPbNum]->pbId = parentID * 2 + 2;

                    i--;
                }
            }
        }
    }

    // when there is no space in physical memory
    int deleteAid = 0;
    while(flag){

        if(strcmp(page_opt.c_str(), "fifo") == 0){
            // fifo
            deleteAid = pageChange_fifo(currentCpuTask, physicalMem, physicalNum, aid);

        }else if(strcmp(page_opt.c_str(), "lru") == 0){
            // lru
            deleteAid = pageChange_lru(currentCpuTask, physicalMem, physicalNum, aid);

        }else if(strcmp(page_opt.c_str(), "lru-sampled") == 0){
            // lru-sampled
            deleteAid = pageChange_lru_sample(currentCpuTask, physicalMem, physicalNum, aid);

        }else if(strcmp(page_opt.c_str(), "lfu") == 0){
            // lfu
            deleteAid = pageChange_lfu(currentCpuTask, physicalMem, physicalNum, aid);

        }else if(strcmp(page_opt.c_str(), "mfu") == 0){
            // mfu
            deleteAid = pageChange_mfu(currentCpuTask, physicalMem, physicalNum, aid);

        }else if(strcmp(page_opt.c_str(), "optimal") == 0){
            // optimal
            deleteAid = pageChange_lru(currentCpuTask, physicalMem, physicalNum, aid);

        }else{
            printf("%s\n", "Error : page change option was wrong!");
        }

        //check
        list<Task*>::iterator task_iter;
        for(task_iter = runningTask->begin() ; task_iter != runningTask->end() ; task_iter++){
            Task* task = task_iter.operator*();
            for(int i = 0 ; i < task->pageTableSize ; i++){
                if(task->pageTable_aid[i] != nullptr && task->pageTable_aid[i]->aid == deleteAid){
                    task->pageTable_valid[i]->aid = 0;
                }
            }
        }


        // retry memory access
        for(int i = 0 ; i < physicalNum ; i++){
            if(physicalMem[i] != nullptr && physicalMem[i]->aid == -1){
                PageBundle* pb = physicalMem[i];

                if(pb->pageNum == targetPb->buddyPageNum){
                    // allocate physical Memory
                    physicalMem[i] = new PageBundle(pb->pageNum, targetPb->aid, i);
                    physicalMem[i]->buddyPageNum = targetPb->buddyPageNum;
                    physicalMem[i]->allocateTime = currentCycle;
                    physicalMem[i]->accessTime = currentCycle;
                    physicalMem[i]->accessCount = 1;
                    physicalMem[i]->pbId = pb->pbId;
                    physicalMem[i]->parentId = pb->parentId;
                    currentCpuTask->pageTable_valid[targetIndex]->aid = 1;

                    physicalMem[i]->reference_bit = 1;
                    for(int j = 0 ; j < 8 ; j++){
                        physicalMem[i]->reference_byte.push_front(0);
                    }

                    flag = false;
                    break;
                }else if(pb->pageNum > targetPb->buddyPageNum){
                    // devide physical Memory by Buddy System
                    int childPbNum = pb->pageNum/2;
                    int parentID = physicalMem[i]->pbId;

                    physicalMem[i] = new PageBundle(childPbNum, -1, i);
                    physicalMem[i]->parentId = parentID;
                    physicalMem[i]->pbId = parentID*2 + 1;

                    physicalMem[i+childPbNum] = new PageBundle(childPbNum, -1, i+childPbNum);
                    physicalMem[i+childPbNum]->parentId = parentID;
                    physicalMem[i+childPbNum]->pbId = parentID*2 + 2;

                    i--;
                }
            }
        }
    }

    currentCpuTask->flagToEmpty = false;
    currentCpuTask->flagToComplete = true;
}
