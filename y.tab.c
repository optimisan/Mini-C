/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "./util/AST.h"
#include "./util/symbol.h"
#include "./util/token.h"
#include "./backend/backend.h"

char *currentFileName;
Type* currentFunctionType;
extern int level;
extern int lineno, col;
int templineno, tempcol;

int yyerror(char *s);
Symbol* getSymbol(char* name, SymbolTable* table, Coordinate src, char* format, ...);
void compileError(Coordinate pos, int lexemeLength, char *format, ...);
void errorMessage(Coordinate pos, int lexemeLength, char *format, ...);
int typeCheckAssign(TypeEnum t1, TypeEnum t2);
TypeEnum typeWiden(TypeEnum t1, TypeEnum t2);
void typeCheckUnary(Node* t);
void typeCheckArrayInitialiser(Type* elementType, Node* expr);

Node* param_list_node, *funcBodyNode;
int yylex();

#line 100 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    K_INT = 258,                   /* K_INT  */
    K_FLOAT = 259,                 /* K_FLOAT  */
    K_CHAR = 260,                  /* K_CHAR  */
    FOR = 261,                     /* FOR  */
    WHILE = 262,                   /* WHILE  */
    ELSE = 263,                    /* ELSE  */
    IF = 264,                      /* IF  */
    SWITCH = 265,                  /* SWITCH  */
    CASE = 266,                    /* CASE  */
    RETURN = 267,                  /* RETURN  */
    CONTINUE = 268,                /* CONTINUE  */
    BREAK = 269,                   /* BREAK  */
    DEFAULT = 270,                 /* DEFAULT  */
    INTEGER = 271,                 /* INTEGER  */
    FLOAT = 272,                   /* FLOAT  */
    CHARACTER = 273,               /* CHARACTER  */
    STRING = 274,                  /* STRING  */
    PLUS_ASSIGN = 275,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 276,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 277,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 278,            /* SLASH_ASSIGN  */
    MOD_ASSIGN = 279,              /* MOD_ASSIGN  */
    IDENTIFIER = 280,              /* IDENTIFIER  */
    ERROR = 281,                   /* ERROR  */
    EOF_TOKEN = 282,               /* EOF_TOKEN  */
    IFX = 283,                     /* IFX  */
    AND = 284,                     /* AND  */
    OR = 285,                      /* OR  */
    GE = 286,                      /* GE  */
    LE = 287,                      /* LE  */
    EQ = 288,                      /* EQ  */
    NE = 289,                      /* NE  */
    INC = 290,                     /* INC  */
    DEC = 291,                     /* DEC  */
    UMINUS = 292,                  /* UMINUS  */
    ARR = 293                      /* ARR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define K_INT 258
#define K_FLOAT 259
#define K_CHAR 260
#define FOR 261
#define WHILE 262
#define ELSE 263
#define IF 264
#define SWITCH 265
#define CASE 266
#define RETURN 267
#define CONTINUE 268
#define BREAK 269
#define DEFAULT 270
#define INTEGER 271
#define FLOAT 272
#define CHARACTER 273
#define STRING 274
#define PLUS_ASSIGN 275
#define MINUS_ASSIGN 276
#define STAR_ASSIGN 277
#define SLASH_ASSIGN 278
#define MOD_ASSIGN 279
#define IDENTIFIER 280
#define ERROR 281
#define EOF_TOKEN 282
#define IFX 283
#define AND 284
#define OR 285
#define GE 286
#define LE 287
#define EQ 288
#define NE 289
#define INC 290
#define DEC 291
#define UMINUS 292
#define ARR 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "parser.y"

    int iValue;
    float fValue;
    char* sValue;
    IdStruct id;
    char cValue;
    int* sizes;
    Node* node;

#line 239 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_K_INT = 3,                      /* K_INT  */
  YYSYMBOL_K_FLOAT = 4,                    /* K_FLOAT  */
  YYSYMBOL_K_CHAR = 5,                     /* K_CHAR  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_SWITCH = 10,                    /* SWITCH  */
  YYSYMBOL_CASE = 11,                      /* CASE  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 14,                     /* BREAK  */
  YYSYMBOL_DEFAULT = 15,                   /* DEFAULT  */
  YYSYMBOL_INTEGER = 16,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 17,                     /* FLOAT  */
  YYSYMBOL_CHARACTER = 18,                 /* CHARACTER  */
  YYSYMBOL_STRING = 19,                    /* STRING  */
  YYSYMBOL_PLUS_ASSIGN = 20,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 21,              /* MINUS_ASSIGN  */
  YYSYMBOL_STAR_ASSIGN = 22,               /* STAR_ASSIGN  */
  YYSYMBOL_SLASH_ASSIGN = 23,              /* SLASH_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 24,                /* MOD_ASSIGN  */
  YYSYMBOL_IDENTIFIER = 25,                /* IDENTIFIER  */
  YYSYMBOL_ERROR = 26,                     /* ERROR  */
  YYSYMBOL_EOF_TOKEN = 27,                 /* EOF_TOKEN  */
  YYSYMBOL_IFX = 28,                       /* IFX  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_GE = 31,                        /* GE  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_EQ = 33,                        /* EQ  */
  YYSYMBOL_NE = 34,                        /* NE  */
  YYSYMBOL_35_ = 35,                       /* '>'  */
  YYSYMBOL_36_ = 36,                       /* '<'  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '-'  */
  YYSYMBOL_39_ = 39,                       /* '*'  */
  YYSYMBOL_40_ = 40,                       /* '/'  */
  YYSYMBOL_41_ = 41,                       /* '%'  */
  YYSYMBOL_INC = 42,                       /* INC  */
  YYSYMBOL_DEC = 43,                       /* DEC  */
  YYSYMBOL_UMINUS = 44,                    /* UMINUS  */
  YYSYMBOL_45_ = 45,                       /* '['  */
  YYSYMBOL_46_ = 46,                       /* ']'  */
  YYSYMBOL_ARR = 47,                       /* ARR  */
  YYSYMBOL_48_ = 48,                       /* ';'  */
  YYSYMBOL_49_ = 49,                       /* '('  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '='  */
  YYSYMBOL_53_ = 53,                       /* '{'  */
  YYSYMBOL_54_ = 54,                       /* '}'  */
  YYSYMBOL_55_ = 55,                       /* ':'  */
  YYSYMBOL_56_ = 56,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_program = 58,                   /* program  */
  YYSYMBOL_declarations = 59,              /* declarations  */
  YYSYMBOL_declaration = 60,               /* declaration  */
  YYSYMBOL_functionDecl = 61,              /* functionDecl  */
  YYSYMBOL_62_1 = 62,                      /* $@1  */
  YYSYMBOL_param_list = 63,                /* param_list  */
  YYSYMBOL_varInitialiser = 64,            /* varInitialiser  */
  YYSYMBOL_arrayInitialiser = 65,          /* arrayInitialiser  */
  YYSYMBOL_array_init_list = 66,           /* array_init_list  */
  YYSYMBOL_varDeclaration = 67,            /* varDeclaration  */
  YYSYMBOL_varType = 68,                   /* varType  */
  YYSYMBOL_varNames = 69,                  /* varNames  */
  YYSYMBOL_arraySpecifier = 70,            /* arraySpecifier  */
  YYSYMBOL_funcBody = 71,                  /* funcBody  */
  YYSYMBOL_72_2 = 72,                      /* @2  */
  YYSYMBOL_stmtOrDecl = 73,                /* stmtOrDecl  */
  YYSYMBOL_stmtList = 74,                  /* stmtList  */
  YYSYMBOL_stmt = 75,                      /* stmt  */
  YYSYMBOL_forStmt = 76,                   /* forStmt  */
  YYSYMBOL_77_3 = 77,                      /* $@3  */
  YYSYMBOL_forInit = 78,                   /* forInit  */
  YYSYMBOL_forCond = 79,                   /* forCond  */
  YYSYMBOL_forIter = 80,                   /* forIter  */
  YYSYMBOL_assignExpr = 81,                /* assignExpr  */
  YYSYMBOL_switchStmt = 82,                /* switchStmt  */
  YYSYMBOL_83_4 = 83,                      /* $@4  */
  YYSYMBOL_switchBody = 84,                /* switchBody  */
  YYSYMBOL_switches = 85,                  /* switches  */
  YYSYMBOL_cases = 86,                     /* cases  */
  YYSYMBOL_caseLabel = 87,                 /* caseLabel  */
  YYSYMBOL_88_5 = 88,                      /* $@5  */
  YYSYMBOL_caseType = 89,                  /* caseType  */
  YYSYMBOL_whileStmt = 90,                 /* whileStmt  */
  YYSYMBOL_blockStmt = 91,                 /* blockStmt  */
  YYSYMBOL_92_6 = 92,                      /* @6  */
  YYSYMBOL_ifStmt = 93,                    /* ifStmt  */
  YYSYMBOL_expr = 94,                      /* expr  */
  YYSYMBOL_arrayExpr = 95,                 /* arrayExpr  */
  YYSYMBOL_callExpr = 96,                  /* callExpr  */
  YYSYMBOL_arg_list = 97,                  /* arg_list  */
  YYSYMBOL_returnStmt = 98,                /* returnStmt  */
  YYSYMBOL_continueStmt = 99,              /* continueStmt  */
  YYSYMBOL_breakStmt = 100                 /* breakStmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,     2,     2,    41,     2,     2,
      49,    50,    39,    37,    51,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    48,
      36,    52,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      42,    43,    44,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    93,    94,    97,    98,    99,   103,   102,
     154,   165,   179,   182,   186,   190,   192,   194,   195,   196,
     197,   205,   283,   283,   283,   285,   286,   288,   291,   294,
     297,   297,   302,   303,   304,   308,   309,   312,   313,   315,
     317,   318,   319,   320,   321,   322,   323,   324,   327,   327,
     332,   333,   334,   337,   338,   341,   342,   345,   353,   360,
     367,   374,   380,   389,   389,   395,   397,   398,   401,   402,
     405,   405,   414,   414,   416,   418,   418,   424,   425,   427,
     428,   429,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   458,   473,   515,   516,   517,   520,   527,   536,
     538
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "K_INT", "K_FLOAT",
  "K_CHAR", "FOR", "WHILE", "ELSE", "IF", "SWITCH", "CASE", "RETURN",
  "CONTINUE", "BREAK", "DEFAULT", "INTEGER", "FLOAT", "CHARACTER",
  "STRING", "PLUS_ASSIGN", "MINUS_ASSIGN", "STAR_ASSIGN", "SLASH_ASSIGN",
  "MOD_ASSIGN", "IDENTIFIER", "ERROR", "EOF_TOKEN", "IFX", "AND", "OR",
  "GE", "LE", "EQ", "NE", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "INC", "DEC", "UMINUS", "'['", "']'", "ARR", "';'", "'('", "')'", "','",
  "'='", "'{'", "'}'", "':'", "'!'", "$accept", "program", "declarations",
  "declaration", "functionDecl", "$@1", "param_list", "varInitialiser",
  "arrayInitialiser", "array_init_list", "varDeclaration", "varType",
  "varNames", "arraySpecifier", "funcBody", "@2", "stmtOrDecl", "stmtList",
  "stmt", "forStmt", "$@3", "forInit", "forCond", "forIter", "assignExpr",
  "switchStmt", "$@4", "switchBody", "switches", "cases", "caseLabel",
  "$@5", "caseType", "whileStmt", "blockStmt", "@6", "ifStmt", "expr",
  "arrayExpr", "callExpr", "arg_list", "returnStmt", "continueStmt",
  "breakStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -138,    20,    22,  -138,  -138,  -138,  -138,  -138,  -138,   -18,
       4,    31,  -138,  -138,    11,  -138,    10,   123,   -42,    40,
     -43,    41,     1,    57,  -138,  -138,  -138,   123,  -138,    32,
    -138,  -138,  -138,  -138,  -138,    28,   228,   228,    57,   228,
    -138,   401,  -138,  -138,    27,    56,  -138,   228,    39,   295,
    -138,    16,   401,    39,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,  -138,  -138,
    -138,   401,   -28,  -138,    57,  -138,   416,   416,    59,    59,
      59,    59,    59,    59,    84,    84,    39,    39,    39,   383,
    -138,  -138,   228,  -138,   401,  -138,   133,   401,    44,    45,
      58,  -138,   228,  -138,  -138,   -31,  -138,  -138,  -138,    61,
      40,  -138,  -138,    63,  -138,  -138,  -138,  -138,   401,    12,
      64,    67,    69,    72,  -138,   228,   228,    81,   401,  -138,
    -138,   228,  -138,  -138,  -138,  -138,  -138,   228,  -138,  -138,
    -138,  -138,   187,   317,   339,   228,   401,   160,   401,  -138,
      73,  -138,   214,   214,   361,  -138,   228,  -138,    80,    52,
      83,   401,   214,    35,  -138,   240,  -138,  -138,  -138,    78,
      35,  -138,  -138,    85,  -138,  -138,  -138,   214,   228,   214,
     214,  -138,   268,  -138,  -138
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,    22,    24,    23,     2,     3,     5,
       0,     0,     6,     7,    29,    25,    21,    12,    13,     0,
       0,     0,     0,     0,    29,    26,     8,     0,    10,     0,
      28,    79,    82,    80,    83,    81,     0,     0,     0,     0,
      15,    14,   101,    84,     0,     0,    27,   106,    85,     0,
      19,     0,    17,    86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     9,
      11,   104,     0,   100,     0,    16,    98,    99,    94,    95,
      96,    97,    92,    91,    87,    88,    89,    90,    93,     0,
      34,   103,     0,    20,    18,   102,     0,   105,     0,     0,
       0,    63,   107,   109,   110,    81,    37,    75,    31,     0,
       0,    32,    43,     0,    44,    42,    38,    41,     0,   101,
      84,     0,     0,     0,    48,     0,     0,     0,   108,    58,
      59,     0,    34,    33,    39,    61,    62,     0,    40,    45,
      47,    46,    52,     0,     0,     0,    57,     0,    60,    51,
       0,    50,     0,     0,     0,    76,    54,    74,    77,     0,
       0,    53,     0,    67,    64,    56,    78,    72,    73,     0,
      66,    36,    70,     0,    55,    65,    36,    68,     0,     0,
      69,    35,     0,    49,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,  -138,  -138,  -138,  -138,   115,   -29,  -138,
      -1,     2,  -138,  -138,  -138,  -138,    21,   -32,   -61,  -138,
    -138,  -138,  -138,  -138,  -137,  -138,  -138,  -138,  -138,  -138,
     -22,  -138,  -138,  -138,  -138,  -138,  -138,   -23,   -94,   -90,
    -138,  -138,  -138,  -138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    44,    20,    15,    40,    51,
     109,   110,    16,    18,    69,    90,    96,   177,   111,   112,
     142,   150,   160,   173,   113,   114,   127,   164,   169,   170,
     171,   178,   172,   115,   116,   132,   117,   118,    42,    43,
      72,   121,   122,   123
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    10,   119,    22,    11,   151,   120,    26,    27,    50,
      23,   129,   130,    48,    49,    52,    53,    29,    47,    21,
       3,   131,    91,    92,    71,     4,     5,     6,   174,    45,
      12,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    93,   167,    30,   119,     7,
     168,    94,    13,   119,   135,   136,    14,   120,   119,   119,
      17,    19,   120,   120,   137,    24,    28,    74,   119,    97,
      75,   119,   120,    31,    32,    33,    34,    47,    46,   128,
      68,    70,    35,   119,    67,   119,   119,   120,   162,   120,
     120,   157,   158,   124,   125,    36,    62,    63,    64,    65,
      66,   166,   143,   144,    67,   163,    37,   126,   146,   133,
      38,   134,   138,    39,   148,   139,   181,   140,   183,   181,
     141,   156,   154,    64,    65,    66,     4,     5,     6,    67,
     145,   165,   175,   161,    25,   179,     4,     5,     6,    98,
      99,   149,   100,   101,   180,   102,   103,   104,   176,    31,
      32,    33,    34,   147,     0,   182,     0,     0,   105,     0,
       0,     0,     0,     4,     5,     6,    98,    99,     0,   100,
     101,    36,   102,   103,   104,     0,    31,    32,    33,    34,
       0,   106,    37,     0,     0,   105,   107,   108,     0,    39,
       4,     5,     6,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,    31,    32,    33,    34,     0,   106,    37,
       0,     0,   105,   107,   155,     0,    39,     0,     0,     0,
      98,    99,     0,   100,   101,    36,   102,   103,   104,     0,
      31,    32,    33,    34,     0,     0,    37,     0,     0,   105,
       0,     0,     0,    39,    31,    32,    33,    34,     0,     0,
       0,     0,    36,    35,     0,     0,    31,    32,    33,    34,
       0,     0,   106,    37,     0,   105,    36,   107,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    37,    36,     0,
       0,     0,     0,     0,    39,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    39,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   184,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     0,     0,     0,
      67,     0,     0,     0,     0,    73,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,     0,
       0,     0,    67,     0,     0,     0,     0,   152,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,     0,     0,     0,    67,     0,     0,     0,     0,   153,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     0,     0,     0,    67,     0,     0,     0,
       0,   159,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,     0,     0,     0,    67,    95,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     0,     0,     0,    67,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,     0,
       0,    67
};

static const yytype_int16 yycheck[] =
{
      23,     2,    96,    45,     2,   142,    96,    50,    51,    38,
      52,    42,    43,    36,    37,    38,    39,    16,    49,    17,
       0,    52,    50,    51,    47,     3,     4,     5,   165,    27,
      48,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    74,    11,    46,   142,    27,
      15,    74,    48,   147,    42,    43,    25,   147,   152,   153,
      49,    51,   152,   153,    52,    25,    25,    51,   162,    92,
      54,   165,   162,    16,    17,    18,    19,    49,    46,   102,
      53,    25,    25,   177,    45,   179,   180,   177,     8,   179,
     180,   152,   153,    49,    49,    38,    37,    38,    39,    40,
      41,   162,   125,   126,    45,    53,    49,    49,   131,    48,
      53,    48,    48,    56,   137,    48,   177,    48,   179,   180,
      48,    48,   145,    39,    40,    41,     3,     4,     5,    45,
      49,    48,    54,   156,    19,    50,     3,     4,     5,     6,
       7,   142,     9,    10,   176,    12,    13,    14,   170,    16,
      17,    18,    19,   132,    -1,   178,    -1,    -1,    25,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    38,    12,    13,    14,    -1,    16,    17,    18,    19,
      -1,    48,    49,    -1,    -1,    25,    53,    54,    -1,    56,
       3,     4,     5,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    16,    17,    18,    19,    -1,    48,    49,
      -1,    -1,    25,    53,    54,    -1,    56,    -1,    -1,    -1,
       6,     7,    -1,     9,    10,    38,    12,    13,    14,    -1,
      16,    17,    18,    19,    -1,    -1,    49,    -1,    -1,    25,
      -1,    -1,    -1,    56,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    38,    25,    -1,    -1,    16,    17,    18,    19,
      -1,    -1,    48,    49,    -1,    25,    38,    53,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    49,    38,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    50,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    50,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    50,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    50,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    45,    46,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    45,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    58,    59,     0,     3,     4,     5,    27,    60,    61,
      67,    68,    48,    48,    25,    64,    69,    49,    70,    51,
      63,    68,    45,    52,    25,    64,    50,    51,    25,    16,
      46,    16,    17,    18,    19,    25,    38,    49,    53,    56,
      65,    94,    95,    96,    62,    68,    46,    49,    94,    94,
      65,    66,    94,    94,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    45,    53,    71,
      25,    94,    97,    50,    51,    54,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      72,    50,    51,    65,    94,    46,    73,    94,     6,     7,
       9,    10,    12,    13,    14,    25,    48,    53,    54,    67,
      68,    75,    76,    81,    82,    90,    91,    93,    94,    95,
      96,    98,    99,   100,    49,    49,    49,    83,    94,    42,
      43,    52,    92,    48,    48,    42,    43,    52,    48,    48,
      48,    48,    77,    94,    94,    49,    94,    73,    94,    67,
      78,    81,    50,    50,    94,    54,    48,    75,    75,    50,
      79,    94,     8,    53,    84,    48,    75,    11,    15,    85,
      86,    87,    89,    80,    81,    54,    87,    74,    88,    50,
      74,    75,    94,    75,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    60,    62,    61,
      63,    63,    63,    64,    64,    64,    65,    66,    66,    66,
      66,    67,    68,    68,    68,    69,    69,    70,    70,    70,
      72,    71,    73,    73,    73,    74,    74,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    77,    76,
      78,    78,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    81,    83,    82,    84,    85,    85,    86,    86,
      88,    87,    89,    89,    90,    92,    91,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    96,    97,    97,    97,    98,    98,    99,
     100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     2,     2,     0,     7,
       2,     4,     0,     2,     4,     4,     3,     1,     3,     1,
       3,     2,     1,     1,     1,     1,     3,     4,     3,     0,
       0,     4,     2,     3,     0,     2,     0,     1,     1,     2,
       2,     1,     1,     1,     1,     2,     2,     2,     0,    10,
       1,     1,     0,     1,     0,     1,     0,     3,     2,     2,
       3,     2,     2,     0,     6,     3,     1,     0,     2,     3,
       0,     4,     1,     1,     5,     0,     4,     5,     7,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     4,     1,     3,     0,     1,     2,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarations EOF_TOKEN  */
