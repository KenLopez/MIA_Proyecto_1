#include "../headers/mount.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void Mount::unmount(vector<PARAMETER*>* params){
    int i;
    int j;
    string id;
    PARAMETER* p;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        if(p->name == pID){
            if(id!=""){
                cout<<"ERROR UNMOUNT: Parámetro id ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR UNMOUNT: Id no válido."<<endl;
                return;
            }
            id = p->text;
        }else{
            cout<<"ERROR UNMOUNT: Comando unmount posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if(id==""){
        cout<<"ERROR UNMOUNT: Comando unmount no posee parámetros obligatorios (id)."<<endl;
        return;
    }
    for ( i = 0; i < mounted.size(); i++)
    {
        for ( j = 0; j < mounted[i].mounted.size(); j++)
        {
            if(mounted[i].mounted[j].id == id){
                mounted[i].mounted[j].status = 0;
                if(!countActives(&(mounted[i]))){
                    mounted[i].status = 0;
                }
                cout<<"La partición "<<id<<" ha sido desmontada exitosamente."<<endl;
                return;
            }
        }
        
    }
    cout << "ERROR UNMOUNT: No se pudo desmontar la partición "<<id<<", no se encuentra montada."<<endl;
    return;
}

int Mount::countActives(DISK_MOUNT* disk){
    int i;
    for ( i = 0; i < disk->mounted.size(); i++)
    {
        if((*disk).mounted[i].status){
            return 1;
        }
    }
    return 0;
}

void Mount::mountNew(vector<PARAMETER*>* params){
    string path;
    string name;
    DISK_MOUNT new_disk;
    PART_MOUNT new_part;
    std::stringstream ss;
    string part_num;
    int i;
    int disk_index;
    int part_index;
    PARAMETER* p;
    MBR_STRUCT mbr;
    PART_STRUCT* partition;
    vector<PART_STRUCT*>primaries;
    vector<EBR_STRUCT>logics;
    FILE* file;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        if(p->name == pPATH){
            if(path!=""){
                cout<<"ERROR MOUNT: Parámetro path ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR MOUNT: Ruta no válida."<<endl;
                return;
            }
            path = p->text;
        }else if(p->name == pNAME){
            if(name!=""){
                cout<<"ERROR MOUNT: Parámetro name ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR MOUNT: Nombre de partición no válido."<<endl;
                return;
            }
            name = p->text;
        }else{
            cout<<"ERROR MOUNT: Comando mount posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if(path=="" || name==""){
        cout<<"ERROR MOUNT: Comando mount no posee parámetros obligatorios (path, name)."<<endl;
        return;
    }
    if(file = fopen(path.c_str(), "r+")){
        mbr = getMBR(file);
        primaries = getPrimaries(&mbr);
        for ( i = 0; i < primaries.size(); i++)
        {
            if(primaries[i]->part_status && primaries[i]->part_name == name){
                if(primaries[i]->part_type == 'E'){
                    cout<<"ERROR MOUNT: No puedes montar una partición extendida."<<endl;
                    return;
                }else{
                    disk_index = findDisk(path);
                    if(disk_index == -1){
                        disk_index = findDiskMount();
                        new_disk.disk = path;
                        new_disk.status = 1;
                        if(disk_index == -1){    
                            mounted.push_back(new_disk);
                            disk_index = mounted.size()-1;
                        }else{
                            mounted[disk_index] = new_disk;
                        }
                    }
                    part_index = findPartition(&(mounted[disk_index]), name);
                    if(part_index == -1){
                        new_part.ini = primaries[i]->part_start;
                        new_part.name = primaries[i]->part_name;
                        new_part.status = 1;
                        new_part.type = tPRIMARY;
                        part_index = findMount(&(mounted[disk_index]));
                        if(part_index == -1){
                            part_index = mounted[disk_index].mounted.size();
                            ss << part_index + 1;
                            ss >> part_num;
                            new_part.id = "vd" + intToLetter(0) + part_num;
                            mounted[disk_index].mounted.push_back(new_part);
                        }else{
                            new_part.id = mounted[disk_index].mounted[part_index].id;
                            mounted[disk_index].mounted[part_index] = new_part;
                        }
                        cout<<"La partición "<<name<<"en "<<path<<" ha sido montada exitosamente. (ID: "<<new_part.id<<")"<<endl;
                        return;
                    }else{
                        cout<<"ERROR MOUNT: La partición "<<name<<" en "<<path<<" ya se encuentra montada."<<endl;
                        return;
                    }
                }
            }
        }
        partition = getExtended(&mbr);
        if(partition){
            logics = getLogics(file, partition->part_start);
            for ( i = 0; i < logics.size(); i++)
            {
                if(logics[i].part_status && logics[i].part_name == name){
                    disk_index = findDisk(path);
                    if(disk_index == -1){
                        disk_index = findDiskMount();
                        new_disk.disk = path;
                        new_disk.status = 1;
                        if(disk_index == -1){    
                            mounted.push_back(new_disk);
                            disk_index = mounted.size()-1;
                        }else{
                            mounted[disk_index] = new_disk;
                        }
                    }
                    part_index = findPartition(&(mounted[disk_index]), name);
                    if(part_index == -1){
                        new_part.ini = logics[i].part_start;
                        new_part.name = logics[i].part_name;
                        new_part.status = 1;
                        new_part.type = tLOGIC;
                        part_index = findMount(&(mounted[disk_index]));
                        if(part_index == -1){
                            part_index = mounted[disk_index].mounted.size();
                            ss << part_index + 1;
                            ss >> part_num;
                            new_part.id = "vd" + intToLetter(0) + part_num;
                            mounted[disk_index].mounted.push_back(new_part);
                        }else{
                            new_part.id = mounted[disk_index].mounted[part_index].id;
                            mounted[disk_index].mounted[part_index] = new_part;
                        }
                        cout<<"La partición "<<name<<" en "<<path<<" ha sido montada exitosamente. (ID: "<<new_part.id<<")"<<endl;;
                        return;
                    }else{
                        cout<<"ERROR MOUNT: La partición "<<name<<" en "<<path<<" ya se encuentra montada."<<endl;
                        return;
                    }
                }
            }      
        }
        cout << "ERROR MOUNT: La partición "<<name<<" no fue encontrada en "<<path<<"."<<endl;;
        return;
    }else{
        cout << "ERROR MOUNT: El disco "<<getName(path)<<" no fue encontrado en la ruta "<<path<<"."<<endl;
        return;
    }
}

int Mount::findDisk(string path){
    int i;
    for ( i = 0; i < mounted.size(); i++)
    {
        if(mounted[i].disk == path){
            return i;
        }
    }
    return -1;
}

int Mount::findPartition(DISK_MOUNT* disk, string name){
    int i;
    for ( i = 0; i < disk->mounted.size(); i++)
    {
        if(((*disk).mounted[i].name == name)){
            return i;
        }
    }
    return -1;
}

int Mount::findDiskMount(){
    int i;
    for ( i = 0; i < mounted.size(); i++)
    {
        if(!mounted[i].status){
            return i;
        }
    }
    return -1;
    
}

int Mount::findMount(DISK_MOUNT* disk){
    int i;
    for ( i = 0; i < (*disk).mounted.size(); i++)
    {
        if(!(*disk).mounted[i].status){
            return i;
        }
    }
    return -1;
}