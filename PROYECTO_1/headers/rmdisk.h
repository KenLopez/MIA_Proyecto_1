#ifndef __RMDISK_H__
#define __RMDISK_H__


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
class Rmdisk
{
public:
    string path;
    Rmdisk();
    void execute(vector<PARAMETER*>* params);
};
#endif