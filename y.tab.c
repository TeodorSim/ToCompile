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
    
    /* obiecte */
    bool inside_object = false; //true <- simbolul face parte dintr-un obiect; false <- invers
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
struct{
    int nrSimb;
    bool activ;
} inside_struct;
//inside_struct.activ=true - varibila e parte dins struct
//inside_struct.activ=true - varibila nu e parte dins struct
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
    if(strcmp(dtyp, "structure")==0){
        //reiteram in tabelul de simboluri pentru a modifca numele variabilelor din struct
        // luam toate simbolurile ce au flagul de 'inside_object' activ
        int copie_nrSimb = nrSimb -1;
        while(copie_nrSimb > 0 && Simb[copie_nrSimb].inside_object==true){
            //structNume.variabilaInternaNume;
            char copie_nume[STRING_DIMENSION];
            strcpy(copie_nume, dnume);
            strcat(copie_nume, ".");
            strcat(copie_nume, Simb[copie_nrSimb].nume);
            strcpy(Simb[copie_nrSimb].nume, copie_nume);
            
            //resetam flag ul
            Simb[copie_nrSimb].inside_object = false;

            //continuam cautarea
            copie_nrSimb--;
        }
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

#line 398 "y.tab.c"

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

#line 583 "y.tab.c"

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
  YYSYMBOL_OPEN_PRTHS = 10,                /* OPEN_PRTHS  */
  YYSYMBOL_CLOSE_PRTHS = 11,               /* CLOSE_PRTHS  */
  YYSYMBOL_BGIN = 12,                      /* BGIN  */
  YYSYMBOL_END = 13,                       /* END  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_WHILE = 16,                     /* WHILE  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_ASSIGN = 20,                    /* ASSIGN  */
  YYSYMBOL_LESS = 21,                      /* LESS  */
  YYSYMBOL_LESSEQ = 22,                    /* LESSEQ  */
  YYSYMBOL_GRT = 23,                       /* GRT  */
  YYSYMBOL_GRTEQ = 24,                     /* GRTEQ  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_DIV = 31,                       /* DIV  */
  YYSYMBOL_MULTIP = 32,                    /* MULTIP  */
  YYSYMBOL_MOD = 33,                       /* MOD  */
  YYSYMBOL_LBRACES = 34,                   /* LBRACES  */
  YYSYMBOL_RBRACES = 35,                   /* RBRACES  */
  YYSYMBOL_LPAR = 36,                      /* LPAR  */
  YYSYMBOL_RPAR = 37,                      /* RPAR  */
  YYSYMBOL_LBRACKET = 38,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 39,                  /* RBRACKET  */
  YYSYMBOL_POINT = 40,                     /* POINT  */
  YYSYMBOL_SINGLE_QUOTES = 41,             /* SINGLE_QUOTES  */
  YYSYMBOL_COMMA = 42,                     /* COMMA  */
  YYSYMBOL_SEMI_COLLON = 43,               /* SEMI_COLLON  */
  YYSYMBOL_PRINT = 44,                     /* PRINT  */
  YYSYMBOL_PRIVAT = 45,                    /* PRIVAT  */
  YYSYMBOL_PUBLIC = 46,                    /* PUBLIC  */
  YYSYMBOL_PROTECTED = 47,                 /* PROTECTED  */
  YYSYMBOL_BOOL_VAL = 48,                  /* BOOL_VAL  */
  YYSYMBOL_INT_NUM = 49,                   /* INT_NUM  */
  YYSYMBOL_REAL_NUM = 50,                  /* REAL_NUM  */
  YYSYMBOL_CHAR_VAL = 51,                  /* CHAR_VAL  */
  YYSYMBOL_STRING_VAL = 52,                /* STRING_VAL  */
  YYSYMBOL_ARRAY_IDENTIF = 53,             /* ARRAY_IDENTIF  */
  YYSYMBOL_VOID = 54,                      /* VOID  */
  YYSYMBOL_INT = 55,                       /* INT  */
  YYSYMBOL_FLOAT = 56,                     /* FLOAT  */
  YYSYMBOL_CHAR = 57,                      /* CHAR  */
  YYSYMBOL_STRING = 58,                    /* STRING  */
  YYSYMBOL_BOOL = 59,                      /* BOOL  */
  YYSYMBOL_IDENTIF = 60,                   /* IDENTIF  */
  YYSYMBOL_61_ = 61,                       /* '+'  */
  YYSYMBOL_62_ = 62,                       /* '-'  */
  YYSYMBOL_63_ = 63,                       /* '*'  */
  YYSYMBOL_64_ = 64,                       /* '/'  */
  YYSYMBOL_65_ = 65,                       /* '%'  */
  YYSYMBOL_66_ = 66,                       /* '{'  */
  YYSYMBOL_67_ = 67,                       /* '}'  */
  YYSYMBOL_68_ = 68,                       /* '['  */
  YYSYMBOL_69_ = 69,                       /* ']'  */
  YYSYMBOL_70_ = 70,                       /* '('  */
  YYSYMBOL_71_ = 71,                       /* ')'  */
  YYSYMBOL_72_ = 72,                       /* ';'  */
  YYSYMBOL_73_ = 73,                       /* ','  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_vartype = 75,                   /* vartype  */
  YYSYMBOL_PROGRAM = 76,                   /* PROGRAM  */
  YYSYMBOL_BLOC = 77,                      /* BLOC  */
  YYSYMBOL_INSTRUCTIUNI = 78,              /* INSTRUCTIUNI  */
  YYSYMBOL_INSTRUCTIUNE = 79,              /* INSTRUCTIUNE  */
  YYSYMBOL_STRUCTURI = 80,                 /* STRUCTURI  */
  YYSYMBOL_STRUCTURA = 81,                 /* STRUCTURA  */
  YYSYMBOL_DECLARATII_IN_OBJECT = 82,      /* DECLARATII_IN_OBJECT  */
  YYSYMBOL_DECLARATIE_IN_OBJ = 83,         /* DECLARATIE_IN_OBJ  */
  YYSYMBOL_DECLARATII = 84,                /* DECLARATII  */
  YYSYMBOL_DECLARATIE = 85                 /* DECLARATIE  */
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   103

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  89

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
       2,     2,     2,     2,     2,     2,     2,    65,     2,     2,
      70,    71,    63,    61,    73,    62,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    72,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    69,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   371,   371,   372,   373,   374,   375,   400,   401,   402,
     403,   409,   411,   412,   416,   426,   438,   450,   468,   480,
     492,   527,   541,   581,   582,   588,   600,   601,   605,   616,
     630,   643,   662,   675,   688,   725,   740,   777,   781,   782,
     786,   795,   806,   817,   834,   845,   856,   890,   903,   937
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
  "STRUCTURE", "CLASS", "TYPEOF", "TREQQ", "CLASS_TYP", "OPEN_PRTHS",
  "CLOSE_PRTHS", "BGIN", "END", "IF", "ELSE", "WHILE", "FOR", "DO",
  "RETURN", "ASSIGN", "LESS", "LESSEQ", "GRT", "GRTEQ", "EQ", "NOT", "AND",
  "OR", "PLUS", "MINUS", "DIV", "MULTIP", "MOD", "LBRACES", "RBRACES",
  "LPAR", "RPAR", "LBRACKET", "RBRACKET", "POINT", "SINGLE_QUOTES",
  "COMMA", "SEMI_COLLON", "PRINT", "PRIVAT", "PUBLIC", "PROTECTED",
  "BOOL_VAL", "INT_NUM", "REAL_NUM", "CHAR_VAL", "STRING_VAL",
  "ARRAY_IDENTIF", "VOID", "INT", "FLOAT", "CHAR", "STRING", "BOOL",
  "IDENTIF", "'+'", "'-'", "'*'", "'/'", "'%'", "'{'", "'}'", "'['", "']'",
  "'('", "')'", "';'", "','", "$accept", "vartype", "PROGRAM", "BLOC",
  "INSTRUCTIUNI", "INSTRUCTIUNE", "STRUCTURI", "STRUCTURA",
  "DECLARATII_IN_OBJECT", "DECLARATIE_IN_OBJ", "DECLARATII", "DECLARATIE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-59)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,    -6,   -59,   -59,   -59,   -59,   -59,   -44,     8,     0,
     -58,    -5,   -49,    35,   -59,    15,   -59,   -41,    25,    35,
     -36,   -30,     5,   -59,    35,    27,   -29,   -59,   -20,   -10,
     -28,   -23,   -59,    58,   -59,   -19,     7,   -59,   -59,    35,
      67,    35,   -59,   -59,    61,    22,    26,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,   -59,    17,   -59,    75,   -59,    84,
     -59,    86,    23,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,    36,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      49,     0,     2,     4,     3,     6,     5,     0,     0,    49,
       0,    49,     0,    37,    47,    40,     1,     0,     0,    11,
       0,     0,    49,    23,     0,     0,     0,    38,     0,    37,
       0,     0,    21,    14,     8,     0,     0,    12,    24,     0,
       0,     0,    39,    35,    28,     0,     0,    26,    45,    41,
      42,    43,    44,    48,    46,     0,    21,    14,    13,     0,
       7,     0,     0,    25,    27,    19,    15,    16,    17,    18,
      22,    20,     0,     9,    10,    33,    29,    30,    31,    32,
      36,    34,    19,    15,    16,    17,    18,    22,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,     2,   -59,   -21,   -59,    81,    90,    -3,   -59,    73,
      94,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    35,     8,    18,    19,    20,     9,    10,    29,    30,
      11,    12
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       1,    45,     7,    40,    13,     1,    21,    24,    16,    14,
      26,    17,    32,     7,    23,    28,    15,    39,    59,    33,
      61,    26,    21,    27,     7,    48,    49,    50,    51,    52,
      53,    28,     1,    43,    56,    31,    37,    54,    34,    41,
      44,    57,    38,    42,    47,     2,     3,     4,     5,     6,
       2,     3,     4,     5,     6,     2,     3,     4,     5,     6,
       2,     3,     4,     5,     6,    65,    66,    67,    68,    69,
      70,    75,    76,    77,    78,    79,    80,    71,    55,    58,
      60,    62,    63,    81,    82,    83,    84,    85,    86,    87,
       2,     3,     4,     5,     6,    72,    88,    73,    64,    74,
      36,    25,    46,    22
};

