//
// Created by seungsu on 20. 6. 8..
//

#include "cmd_lock.h"

void cmd_lock(Task* &currentCpuTask, list<int>* lockList, int lockId) {

    list<int>::iterator int_iter;
    bool flag = true;

    for(int_iter = lockList->begin() ; int_iter != lockList->end() ; int_iter++){
        if(int_iter.operator*() == lockId){
            flag = false;

            currentCpuTask->flagToEmpty = false;
            currentCpuTask->flagToComplete = false;
            break;
        }
    }

    if(flag){
        lockList->push_back(lockId);

        currentCpuTask->flagToEmpty = false;
        currentCpuTask->flagToComplete = true;
    }

}
