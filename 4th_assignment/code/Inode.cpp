//
// Created by seungsu on 2020-06-26.
//

#include "Inode.h"

void Inode::make_Inode(int file_size) {
    int fileBlockNum = file_size/1024;
    if (file_size%1024 != 0){
        fileBlockNum++;
    }

    // calculate size
    int directSize = 0;
    int singleIndirectSize = 0;
    int doubleIndirectSize = 0;
    if(fileBlockNum <= 12){
        directSize = fileBlockNum;
    }else if(fileBlockNum <= 256 + 12){
        directSize = 12;
        singleIndirectSize = fileBlockNum - 12;
    }else {
        directSize = 12;
        singleIndirectSize = 256;
        doubleIndirectSize = fileBlockNum - 256 - 12;
    }

    // allocate direct blocks
    direct_numBlocks = directSize;

    // allocate single indirect blocks
    if(singleIndirectSize != 0){
        single_indirect_numBlocks = 1 + singleIndirectSize;
    }

    // allocate double indirect blocks
    if(doubleIndirectSize != 0){
        int indirectNum = doubleIndirectSize/256;
        if(doubleIndirectSize%256 != 0){
            indirectNum++;
        }
        double_indirect_numBlocks = 1 + indirectNum + doubleIndirectSize;
    }
}
