#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;
#include "headers/utilities.h"

int main(int argc, char* argv[])
{
    if(argc<2){
        cout<<"ERROR: No se introdujo ningún comando."<<endl;
        return 0;
    }

    string args = getCMD(argc, argv);
    parse(args.c_str());
    return 0;
}