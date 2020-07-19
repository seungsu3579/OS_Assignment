//
// Created by seungsu on 2020-06-26.
//

#include "cmd_mkfile.h"

void cmd_mkfile(Dentry *current_dentry, list<string> &args, int &totalBlockNum, priority_queue<int, vector<int>, greater<int>> &inode_id, list<int> &alloc_inode_id) {
    // arguments
    string fileName;
    int fileSize;
    try{
        if(args.size() != 2){
            throw 3;
        }
        fileName = args.front();
        fileSize = stoi(args.back());
    } catch (int expn) {
        cout << "error" << endl;
        return;
    }

    // check whether filename is correct
    bool error = false;
    list<string>::iterator s_iter;
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        error = current_dentry->isInInode(s_iter.operator*());
        if(error){
            break;
        }
    }
    // check whether filesize is correct
    Inode checkInode = Inode(-1, "check", fileSize, totalBlockNum);
    if(totalBlockNum > 973){
        error = true;
    }
    totalBlockNum -= checkInode.totalBlocks;

    // check whether number of inode is more than 128
    if(inode_id.size() == 0){
        error = true;
    }

    if(error){
        cout << "error" << endl;
        return;
    }

    // make file
    int _id = inode_id.top();
    alloc_inode_id.push_back(_id);
    inode_id.pop();

    // make inode structure
    Inode* newInode = new Inode(_id, fileName, fileSize, totalBlockNum);

    // add directory
    current_dentry->d_inode.push_back(newInode);

    // print log
    int space_left = 973 - totalBlockNum;
    cout << "Now you have ..." << endl;
    cout << space_left << " / 973 (blocks)" << endl;

}
