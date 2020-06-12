#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <list>
#include "Task.h"
#include "InputIO.h"
#include "check_sleep.h"
#include "cmd_sleep.h"
#include "check_ioWait.h"
#include "cmd_ioWait.h"
#include "check_taskToRun.h"
#include "scheduler.h"
#include "commandExecuter.h"
#include "printLog.h"
#include "printMemoryLog.h"
#include "updateStatus.h"
#include "debugLog.h"
#include "PageBundle.h"
#include "report_criteria.h"


using namespace std;

int main(int argc, char* argv[]) {


    string sched = "fcfs";
    string page = "fifo";
    string dir = ".";
    int totalEventNum;
    int vmemSize;
    int pmemSize;
    int pageSize;
    int allocationID = 1;
    int timeInterval = 0;                   // time interval for lru-sample
    int page_fault = 0;
    int accessCounter = 0;

//    save options
    for(int i=1; i<argc ; i++){
        string option = argv[i];
        int pivot = option.find("=") + 1;
        int opt_length = option.size() - pivot;
        string opt = option.substr(0, pivot);
        string opt_detail = option.substr(pivot, opt_length);

        if(strcmp(opt.c_str(), "-sched=") == 0){
            sched = opt_detail;
        }else if(strcmp(opt.c_str(), "-page=") == 0){
            page = opt_detail;
        }else if(strcmp(opt.c_str(), "-dir=") == 0){
            dir = opt_detail;
        }
    }


//    save task
    string input_file = dir + "/" + "input";

    ifstream infile;
    infile.open(input_file.c_str());
    infile>>totalEventNum>>vmemSize>>pmemSize>>pageSize;

    list<Task*> all_task;
    list<Task*> runningTask;
    list<InputIO*> all_input;
    list<PageBundle*> all_pages;

    int pid_count = 0;
    for(int i=0 ; i<totalEventNum ; i++) {
        int startTime;
        string process_name;
        infile >> startTime >> process_name;

        if (strcmp(process_name.c_str(), "INPUT") == 0) {
            int target_pid;
            infile >> target_pid;
            all_input.push_back(new InputIO(process_name, startTime, target_pid));
        } else {
            Task *newTask = new Task(startTime, dir, process_name, pid_count);
            newTask->burstTime = 5.0;
            newTask->burstTime_exp = 5.0;
            newTask->setData(vmemSize, pageSize);
            all_task.push_back(newTask);
            pid_count++;
        }
    }


    list<Task*> run_queue;
    list<Task*> sleepList;
    list<Task*> ioWaitList;
    list<Task*> endProcess;
    list<int> lockList;

    int physicalMemorySize = pmemSize/pageSize;
    PageBundle** physicalMemory = new PageBundle*[physicalMemorySize];

    for(int i = 0 ; i < physicalMemorySize ; i++){
        if(i == 0){
            physicalMemory[i] = new PageBundle(physicalMemorySize, -1, 0);
            physicalMemory[i]->pbId = 0;
            physicalMemory[i]->parentId = -1;
        }else{
            physicalMemory[i] = nullptr;
        }
    }

    Task* nullTask = new Task(-1, ".", "null", -1);
    nullTask->burstTime = 10000000.0;
    nullTask->burstTime_exp = 10000000.0;
    nullTask->runningTime = -1;
    Task* currentCpuTask = nullTask;


    // main loop
    int inProcessing = all_task.size();
    int currentCycle = 0;
    scheduler schedulerBot = scheduler(sched, &run_queue, nullTask);


    string out_schedule = dir + "/scheduler.txt";
    FILE* fp_sched = fopen(out_schedule.c_str(), "w");

    string out_memory = dir + "/memory.txt";
    FILE* fp_memory = fopen(out_memory.c_str(), "w");

    while(inProcessing > 0){

        bool append = false;
        currentCycle++;

        // step 1
        bool append1 = check_sleep(&run_queue, &sleepList);

        // step 2
        bool append2 = check_ioWait(&run_queue, &ioWaitList, &all_input, currentCycle);

        // step 3
        bool append3 = check_taskToRun(&run_queue, &runningTask, &all_task, currentCycle);

        append = append1 || append2 || append3;

        // step 4
        currentCpuTask = schedulerBot.schedule(currentCpuTask, append);

        report_criteria(currentCpuTask, &run_queue, currentCycle);

        // step 5
        commandExecuter(currentCpuTask, &sleepList, &ioWaitList, &lockList, &runningTask, &all_pages, physicalMemory, sched, page, allocationID, physicalMemorySize, currentCycle, page_fault);

        if(currentCpuTask->pid != -1){
            int* runCmd = currentCpuTask->current_cmd.operator*();
            if(runCmd[0] == 1){
                accessCounter++;
            }
        }

        // step 6
        printLog(fp_sched, currentCpuTask, run_queue, sleepList, ioWaitList, currentCycle);
        printMemoryLog(fp_memory, currentCpuTask, &all_pages, physicalMemory, physicalMemorySize, &runningTask, currentCycle, page_fault);

        // step 7
        updateStatus(currentCpuTask, nullTask, &run_queue, &runningTask, &sleepList, &ioWaitList, &endProcess, physicalMemory, physicalMemorySize, currentCycle, timeInterval);

        // check number of running process
        inProcessing = run_queue.size() + sleepList.size() + ioWaitList.size();
        if(currentCpuTask->pid != -1){
            inProcessing++;
        }

    }
    fprintf(fp_memory, "page fault = %d\n", page_fault);

    // end!
    fclose(fp_sched);
    fclose(fp_memory);

}
