#ifndef __FDISK_H__
#define __FDISK_H__


#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "./Structs.h"
#include "./utilities.h"
using std::vector;
using std::string;
using std::endl;
using std::cout;
class Fdisk
{
public:
    int size, add;
    string path, name;
    PARAM_TYPE unit, fit, type, delet; 

    Fdisk();
    void execute(vector<PARAMETER*>* params);
    void readDisk();
    void newPrimary();
    void newLogic(EBR_STRUCT* nEBR);
    bool checkPrimary();
    vector<DISK_SPACE> getAvailablePrimary();
    bool allocateLogic();
    void newExtended();
    bool allocatePartition(vector<DISK_SPACE> free);
    void deletePartition();
    bool checkPartName();
    void changeSize();
    void changePrimary(int index);
    void changeLogic(int index);
    void deletePrimary(int index);
    void deleteLogic(int index);
    int searchPrimary();
    int searchLogic();

private:
    FILE* file;
    MBR_STRUCT mbr;
    PART_STRUCT* partition;
    vector<PART_STRUCT*>primaries;
    vector<EBR_STRUCT>logics;

};
#endif