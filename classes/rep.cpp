#include "../headers/rep.h"
#include "../headers/mount.h"

Rep::Rep(){
    name = tNONE;
}

void Rep::execute(vector<PARAMETER*>* params){
    int i, j;
    PARAMETER* p;
    PART_MOUNT* partition;
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

        case pID:
            if(id!=""){
                cout<<"ERROR REP: Parámetro id ya fue definido."<<endl;
                return;
            }
            id = p->text;
            break;
        case pRUTA:
            break;
        default:
            cout<<"ERROR REP: Comando rep posee parámetros incorrectos."<<endl;
            return;
        }
    }
    if(path=="" || name==tNONE || id==""){
        cout<<"ERROR REP: Comando rep no posee parámetros obligatorios (path, id, name)."<<endl;
        return;
    }
    for ( i = 0; i < mount->mounted.size(); i++)
    {
        if(mount->mounted[i].status){
            for ( j = 0; j < mount->mounted[i].mounted.size(); j++){
                if(mount->mounted[i].mounted[j].status && mount->mounted[i].mounted[j].id == id){
                    disk = mount->mounted[i].disk;
                    partition = &(mount->mounted[i].mounted[j]);
                    break;
                }
            } 
        }   
    }
    if(partition == NULL){
        cout << "ERROR REP: La partición "<<id<<" no ha sido montada."<<endl;
        return;
    }
    FILE* file;
    if(file = fopen(disk.c_str(), "r+")){
        switch (name)
        {
        case tMBR:
            createMBR(file);
            break;
        case tDISK:
            createDisk(file);
            break;
        default:
            break;
        }
    }else{
        cout << "ERROR REP: El disco "<<getName(disk)<<" no fue encontrado en la ruta "<<disk<<"."<<endl;
        return;
    }
}

void Rep::createDisk(FILE* file){
    int i, pos;
    MBR_STRUCT mbr = getMBR(file);
    vector<PART_STRUCT*> primaries = getPrimaries(&mbr);
    PART_STRUCT* primary = getNextPrimary(primaries, sizeof(MBR_STRUCT));
    PART_STRUCT* ext = getExtended(&mbr);
    vector<EBR_STRUCT>logics;
    if(ext){
        logics = getLogics(file, ext->part_start);
    }
    string dot;
    dot += "digraph G{\nnode [shape=record];\nnode1 [label = \"{\n{";
    dot += "\nMBR\\nInicio: "+intToString(0)+"\\n"+"Final: "+intToString(sizeof(MBR_STRUCT))+"\\nPorcentaje: "+floatToString(((float)sizeof(MBR_STRUCT))/((float)mbr.mbr_tamano)*((float)100))+"%";
    pos = sizeof(MBR_STRUCT);
    for ( i = 0; i < primaries.size(); i++)
    {
        primary = getNextPrimary(primaries, primary->part_start+primary->part_size);
        if(primary==NULL){
            dot += dotFreeSpace(pos+1, mbr.mbr_tamano, mbr.mbr_tamano);
            break;
        }else if(primary->part_start>pos+1){
            dot += dotFreeSpace(pos+1, primary->part_start-1, mbr.mbr_tamano);
        }
        dot += dotPrimary(primary, mbr.mbr_tamano, logics);
        pos = primary->part_start+primary->part_size;
    }
    if(primary!=NULL && i==primaries.size()-1){
        dot+= dotFreeSpace(pos, mbr.mbr_tamano, mbr.mbr_tamano);
    }
    dot += "\n}\n}\"]\n}";
    fclose(file);
    string name = getNameExt(path);
    string ruta = "../reporte_Disk_"+name+".dot";
    string output = getDIR(path)+"/"+name;
    if(FILE *file2 = fopen(ruta.c_str(), "w")){
        fputs(dot.c_str(), file2);
        fclose(file2);
    }
    createDirs(getDIR(path).c_str());
    std::string syst = "dot -Tsvg "+ruta+" -o \"" + output + ".svg\"";
    cout<<syst<<endl;
    system(syst.c_str());
    cout<<"Se creo el reporte: "<<getName(output)<<" correctamente."<<endl;
}

