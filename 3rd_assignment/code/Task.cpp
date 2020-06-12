//
// Created by seungsu on 20. 6. 4..
//

#include "Task.h"

void Task::setData(int vmemSize, int pageSize) {

    pageTableSize = vmemSize/pageSize;

    pageTable_aid = new PageBundle*[pageTableSize];
    pageTable_valid = new PageBundle*[pageTableSize];

    for(int i = 0 ; i < pageTableSize ; i++){
        if(i == 0){
            pageTable_aid[0] = new PageBundle(pageTableSize, -1, 0);
            pageTable_valid[0] = new PageBundle(pageTableSize, -1, 0);
        }else{
            pageTable_aid[i] = nullptr;
            pageTable_valid[i] = nullptr;
        }
    }




    ifstream process;
    string process_name = directory + "/" + file_name;
    process.open(process_name.c_str());

    process>>cmd_num;
    for(int i = 0 ; i < cmd_num ; i++) {
        int *cmd = new int[2];
        for (int k = 0; k < 2; k++) {
            process>>cmd[k];
        }
        cmd_list.push_back(cmd);
    }
    process.close();

    current_cmd = cmd_list.begin();
    current_cmd_int = 1;
}

void Task::printCmd() {
    printf("%d  %d  %s\n", pid, cmd_num, file_name.c_str());
    list<int*>::iterator iter = cmd_list.begin();
    for(; iter != cmd_list.end() ; iter++){
        int* cmd = *iter;
        printf("cmd : %d   | opt : %d\n", cmd[0], cmd[1]);
    }

}

void Task::calcSimple() {


    // update burstTime info at Task
    int usedTime = runningTime + 1;
    usedCpuTime.push_back(usedTime);
    double num = (double)usedCpuTime.size();

    // calculate sjf-exponential burst time
    double pre_burstTime;
    double new_burstTime;

    if(usedCpuTime.size() == 1){
        new_burstTime = (double) usedTime;
        printf(">>> %f = %f\n", (double) usedTime, new_burstTime);
    }else{
        pre_burstTime = burstTime;
        double tmp1 = 1/num;
        double tmp2 = (num-1)/num;
        new_burstTime = tmp1*(double)usedTime + tmp2*pre_burstTime;
        printf(">>> %f*(%f) + %f*(%f) = %f\n", (double)usedTime, tmp1, pre_burstTime, tmp2, new_burstTime);
    }
    burstTime = new_burstTime;


//
//    // update burstTime info at Task
//    int usedTime = runningTime + 1;
//    usedCpuTime.push_back(usedTime);
//
//    // calculate sjf-simple burst time
//    list<int>::iterator time_iter;
//    int expectedTime = 0;
//    for(time_iter = usedCpuTime.begin() ; time_iter != usedCpuTime.end() ; time_iter++){
//        expectedTime += time_iter.operator*();
//    }
//    burstTime = expectedTime/usedCpuTime.size();
////    printf(">>> %f / %d = %f\n", expectedTime, usedCpuTime.size(), burstTime);



}

void Task::calcExponential() {

    // update burstTime info at Task
    int usedTime = runningTime + 1;
    usedCpuTime.push_back(usedTime);

    // calculate sjf-exponential burst time
    double pre_burstTime;
    double new_burstTime;

    if(usedCpuTime.size() == 1){
        new_burstTime = (double) usedTime;
        printf(">>> %f = %f\n", (double) usedTime, new_burstTime);
    }else{
        pre_burstTime = burstTime_exp;
        new_burstTime = (0.6)*(double)usedTime + (0.4)*pre_burstTime;
        printf(">>> %f*(0.6) + %f*(0.4) = %f\n", (double)usedTime, pre_burstTime, new_burstTime);
    }
    burstTime_exp = new_burstTime;

}