#line 86 "parser.y"
                                { 
                        printf("Program end\n"); 
                        backend((yyvsp[-1].node), currentFileName);
                        return 0;
                    }
#line 1513 "y.tab.c"
    break;

  case 3: /* declarations: declarations declaration  */
#line 93 "parser.y"
                                       { (yyval.node) = oprNode(OPR_DECL_LIST, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1519 "y.tab.c"
    break;

  case 4: /* declarations: %empty  */
#line 94 "parser.y"
      {(yyval.node) = NULL;}
#line 1525 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 103 "parser.y"
                        {
                            Symbol* funcSymbol = install((yyvsp[-3].id).name, &identifiers, level, (yyvsp[-3].id).src);
                            if(funcSymbol->type){
                                compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Function %s already declared", (yyvsp[-3].id).name);
                            }
                            Type* funcType = malloc(sizeof(Type));
                            funcSymbol->type = funcType;
                            funcType->sym = funcSymbol;
                            funcType->op = T_FUNCTION;
                            funcType->type = malloc(sizeof(Type));
                            funcType->type->op = (yyvsp[-4].iValue);
                            currentFunctionType = funcType;
                            int numParams=0;
                            Node* temp = (yyvsp[-1].node);
                            while(temp){
                                numParams++;
                                if(temp->as.opr.nops == 2)
                                    temp = temp->as.opr.operands[0];
                                else temp = NULL;
                            }
                            funcType->size = numParams;
                            funcType->proto = malloc(sizeof(Type*) * numParams);
                            Node* param = (yyvsp[-1].node);
                            int i=0;
                            printf("donefg %d\n", numParams);
                            while(param){
                                if(param->as.opr.nops == 2){
                                    //last param
                                    // printf("Type of param is %d\n", param->as.opr.operands[0]->type);
                                    funcType->proto[i] = param->as.opr.operands[1]->as.symbol->type;
                                } else {
                                    funcType->proto[i] = param->as.opr.operands[0]->as.symbol->type;
                                }
                                i++;
                                if(param->as.opr.nops == 2)
                                    param = param->as.opr.operands[0];
                                else param = NULL;
                            }
                            printf("func proto %d\n", funcType->proto[0]->op);
                            beginScope();
                        }
#line 1571 "y.tab.c"
    break;

  case 9: /* functionDecl: varType IDENTIFIER '(' param_list ')' $@1 funcBody  */
#line 145 "parser.y"
                {
                    endScope();
                    Symbol* funcSymbol = lookup((yyvsp[-5].id).name, identifiers);
                    // printNode(param_list_node);
                    (yyval.node) = oprNode(OPR_FUNC, 3, identifierNode(funcSymbol), param_list_node, funcBodyNode);
                    currentFunctionType = NULL;
                }
#line 1583 "y.tab.c"
    break;

  case 10: /* param_list: varType IDENTIFIER  */
#line 154 "parser.y"
                               {
                        Symbol* psym = install((yyvsp[0].id).name, &identifiers, level, (yyvsp[0].id).src);
                        (yyval.node) = oprNode(OPR_LIST, 1, identifierNode(psym)); 
                        printf("Found param %s\n", (yyvsp[0].id).name);
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = (yyvsp[-1].iValue);
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                        param_list_node = (yyval.node);
                    }
#line 1599 "y.tab.c"
    break;

  case 11: /* param_list: param_list ',' varType IDENTIFIER  */
#line 165 "parser.y"
                                        {
                        printf("Found param %s\n", (yyvsp[0].id).name);
                        Symbol* psym = install((yyvsp[0].id).name, &identifiers, level, (yyvsp[0].id).src);
                        if(psym->type){
                            compileError((yyvsp[0].id).src, strlen((yyvsp[0].id).name), "Parameter %s already declared", (yyvsp[0].id).name);
                        }
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = (yyvsp[-1].iValue);
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                        (yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-3].node), identifierNode(psym));
                        param_list_node = (yyval.node);
                    }
