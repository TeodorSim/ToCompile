#!/bin/bash

echo "compiling $1"
rm -f y.tab.h
rm -f y.tab.c
rm -f $1.tab.h
rm -f $1.tab.c
rm -f lex.yy.c
rm -f $1
yacc -d $1.y
flex $1.l
gcc lex.yy.c y.tab.c -o $1

