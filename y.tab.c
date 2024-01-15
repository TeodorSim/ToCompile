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
#define CLASS_LEVEL 3

#define INT_VECTOR_VALUE_STOP -9999
#define FLOAT_VECTOR_VALUE_STOP -9999.0

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
	int constant;//CONSTANT
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
int global =0; // 0- global 1- main 2 - scope functii 3 -class scope
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
                if(Simb[i].global == 2){
                    fprintf(tabel, " %s  %s "," | Scope: ", "FUNCTION");
                }else{
                    fprintf(tabel, " %s  %s "," | Scope: ", "CLASS");
                }
            }
	    }

        /* tipe variabila :constant */
        fprintf(tabel, " | Const: %d ", Simb[i].constant);
	    
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

            /* arrays */
            if(strcmp(Simb[i].typ, "int vector") == 0 ){
                fprintf(tabel, " [ ");
                //printf("In TabelSimb; vector %s are Val_occupied : %d\n", Simb[i].nume, Simb[i].vectorIntVal_occupied);
                for(int element_vector = 0; element_vector < Simb[i].vectorIntVal_occupied  ; element_vector++){
                    if(element_vector == Simb[i].vectorIntVal_occupied - 1){
                        fprintf(tabel, " %d ]", Simb[i].vectorIntVal[element_vector]);
                    }
                    else{
                        fprintf(tabel, " %d, ", Simb[i].vectorIntVal[element_vector]);
                    }
                }
            }

            if(strcmp(Simb[i].typ, "float vector") == 0 ){
                fprintf(tabel, " [ ");
                //printf("In TabelSimb; vector %s are Val_occupied : %d\n", Simb[i].nume, Simb[i].vectorFloatVal_occupied);
                for(int element_vector = 0; element_vector < Simb[i].vectorFloatVal_occupied  ; element_vector++){
                    if(element_vector == Simb[i].vectorFloatVal_occupied - 1){
                        fprintf(tabel, " %d ]", Simb[i].vectorFloatVal[element_vector]);
                    }
                    else{
                        fprintf(tabel, " %d, ", Simb[i].vectorFloatVal[element_vector]);
                    }
                }
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
    Simb[nrSimb].constant=dconstant;
    Simb[nrSimb].init=0;
    Simb[nrSimb].intVal=-1;
    Simb[nrSimb].floatVal= -1;
    strcpy(Simb[nrSimb].charVal , "");
    strcpy(Simb[nrSimb].stingVal , "");
    Simb[nrSimb].vectorIntVal_occupied = 0;
    Simb[nrSimb].vectorFloatVal_occupied = 0;
    for(int i = 0; i< VECTOR_DIMENSION; i++){
        Simb[nrSimb].vectorIntVal[i] = INT_VECTOR_VALUE_STOP;
        Simb[nrSimb].vectorFloatVal[i] = FLOAT_VECTOR_VALUE_STOP;
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
    if(strcmp(dtyp, "classOf")==0){
        //reiteram in tabelul de simboluri pentru a modifca numele variabilelor din clasa
        // luam toate simbolurile ce au flagul de 'inside_object' activ
        int copie_nrSimb = nrSimb -1;
        while(copie_nrSimb > 0 && Simb[copie_nrSimb].inside_object==true){
            //classNume.variabilaInternaNume;
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
void updateINTarray(char numer[], int val, int position){
    int k=verifdecl(numer);
    if(k!=-1)
    {
        Simb[k].init=1;
        /*data in vector devine valabila pana la positia maxima */
        if(position >= Simb[k].vectorIntVal_occupied){
            for( int i = Simb[k].vectorIntVal_occupied; i< position +1; i++){
                //transfrom from value -9999 to 0 so it will be printed in .txt
                Simb[k].vectorIntVal[i] = 0;
            }
            Simb[k].vectorIntVal_occupied = position;
        }
        Simb[k].vectorIntVal[position] = val;
    } 
}
void updateFLOATarray(char numer[], int val, int position){
    int k=verifdecl(numer);
    if(k!=-1)
    {
        Simb[k].init=1;
        /*data in vector devine valabila pana la positia maxima */
        if(position > Simb[k].vectorFloatVal_occupied){
            for( int i = Simb[k].vectorFloatVal_occupied; i< position +1; i++){
                //transfrom from value -9999 to 0 so it will be printed in .txt
                Simb[k].vectorFloatVal[i] = 0;
            }
            Simb[k].vectorFloatVal_occupied = position;
        }
        Simb[k].vectorFloatVal[position] = val;
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

#line 473 "y.tab.c"

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

#line 666 "y.tab.c"

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
  YYSYMBOL_OPEN_SQR_PRTHS = 3,             /* OPEN_SQR_PRTHS  */
  YYSYMBOL_CLOSE_SQR_PRTHS = 4,            /* CLOSE_SQR_PRTHS  */
  YYSYMBOL_CONSTANT = 5,                   /* CONSTANT  */
  YYSYMBOL_EVAL = 6,                       /* EVAL  */
  YYSYMBOL_STRUCTURE = 7,                  /* STRUCTURE  */
  YYSYMBOL_CLASSOF = 8,                    /* CLASSOF  */
  YYSYMBOL_TYPEOF = 9,                     /* TYPEOF  */
  YYSYMBOL_TREQQ = 10,                     /* TREQQ  */
  YYSYMBOL_CLASS_TYP = 11,                 /* CLASS_TYP  */
  YYSYMBOL_OPEN_PRTHS = 12,                /* OPEN_PRTHS  */
  YYSYMBOL_CLOSE_PRTHS = 13,               /* CLOSE_PRTHS  */
  YYSYMBOL_BGIN = 14,                      /* BGIN  */
  YYSYMBOL_END = 15,                       /* END  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_DO = 20,                        /* DO  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_LESS = 23,                      /* LESS  */
  YYSYMBOL_LESSEQ = 24,                    /* LESSEQ  */
  YYSYMBOL_GRT = 25,                       /* GRT  */
  YYSYMBOL_GRTEQ = 26,                     /* GRTEQ  */
  YYSYMBOL_EQ = 27,                        /* EQ  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_PLUS = 31,                      /* PLUS  */
  YYSYMBOL_MINUS = 32,                     /* MINUS  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_MULTIP = 34,                    /* MULTIP  */
  YYSYMBOL_MOD = 35,                       /* MOD  */
  YYSYMBOL_LBRACES = 36,                   /* LBRACES  */
  YYSYMBOL_RBRACES = 37,                   /* RBRACES  */
  YYSYMBOL_LPAR = 38,                      /* LPAR  */
  YYSYMBOL_RPAR = 39,                      /* RPAR  */
  YYSYMBOL_LBRACKET = 40,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 41,                  /* RBRACKET  */
  YYSYMBOL_POINT = 42,                     /* POINT  */
  YYSYMBOL_SINGLE_QUOTES = 43,             /* SINGLE_QUOTES  */
  YYSYMBOL_COMMA = 44,                     /* COMMA  */
  YYSYMBOL_SEMI_COLLON = 45,               /* SEMI_COLLON  */
  YYSYMBOL_PRINT = 46,                     /* PRINT  */
  YYSYMBOL_PRIVAT = 47,                    /* PRIVAT  */
  YYSYMBOL_PUBLIC = 48,                    /* PUBLIC  */
  YYSYMBOL_PROTECTED = 49,                 /* PROTECTED  */
  YYSYMBOL_DOUA_DOUA_PCTE = 50,            /* DOUA_DOUA_PCTE  */
  YYSYMBOL_PRIVATE = 51,                   /* PRIVATE  */
  YYSYMBOL_BOOL_VAL = 52,                  /* BOOL_VAL  */
  YYSYMBOL_INT_NUM = 53,                   /* INT_NUM  */
  YYSYMBOL_REAL_NUM = 54,                  /* REAL_NUM  */
  YYSYMBOL_CHAR_VAL = 55,                  /* CHAR_VAL  */
  YYSYMBOL_STRING_VAL = 56,                /* STRING_VAL  */
  YYSYMBOL_ARRAY_IDENTIF = 57,             /* ARRAY_IDENTIF  */
  YYSYMBOL_VOID = 58,                      /* VOID  */
  YYSYMBOL_INT = 59,                       /* INT  */
  YYSYMBOL_FLOAT = 60,                     /* FLOAT  */
  YYSYMBOL_CHAR = 61,                      /* CHAR  */
  YYSYMBOL_STRING = 62,                    /* STRING  */
  YYSYMBOL_BOOL = 63,                      /* BOOL  */
  YYSYMBOL_IDENTIF = 64,                   /* IDENTIF  */
  YYSYMBOL_65_ = 65,                       /* '+'  */
  YYSYMBOL_66_ = 66,                       /* '-'  */
  YYSYMBOL_67_ = 67,                       /* '*'  */
  YYSYMBOL_68_ = 68,                       /* '/'  */
  YYSYMBOL_69_ = 69,                       /* '%'  */
  YYSYMBOL_70_ = 70,                       /* '{'  */
  YYSYMBOL_71_ = 71,                       /* '}'  */
  YYSYMBOL_72_ = 72,                       /* '['  */
  YYSYMBOL_73_ = 73,                       /* ']'  */
  YYSYMBOL_74_ = 74,                       /* '('  */
  YYSYMBOL_75_ = 75,                       /* ')'  */
  YYSYMBOL_76_ = 76,                       /* ';'  */
  YYSYMBOL_77_ = 77,                       /* ','  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_vartype = 79,                   /* vartype  */
  YYSYMBOL_PROGRAM = 80,                   /* PROGRAM  */
  YYSYMBOL_CLASE = 81,                     /* CLASE  */
  YYSYMBOL_CLASA = 82,                     /* CLASA  */
  YYSYMBOL_CLASABLOC = 83,                 /* CLASABLOC  */
  YYSYMBOL_BLOC = 84,                      /* BLOC  */
  YYSYMBOL_INSTRUCTIUNI = 85,              /* INSTRUCTIUNI  */
  YYSYMBOL_INSTRUCTIUNE = 86,              /* INSTRUCTIUNE  */
  YYSYMBOL_STRUCTURI = 87,                 /* STRUCTURI  */
  YYSYMBOL_STRUCTURA = 88,                 /* STRUCTURA  */
  YYSYMBOL_DECLARATII_IN_OBJECT = 89,      /* DECLARATII_IN_OBJECT  */
  YYSYMBOL_DECLARATIE_IN_OBJ = 90,         /* DECLARATIE_IN_OBJ  */
  YYSYMBOL_DECLARATII = 91,                /* DECLARATII  */
  YYSYMBOL_DECLARATIE = 92                 /* DECLARATIE  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   220

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


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
       2,     2,     2,     2,     2,     2,     2,    69,     2,     2,
      74,    75,    67,    65,    77,    66,     2,    68,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    76,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,     2,    71,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   446,   446,   447,   448,   449,   450,   475,   476,   477,
     478,   492,   493,   496,   517,   518,   519,   520,   525,   527,
     528,   532,   542,   554,   566,   584,   596,   608,   643,   657,
     692,   717,   742,   772,   784,   796,   808,   820,   837,   838,
     843,   855,   856,   860,   871,   885,   898,   917,   930,   943,
     980,  1017,  1066,  1077,  1088,  1105,  1116,  1127,  1180,  1181,
    1185,  1194,  1205,  1216,  1233,  1244,  1255,  1289,  1335,  1369,
    1386,  1403,  1420,  1437,  1454,  1478,  1502,  1531,  1542,  1553,
    1570,  1581,  1592
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
  "\"end of file\"", "error", "\"invalid token\"", "OPEN_SQR_PRTHS",
  "CLOSE_SQR_PRTHS", "CONSTANT", "EVAL", "STRUCTURE", "CLASSOF", "TYPEOF",
  "TREQQ", "CLASS_TYP", "OPEN_PRTHS", "CLOSE_PRTHS", "BGIN", "END", "IF",
  "ELSE", "WHILE", "FOR", "DO", "RETURN", "ASSIGN", "LESS", "LESSEQ",
  "GRT", "GRTEQ", "EQ", "NOT", "AND", "OR", "PLUS", "MINUS", "DIV",
  "MULTIP", "MOD", "LBRACES", "RBRACES", "LPAR", "RPAR", "LBRACKET",
  "RBRACKET", "POINT", "SINGLE_QUOTES", "COMMA", "SEMI_COLLON", "PRINT",
  "PRIVAT", "PUBLIC", "PROTECTED", "DOUA_DOUA_PCTE", "PRIVATE", "BOOL_VAL",
  "INT_NUM", "REAL_NUM", "CHAR_VAL", "STRING_VAL", "ARRAY_IDENTIF", "VOID",
  "INT", "FLOAT", "CHAR", "STRING", "BOOL", "IDENTIF", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'{'", "'}'", "'['", "']'", "'('", "')'", "';'", "','",
  "$accept", "vartype", "PROGRAM", "CLASE", "CLASA", "CLASABLOC", "BLOC",
  "INSTRUCTIUNI", "INSTRUCTIUNE", "STRUCTURI", "STRUCTURA",
  "DECLARATII_IN_OBJECT", "DECLARATIE_IN_OBJ", "DECLARATII", "DECLARATIE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-123)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      15,    -2,  -123,  -123,  -123,  -123,  -123,    14,    -3,     8,
      22,   -49,     9,   -44,   109,   -29,   104,   -24,  -123,    19,
    -123,    16,    -1,    31,    61,   -31,   -16,   -11,  -123,    61,
      15,   -12,  -123,     2,    45,     4,    83,  -123,  -123,  -123,
    -123,  -123,    43,    62,    47,   123,  -123,    80,  -123,    17,
     -52,    27,  -123,  -123,    61,   119,    30,  -123,   -43,  -123,
     113,    34,   122,  -123,   115,   128,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,   169,  -123,  -123,  -123,  -123,  -123,    91,
     146,   133,  -123,   178,  -123,   186,  -123,    61,  -123,   180,
      97,  -123,  -123,    42,  -123,  -123,  -123,  -123,  -123,   181,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,   200,  -123,  -123,
    -123,  -123,  -123,   110,  -123,   190,   138,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,    76,   184,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,   199,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,   142,   144,   199,   134,  -123,
    -123,  -123,   197,   135,  -123,   164,  -123,   163,   201,   109,
    -123,    50,   165,   166,   109,   109,   109,    79,   167,   109,
     109
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      82,     0,     2,     4,     3,     6,     5,     0,     0,     0,
      82,     0,    82,     0,     0,     0,     0,     0,    67,    60,
       1,     0,     0,     0,    18,     0,     0,    82,    38,     0,
      82,     0,    58,     0,     0,     0,     0,    73,    69,    70,
      71,    72,     0,     0,     0,     0,    28,    21,     8,     0,
       0,     0,    19,    39,     0,     0,    82,    59,     0,    51,
      43,     0,     0,    41,     0,     0,    65,    61,    62,    63,
      64,    68,    66,     0,    37,    33,    34,    35,    36,     0,
       0,     0,    28,    21,    20,     0,     7,     0,    57,     0,
       0,    40,    42,     0,    81,    77,    78,    79,    80,     0,
      26,    22,    23,    24,    25,    29,    27,     0,    37,    33,
      34,    35,    36,     0,     9,     0,     0,    48,    44,    45,
      46,    47,    50,    49,    74,    75,    76,     0,     0,    26,
      22,    23,    24,    25,    29,    27,     0,    56,    52,    53,
      54,    55,    30,    31,    32,     0,     0,    10,     0,    30,
      31,    32,     0,     0,    11,    17,    12,     0,     0,     0,
      13,     0,     0,     0,     0,     0,    16,    15,     0,     0,
      14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,     1,  -123,  -123,    71,  -123,   -20,  -123,   195,   208,
      -4,  -122,   -34,     5,     6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    33,     9,   147,   148,   158,    23,    24,    25,    10,
      11,    34,    35,    12,    13
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      62,     8,    17,    54,    17,    82,    26,    58,    20,    55,
      14,    22,    83,     8,    88,    27,     1,    15,    31,    44,
      80,    89,     1,    29,    36,    50,    26,    28,     8,     1,
      50,     8,    32,    31,    85,    56,    16,   161,    45,    81,
      42,    43,   166,   167,    87,    52,    48,   170,     2,     3,
       4,     5,     6,     7,    18,    50,    46,     8,    61,    59,
      53,    19,    31,    47,    57,    65,    60,   115,     2,     3,
       4,     5,     6,     7,     2,     3,     4,     5,     6,     7,
      63,     2,     3,     4,     5,     6,    21,    64,    50,     2,
       3,     4,     5,     6,     7,   124,   125,   126,    91,   162,
      73,   163,    79,    84,     2,     3,     4,     5,     6,     2,
       3,     4,     5,     6,    66,    67,    68,    69,    70,    71,
       2,     3,     4,     5,     6,    49,    72,    62,   168,   142,
     143,   144,    62,    62,    86,    90,    62,    93,     2,     3,
       4,     5,     6,   100,   101,   102,   103,   104,   105,   117,
     118,   119,   120,   121,   122,   106,    37,    38,    39,    40,
      41,   123,   129,   130,   131,   132,   133,   134,     2,     3,
       4,     5,     6,    99,   135,    74,    75,    76,    77,    78,
      94,    95,    96,    97,    98,   108,   109,   110,   111,   112,
     137,   138,   139,   140,   141,   149,   150,   151,    92,   107,
     113,   114,   116,   127,   128,   136,   145,   146,   152,   155,
     154,   156,   157,   159,   160,   164,   165,   169,   153,    51,
      30
};

static const yytype_uint8 yycheck[] =
{
      34,     0,     5,    14,     5,    57,    10,     5,     0,    29,
      12,    10,    64,    12,    57,    10,     7,     3,    12,     3,
       3,    64,     7,    14,    53,    24,    30,    76,    27,     7,
      29,    30,    76,    27,    54,    30,    22,   159,    22,    22,
      64,    22,   164,   165,    14,    76,    15,   169,    59,    60,
      61,    62,    63,    64,    57,    54,    57,    56,    13,    57,
      76,    64,    56,    64,    76,    22,    64,    87,    59,    60,
      61,    62,    63,    64,    59,    60,    61,    62,    63,    64,
      76,    59,    60,    61,    62,    63,    64,     4,    87,    59,
      60,    61,    62,    63,    64,    53,    54,    55,    64,    49,
      53,    51,    22,    76,    59,    60,    61,    62,    63,    59,
      60,    61,    62,    63,    52,    53,    54,    55,    56,    57,
      59,    60,    61,    62,    63,    64,    64,   161,    49,    53,
      54,    55,   166,   167,    15,    22,   170,    22,    59,    60,
      61,    62,    63,    52,    53,    54,    55,    56,    57,    52,
      53,    54,    55,    56,    57,    64,    52,    53,    54,    55,
      56,    64,    52,    53,    54,    55,    56,    57,    59,    60,
      61,    62,    63,     4,    64,    52,    53,    54,    55,    56,
      52,    53,    54,    55,    56,    52,    53,    54,    55,    56,
      52,    53,    54,    55,    56,    53,    54,    55,    76,    53,
      22,    15,    22,    22,     4,    15,    22,     8,    64,    12,
      76,    76,    48,    50,    13,    50,    50,    50,   147,    24,
      12
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    59,    60,    61,    62,    63,    64,    79,    80,
      87,    88,    91,    92,    12,     3,    22,     5,    57,    64,
       0,    64,    79,    84,    85,    86,    88,    91,    76,    14,
      87,    92,    76,    79,    89,    90,    53,    52,    53,    54,
      55,    56,    64,    22,     3,    22,    57,    64,    15,    64,
      79,    86,    76,    76,    14,    84,    91,    76,     5,    57,
      64,    13,    90,    76,     4,    22,    52,    53,    54,    55,
      56,    57,    64,    53,    52,    53,    54,    55,    56,    22,
       3,    22,    57,    64,    76,    84,    15,    14,    57,    64,
      22,    64,    76,    22,    52,    53,    54,    55,    56,     4,
      52,    53,    54,    55,    56,    57,    64,    53,    52,    53,
      54,    55,    56,    22,    15,    84,    22,    52,    53,    54,
      55,    56,    57,    64,    53,    54,    55,    22,     4,    52,
      53,    54,    55,    56,    57,    64,    15,    52,    53,    54,
      55,    56,    53,    54,    55,    22,     8,    81,    82,    53,
      54,    55,    64,    82,    76,    12,    76,    48,    83,    50,
      13,    89,    49,    51,    50,    50,    89,    89,    49,    50,
      89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    78,    79,    79,    79,    79,    79,    80,    80,    80,
      80,    81,    81,    82,    83,    83,    83,    83,    84,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      88,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     4,     3,     5,
       7,     2,     3,     5,     9,     6,     6,     0,     1,     2,
       3,     2,     4,     4,     4,     4,     4,     4,     2,     4,
       6,     6,     6,     3,     3,     3,     3,     3,     2,     3,
       5,     2,     3,     2,     4,     4,     4,     4,     4,     4,
       4,     2,     5,     5,     5,     5,     5,     3,     2,     3,
       2,     4,     4,     4,     4,     4,     4,     2,     4,     3,
       3,     3,     3,     3,     6,     6,     6,     5,     5,     5,
       5,     5,     0
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
  case 13: /* CLASA: CLASSOF IDENTIF OPEN_PRTHS CLASABLOC CLOSE_PRTHS  */
#line 496 "fis.y"
                                                       {
            if(verifdecl((yyvsp[-3].dataTyp))== -1){
                global = CLASS_LEVEL;
                declarare((yyvsp[-3].dataTyp), "classOf", global, 0);


                /* change SCOPE to class to every variable declared inside of this class */
                for(int lll = 1; lll <= nrSimb ; lll++){
                    if (strncmp(Simb[lll].nume, (yyvsp[-3].dataTyp), strlen((yyvsp[-3].dataTyp))) == 0 && Simb[lll].nume[strlen((yyvsp[-3].dataTyp))] == '.'){
                        //printf("Variabila %s ar putea face parte din clasa variabilei %s\n", Simb[lll].nume, $2);
                        Simb[lll].global = CLASS_LEVEL;
                    }
                }
            }
            else{
                printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            }
            global = 0;
        }
#line 1880 "y.tab.c"
    break;

  case 21: /* INSTRUCTIUNE: vartype IDENTIF  */
#line 532 "fis.y"
                    {
        global = 1;
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
#line 1895 "y.tab.c"
    break;

  case 22: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN INT_NUM  */
#line 542 "fis.y"
                                   {
        global = 1;
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 1912 "y.tab.c"
    break;

  case 23: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN REAL_NUM  */
#line 554 "fis.y"
                                    {
        global = 1;
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 1929 "y.tab.c"
    break;

  case 24: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 566 "fis.y"
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
#line 1952 "y.tab.c"
    break;

  case 25: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN STRING_VAL  */
#line 584 "fis.y"
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
#line 1969 "y.tab.c"
    break;

  case 26: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 596 "fis.y"
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
#line 1986 "y.tab.c"
    break;

  case 27: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN IDENTIF  */
#line 608 "fis.y"
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
#line 2026 "y.tab.c"
    break;

  case 28: /* INSTRUCTIUNE: vartype ARRAY_IDENTIF  */
#line 643 "fis.y"
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
#line 2045 "y.tab.c"
    break;

  case 29: /* INSTRUCTIUNE: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 657 "fis.y"
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
#line 2085 "y.tab.c"
    break;

  case 30: /* INSTRUCTIUNE: IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN INT_NUM  */
#line 692 "fis.y"
                                                                   {
            global = 1;
            int store_temp_position = verifdecl((yyvsp[-5].dataTyp));
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                yyerror("eroare");
            }
            else{
                /* check the vector dimensions */
                if(strcmp(Simb[store_temp_position].typ, "int vector") != 0){
                    printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                }
                else{
                    if((yyvsp[-3].intTyp)<0 || (yyvsp[-3].intTyp)>(STRING_DIMENSION-1) || (yyvsp[-3].intTyp)> Simb[store_temp_position].vectorIntVal_occupied){
                        printf("Dimnesiunea %d nu este conforma pentru variabila %s. Eroare la linia :%d \n", (yyvsp[-3].intTyp), Simb[store_temp_position].nume,  yylineno);
                        yyerror("eroare");
                    }
                    else{
                        updateINTarray((yyvsp[-5].dataTyp), (yyvsp[0].intTyp), (yyvsp[-3].intTyp) );
                        //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                    }
                }
            }
            global = 0;
        }
#line 2115 "y.tab.c"
    break;

  case 31: /* INSTRUCTIUNE: IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN REAL_NUM  */
#line 717 "fis.y"
                                                                    {
            global = 1;
            int store_temp_position = verifdecl((yyvsp[-5].dataTyp));
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                yyerror("eroare");
            }
            else{
                /* check the vector dimensions */
                if(strcmp(Simb[store_temp_position].typ, "float vector") != 0){
                    printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                }
                else{
                    if((yyvsp[-3].intTyp)<0 || (yyvsp[-3].intTyp)>(STRING_DIMENSION-1)){
                        printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", (yyvsp[-3].intTyp),  yylineno);
                        yyerror("eroare");
                    }
                    else{
                        updateFLOATarray((yyvsp[-5].dataTyp), (yyvsp[0].floatTyp), (yyvsp[-3].intTyp));
                        //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                    }
                }
            }
            global = 0;
        }
#line 2145 "y.tab.c"
    break;

  case 32: /* INSTRUCTIUNE: IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN CHAR_VAL  */
#line 742 "fis.y"
                                                                    {
            global = 1;
            int store_temp_position = verifdecl((yyvsp[-5].dataTyp));
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                yyerror("eroare");
            }
            else{
                /* check type */
                if(strcmp(Simb[store_temp_position].typ, "string") != 0){
                    printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                }
                else{
                    /* check dimension */
                    if((yyvsp[-3].intTyp)<0 || (yyvsp[-3].intTyp)>(STRING_DIMENSION-1) || (yyvsp[-3].intTyp) > strlen(Simb[store_temp_position].stingVal)){
                        printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", (yyvsp[-3].intTyp),  yylineno);
                    }
                    else{
                        char get_input_temp[STRING_DIMENSION];
                        strcpy(get_input_temp, (yyvsp[0].charTyp));
                        //input as : 'c'
                        Simb[store_temp_position].stingVal[(yyvsp[-3].intTyp)] = get_input_temp[1];

                        //flag de initializat
                        Simb[store_temp_position].init = 1;
                    }
                }
            }
            global = 0;
        }
#line 2180 "y.tab.c"
    break;

  case 33: /* INSTRUCTIUNE: IDENTIF ASSIGN INT_NUM  */
#line 772 "fis.y"
                            {
        global = 1;
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 2197 "y.tab.c"
    break;

  case 34: /* INSTRUCTIUNE: IDENTIF ASSIGN REAL_NUM  */
#line 784 "fis.y"
                             {
        global = 1;
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 2214 "y.tab.c"
    break;

  case 35: /* INSTRUCTIUNE: IDENTIF ASSIGN CHAR_VAL  */
#line 796 "fis.y"
                             {
        global = 1;
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            initializareCHAR((yyvsp[-2].dataTyp), (yyvsp[0].charTyp));
            }
        global = 0;
        }
#line 2231 "y.tab.c"
    break;

  case 36: /* INSTRUCTIUNE: IDENTIF ASSIGN STRING_VAL  */
#line 808 "fis.y"
                               {
        global = 1;
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            initializareSTRING((yyvsp[-2].dataTyp), (yyvsp[0].stringTyp));
            }
        global = 0;
        }
#line 2248 "y.tab.c"
    break;

  case 37: /* INSTRUCTIUNE: IDENTIF ASSIGN BOOL_VAL  */
#line 820 "fis.y"
                             {
        global = 1;
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            initializareBOOL((yyvsp[-2].dataTyp), (yyvsp[0].boolTyp));
            }
        global = 0;
        }
#line 2265 "y.tab.c"
    break;

  case 40: /* STRUCTURA: STRUCTURE OPEN_PRTHS DECLARATII_IN_OBJECT CLOSE_PRTHS IDENTIF  */
#line 843 "fis.y"
                                                                  {
            if(verifdecl((yyvsp[0].dataTyp))== -1){
                declarare((yyvsp[0].dataTyp), "structure", global, 0);
            
            }
            else{
                printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            }
        }
#line 2279 "y.tab.c"
    break;

  case 43: /* DECLARATIE_IN_OBJ: vartype IDENTIF  */
#line 860 "fis.y"
                     {
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
#line 2295 "y.tab.c"
    break;

  case 44: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN INT_NUM  */
#line 871 "fis.y"
                                   {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
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
#line 2314 "y.tab.c"
    break;

  case 45: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN REAL_NUM  */
#line 885 "fis.y"
                                    {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 2332 "y.tab.c"
    break;

  case 46: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 898 "fis.y"
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
#line 2356 "y.tab.c"
    break;

  case 47: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN STRING_VAL  */
#line 917 "fis.y"
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
#line 2374 "y.tab.c"
    break;

  case 48: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 930 "fis.y"
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
#line 2392 "y.tab.c"
    break;

  case 49: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN IDENTIF  */
#line 943 "fis.y"
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
#line 2434 "y.tab.c"
    break;

  case 50: /* DECLARATIE_IN_OBJ: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 980 "fis.y"
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
#line 2476 "y.tab.c"
    break;

  case 51: /* DECLARATIE_IN_OBJ: vartype ARRAY_IDENTIF  */
#line 1017 "fis.y"
                          {
            /* take out the [INT] from name */
            char save_name[STRING_DIMENSION];
            strcpy(save_name, (yyvsp[0].arrayTyp));
            int position_of_start = 0;
            
            /* find the position of "[" and "]" in declaration */
            while(position_of_start < strlen(save_name) && save_name[position_of_start]!='['){
                position_of_start += 1 ;
            }

            /* store the dimension */
            char dimension_temp[STRING_DIMENSION];
            strcpy(dimension_temp, save_name + position_of_start + 1);

            /* now the string is as: "10]". deleting the last "]" */
            dimension_temp[strlen(dimension_temp) - 1] = '\0';
            int dimension_to_declare = atoi(dimension_temp);

            /* take out the "[INT]" from variable name */
            save_name[position_of_start] = '\0';
            //printf("Variable name before: %s. Variable name now: %s and dimension: %d. '[' starts at: %d\n", $2, save_name, dimension_to_declare, position_of_start);

            if(verifdecl(save_name)!=-1){
                printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
                yyerror("eroare");
                }
            else{
                /* spatiu pt vector */
                char to_hold[VECTOR_DIMENSION];
                if(strcmp((yyvsp[-1].dataTyp), "char") == 0){
                    strcpy(to_hold, "string");
                    declarare(save_name, to_hold, global, 0);
                }
                else{
                    strcpy(to_hold, (yyvsp[-1].dataTyp));
                    strcat(to_hold, " vector");
                    declarare(save_name, to_hold, global, 0);
                            
                    /*marcam variabila ca parte dintr-un obiect */
                    Simb[nrSimb].inside_object = true;

                    //initializam sa schimbam default value din array:
                    updateINTarray(save_name, 0, dimension_to_declare);
                    //printf("Variabila este in tab de simb: nume %s tip %s init %d\n", Simb[nrSimb].nume, Simb[nrSimb].typ, Simb[nrSimb].init );
                }
            }
            global = 0;
        }
#line 2530 "y.tab.c"
    break;

  case 52: /* DECLARATIE_IN_OBJ: vartype CONSTANT IDENTIF ASSIGN INT_NUM  */
#line 1066 "fis.y"
                                            {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp) , (yyvsp[-4].dataTyp), global, 1);
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 2546 "y.tab.c"
    break;

  case 53: /* DECLARATIE_IN_OBJ: vartype CONSTANT IDENTIF ASSIGN REAL_NUM  */
#line 1077 "fis.y"
                                             {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 2562 "y.tab.c"
    break;

  case 54: /* DECLARATIE_IN_OBJ: vartype CONSTANT IDENTIF ASSIGN CHAR_VAL  */
#line 1088 "fis.y"
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
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $5 );
            initializareCHAR((yyvsp[-2].dataTyp), (yyvsp[0].charTyp));
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
#line 2584 "y.tab.c"
    break;

  case 55: /* DECLARATIE_IN_OBJ: vartype CONSTANT IDENTIF ASSIGN STRING_VAL  */
#line 1105 "fis.y"
                                                {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            initializareSTRING((yyvsp[-2].dataTyp), (yyvsp[0].stringTyp));
            }
        global = 0;
        }
#line 2600 "y.tab.c"
    break;

  case 56: /* DECLARATIE_IN_OBJ: vartype CONSTANT IDENTIF ASSIGN BOOL_VAL  */
#line 1116 "fis.y"
                                              {
       if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            initializareBOOL((yyvsp[-2].dataTyp), (yyvsp[0].boolTyp));
            } 
        global = 0;
        }
#line 2616 "y.tab.c"
    break;

  case 57: /* DECLARATIE_IN_OBJ: vartype CONSTANT ARRAY_IDENTIF  */
#line 1127 "fis.y"
                                   {
            /* take out the [INT] from name */
            char save_name[STRING_DIMENSION];
            strcpy(save_name, (yyvsp[0].arrayTyp));
            int position_of_start = 0;
            
            /* find the position of "[" and "]" in declaration */
            while(position_of_start < strlen(save_name) && save_name[position_of_start]!='['){
                position_of_start += 1 ;
            }

            /* store the dimension */
            char dimension_temp[STRING_DIMENSION];
            strcpy(dimension_temp, save_name + position_of_start + 1);

            /* now the string is as: "10]". deleting the last "]" */
            dimension_temp[strlen(dimension_temp) - 1] = '\0';
            int dimension_to_declare = atoi(dimension_temp);

            /* take out the "[INT]" from variable name */
            save_name[position_of_start] = '\0';
            //printf("Variable name before: %s. Variable name now: %s and dimension: %d. '[' starts at: %d\n", $3, save_name, dimension_to_declare, position_of_start);

            if(verifdecl(save_name)!=-1){
                printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
                yyerror("eroare");
                }
            else{
                /* spatiu pt vector */
                char to_hold[VECTOR_DIMENSION];
                if(strcmp((yyvsp[-2].dataTyp), "char") == 0){
                    strcpy(to_hold, "string");
                    declarare(save_name, to_hold, global, 1);
                }
                else{
                    strcpy(to_hold, (yyvsp[-2].dataTyp));
                    strcat(to_hold, " vector");
                    declarare(save_name, to_hold, global, 1);
                            
                    /*marcam variabila ca parte dintr-un obiect */
                    Simb[nrSimb].inside_object = true;

                    //initializam sa schimbam default value din array:
                    updateINTarray(save_name, 0, dimension_to_declare);
                    //printf("Variabila este in tab de simb: nume %s tip %s init %d\n", Simb[nrSimb].nume, Simb[nrSimb].typ, Simb[nrSimb].init );
                }
            }
            global = 0;
        }
#line 2670 "y.tab.c"
    break;

  case 60: /* DECLARATIE: vartype IDENTIF  */
#line 1185 "fis.y"
                     {
        if(verifdecl((yyvsp[0].dataTyp))== -1){
            declarare((yyvsp[0].dataTyp), (yyvsp[-1].dataTyp),global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
#line 2684 "y.tab.c"
    break;

  case 61: /* DECLARATIE: vartype IDENTIF ASSIGN INT_NUM  */
#line 1194 "fis.y"
                                   {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 2700 "y.tab.c"
    break;

  case 62: /* DECLARATIE: vartype IDENTIF ASSIGN REAL_NUM  */
#line 1205 "fis.y"
                                    {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-3].dataTyp), global, 0);
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 2716 "y.tab.c"
    break;

  case 63: /* DECLARATIE: vartype IDENTIF ASSIGN CHAR_VAL  */
#line 1216 "fis.y"
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
#line 2738 "y.tab.c"
    break;

  case 64: /* DECLARATIE: vartype IDENTIF ASSIGN STRING_VAL  */
#line 1233 "fis.y"
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
#line 2754 "y.tab.c"
    break;

  case 65: /* DECLARATIE: vartype IDENTIF ASSIGN BOOL_VAL  */
#line 1244 "fis.y"
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
#line 2770 "y.tab.c"
    break;

  case 66: /* DECLARATIE: vartype IDENTIF ASSIGN IDENTIF  */
#line 1255 "fis.y"
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
#line 2809 "y.tab.c"
    break;

  case 67: /* DECLARATIE: vartype ARRAY_IDENTIF  */
#line 1289 "fis.y"
                           {
            /* take out the [INT] from name */
            char save_name[STRING_DIMENSION];
            strcpy(save_name, (yyvsp[0].arrayTyp));
            int position_of_start = 0;
            
            /* find the position of "[" and "]" in declaration */
            while(position_of_start < strlen(save_name) && save_name[position_of_start]!='['){
                position_of_start += 1 ;
            }

            /* store the dimension */
            char dimension_temp[STRING_DIMENSION];
            strcpy(dimension_temp, save_name + position_of_start + 1);

            /* now the string is as: "10]". deleting the last "]" */
            dimension_temp[strlen(dimension_temp) - 1] = '\0';
            int dimension_to_declare = atoi(dimension_temp);

            /* take out the "[INT]" from variable name */
            save_name[position_of_start] = '\0';
            //printf("Variable name before: %s. Variable name now: %s and dimension: %d. '[' starts at: %d\n", $2, save_name, dimension_to_declare, position_of_start);

            if(verifdecl(save_name)!=-1){
                printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
                yyerror("eroare");
                }
            else{
                /* spatiu pt vector */
                char to_hold[VECTOR_DIMENSION];
                if(strcmp((yyvsp[-1].dataTyp), "char") == 0){
                    strcpy(to_hold, "string");
                    declarare(save_name, to_hold, global, 0);
                }
                else{
                    strcpy(to_hold, (yyvsp[-1].dataTyp));
                    strcat(to_hold, " vector");
                    declarare(save_name, to_hold, global, 0);

                    //initializam sa schimbam default value din array:
                    updateINTarray(save_name, 0, dimension_to_declare);
                    //printf("Variabila este in tab de simb: nume %s tip %s init %d\n", Simb[nrSimb].nume, Simb[nrSimb].typ, Simb[nrSimb].init );
                }
            }
            global = 0;
        }
#line 2860 "y.tab.c"
    break;

  case 68: /* DECLARATIE: vartype IDENTIF ASSIGN ARRAY_IDENTIF  */
#line 1335 "fis.y"
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
#line 2899 "y.tab.c"
    break;

  case 69: /* DECLARATIE: IDENTIF ASSIGN INT_NUM  */
#line 1369 "fis.y"
                            {
        int k = verifdecl((yyvsp[-2].dataTyp));
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
                }
            }
        global = 0;
        }
#line 2921 "y.tab.c"
    break;

  case 70: /* DECLARATIE: IDENTIF ASSIGN REAL_NUM  */
#line 1386 "fis.y"
                             {
        int k = verifdecl((yyvsp[-2].dataTyp));
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
                }
            }
        global = 0;
        }
#line 2943 "y.tab.c"
    break;

  case 71: /* DECLARATIE: IDENTIF ASSIGN CHAR_VAL  */
#line 1403 "fis.y"
                             {
        int k = verifdecl((yyvsp[-2].dataTyp));
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareCHAR((yyvsp[-2].dataTyp), (yyvsp[0].charTyp));
                }
            }
        global = 0;
        }
#line 2965 "y.tab.c"
    break;

  case 72: /* DECLARATIE: IDENTIF ASSIGN STRING_VAL  */
#line 1420 "fis.y"
                               {
        int k = verifdecl((yyvsp[-2].dataTyp));
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareSTRING((yyvsp[-2].dataTyp), (yyvsp[0].stringTyp));
                }
            }
        global = 0;
        }
#line 2987 "y.tab.c"
    break;

  case 73: /* DECLARATIE: IDENTIF ASSIGN BOOL_VAL  */
#line 1437 "fis.y"
                             {
        int k = verifdecl((yyvsp[-2].dataTyp));
        if(verifdecl((yyvsp[-2].dataTyp))==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareBOOL((yyvsp[-2].dataTyp), (yyvsp[0].boolTyp));
                }
            }
        global = 0;
        }
