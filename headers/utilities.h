#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Structs.h"
#include "../headers/mkdisk.h"
#include "../headers/rmdisk.h"
#include "../headers/fdisk.h"
#include "../headers/exec.h"
#include "../headers/Structs.h"
#include "../headers/rep.h"
#include "../analizador/Parser.h"
#include "../analizador/Lexer.h"
using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<string> split(string delim, string str);

string getDIR(string f_path);

string getName(string f_path);

int toBytes(int num, PARAM_TYPE size);

MBR_STRUCT getMBR(FILE* file);

char paramToChar(PARAM_TYPE t);

PARAM_TYPE charToParam(char t);

DISK_SPACE newSpace(int i, int s);

vector<PART_STRUCT*> getPrimaries(MBR_STRUCT* mbr);

vector<EBR_STRUCT> getLogics(FILE* file, int ini);

int convertBytes(int size, PARAM_TYPE unit);

PART_STRUCT* getExtended(MBR_STRUCT* mbr);

string getCMD(int argc, char* argv[]);

COMMAND* parse(string cmd);

void execCmd(COMMAND* command);

#endif