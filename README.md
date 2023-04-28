# Mini-C

A compiler for a subset of C, made using lex and yacc.

## Language features

### Error reporting

The compiler provides the approximate location of the syntax/semantic error in the source file.

**Array out of bounds check**
Array indices are checked at runtime for out-of-bound accesses!

### Types

`int`, `char`, `float` and n-dimensional arrays.

> There is no way to convert between types via implicit or explicit type casts.

### Statements

Almost all math expressions: Do not work on arrays.

Control flow: if-else, for, while

Variable declarations can be aggregated with commas: `int a=3, b=4;`

### Functions

Functions cannot have `void` return type. Only `int`, `char` and `float` can be returned.

> This limitation is only because of the syntax (there is no syntax defined to represent array types)

#### System functions

As of now, `printf` is the only system function. It works like the 'real' `printf(char* format, ...)` where the first argument must be a character string.

## Running

Run `bash compile.bash` to compile the program. You must have `yacc` and `lex` installed.

Specify a file name as the argument above to compile and run the file:

```bash
> bash compile.bash test.mini.c
```

## Output

The program outputs the three address code in a file creatde by appending `.ir` to source file name. This IR is executed and the output shown on stdout.
