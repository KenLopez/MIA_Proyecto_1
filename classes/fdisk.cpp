#include "../headers/fdisk.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

Fdisk::Fdisk(){
    path = "";
    size = -1;
    add = 0;
    name = "";
    unit = tNONE;
    delet = tNONE;
    fit = tNONE;
    type = tNONE;
}

void Fdisk::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        switch (p->name)
        {
        case pPATH:
            if(path!=""){
                cout<<"ERROR FDISK: Parámetro path ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR FDISK: Ruta no válida."<<endl;
                return;
            }
            path = p->text;
            break;
        
        case pSIZE:
            if(size!=-1){
                cout<<"ERROR FDISK: Parámetro size ya fue definido."<<endl;
                return;
            }else if(p->value == 0){
                cout<<"ERROR FDISK: Size debe ser mayor a 0."<<endl;
                return;
            }
            size = p->value;
            break;
        case pNAME:
            if(name!=""){
                cout<<"ERROR FDISK: Parámetro name ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR FDISK: Nombre no válido."<<endl;
                return;
            }else if(strlen(p->text)>16){
                cout<<"ERROR FDISK: Nombre excede la cantidad máxima de caracteres [16]."<<endl;
                return;
            }
            name = p->text;
            break;
        
        case pTYPE:
            if(type!=tNONE){
                cout<<"ERROR FDISK: Parámetro type ya fue definido."<<endl;
                return;
            }
            type = p->param;
            break;
        
        case pUNIT:
            if(unit!=tNONE){
                cout<<"ERROR FDISK: Parámetro unit ya fue definido."<<endl;
                return;
            }
            unit = p->param;
            break;
        
        case pDELETE:
            if(delet!=tNONE){
                cout<<"ERROR FDISK: Parámetro delete ya fue definido."<<endl;
                return;
            }
            delet = p->param;
            break;
        
        case pFIT:
            if(fit!=tNONE){
                cout<<"ERROR FDISK: Parámetro fit ya fue definido."<<endl;
                return;
            }
            fit = p->param;
            break;
        
        case pADD:
            if(add != 0){
                cout<<"ERROR FDISK: Parámetro add ya fue definido."<<endl;
                return;
            }else if(p->param == 0){
                cout<<"ERROR FDISK: Parámetro add debe ser diferente de 0."<<endl;
                return;
            }
            add = p->value;
            break;
        default:
            cout<<"ERROR FDISK: Comando fdisk posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if((size==-1 && add==0 && delet==tNONE) || path=="" || name==""){
        cout<<"ERROR FDISK: Comando fdisk no posee parámetros obligatorios (size / add / delete; path, name)."<<endl;
        return;
    }
    if(name.length()>16){ cout<<"ERROR FDISK: Nombre de partición supera la longitud máxima (16)."<<endl; return; }
    if(unit == tNONE){ unit = tKB; }
    if(type == tNONE){ type = tPRIMARY; }
    if(fit == tNONE){ fit = tWF; }
    size = convertBytes(size, unit);
    add = convertBytes(add, unit);
    if(file = fopen(path.c_str(), "r+")){
        mbr = getMBR(file);
        primaries = getPrimaries(&mbr);
        partition = getExtended(&mbr);
        if(partition){
            logics = getLogics(file, partition->part_start);
        }
        if(size>0){
            if(!checkPartName()){
                cout << "ERROR FDISK: La partición "<<name<<" no pudo ser creada, existe una partición "; 
                cout << "con el mismo nombre."<<endl;
                return;
            }
            switch (type)
            {
            case tEXTENDED:
                if(partition){
                    cout << "ERROR FDISK: La partición "<<name<<" no pudo ser creada, partición "; 
                    cout << "extendida ya fue creada ("<<partition->part_name<<")."<<endl;
                    break;
                }

            case tPRIMARY:
                if(checkPrimary()){
                    vector<DISK_SPACE> free = getAvailablePrimary();
                    if(free.size()>0){
                        if(allocatePartition(free)){
                            newPrimary();
                            if(type==tEXTENDED){
                                newExtended();
                            }
                            cout << "La partición "<<name<<" ha sido creada exitosamente en "<<path<<"."<<endl; 
                            break;
                        }
                    }
                    cout << "ERROR FDISK: La partición "<<name<<" no pudo ser creada en "<<path<<", espacio insuficiente para alojar."<<endl; 
                    break;
                }else{
                    cout << "ERROR FDISK: La partición "<<name<<" no pudo ser creada en "<<path<<", la capacidad máxima "; 
                    cout << "de particiones primarias alcanzó su límite."<<endl;
                    break;
                }
                break;
            
            case tLOGIC:
                if(partition){
                    if(allocateLogic()){
                        cout << "La partición "<<name<<" ha sido creada exitosamente en "<<path<<"."<<endl; 
                    }else{
                        cout << "ERROR FDISK: La partición "<<name<<" no pudo ser creada en "<<path<<", espacio insuficiente para alojar."<<endl;
                    }
                }else{
                    cout << "ERROR FDISK: La partición "<<name<<" no pudo ser creada en "<<path<<", partición "; 
                    cout << "extendida no fue encontrada."<<endl;
                }
                break;
            default:
                break;
            }
        }else if(delet!=tNONE){
           deletePartition();
        }else if(add!=0){
            changeSize();
        }
        fclose(file);
    }else { 
        cout << "ERROR FDISK: El disco "<<getName(path)<<" no fue encontrado en la ruta "<<path<<"."<<endl;
    }
}

