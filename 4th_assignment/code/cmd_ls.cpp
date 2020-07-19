//
// Created by seungsu on 2020-06-26.
//

#include "cmd_ls.h"


bool compare(Inode* a, Inode* b){
    return a->id < b->id;
}

void cmd_ls(Dentry *current_dentry) {
    list<Dentry*>::iterator d_iter;
    list<Inode*>::iterator i_iter;
    list<char*>::iterator s_iter;

    for(d_iter = current_dentry->d_dentry.begin() ; d_iter != current_dentry->d_dentry.end() ; d_iter++){
        cout << d_iter.operator*()->name << " ";
    }

    // sort by inode_id
    current_dentry->d_inode.sort(compare);

    // print log
    for(i_iter = current_dentry->d_inode.begin() ; i_iter != current_dentry->d_inode.end() ; i_iter++){
        cout << i_iter.operator*()->name << " ";
    }
    cout << endl;
}
