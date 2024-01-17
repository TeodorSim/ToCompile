%{
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
            if(strcmp(Simb[i].typ, "int vector") == 0 ){;
                char temp_la_temp[STRING_DIMENSION];
                char temp_la_scris[STRING_DIMENSION];
                strcpy(temp_la_scris, " [ ");
                 for(int element_vector = 0; element_vector < Simb[i].vectorIntVal_occupied  ; element_vector++){
                    strcpy(temp_la_temp, "");
                    if(element_vector == Simb[i].vectorIntVal_occupied - 1){
                        sprintf(temp_la_temp," %d ]", Simb[i].vectorIntVal[element_vector]);
                    }
                    else{
                        sprintf(temp_la_temp," %d, ", Simb[i].vectorIntVal[element_vector]);
                    }
                    strcat(temp_la_scris, temp_la_temp);
                }
                fprintf(tabel, " %s ", temp_la_scris);
            }

            if(strcmp(Simb[i].typ, "float vector") == 0 ){
                fprintf(tabel, " [ ");
                char temp_la_temp[STRING_DIMENSION];
                //printf("In TabelSimb; vector %s are Val_occupied : %d\n", Simb[i].nume, Simb[i].vectorFloatVal_occupied);
                for(int element_vector = 0; element_vector < Simb[i].vectorFloatVal_occupied  ; element_vector++){
                    strcpy(temp_la_temp, "");
                    if(element_vector == Simb[i].vectorFloatVal_occupied - 1){
                        sprintf(temp_la_temp, " %f ]", Simb[i].vectorFloatVal[element_vector]);
                        //fprintf(tabel, " %f ]", Simb[i].vectorFloatVal[element_vector]);
                    }
                    else{
                        sprintf(temp_la_temp, " %f, ",Simb[i].vectorFloatVal[element_vector]);
                        //fprintf(tabel, " %f, ", Simb[i].vectorFloatVal[element_vector]);
                    }
                    fprintf(tabel, " %s ", temp_la_temp);
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
char* typeOfff(char n[]){
    printf("   numele:  %s   ", n);
    for(int i=1;i<=nrSimb;i++)
    {
        if(strcmp(Simb[i].nume,n)==0)
        return Simb[i].typ;
    }
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

%token  OPEN_SQR_PRTHS CLOSE_SQR_PRTHS CONSTANT EVAL STRUCTURE CLASSOF TYPEOF TREQQ CLASS_TYP OPEN_PRTHS CLOSE_PRTHS BGIN END IF ELSE WHILE FOR DO RETURN ASSIGN LESS LESSEQ GRT GRTEQ EQ NOT AND OR PLUS MINUS DIV MULTIP MOD LBRACES RBRACES LPAR RPAR LBRACKET RBRACKET POINT SINGLE_QUOTES COMMA SEMI_COLLON PRINT PRIVAT PUBLIC PROTECTED 
%token DOUA_DOUA_PCTE PRIVATE
%type <dataTyp> vartype
%type <intTyp> EXPRESIE EXPRESII

%token <boolTyp> BOOL_VAL

%token <intTyp> INT_NUM

%token <floatTyp> REAL_NUM

%token <charTyp> CHAR_VAL

%token <stringTyp> STRING_VAL

//%token <dataTyp> IDENTIF

//array/ vector
%token <arrayTyp> ARRAY_IDENTIF

%token <dataTyp> VOID INT FLOAT CHAR STRING BOOL IDENTIF

%left '+' '-'
%left '*' '/' '%'
%left '{' '}' '[' ']' '(' ')' 

//------
%start PROGRAM // simbolul de start a gramaticii
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

PROGRAM: DECLARATII BGIN BLOC END
    | STRUCTURI BLOC END
    | STRUCTURI DECLARATII BGIN BLOC END
    | DECLARATII STRUCTURI DECLARATII BGIN BLOC END CLASE DECLARATII
;

//---------------------------------------------------------------
//clase:

/*
classOf className
{
    public::

}
*/

CLASE: CLASA ';'
     | CLASE CLASA ';'
     ;

CLASA: CLASSOF IDENTIF OPEN_PRTHS CLASABLOC CLOSE_PRTHS{
            if(verifdecl($2)== -1){
                global = CLASS_LEVEL;
                declarare($2, "classOf", global, 0);


                /* change SCOPE to class to every variable declared inside of this class */
                for(int lll = 1; lll <= nrSimb ; lll++){
                    if (strncmp(Simb[lll].nume, $2, strlen($2)) == 0 && Simb[lll].nume[strlen($2)] == '.'){
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
    ;

CLASABLOC: PUBLIC DOUA_DOUA_PCTE DECLARATII_IN_OBJECT PRIVATE DOUA_DOUA_PCTE DECLARATII_IN_OBJECT PROTECTED DOUA_DOUA_PCTE DECLARATII_IN_OBJECT
    | PUBLIC DOUA_DOUA_PCTE DECLARATII_IN_OBJECT PRIVATE DOUA_DOUA_PCTE DECLARATII_IN_OBJECT
    | PUBLIC DOUA_DOUA_PCTE DECLARATII_IN_OBJECT PROTECTED DOUA_DOUA_PCTE DECLARATII_IN_OBJECT
    |
    ;

//---------------------------------------------------------------
//bloc de functie
BLOC: INSTRUCTIUNI;

INSTRUCTIUNI: INSTRUCTIUNE ';'
	    | INSTRUCTIUNI INSTRUCTIUNE ';'
;

INSTRUCTIUNE: 
    vartype IDENTIF {
        global = 1;
        if(verifdecl($2)== -1){
            declarare($2, $1,global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
    |vartype IDENTIF ASSIGN INT_NUM{
        global = 1;
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareINT($2, $4);
            }
        global = 0;
        }
    |vartype IDENTIF ASSIGN REAL_NUM{
        global = 1;
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareFLOAT($2, $4);
            }
        global = 0;
        }
    |vartype IDENTIF ASSIGN CHAR_VAL{
        global = 1;
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else if(strlen($4)!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror("eroare");
        }
        else{
            declarare($2, $1, global, 0);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $4 );
            initializareCHAR($2, $4);
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN STRING_VAL{
        global = 1;
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareSTRING($2, $4);
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN BOOL_VAL{
        global = 1;
       if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareBOOL($2, $4);
            } 
        global = 0;
        }
    | vartype IDENTIF ASSIGN IDENTIF{
        global = 1;
        if(verifdecl($2)!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", $2,  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl($4)==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $4,  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit($4)==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", $4, yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp($4, tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp($1, tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare($2, $1, global, 0);
                        copyVal($2, $4);
                        }
                    }
                }
            }
        global = 0;
        }
    | vartype ARRAY_IDENTIF{
        global = 1;
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            /* spatiu pt vector */
            char to_hold[100];
            strcpy(to_hold, $1);
            strcat(to_hold, " vector");
            declarare($2, to_hold, global, 0);
            } 
        }
    | vartype IDENTIF ASSIGN ARRAY_IDENTIF{
        global = 1;
        if(verifdecl($2)!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", $2,  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl($4)==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $4,  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit($4)==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", $4, yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp($4, tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp($1, tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare($2, $1, global, 0);
                        copyVal($2, $4);
                        }
                    }
                }
            }
        global = 0;
        }
    | IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN INT_NUM{
            global = 1;
            int store_temp_position = verifdecl($1);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $1,  yylineno);
                yyerror("eroare");
            }
            else{
                if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }
                else{
                    /* check the vector dimensions */
                    if(strcmp(Simb[store_temp_position].typ, "int vector") != 0){
                        printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", $1,  yylineno);
                    }
                    else{
                        if($3<0 || $3>(STRING_DIMENSION-1) || $3> Simb[store_temp_position].vectorIntVal_occupied){
                            printf("Dimnesiunea %d nu este conforma pentru variabila %s. Eroare la linia :%d \n", $3, Simb[store_temp_position].nume,  yylineno);
                            yyerror("eroare");
                        }
                        else{
                            updateINTarray($1, $6, $3 );
                            //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                        }
                    }
                }
            }
            global = 0;
        }
    | IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN REAL_NUM{
            global = 1;
            int store_temp_position = verifdecl($1);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $1,  yylineno);
                yyerror("eroare");
            }
            else{
                if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }
                else{
                    /* check the vector dimensions */
                    if(strcmp(Simb[store_temp_position].typ, "float vector") != 0){
                        printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", $1,  yylineno);
                    }
                    else{
                        if($3<0 || $3>(STRING_DIMENSION-1)){
                            printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", $3,  yylineno);
                            yyerror("eroare");
                        }
                        else{
                            updateFLOATarray($1, $6, $3);
                            //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                        }
                    }
                }
            }
            global = 0;
        }
    | IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN CHAR_VAL{
            global = 1;
            int store_temp_position = verifdecl($1);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $1,  yylineno);
                yyerror("eroare");
            }
            else{
                if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }
                else{
                    /* check type */
                    if(strcmp(Simb[store_temp_position].typ, "string") != 0){
                        printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", $1,  yylineno);
                    }
                    else{
                        /* check dimension */
                        if($3<0 || $3>(STRING_DIMENSION-1) || $3 > strlen(Simb[store_temp_position].stingVal)){
                            printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", $3,  yylineno);
                        }
                        else{
                            char get_input_temp[STRING_DIMENSION];
                            strcpy(get_input_temp, $6);
                            //input as : 'c'
                            Simb[store_temp_position].stingVal[$3] = get_input_temp[1];

                            //flag de initializat
                            Simb[store_temp_position].init = 1;
                        }
                    }
                }
            }
            global = 0;
        }
    | IDENTIF ASSIGN INT_NUM{
        global = 1;
        int store_temp_position = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }
            else{
                //declarare($2, $1, global, 0);
                initializareINT($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN REAL_NUM{
        global = 1;
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareFLOAT($1, $3);
            }
        }
        global = 0;
        }
    | IDENTIF ASSIGN CHAR_VAL{
        global = 1;
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareCHAR($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN STRING_VAL{
        global = 1;
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareSTRING($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN BOOL_VAL{
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareBOOL($1, $3);
                }
            }
        global = 0;
        }
    | TYPEOF '(' IDENTIF ')'{
            int store_temp_position = verifdecl($3);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $3,  yylineno);
                yyerror("eroare");
            }
            else{
                char type_to_print_temp[STRING_DIMENSION];
                //printf("Tipul de date pentru %s este %s.\n",$3, typeOfff($3 ));
                getTyp($3, type_to_print_temp);
                printf("Tipul de date pentru %s este %s.\n",$3, type_to_print_temp);
            }
        }
    | EVAL '(' IDENTIF ')'{
            int store_temp_position = verifdecl($3);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $3,  yylineno);
                yyerror("eroare");
            }
            else{
                char type_to_print_temp[STRING_DIMENSION];
                char char_to_transfer_temp[STRING_DIMENSION];
                getTyp($3, type_to_print_temp);
                char value_to_print_temp[STRING_DIMENSION];
                
                if (strcmp(Simb[store_temp_position].typ, "int") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %d ", Simb[store_temp_position].intVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }

                if (strcmp(Simb[store_temp_position].typ, "bool") == 0) {
                    if(Simb[store_temp_position].boolVal == true){
                        strcpy(char_to_transfer_temp, " true ");
                    }
                    else{
                        strcpy(char_to_transfer_temp, " false");
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }

                if (strcmp(Simb[store_temp_position].typ, "float") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %f ", Simb[store_temp_position].floatVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }
                
                if (strcmp(Simb[store_temp_position].typ, "string") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", Simb[store_temp_position].stingVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                if (strcmp(Simb[store_temp_position].typ, "char") == 0 ){
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", Simb[store_temp_position].charVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                /* arrays */
                if(strcmp(Simb[store_temp_position].typ, "int vector") == 0 ){
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", " [ ");
                    char temp_la_temp[STRING_DIMENSION];
                    for(int element_vector = 0; element_vector < Simb[store_temp_position].vectorIntVal_occupied  ; element_vector++){
                        strcpy(temp_la_temp, "");
                        if(element_vector == Simb[store_temp_position].vectorIntVal_occupied - 1){
                            sprintf(temp_la_temp, " %d ]", Simb[store_temp_position].vectorIntVal[element_vector]);
                        }
                        else{
                            sprintf(temp_la_temp, " %d, ", Simb[store_temp_position].vectorIntVal[element_vector]);
                        }
                        strcat(char_to_transfer_temp, temp_la_temp);
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                if(strcmp(Simb[store_temp_position].typ, "float vector") == 0 ){
                    strcpy(char_to_transfer_temp, " [ ");
                    char temp_la_temp[STRING_DIMENSION];
                    
                    for(int element_vector = 0; element_vector < Simb[store_temp_position].vectorFloatVal_occupied  ; element_vector++){
                        strcpy(temp_la_temp, "");
                        if(element_vector == Simb[store_temp_position].vectorFloatVal_occupied - 1){
                            sprintf(temp_la_temp, " %f ] ", Simb[store_temp_position].vectorFloatVal[element_vector]);
                        }
                        else{
                            sprintf(temp_la_temp, " %f, ", Simb[store_temp_position].vectorFloatVal[element_vector]);
                        }
                        strcat(char_to_transfer_temp, temp_la_temp );
                }
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }
                printf("Variabile %s stocheaza: %s\n", $3, value_to_print_temp);
            }
        }
    
    ;

//---------------------------------------------------------------
//struct type
STRUCTURI: 
    STRUCTURA ';'
    | STRUCTURI STRUCTURA ';'
;

//structure { decl; } a;
STRUCTURA: 
    STRUCTURE OPEN_PRTHS DECLARATII_IN_OBJECT CLOSE_PRTHS IDENTIF {
            if(verifdecl($5)== -1){
                declarare($5, "structure", global, 0);
            
            }
            else{
                printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            }
        }
;

/* necesar pentru a calcula variabilele interne dintr-un obiect */
DECLARATII_IN_OBJECT: DECLARATIE_IN_OBJ ';'
    | DECLARATII_IN_OBJECT DECLARATIE_IN_OBJ ';'
;

DECLARATIE_IN_OBJ:  
     vartype IDENTIF {
        if(verifdecl($2)== -1){
            declarare($2, $1,global,0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
    |vartype IDENTIF ASSIGN INT_NUM{
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
                printf("inside DECLARATIE_IN_OBJ\n");
            declarare($2, $1, global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareINT($2, $4);
            }
        global = 0;
        }
    |vartype IDENTIF ASSIGN REAL_NUM{
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareFLOAT($2, $4);
            }
        global = 0;
        }
    |vartype IDENTIF ASSIGN CHAR_VAL{
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else if(strlen($4)!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror("eroare");
        }
        else{
            declarare($2, $1, global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $4 );
            initializareCHAR($2, $4);
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN STRING_VAL{
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareSTRING($2, $4);
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN BOOL_VAL{
       if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            /*marcam variabila ca parte dintr-un obiect */
            Simb[nrSimb].inside_object = true;
            initializareBOOL($2, $4);
            } 
        global = 0;
        }
    | vartype IDENTIF ASSIGN IDENTIF{
        if(verifdecl($2)!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", $2,  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl($4)==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $4,  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit($4)==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", $4, yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp($4, tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp($1, tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare($2, $1, global, 0);
                        
                        /*marcam variabila ca parte dintr-un obiect */
                        Simb[nrSimb].inside_object = true;
                        copyVal($2, $4);
                        }
                    }
                }
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN ARRAY_IDENTIF{
        if(verifdecl($2)!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", $2,  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl($4)==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $4,  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit($4)==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", $4, yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp($4, tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp($1, tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare($2, $1, global, 0);
                        
                        /*marcam variabila ca parte dintr-un obiect */
                        Simb[nrSimb].inside_object = true;
                        copyVal($2, $4);
                        }
                    }
                }
            }
        global = 0;
        }
    |vartype ARRAY_IDENTIF{
            /* take out the [INT] from name */
            char save_name[STRING_DIMENSION];
            strcpy(save_name, $2);
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
                if(strcmp($1, "char") == 0){
                    strcpy(to_hold, "string");
                    declarare(save_name, to_hold, global, 0);
                }
                else{
                    strcpy(to_hold, $1);
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
    |vartype CONSTANT IDENTIF ASSIGN INT_NUM{
        if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3 , $1, global, 1);
            initializareINT($3, $5);
            }
        global = 0;
        }
    |vartype CONSTANT IDENTIF ASSIGN REAL_NUM{
         if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3, $1, global, 1);
            initializareFLOAT($3, $5);
            }
        global = 0;
        }
    |vartype CONSTANT IDENTIF ASSIGN CHAR_VAL{
        if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else if(strlen($5)!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror("eroare");
        }
        else{
            declarare($3, $1, global, 1);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $5 );
            initializareCHAR($3, $5);
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
    | vartype CONSTANT IDENTIF ASSIGN STRING_VAL{
         if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3, $1, global, 1);
            initializareSTRING($3, $5);
            }
        global = 0;
        }
    | vartype CONSTANT IDENTIF ASSIGN BOOL_VAL{
       if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3, $1, global, 1);
            initializareBOOL($3, $5);
            } 
        global = 0;
        }
    | vartype CONSTANT ARRAY_IDENTIF{
            /* take out the [INT] from name */
            char save_name[STRING_DIMENSION];
            strcpy(save_name, $3);
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
                if(strcmp($1, "char") == 0){
                    strcpy(to_hold, "string");
                    declarare(save_name, to_hold, global, 1);
                }
                else{
                    strcpy(to_hold, $1);
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
    | TYPEOF '(' IDENTIF ')'{
            int store_temp_position = verifdecl($3);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $3,  yylineno);
                yyerror("eroare");
            }
            else{
                char type_to_print_temp[STRING_DIMENSION];
                //printf("Tipul de date pentru %s este %s.\n",$3, typeOfff($3 ));
                getTyp($3, type_to_print_temp);
                printf("Tipul de date pentru %s este %s.\n",$3, type_to_print_temp);
            }
        }
    | EVAL '(' IDENTIF ')'{
            int store_temp_position = verifdecl($3);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $3,  yylineno);
                yyerror("eroare");
            }
            else{
                char type_to_print_temp[STRING_DIMENSION];
                char char_to_transfer_temp[STRING_DIMENSION];
                getTyp($3, type_to_print_temp);
                char value_to_print_temp[STRING_DIMENSION];
                
                if (strcmp(Simb[store_temp_position].typ, "int") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %d ", Simb[store_temp_position].intVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }

                if (strcmp(Simb[store_temp_position].typ, "bool") == 0) {
                    if(Simb[store_temp_position].boolVal == true){
                        strcpy(char_to_transfer_temp, " true ");
                    }
                    else{
                        strcpy(char_to_transfer_temp, " false");
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }

                if (strcmp(Simb[store_temp_position].typ, "float") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %f ", Simb[store_temp_position].floatVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }
                
                if (strcmp(Simb[store_temp_position].typ, "string") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", Simb[store_temp_position].stingVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                if (strcmp(Simb[store_temp_position].typ, "char") == 0 ){
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", Simb[store_temp_position].charVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                /* arrays */
                if(strcmp(Simb[store_temp_position].typ, "int vector") == 0 ){
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", " [ ");
                    printf("Simb[store_temp_position].vectorIntVal_occupied: %d", Simb[store_temp_position].vectorIntVal_occupied);
                    for(int element_vector = 0; element_vector < Simb[store_temp_position].vectorIntVal_occupied  ; element_vector++){
                        if(element_vector == Simb[store_temp_position].vectorIntVal_occupied - 1){
                            sprintf(char_to_transfer_temp, " %d ]", Simb[store_temp_position].vectorIntVal[element_vector]);
                        }
                        else{
                            sprintf(char_to_transfer_temp, " %d, ", Simb[store_temp_position].vectorIntVal[element_vector]);
                        }
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                if(strcmp(Simb[store_temp_position].typ, "float vector") == 0 ){
                    strcpy(char_to_transfer_temp, " [ ");
                    for(int element_vector = 0; element_vector < Simb[store_temp_position].vectorFloatVal_occupied  ; element_vector++){
                        if(element_vector == Simb[store_temp_position].vectorFloatVal_occupied - 1){
                            sprintf(char_to_transfer_temp, " %f ] ", Simb[store_temp_position].vectorFloatVal[element_vector]);
                        }
                        else{
                            sprintf(char_to_transfer_temp, " %f, ", Simb[store_temp_position].vectorFloatVal[element_vector]);
                        }
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }
                printf("Variabile %s stocheaza: %s\n", $3, value_to_print_temp);
            }
        }
    
    
;
//---------------------------------------------------------------
	
DECLARATII : DECLARATIE ';' 
| DECLARATII DECLARATIE ';'
;

DECLARATIE: 
     vartype IDENTIF {
        if(verifdecl($2)== -1){
            declarare($2, $1,global,0);
        } 
        else {
            printf("Variabila a fost deja declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
    |vartype IDENTIF ASSIGN INT_NUM{
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareINT($2, $4);
            }
        global = 0;
        }
    |vartype IDENTIF ASSIGN REAL_NUM{
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareFLOAT($2, $4);
            }
        global = 0;
        }
    |vartype IDENTIF ASSIGN CHAR_VAL{
        if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else if(strlen($4)!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror("eroare");
        }
        else{
            declarare($2, $1, global, 0);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $4 );
            initializareCHAR($2, $4);
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN STRING_VAL{
         if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareSTRING($2, $4);
            }
        global = 0;
        }
    | vartype IDENTIF ASSIGN BOOL_VAL{
       if(verifdecl($2)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($2, $1, global, 0);
            initializareBOOL($2, $4);
            } 
        global = 0;
        }
    | vartype IDENTIF ASSIGN IDENTIF{
            if(verifdecl($2)!=-1){
                printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", $2,  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifdecl($4)==-1){
                    printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $4,  yylineno);
                    yyerror("eroare");
                    }
                else{
                    if(verifinit($4)==-1){
                        printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", $4, yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* verificare variabilele sunt de acelasi tip */
                        char tip_var_second[100];
                        getTyp($4, tip_var_second);
                        //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                        if(strcmp($1, tip_var_second)!=0){
                            printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                            yyerror("eroare");
                            }
                        else{
                            /* declarare variabila $1 */
                            declarare($2, $1, global, 0);
                            copyVal($2, $4);
                            }
                        }
                    }
                }
            global = 0;
        }
    | vartype ARRAY_IDENTIF{
            /* take out the [INT] from name */
            char save_name[STRING_DIMENSION];
            strcpy(save_name, $2);
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
                if(strcmp($1, "char") == 0){
                    strcpy(to_hold, "string");
                    declarare(save_name, to_hold, global, 0);
                }
                else{
                    strcpy(to_hold, $1);
                    strcat(to_hold, " vector");
                    declarare(save_name, to_hold, global, 0);

                    //initializam sa schimbam default value din array:
                    updateINTarray(save_name, 0, dimension_to_declare);
                    //printf("Variabila este in tab de simb: nume %s tip %s init %d\n", Simb[nrSimb].nume, Simb[nrSimb].typ, Simb[nrSimb].init );
                }
            }
            global = 0;
        }
    | vartype IDENTIF ASSIGN ARRAY_IDENTIF{
        if(verifdecl($2)!=-1){
            printf("Variabila %s a fost declarata deja. Eroare la linia :%d \n", $2,  yylineno);
            yyerror("eroare");
            }
        else{
            if(verifdecl($4)==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $4,  yylineno);
                yyerror("eroare");
                }
            else{
                if(verifinit($4)==-1){
                    printf("Variabila %s nu a fost initializata. Eroare la linia :%d\n", $4, yylineno);
                    yyerror("eroare");
                    }
                else{
                    /* verificare variabilele sunt de acelasi tip */
                    char tip_var_second[100];
                    getTyp($4, tip_var_second);
                    //printf("tip $2: '%s'\ntip $4: '%s'\n", $1, tip_var_second);
                    if(strcmp($1, tip_var_second)!=0){
                        printf("Variabilele trebuie sa fie de acelasi tip. Eroare la linia :%d\n", yylineno);
                        yyerror("eroare");
                        }
                    else{
                        /* declarare variabila $1 */
                        declarare($2, $1, global, 0);
                        copyVal($2, $4);
                        }
                    }
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN INT_NUM{
        int k = verifdecl($1);
        int store_temp_position = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }
            else{
                //declarare($2, $1, global, 0);
                initializareINT($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN REAL_NUM{
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
            initializareFLOAT($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN CHAR_VAL{
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareCHAR($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN STRING_VAL{
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareSTRING($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF ASSIGN BOOL_VAL{
        int k = verifdecl($1);
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            //declarare($2, $1, global, 0);
            if(Simb[k].constant == 1){
                printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[k].nume, yylineno);
                yyerror("eroare");
            }else{
                initializareBOOL($1, $3);
                }
            }
        global = 0;
        }
    | IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN INT_NUM{
            int store_temp_position = verifdecl($1);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $1,  yylineno);
                yyerror("eroare");
            }
            else{
                if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }else{
                    /* check the vector dimensions */
                    if(strcmp(Simb[store_temp_position].typ, "int vector") != 0){
                        printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", $1,  yylineno);
                    }
                    else{
                        if($3<0 || $3>(STRING_DIMENSION-1) || $3> Simb[store_temp_position].vectorIntVal_occupied){
                            printf("Dimnesiunea %d nu este conforma pentru variabila %s. Eroare la linia :%d \n", $3, Simb[store_temp_position].nume,  yylineno);
                            yyerror("eroare");
                        }
                        else{
                            updateINTarray($1, $6, $3 );
                            //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                        }
                    }
                }
            }
            global = 0;
        }
    | IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN REAL_NUM{
            int store_temp_position = verifdecl($1);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $1,  yylineno);
                yyerror("eroare");
            }
            else{
                if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }else{
                    /* check the vector dimensions */
                    if(strcmp(Simb[store_temp_position].typ, "float vector") != 0){
                        printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", $1,  yylineno);
                    }
                    else{
                        if($3<0 || $3>(STRING_DIMENSION-1)){
                            printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", $3,  yylineno);
                            yyerror("eroare");
                        }
                        else{
                            updateFLOATarray($1, $6, $3);
                            //printf("Pozitia max din vector nume %s este acum: %d. Pozitia trimisa acum: %d\n", Simb[store_temp_position].nume, Simb[store_temp_position].vectorIntVal_occupied, $3);
                        }
                    }
                }
            }
            global = 0;
        }
    | IDENTIF OPEN_SQR_PRTHS INT_NUM CLOSE_SQR_PRTHS ASSIGN CHAR_VAL{
            int store_temp_position = verifdecl($1);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $1,  yylineno);
                yyerror("eroare");
            }
            else{
                if(Simb[store_temp_position].constant == 1){
                    printf("Variabila %s este de tip constant! Nu poate fi suprascrisa. Eroare la linia :%d \n", Simb[store_temp_position].nume, yylineno);
                    yyerror("eroare");
                }
                else{
                    /* check type */
                    if(strcmp(Simb[store_temp_position].typ, "string") != 0){
                        printf("Variabila %s nu este de tip string. Eroare la linia :%d \n", $1,  yylineno);
                    }
                    else{
                        /* check dimension */
                        if($3<0 || $3>(STRING_DIMENSION-1) || $3 > strlen(Simb[store_temp_position].stingVal)){
                            printf("Dimnesiunea %d nu este conforma. Eroare la linia :%d \n", $3,  yylineno);
                            }
                        else{
                            char get_input_temp[STRING_DIMENSION];
                            strcpy(get_input_temp, $6);
                            //input as : 'c'
                            Simb[store_temp_position].stingVal[$3] = get_input_temp[1];

                            //flag de initializat
                            Simb[store_temp_position].init = 1;
                            }
                        }
                    }
                }
            global = 0;
        }
    | vartype CONSTANT IDENTIF ASSIGN INT_NUM{
        if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3 , $1, global, 1);
            initializareINT($3, $5);
            }
        global = 0;
        }
    |vartype CONSTANT IDENTIF ASSIGN REAL_NUM{
         if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3, $1, global, 1);
            initializareFLOAT($3, $5);
            }
        global = 0;
        }
    |vartype CONSTANT IDENTIF ASSIGN CHAR_VAL{
        if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else if(strlen($5)!=3){
            printf("Tipul de date accepta un caracter, nu un string. Erroare la linia :%d \n", yylineno);
            yyerror("eroare");
        }
        else{
            declarare($3, $1, global, 1);
            //printf("vartype IDENTIF ASSIGN CHAR_VAL are char_val: %s\n", $5 );
            initializareCHAR($3, $5);
           // printf("vartype IDENTIF ASSIGN CHAR_VA() pt Simb[%d].charVal: '%s'.\n", 7,Simb[7].charVal );
            }
        global = 0;
        }
    | vartype CONSTANT IDENTIF ASSIGN STRING_VAL{
         if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3, $1, global, 1);
            initializareSTRING($3, $5);
            }
        global = 0;
        }
    | vartype CONSTANT IDENTIF ASSIGN BOOL_VAL{
       if(verifdecl($3)!=-1){
            printf("Variabila a fost declarata deja. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        else{
            declarare($3, $1, global, 1);
            initializareBOOL($3, $5);
            } 
        global = 0;
        }
    | TYPEOF '(' IDENTIF ')'{
            int store_temp_position = verifdecl($3);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $3,  yylineno);
                yyerror("eroare");
            }
            else{
                char type_to_print_temp[STRING_DIMENSION];
                //printf("Tipul de date pentru %s este %s.\n",$3, typeOfff($3 ));
                getTyp($3, type_to_print_temp);
                printf("Tipul de date pentru %s este %s.\n",$3, type_to_print_temp);
            }
        }
    | EVAL '(' IDENTIF ')'{
            int store_temp_position = verifdecl($3);
            if(store_temp_position ==-1){
                printf("Variabila %s nu a fost declarata deja. Eroare la linia :%d \n", $3,  yylineno);
                yyerror("eroare");
            }
            else{
                char type_to_print_temp[STRING_DIMENSION];
                char char_to_transfer_temp[STRING_DIMENSION];
                getTyp($3, type_to_print_temp);
                char value_to_print_temp[STRING_DIMENSION];

                /* class or struct fara nimic */
                if (strcmp(Simb[store_temp_position].typ, "classOf") == 0 || 
                strcmp(Simb[store_temp_position].typ, "structure") == 0 ) 
                {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", Simb[store_temp_position].typ);
                    strcpy(value_to_print_temp, "Tipul: ");
                    strcat(value_to_print_temp, char_to_transfer_temp);
                    strcat(value_to_print_temp, " .Prin urmare, nu poate fi afisata o valoare.");
                }
                
                if (strcmp(Simb[store_temp_position].typ, "int") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %d ", Simb[store_temp_position].intVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }

                if (strcmp(Simb[store_temp_position].typ, "bool") == 0) {
                    if(Simb[store_temp_position].boolVal == true){
                        strcpy(char_to_transfer_temp, " true ");
                    }
                    else{
                        strcpy(char_to_transfer_temp, " false");
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }

                if (strcmp(Simb[store_temp_position].typ, "float") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %f ", Simb[store_temp_position].floatVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp);
                }
                
                if (strcmp(Simb[store_temp_position].typ, "string") == 0) {
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %f ", Simb[store_temp_position].stingVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                if (strcmp(Simb[store_temp_position].typ, "char") == 0 ){
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", Simb[store_temp_position].charVal);
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                /* arrays */
                if(strcmp(Simb[store_temp_position].typ, "int vector") == 0 ){
                    strcpy(char_to_transfer_temp, "");
                    sprintf(char_to_transfer_temp, " %s ", " [ ");
                    char temp_la_temp[STRING_DIMENSION];
                    
                    for(int element_vector = 0; element_vector < Simb[store_temp_position].vectorIntVal_occupied  ; element_vector++){
                        strcpy(temp_la_temp, "");
                        if(element_vector == Simb[store_temp_position].vectorIntVal_occupied - 1){
                            sprintf(temp_la_temp, " %d ]", Simb[store_temp_position].vectorIntVal[element_vector]);
                        }
                        else{
                            sprintf(temp_la_temp, " %d, ", Simb[store_temp_position].vectorIntVal[element_vector]);
                        }

                        strcat(char_to_transfer_temp, temp_la_temp );
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }

                if(strcmp(Simb[store_temp_position].typ, "float vector") == 0 ){
                    strcpy(char_to_transfer_temp, " [ ");
                    char temp_la_temp[STRING_DIMENSION];
                    
                    for(int element_vector = 0; element_vector < Simb[store_temp_position].vectorFloatVal_occupied  ; element_vector++){
                        strcpy(temp_la_temp, "");
                        if(element_vector == Simb[store_temp_position].vectorFloatVal_occupied - 1){
                            sprintf(temp_la_temp, " %f ] ", Simb[store_temp_position].vectorFloatVal[element_vector]);
                        }
                        else{
                            sprintf(temp_la_temp, " %f, ", Simb[store_temp_position].vectorFloatVal[element_vector]);
                        }

                        strcat(char_to_transfer_temp, temp_la_temp );
                    }
                    strcpy(value_to_print_temp, char_to_transfer_temp );
                }
                printf("Variabile %s stocheaza: %s\n", $3, value_to_print_temp);
            }
        }
    
    ;


VARARG: INT_NUM
      | REAL_NUM
      | CHAR_VAL
      | STRING_VAL
      | BOOL
      | IDENTIF {
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");}
            }
      | ARRAY_IDENTIF {
        if(verifdecl($1)==-1){
            printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");}
        } 
      | VARARG ',' INT_NUM
      | VARARG ',' REAL_NUM
      | VARARG ',' CHAR_VAL
      | VARARG ',' STRING_VAL
      | VARARG ',' IDENTIF {
        if(verifdecl($3)==-1){
            printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
      | VARARG ',' ARRAY_IDENTIF {
        if(verifdecl($3)==-1){
            printf("Variabila nu a fost declarata. Eroare la linia :%d \n", yylineno);
            yyerror("eroare");
            }
        }
      |/*null*/
      ;
%%

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