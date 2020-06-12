//
// Created by seungsu on 20. 6. 11..
//

#include "pageChange_lru_sample.h"

int pageChange_lru_sample(Task *&currentCpuTask, PageBundle **physicalMem, int physicalNum, int aid) {


    PageBundle* deleteBundle = nullptr;
    double allocateCycle = 280.0000;
    int bit = 2;
    int targetIndex;
    int returnAid = 0;

    // find release memory by fifo
    for(int i = 0 ; i < physicalNum ; i++){
        if(physicalMem[i] != nullptr && physicalMem[i]->aid != -1){
            // find allocated page bundle long time ago
            double refer_value = physicalMem[i]->calcReferenceValue();

            if (physicalMem[i]->reference_bit == bit) {
                if (refer_value < allocateCycle) {
                    deleteBundle = physicalMem[i];
                    allocateCycle = refer_value;
                    bit = physicalMem[i]->reference_bit;
                    targetIndex = i;
                }
            } else if(physicalMem[i]->reference_bit < bit) {
                deleteBundle = physicalMem[i];
                allocateCycle = refer_value;
                targetIndex = i;
                bit = physicalMem[i]->reference_bit;
            }
        }
    }


    // delete page bundle at physical memory
    physicalMem[targetIndex] = new PageBundle(deleteBundle->buddyPageNum, -1, targetIndex);
    physicalMem[targetIndex]->buddyPageNum = deleteBundle->buddyPageNum;
    physicalMem[targetIndex]->pbId = deleteBundle->pbId;
    physicalMem[targetIndex]->parentId = deleteBundle->parentId;

    returnAid = deleteBundle->aid;


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

    return returnAid;

}
