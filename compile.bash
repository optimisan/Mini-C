echo "Compiling"
yacc -d parser.y
lex tokenizer.l
gcc lex.yy.c y.tab.c main.c ./util/token.c ./util/symbol.c ./util/AST.c ./util/map.c -o parser
if [ $# -eq 0 ]
  then
    echo "Compiled"
  else
    ./parser $1
fi