#include "../headers/utilities.h"

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

void execCmd(COMMAND* command){
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
        /*rep = new Rep();
        rep->execute(command.parameters);*/
        cout<<"REP"<<endl;
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
    default:
        break;
    }
}

COMMAND* parse(string cmd)
{   
    COMMAND* command = new COMMAND();

    char* entrada = (char*)cmd.c_str();

    YY_BUFFER_STATE state = yy_scan_string(entrada);
    if (yyparse(command)) {
        cout<<"ERROR: El comando: "<<cmd<<", no pudo ser ejecutado."<<endl;
        return NULL;
    }
    return command;
}