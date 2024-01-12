%{
    /*
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define GLOBAL 0
#define MAIN 1
#define FUNCTION 2

#define true 1
#define false 0

extern FILE* yyin;
extern char* yytext;
extern int yylineno;

  struct simboluri {
	char nume[100];//NUME
	char typ[50];//TIP
	int global;//LOCATIE_VAR  
	int costant;//CONSTANT
	int init;// daca variabila are valoare
	int intVal; //VALOARE
	float floatVal;//VALOARE
	char charVal[3];//VALOARE -> 'a'
	char stingVal[256];//VALOARE
	int vectorIntVal[100];//VALOARE
	float vectorFloatVal[100];//VALOARE
    int boolVal;//BOOL VALOARE
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
%}

%union {
  int intTyp;
  float floatTyp;
  char* charTyp;
  char* stringTyp;
  char* dataTyp; // IDENTIF or INT/VOID/FLOAT/CHAR/STRING/BOOL
  char* arrayTyp;
  char* tip_val;
  struct node *astval;
  char* boolTyp;
}

%token  CONSTANT EVAL STRUCTURE CLASS TYPEOF TREQQ CLASS_TYP BGIN END IF ELSE WHILE FOR DO RETURN ASSIGN LESS LESSEQ GRT GRTEQ EQ NOT AND OR PLUS MINUS DIV MULTIP MOD LBRACES RBRACES LPAR RPAR LBRACKET RBRACKET POINT SINGLE_QUOTES COMMA SEMI_COLLON PRINT PRIVAT PUBLIC PROTECTED 

%type <dataTyp> vartype
%type <intTyp> EXPRESIE EXPRESII

%token <boolTyp> BOOL_VAL

%token <intTyp> INT_NUM

%token <floatTyp> REAL_NUM

%token <charTyp> CHAR_VAL

%token <stringTyp> STRING_VAL

//%token <dataTyp> IDENTIF

%token <arrayTyp> ARRAY_IDENTIF

%token <dataTyp> VOID INT FLOAT CHAR STRING BOOL IDENTIF

%left '+' '-'
%left '*' '/' '%'
%left '{' '}' '[' ']' '(' ')' 

//------
%start INSTRUCTIUNI // simbolul de start a gramaticii
//------
%%

vartype: INT
       | CHAR
       | FLOAT
       | BOOL
       | STRING
       ;

EXPRESII: EXPRESIE    
| EXPRESII EXPRESIE    
;

EXPRESIE : EXPRESIE  '+' EXPRESIE  {
        $$ = $1 + $3;
        printf("A ajuns la Expresie + Expresie\n");
    }
	  | EXPRESIE  '-' EXPRESIE {$$ = $1 - $3;}
	  | EXPRESIE '*' EXPRESIE  {$$ = $1 * $3;}
	  | EXPRESIE  '/' EXPRESIE {$$ = $1 / $3;}
      | EXPRESIE  '%' EXPRESIE {$$ = $1 % $3;}
      | INT_NUM {
        $<intTyp>$ = $1;
        printf("A ajuns la Expersie : INT\n");
        }
      | REAL_NUM {
        $<floatTyp>$ = $1;
        printf("A ajuns la Expersie : INT\n");
        }
 ;

INSTRUCTIUNI: INSTRUCTIUNE ';'
	    | INSTRUCTIUNI INSTRUCTIUNE ';'
;

INSTRUCTIUNE: 
    vartype IDENTIF {
        if(verifdecl($2)== -1){
            declarare($2, $1,global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror();
            }
        }
    |vartype IDENTIF ASSIGN INT_NUM{
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror();
            }
        else{
            declarare($2, $1, global, 0);
            initializareINT($2, $4);
            }
        }
    |vartype IDENTIF ASSIGN REAL_NUM{
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror();
            }
        else{
            declarare($2, $1, global, 0);
            initializareFLOAT($2, $4);
            }
        }
    | vartype IDENTIF ASSIGN CHAR_VAL{
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror();
            }
        else if(strlen($4)!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror();
        }
        else{
            declarare($2, $1, global, 0);
            initializareCHAR($2, $4);
            }
        }
    | vartype IDENTIF ASSIGN STRING_VAL{
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror();
            }
        else{
            declarare($2, $1, global, 0);
            initializareSTRING($2, $4);
            }
        }
    | vartype IDENTIF ASSIGN BOOL_VAL{
       if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror();
            }
        else{
            declarare($2, $1, global, 0);
            initializareBOOL($2, $4);
            } 
    }
    ;



VARARG: INT_NUM
      | REAL_NUM
      | CHAR_VAL
      | STRING_VAL
      | BOOL
      | IDENTIF {if(verifdecl($1)==-1){printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);yyerror();}}
      | ARRAY_IDENTIF {if(verifdecl($1)==-1){printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);yyerror();}} 
      | VARARG ',' INT_NUM
      | VARARG ',' REAL_NUM
      | VARARG ',' CHAR_VAL
      | VARARG ',' STRING_VAL
      | VARARG ',' IDENTIF {if(verifdecl($3)==-1){printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);yyerror();}}
      | VARARG ',' ARRAY_IDENTIF {if(verifdecl($3)==-1){printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);yyerror();}}
      |/*null*/
      ;
%%

int errors_occurred = 0;

int yyerror(char * s) {
    errors_occurred++;   
    printf("%s %s %d\n","Syntax ERROR.", ".\nErrors occurred! Current error at line: ", yylineno);
   // printf("%s\n", s);
}

int main(int argc, char** argv) {

    yyin=fopen(argv[1],"r");

    yyparse();
    
    clear_table();
    tabel_sim();
    clear_table2();
    tabel_fun();
    
    if (errors_occurred == 0) {
        printf("-------------------------------------------------------------------------\n"); 
        printf("\n\nNo errors occurred !!! :D \n\n\n"); 
        printf("-------------------------------------------------------------------------\n"); 
    }
};