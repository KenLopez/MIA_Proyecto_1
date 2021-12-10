#include "../headers/rep.h"

Rep::Rep(){
    name = tNONE;
}

void Rep::execute(vector<PARAMETER*>* params){
    int i;
    PARAMETER* p;
    for (i = 0; i < params->size(); i++)
    {
        p = (*params)[i];
        switch (p->name)
        {
        case pPATH:
            if(path!=""){
                cout<<"ERROR REP: Parámetro path ya fue definido."<<endl;
                return;
            }else if(p->text==""){
                cout<<"ERROR REP: Ruta no válida."<<endl;
                return;
            }
            path = p->text;
            break;
        
        case pNAME:
            if(name!=tNONE){
                cout<<"ERROR REP: Parámetro name ya fue definido."<<endl;
                return;
            }else if(p->param==tNONE){
                cout<<"ERROR REP: Nombre no válido."<<endl;
                return;
            }
            name = p->param;
            break;
        default:
            cout<<"ERROR REP: Comando rep posee parámetros incorrectos."<<endl;
            return;
        }
    }
    FILE* file;
    if(file = fopen(path.c_str(), "r+")){
        switch (name)
        {
        case tDISK:
            createDisk(file);
            break;

        default:
            break;
        }
    }else{
        cout << "ERROR FDISK: El disco "<<getName(path)<<" no fue encontrado en la ruta especificada."<<endl;
    }
}

void Rep::createDisk(FILE* file){
    int i;
    string name = getName(path);
    vector<EBR_STRUCT> logics;
    MBR_STRUCT mbr = getMBR(file);
    vector<PART_STRUCT*> primaries = getPrimaries(&mbr);
    PART_STRUCT* ext = getExtended(&mbr);
    string dot = "digraph G{\n\""+name+"\"[ shape=plaintext label=<\n<table cellpadding=\"5\" cellspacing=\"0\" border=\"0\">\n";
    dot += "<tr>\n<td colspan=\"2\" align=\"left\">MBR "+name+"</td>\n</tr>\n<tr>\n<td border=\"1\">Nombre</td>\n<td border=\"1\">Valor</td>\n</tr>\n";
    dot += "<tr>\n<td border=\"1\">mbr_tamano</td>\n<td border=\"1\">"+mbr.mbr_tamano;
    dot += "</td>\n</tr>\n";
    dot += "<tr>\n<td border=\"1\">mbr_disk_signature</td>\n<td border=\"1\">"+mbr.mbr_disk_signature;
    dot += "</td>\n</tr>\n";
    dot += "<tr>\n<td border=\"1\">mbr_fecha_creacion</td>\n<td border=\"1\">"+string(mbr.mbr_fecha_creacion);
    dot += "</td>\n</tr>\n";
    dot += "<tr>\n<td border=\"1\">disk_fit</td>\n<td border=\"1\">"+mbr.disk_fit;
    dot += "</td>\n</tr>\n";
    for ( i = 0; i < primaries.size(); i++)
    {
        dot += "<tr>\n<td border=\"1\" colspan=\"2\">mbr_partition"+(i+1);
        dot += "</td>\n</td>\n</tr>\n";
        dot += "<tr>\n<td border=\"1\">part_status</td>\n<td border=\"1\">"+primaries[i]->part_status;
        dot += "</td>\n</tr>\n";
        dot += "<tr>\n<td border=\"1\">part_type</td>\n<td border=\"1\">"+primaries[i]->part_type;
        dot += "</td>\n</tr>\n";
        dot += "<tr>\n<td border=\"1\">part_fit</td>\n<td border=\"1\">"+primaries[i]->part_fit;
        dot += "</td>\n</tr>\n";
        dot += "<tr>\n<td border=\"1\">part_start</td>\n<td border=\"1\">"+primaries[i]->part_start;
        dot += "</td>\n</tr>\n";
        dot += "<tr>\n<td border=\"1\">part_size</td>\n<td border=\"1\">"+primaries[i]->part_size;
        dot += "</td>\n</tr>\n";
        dot += "<tr>\n<td border=\"1\">part_name</td>\n<td border=\"1\">"+string(primaries[i]->part_name);
        dot += "</td>\n</tr>\n";
    }
    
    if(ext != NULL){
        logics = getLogics(file, ext->part_start);
        for ( i = 0; i < logics.size(); i++)
        {
            dot += string(primaries[i]->part_name)+"[ shape=plaintext label=<\n<table cellpadding=\"5\" cellspacing=\"0\" border=\"0\">\n";
            dot += dot += "<tr>\n<td colspan=\"2\" align=\"left\">MBR "+string(primaries[i]->part_name)+"</td>\n</tr>\n<tr>\n<td border=\"1\">Nombre</td>\n<td border=\"1\">Valor</td>\n</tr>\n";
        }
    }

}