void Fdisk::changeSize(){
    int i = searchPrimary();
     if(i!=-1){
        changePrimary(i);
        return;
    }
    i = searchLogic();
    if(i!=-1){
        changeLogic(i);
        return;
    }
    cout << "ERROR FDISK: La partición "<<name<<" no fue encontrada en la ruta "<<path<<"."<<endl;
}

void Fdisk::changePrimary(int index){
    if(add>0){
        int i;
        PART_STRUCT* next = primaries[index];
        for ( i = 0; i < primaries.size(); i++)
        {
            if((primaries[i]->part_status)&&(primaries[i]->part_start>primaries[index]->part_start)){
                if(index!=i){
                    next = primaries[i];
                }
            }
        }
        if(next->part_start!=primaries[index]->part_start){
            if(next->part_start-(primaries[index]->part_start+primaries[index]->part_size)>=add){
                primaries[index]->part_size += add;
                newPrimary();
                cout << "La partición "<<name<<" ha sido ampliada exitosamente en "<<path<<"."<<endl; 
            }else{
                cout << "ERROR FDISK: La partición "<<name<<" no pudo ser ampliada en "<<path<<", no existe suficiente espacio disponible."<<endl;
            }
        }else if(mbr.mbr_tamano-(primaries[index]->part_start+primaries[index]->part_size)>=add){
            primaries[index]->part_size += add;
            newPrimary();
            cout << "La partición "<<name<<" ha sido ampliada exitosamente en "<<path<<"."<<endl; 
        }else{
            cout << "ERROR FDISK: La partición "<<name<<" no pudo ser ampliada en "<<path<<", no existe suficiente espacio disponible."<<endl;
        }
    }else{
        int result = primaries[index]->part_size+add;
        if(result>0){
            primaries[index]->part_size = result;
            newPrimary();
            cout << "La partición "<<name<<" ha sido encogida exitosamente en "<<path<<"."<<endl; 
        }else{
            cout << "ERROR FDISK: La partición "<<name<<" no pudo ser encogida en "<<path<<", espacio a encoger supera tamaño de partición."<<endl;
        }
    }   
}

void Fdisk::changeLogic(int index){
    if(add>0){
        int lim = logics[index].part_start+logics[index].part_size;
        if(logics[index].part_next==-1 && ((partition->part_start+partition->part_size)>=(logics[index].part_start+logics[index].part_size+add))){
            logics[index].part_size += add;
            newLogic(&logics[index]);
            cout << "La partición "<<name<<" ha sido ampliada exitosamente en "<<path<<"."<<endl;
        }else if((logics[index].part_next-lim)>=add){
            logics[index].part_size += add;
            newLogic(&logics[index]);
            cout << "La partición "<<name<<" ha sido ampliada exitosamente en "<<path<<"."<<endl; 
        }else{
             cout << "ERROR FDISK: La partición "<<name<<" no pudo ser ampliada en "<<path<<", no existe suficiente espacio disponible."<<endl;
        }
    }else{
        int result = logics[index].part_size+add;
        if(result>0 && result>sizeof(EBR_STRUCT)){
            logics[index].part_size = result;
            newLogic(&logics[index]);
            cout << "La partición "<<name<<" ha sido encogida exitosamente en "<<path<<"."<<endl; 
        }else{
            cout << "ERROR FDISK: La partición "<<name<<" no pudo ser encogida en "<<path<<", espacio a encoger supera tamaño mínimo requerido (";
            cout<<sizeof(EBR_STRUCT)<<")"<<endl;
        }
    }
}

void Fdisk::deletePrimary(int index){
    if(primaries[index]->part_type == 'E'){
        if(logics.size()>0){
            cout<<"ERROR FDISK: La particion "<<primaries[index]->part_name<<" no pudo ser eliminada, pues es una partición extendida y existen particiones lógicas creadas."<<endl;
            return;
        }
    }
    switch (delet)
    {
    case tFULL:
        fseek(file, primaries[index]->part_start, SEEK_SET);
        int j;
        for ( j = 0; j < primaries[index]->part_size; j++)
        {
            putc('\0', file);
        }
        PART_STRUCT n;
        n.part_status = 0;
        *primaries[index] = n;
        newPrimary();
        break;
    case tFAST:
        primaries[index]->part_status = 0;
        newPrimary();
        break;
    default:
        break;
    }
}

