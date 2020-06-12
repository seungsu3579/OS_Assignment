//
// Created by seungsu on 20. 6. 8..
//

#include "PageBundle.h"

void PageBundle::calcBuddySize(int physicalMemSize) {

    buddyPageNum = 0;
    int a = physicalMemSize;
    int b = physicalMemSize/2;
    while(true){
        if(a >= pageNum && b < pageNum){
            buddyPageNum = a;
            break;
        }
        a /= 2;
        b /= 2;
    }

}

double PageBundle::calcReferenceValue() {
    list<int>::iterator int_iter;
    double exp = 7;
    double reference_value = 0;

    for(int_iter = reference_byte.begin() ; int_iter != reference_byte.end() ; int_iter++){
        if(int_iter.operator*() == 1){
            reference_value = pow(2, exp);
        }
        exp = exp - 1.00000;
    }
    return reference_value;

}
