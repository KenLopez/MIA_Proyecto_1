#ifndef __REP_H__
#define __REP_H__


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
class Mount;
class Rep
{
public:
    PARAM_TYPE name;
    string path, id, disk;
    Mount* mount;
    Rep();
    void execute(vector<PARAMETER*>* params);
    void createMBR(FILE* file);
    void createDisk(FILE* file);
};
#endif