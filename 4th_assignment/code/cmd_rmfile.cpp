//
// Created by seungsu on 2020-06-26.
//

#include "cmd_rmfile.h"

void cmd_rmfile(Dentry *current_dentry, list<string> &args, int &totalBlockNum, priority_queue<int, vector<int>, greater<int>> &inode_id, list<int> &alloc_inode_id) {

    // check whether arguments are correct
    bool error = false;
    list<string>::iterator s_iter;
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        error = current_dentry->isInInode(s_iter.operator*());
        if(error == 0){
            error = true;
            break;
        }
        error = false;
    }

    if(error){
        cout << "error" << endl;
        return;
    }

    int delete_space = 0;

    // remove file list
    list<Inode*> rmInodeList;

    // remove file
    list<Inode*>::iterator i_iter;
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        for(i_iter = current_dentry->d_inode.begin() ; i_iter != current_dentry->d_inode.end() ; i_iter++){
            if(strcmp(i_iter.operator*()->name.c_str() ,s_iter.operator*().c_str()) == 0){
                delete_space += i_iter.operator*()->totalBlocks;
                rmInodeList.push_back(i_iter.operator*());
            }
        }
    }

    for(i_iter = rmInodeList.begin() ; i_iter != rmInodeList.end() ; i_iter++){
        current_dentry->d_inode.remove(i_iter.operator*());
        inode_id.push(i_iter.operator*()->id);
        alloc_inode_id.remove(i_iter.operator*()->id);
    }

    totalBlockNum -= delete_space;

    int space_left = 973 - totalBlockNum;

    // result print
    cout << "Now you have ..." << endl;
    cout << space_left << " / 973 (blocks)" << endl;


}
