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
                cout<<"\033[91mERROR RMDISK: Parámetro path ya fue definido.\033[0m"<<endl;
                return;
            }else if(p->text==""){
                cout<<"\033[91mERROR RMDISK: Ruta no válida.\033[0m"<<endl;
                return;
            }
            path = p->text;
        }else{
            cout<<"\033[91mERROR RMDISK: Comando mkdisk posee parámetros incorrectos.\033[0m"<<endl;
            return;
        }
    }
    if(path==""){
        cout<<"\033[91mERROR RMDISK: Comando mkdisk no posee parámetros obligatorios (path).\033[0m"<<endl;
        return;
    }
    if(FILE *file = fopen(path.c_str(), "r")){ 
        fclose(file);
        if(remove(path.c_str())!=0){
            cout << "\033[91mERROR RMDISK: El disco "<<path<<" no pudo ser eliminado en la ruta "<<path<<".\033[0m"<<endl;    
        }else{
            cout << "\033[92mEl disco: "<<path<<", fue eliminado exitosamente.\033[0m"<<endl;
        }
    }else { 
        cout << "\033[91mERROR RMDISK: El disco "<<getName(path)<<" no fue encontrado en la ruta "<<path<<".\033[0m"<<endl;
    }
}