void Fdisk::deleteLogic(int index){
    if(logics.size()==1){
        newExtended();
        return;
    }else if(index == 0){
        if(delet==tFULL){
            fseek(file, logics[index].part_start, SEEK_SET);
            int j;
            for ( j = 0; j < logics[index].part_size; j++)
            {
                putc('\0', file);
            }
            EBR_STRUCT nEBR;
            nEBR.part_status = 0;
            nEBR.part_start = partition->part_start;
            nEBR.part_next = logics[index].part_next;
            newLogic(&nEBR);
        }else{
            logics[index].part_status = 0;
            newLogic(&logics[index]);
        }
        return;
    }else if(index == logics.size()-1){
        logics[index-1].part_next = -1;
        newLogic(&logics[index-1]);
    }else{
        logics[index-1].part_next = logics[index+1].part_start;
        newLogic(&logics[index-1]);
    }
    switch (delet)
    {
    case tFULL:
        fseek(file, logics[index].part_start, SEEK_SET);
        int j;
        for ( j = 0; j < logics[index].part_size; j++)
        {
            putc('\0', file);
        }
        break;
    default:
        break;
    }
}

void Fdisk::deletePartition(){
    int i = searchPrimary();
     if(i!=-1){
        deletePrimary(i);
        cout << "La partición "<<name<<" ha sido borrada exitosamente en "<<path<<"."<<endl; 
        return;
    }
    i = searchLogic();
    if(i!=-1){
        deleteLogic(i);
        cout << "La partición "<<name<<" ha sido borrada exitosamente en "<<path<<"."<<endl; 
        return;
    }
    cout << "ERROR FDISK: La partición "<<name<<" no fue encontrada en la ruta "<<path<<"."<<endl;
}

int Fdisk::searchLogic(){
    int i;
    for(i=0; i<logics.size(); i++){
        if(logics[i].part_name == name){
            return i;
        }
    }
    return -1;
}

int Fdisk::searchPrimary(){
    int i;
    for ( i = 0; i < primaries.size(); i++)
    {
        if(primaries[i]->part_name == name){
            return i;
        }
    }
    return -1;
}

bool Fdisk::allocatePartition(vector<DISK_SPACE> free){
    int i;
    DISK_SPACE space = free[0];
    PART_STRUCT newPart;
    newPart.part_size = size;
    newPart.part_fit = paramToChar(fit);
    newPart.part_status = 1;
    newPart.part_type = paramToChar(type);
    for ( i = 0; i < free.size(); i++)
    {
        if(free[i].size>=size){
            if(mbr.disk_fit=='F'){
                newPart.part_start = free[i].ini;
                *partition = newPart;
                strcpy(partition->part_name, name.c_str());
                return true;
            }else if(mbr.disk_fit=='B'){
                if(space.size>free[i].size || space.size<size){
                    space = free[i];
                }
            }else if(mbr.disk_fit == 'W'){
                if(space.size<free[i].size){
                    space = free[i];
                }
            }
        }
    }
    if(space.size>=size){
        newPart.part_start = space.ini;
        *partition = newPart;
        strcpy(partition->part_name, name.c_str());
        return true;
    }
    return false;
    
}

vector<DISK_SPACE> Fdisk::getAvailablePrimary(){
    vector<DISK_SPACE>free ;
    free.push_back(newSpace(sizeof(MBR_STRUCT)+1, mbr.mbr_tamano-sizeof(MBR_STRUCT)));
    int i, j;
    for ( i = 0; i < primaries.size(); i++)
    {
        PART_STRUCT prim = *primaries[i];
        int prim_end = primaries[i]->part_start+primaries[i]->part_size-1;
        if(primaries[i]->part_status){
            for ( j = 0; j < free.size(); j++)
            {
                DISK_SPACE fr = free[j];
                int fr_end = free[j].ini+free[j].size-1;
                
                if(prim.part_start == fr.ini){
                    if(prim_end != fr_end){
                        free[j].ini = prim_end+1;
                        free[j].size = fr.size-prim.part_size;
                    }
                }else if(prim_end == fr_end){
                    free[j].ini = fr.ini;
                    free[j].size = fr.size-prim.part_size;
                }else if(prim.part_start>fr.ini && prim_end<fr_end){
                    free[j].ini = fr.ini;
                    free[j].size = prim.part_start-fr.ini;
                    free.insert(free.begin()+j+1, newSpace(prim_end+1, fr_end-prim_end));
                }
            }
            
        }
    }
    return free;
}

