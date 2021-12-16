#include "../headers/utilities.h"
#include "../headers/mount.h"

vector<string> split(string delim, string str){
    int pos;
    int i = 0;
    int size = 1; 
    string word;
    string s = str;

    while (( pos = s.find (delim)) != string::npos)
    {
        s.erase(0, pos + delim.length()); 
        size++;
    }
    pos = 0;
    vector<string> splitted (size);
    
    for ( i = 0; i < size; i++)
    {
        pos = str.find(delim);
        word = str.substr(0, pos);  
        splitted[i] = word;  
        str.erase(0, pos + delim.length()); 
    }

    return splitted;

}

void createDirs(string dirs){
    int i;
    vector<string> d = split("/", dirs);
    string final = "/";
    for (i = 1; i < d.size(); i++)
    {
        final+=d[i];
        mkdir(final.c_str(), 0777)==-1;
        final+="/";
    }
    
}

string getDIR(string f_path){
    vector<string> v = split("/", f_path);
    string p;
    int i;
    for ( i = 0; i < v.size(); i++)
    {
        if(i!=v.size()-1){
            p+=v[i];
            if(i!=v.size()-2){
                p+="/";
            }
        }
    }
    return p;
}

string getName(string f_path){
    vector<string> v = split("/", f_path);
    return v[v.size()-1];
}

string getNameExt(string f_path){
    vector<string> v = split("/", f_path);
    vector<string> v2 = split(".", v[v.size()-1]);
    return v2[0];
}

MBR_STRUCT getMBR(FILE* file){
    MBR_STRUCT disk;
    rewind(file);
    fread(&disk, sizeof(MBR_STRUCT), 1, file);
    return disk;
}

char paramToChar(PARAM_TYPE t){
    switch (t)
    {
    case tFF:
        return 'F';
    case tWF:
        return 'W';
    case tBF:
        return 'B';
    case tMB:
        return 'M';
    case tKB:
        return 'K';
    case tB:
        return 'b';
    case tPRIMARY:
        return 'P';
    case tEXTENDED:
        return 'E';
    case tLOGIC:
        return 'L';
    default:
        return '\0';
    }
}

string intToLetter(int num){
    string letter;
    char symbol = (char)('a' + num);
    letter.push_back(symbol);
    return letter;
}

PARAM_TYPE charToParam(char t){
    switch (t)
    {
    case 'F':
        return tFF;
    case 'W':
        return tWF;
    case 'B':
        return tBF;
    case 'M':
        return tMB;
    case 'K':
        return tKB;
    case 'b':
        return tB;
    case 'P':
        return tPRIMARY;
    case 'E':
        return tEXTENDED;
    case 'L':
        return tLOGIC;
    default:
        return tNONE;
    }
}

DISK_SPACE newSpace(int i, int s){
    DISK_SPACE n;
    n.ini = i;
    n.size = s;
    return n;
}

vector<PART_STRUCT*> getPrimaries(MBR_STRUCT* mbr){
    vector<PART_STRUCT*> primaries;
    primaries.push_back(&(mbr->mbr_partition_1));
    primaries.push_back(&(mbr->mbr_partition_2));
    primaries.push_back(&(mbr->mbr_partition_3));
    primaries.push_back(&(mbr->mbr_partition_4));
    /*int i;
    for ( i = 0; i < primaries.size(); i++)
    {
        cout<<primaries[i]->part_name<<": "<<primaries[i]->part_start<<", "<<primaries[i]->part_size<<"B"<<", "<<primaries[i]->part_fit<<"F";
        if(primaries[i]->part_status){
            cout<<" ACTIVA"<<endl;
        }else{
            cout<<" NO ACTIVA"<<endl;
        }
    }*/
    return primaries;
}

PART_STRUCT* getExtended(MBR_STRUCT* mbr){
    if(mbr->mbr_partition_1.part_status && mbr->mbr_partition_1.part_type == 'E'){
        return &mbr->mbr_partition_1;
    }
    if(mbr->mbr_partition_2.part_status && mbr->mbr_partition_2.part_type == 'E'){
        return &mbr->mbr_partition_2;
    }
    if(mbr->mbr_partition_3.part_status && mbr->mbr_partition_3.part_type == 'E'){
        return &mbr->mbr_partition_3;
    }
    if(mbr->mbr_partition_4.part_status && mbr->mbr_partition_4.part_type == 'E'){
        return &mbr->mbr_partition_4;
    }
    return NULL; 
}

vector<EBR_STRUCT> getLogics(FILE* file, int ini){
    vector<EBR_STRUCT> ebrs;
    EBR_STRUCT ebr;
    fseek(file, ini, SEEK_SET);
    do{
        fread(&ebr, sizeof(EBR_STRUCT), 1, file);
        if(ebr.part_status){
            ebrs.push_back(ebr);
        }
        if(ebr.part_next != -1){
            fseek(file, ebr.part_next, SEEK_SET);
        }
    }while(ebr.part_next != -1);
    /*int i;
    cout<<"CANTIDAD DE LOGICAS: "<<ebrs.size()<<endl;
    for ( i = 0; i < ebrs.size(); i++)
    {
        if(ebrs[i].part_status){
            cout<<ebrs[i].part_name<<": "<<ebrs[i].part_start<<", "<<ebrs[i].part_size<<"B"<<endl;
        }
    }*/
    return ebrs;
}