void Rep::createMBR(FILE* file){
    int i;
    string n = getName(disk);
    vector<EBR_STRUCT> logics;
    MBR_STRUCT mbr = getMBR(file);
    vector<PART_STRUCT*> primaries = getPrimaries(&mbr);
    PART_STRUCT* ext = getExtended(&mbr);
    string dot;
    dot += "digraph G{\n\""+n+"\"[ shape=plaintext label=<\n<table cellpadding=\"5\" cellspacing=\"0\" border=\"0\">\n<tr><td colspan=\"2\" align=\"left\">MBR "+n;
    dot += "</td></tr>\n<tr><td border=\"1\">Nombre</td>\n<td border=\"1\">Valor</td></tr>\n";
    dot += "<tr><td border=\"1\">mbr_tamaño</td><td border=\"1\">"+intToString(mbr.mbr_tamano)+"</td></tr>\n";
    dot += "<tr><td border=\"1\">mbr_fecha_creacion</td>\n<td border=\"1\">"+string(mbr.mbr_fecha_creacion)+"</td></tr>\n";
    dot += "<tr><td border=\"1\">mbr_disk_signature</td>\n<td border=\"1\">"+intToString(mbr.mbr_disk_signature)+"</td></tr>\n";
    dot += "<tr><td border=\"1\">disk_fit</td>\n<td border=\"1\">"+charToString(mbr.disk_fit)+"</td></tr>\n";
    for ( i = 0; i < primaries.size(); i++)
    {
        dot += "<tr><td border=\"1\" colspan=\"2\">mbr_partition"+intToString(i+1)+"</td></tr>\n";
        dot += "<tr><td border=\"1\">part_status</td><td border=\"1\">"+intToString(primaries[i]->part_status)+"</td></tr>\n";
        dot += "<tr><td border=\"1\">part_type</td><td border=\"1\">"+charToString(primaries[i]->part_type)+"</td></tr>\n";
        dot += "<tr><td border=\"1\">part_fit</td><td border=\"1\">"+charToString(primaries[i]->part_fit)+"</td></tr>\n";
        dot += "<tr><td border=\"1\">part_start</td><td border=\"1\">"+intToString(primaries[i]->part_start)+"</td></tr>\n";
        dot += "<tr><td border=\"1\">part_size</td><td border=\"1\">"+intToString(primaries[i]->part_size)+"</td></tr>\n";
        dot += "<tr><td border=\"1\">part_name</td><td border=\"1\">"+string(primaries[i]->part_name)+"</td></tr>\n";
    }

    dot += "</table>>]\n";
    
    if(ext != NULL){
        logics = getLogics(file, ext->part_start);
        for ( i = 0; i < logics.size(); i++)
        {
            if(!logics[i].part_status){
                continue;
            }
            dot += string(logics[i].part_name)+"[ shape=plaintext label=<\n<table cellpadding=\"5\" cellspacing=\"0\" border=\"0\">\n";
            dot += "<tr><td colspan=\"2\" align=\"left\">EBR "+intToString(i+1)+"</td></tr>\n<tr><td border=\"1\">Nombre</td><td border=\"1\">Valor</td></tr>\n";
            dot += "<tr><td border=\"1\">part_status</td><td border=\"1\">"+intToString(logics[i].part_status)+"</td></tr>\n";
            dot += "<tr><td border=\"1\">part_fit</td><td border=\"1\">"+charToString(logics[i].part_fit)+"</td></tr>\n";
            dot += "<tr><td border=\"1\">part_start</td><td border=\"1\">"+intToString(logics[i].part_start)+"</td></tr>\n";
            dot += "<tr><td border=\"1\">part_size</td><td border=\"1\">"+intToString(logics[i].part_size)+"</td></tr>\n";
            dot += "<tr><td border=\"1\">part_next</td><td border=\"1\">"+intToString(logics[i].part_next)+"</td></tr>\n";
            dot += "<tr><td border=\"1\">part_name</td><td border=\"1\">"+string(logics[i].part_name)+"</td></tr>\n";
            dot += "</table>>]\n";
        }
    }
    dot += "}";
    fclose(file);
    string name = getNameExt(path);
    string ruta = "../reporte_MBR_"+name+".dot";
    string output = getDIR(path)+"/"+name;
    if(FILE *file2 = fopen(ruta.c_str(), "w")){
        fputs(dot.c_str(), file2);
        fclose(file2);
    }
    createDirs(getDIR(path).c_str());
    std::string syst = "dot -Tsvg "+ruta+" -o \"" + output + ".svg\"";
    cout<<syst<<endl;
    system(syst.c_str());
    cout<<"Se creo el reporte: "<<getName(output)<<" correctamente."<<endl;
}