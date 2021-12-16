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
                cout<<"\033[91mERROR EXEC: Parámetro path ya fue definido.\033[0m"<<endl;
                return;
            }else if(p->text==""){
                cout<<"\033[91mERROR EXEC: Ruta no válida.\033[0m"<<endl;
                return;
            }
            path = p->text;
            break;
        default:
            cout<<"\033[91mERROR EXEC: Comando rep posee parámetros incorrectos.\033[0m"<<endl;
            return;
        }
    }
    if(path==""){
        cout<<"\033[91mERROR EXEC: Comando exec no posee parámetros obligatorios (path).\033[0m"<<endl;
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
            command = parse(commands[i]);
            if(command!=NULL){
                if(command->name == cCOMMENT){
                    cout<<"\033[95m";
                }else{
                    cout<<"\033[96m";
                }
                cout<<commands[i]<<"\033[0m"<<endl;
                execCmd(command, &mount);
            }
        }
    }else{
        cout << "\033[91mERROR EXEC: El archivo "<<getName(path)<<" no fue encontrado en la ruta especificada.\033[0m"<<endl;
    }
}