#line 1618 "y.tab.c"
    break;

  case 12: /* param_list: %empty  */
#line 179 "parser.y"
      {(yyval.node)=NULL; param_list_node = NULL;}
#line 1624 "y.tab.c"
    break;

  case 13: /* varInitialiser: IDENTIFIER arraySpecifier  */
#line 182 "parser.y"
                                          {
                                    (yyval.node) = oprNode('=', 2, identifierNode(install((yyvsp[-1].id).name, &identifiers, level, (yyvsp[-1].id).src)), (yyvsp[0].node));
                                    (yyval.node)->src = (yyvsp[-1].id).src;
                                    }
#line 1633 "y.tab.c"
    break;

  case 14: /* varInitialiser: IDENTIFIER arraySpecifier '=' expr  */
#line 186 "parser.y"
                                         {
                                    (yyval.node) = oprNode('=', 3, identifierNode(install((yyvsp[-3].id).name, &identifiers, level, (yyvsp[-3].id).src)), (yyvsp[-2].node), (yyvsp[0].node));
                                    (yyval.node)->src = (yyvsp[-3].id).src;
                                    }
#line 1642 "y.tab.c"
    break;

  case 15: /* varInitialiser: IDENTIFIER arraySpecifier '=' arrayInitialiser  */
#line 190 "parser.y"
                                                     {(yyval.node) = oprNode('=', 3, identifierNode(install((yyvsp[-3].id).name, &identifiers, level, (yyvsp[-3].id).src)), (yyvsp[-2].node), (yyvsp[0].node)); (yyval.node)->src = (yyvsp[-3].id).src;}
