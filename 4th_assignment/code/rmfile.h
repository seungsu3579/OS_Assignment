//
// Created by seungsu on 2020-06-27.
//
#include <list>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include "Dentry.h"
#include "Inode.h"

#ifndef PROJECT4_RMFILE_H
#define PROJECT4_RMFILE_H


void rmfile(Dentry* current_dentry, list<string> &args, int &totalBlockNum, priority_queue<int, vector<int>, greater<int>> &inode_id, list<int> &alloc_inode_id);

#endif //PROJECT4_RMFILE_H
