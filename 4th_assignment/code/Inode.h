//
// Created by seungsu on 2020-06-26.
//
#include <string>
#include <string.h>

using namespace std;

#ifndef PROJECT4_INODE_H
#define PROJECT4_INODE_H


class Inode {
public:
    int id;
    string name;
    int size;

    int direct_numBlocks;
    int single_indirect_numBlocks;
    int double_indirect_numBlocks;
    int totalBlocks;

    Inode(){}

    Inode(int _id, string _name, int _size, int &totalBlockNum){
        id = _id;
        name = _name;
        size = _size;
        direct_numBlocks = 0;
        single_indirect_numBlocks = 0;
        double_indirect_numBlocks = 0;
        make_Inode(_size);
        totalBlocks = direct_numBlocks + single_indirect_numBlocks + double_indirect_numBlocks;
        totalBlockNum += totalBlocks;
    }

    void make_Inode(int file_size);
};

#endif //PROJECT4_INODE_H
