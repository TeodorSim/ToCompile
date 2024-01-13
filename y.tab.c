/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "fis.y"

#include <cstdio>
#include <cstdbool>
#include <cstring>
#include <cstdlib>
#include <cmath>

#define GLOBAL 0
#define MAIN 1
#define FUNCTION 2

#define true 1
#define false 0

#define VECTOR_DIMENSION 100
#define STRING_DIMENSION 256

extern int yylex(void);
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
void yyerror(char *);

  struct simboluri {
	char nume[STRING_DIMENSION];//NUME
	char typ[STRING_DIMENSION];//TIP
	int global;//LOCATIE_VAR  
	int costant;//CONSTANT
	int init;// daca variabila are valoare
	int intVal; //VALOARE
	float floatVal;//VALOARE
	char charVal[3];//VALOARE -> 'a'
    int boolVal;//BOOL VALOARE
    
    /* arrays */
	char stingVal[STRING_DIMENSION];//VALOARE
    int stingVal_occupied;//positioa pana la care sunt valori in string stingVal
	int vectorIntVal[VECTOR_DIMENSION];//VALOARE
    int vectorIntVal_occupied;//positia pana la care sunt valori in vectorul vectorIntVal
	float vectorFloatVal[VECTOR_DIMENSION];//VALOARE
    int vectorFloatVal_occupied;//positia pana la care sunt valori in vectorul vectorFloatVal
} Simb[256];


union value {
     int intVal;
     float floatVal;
     char strVal[101];
     char charVal;
	 int boolVal;
};

struct node {
	int type;
	union value var;
	struct node *left;
	struct node *right;
};



int nrFun=0; // nr de functii descrise
int nrSimb=0;// variabila va nr cate simboluri au fost declarate
int nrparametrii[50]={0};
int global =0; // 0- global 1- main 2 - scope functii
int nrf=0 ;// pe asocierea parametrilor
FILE* tabel;
FILE* tabel2;
void clear_table(){

     tabel=fopen("symbol_table.txt","w");
}

void tabel_sim () {
    tabel = fopen("symbol_table.txt", "a");

    for (int i = 1; i <= nrSimb; i++) {

    	fprintf(tabel, "%s  %s  %s  %s ", "Nume: ", Simb[i].nume, " | Tip: ", Simb[i].typ);

        if(Simb[i].global == 0) {
            fprintf(tabel, " %s  %s "," | Scope: ", "GLOBAL");
	    }
	    else {
            if(Simb[i].global == 1) {
                fprintf(tabel, " %s  %s "," | Scope: ", "MAIN");
	        }else{
                fprintf(tabel, " %s  %s "," | Scope: ", "FUNCTION");
            }
	    }

        /* tipe variabila :constant 
        fprintf(tabel, " %s ", " | Const: %d ", Simb[i].costant);
	    
        /* variabila initializata */
        if (Simb[i].init == 1) {
            fprintf(tabel, " %s ", " | Valoare: ");
            
            if (strcmp(Simb[i].typ, "int") == 0 ) {
                fprintf(tabel, " %d ", Simb[i].intVal);
            }
            
            if(strcmp(Simb[i].typ, "bool") == 0){
                if(Simb[i].boolVal == true){
                    fprintf(tabel, " true ");
                }
                else{
                    fprintf(tabel, " false");
                }
            } 

            if (strcmp(Simb[i].typ, "float") == 0) {
                fprintf(tabel, " %f ", Simb[i].floatVal);
            }
            
            if (strcmp(Simb[i].typ, "string") == 0) {
                fprintf(tabel, " %s ",Simb[i].stingVal );
            }

            if (strcmp(Simb[i].typ, "char") == 0 ){
                //printf("tabel_sim() pt Simb[%d].charVal: '%s'.\n", i,Simb[i].charVal );
                fprintf(tabel, " %s ",Simb[i].charVal );
            }
        }
        else {
            fprintf(tabel, " %s ", " | Neinitializata");        
        }
        
    fprintf(tabel, " %s " , "\n");
    }
}