#line 3009 "y.tab.c"
    break;

  case 74: /* DECLARATIE: IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN INT_NUM  */
#line 1454 "fis.y"
                                                                   {
            int store_temp_position = verifdecl((yyvsp[-5].dataTyp));
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                yyerror("eroare");
            }
            else{
                /* check the vector dimensions */
                if(strcmp(Simb[store_temp_position].typ, "int vector") != 0){
                    printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                }
                else{
                    if((yyvsp[-3].intTyp)<0 || (yyvsp[-3].intTyp)>(STRING_DIMENSION-1) || (yyvsp[-3].intTyp)> Simb[store_temp_position].vectorIntVal_occupied){
                        printf("Dimnesiunea %d nu este conforma pentru variabila %s. Eroare la linia :%d \n", (yyvsp[-3].intTyp), Simb[store_temp_position].nume,  yylineno);
                        yyerror("eroare");
                    }
                    else{
                        updateINTarray((yyvsp[-5].dataTyp), (yyvsp[0].intTyp), (yyvsp[-3].intTyp) );
                        //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                    }
                }
            }
            global = 0;
        }
#line 3038 "y.tab.c"
    break;

  case 75: /* DECLARATIE: IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN REAL_NUM  */
#line 1478 "fis.y"
                                                                    {
            int store_temp_position = verifdecl((yyvsp[-5].dataTyp));
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                yyerror("eroare");
            }
            else{
                /* check the vector dimensions */
                if(strcmp(Simb[store_temp_position].typ, "float vector") != 0){
                    printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                }
                else{
                    if((yyvsp[-3].intTyp)<0 || (yyvsp[-3].intTyp)>(STRING_DIMENSION-1)){
                        printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", (yyvsp[-3].intTyp),  yylineno);
                        yyerror("eroare");
                    }
                    else{
                        updateFLOATarray((yyvsp[-5].dataTyp), (yyvsp[0].floatTyp), (yyvsp[-3].intTyp));
                        //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                    }
                }
            }
            global = 0;
        }