bool Fdisk::allocateLogic(){
    EBR_STRUCT nEBR;
    int space = 0;
    int index = 0;
    if(logics.size()==0){
        if(partition->part_size<size){
            return false;
        }
        space = partition->part_size;
        nEBR.part_next = -1;
        nEBR.part_start = partition->part_start;
        nEBR.part_size = size;
        nEBR.part_fit = paramToChar(fit);
        nEBR.part_status = 1;
        strcpy(nEBR.part_name, name.c_str());
        fseek(file, nEBR.part_start, SEEK_SET);
        fwrite(&nEBR, sizeof(EBR_STRUCT), 1, file);
        return true;
    }else if (logics[0].part_start!=partition->part_start){
        space = logics[0].part_start-partition->part_start;
        index = -1;
    }else if(logics[0].part_next == -1){
        space = (partition->part_start+partition->part_size-1)-(logics[0].part_start+logics[0].part_size-1);
    }else{
        space = logics[0].part_next - (logics[0].part_start+logics[0].part_size-1);
    }
    if(space<=0){
        return false;
    }
    int i, s;
    for ( i = 0; i < logics.size(); i++)
    {   
        if(logics[i].part_next == -1){
            s = (partition->part_start+partition->part_size-1)-(logics[i].part_start+logics[i].part_size-1);
        }else{
            s = logics[i].part_next - (logics[i].part_start+logics[i].part_size-1);
        }
        //cout<<"SPACE "<<s<<endl;
        if(s>=size){
            if(partition->part_fit=='F'){
                nEBR.part_size = size;
                nEBR.part_fit = paramToChar(fit);
                nEBR.part_status = 1;
                strcpy(nEBR.part_name, name.c_str());
                if(i==-1){
                    nEBR.part_start = partition->part_start;
                    nEBR.part_next = logics[0].part_start;
                }else{
                    nEBR.part_next = logics[i].part_next;
                    nEBR.part_start = logics[i].part_start+logics[i].part_size;
                    logics[i].part_next = nEBR.part_start;
                    fseek(file, logics[i].part_start, SEEK_SET);
                    fwrite(&logics[i], sizeof(EBR_STRUCT), 1, file);
                }
                newLogic(&nEBR);
                return true;
            }else if(partition->part_fit=='B'){
                if(space>s || space<size){
                    space = s;
                    index = i;
                }
            }else if(partition->part_fit == 'W'){
                if(space<s){
                    space = s;
                    index = i;
                }
            }
        }
    }
    if(space>=size){
        nEBR.part_size = size;
        nEBR.part_fit = paramToChar(fit);
        nEBR.part_status = 1;
        strcpy(nEBR.part_name, name.c_str());
        if(index!=-1){
            nEBR.part_next = logics[index].part_next;
            nEBR.part_start = logics[index].part_start+logics[index].part_size;
            logics[index].part_next = nEBR.part_start;
            fseek(file, logics[index].part_start, SEEK_SET);
            fwrite(&logics[index], sizeof(EBR_STRUCT), 1, file);
        }else{
            nEBR.part_next = logics[0].part_next;
            nEBR.part_start = partition->part_start;
        }
        newLogic(&nEBR);
        return true;
    }
    return false;
    
}

void Fdisk::newLogic(EBR_STRUCT* nEBR){
    fseek(file, nEBR->part_start, SEEK_SET);
    fwrite(nEBR, sizeof(EBR_STRUCT), 1, file);
}

void Fdisk::newPrimary(){
    rewind(file);
    fwrite(&mbr, sizeof(MBR_STRUCT), 1, file);
}

void Fdisk::newExtended(){
    EBR_STRUCT nEBR;
    nEBR.part_status = 0;
    nEBR.part_start = partition->part_start;
    nEBR.part_next = -1;
    fseek(file, partition->part_start, SEEK_SET);
    fwrite(&nEBR, sizeof(EBR_STRUCT),1,file);
    //cout<<"SIZE OF EBR_STRUCT:"<<sizeof(EBR_STRUCT)<<endl;
}

bool Fdisk::checkPrimary(){
    int i;
    for ( i = 0; i < primaries.size(); i++)
    {
        if(!primaries[i]->part_status){
            partition = primaries[i];
            return true;
        }/*else{
            cout<<"Partición"<<i+1<<": "<<primaries[i]->part_type<<endl;
        }*/
    }
    return false;
}

bool Fdisk::checkPartName(){
    int i, j;
    for ( i = 0; i < primaries.size(); i++)
    {
        if(primaries[i]->part_status){
            if(primaries[i]->part_name==name){
                return false;
            }
        }
    }
    for ( i = 0; i < logics.size(); i++)
    {
        if(logics[i].part_name==name){
            return false;
        }
    }
    
    return true;
}