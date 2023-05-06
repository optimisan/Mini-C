#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* Flag set by ‘--verbose’. */
int dumpIR = 0, dumpAST = 0, dumpTokens = 0;

/**
 * @brief Parse command line options
 *
 * Available options:
 * -h, --help
 * --dump-ir
 * --dump-ast
 * --dump-tokens
 *
 * @param argc
 * @param argv
 * @return char* Returns the filename of the source code.
 */
char *parseOptions(int argc, char **argv)
{
  int c;

  while (1)
  {
    static struct option long_options[] =
        {
            /* These options set a flag. */
            {"dump-ir", no_argument, &dumpIR, 1},
            {"dump-ast", no_argument, &dumpAST, 1},
            {"dump-tokens", no_argument, &dumpTokens, 1},
            {0, 0, 0, 0}};
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "h",
                    long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c)
    {
    case 0:
      /* If this option set a flag, do nothing else now. */
      // if (long_options[option_index].flag != 0)
      //   break;
      // printf("option %s", long_options[option_index].name);
      // if (optarg)
      //   printf(" with arg %s", optarg);
      // printf("\n");
      break;

    case 'h':
      // print help
      printf("Usage: %s [options] <filename>\n", argv[0]);
      printf("Options:\n");
      printf("  -h, --help\t\tPrint this help message\n");
      printf("  --dump-ir\t\tDump IR\n");
      printf("  --dump-ast\t\tDump AST\n");
      printf("  --dump-tokens\t\tDump tokens\n");
      exit(0);
      break;

    case '?':
      /* getopt_long already printed an error message. */
      break;

    default:
      abort();
    }
  }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  if (dumpIR)
    puts("dumpIR is set");
  if (dumpAST)
    puts("dumpAST is set");
  if (dumpTokens)
    puts("dumpTokens is set");
  /* Print any remaining command line arguments (not options). */

  if (optind == argc - 1)
    return argv[optind];
  else
  {
    printf("Usage: %s [options] <filename>\n", argv[0]);
    printf("Options:\n");
    printf("  -h, --help\t\tPrint this help message\n");
    printf("  --dump-ir\t\tDump IR\n");
    printf("  --dump-ast\t\tDump AST\n");
    printf("  --dump-tokens\t\tDump tokens\n");
    exit(1);
  }
  // putchar('\n');
}