#line 3067 "y.tab.c"
    break;

  case 76: /* DECLARATIE: IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN CHAR_VAL  */
#line 1502 "fis.y"
                                                                    {
            int store_temp_position = verifdecl((yyvsp[-5].dataTyp));
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                yyerror("eroare");
            }
            else{
                /* check type */
                if(strcmp(Simb[store_temp_position].typ, "string") != 0){
                    printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", (yyvsp[-5].dataTyp),  yylineno);
                }
                else{
                    /* check dimension */
                    if((yyvsp[-3].intTyp)<0 || (yyvsp[-3].intTyp)>(STRING_DIMENSION-1) || (yyvsp[-3].intTyp) > strlen(Simb[store_temp_position].stingVal)){
                        printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", (yyvsp[-3].intTyp),  yylineno);
                    }
                    else{
                        char get_input_temp[STRING_DIMENSION];
                        strcpy(get_input_temp, (yyvsp[0].charTyp));
                        //input as : 'c'
                        Simb[store_temp_position].stingVal[(yyvsp[-3].intTyp)] = get_input_temp[1];

                        //flag de initializat
                        Simb[store_temp_position].init = 1;
                    }
                }
            }
            global = 0;
        }
#line 3101 "y.tab.c"
    break;

  case 77: /* DECLARATIE: vartype CONSTANT IDENTIF ASSIGN INT_NUM  */