static const yytype_int8 yycheck[] =
{
       5,    11,     0,    24,    10,     5,     9,    12,     0,    53,
      11,     9,    53,    11,    72,    13,    60,    12,    39,    60,
      41,    22,    25,    72,    22,    48,    49,    50,    51,    52,
      53,    29,     5,    53,    53,    20,    72,    60,    13,    12,
      60,    60,    72,    72,    72,    55,    56,    57,    58,    59,
      55,    56,    57,    58,    59,    55,    56,    57,    58,    59,
      55,    56,    57,    58,    59,    48,    49,    50,    51,    52,
      53,    48,    49,    50,    51,    52,    53,    60,    20,    72,
      13,    20,    60,    60,    48,    49,    50,    51,    52,    53,
      55,    56,    57,    58,    59,    20,    60,    13,    72,    13,
      19,    11,    29,     9
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    55,    56,    57,    58,    59,    75,    76,    80,
      81,    84,    85,    10,    53,    60,     0,    75,    77,    78,
      79,    81,    84,    72,    12,    80,    85,    72,    75,    82,
      83,    20,    53,    60,    13,    75,    79,    72,    72,    12,
      77,    12,    72,    53,    60,    11,    83,    72,    48,    49,
      50,    51,    52,    53,    60,    20,    53,    60,    72,    77,
      13,    77,    20,    60,    72,    48,    49,    50,    51,    52,
      53,    60,    20,    13,    13,    48,    49,    50,    51,    52,
      53,    60,    48,    49,    50,    51,    52,    53,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    75,    76,    76,    76,
      76,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    81,    82,    82,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     4,     3,     5,
       5,     1,     2,     3,     2,     4,     4,     4,     4,     4,
       4,     2,     4,     2,     3,     5,     2,     3,     2,     4,
       4,     4,     4,     4,     4,     2,     4,     0,     2,     3,
       2,     4,     4,     4,     4,     4,     4,     2,     4,     0
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
  case 14: /* INSTRUCTIUNE: vartype IDENTIF  */
#line 416 "fis.y"
                    {
        global = 1;
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        }
#line 1717 "y.tab.c"
    break;

  case 15: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN INT_NUM  */
#line 426 "fis.y"
                                   {
        global = 1;
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
#line 1734 "y.tab.c"
    break;

  case 16: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN REAL_NUM  */
#line 438 "fis.y"
                                    {
        global = 1;
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
#line 1751 "y.tab.c"
    break;

  case 17: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 450 "fis.y"
                                    {
        global = 1;
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
#line 1774 "y.tab.c"
    break;

  case 18: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN STRING_VAL  */
#line 468 "fis.y"
                                       {
        global = 1;
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
#line 1791 "y.tab.c"
    break;

  case 19: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 480 "fis.y"
                                     {
        global = 1;
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
#line 1808 "y.tab.c"
    break;

  case 20: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN IDENTIF  */
#line 492 "fis.y"
                                    {
        global = 1;
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
#line 1848 "y.tab.c"
    break;

  case 21: /* INSTRUCTIUNE: vartype ARRAY_IDENTIF  */
#line 527 "fis.y"
                           {
        global = 1;
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
#line 1867 "y.tab.c"
    break;

  case 22: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 541 "fis.y"
                                          {
        global = 1;
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
#line 1907 "y.tab.c"
    break;

  case 25: /* STRUCTURA: STRUCTURE OPEN_PRTHS DECLARATII_IN_OBJECT CLOSE_PRTHS IDENTIF  */
#line 588 "fis.y"
                                                                  {
            if(verifdecl((yyvsp[0].dataTyp))== -1){
                declarare((yyvsp[0].dataTyp), "structure", global, 0);
            
            }
            else{
                printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            }
        }
#line 1921 "y.tab.c"
    break;

  case 28: /* DECLARATIE_IN_OBJ: vartype IDENTIF  */
#line 605 "fis.y"
                     {
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        }
#line 1937 "y.tab.c"
    break;

  case 29: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN INT_NUM  */
#line 616 "fis.y"
                                   {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        else{
                printf("inside DECLARATIE_IN_OBJ\n");
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 1956 "y.tab.c"
    break;

  case 30: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN REAL_NUM  */
#line 630 "fis.y"
                                    {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 1974 "y.tab.c"
    break;

  case 31: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 643 "fis.y"
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
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $4 );
            initializareCHAR((yyvsp[-2].dataTyp), (yyvsp[0].charTyp));
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
#line 1998 "y.tab.c"
    break;

  case 32: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN STRING_VAL  */
#line 662 "fis.y"
                                       {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareSTRING((yyvsp[-2].dataTyp), (yyvsp[0].stringTyp));
            }
        global = 0;
        }
#line 2016 "y.tab.c"
    break;

  case 33: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 675 "fis.y"
                                     {
       if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareBOOL((yyvsp[-2].dataTyp), (yyvsp[0].boolTyp));
            } 
        global = 0;
        }
#line 2034 "y.tab.c"
    break;

  case 34: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN IDENTIF  */
#line 688 "fis.y"
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
                        
                        /*marcam variabila ca parte dintr-un obiect */
                        Simb[nrSimb].inside_object = true;
                        copyVal((yyvsp[-2].dataTyp), (yyvsp[0].dataTyp));
                        }
                    }
                }
            }
        global = 0;
        }
#line 2076 "y.tab.c"
    break;

  case 35: /* DECLARATIE_IN_OBJ: vartype ARRAY_IDENTIF  */
#line 725 "fis.y"
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
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            } 
        }
#line 2096 "y.tab.c"
    break;

  case 36: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 740 "fis.y"
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
                        
                        /*marcam variabila ca parte dintr-un obiect */
                        Simb[nrSimb].inside_object = true;
                        copyVal((yyvsp[-2].dataTyp), (yyvsp[0].arrayTyp));
                        }
                    }
                }
            }
        global = 0;
        }
