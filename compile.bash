yacc -d parser.y
lex tokenizer.l
gcc lex.yy.c y.tab.c -o parser