#line 1531 "fis.y"
                                             {
        if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp) , (yyvsp[-4].dataTyp), global, 1);
            initializareINT((yyvsp[-2].dataTyp), (yyvsp[0].intTyp));
            }
        global = 0;
        }
#line 3117 "y.tab.c"
    break;

  case 78: /* DECLARATIE: vartype CONSTANT IDENTIF ASSIGN REAL_NUM  */
#line 1542 "fis.y"
                                             {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            initializareFLOAT((yyvsp[-2].dataTyp), (yyvsp[0].floatTyp));
            }
        global = 0;
        }
#line 3133 "y.tab.c"
    break;

  case 79: /* DECLARATIE: vartype CONSTANT IDENTIF ASSIGN CHAR_VAL  */
#line 1553 "fis.y"
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
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $5 );
            initializareCHAR((yyvsp[-2].dataTyp), (yyvsp[0].charTyp));
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
#line 3155 "y.tab.c"
    break;

  case 80: /* DECLARATIE: vartype CONSTANT IDENTIF ASSIGN STRING_VAL  */
#line 1570 "fis.y"
                                                {
         if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            initializareSTRING((yyvsp[-2].dataTyp), (yyvsp[0].stringTyp));
            }
        global = 0;
        }
#line 3171 "y.tab.c"
    break;

  case 81: /* DECLARATIE: vartype CONSTANT IDENTIF ASSIGN BOOL_VAL  */
#line 1581 "fis.y"
                                              {
       if(verifdecl((yyvsp[-2].dataTyp))!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare((yyvsp[-2].dataTyp), (yyvsp[-4].dataTyp), global, 1);
            initializareBOOL((yyvsp[-2].dataTyp), (yyvsp[0].boolTyp));
            } 
        global = 0;
        }
#line 3187 "y.tab.c"
    break;


#line 3191 "y.tab.c"

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

#line 1629 "fis.y"


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
