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
    PATH = 262,                    /* PATH  */
    MB = 263,                      /* MB  */
    KB = 264,                      /* KB  */
    B = 265,                       /* B  */
    UNIT = 266,                    /* UNIT  */
    FFIT = 267,                    /* FFIT  */
    BFIT = 268,                    /* BFIT  */
    WFIT = 269,                    /* WFIT  */
    FIT = 270,                     /* FIT  */
    IGUAL = 271,                   /* IGUAL  */
    SIZE = 272,                    /* SIZE  */
    NAME = 273,                    /* NAME  */
    ADD = 274,                     /* ADD  */
    DELET = 275,                   /* DELET  */
    TYPE = 276,                    /* TYPE  */
    FULL = 277,                    /* FULL  */
    FAST = 278,                    /* FAST  */
    MBR = 279,                     /* MBR  */
    DISK = 280,                    /* DISK  */
    PRIMARY = 281,                 /* PRIMARY  */
    EXTENDED = 282,                /* EXTENDED  */
    LOGIC = 283,                   /* LOGIC  */
    CADENA = 284,                  /* CADENA  */
    ID = 285,                      /* ID  */
    REP = 286,                     /* REP  */
    EXEC = 287,                    /* EXEC  */
    MOUNT = 288,                   /* MOUNT  */
    UMOUNT = 289,                  /* UMOUNT  */
    NUM = 290,                     /* NUM  */
    PAUSE = 291,                   /* PAUSE  */
    COMMENT = 292,                 /* COMMENT  */
    SEPARATOR = 293,               /* SEPARATOR  */
    PID = 294,                     /* PID  */
    ROOT = 295                     /* ROOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "analizador/Parser.y"

    char* text;
    int value;
    PARAMETER* param;
    std::vector<PARAMETER*>* params;
    PARAM_TYPE pt;

#line 112 "analizador/Parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (COMMAND *command);

#endif /* !YY_YY_ANALIZADOR_PARSER_H_INCLUDED  */
