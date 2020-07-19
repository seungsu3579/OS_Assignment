//
// Created by seungsu on 2020-06-27.
//

#include "cmd_cd.h"

void cmd_cd(Dentry *root_dentry, Dentry* &current_dentry, list<string> &args, string &current_path) {
    string dir;
    list<string> path;
    list<string>::iterator s_iter;
    list<Dentry*>::iterator d_iter;
    if(args.size() == 0){
        cout << "error" << endl;
        return;
    }else{
        dir = args.front();
    }

    // check is it start from root
    bool isRoot = false;
    if(strcmp(dir.substr(0).c_str(), "/") == 0){
        current_dentry = root_dentry;
        current_path = "/";
    }

    // devide arguments
    int index = 0;
    while(index != string::npos){
        index = dir.find("/", 0);
        if(index != 0 && dir.size() != 0){
            path.push_back(dir.substr(0, index));
        }
        dir = dir.substr(index + 1);
    }


    // check is it correct directory
    bool error = false;
    Dentry* tmp = current_dentry;
    for(s_iter = path.begin() ; s_iter != path.end() ; s_iter++){
        bool exist = false;
        if(strcmp(s_iter.operator*().c_str(), "..") == 0){
            if(tmp->parent != nullptr){
                tmp = tmp->parent;
                exist = true;
            }else{
                exist = false;
            }
        }else if(strcmp(s_iter.operator*().c_str(), "") != 0){
            if(strcmp(s_iter.operator*().c_str(), ".") == 0){
                exist = true;
                break;
            }else{
                for(d_iter = tmp->d_dentry.begin() ; d_iter != tmp->d_dentry.end() ; d_iter++){
                    if(strcmp(d_iter.operator*()->name.c_str(), s_iter.operator*().c_str()) == 0){
                        exist = true;
                        tmp = d_iter.operator*();
                        break;
                    }
                }
            }
        }

        if(!exist){
            error = true;
            break;
        }
    }
    if(error){
        cout << "error" << endl;
        return;
    }


    // change directory
    for(s_iter = path.begin() ; s_iter != path.end() ; s_iter++){
        if(strcmp(s_iter.operator*().c_str(), "..") == 0){
            index = current_path.find(current_dentry->name, 0);
            current_path = current_path.substr(0, index - 1);
            current_dentry = current_dentry->parent;
            if(current_dentry->parent == nullptr){
                current_path = "/";
                isRoot = true;
            }
        }else if(strcmp(s_iter.operator*().c_str(), "") == 0){
        }else{
            if(strcmp(s_iter.operator*().c_str(), ".") != 0){
                for(d_iter = current_dentry->d_dentry.begin() ; d_iter != current_dentry->d_dentry.end() ; d_iter++){
                    if(strcmp(d_iter.operator*()->name.c_str(), s_iter.operator*().c_str()) == 0){
                        if(current_dentry->parent == nullptr){
                            isRoot = true;
                        }
                        current_dentry = d_iter.operator*();
                        if(isRoot){
                            current_path += s_iter.operator*();
                            isRoot = false;
                        }else{
                            current_path += "/" + s_iter.operator*();
                        }
                        break;
                    }
                }
            }
        }
    }
}