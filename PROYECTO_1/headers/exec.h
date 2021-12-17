#ifndef __EXEC_H__
#define __EXEC_H__


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "./Structs.h"
#include "./utilities.h"
using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::ifstream;
class Exec
{
public:
    string path;
    vector<string> commands;
    Exec();
    void execute(vector<PARAMETER*>* params);
};
#endif