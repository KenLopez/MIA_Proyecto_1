#include "../headers/mkdisk.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

Mkdisk::Mkdisk(){
    size = -1;
    path = "";
    unit = tNONE; 
    fit = tNONE;
}

void Mkdisk::writeDisk(FILE* file){
    MBR_STRUCT newDisk;
    newDisk.mbr_tamano = size;
    newDisk.disk_fit = paramToChar(fit);
    time_t t;
    time(&t);
    char datetime[20];
    struct tm *tm = localtime(&t);
    strftime(datetime, 20, "%d/%m/%Y %H:%M:%S", tm);
    strcpy(newDisk.mbr_fecha_creacion, datetime);
    newDisk.mbr_disk_signature = rand() % 9999 + 1;
    newDisk.mbr_partition_1.part_status = 0;
    newDisk.mbr_partition_2.part_status = 0;
    newDisk.mbr_partition_3.part_status = 0;
    newDisk.mbr_partition_4.part_status = 0;
    fwrite("\0", 1, 1, file);
    fseek(file, newDisk.mbr_tamano - 1, SEEK_SET);
    fwrite("\0", 1, 1, file);
    rewind(file);
    fwrite(&newDisk, sizeof(MBR_STRUCT), 1, file);
    fclose(file);
    cout<<"Disco "<<path<<", creado exitosamente."<<endl;
}

void Mkdisk::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        if(p->name == pPATH){
            if(path!=""){
                cout<<"ERROR MKDISK: Parámetro path ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR MKDISK: Ruta no válida."<<endl;
                return;
            }
            path = p->text;
        }else if(p->name == pSIZE){
            if(size>0){
                cout<<"ERROR MKDISK: Parámetro size ya fue definido."<<endl;
                return;
            }else if(p->value==0){
                cout<<"ERROR MKDISK: El tamanio de disco debe ser mayor a 0."<<endl;
                return;
            }
            size = p->value;
        }else if(p->name == pUNIT){
            if(unit!=tNONE){
                cout<<"ERROR MKDISK: Parámetro unit ya fue definido."<<endl;
                return;
            }
            unit = p->param;
        }else if(p->name == pFIT){
            if(fit!=tNONE){
                cout<<"ERROR MKDISK: Parámetro fit ya fue definido."<<endl;
                return;
            }
            fit = p->param;
        }else{
            cout<<"ERROR MKDISK: Comando mkdisk posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if(path=="" || size<1){
        cout<<"ERROR MKDISK: Comando mkdisk no posee parámetros obligatorios (unit, path)."<<endl;
        return;
    }
    if(fit == tNONE){ fit = tFF; }
    if(unit == tNONE){ unit = tMB; }
    size = convertBytes(size, unit);
    if(FILE *file = fopen(path.c_str(), "r")){
         
        cout << "ERROR MKDISK: El disco "<<getName(path)<<" ya existe en "<<path<<"."<<endl; 
        fclose(file);
    }
    else { 
        if(FILE *file = fopen(path.c_str(), "w")){
            writeDisk(file);
            return;
        }
        if(mkdir(getDIR(path).c_str(), 0777) == -1){
            cout<<"ERROR MKDISK: No se pudo crear el directorio."<<endl;
            return;
        }else{
            if(FILE *file = fopen(path.c_str(), "w")){
                writeDisk(file);
                return;
            }else{
               cout<<"ERROR MKDISK: No se pudo crear el disco."<<endl;
                return; 
            }
        }
    }
}
