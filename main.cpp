#include <iostream>
#include <vector>
using namespace std;
#include "headers/utilities.h"

int main(int argc, char* argv[])
{
    if(argc<2){
        cout<<"ERROR: No se introdujo ningún comando."<<endl;
        return 0;
    }

    string args = getCMD(argc, argv);
    COMMAND* command;
    command = parse(args.c_str());
    execCmd(command);
    return 0;
}