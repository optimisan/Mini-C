echo "Compiling"
yacc -d parser.y
lex tokenizer.l
if gcc lex.yy.c y.tab.c main.c ./util/token.c ./util/symbol.c ./util/AST.c ./util/map.c ./backend/backend.c ./backend/ir.c ./backend/irgen.c ./backend/built-in-functions.c ./vm/vm.c ./util/options.c -o compiler -lm ; then
  if [ $# -eq 0 ]
    then
      echo -e "\u001b[1m\u001b[32mCompilation successful\u001b[0m"
    else
      ./compiler $1
  fi
else
  echo -e "\u001b[1m\u001b[31mCompilation failed\u001b[0m"
fi