//
// Created by seungsu on 2020-06-26.
//

#include "cmd_inode.h"

void cmd_inode(Dentry *current_dentry, list<string> &args) {

    string fileName = args.front();
    list<Inode*>::iterator i_iter;
    bool error = true;
    for(i_iter = current_dentry->d_inode.begin() ; i_iter != current_dentry->d_inode.end() ; i_iter++){
        if(strcmp(i_iter.operator*()->name.c_str(), fileName.c_str()) == 0){
            error = false;
            break;
        }
    }

    if(error){
        cout << "error" << endl;
        return;
    }else{
        cout << "ID: " << i_iter.operator*()->id << endl;
        cout << "Name: " << i_iter.operator*()->name << endl;
        cout << "Size: " << i_iter.operator*()->size << " (bytes)" << endl;
        cout << "Direct blocks: " << i_iter.operator*()->direct_numBlocks << endl;
        cout << "Single indirect blocks: " << i_iter.operator*()->single_indirect_numBlocks << endl;
        cout << "Double indirect blocks: " << i_iter.operator*()->double_indirect_numBlocks << endl;
    }

}