void clear_table2(){

     tabel2=fopen("symbol_table_functions.txt","w");
}

void tabel_fun () {
    int i;
    tabel2 = fopen("symbol_table_functions.txt", "a");
}

//declararii sim
void declarare(char dnume[], char dtyp[], int dglobal, int dconstant)
{
    nrSimb++;
    strcpy(Simb[nrSimb].nume, dnume);
    strcpy(Simb[nrSimb].typ, dtyp);
    Simb[nrSimb].global= dglobal;
    Simb[nrSimb].costant=dconstant;
    Simb[nrSimb].init=0;
    Simb[nrSimb].intVal=-1;
    Simb[nrSimb].floatVal= -1;
    strcpy(Simb[nrSimb].charVal , "");
    strcpy(Simb[nrSimb].stingVal , "");
    Simb[nrSimb].vectorIntVal_occupied = 0;
    Simb[nrSimb].vectorFloatVal_occupied = 0;
    for(int i = 0; i< VECTOR_DIMENSION; i++){
        Simb[nrSimb].vectorIntVal_occupied = 0;
        Simb[nrSimb].vectorFloatVal_occupied = 0;
    }
}

// varificam daca o variabila a fost declarata
int verifdecl(char x[]) {
    for (int i = 0; i <= nrSimb; i++) {
         if (strcmp(x, Simb[i].nume) == 0) {
             //printf("ajunge in verifdecl \n");
             return i;
         }
    }
    return -1;
}
// varificam daca o variabila a fost intializata
int verifinit(char x[]) {
    int i;
    for (i = 0; i <= nrSimb; i++) {
         if (strcmp(x, Simb[i].nume) == 0) {
              if (Simb[i].init == 0)
                 return -1;
              else 
                 return 1;
         }
    }
    return -1;
}
/* tipul unei variabile */
void getTyp(char nume[], char get[])
{
    int k=verifdecl(nume);
    strcpy(get, Simb[k].typ);
}
/* copiere date dintr-o variabila in alta */
void copyVal(char receivs[], char sends[])
{
    int nr1=verifdecl(receivs);// pozitia variabilei care primeste valarea
    int nr2=verifdecl(sends);// pozitia variabilei care ofera valoare
    char tip[30];
    getTyp(sends,tip);
    if(strcmp(tip,"int")==0)
    {
        Simb[nr1].intVal=Simb[nr2].intVal;
        Simb[nr1].init=1;
    }
    else{
        if(strcmp(tip,"float")==0)
        {
            Simb[nr1].floatVal=Simb[nr2].floatVal;
            Simb[nr1].init=1;
        }
        else{
            if(strcmp(tip,"char")==0)
            {
                strcpy(Simb[nr1].charVal,Simb[nr2].charVal);
                Simb[nr1].init=1;
            }
            else{
                if(strcmp(tip,"string")==0)
                {
                    strcpy(Simb[nr1].stingVal,Simb[nr2].stingVal);
                    Simb[nr1].init=1;
                }
                else if(strcmp(tip, "bool")==0)
                {
                    Simb[nr1].boolVal=Simb[nr2].boolVal;
                    Simb[nr1].init=1;
                }
            }
        }

    }
}


