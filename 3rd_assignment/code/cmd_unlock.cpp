//
// Created by seungsu on 20. 6. 8..
//

#include "cmd_unlock.h"

void cmd_unlock(Task* &currentCpuTask, list<int>* lockList, int unlockId) {

    list<int>::iterator int_iter;
    list<int> tmp;

    for(int_iter = lockList->begin() ; int_iter != lockList->end() ; int_iter++){
        if(int_iter.operator*() == unlockId){
            tmp.push_back(int_iter.operator*());
        }
    }

    for(int_iter = tmp.begin() ; int_iter != tmp.end() ; int_iter++){
        lockList->remove(int_iter.operator*());
    }

    currentCpuTask->flagToEmpty = false;
    currentCpuTask->flagToComplete = true;
}
