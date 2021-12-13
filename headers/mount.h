#ifndef __MOUNT_H__
#define __MOUNT_H__


#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include "./Structs.h"
#include "./utilities.h"
using std::vector;
using std::string;
using std::endl;
using std::cout;
class Mount
{
public:
    vector<DISK_MOUNT> mounted;
    void mountNew(vector<PARAMETER*>* params);
    void unmount(vector<PARAMETER*>* params);
    int findDisk(string path);
    int findPartition(DISK_MOUNT* disk, string name);
    int findMount(DISK_MOUNT* disk);
    int findDiskMount();
    int countActives(DISK_MOUNT* disk);
};
#endif