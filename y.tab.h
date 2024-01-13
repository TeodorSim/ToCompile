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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    CONSTANT = 258,                /* CONSTANT  */
    EVAL = 259,                    /* EVAL  */
    STRUCTURE = 260,               /* STRUCTURE  */
    CLASS = 261,                   /* CLASS  */
    TYPEOF = 262,                  /* TYPEOF  */
    TREQQ = 263,                   /* TREQQ  */
    CLASS_TYP = 264,               /* CLASS_TYP  */
    BGIN = 265,                    /* BGIN  */
    END = 266,                     /* END  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    FOR = 270,                     /* FOR  */
    DO = 271,                      /* DO  */
    RETURN = 272,                  /* RETURN  */
    ASSIGN = 273,                  /* ASSIGN  */
    LESS = 274,                    /* LESS  */
    LESSEQ = 275,                  /* LESSEQ  */
    GRT = 276,                     /* GRT  */
    GRTEQ = 277,                   /* GRTEQ  */
    EQ = 278,                      /* EQ  */
    NOT = 279,                     /* NOT  */
    AND = 280,                     /* AND  */
    OR = 281,                      /* OR  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    DIV = 284,                     /* DIV  */
    MULTIP = 285,                  /* MULTIP  */
    MOD = 286,                     /* MOD  */
    LBRACES = 287,                 /* LBRACES  */
    RBRACES = 288,                 /* RBRACES  */
    LPAR = 289,                    /* LPAR  */
    RPAR = 290,                    /* RPAR  */
    LBRACKET = 291,                /* LBRACKET  */
    RBRACKET = 292,                /* RBRACKET  */
    POINT = 293,                   /* POINT  */
    SINGLE_QUOTES = 294,           /* SINGLE_QUOTES  */
    COMMA = 295,                   /* COMMA  */
    SEMI_COLLON = 296,             /* SEMI_COLLON  */
    PRINT = 297,                   /* PRINT  */
    PRIVAT = 298,                  /* PRIVAT  */
    PUBLIC = 299,                  /* PUBLIC  */
    PROTECTED = 300,               /* PROTECTED  */
    BOOL_VAL = 301,                /* BOOL_VAL  */
    INT_NUM = 302,                 /* INT_NUM  */
    REAL_NUM = 303,                /* REAL_NUM  */
    CHAR_VAL = 304,                /* CHAR_VAL  */
    STRING_VAL = 305,              /* STRING_VAL  */
    ARRAY_IDENTIF = 306,           /* ARRAY_IDENTIF  */
    VOID = 307,                    /* VOID  */
    INT = 308,                     /* INT  */
    FLOAT = 309,                   /* FLOAT  */
    CHAR = 310,                    /* CHAR  */
    STRING = 311,                  /* STRING  */
    BOOL = 312,                    /* BOOL  */
    IDENTIF = 313                  /* IDENTIF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CONSTANT 258
#define EVAL 259
#define STRUCTURE 260
#define CLASS 261
#define TYPEOF 262
#define TREQQ 263
#define CLASS_TYP 264
#define BGIN 265
#define END 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define FOR 270
#define DO 271
#define RETURN 272
#define ASSIGN 273
#define LESS 274
#define LESSEQ 275
#define GRT 276
#define GRTEQ 277
#define EQ 278
#define NOT 279
#define AND 280
#define OR 281
#define PLUS 282
#define MINUS 283
#define DIV 284
#define MULTIP 285
#define MOD 286
#define LBRACES 287
#define RBRACES 288
#define LPAR 289
#define RPAR 290
#define LBRACKET 291
#define RBRACKET 292
#define POINT 293
#define SINGLE_QUOTES 294
#define COMMA 295
#define SEMI_COLLON 296
#define PRINT 297
#define PRIVAT 298
#define PUBLIC 299
#define PROTECTED 300
#define BOOL_VAL 301
#define INT_NUM 302
#define REAL_NUM 303
#define CHAR_VAL 304
#define STRING_VAL 305
#define ARRAY_IDENTIF 306
#define VOID 307
#define INT 308
#define FLOAT 309
#define CHAR 310
#define STRING 311
#define BOOL 312
#define IDENTIF 313

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 305 "fis.y"

  int intTyp;
  float floatTyp;
  char* charTyp;
  char* stringTyp;
  char* dataTyp; // IDENTIF or INT/VOID/FLOAT/CHAR/STRING/BOOL
  char* arrayTyp;
  char* tip_val;
  struct node *astval;
  char* boolTyp;

#line 195 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