#line 1648 "y.tab.c"
    break;

  case 16: /* arrayInitialiser: '{' array_init_list '}'  */
#line 192 "parser.y"
                                          { (yyval.node) = (yyvsp[-1].node); (yyval.node)->exprType.op = T_ARRAY;}
#line 1654 "y.tab.c"
    break;

  case 17: /* array_init_list: expr  */
#line 194 "parser.y"
                      { (yyval.node) = oprNode(OPR_LIST, 1, (yyvsp[0].node));}
#line 1660 "y.tab.c"
    break;

  case 18: /* array_init_list: array_init_list ',' expr  */
#line 195 "parser.y"
                               { (yyval.node) = oprNode(OPR_LIST, 3, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1666 "y.tab.c"
    break;

  case 19: /* array_init_list: arrayInitialiser  */
#line 196 "parser.y"
                       { (yyval.node) = oprNode(OPR_LIST, 1, (yyvsp[0].node)); (yyval.node)->exprType.op = T_ARRAY;}
#line 1672 "y.tab.c"
    break;

  case 20: /* array_init_list: array_init_list ',' arrayInitialiser  */
#line 197 "parser.y"
                                           { (yyval.node) = oprNode(OPR_LIST, 3, (yyvsp[-2].node), (yyvsp[0].node), NULL); (yyval.node)->exprType.op = T_ARRAY;}
#line 1678 "y.tab.c"
    break;

  case 21: /* varDeclaration: varType varNames  */
#line 205 "parser.y"
                                 {
    (yyval.node) = oprNode(OPR_VAR_DECL, 1, (yyvsp[0].node));
    printf("Found var decl %d, \n", (yyvsp[0].node)->as.opr.type);
    //iterate through the list of variables and add them to the symbol table
    Node* varName = (yyvsp[0].node);
    while(varName != NULL) {
        Node* varInitialiser;
        if(varName->as.opr.type == OPR_LIST) {
            varInitialiser = varName->as.opr.operands[1];
            printf("Found list %d\n", varInitialiser->as.opr.type);
        } else {
            varInitialiser = varName;
        }
        printf("Found var decl for '%s', \n", varInitialiser->as.opr.operands[0]->as.symbol->name);
        Symbol* varSymbol = varInitialiser->as.opr.operands[0]->as.symbol;
        Symbol* installed = install(varSymbol->name, &identifiers, level, varSymbol->src);
        Coordinate src = varSymbol->src;
        if(installed->type){
            errorMessage(varInitialiser->src, strlen(varSymbol->name), "Error: Variable '%s' already declared", varSymbol->name);
            compileError(varSymbol->src, strlen(varSymbol->name), "Declared here");
        }
        Type* type = malloc(sizeof(Type));
        type->sym = installed;
        installed->type = type;
        type->op = (yyvsp[-1].iValue);
        int arrLastSize = -1;
        //check if this is an array
        if(varInitialiser->as.opr.operands[1] != NULL){
            Node* arraySpecifier = varInitialiser->as.opr.operands[1];
            Type* innerType = type;
            do {
                arrLastSize = arraySpecifier->as.opr.operands[1]->as.value->as.integer;
                //check if size is declared for dimensions other than first
                if(arrLastSize <= 0 && arraySpecifier->as.opr.operands[0] != NULL){
                    compileError(src, strlen(varSymbol->name), "Array dimensions except the first cannot be empty %d", arrLastSize);
                }
                Type* outerType = malloc(sizeof(Type));
                outerType->sym = installed;
                outerType->op = T_ARRAY;
                outerType->type = innerType;
                outerType->size = arrLastSize;
                innerType = outerType;
            } while((arraySpecifier = arraySpecifier->as.opr.operands[0]));
            installed->type=innerType;
        }

        // printf("\nType op of this var is %d\n", installed->type->op);
        
        //Check if there is an initialiser expression assignment
        if(varInitialiser->as.opr.nops == 3){
            Node* expr = varInitialiser->as.opr.operands[2];
            // printf("Found initialiser %d\n", expr->exprType);
            if(!typeCheckAssign(installed->type->op, expr->exprType.op)){
                compileError(src, strlen(varSymbol->name), "Type mismatch in variable initialisation %s", varSymbol->name);
            }
            //Check if string initialiser
            if(expr->type == NODE_LITERAL && expr->as.value->type == T_ARRAY){
                if(installed->type->op != T_ARRAY || installed->type->type->op != T_CHAR){
                    compileError(src, strlen(varSymbol->name), "Type mismatch (string must be char[]) in variable initialisation %s", varSymbol->name);
                }
            }
            //Check if the initialiser is an array
            if(expr->as.opr.type == OPR_LIST){
                //check every element type
                typeCheckArrayInitialiser(installed->type, expr);
            }

        }
        //Move forward to the next variable
        if(varName->as.opr.type == OPR_LIST){
            varName = varName->as.opr.operands[0];
        } else {
            varName = NULL;
        }
    }
}
#line 1759 "y.tab.c"
    break;

  case 22: /* varType: K_INT  */
#line 283 "parser.y"
               {(yyval.iValue) = T_INT;}
#line 1765 "y.tab.c"
    break;

  case 23: /* varType: K_CHAR  */
#line 283 "parser.y"
                                      {(yyval.iValue) = T_CHAR;}
#line 1771 "y.tab.c"
    break;

  case 24: /* varType: K_FLOAT  */
#line 283 "parser.y"
                                                              {(yyval.iValue) = T_FLOAT;}
#line 1777 "y.tab.c"
    break;

  case 26: /* varNames: varNames ',' varInitialiser  */
#line 286 "parser.y"
                                  {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1783 "y.tab.c"
    break;

  case 27: /* arraySpecifier: arraySpecifier '[' INTEGER ']'  */
#line 288 "parser.y"
                                               {
                                        (yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-3].node), intNode((yyvsp[-1].iValue)));
                                    }
#line 1791 "y.tab.c"
    break;

  case 28: /* arraySpecifier: arraySpecifier '[' ']'  */
#line 291 "parser.y"
                             {
                            (yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), intNode(0));
                        }
