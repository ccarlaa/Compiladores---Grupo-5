/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_BUILD_Y_TAB_H_INCLUDED
# define YY_YY_BUILD_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 61 "parser/parser.y"

    #include "ast.h"

#line 53 "build/y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_ID = 258,                    /* T_ID  */
    T_STRING = 259,                /* T_STRING  */
    T_CHAR_LITERAL = 260,          /* T_CHAR_LITERAL  */
    T_NUMBER_FLOAT = 261,          /* T_NUMBER_FLOAT  */
    T_NUMBER_INT = 262,            /* T_NUMBER_INT  */
    T_INT = 263,                   /* T_INT  */
    T_FLOAT = 264,                 /* T_FLOAT  */
    T_CHAR = 265,                  /* T_CHAR  */
    T_VOID = 266,                  /* T_VOID  */
    T_IF = 267,                    /* T_IF  */
    T_ELSE = 268,                  /* T_ELSE  */
    T_WHILE = 269,                 /* T_WHILE  */
    T_FOR = 270,                   /* T_FOR  */
    T_RETURN = 271,                /* T_RETURN  */
    T_PRINTF = 272,                /* T_PRINTF  */
    T_SCANF = 273,                 /* T_SCANF  */
    T_SWITCH = 274,                /* T_SWITCH  */
    T_CASE = 275,                  /* T_CASE  */
    T_DEFAULT = 276,               /* T_DEFAULT  */
    T_BREAK = 277,                 /* T_BREAK  */
    T_CONTINUE = 278,              /* T_CONTINUE  */
    T_DO = 279,                    /* T_DO  */
    T_MOD = 280,                   /* T_MOD  */
    T_INC = 281,                   /* T_INC  */
    T_DEC = 282,                   /* T_DEC  */
    T_PLUS_ASSIGN = 283,           /* T_PLUS_ASSIGN  */
    T_MINUS_ASSIGN = 284,          /* T_MINUS_ASSIGN  */
    T_ARROW = 285,                 /* T_ARROW  */
    T_DOT = 286,                   /* T_DOT  */
    T_AMPERSAND = 287,             /* T_AMPERSAND  */
    T_BIT_OR = 288,                /* T_BIT_OR  */
    T_PLUS = 289,                  /* T_PLUS  */
    T_MINUS = 290,                 /* T_MINUS  */
    T_MULT = 291,                  /* T_MULT  */
    T_DIV = 292,                   /* T_DIV  */
    T_ASSIGN = 293,                /* T_ASSIGN  */
    T_EQ = 294,                    /* T_EQ  */
    T_NEQ = 295,                   /* T_NEQ  */
    T_LT = 296,                    /* T_LT  */
    T_GT = 297,                    /* T_GT  */
    T_LE = 298,                    /* T_LE  */
    T_GE = 299,                    /* T_GE  */
    T_AND = 300,                   /* T_AND  */
    T_OR = 301,                    /* T_OR  */
    T_NOT = 302,                   /* T_NOT  */
    T_LPAREN = 303,                /* T_LPAREN  */
    T_RPAREN = 304,                /* T_RPAREN  */
    T_LBRACE = 305,                /* T_LBRACE  */
    T_RBRACE = 306,                /* T_RBRACE  */
    T_SEMICOLON = 307,             /* T_SEMICOLON  */
    T_COMMA = 308,                 /* T_COMMA  */
    T_COLON = 309,                 /* T_COLON  */
    T_CONST = 310,                 /* T_CONST  */
    T_UNSIGNED = 311,              /* T_UNSIGNED  */
    T_PRINTF_ARGS = 312            /* T_PRINTF_ARGS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 65 "parser/parser.y"

    char *sval;
    int ival;
    float fval;
    ASTNode *ast;

#line 134 "build/y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_Y_TAB_H_INCLUDED  */
