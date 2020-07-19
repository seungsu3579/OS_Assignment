//
// Created by seungsu on 2020-06-26.
//

#include "Dentry.h"

bool Dentry::isInDentry(string name) {
    list<Dentry*>::iterator d_iter;
    for(d_iter = d_dentry.begin() ; d_iter != d_dentry.end() ; d_iter++){
        if (strcmp(d_iter.operator*()->name.c_str(), name.c_str()) == 0){
            return true;
        }
    }
    return false;
}

bool Dentry::isInInode(string name) {
    list<Inode*>::iterator i_iter;
    for(i_iter = d_inode.begin() ; i_iter != d_inode.end() ; i_iter++){
        if (strcmp(i_iter.operator*()->name.c_str(), name.c_str()) == 0){
            return true;
        }
    }
    return false;
}

int Dentry::calc_blocks() {
    int numBlocks = 0;
    list<Inode*>::iterator i_iter;
    for(i_iter = d_inode.begin() ; i_iter != d_inode.end() ; i_iter++){
        numBlocks += i_iter.operator*()->totalBlocks;
        i_iter.operator*();
    }

    list<Dentry*>::iterator d_iter;
    for(d_iter = d_dentry.begin() ; d_iter != d_dentry.end() ; d_iter++){
        numBlocks += d_iter.operator*()->calc_blocks();
    }

    return numBlocks;
}
