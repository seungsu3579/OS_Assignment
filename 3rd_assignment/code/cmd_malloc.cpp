//
// Created by seungsu on 20. 6. 8..
//

#include "cmd_malloc.h"

void cmd_malloc(Task* &currentCpuTask, list<PageBundle*>* all_pages, int memorySize, int &aid) {

    currentCpuTask->memoryCursor = -1;

    for(int i = 0 ; i < currentCpuTask->pageTableSize ; i++){
        if(currentCpuTask->pageTable_aid[i] != nullptr){
            // check this part is valid
            PageBundle* pb = currentCpuTask->pageTable_aid[i];
            if(pb->aid == -1 && pb->pageNum >= memorySize){

                int binSize = pb->pageNum - memorySize;

                PageBundle* malloc = new PageBundle(memorySize, aid, i);
                PageBundle* malloc_v = new PageBundle(memorySize, 0, i);
                malloc->accessCount = 0;

                currentCpuTask->pageTable_aid[i] = malloc;
                currentCpuTask->pageTable_valid[i] = malloc_v;

                all_pages->push_back(malloc);

                currentCpuTask->recentAid = aid;
                currentCpuTask->recentPageNum = memorySize;

                if(binSize != 0){
                    PageBundle* bin = new PageBundle(binSize, -1, i+memorySize);
                    currentCpuTask->pageTable_aid[i+memorySize] = bin;
                    currentCpuTask->pageTable_valid[i+memorySize] = bin;
                }

                aid++;

                break;
            }
        }
    }

    currentCpuTask->flagToEmpty = false;
    currentCpuTask->flagToComplete = true;

}
