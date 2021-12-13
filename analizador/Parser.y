%{

#include <iostream>
#include "../headers/Structs.h"
#include <vector>
#include <stdio.h>
#include "Parser.h"
#include "Lexer.h"


void yyerror(COMMAND *command, const char *msg) { return; }

%}

%output  "analizador/Parser.cpp"
%defines "analizador/Parser.h"

%parse-param { COMMAND *command }

%token <text>MKDSK
%token <text>RMDSK
%token <text>FDSK
%token <text>RUTA
%token <text>PATH
%token <text>MB
%token <text>KB
%token <text>B
%token <text>UNIT
%token <text>FFIT
%token <text>BFIT
%token <text>WFIT
%token <text>FIT
%token <text>IGUAL
%token <text>SIZE
%token <text>NAME
%token <text>ADD
%token <text>DELET
%token <text>TYPE
%token <text>FULL
%token <text>FAST
%token <text>MBR
%token <text>DISK
%token <text>PRIMARY
%token <text>EXTENDED
%token <text>LOGIC
%token <text>CADENA
%token <text>ID
%token <text>REP
%token <text>EXEC
%token <text>MOUNT
%token <text>UMOUNT
%token <value>NUM
%token <value>PAUSE
%token <text>COMMENT
%token <text>SEPARATOR

%type <params>parameters
%type <param>parameter
%type <pt>fit_opt
%type <pt>unit_size
%type <pt>part_type
%type <pt>del_type
%type <pt>rep_type
%type <text>path_string
%type <text>name_string


%start input

%union{
    char* text;
    int value;
    PARAMETER* param;
    std::vector<PARAMETER*>* params;
    PARAM_TYPE pt;
}

%%
    input
        :MKDSK parameters 
        { 
            command->name = cCREATE_DISK;
            command->parameters = $2;
        }
        |RMDSK parameters
        {
            command->name = cRMDISK;
            command->parameters = $2;
        }
        |FDSK parameters
        {
            command->name = cFDISK;
            command->parameters = $2;   
        }
        |REP parameters
        {
            command->name = cREP;
            command->parameters = $2;
        }
        |EXEC parameters
        {
            command->name = cEXEC;
            command->parameters = $2;
        }
        |MOUNT parameters
        {
            command->name = cMOUNT;
            command->parameters = $2;
        }
        |UMOUNT parameters
        {
            command->name = cUMOUNT;
            command->parameters = $2;
        }
        |PAUSE
        {
            command->name = cPAUSE;
        }
        |COMMENT
        {
            command->name = cCOMMENT;
        }
        ;
    
    parameters
        :parameters parameter   
        { 
            $1->push_back($2); 
            $$ = $1; 
        }
        |parameter              
        { 
            std::vector<PARAMETER*>* v = new std::vector<PARAMETER*>();
            v->push_back($1); 
            $$ = v; 
        }
        ;
    
    parameter
        :PATH separator path_string           { $$ = createParam(pPATH, $3, 0, tNONE); }
        |UNIT separator unit_size             { $$ = createParam(pUNIT, NULL, 0, $3); }
        |FIT separator fit_opt                { $$ = createParam(pFIT, NULL, 0, $3); }
        |SIZE separator NUM                   { $$ = createParam(pSIZE, NULL, $3, tNONE); }
        |TYPE separator part_type             { $$ = createParam(pTYPE, NULL, 0, $3); }
        |ADD separator NUM                    { $$ = createParam(pADD, NULL, $3, tNONE); }
        |DELET separator del_type             { $$ = createParam(pDELETE, NULL, 0, $3); }
        |NAME separator rep_type              { $$ = createParam(pNAME, NULL, 0, $3); }
        |NAME separator name_string           { $$ = createParam(pNAME, $3, 0, tNONE); }
        ;

    separator
        : SEPARATOR
        | IGUAL
        ;
    
    rep_type
        :MBR    { $$ = tMBR; }
        |DISK   { $$ = tDISK; }
        ;

    name_string
        :CADENA { $$ = $1; }
        |ID     { $$ = $1; }
        ;

    path_string
        :RUTA   { $$ = $1; }
        |CADENA { $$ = $1; }
        ;

    unit_size
        :KB { $$ = tKB; }
        |MB { $$ = tMB; }
        |B  { $$ = tB; }
        ;
    
    fit_opt
        :FFIT { $$ = tFF; }
        |WFIT { $$ = tWF; }
        |BFIT { $$ = tBF; }
        ;

    part_type
        :LOGIC      { $$ = tLOGIC; }
        |EXTENDED   { $$ = tEXTENDED; }
        |PRIMARY    { $$ = tPRIMARY; }
        ;
    
    del_type
        :FULL       { $$ = tFULL; }
        |FAST       { $$ = tFAST; }
        ;

%%