// initializari tip
void initializareINT(char nume[], int val)
{
    int k=verifdecl(nume);
    if(k!=-1)
    {
        Simb[k].init=1;
        Simb[k].intVal=val;
    }
}
void initializareINTarray(char numer[], int val, int position){
    int k=verifdecl(numer);
    if(k!=-1)
    {
        Simb[k].init=1;
        Simb[k].vectorIntVal[position] = val;
        if(position > Simb[k].vectorIntVal_occupied){
             Simb[k].vectorIntVal_occupied = position;
        }
    } 
}
void initializareFLOAT(char nume[], float val)
{
    int k=verifdecl(nume);
    if(k!=-1)
    {
        Simb[k].init=1;
        Simb[k].floatVal=val;
    }
}
void initializareCHAR(char nume[], char val[])
{
    int k=verifdecl(nume);
    if(k!=-1)
    {
        Simb[k].init=1;
        strcpy(Simb[k].charVal,val);
        //printf("initializareCHAR() a pus in Simb[%d].charVal: %s and type: Simb[%d].typ: %s\n", k, Simb[k].charVal, k, Simb[k].typ);
    }
}
void initializareSTRING(char nume[], char val[])
{
    int k=verifdecl(nume);
    if(k!=-1)
    {
        Simb[k].init=1;
        strcpy(Simb[k].stingVal,val);
    }
}
void initializareBOOL(char nume[], char val[])
{
    int k=verifdecl(nume);
    if(k!=-1)
    {
        Simb[k].init=1;
        if(strcmp(val, "\"true\"")==0){
            Simb[k].boolVal=true;
        }
        else{
            Simb[k].boolVal=false;
        }
    }
}

#line 370 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 300 "fis.y"

  int intTyp;
  float floatTyp;
  char* charTyp;
  char* stringTyp;
  char* dataTyp; // IDENTIF or INT/VOID/FLOAT/CHAR/STRING/BOOL
  char* arrayTyp;
  char* tip_val;
  struct node *astval;
  char* boolTyp;

