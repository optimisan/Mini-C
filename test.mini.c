
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util/map.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

char *getlineat(int lineno)
{
  FILE *file = fopen("test.mini.c", "r");
  // read the line `lineno` from file
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  while ((read = getline(&line, &len, file)) != -1)
  {
    if (i == lineno)
    {
      return line;
    }
    i++;
  }
}

void point_at_in_line(int lineno, int from, int to)
{
  // print the line and show a caret from bottom line at position `col`
  char *line = getlineat(lineno);
  // Recover silently and gracefully in invalid inputs
  if (from > to)
  {
    int temp = from;
    from = to;
    to = temp;
  }
  if (strlen(line) < to)
  {
    to = strlen(line);
  }
  if (strlen(line) < from)
  {
    from = strlen(line);
  }
  // print all characters till 'from'
  fprintf(stderr, "%.*s", from, line);
  // color characters enclosed in from-to with red and boldface
  fprintf(stderr, "\e[31;1m%.*s\e[0m", to - from, line + from);
  // print all characters from 'to' till end of line
  fprintf(stderr, "%s", line + to);
  for (int i = 0; i < from - 1; i++)
  {
    fprintf(stderr, " ");
  }
  fprintf(stderr, "\e[32;1m" ANSI_COLOR_RED "~^" ANSI_COLOR_RESET "\n");
}
typedef struct
{
  int a;
} st;
void test(void *a)
{
  printf("got as %d\n", *(int *)a);
}
#define TO_UINTPTR(x) (*(uintptr_t *)(&x))
#define FROM_UINTPTR(x, type) (*(type *)(&x))
hashmap *m;
void store(int reg, uintptr_t value)
{
  int key[] = {reg};
  hashmap_set(m, hashmap_static_arr(key), value);
}

uintptr_t load(int reg)
{
  uintptr_t value;
  int key[] = {reg};
  hashmap_get(m, hashmap_static_arr(key), &value);
  return value;
}
int main()
{
  int a = 10;
  float b = 4.56;
  uintptr_t v1 = TO_UINTPTR(a);
  uintptr_t v2 = TO_UINTPTR(b);
  printf("%f\n", FROM_UINTPTR(v2, float));
}
void testmap()
{
  // point_at_in_line(3, 5, 600);
  // st *a = malloc(sizeof(st));
  // a->a = 10;
  // hashmap *m = hashmap_create();
  // hashmap_get_set(m, "a", 1, (uintptr_t *)&a);
  // st *b;
  // hashmap_get(m, "a", 1, (uintptr_t *)&b);
  // printf("%d", b->a);
  int a = 10;
  float b = 4.56;
  char *str = "asd";
  int temp[] = {12, 2, 3, 4};
  int *arr = malloc(sizeof(int) * 4);
  memcpy(arr, temp, sizeof(int) * 4);
  uintptr_t p = TO_UINTPTR(arr);
  // printf("%d", FROM_UINTPTR(p, int *)[0]);

  m = hashmap_create();
  store(1, TO_UINTPTR(a));
  store(2, TO_UINTPTR(b));
  uintptr_t val = load(1);
  printf("%d", FROM_UINTPTR(val, int));
  return 0;
  int key = 1;
  hashmap_set(m, &key, sizeof(int), TO_UINTPTR(a));
  // uintptr_t val;
  int key2 = 1 - 0 + 4 * 0;
  hashmap_get(m, &key2, sizeof(int), &val);
  printf("%d", FROM_UINTPTR(val, int));
}