#line 1799 "y.tab.c"
    break;

  case 29: /* arraySpecifier: %empty  */
#line 294 "parser.y"
      { (yyval.node) = NULL; }
#line 1805 "y.tab.c"
    break;

  case 30: /* @2: %empty  */
#line 297 "parser.y"
              {beginScope(); (yyval.node) = NULL;}
#line 1811 "y.tab.c"
    break;

  case 31: /* funcBody: '{' @2 stmtOrDecl '}'  */
#line 299 "parser.y"
              {endScope(); (yyval.node) = (yyvsp[-2].node); printf("Printing stmtordecl\n"); printNode(funcBodyNode);}
#line 1817 "y.tab.c"
    break;

  case 32: /* stmtOrDecl: stmtOrDecl stmt  */
#line 302 "parser.y"
                            {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-1].node), (yyvsp[0].node)); funcBodyNode = (yyval.node);}
#line 1823 "y.tab.c"
    break;

  case 33: /* stmtOrDecl: stmtOrDecl varDeclaration ';'  */
#line 303 "parser.y"
                                    {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), (yyvsp[-1].node)); funcBodyNode = (yyval.node);}
#line 1829 "y.tab.c"
    break;

  case 34: /* stmtOrDecl: %empty  */
#line 304 "parser.y"
      {(yyval.node) = NULL; funcBodyNode = (yyval.node);}
#line 1835 "y.tab.c"
    break;

  case 37: /* stmt: ';'  */
#line 312 "parser.y"
          {(yyval.node) = NULL;}
#line 1841 "y.tab.c"
    break;

  case 48: /* $@3: %empty  */
#line 327 "parser.y"
                 {beginScope();}
#line 1847 "y.tab.c"
    break;

  case 49: /* forStmt: FOR '(' $@3 forInit ';' forCond ';' forIter ')' stmt  */
#line 327 "parser.y"
                                                                          {
    endScope();

}
#line 1856 "y.tab.c"
    break;

  case 52: /* forInit: %empty  */
#line 334 "parser.y"
      {(yyval.node) = NULL;}