#line 551 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONSTANT = 3,                   /* CONSTANT  */
  YYSYMBOL_EVAL = 4,                       /* EVAL  */
  YYSYMBOL_STRUCTURE = 5,                  /* STRUCTURE  */
  YYSYMBOL_CLASS = 6,                      /* CLASS  */
  YYSYMBOL_TYPEOF = 7,                     /* TYPEOF  */
  YYSYMBOL_TREQQ = 8,                      /* TREQQ  */
  YYSYMBOL_CLASS_TYP = 9,                  /* CLASS_TYP  */
  YYSYMBOL_BGIN = 10,                      /* BGIN  */
  YYSYMBOL_END = 11,                       /* END  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_DO = 16,                        /* DO  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_ASSIGN = 18,                    /* ASSIGN  */
  YYSYMBOL_LESS = 19,                      /* LESS  */
  YYSYMBOL_LESSEQ = 20,                    /* LESSEQ  */
  YYSYMBOL_GRT = 21,                       /* GRT  */
  YYSYMBOL_GRTEQ = 22,                     /* GRTEQ  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_OR = 26,                        /* OR  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_DIV = 29,                       /* DIV  */
  YYSYMBOL_MULTIP = 30,                    /* MULTIP  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_LBRACES = 32,                   /* LBRACES  */
  YYSYMBOL_RBRACES = 33,                   /* RBRACES  */
  YYSYMBOL_LPAR = 34,                      /* LPAR  */
  YYSYMBOL_RPAR = 35,                      /* RPAR  */
  YYSYMBOL_LBRACKET = 36,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 37,                  /* RBRACKET  */
  YYSYMBOL_POINT = 38,                     /* POINT  */
  YYSYMBOL_SINGLE_QUOTES = 39,             /* SINGLE_QUOTES  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_SEMI_COLLON = 41,               /* SEMI_COLLON  */
  YYSYMBOL_PRINT = 42,                     /* PRINT  */
  YYSYMBOL_PRIVAT = 43,                    /* PRIVAT  */
  YYSYMBOL_PUBLIC = 44,                    /* PUBLIC  */
  YYSYMBOL_PROTECTED = 45,                 /* PROTECTED  */
  YYSYMBOL_BOOL_VAL = 46,                  /* BOOL_VAL  */
  YYSYMBOL_INT_NUM = 47,                   /* INT_NUM  */
  YYSYMBOL_REAL_NUM = 48,                  /* REAL_NUM  */
  YYSYMBOL_CHAR_VAL = 49,                  /* CHAR_VAL  */
  YYSYMBOL_STRING_VAL = 50,                /* STRING_VAL  */
  YYSYMBOL_ARRAY_IDENTIF = 51,             /* ARRAY_IDENTIF  */
  YYSYMBOL_VOID = 52,                      /* VOID  */
  YYSYMBOL_INT = 53,                       /* INT  */
  YYSYMBOL_FLOAT = 54,                     /* FLOAT  */
  YYSYMBOL_CHAR = 55,                      /* CHAR  */
  YYSYMBOL_STRING = 56,                    /* STRING  */
  YYSYMBOL_BOOL = 57,                      /* BOOL  */
  YYSYMBOL_IDENTIF = 58,                   /* IDENTIF  */
  YYSYMBOL_59_ = 59,                       /* '+'  */
  YYSYMBOL_60_ = 60,                       /* '-'  */
  YYSYMBOL_61_ = 61,                       /* '*'  */
  YYSYMBOL_62_ = 62,                       /* '/'  */
  YYSYMBOL_63_ = 63,                       /* '%'  */
  YYSYMBOL_64_ = 64,                       /* '{'  */
  YYSYMBOL_65_ = 65,                       /* '}'  */
  YYSYMBOL_66_ = 66,                       /* '['  */
  YYSYMBOL_67_ = 67,                       /* ']'  */
  YYSYMBOL_68_ = 68,                       /* '('  */
  YYSYMBOL_69_ = 69,                       /* ')'  */
  YYSYMBOL_70_ = 70,                       /* ';'  */
  YYSYMBOL_71_ = 71,                       /* ','  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_vartype = 73,                   /* vartype  */
  YYSYMBOL_INSTRUCTIUNI = 74,              /* INSTRUCTIUNI  */
  YYSYMBOL_INSTRUCTIUNE = 75               /* INSTRUCTIUNE  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   57

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  4
/* YYNRULES -- Number of rules.  */
#define YYNRULES  17
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  23

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    63,     2,     2,
      68,    69,    61,    59,    71,    60,     2,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    70,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    65,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   343,   343,   344,   345,   346,   347,   372,   373,   377,
     386,   397,   408,   425,   436,   447,   481,   494
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONSTANT", "EVAL",
  "STRUCTURE", "CLASS", "TYPEOF", "TREQQ", "CLASS_TYP", "BGIN", "END",
  "IF", "ELSE", "WHILE", "FOR", "DO", "RETURN", "ASSIGN", "LESS", "LESSEQ",
  "GRT", "GRTEQ", "EQ", "NOT", "AND", "OR", "PLUS", "MINUS", "DIV",
  "MULTIP", "MOD", "LBRACES", "RBRACES", "LPAR", "RPAR", "LBRACKET",
  "RBRACKET", "POINT", "SINGLE_QUOTES", "COMMA", "SEMI_COLLON", "PRINT",
  "PRIVAT", "PUBLIC", "PROTECTED", "BOOL_VAL", "INT_NUM", "REAL_NUM",
  "CHAR_VAL", "STRING_VAL", "ARRAY_IDENTIF", "VOID", "INT", "FLOAT",
  "CHAR", "STRING", "BOOL", "IDENTIF", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'{'", "'}'", "'['", "']'", "'('", "')'", "';'", "','", "$accept",
  "vartype", "INSTRUCTIUNI", "INSTRUCTIUNE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -38,   -63,   -63,   -63,   -63,   -63,   -44,     0,   -62,   -63,
      -9,   -63,   -60,   -63,   -45,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     2,     4,     3,     6,     5,     0,     0,     0,    16,
       9,     1,     0,     7,     0,     8,    14,    10,    11,    12,
      13,    17,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,     4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      11,    16,    17,    18,    19,    20,    21,     9,    13,    14,
      15,    12,     0,    22,    10,     1,     2,     3,     4,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5
};

