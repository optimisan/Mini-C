# Mini-C

A compiler for a subset of C, made using lex and yacc.

## Language features

1. Type: int, float, char
2. Basic statements: expression statement, assignment statements, and compound statements, declaration statement.
3. Control and looping statements: if statement, for statement, while statement, and
   switch statement. (note that nesting of these statements is also possible.)
4. System functions: printf and scanf statements.
5. Other: Variables, arrays, and function

The syntax for the above is same as in C language. The structure of the input program is also same as a C program.

## Running

Run `bash compile.bash` to compile the program. You must have `yacc` and `lex` installed.

Specify a file name as the argument above to compile and run the file:

```bash
> bash compile.bash test.mini.c
```

## Output

The program outputs the three address code in a file creatde by appending `.ir` to source file name. This IR is executed and the output shown on stdout.
