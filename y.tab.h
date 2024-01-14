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
    OPEN_PRTHS = 265,              /* OPEN_PRTHS  */
    CLOSE_PRTHS = 266,             /* CLOSE_PRTHS  */
    BGIN = 267,                    /* BGIN  */
    END = 268,                     /* END  */
    IF = 269,                      /* IF  */
    ELSE = 270,                    /* ELSE  */
    WHILE = 271,                   /* WHILE  */
    FOR = 272,                     /* FOR  */
    DO = 273,                      /* DO  */
    RETURN = 274,                  /* RETURN  */
    ASSIGN = 275,                  /* ASSIGN  */
    LESS = 276,                    /* LESS  */
    LESSEQ = 277,                  /* LESSEQ  */
    GRT = 278,                     /* GRT  */
    GRTEQ = 279,                   /* GRTEQ  */
    EQ = 280,                      /* EQ  */
    NOT = 281,                     /* NOT  */
    AND = 282,                     /* AND  */
    OR = 283,                      /* OR  */
    PLUS = 284,                    /* PLUS  */
    MINUS = 285,                   /* MINUS  */
    DIV = 286,                     /* DIV  */
    MULTIP = 287,                  /* MULTIP  */
    MOD = 288,                     /* MOD  */
    LBRACES = 289,                 /* LBRACES  */
    RBRACES = 290,                 /* RBRACES  */
    LPAR = 291,                    /* LPAR  */
    RPAR = 292,                    /* RPAR  */
    LBRACKET = 293,                /* LBRACKET  */
    RBRACKET = 294,                /* RBRACKET  */
    POINT = 295,                   /* POINT  */
    SINGLE_QUOTES = 296,           /* SINGLE_QUOTES  */
    COMMA = 297,                   /* COMMA  */
    SEMI_COLLON = 298,             /* SEMI_COLLON  */
    PRINT = 299,                   /* PRINT  */
    PRIVAT = 300,                  /* PRIVAT  */
    PUBLIC = 301,                  /* PUBLIC  */
    PROTECTED = 302,               /* PROTECTED  */
    BOOL_VAL = 303,                /* BOOL_VAL  */
    INT_NUM = 304,                 /* INT_NUM  */
    REAL_NUM = 305,                /* REAL_NUM  */
    CHAR_VAL = 306,                /* CHAR_VAL  */
    STRING_VAL = 307,              /* STRING_VAL  */
    ARRAY_IDENTIF = 308,           /* ARRAY_IDENTIF  */
    VOID = 309,                    /* VOID  */
    INT = 310,                     /* INT  */
    FLOAT = 311,                   /* FLOAT  */
    CHAR = 312,                    /* CHAR  */
    STRING = 313,                  /* STRING  */
    BOOL = 314,                    /* BOOL  */
    IDENTIF = 315                  /* IDENTIF  */
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
#define OPEN_PRTHS 265
#define CLOSE_PRTHS 266
#define BGIN 267
#define END 268
#define IF 269
#define ELSE 270
#define WHILE 271
#define FOR 272
#define DO 273
#define RETURN 274
#define ASSIGN 275
#define LESS 276
#define LESSEQ 277
#define GRT 278
#define GRTEQ 279
#define EQ 280
#define NOT 281
#define AND 282
#define OR 283
#define PLUS 284
#define MINUS 285
#define DIV 286
#define MULTIP 287
#define MOD 288
#define LBRACES 289
#define RBRACES 290
#define LPAR 291
#define RPAR 292
#define LBRACKET 293
#define RBRACKET 294
#define POINT 295
#define SINGLE_QUOTES 296
#define COMMA 297
#define SEMI_COLLON 298
#define PRINT 299
#define PRIVAT 300
#define PUBLIC 301
#define PROTECTED 302
#define BOOL_VAL 303
#define INT_NUM 304
#define REAL_NUM 305
#define CHAR_VAL 306
#define STRING_VAL 307
#define ARRAY_IDENTIF 308
#define VOID 309
#define INT 310
#define FLOAT 311
#define CHAR 312
#define STRING 313
#define BOOL 314
#define IDENTIF 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 328 "fis.y"

  int intTyp;
  float floatTyp;
  char* charTyp;
  char* stringTyp;
  char* dataTyp; // IDENTIF or INT/VOID/FLOAT/CHAR/STRING/BOOL
  char* arrayTyp;
  char* tip_val;
  struct node *astval;
  char* boolTyp;

#line 199 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
