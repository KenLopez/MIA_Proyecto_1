#include "../headers/exec.h"
#include "../headers/mount.h"
Exec::Exec(){
    path = "";
}

void Exec::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
    Mount mount;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        switch (p->name)
        {
        case pPATH:
            if(path!=""){
                cout<<"ERROR EXEC: Parámetro path ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR EXEC: Ruta no válida."<<endl;
                return;
            }
            path = p->text;
            break;
        default:
            cout<<"ERROR EXEC: Comando rep posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if(path==""){
        cout<<"ERROR EXEC: Comando exec no posee parámetros obligatorios (path)."<<endl;
        return;
    }
    ifstream file(path.c_str());
    if(file.good()){
        string data;
        int i;
        while (getline (file, data)) 
        {
            if(data != ""){
                commands.push_back(data);   
            }
        }
        file.close();
        COMMAND* command;
        for ( i = 0; i < commands.size(); i++)
        {
            cout<<commands[i]<<endl;
            command = parse(commands[i]);
            if(command!=NULL){
                execCmd(command, &mount);
            }
        }
    }else{
        cout << "ERROR EXEC: El archivo "<<getName(path)<<" no fue encontrado en la ruta especificada."<<endl;
    }
}