#line 1862 "y.tab.c"
    break;

  case 54: /* forCond: %empty  */
#line 338 "parser.y"
      {(yyval.node) = NULL;}
#line 1868 "y.tab.c"
    break;

  case 56: /* forIter: %empty  */
#line 342 "parser.y"
      {(yyval.node)=NULL;}
#line 1874 "y.tab.c"
    break;

  case 57: /* assignExpr: IDENTIFIER '=' expr  */
#line 345 "parser.y"
                                {
                // printf("Found assign target\n");
                Symbol* sym = getSymbol((yyvsp[-2].id).name, identifiers, (yyvsp[-2].id).src, "Variable '%s' not declared", (yyvsp[-2].id).name);
                if(!typeCheckAssign(sym->type->op, (yyvsp[0].node)->exprType.op)){
                    compileError((yyvsp[-2].id).src, strlen((yyvsp[-2].id).name), "Type mismatch in assignment %s", (yyvsp[-2].id).name);
                }
                (yyval.node) = oprNode(OPR_ASSIGN, 2, identifierNode(sym), (yyvsp[0].node));
            }
#line 1887 "y.tab.c"
    break;

  case 58: /* assignExpr: IDENTIFIER INC  */
#line 353 "parser.y"
                     {
                Symbol* sym = getSymbol((yyvsp[-1].id).name, identifiers, (yyvsp[-1].id).src, "Variable '%s' not declared", (yyvsp[-1].id).name);
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError((yyvsp[-1].id).src, strlen((yyvsp[-1].id).name), "Only int and float can be incremented %s", (yyvsp[-1].id).name);
                }
                (yyval.node) = oprNode(OPR_INC, 1, identifierNode(sym));
            }
#line 1899 "y.tab.c"
    break;

  case 59: /* assignExpr: IDENTIFIER DEC  */
#line 360 "parser.y"
                     {
                Symbol* sym = getSymbol((yyvsp[-1].id).name, identifiers, (yyvsp[-1].id).src, "Variable '%s' not declared", (yyvsp[-1].id).name);
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError((yyvsp[-1].id).src, strlen((yyvsp[-1].id).name), "Only int and float can be decremented %s", (yyvsp[-1].id).name);
                }
                (yyval.node) = oprNode(OPR_DEC, 1, identifierNode(sym));
            }
#line 1911 "y.tab.c"
    break;

  case 60: /* assignExpr: arrayExpr '=' expr  */
