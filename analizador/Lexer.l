%{
    #include <iostream>
    #include <vector>
    #include <string.h>
    #include "../headers/Structs.h"
    #include "Parser.h"
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

"exec"          {yylval.text = strdup(yytext); return EXEC;}
"size"          {yylval.text = strdup(yytext); return SIZE;}
"path"          {yylval.text = strdup(yytext); return PATH;}
"type"          {yylval.text = strdup(yytext); return TYPE;}
"delete"        {yylval.text = strdup(yytext); return DELET;}
"name"          {yylval.text = strdup(yytext); return NAME;}
"add"           {yylval.text = strdup(yytext); return ADD;}
"rep"           {yylval.text = strdup(yytext); return REP;}
"mount"           {yylval.text = strdup(yytext); return MOUNT;}
"umount"           {yylval.text = strdup(yytext); return MOUNT;}

"mbr"           {yylval.text = strdup(yytext); return MBR;}
"disk"           {yylval.text = strdup(yytext); return DISK;}
"fast"          {yylval.text = strdup(yytext); return FAST;}
"full"          {yylval.text = strdup(yytext); return FULL;}
"BF"            {yylval.text = strdup(yytext); return BFIT;}
"FF"            {yylval.text = strdup(yytext); return FFIT;}
"WF"            {yylval.text = strdup(yytext); return WFIT;}
"u"             {yylval.text = strdup(yytext); return UNIT;}
"f"             {yylval.text = strdup(yytext); return FIT;}
"b"             {yylval.text = strdup(yytext); return B;}
"k"             {yylval.text = strdup(yytext); return KB;}
"m"             {yylval.text = strdup(yytext); return MB;}
"P"             {yylval.text = strdup(yytext); return PRIMARY;}
"E"             {yylval.text = strdup(yytext); return EXTENDED;}
"L"             {yylval.text = strdup(yytext); return LOGIC;}


[0-9]+          {yylval.value = atoi(yytext); return NUM;} 
[A-Za-z0-9_]([A-Za-z0-9_ ])*[A-Za-z0-9_]  {yylval.text = strdup(yytext); return ID;}
["][^"]*["]   {strncpy(yylval.text, &yytext[1], strlen(yytext)-2); return CADENA;}
((".")*("/"))?([A-Za-z0-9_ ])+("/"([A-Za-z0-9_ ])+)*("."([a-zA-Z0-9])+) {yylval.text = strdup(yytext); return RUTA;}
.               {std::cout<<"Error Lexico: "<< yytext<<std::endl;}
%%