int convertBytes(int size, PARAM_TYPE unit){
    switch (unit)
    {
        case tMB:
            size = size * 1000;
        case tKB:
            size = size*1000;
        default:
            break;
    }
    return size;
}

string getCMD(int argc, char* argv[]){
    string args;
    args = argv[1];
    for (int i = 2; i < argc; i++){
        args = args + " " + argv[i];     
    }
    return args;
}

void execCmd(COMMAND* command, Mount* mount){
    Mkdisk *mkdsk;
    Rmdisk *rmdsk; 
    Fdisk *fdsk; 
    Rep *rep; 
    Exec *exec;

    switch (command->name)
    {
    case cCREATE_DISK:
        mkdsk = new Mkdisk();
        mkdsk->execute(command->parameters);
        break;
    case cRMDISK:
        rmdsk = new Rmdisk();
        rmdsk->execute(command->parameters);
        break;
    case cFDISK:
        fdsk = new Fdisk();
        fdsk->execute(command->parameters);
        break;
    case cREP:
        rep = new Rep();
        rep->mount = mount;
        rep->execute(command->parameters);
        break;
    case cEXEC:
        exec = new Exec();
        exec->execute(command->parameters);
        break;
    case cPAUSE:
        cout<<"Ejecución detenida. Presione cualquier tecla para continuar...";
        getchar();
        cout<<endl;
        break;
    case cMOUNT:
        mount->mountNew(command->parameters);
        break;
    case cUMOUNT:
        mount->unmount(command->parameters);
        break;
    default:
        break;
    }
}

string intToString(int num){
    std::stringstream ss;
    string str;
    ss<<num;
    ss>>str;
    return str;
}

string charToString(char ch){
    std::stringstream ss;
    string str;
    ss<<ch;
    ss>>str;
    return str;
}

string floatToString(float num){
    std::stringstream ss;
    string str;
    ss<<num;
    ss>>str;
    return str;
}

PART_STRUCT* getNextPrimary(vector<PART_STRUCT*> primaries, int pos){
    int i;
    PART_STRUCT* next = NULL;
    for ( i = 0; i < primaries.size(); i++)
    {
        if(primaries[i]->part_status){
            if(next == NULL){
                if(primaries[i]->part_start>=pos){
                    next = primaries[i];
                }
            }else{
                if(next->part_start>primaries[i]->part_start && primaries[i]->part_start>=pos){
                    next = primaries[i];
                }
            }
        }
    }
    return next;
}

COMMAND* parse(string cmd)
{   
    COMMAND* command = new COMMAND();

    char* entrada = (char*)cmd.c_str();

    YY_BUFFER_STATE state = yy_scan_string(entrada);
    if (yyparse(command) || !command->name) {
        cout<<"ERROR: El comando: "<<cmd<<", no pudo ser ejecutado."<<endl;
        return NULL;
    }
    return command;
}

string dotFreeSpace(int ini, int end, int size){
    return "\n|ESPACIO LIBRE\\nInicio: "+intToString(ini)+"\\nFinal: "+intToString(end)+"\\nPorcentaje: "+floatToString(((float)(end-ini))/((float)size)*((float)100))+"%";
}

string dotPrimary(PART_STRUCT* part,  int size, vector<EBR_STRUCT>logics){
    int i;
    int pos = part->part_start;
    string str;
    string type;
    str+= "\\n"+string(part->part_name)+"\\nInicio: "+intToString(part->part_start)+"\\nFinal: "+intToString(part->part_start+part->part_size);
    if(part->part_type == 'E'){
        str = "\n|{\nEXTENDIDA"+str;
        str += "\n|{\n";
        if(logics.size()==0){
            str+=dotFreeSpace(part->part_start, part->part_start+part->part_size, size);
        }
        for ( i = 0; i < logics.size(); i++)
        {
            if(logics[i].part_start > pos+1){
                str+=dotFreeSpace(pos+1, logics[i].part_start-1, size);
            }
            if(i!=0){
                str+="\n|";
            }else{
                str+="\n";
            }
            str+="EBR\\nInicio: "+intToString(logics[i].part_start)+"\\n"+"Final: "+intToString(logics[i].part_start+sizeof(EBR_STRUCT));
            str+="\\nPorcentaje: "+floatToString(((float)sizeof(EBR_STRUCT))/((float)size)*((float)100))+"%";
            str+=dotLogic(&(logics[i]), size);
            pos = logics[i].part_start+logics[i].part_size;
        }
        if(pos<(part->part_start+part->part_size)){
            str+=dotFreeSpace(pos, part->part_start+part->part_size, size);
        }
        str+="\n}\n}";
    }else{
        str = "\n|PRIMARIA"+str+"\\nPorcentaje: "+floatToString(((float)part->part_size)/((float)size)*((float)100))+"%";
    }
    return str;
}

string dotLogic(EBR_STRUCT* part, int size){
    string str = "\n|LOGICA\\n"+string(part->part_name)+"\\nInicio: "+intToString(part->part_start+sizeof(EBR_STRUCT)+1)+"\\nFinal: ";
    str += intToString(part->part_start+part->part_size)+"\\nPorcentaje: "+floatToString(((float)part->part_size)/((float)size)*((float)100))+"%";
    return str;
}

