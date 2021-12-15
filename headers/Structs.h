#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

/*** Constantes ENUM ***/

typedef enum tagCOMMAND_NAME
{
    cNONE,
    cCREATE_DISK,
    cRMDISK,
    cFDISK,
    cREP,
    cEXEC,
    cMOUNT,
    cUMOUNT,
    cPAUSE,
    cCOMMENT,
} COMMAND_NAME;

typedef enum tagPARAM_NAME{
    pSIZE,
    pPATH,
    pUNIT,
    pFIT,
    pNONE,
    pTYPE,
    pDELETE, 
    pNAME,
    pADD,
    pID,
    pRUTA,
    
} PARAM_NAME;

typedef enum tagPARAM_TYPE{
    tFF,
    tWF,
    tBF,
    tNONE,
    tMB,
    tKB,
    tB,
    tPRIMARY,
    tEXTENDED,
    tLOGIC,
    tFULL,
    tFAST,
    tMBR,
    tDISK,
    
} PARAM_TYPE;

typedef struct tagParameter
{
    PARAM_NAME name;
    char* text;
    int value;
    PARAM_TYPE param;
} PARAMETER;

PARAMETER *createParam(PARAM_NAME name, char* text, int value, PARAM_TYPE param);
void deleteParam(PARAMETER *p);

/*** Command ***/
typedef struct tagCOMMAND {
    COMMAND_NAME name;
    std::vector<PARAMETER*> *parameters;
} COMMAND;

COMMAND *allocateCOMMAND();
void deleteCOMMAND(COMMAND *b);

typedef struct tagPARTITION
{
    int part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
} PART_STRUCT;

typedef struct tagEBR
{
    int part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];

} EBR_STRUCT;

typedef struct tagPartitionMount{
    string id;
    int status;
    PARAM_TYPE type;
    string name;
    int ini;
} PART_MOUNT;

typedef struct tagDiskMount
{
    string disk;
    int status;
    vector<PART_MOUNT> mounted;
} DISK_MOUNT;

typedef struct tagDISK_SPACE
{
    int size;
    int ini;
} DISK_SPACE;

typedef struct tagMBR
{
    int mbr_tamano;
    char mbr_fecha_creacion[20];
    int mbr_disk_signature;
    char disk_fit;
    PART_STRUCT mbr_partition_1;
    PART_STRUCT mbr_partition_2;
    PART_STRUCT mbr_partition_3;
    PART_STRUCT mbr_partition_4;

} MBR_STRUCT;

#endif
