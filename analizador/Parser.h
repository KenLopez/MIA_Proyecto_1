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
    PATH = 263,                    /* PATH  */
    MB = 264,                      /* MB  */
    KB = 265,                      /* KB  */
    B = 266,                       /* B  */
    UNIT = 267,                    /* UNIT  */
    FFIT = 268,                    /* FFIT  */
    BFIT = 269,                    /* BFIT  */
    WFIT = 270,                    /* WFIT  */
    FIT = 271,                     /* FIT  */
    IGUAL = 272,                   /* IGUAL  */
    SIZE = 273,                    /* SIZE  */
    NAME = 274,                    /* NAME  */
    ADD = 275,                     /* ADD  */
    DELET = 276,                   /* DELET  */
    TYPE = 277,                    /* TYPE  */
    FULL = 278,                    /* FULL  */
    FAST = 279,                    /* FAST  */
    MBR = 280,                     /* MBR  */
    DISK = 281,                    /* DISK  */
    PRIMARY = 282,                 /* PRIMARY  */
    EXTENDED = 283,                /* EXTENDED  */
    LOGIC = 284,                   /* LOGIC  */
    CADENA = 285,                  /* CADENA  */
    ID = 286,                      /* ID  */
    REP = 287,                     /* REP  */
    EXEC = 288,                    /* EXEC  */
    MOUNT = 289,                   /* MOUNT  */
    UMOUNT = 290,                  /* UMOUNT  */
    NUM = 291                      /* NUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 69 "analizador/Parser.y"

    char* text;
    int value;
    PARAMETER* param;
    std::vector<PARAMETER*>* params;
    PARAM_TYPE pt;

#line 108 "analizador/Parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (COMMAND *command);

#endif /* !YY_YY_ANALIZADOR_PARSER_H_INCLUDED  */