static const yytype_int8 yycheck[] =
{
       0,    46,    47,    48,    49,    50,    51,    51,    70,    18,
      70,     7,    -1,    58,    58,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    53,    54,    55,    56,    57,    73,    74,    75,    51,
      58,     0,    75,    70,    18,    70,    46,    47,    48,    49,
      50,    51,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    75,    75,    75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     2,     3,     2,
       4,     4,     4,     4,     4,     4,     2,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 9: /* INSTRUCTIUNE: vartype IDENTIF  */
#line 377 "fis.y"
                    {
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        }
#line 1633 "y.tab.c"
    break;

  case 10: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN INT_NUM  */
#line 386 "fis.y"
                                   {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 1649 "y.tab.c"
    break;

  case 11: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN REAL_NUM  */
#line 397 "fis.y"
                                    {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 1665 "y.tab.c"
    break;

  case 12: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 408 "fis.y"
                                    {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else if(strlen((yyvsp[0].charTyp))!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror("eroare");
        }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $4 );
            initializareCHAR((yyvsp[-2].dataTyp), (yyvsp[0].charTyp));
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
#line 1687 "y.tab.c"
    break;

  case 13: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN STRING_VAL  */
#line 425 "fis.y"
                                       {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareSTRING((yyvsp[-2].dataTyp), (yyvsp[0].stringTyp));
            }
        global = 0;
        }
#line 1703 "y.tab.c"
    break;

  case 14: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 436 "fis.y"
                                     {
       if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareBOOL((yyvsp[-2].dataTyp), (yyvsp[0].boolTyp));
            } 
        global = 0;
        }
#line 1719 "y.tab.c"
    break;

  case 15: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN IDENTIF  */
#line 447 "fis.y"
                                    {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-2].dataTyp),  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl((yyvsp[0].dataTyp))==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[0].dataTyp),  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit((yyvsp[0].dataTyp))==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", (yyvsp[0].dataTyp), yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp((yyvsp[0].dataTyp), tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp((yyvsp[-3].dataTyp), tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
                        copyVal((yyvsp[-2].dataTyp), (yyvsp[0].dataTyp));
                        }
                    }
                }
            }
        global = 0;
        }
#line 1758 "y.tab.c"
    break;

  case 16: /* INSTRUCTIUNE: vartype ARRAY_IDENTIF  */
#line 481 "fis.y"
                           {
        if(verifdecl((yyvsp[0].arrayTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            /* spatiu pt vector */
            char to_hold[100];
            strcpy(to_hold, (yyvsp[-1].dataTyp));
            strcat(to_hold, " vector");
            declarare((yyvsp[0].arrayTyp), to_hold, global, 0);
            } 
        }
#line 1776 "y.tab.c"
    break;

  case 17: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 494 "fis.y"
                                          {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-2].dataTyp),  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl((yyvsp[0].arrayTyp))==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[0].arrayTyp),  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit((yyvsp[0].arrayTyp))==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", (yyvsp[0].arrayTyp), yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp((yyvsp[0].arrayTyp), tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp((yyvsp[-3].dataTyp), tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
                        copyVal((yyvsp[-2].dataTyp), (yyvsp[0].arrayTyp));
                        }
                    }
                }
            }
        global = 0;
        }
#line 1815 "y.tab.c"
    break;


#line 1819 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 565 "fis.y"


int errors_occurred = 0;

void yyerror(char * s) {
    printf("-\\---/\\---/-\n");
    printf("--\\-/--\\-/--\n");
    printf("--/-\\--/-\\--\n");
    printf("-/---\\/---\\-\n");
    errors_occurred++;   
    printf("message: %s\n", s);
    printf("%s %s %d\n","Syntax ERROR.", "\nErrors occurred! Current error at line: ", yylineno);
    printf("--------------------------------\n");
}

int main(int argc, char** argv) {

    yyin=fopen(argv[1],"r");

    yyparse();
    
    clear_table();
    tabel_sim();
    clear_table2();
    tabel_fun();
    
    if (errors_occurred == 0) {
        printf("------/-\n");
        printf("-----/--\n");
        printf("-\\--/---\n");
        printf("--\\/----\n");
        printf("input passed.\n");
    }
}