#line 2138 "y.tab.c"
    break;

  case 40: /* DECLARATIE: vartype IDENTIF  */
#line 786 "fis.y"
                     {
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        }
#line 2152 "y.tab.c"
    break;

  case 41: /* DECLARATIE: vartype IDENTIF ASSIGN INT_NUM  */
#line 795 "fis.y"
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
#line 2168 "y.tab.c"
    break;

  case 42: /* DECLARATIE: vartype IDENTIF ASSIGN REAL_NUM  */
#line 806 "fis.y"
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
#line 2184 "y.tab.c"
    break;

  case 43: /* DECLARATIE: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 817 "fis.y"
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
#line 2206 "y.tab.c"
    break;

  case 44: /* DECLARATIE: vartype IDENTIF ASSIGN STRING_VAL  */
#line 834 "fis.y"
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
#line 2222 "y.tab.c"
    break;

  case 45: /* DECLARATIE: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 845 "fis.y"
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
#line 2238 "y.tab.c"
    break;

  case 46: /* DECLARATIE: vartype IDENTIF ASSIGN IDENTIF  */
#line 856 "fis.y"
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
#line 2277 "y.tab.c"
    break;

  case 47: /* DECLARATIE: vartype ARRAY_IDENTIF  */
#line 890 "fis.y"
                           {
        if(verifdecl((yyvsp[0].arrayTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            //yyerror("eroare");
            }
        else{
            /* spatiu pt vector */
            char to_hold[100];
            strcpy(to_hold, (yyvsp[-1].dataTyp));
            strcat(to_hold, " vector");
            declarare((yyvsp[0].arrayTyp), to_hold, global, 0);
            } 
        }
#line 2295 "y.tab.c"
    break;

  case 48: /* DECLARATIE: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 903 "fis.y"
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
#line 2334 "y.tab.c"
    break;


#line 2338 "y.tab.c"

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

#line 973 "fis.y"


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
