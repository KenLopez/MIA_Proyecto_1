/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ANALIZADOR_PARSER_H_INCLUDED
# define YY_YY_ANALIZADOR_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    MKDSK = 258,                   /* MKDSK  */
    RMDSK = 259,                   /* RMDSK  */
    FDSK = 260,                    /* FDSK  */
    RUTA = 261,                    /* RUTA  */
    DDASH = 262,                   /* DDASH  */
    DDASHO = 263,                  /* DDASHO  */
    DDOSPT = 264,                  /* DDOSPT  */
    PATH = 265,                    /* PATH  */
    MB = 266,                      /* MB  */
    KB = 267,                      /* KB  */
    B = 268,                       /* B  */
    UNIT = 269,                    /* UNIT  */
    FFIT = 270,                    /* FFIT  */
    BFIT = 271,                    /* BFIT  */
    WFIT = 272,                    /* WFIT  */
    FIT = 273,                     /* FIT  */
    IGUAL = 274,                   /* IGUAL  */
    SIZE = 275,                    /* SIZE  */
    NAME = 276,                    /* NAME  */
    ADD = 277,                     /* ADD  */
    DELET = 278,                   /* DELET  */
    TYPE = 279,                    /* TYPE  */
    FULL = 280,                    /* FULL  */
    FAST = 281,                    /* FAST  */
    MBR = 282,                     /* MBR  */
    DISK = 283,                    /* DISK  */
    PRIMARY = 284,                 /* PRIMARY  */
    EXTENDED = 285,                /* EXTENDED  */
    LOGIC = 286,                   /* LOGIC  */
    CADENA = 287,                  /* CADENA  */
    ID = 288,                      /* ID  */
    REP = 289,                     /* REP  */
    EXEC = 290,                    /* EXEC  */
    MOUNT = 291,                   /* MOUNT  */
    UMOUNT = 292,                  /* UMOUNT  */
    NUM = 293                      /* NUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 71 "analizador/Parser.y"

    char* text;
    int value;
    PARAMETER* param;
    std::vector<PARAMETER*>* params;
    PARAM_TYPE pt;

#line 110 "analizador/Parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (COMMAND *command);

#endif /* !YY_YY_ANALIZADOR_PARSER_H_INCLUDED  */
