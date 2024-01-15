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
    OPEN_SQR_PRTHS = 258,          /* OPEN_SQR_PRTHS  */
    CLOSE_SQR_PRTHS = 259,         /* CLOSE_SQR_PRTHS  */
    CONSTANT = 260,                /* CONSTANT  */
    EVAL = 261,                    /* EVAL  */
    STRUCTURE = 262,               /* STRUCTURE  */
    CLASSOF = 263,                 /* CLASSOF  */
    TYPEOF = 264,                  /* TYPEOF  */
    TREQQ = 265,                   /* TREQQ  */
    CLASS_TYP = 266,               /* CLASS_TYP  */
    OPEN_PRTHS = 267,              /* OPEN_PRTHS  */
    CLOSE_PRTHS = 268,             /* CLOSE_PRTHS  */
    BGIN = 269,                    /* BGIN  */
    END = 270,                     /* END  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    WHILE = 273,                   /* WHILE  */
    FOR = 274,                     /* FOR  */
    DO = 275,                      /* DO  */
    RETURN = 276,                  /* RETURN  */
    ASSIGN = 277,                  /* ASSIGN  */
    LESS = 278,                    /* LESS  */
    LESSEQ = 279,                  /* LESSEQ  */
    GRT = 280,                     /* GRT  */
    GRTEQ = 281,                   /* GRTEQ  */
    EQ = 282,                      /* EQ  */
    NOT = 283,                     /* NOT  */
    AND = 284,                     /* AND  */
    OR = 285,                      /* OR  */
    PLUS = 286,                    /* PLUS  */
    MINUS = 287,                   /* MINUS  */
    DIV = 288,                     /* DIV  */
    MULTIP = 289,                  /* MULTIP  */
    MOD = 290,                     /* MOD  */
    LBRACES = 291,                 /* LBRACES  */
    RBRACES = 292,                 /* RBRACES  */
    LPAR = 293,                    /* LPAR  */
    RPAR = 294,                    /* RPAR  */
    LBRACKET = 295,                /* LBRACKET  */
    RBRACKET = 296,                /* RBRACKET  */
    POINT = 297,                   /* POINT  */
    SINGLE_QUOTES = 298,           /* SINGLE_QUOTES  */
    COMMA = 299,                   /* COMMA  */
    SEMI_COLLON = 300,             /* SEMI_COLLON  */
    PRINT = 301,                   /* PRINT  */
    PRIVAT = 302,                  /* PRIVAT  */
    PUBLIC = 303,                  /* PUBLIC  */
    PROTECTED = 304,               /* PROTECTED  */
    DOUA_DOUA_PCTE = 305,          /* DOUA_DOUA_PCTE  */
    PRIVATE = 306,                 /* PRIVATE  */
    BOOL_VAL = 307,                /* BOOL_VAL  */
    INT_NUM = 308,                 /* INT_NUM  */
    REAL_NUM = 309,                /* REAL_NUM  */
    CHAR_VAL = 310,                /* CHAR_VAL  */
    STRING_VAL = 311,              /* STRING_VAL  */
    ARRAY_IDENTIF = 312,           /* ARRAY_IDENTIF  */
    VOID = 313,                    /* VOID  */
    INT = 314,                     /* INT  */
    FLOAT = 315,                   /* FLOAT  */
    CHAR = 316,                    /* CHAR  */
    STRING = 317,                  /* STRING  */
    BOOL = 318,                    /* BOOL  */
    IDENTIF = 319                  /* IDENTIF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define OPEN_SQR_PRTHS 258
#define CLOSE_SQR_PRTHS 259
#define CONSTANT 260
#define EVAL 261
#define STRUCTURE 262
#define CLASSOF 263
#define TYPEOF 264
#define TREQQ 265
#define CLASS_TYP 266
#define OPEN_PRTHS 267
#define CLOSE_PRTHS 268
#define BGIN 269
#define END 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define FOR 274
#define DO 275
#define RETURN 276
#define ASSIGN 277
#define LESS 278
#define LESSEQ 279
#define GRT 280
#define GRTEQ 281
#define EQ 282
#define NOT 283
#define AND 284
#define OR 285
#define PLUS 286
#define MINUS 287
#define DIV 288
#define MULTIP 289
#define MOD 290
#define LBRACES 291
#define RBRACES 292
#define LPAR 293
#define RPAR 294
#define LBRACKET 295
#define RBRACKET 296
#define POINT 297
#define SINGLE_QUOTES 298
#define COMMA 299
#define SEMI_COLLON 300
#define PRINT 301
#define PRIVAT 302
#define PUBLIC 303
#define PROTECTED 304
#define DOUA_DOUA_PCTE 305
#define PRIVATE 306
#define BOOL_VAL 307
#define INT_NUM 308
#define REAL_NUM 309
#define CHAR_VAL 310
#define STRING_VAL 311
#define ARRAY_IDENTIF 312
#define VOID 313
#define INT 314
#define FLOAT 315
#define CHAR 316
#define STRING 317
#define BOOL 318
#define IDENTIF 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 403 "fis.y"

  int intTyp;
  float floatTyp;
  char* charTyp;
  char* stringTyp;
  char* dataTyp; // IDENTIF or INT/VOID/FLOAT/CHAR/STRING/BOOL
  char* arrayTyp;
  char* tip_val;
  struct node *astval;
  char* boolTyp;

#line 207 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
