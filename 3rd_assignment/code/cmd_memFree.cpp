//
// Created by seungsu on 20. 6. 8..
//

#include "cmd_memFree.h"

void cmd_memFree(Task* &currentCpuTask, int aid, PageBundle** physicalMem, int physicalNum){

    int prev = -1;
    int next = -1;

    // release memory from
    for(int i = 0 ; i < currentCpuTask->pageTableSize ; i++){
        if(currentCpuTask->pageTable_aid[i] != nullptr){
            PageBundle* pb = currentCpuTask->pageTable_aid[i];
            PageBundle* pb_v = currentCpuTask->pageTable_valid[i];

            //find allocated id
            if(pb->aid == aid ){

                // check around memory isEmpty?
                for(int k = i; k < currentCpuTask->pageTableSize ; k++){
                    if(k == i){
                        continue;
                    }
                    if(currentCpuTask->pageTable_aid[k] != nullptr){
                        if(currentCpuTask->pageTable_aid[k]->aid == -1){
                            next = k;
                        }
                        break;
                    }
                }
                for(int j = i ; j >= 0 ; j--){
                    if(j == i){
                        continue;
                    }
                    if(currentCpuTask->pageTable_aid[j] != nullptr){
                        if(currentCpuTask->pageTable_aid[j]->aid == -1){
                            prev = j;
                        }
                        break;
                    }
                }

                // free memory and conquer bins
                int binSize = pb->pageNum;
                int binIndex = pb->index;

                currentCpuTask->recentPageNum = pb->pageNum;
                currentCpuTask->recentAid = pb->aid;

                if(next != -1){
                    binSize += currentCpuTask->pageTable_aid[next]->pageNum;

                    currentCpuTask->pageTable_aid[next] = nullptr;
                    currentCpuTask->pageTable_valid[next] = nullptr;
                }
                if(prev != -1){
                    binIndex = currentCpuTask->pageTable_aid[prev]->index;
                    binSize += currentCpuTask->pageTable_aid[prev]->pageNum;

                    currentCpuTask->pageTable_aid[i] = nullptr;
                    currentCpuTask->pageTable_valid[i] = nullptr;
                }

                PageBundle* bin = new PageBundle(binSize, -1, binIndex);
                currentCpuTask->pageTable_aid[binIndex] = bin;
                currentCpuTask->pageTable_valid[binIndex] = bin;

                break;
            }
        }
    }



    // release memory from physical memory
    PageBundle* deleteBundle = nullptr;
    int targetIndex;

    // delete page bundle at physical memory
    for(int i = 0 ; i < physicalNum ; i++){
        if(physicalMem[i] != nullptr && physicalMem[i]->aid == aid){
            deleteBundle = physicalMem[i];
            targetIndex = i;
            break;
        }
    }

    if(deleteBundle != nullptr){

        physicalMem[targetIndex] = new PageBundle(deleteBundle->buddyPageNum, -1, targetIndex);
        physicalMem[targetIndex]->buddyPageNum = deleteBundle->buddyPageNum;
        physicalMem[targetIndex]->pbId = deleteBundle->pbId;
        physicalMem[targetIndex]->parentId = deleteBundle->parentId;

        // check around page bundle to conquer ( Buddy System )
        // right
        for(int i = targetIndex ; i < physicalNum ; i++){
            if(i == targetIndex){
                continue;
            }
            if(physicalMem[i] != nullptr){
                if(physicalMem[i]->aid == -1){
                    if(physicalMem[i]->parentId == deleteBundle->parentId){
                        int tmp = physicalMem[i]->parentId;
                        physicalMem[targetIndex] = new PageBundle(deleteBundle->buddyPageNum*2 , -1, targetIndex);
                        physicalMem[targetIndex]->pbId = tmp;
                        physicalMem[targetIndex]->buddyPageNum = deleteBundle->buddyPageNum*2;
                        if(tmp%2 == 0){
                            tmp = (tmp - 2)/2;
                        }else{
                            tmp = (tmp - 1)/2;
                        }
                        physicalMem[targetIndex]->parentId = tmp;

                        physicalMem[i] = nullptr;
                    }
                }
                break;
            }
        }

        // left
        for(int i = targetIndex ; i >= 0 ; i--){
            if(i == targetIndex){
                continue;
            }
            if(physicalMem[i] != nullptr){
                if(physicalMem[i]->aid == -1){
                    if(physicalMem[i]->parentId == deleteBundle->parentId){
                        int tmp = physicalMem[i]->parentId;
                        physicalMem[i] = new PageBundle(deleteBundle->buddyPageNum*2 , -1, i);
                        physicalMem[i]->pbId = tmp;
                        physicalMem[i]->buddyPageNum = deleteBundle->buddyPageNum*2;
                        if(tmp%2 == 0){
                            tmp = (tmp - 2)/2;
                        }else{
                            tmp = (tmp - 1)/2;
                        }
                        physicalMem[i]->parentId = tmp;

                        physicalMem[targetIndex] = nullptr;
                    }
                }
                break;
            }
        }
    }

    // to update later
    currentCpuTask->flagToEmpty = false;
    currentCpuTask->flagToComplete = true;

}