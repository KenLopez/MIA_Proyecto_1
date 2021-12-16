#include <iostream>
#include <vector>
using namespace std;
#include "headers/utilities.h"
#include "headers/mount.h"

int main(int argc, char* argv[])
{
    if(argc<2){
        cout<<"ERROR: No se introdujo ningún comando."<<endl;
        return 0;
    }
    string args = getCMD(argc, argv);
    COMMAND* command;
    Mount mount;
    command = parse(args.c_str());
    if(command!=NULL){
        execCmd(command, &mount);
    }
    return 0;
}