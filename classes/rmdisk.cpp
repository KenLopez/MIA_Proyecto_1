#include "../headers/rmdisk.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

Rmdisk::Rmdisk(){
    path = "";
}

void Rmdisk::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        if(p->name == pPATH){
            if(path!=""){
                cout<<"ERROR RMDISK: Parámetro path ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR RMDISK: Ruta no válida."<<endl;
                return;
            }
            path = p->text;
        }else{
            cout<<"ERROR RMDISK: Comando mkdisk posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if(path==""){
        cout<<"ERROR RMDISK: Comando mkdisk no posee parámetros obligatorios (path)."<<endl;
        return;
    }
    if(FILE *file = fopen(path.c_str(), "r")){ 
        fclose(file);
        if(remove(path.c_str())!=0){
            cout << "ERROR RMDISK: El disco "<<path<<" no pudo ser eliminado en la ruta "<<path<<"."<<endl;    
        }else{
            cout << "El disco: "<<path<<", fue eliminado exitosamente."<<endl;
        }
    }else { 
        cout << "ERROR RMDISK: El disco "<<getName(path)<<" no fue encontrado en la ruta "<<path<<"."<<endl;
    }
}
