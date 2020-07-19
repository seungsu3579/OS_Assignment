//
// Created by seungsu on 2020-06-26.
//

#include "cmd_mkdir.h"

void cmd_mkdir(Dentry *current_dentry, list<string> &args) {

    // check whether arguments are correct
    bool error = false;
    list<string>::iterator s_iter;
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        // check whether directory is in d_dentry of current_dentry
        error = current_dentry->isInDentry(s_iter.operator*());
        if(error){
            break;
        }
    }

    if(error){
        cout << "error" << endl;
        return;
    }

    // make directory
    for(s_iter = args.begin() ; s_iter != args.end() ; s_iter++){
        Dentry* newDentry = new Dentry(s_iter.operator*(), current_dentry);
        current_dentry->d_dentry.push_back(newDentry);
    }

}
