//
// Created by seungsu on 20. 6. 4..
//

#include <string>
#include <string.h>
#ifndef PRACTICE1_INPUTIO_H
#define PRACTICE1_INPUTIO_H

using namespace std;

class InputIO{

public:
    int target_pid;
    int startCycle;
    string file_name;

    InputIO(string fileName, int start, int t_pid){
        startCycle = start;
        target_pid = t_pid;
        file_name = fileName;
    }

    InputIO(){
    }
};

#endif //PRACTICE1_INPUTIO_H
