//
// Created by seungsu on 20. 6. 8..
//

#include <list>
#include <math.h>
#ifndef PRACTICE1_PAGEBUNDLE_H
#define PRACTICE1_PAGEBUNDLE_H

using namespace std;

class PageBundle {
public:
    int accessTime;
    int allocateTime;
    int accessCount;
    int reference_bit;
    list<int> reference_byte;

    int buddyPageNum;
    int pageNum;
    int aid;
    int index;

    int pbId;
    int parentId;

    PageBundle(int page, int allocationId, int ind){
        pageNum = page;
        aid = allocationId;
        index = ind;
    }

    PageBundle(){
    }

    void calcBuddySize(int physicalMemSize);

    double calcReferenceValue();

};


#endif //PRACTICE1_PAGEBUNDLE_H
