%option case-insensitive
%{
    #include <iostream>
    #include <vector>
    #include <string.h>
    #include <string>
    #include "../headers/Structs.h"
    #include "Parser.h"
    using std::string;
%}

%option outfile="analizador/Lexer.cpp" header-file="analizador/Lexer.h"
%option noyywrap nounput batch noinput


BLANCOS     [ \r\t\n]+
COMENTARIOS "#".* 
GUION       "-"|"–"
COMILLA     [\"]|"“"|"”"
ENTERO      {GUION}?[0-9]+
LETRA       [a-zA-Z]
CARS        ({LETRA}|{ENTERO}|"_"|"-"|"–")
ID          ({CARS}+)
IDC         ({COMILLA}{ID}{COMILLA})
RUTA        ([\/]({CARS}|" ")+)*([\/]({CARS}|" ")+"."{CARS}+)
CADENA      ({COMILLA}{RUTA}{COMILLA})

%%
{BLANCOS}       { continue; /* Ignoramos espacios. */ }
{COMENTARIOS}   { return COMMENT; /* Ignoramos comentarios. */ }

"rmdisk"        { return RMDSK; }
"mkdisk"        { return MKDSK; }
"fdisk"         { return FDSK; }
"pause"         { return PAUSE; }
"exec"          {return EXEC;}
"mount"         {return MOUNT;}
"unmount"       {return UMOUNT;}
"rep"           {return REP;}

"="             {return IGUAL;}
"~:~"           {return SEPARATOR;}

{GUION}"size"          {return SIZE;}
{GUION}"path"          {return PATH;}
{GUION}"type"          {return TYPE;}
{GUION}"delete"        {return DELET;}
{GUION}"name"          {return NAME;}
{GUION}"add"           {return ADD;}
{GUION}"unit"          {return UNIT;}
{GUION}"fit"           {return FIT;}
{GUION}"id"            {return PID;}
{GUION}"ruta"          {return ROOT;}

"mbr"           {return MBR;}
"disk"          {return DISK;}
"fast"          {return FAST;}
"full"          {return FULL;}

"BF"            {return BFIT;}
"FF"            {return FFIT;}
"WF"            {return WFIT;}
"b"             {return B;}
"k"             {return KB;}
"m"             {return MB;}
"P"             {return PRIMARY;}
"E"             {return EXTENDED;}
"L"             {return LOGIC;}


{ENTERO}        {yylval.value = atoi(yytext); return NUM;} 
{ID}            {yylval.text = strdup(yytext); return ID;}
{IDC}           {yylval.text = strndup(&yytext[1], strlen(yytext)-2); return ID;}
{RUTA}          {yylval.text = strdup(yytext); return RUTA;}
{CADENA}        {yylval.text = strndup(&yytext[1], strlen(yytext)-2); return CADENA;}
.               {std::cout<<"ERROR: El caracter "<< yytext<<" no pudo ser reconocido."<<std::endl;}
%%
