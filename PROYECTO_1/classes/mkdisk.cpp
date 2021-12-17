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
    cout<<"\033[92mDisco "<<path<<", creado exitosamente.\033[0m"<<endl;
}

void Mkdisk::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        if(p->name == pPATH){
            if(path!=""){
                cout<<"\033[91mERROR MKDISK: Parámetro path ya fue definido.\033[0m"<<endl;
                return;
            }else if(p->text==""){
                cout<<"\033[91mERROR MKDISK: Ruta no válida.\033[0m"<<endl;
                return;
            }
            path = p->text;
        }else if(p->name == pSIZE){
            if(size>0){
                cout<<"\033[91mERROR MKDISK: Parámetro size ya fue definido.\033[0m"<<endl;
                return;
            }else if(p->value==0){
                cout<<"\033[91mERROR MKDISK: El tamanio de disco debe ser mayor a 0.\033[0m"<<endl;
                return;
            }
            size = p->value;
        }else if(p->name == pUNIT){
            if(unit!=tNONE){
                cout<<"\033[91mERROR MKDISK: Parámetro unit ya fue definido.\033[0m"<<endl;
                return;
            }
            unit = p->param;
        }else if(p->name == pFIT){
            if(fit!=tNONE){
                cout<<"\033[91mERROR MKDISK: Parámetro fit ya fue definido.\033[0m"<<endl;
                return;
            }
            fit = p->param;
        }else{
            cout<<"\033[91mERROR MKDISK: Comando mkdisk posee parámetros incorrectos.\033[0m"<<endl;
            return;
        }
    }
    if(path=="" || size<1){
        cout<<"\033[91mERROR MKDISK: Comando mkdisk no posee parámetros obligatorios (size, path).\033[0m"<<endl;
        return;
    }
    if(fit == tNONE){ fit = tFF; }
    if(unit == tNONE){ unit = tMB; }
    size = convertBytes(size, unit);
    if(FILE *file = fopen(path.c_str(), "r")){
        cout << "\033[91mERROR MKDISK: El disco "<<getName(path)<<" ya existe en "<<path<<".\033[0m"<<endl; 
        fclose(file);
        return;
    }else { 
        createDirs(getDIR(path));
        if(FILE *file = fopen(path.c_str(), "w")){
            writeDisk(file);
            return;
        }else{
            cout<<"\033[91mERROR MKDISK: No se pudo crear el disco.\033[0m"<<endl;
            return; 
        }
    }
}