#line 367 "parser.y"
                         {
                printf("Got array type as %d\n", (yyvsp[-2].node)->exprType.op);
                if(!typeCheckAssign((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op)){
                    compileError((yyvsp[-2].node)->src, (yyvsp[0].node)->src.length + (yyvsp[-2].node)->src.length, "Type mismatch in assignment to array");
                }
                (yyval.node) = oprNode(OPR_ASSIGN, 2, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1923 "y.tab.c"
    break;

  case 61: /* assignExpr: arrayExpr INC  */
#line 374 "parser.y"
                    {
                if((yyvsp[-1].node)->exprType.op != T_INT && (yyvsp[-1].node)->exprType.op != T_FLOAT){
                    compileError((yyvsp[-1].node)->src, (yyvsp[-1].node)->src.length + 2, "Only int and float can be incremented");
                }
                (yyval.node) = oprNode(OPR_INC, 1, (yyvsp[-1].node));
            }
#line 1934 "y.tab.c"
    break;

  case 62: /* assignExpr: arrayExpr DEC  */
#line 380 "parser.y"
                    {
                if((yyvsp[-1].node)->exprType.op != T_INT || (yyvsp[-1].node)->exprType.op != T_FLOAT){
                    compileError((yyvsp[-1].node)->src, (yyvsp[-1].node)->src.length+2, "Only int and float can be decremented");
                }
                (yyval.node) = oprNode(OPR_DEC, 1, (yyvsp[-1].node));
            }
#line 1945 "y.tab.c"
    break;

  case 63: /* $@4: %empty  */
#line 389 "parser.y"
                    { errorMessage((Coordinate){lineno, col-6, 0}, 6, 
                                    ANSI_COLOR_BOLD ANSI_COLOR_BLUE 
                                    "Warning: " ANSI_COLOR_RESET "Switch statement is not implemented");
                    }
#line 1954 "y.tab.c"
    break;

  case 64: /* switchStmt: SWITCH $@4 '(' expr ')' switchBody  */
#line 393 "parser.y"
                            { (yyval.node) = NULL; }
#line 1960 "y.tab.c"
    break;

  case 70: /* $@5: %empty  */
#line 405 "parser.y"
                    {templineno = lineno; tempcol = col- 4;}
#line 1966 "y.tab.c"
    break;

  case 71: /* caseLabel: caseType $@5 expr ':'  */
#line 405 "parser.y"
                                                                      {
                if((yyvsp[-1].node)->type!= NODE_LITERAL){
                    compileError((Coordinate){templineno, tempcol, 0}, (yyvsp[-1].node)->src.length + 5, "Case label must be a constant");
                }
                if((yyvsp[-1].node)->exprType.op != T_INT){
                    compileError((Coordinate){templineno, tempcol, 0}, (yyvsp[-1].node)->src.length+5, "Case label must be an integer");
                }
}
#line 1979 "y.tab.c"
    break;

  case 74: /* whileStmt: WHILE '(' expr ')' stmt  */
#line 416 "parser.y"
                                   {(yyval.node) = oprNode(OPR_WHILE, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1985 "y.tab.c"
    break;

  case 75: /* @6: %empty  */
#line 418 "parser.y"
                        {beginScope();}
#line 1991 "y.tab.c"
    break;

  case 76: /* blockStmt: '{' @6 stmtOrDecl '}'  */
#line 421 "parser.y"
                        {endScope(); (yyval.node) = (yyvsp[-2].node);}
#line 1997 "y.tab.c"
    break;

  case 77: /* ifStmt: IF '(' expr ')' stmt  */
#line 424 "parser.y"
                                       {printf("Unmatched if statement\n");}
#line 2003 "y.tab.c"
    break;

  case 78: /* ifStmt: IF '(' expr ')' stmt ELSE stmt  */
#line 425 "parser.y"
                                     {printf("Matched if statement\n");}
#line 2009 "y.tab.c"
    break;

  case 79: /* expr: INTEGER  */
#line 427 "parser.y"
              {(yyval.node) = intNode((yyvsp[0].iValue));}
#line 2015 "y.tab.c"
    break;

  case 80: /* expr: CHARACTER  */
#line 428 "parser.y"
                {(yyval.node) = charNode((yyvsp[0].cValue)); }
#line 2021 "y.tab.c"
    break;

  case 81: /* expr: IDENTIFIER  */
#line 429 "parser.y"
                 { 
            Symbol* foundId = getSymbol((yyvsp[0].id).name, identifiers, (yyvsp[0].id).src, "Identifier '%s' not declared in this scope", (yyvsp[0].id).name);
            (yyval.node) = identifierNode(foundId);
            printf("Idenfitier base type is %d\n", (yyval.node)->exprType.ndim);
        }
#line 2031 "y.tab.c"
    break;

  case 82: /* expr: FLOAT  */
#line 434 "parser.y"
            {(yyval.node) = floatNode((yyvsp[0].fValue));}
#line 2037 "y.tab.c"
    break;

  case 83: /* expr: STRING  */
#line 435 "parser.y"
             {(yyval.node) = strNode((yyvsp[0].sValue), strlen((yyvsp[0].sValue))); printf("String here, %d\n", (yyval.node)->src.length);}
#line 2043 "y.tab.c"
    break;

  case 84: /* expr: callExpr  */
#line 436 "parser.y"
               {(yyval.node) = (yyvsp[0].node);}
#line 2049 "y.tab.c"
    break;

  case 85: /* expr: '-' expr  */
#line 437 "parser.y"
                            { (yyval.node) = oprNode('-', 1, (yyvsp[0].node)); typeCheckUnary((yyvsp[0].node)); (yyval.node)->exprType.op = (yyvsp[0].node)->exprType.op;}
#line 2055 "y.tab.c"
    break;

  case 86: /* expr: '!' expr  */
#line 438 "parser.y"
                            { (yyval.node) = oprNode('!', 1, (yyvsp[0].node)); typeCheckUnary((yyvsp[0].node)); (yyval.node)->exprType.op = (yyvsp[0].node)->exprType.op;}
#line 2061 "y.tab.c"
    break;

  case 87: /* expr: expr '+' expr  */
#line 439 "parser.y"
                    { (yyval.node) = oprNode('+', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2067 "y.tab.c"
    break;

  case 88: /* expr: expr '-' expr  */
#line 440 "parser.y"
                    { (yyval.node) = oprNode('-', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2073 "y.tab.c"
    break;

  case 89: /* expr: expr '*' expr  */
#line 441 "parser.y"
                    { (yyval.node) = oprNode('*', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2079 "y.tab.c"
    break;

  case 90: /* expr: expr '/' expr  */
#line 442 "parser.y"
                    { (yyval.node) = oprNode('/', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2085 "y.tab.c"
    break;

  case 91: /* expr: expr '<' expr  */
#line 443 "parser.y"
                    { (yyval.node) = oprNode('<', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2091 "y.tab.c"
    break;

  case 92: /* expr: expr '>' expr  */
#line 444 "parser.y"
                    { (yyval.node) = oprNode('>', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2097 "y.tab.c"
    break;

  case 93: /* expr: expr '%' expr  */
#line 445 "parser.y"
                    { (yyval.node) = oprNode('%', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = T_INT; if((yyvsp[-2].node)->exprType.op != T_INT || (yyvsp[0].node)->exprType.op != T_INT){compileError((yyvsp[-2].node)->src, (yyvsp[-2].node)->src.length + (yyvsp[0].node)->src.length, "Modulo operator only works on integers");}}
#line 2103 "y.tab.c"
    break;

  case 94: /* expr: expr GE expr  */
#line 446 "parser.y"
                   { (yyval.node) = oprNode(OPR_GE, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2109 "y.tab.c"
    break;

  case 95: /* expr: expr LE expr  */
#line 447 "parser.y"
                   { (yyval.node) = oprNode(OPR_LE, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2115 "y.tab.c"
    break;

  case 96: /* expr: expr EQ expr  */
#line 448 "parser.y"
                   { (yyval.node) = oprNode(OPR_EQ, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2121 "y.tab.c"
    break;

  case 97: /* expr: expr NE expr  */
#line 449 "parser.y"
                   { (yyval.node) = oprNode(OPR_NE, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2127 "y.tab.c"
    break;

  case 98: /* expr: expr AND expr  */
#line 450 "parser.y"
                    { (yyval.node) = oprNode(OPR_AND, 2, (yyvsp[-2].node), (yyvsp[0].node)); (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2133 "y.tab.c"
    break;

  case 99: /* expr: expr OR expr  */
#line 451 "parser.y"
                   { (yyval.node) = oprNode(OPR_OR, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2139 "y.tab.c"
    break;

  case 100: /* expr: '(' expr ')'  */
#line 452 "parser.y"
                   { (yyval.node) = (yyvsp[-1].node);   (yyval.node)->exprType.op = (yyvsp[-1].node)->exprType.op;}
#line 2145 "y.tab.c"
    break;

  case 101: /* expr: arrayExpr  */
#line 453 "parser.y"
                {(yyval.node) = (yyvsp[0].node);       (yyval.node)->exprType.op = (yyvsp[0].node)->exprType.op;}
#line 2151 "y.tab.c"
    break;

  case 102: /* arrayExpr: expr '[' expr ']'  */
#line 458 "parser.y"
                                       {
        printf("Found array expression type %d\n", (yyvsp[-3].node)->exprType.ndim);
        if((yyvsp[-3].node)->exprType.op != T_ARRAY){
            compileError((yyvsp[-3].node)->src, (yyvsp[-3].node)->src.length + (yyvsp[-1].node)->src.length + 2, "Invalid indexing target. Only array types can be indexed.");
        }
        if((yyvsp[-1].node)->exprType.op != T_INT){
            compileError((yyvsp[-1].node)->src, (yyvsp[-1].node)->src.length, "Only int types can be used as indices.");
        }
        (yyval.node) = oprNode('[', 2, (yyvsp[-3].node), (yyvsp[-1].node));
        (yyval.node)->exprType.op = (yyvsp[-3].node)->exprType.ndim == 1 ? (yyvsp[-3].node)->exprType.base : T_ARRAY;
        (yyval.node)->exprType.ndim = (yyvsp[-3].node)->exprType.ndim - 1;
        // $$->exprType.op = $1->exprType.op->type;
        (yyval.node)->src.length = (yyvsp[-3].node)->src.length + (yyvsp[-1].node)->src.length + 2;
    }
#line 2170 "y.tab.c"
    break;

  case 103: /* callExpr: IDENTIFIER '(' arg_list ')'  */
#line 473 "parser.y"
                                      {
                Symbol* callee = lookup((yyvsp[-3].id).name, identifiers);
                if(!callee){
                    // compileError("Error: Function '%s' not defined", $1);
                    compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Function '%s' not defined", (yyvsp[-3].id).name);
                }
                if(callee->type->op != T_FUNCTION){
                    compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Identifier '%s' is not a function", (yyvsp[-3].id).name);
                }
                
                //Type check all parameters
                Node *param = (yyvsp[-1].node);
                int i=callee->type->size-1;
                printf("Starting with %d params\n", i);
                if(param){
                    printf("here\n");
                    while(param->as.opr.nops==2 && i >= 0){
                        printf("Comparing with original type %d\n", callee->type->proto[i]->op);
                        if(!typeCheckAssign(callee->type->proto[i]->op, param->as.opr.operands[1]->exprType.op)){
                            compileError(param->as.opr.operands[1]->src, param->as.opr.operands[1]->src.length, "Type mismatch in function call to '%s'", (yyvsp[-3].id).name);
                        }
                        param = param->as.opr.operands[0];
                        i--;
                    }
                    printf("inside %d\n", callee->type->proto[i] == NULL);
                    printf("Comparing with original type %d \n", /* param->exprType.op, */ callee->type->proto[i]->op);
                    if(i<0) {
                            compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Too many parameters in function call to '%s'", (yyvsp[-3].id).name);
                    }
                    if(!typeCheckAssign(callee->type->proto[i]->op, param->exprType.op)){
                        compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Type mismatch in function call to '%s'", (yyvsp[-3].id).name);
                    }
                    i--;
                }
                if(i >= 0){
                    compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Too few parameters in function call to '%s'; expected %d", (yyvsp[-3].id).name, callee->type->size);
                }
                (yyval.node) = oprNode(OPR_CALL, 2, identifierNode(callee), (yyvsp[-1].node));
                (yyval.node)->exprType.op = callee->type->type->op;
                printNode((yyval.node));
    }
#line 2216 "y.tab.c"
    break;

  case 104: /* arg_list: expr  */
#line 515 "parser.y"
               {(yyval.node) = (yyvsp[0].node);/* oprNode(OPR_LIST, 1,$1); */}
#line 2222 "y.tab.c"
    break;

  case 105: /* arg_list: arg_list ',' expr  */
#line 516 "parser.y"
                        {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2228 "y.tab.c"
    break;

  case 106: /* arg_list: %empty  */
#line 517 "parser.y"
      {(yyval.node) = NULL;}
#line 2234 "y.tab.c"
    break;

  case 107: /* returnStmt: RETURN  */
#line 520 "parser.y"
                   {
                Coordinate src;
                src.line = lineno;
                src.col = 0;
                compileError(src, 0, "Expected an expression to return");
                (yyval.node) = oprNode(OPR_RETURN, 0);
            }
#line 2246 "y.tab.c"
    break;

  case 108: /* returnStmt: RETURN expr  */
#line 527 "parser.y"
                      {
            printf("Checking types %d %d\n", currentFunctionType->type->op, (yyvsp[0].node)->exprType.op);
            if(!typeCheckAssign(currentFunctionType->type->op, (yyvsp[0].node)->exprType.op)){
                compileError((yyvsp[0].node)->src, (yyvsp[0].node)->src.length, "Type mismatch in return statement");
            }
            (yyval.node) = oprNode(OPR_RETURN, 1, (yyvsp[0].node));
        }
#line 2258 "y.tab.c"
    break;

  case 109: /* continueStmt: CONTINUE  */
#line 536 "parser.y"
                       {(yyval.node) = oprNode(OPR_CONTINUE, 0);}
#line 2264 "y.tab.c"
    break;

  case 110: /* breakStmt: BREAK  */
#line 538 "parser.y"
                 {(yyval.node) = oprNode(OPR_BREAK, 0);}
#line 2270 "y.tab.c"
    break;


#line 2274 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 540 "parser.y"

void typeCheckArrayInitialiser(Type* elementType, Node* expr){
    Node* exprList = expr;
    /* printf("Starting array %d\n", elementType->type->op, exprList); */
    if(exprList == NULL) return;
    //if it is not a list, this is the last element
    if(exprList->as.opr.nops == 1){
        Node* insideElement = exprList->as.opr.operands[0];
        printf("Checking 1) %d %d\n", elementType->type->op, insideElement->exprType.op);
        if(!typeCheckAssign(elementType->type->op, insideElement->exprType.op)){
            compileError( insideElement->src,  insideElement->src.length, "Invalid array element type");
        }
        if(insideElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, insideElement);
        }
    } else {
        //this is a list, so check the second operand
        //if it is a list, it will be checked recursively
        /* printf("Checking %d %d\n", elementType->type->op, exprList->as.opr.operands[1]->exprType.op); */
        Node* localElement = exprList->as.opr.operands[1];
        if(localElement->exprType.op != elementType->type->op){
            compileError(localElement->src, localElement->src.length, "Invalid array element type 2");
        }
        if(localElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, exprList->as.opr.operands[1]);
        }
        //advance to next element in list
        typeCheckArrayInitialiser(elementType, exprList->as.opr.operands[0]);
    }
}
void typeCheckUnary(Node* node){
    int invalid = 0;
    switch(node->type){
        case NODE_LITERAL:
            //cannot operate on strings
            invalid = (node->as.value->type == T_ARRAY);
            break;
        case NODE_SYMBOL:
            //cannot operate on arrays
            invalid = (node->as.symbol->type->op == T_ARRAY);
            break;
        case NODE_OPR:
            //cannot operate on arrays
            invalid = (node->exprType.op == T_ARRAY);
            break;
        default:
            invalid = 1;
            break;
    }
    if(invalid){
        Coordinate src;
        src.line=lineno;
        src.col = col;
        compileError(src, 1, "Invalid operand type");
    }
}
/* Type check two types
   Tries to widen a type to match the other,
   otherwise raises compileError.
 */
int typeCheckAssign(TypeEnum varType, TypeEnum exprType){
    //exprType cannot larger than varType
    if(varType != T_ARRAY && exprType == T_ARRAY){
        return 0;
    }
    if(varType == T_ARRAY && exprType != T_ARRAY){
        return 0;
    }

    if(exprType == T_FLOAT && varType != T_FLOAT){
        return 0;
    }
    return 1;
}

TypeEnum typeWiden(TypeEnum t1, TypeEnum t2){
    //arrays are not allowed
    if(t1 == T_ARRAY || t2 == T_ARRAY){
        return -1;
    }
    if(t1 == T_FLOAT || t2 == T_FLOAT){
        return T_FLOAT;
    }
    if(t1 == T_INT || t2 == T_INT){
        return T_INT;
    }
    if(t1 == T_CHAR || t2 == T_CHAR){
        return T_CHAR;
    }
    return -1;
}


void point_at_in_line(int lineno, int from, int to);

Symbol* getSymbol(char* name, SymbolTable* table, Coordinate src, char* format, ...){
    Symbol* foundIdentifier = lookup(name, table);
    if(!foundIdentifier){
        va_list args;
        va_start(args, format);
        fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] " ANSI_COLOR_RESET, currentFileName, src.line, src.col);
        fprintf(stderr, "Error: ");
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        point_at_in_line(src.line-1, src.col -1 , src.col + strlen(name) -1 );
        va_end(args);
        exit(1);
    }
    return foundIdentifier;
}



/**
    * Prints a message to stderr and exits the program
    * @param format The format string
    * @param ... The arguments to the format string
*/

void compileError(Coordinate src, int lexemeLength, char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] " ANSI_COLOR_RESET, currentFileName, src.line, src.col);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    point_at_in_line(src.line-1, src.col -1 , src.col + lexemeLength -1 );
    va_end(args);
    exit(1);
}
// Prints the error but does not exit.
void errorMessage(Coordinate src, int lexemeLength, char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] " ANSI_COLOR_RESET, currentFileName, src.line, src.col);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    point_at_in_line(src.line-1, src.col -1 , src.col + lexemeLength -1 );
    va_end(args);
}
/* int main(int argc, char* argv[]){
    return 0;
} */
/* int yyerror(char *s){
  exit(1);
  return 1;
} */
