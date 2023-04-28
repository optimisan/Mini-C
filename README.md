# Mini-C

A compiler for a subset of C, made using lex and yacc.

## Language features

Before we get to my writeup, here is a program that can successfully run:

```c
int factorial(int n)
{
  int a = 1;
  for (int i = 1; i <= n; i = i + 1)
  {
    a = a * i;
  }
  return a;
}
int main()
{
  int start = time();
  char str[] = "Factorial is %d\n";
  for (int i = 1; i < 20; i = i + 1)
  {
    printf(str, factorial(i));
  }
  int end = time();
  int writtenChars = printf("Time taken: %d milliseconds\n", end - start);
  return writtenChars;
}
```

Looks good to me although `factorial` ends up returning negative values due to overflow.
`time()` also returns negative values of the milliseconds since epoch, but the difference is correct.

### Error reporting

The compiler provides the approximate location of the syntax/semantic error in the source file.

**Array out of bounds check**
Array indices are checked at runtime for out-of-bound accesses!

### But how fast is it?

I ran some loops in python and Mini-C, and this is around 3-4 times slower than python.

That means it is horribly slow. But what was I even expecting out of a 6-day project?

Honestly, I thought this shouldn't be _too_ far from python. So why is it slower? Lot of `malloc`'s might be the case.

That brings me to memory management in this compiler.

It's terrible. An amazing display of profligate structures flying around from front to back (almost).

"Why the heck does an integer need a `38 bytes` worth of a structure!? And so the source program only has `0`s in it, there will be a new `38 byte` structure for each one of them, eh?!" Breathtaking, literally. The program does need some space to breathe.

### Types

`int`, `char`, `float` and n-dimensional arrays.

> There is no way to convert between types via implicit or explicit type casts.

#### Arrays

Since there is no dynamic memory allocation, array sizes must be declared explicitly.

Not so fast!

```c
int size = 5;
int array[size];
```

This program works despite it not being at compile time. Why, you ask? Because I didn't make it the 'right' way. That ushers us into the...

#### Technical Debt

It's massive.

Best to not think of it at all.

Out of, uh, header file, out of mind? A vigorous nod here, indeed. I am writing this zero days after (hopefully) finishing this project and I can guarantee I won't know what's happening in the codebase 3 days down the line.

> Out of sight, out of mind; that's the correct one, lest I forget.

### Statements

Almost all math expressions: Do not work on arrays.

Control flow: if-else, for, while

Variable declarations can be aggregated with commas: `int a=3, b=4;`

### Functions

Functions cannot have `void` return type. Only `int`, `char` and `float` can be returned.

> This limitation is only because of the syntax (there is no syntax defined to represent array types). The rest of the pipeline should support array types if type checker passes.

Note that functions cannot be recursive. This means there also cannot be mutually recursive functions and no forward declarations.

Boring, I know.

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
