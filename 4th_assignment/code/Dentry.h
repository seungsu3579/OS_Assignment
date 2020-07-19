//
// Created by seungsu on 2020-06-26.
//
#include <string>
#include <string.h>
#include <list>
#include "Inode.h"


#ifndef PROJECT4_DENTRY_H
#define PROJECT4_DENTRY_H

using namespace std;

class Dentry {
public:
    string name;

    Dentry* parent;
    list<Dentry*> d_dentry;
    list<Inode*> d_inode;

    Dentry(){}

    Dentry(string _name){
        parent = nullptr;
        name = _name.c_str();
    }

    Dentry(string _name, Dentry* parentDentry){

        name = _name;
        parent = parentDentry;
    }

    bool isInDentry(string name);

    bool isInInode(string name);

    int calc_blocks();

};


#endif //PROJECT4_DENTRY_H
