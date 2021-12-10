#ifndef __MKDISK_H__
#define __MKDISK_H__


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
class Mkdisk
{
public:
    int size;
    string path;
    PARAM_TYPE unit; 
    PARAM_TYPE fit;
    Mkdisk();
    void execute(vector<PARAMETER*>* params);
    void createDisk();
    void writeDisk(FILE* file);
    
};
#endif
