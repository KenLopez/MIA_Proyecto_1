#include "../headers/exec.h"

Exec::Exec(){
    path = "";
}

void Exec::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
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
    ifstream file(path.c_str());
    if(file.good()){
        string data;
        int i;
        while (getline (file, data)) {
            commands.push_back(data);
        }
        file.close();
            cout<<commands[0]<<endl;
            parse(commands[0].c_str());
    }else{
        cout << "ERROR EXEC: El archivo "<<getName(path)<<" no fue encontrado en la ruta especificada."<<endl;
    }
}