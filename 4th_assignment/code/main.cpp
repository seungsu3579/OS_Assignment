#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <sstream>
#include <queue>
#include <iostream>
#include <vector>

#include "Inode.h"
#include "Dentry.h"

#include "cmd_ls.h"
#include "cmd_cd.h"
#include "cmd_mkdir.h"
#include "cmd_rmdir.h"
#include "cmd_mkfile.h"
#include "cmd_rmfile.h"
#include "cmd_inode.h"

using namespace std;

list<string> split_arguments(const string& data) {
    list<string> arguments;
    string arg;
    stringstream ss(data);

    while (ss >> arg) {
        arguments.push_back(arg);
    }
    return arguments;
}


int main() {

    string id = "2016147014";
    string current_path = "/";

    // initialize disk block number
    int totalBlockNum = 0;

    // initialize inode id
    priority_queue<int, vector<int>, greater<int>> inode_id;
    list<int> alloc_inode_id;
    for(int k = 0 ; k < 128 ; k++){
        inode_id.push(k);
    }

    // initialize root
    Dentry *root;
    root = new Dentry("/");

    Dentry* current_dentry = root;


    while (true){

        // get command
        string command;
        string arg;
        list<string> args;

        cout << id << ":" << current_path << "$";
        getline(cin, arg);

        args = split_arguments(arg);
        if(args.empty()){
            continue;
        }else{
            command = args.front();
            args.remove(command);
        }

        if (strcmp(command.c_str(), "exit") == 0){
            // stop
            break;

        }else if(strcmp(command.c_str(), "ls") == 0){
            // show directory and file
            cmd_ls(current_dentry);

        }else if(strcmp(command.c_str(), "cd") == 0){
            // change directory
            cmd_cd(root, current_dentry, args, current_path);

        }else if(strcmp(command.c_str(), "mkdir") == 0){
            // make directory
            cmd_mkdir(current_dentry, args);

        }else if(strcmp(command.c_str(), "rmdir") == 0){
            // remove directory
            cmd_rmdir(current_dentry, args, totalBlockNum, inode_id, alloc_inode_id);

        }else if(strcmp(command.c_str(), "mkfile") == 0){
            // make file
            cmd_mkfile(current_dentry, args, totalBlockNum, inode_id, alloc_inode_id);

        }else if(strcmp(command.c_str(), "rmfile") == 0){
            // remove file
            cmd_rmfile(current_dentry, args, totalBlockNum, inode_id, alloc_inode_id);

        }else if(strcmp(command.c_str(), "inode") == 0){
            // show inode info
            cmd_inode(current_dentry, args);

        }else{
            cout << "error" << endl;
        }
    }
}
