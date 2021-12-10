%{
    #include <iostream>
    #include <vector>
    #include <string.h>
    #include <string>
    #include "../headers/Structs.h"
    #include "Parser.h"
    using std::string;
%}

%option case-insensitive
%option outfile="analizador/Lexer.cpp" header-file="analizador/Lexer.h"
%option noyywrap

%%
[ \r\n\t]*      { continue; /* Ignoramos espacios. */ }
#[^\n]*        { continue; /* Ignoramos comentarios. */ }

"rmdisk"        { yylval.text = strdup(yytext); return RMDSK; }
"mkdisk"        { yylval.text = strdup(yytext); return MKDSK;}
"fdisk"         { yylval.text = strdup(yytext); return FDSK; }

"="             {yylval.text;return IGUAL;}
"-"             {return DDASH;}
"~"             {return DDASHO;}
":"             {return DDOSPT;}

"exec"          {return EXEC;}
"size"          {return SIZE;}
"path"          {return PATH;}
"type"          {return TYPE;}
"delete"        {return DELET;}
"name"          {return NAME;}
"add"           {return ADD;}
"rep"           {return REP;}
"mount"         {return MOUNT;}
"umount"        {return MOUNT;}
"unit"          {return UNIT;}
"fit"           {return FIT;}

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


[0-9]+                                                                      {yylval.value = atoi(yytext); return NUM;} 
[A-Za-z0-9_]([A-Za-z0-9_ ])*[A-Za-z0-9_]                                    {yylval.text = strdup(yytext); return ID;}
["][^"]*["]                                                                 {strncpy(yylval.text, &yytext[1], strlen(yytext)-2); return CADENA;}
((".")*("/"))?([A-Za-z0-9_ ])+("/"([A-Za-z0-9_ ])+)*("."([a-zA-Z0-9])+)     {yylval.text = strdup(yytext); return RUTA;}
.                                                                           {std::cout<<"Error Lexico: "<< yytext<<std::endl;}
%%
