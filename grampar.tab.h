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

#ifndef YY_YY_GRAMPAR_TAB_H_INCLUDED
# define YY_YY_GRAMPAR_TAB_H_INCLUDED
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
    TOK_INTEGER = 258,             /* TOK_INTEGER  */
    TOK_NAME = 259,                /* TOK_NAME  */
    TOK_STRING = 260,              /* TOK_STRING  */
    TOK_LIT_CODE = 261,            /* TOK_LIT_CODE  */
    TOK_LBRACE = 262,              /* "{"  */
    TOK_RBRACE = 263,              /* "}"  */
    TOK_COLON = 264,               /* ":"  */
    TOK_SEMICOLON = 265,           /* ";"  */
    TOK_ARROW = 266,               /* "->"  */
    TOK_LPAREN = 267,              /* "("  */
    TOK_RPAREN = 268,              /* ")"  */
    TOK_COMMA = 269,               /* ","  */
    TOK_TERMINALS = 270,           /* "terminals"  */
    TOK_TOKEN = 271,               /* "token"  */
    TOK_NONTERM = 272,             /* "nonterm"  */
    TOK_FUN = 273,                 /* "fun"  */
    TOK_VERBATIM = 274,            /* "verbatim"  */
    TOK_IMPL_VERBATIM = 275,       /* "impl_verbatim"  */
    TOK_PRECEDENCE = 276,          /* "precedence"  */
    TOK_PRECEDENCE_PREFER_SHIFT = 277, /* "precedence_prefer_shift"  */
    TOK_OPTION = 278,              /* "option"  */
    TOK_EXPECT = 279,              /* "expect"  */
    TOK_CONTEXT_CLASS = 280,       /* "context_class"  */
    TOK_SUBSETS = 281,             /* "subsets"  */
    TOK_DELETE = 282,              /* "delete"  */
    TOK_REPLACE = 283,             /* "replace"  */
    TOK_FORBID_NEXT = 284          /* "forbid_next"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 114 "grampar.y"

  int num;
  LocString *str;
  SourceLoc loc;

  ASTList<TopForm> *topFormList;
  TopForm *topForm;

  ASTList<TermDecl> *termDecls;
  TermDecl *termDecl;
  ASTList<TermType> *termTypes;
  TermType *termType;
  ASTList<PrecSpec> *precSpecs;

  ASTList<SpecFunc> *specFuncs;
  SpecFunc *specFunc;
  ASTList<LocString> *stringList;

  ASTList<ProdDecl> *prodDecls;
  ProdDecl *prodDecl;
  ASTList<RHSElt> *rhsList;
  RHSElt *rhsElt;

#line 117 "grampar.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (ParseParams *parseParam);


#endif /* !YY_YY_GRAMPAR_TAB_H_INCLUDED  */
