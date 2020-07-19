//
// Created by seungsu on 2020-06-26.
//

#include "cmd_rmdir.h"

int calc_blocks(Dentry* target_dentry, int &totalBlockNum, priority_queue<int, vector<int>, greater<int>> &inode_id, list<int> &alloc_inode_id) {
    int numBlocks = 0;
    list<Inode*>::iterator i_iter;
    list<basic_string<char>> files;
    for(i_iter = target_dentry->d_inode.begin() ; i_iter != target_dentry->d_inode.end() ; i_iter++){
        numBlocks += i_iter.operator*()->totalBlocks;
        files.push_back(i_iter.operator*()->name.substr(0));
    }

    if(files.size() != 0){
        rmfile(target_dentry->parent, files, totalBlockNum, inode_id, alloc_inode_id);
    }

    list<Dentry*>::iterator d_iter;
    for(d_iter = target_dentry->d_dentry.begin() ; d_iter != target_dentry->d_dentry.end() ; d_iter++){
        numBlocks += calc_blocks(d_iter.operator*(), totalBlockNum, inode_id, alloc_inode_id);
    }

    return numBlocks;
}


void cmd_rmdir(Dentry *current_dentry, list<string> &args, int &totalBlockNum, priority_queue<int, vector<int>, greater<int>> &inode_id, list<int> &alloc_inode_id) {

    // check whether arguments are correct
    bool error = false;
    list<string>::iterator s_iter;
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        error = current_dentry->isInDentry(s_iter.operator*());
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

    // remove dentry list
    list<Dentry*> rmDentryList;

    // remove directory
    list<Dentry*>::iterator d_iter;
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        for(d_iter = current_dentry->d_dentry.begin() ; d_iter != current_dentry->d_dentry.end() ; d_iter++){
            if(strcmp(d_iter.operator*()->name.c_str() ,s_iter.operator*().c_str()) == 0){
                delete_space += calc_blocks(d_iter.operator*(), totalBlockNum, inode_id, alloc_inode_id);
                rmDentryList.push_back(d_iter.operator*());
            }
        }
    }

    for(d_iter = rmDentryList.begin() ; d_iter != rmDentryList.end() ; d_iter++){
        current_dentry->d_dentry.remove(d_iter.operator*());
    }

    totalBlockNum -= delete_space;

    int space_left = 973 - totalBlockNum;

    // result print
    cout << "Now you have ..." << endl;
    cout << space_left << " / 973 (blocks)" << endl;

}
