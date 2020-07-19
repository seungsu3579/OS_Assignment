//
// Created by seungsu on 2020-06-27.
//
#include <list>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include "Dentry.h"
#include "Inode.h"

#ifndef PROJECT4_CMD_CD_H
#define PROJECT4_CMD_CD_H

using namespace std;

void cmd_cd(Dentry *root_dentry, Dentry* &current_dentry, list<string> &args, string &current_path);



#endif //PROJECT4_CMD_CD_H
