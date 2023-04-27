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
void typeCheckUnary(Node* t);
void typeCheckArrayInitialiser(Type* elementType, Node* expr);

Node* param_list_node, *funcBodyNode;
int yylex();

#line 99 "y.tab.c"

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
#line 29 "parser.y"

    int iValue;
    float fValue;
    char* sValue;
    IdStruct id;
    char cValue;
    int* sizes;
    Node* node;

#line 238 "y.tab.c"

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
  YYSYMBOL_funcArraySpecifier = 63,        /* funcArraySpecifier  */
  YYSYMBOL_param_list = 64,                /* param_list  */
  YYSYMBOL_varInitialiser = 65,            /* varInitialiser  */
  YYSYMBOL_arrayInitialiser = 66,          /* arrayInitialiser  */
  YYSYMBOL_array_init_list = 67,           /* array_init_list  */
  YYSYMBOL_varDeclaration = 68,            /* varDeclaration  */
  YYSYMBOL_varType = 69,                   /* varType  */
  YYSYMBOL_varNames = 70,                  /* varNames  */
  YYSYMBOL_arraySpecifier = 71,            /* arraySpecifier  */
  YYSYMBOL_funcBody = 72,                  /* funcBody  */
  YYSYMBOL_73_2 = 73,                      /* @2  */
  YYSYMBOL_stmtOrDecl = 74,                /* stmtOrDecl  */
  YYSYMBOL_stmt = 75,                      /* stmt  */
  YYSYMBOL_forStmt = 76,                   /* forStmt  */
  YYSYMBOL_77_3 = 77,                      /* $@3  */
  YYSYMBOL_forInit = 78,                   /* forInit  */
  YYSYMBOL_forCond = 79,                   /* forCond  */
  YYSYMBOL_forIter = 80,                   /* forIter  */
  YYSYMBOL_assignExpr = 81,                /* assignExpr  */
  YYSYMBOL_switchStmt = 82,                /* switchStmt  */
  YYSYMBOL_83_4 = 83,                      /* $@4  */
  YYSYMBOL_84_5 = 84,                      /* $@5  */
  YYSYMBOL_switchBody = 85,                /* switchBody  */
  YYSYMBOL_switchList = 86,                /* switchList  */
  YYSYMBOL_caseLabel = 87,                 /* caseLabel  */
  YYSYMBOL_88_6 = 88,                      /* $@6  */
  YYSYMBOL_caseType = 89,                  /* caseType  */
  YYSYMBOL_whileStmt = 90,                 /* whileStmt  */
  YYSYMBOL_blockStmt = 91,                 /* blockStmt  */
  YYSYMBOL_92_7 = 92,                      /* $@7  */
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
#define YYLAST   495

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  190

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
       0,    85,    85,    92,    93,    96,    97,    98,   102,   101,
     160,   160,   161,   171,   184,   187,   191,   195,   197,   199,
     200,   201,   202,   210,   292,   292,   292,   294,   295,   297,
     300,   303,   306,   306,   311,   312,   313,   321,   322,   324,
     326,   327,   328,   329,   330,   331,   332,   333,   336,   336,
     341,   342,   343,   346,   347,   350,   351,   354,   362,   370,
     378,   385,   391,   400,   404,   400,   405,   405,   406,   407,
     408,   409,   410,   411,   422,   422,   431,   431,   433,   435,
     435,   441,   442,   444,   445,   446,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   474,   489,   536,   537,
     538,   541,   548,   557,   559
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
  "declaration", "functionDecl", "$@1", "funcArraySpecifier", "param_list",
  "varInitialiser", "arrayInitialiser", "array_init_list",
  "varDeclaration", "varType", "varNames", "arraySpecifier", "funcBody",
  "@2", "stmtOrDecl", "stmt", "forStmt", "$@3", "forInit", "forCond",
  "forIter", "assignExpr", "switchStmt", "$@4", "$@5", "switchBody",
  "switchList", "caseLabel", "$@6", "caseType", "whileStmt", "blockStmt",
  "$@7", "ifStmt", "expr", "arrayExpr", "callExpr", "arg_list",
  "returnStmt", "continueStmt", "breakStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-119)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -119,     5,     3,  -119,  -119,  -119,  -119,  -119,  -119,   -17,
       4,    42,  -119,  -119,    20,  -119,    25,    21,   -32,    46,
       6,    53,   -13,    76,  -119,  -119,  -119,    21,    36,    40,
    -119,  -119,  -119,  -119,  -119,    33,   270,   270,    76,   270,
    -119,   435,  -119,  -119,    38,    64,    56,  -119,  -119,   270,
      58,   329,  -119,     0,   435,    58,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
    -119,  -119,    36,  -119,   435,    11,  -119,    76,  -119,   450,
     450,    59,    59,    59,    59,    59,    59,    70,    70,    58,
      58,    58,   417,  -119,  -119,  -119,   270,  -119,   435,  -119,
     153,   435,    57,    63,    67,  -119,   270,  -119,  -119,   -31,
    -119,  -119,  -119,    69,    46,  -119,  -119,    72,  -119,  -119,
    -119,  -119,   435,   -20,    73,    74,    75,    78,  -119,   270,
     270,    79,   435,  -119,  -119,   270,  -119,  -119,  -119,  -119,
    -119,   270,  -119,  -119,  -119,  -119,   224,   351,   373,   270,
     435,   207,   435,  -119,    82,  -119,   258,   258,   395,  -119,
     270,  -119,    97,  -119,    83,   435,   258,    65,   274,  -119,
     136,    84,  -119,  -119,  -119,  -119,  -119,    81,   136,  -119,
    -119,   258,  -119,  -119,  -119,  -119,   270,  -119,   302,  -119
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,    24,    26,    25,     2,     3,     5,
       0,     0,     6,     7,    31,    27,    23,    14,    15,     0,
       0,     0,     0,     0,    31,    28,     8,     0,    11,     0,
      30,    83,    86,    84,    87,    85,     0,     0,     0,     0,
      17,    16,   105,    88,     0,     0,     0,    12,    29,   110,
      89,     0,    21,     0,    19,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     9,    11,    10,   108,     0,   104,     0,    18,   102,
     103,    98,    99,   100,   101,    96,    95,    91,    92,    93,
      94,    97,     0,    36,    13,   107,     0,    22,    20,   106,
       0,   109,     0,     0,     0,    63,   111,   113,   114,    85,
      37,    79,    33,     0,     0,    34,    43,     0,    44,    42,
      38,    41,     0,   105,    88,     0,     0,     0,    48,     0,
       0,     0,   112,    58,    59,     0,    36,    35,    39,    61,
      62,     0,    40,    45,    47,    46,    52,     0,     0,     0,
      57,     0,    60,    51,     0,    50,     0,     0,     0,    80,
      54,    78,    81,    64,     0,    53,     0,     0,    56,    82,
      67,     0,    55,    76,    77,    69,    68,     0,    66,    70,
      74,     0,    65,    73,    72,    71,     0,    49,     0,    75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -119,  -119,  -119,  -119,  -119,  -119,    52,  -119,   114,   -28,
    -119,    -2,     2,  -119,  -119,  -119,  -119,     1,   -93,  -119,
    -119,  -119,  -119,  -119,  -118,  -119,  -119,  -119,  -119,  -119,
     -42,  -119,  -119,  -119,  -119,  -119,  -119,   -22,   -98,   -91,
    -119,  -119,  -119,  -119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    44,    47,    20,    15,    40,
      53,   113,   114,    16,    18,    71,    93,   100,   115,   116,
     146,   154,   164,   171,   117,   118,   131,   167,   177,   178,
     179,   186,   180,   119,   120,   136,   121,   122,    42,    43,
      75,   125,   126,   127
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      10,    41,   123,    29,    11,     3,     4,     5,     6,   124,
      52,   133,   134,    22,    50,    51,    54,    55,    49,    21,
      23,   135,   139,   140,     4,     5,     6,    74,   155,    45,
       7,    12,   141,    30,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,   123,    97,
     172,    77,    13,   123,    78,    98,    26,    27,   123,   123,
     124,    95,    96,   161,   162,   124,   124,    14,   123,    17,
     123,    24,   123,   169,   101,   124,    19,   176,    28,   124,
     123,    46,    49,   123,   132,   184,    48,   124,   187,    72,
     124,    70,    31,    32,    33,    34,    64,    65,    66,    67,
      68,    35,    73,    69,    69,   166,   128,   147,   148,    66,
      67,    68,   129,   150,    36,    69,   130,   137,   170,   152,
     138,   142,   143,   144,    94,    37,   145,   158,   149,    38,
     160,   168,    39,    25,   181,   182,   185,   151,   165,     4,
       5,     6,   102,   103,   153,   104,   105,   173,   106,   107,
     108,   174,    31,    32,    33,    34,     4,     5,     6,   102,
     103,   109,   104,   105,   188,   106,   107,   108,   175,    31,
      32,    33,    34,     0,    36,     0,   183,     0,   109,     0,
       0,     0,     0,     0,   110,    37,     0,     0,     0,   111,
       0,    36,    39,     0,     0,     0,     0,     0,     0,     0,
       0,   110,    37,     0,     0,     0,   111,   112,     0,    39,
       4,     5,     6,   102,   103,     0,   104,   105,     0,   106,
     107,   108,     0,    31,    32,    33,    34,     4,     5,     6,
       0,     0,   109,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,     0,    36,     0,     0,     0,   109,
       0,     0,     0,     0,     0,   110,    37,     0,     0,     0,
     111,   159,    36,    39,   102,   103,     0,   104,   105,     0,
     106,   107,   108,    37,    31,    32,    33,    34,     0,     0,
      39,     0,     0,   109,     0,     0,    31,    32,    33,    34,
      31,    32,    33,    34,     0,    35,    36,     0,     0,   109,
       0,     0,     0,     0,     0,     0,   110,    37,    36,     0,
       0,   111,    36,     0,    39,     0,     0,     0,     0,    37,
       0,     0,     0,    37,     0,     0,    39,     0,     0,     0,
      39,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   189,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,     0,     0,     0,    69,     0,     0,     0,     0,    76,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,     0,     0,     0,    69,     0,     0,     0,
       0,   156,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,     0,     0,     0,    69,     0,
       0,     0,     0,   157,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,     0,     0,     0,
      69,     0,     0,     0,     0,   163,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,     0,
       0,     0,    69,    99,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,     0,     0,     0,
      69,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,     0,     0,     0,    69
};

static const yytype_int16 yycheck[] =
{
       2,    23,   100,    16,     2,     0,     3,     4,     5,   100,
      38,    42,    43,    45,    36,    37,    38,    39,    49,    17,
      52,    52,    42,    43,     3,     4,     5,    49,   146,    27,
      27,    48,    52,    46,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   146,    77,
     168,    51,    48,   151,    54,    77,    50,    51,   156,   157,
     151,    50,    51,   156,   157,   156,   157,    25,   166,    49,
     168,    25,   170,   166,    96,   166,    51,   170,    25,   170,
     178,    45,    49,   181,   106,   178,    46,   178,   181,    25,
     181,    53,    16,    17,    18,    19,    37,    38,    39,    40,
      41,    25,    46,    45,    45,     8,    49,   129,   130,    39,
      40,    41,    49,   135,    38,    45,    49,    48,    53,   141,
      48,    48,    48,    48,    72,    49,    48,   149,    49,    53,
      48,    48,    56,    19,    50,    54,   178,   136,   160,     3,
       4,     5,     6,     7,   146,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     3,     4,     5,     6,
       7,    25,     9,    10,   186,    12,    13,    14,   170,    16,
      17,    18,    19,    -1,    38,    -1,   178,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    53,
      -1,    38,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
       3,     4,     5,     6,     7,    -1,     9,    10,    -1,    12,
      13,    14,    -1,    16,    17,    18,    19,     3,     4,     5,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    -1,    38,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,
      53,    54,    38,    56,     6,     7,    -1,     9,    10,    -1,
      12,    13,    14,    49,    16,    17,    18,    19,    -1,    -1,
      56,    -1,    -1,    25,    -1,    -1,    16,    17,    18,    19,
      16,    17,    18,    19,    -1,    25,    38,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    38,    -1,
      -1,    53,    38,    -1,    56,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    49,    -1,    -1,    56,    -1,    -1,    -1,
      56,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    50,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    50,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    50,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    50,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    45,    46,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    58,    59,     0,     3,     4,     5,    27,    60,    61,
      68,    69,    48,    48,    25,    65,    70,    49,    71,    51,
      64,    69,    45,    52,    25,    65,    50,    51,    25,    16,
      46,    16,    17,    18,    19,    25,    38,    49,    53,    56,
      66,    94,    95,    96,    62,    69,    45,    63,    46,    49,
      94,    94,    66,    67,    94,    94,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    45,
      53,    72,    25,    46,    94,    97,    50,    51,    54,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    73,    63,    50,    51,    66,    94,    46,
      74,    94,     6,     7,     9,    10,    12,    13,    14,    25,
      48,    53,    54,    68,    69,    75,    76,    81,    82,    90,
      91,    93,    94,    95,    96,    98,    99,   100,    49,    49,
      49,    83,    94,    42,    43,    52,    92,    48,    48,    42,
      43,    52,    48,    48,    48,    48,    77,    94,    94,    49,
      94,    74,    94,    68,    78,    81,    50,    50,    94,    54,
      48,    75,    75,    50,    79,    94,     8,    84,    48,    75,
      53,    80,    81,    11,    15,    68,    75,    85,    86,    87,
      89,    50,    54,    68,    75,    87,    88,    75,    94,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    60,    62,    61,
      63,    63,    64,    64,    64,    65,    65,    65,    66,    67,
      67,    67,    67,    68,    69,    69,    69,    70,    70,    71,
      71,    71,    73,    72,    74,    74,    74,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    77,    76,
      78,    78,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    81,    83,    84,    82,    85,    85,    86,    86,
      86,    86,    86,    86,    88,    87,    89,    89,    90,    92,
      91,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    95,    96,    97,    97,
      97,    98,    98,    99,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     2,     2,     0,     7,
       2,     0,     3,     5,     0,     2,     4,     4,     3,     1,
       3,     1,     3,     2,     1,     1,     1,     1,     3,     4,
       3,     0,     0,     4,     2,     3,     0,     1,     1,     2,
       2,     1,     1,     1,     1,     2,     2,     2,     0,    10,
       1,     1,     0,     1,     0,     1,     0,     3,     2,     2,
       3,     2,     2,     0,     0,     9,     1,     0,     1,     1,
       1,     2,     2,     2,     0,     4,     1,     1,     5,     0,
       4,     5,     7,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     4,     1,     3,
       0,     1,     2,     1,     1
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
#line 85 "parser.y"
                                { 
                        printf("Program end\n"); 
                        backend((yyvsp[-1].node), currentFileName);
                        return 0;
                    }
#line 1518 "y.tab.c"
    break;

  case 3: /* declarations: declarations declaration  */
#line 92 "parser.y"
                                       { (yyval.node) = oprNode(OPR_DECL_LIST, 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1524 "y.tab.c"
    break;

  case 4: /* declarations: %empty  */
#line 93 "parser.y"
      {(yyval.node) = NULL;}
#line 1530 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 102 "parser.y"
                        {
                            Type* funcType = malloc(sizeof(Type));
                            funcType->sym = NULL;
                            funcType->op = T_FUNCTION;
                            funcType->type = malloc(sizeof(Type));
                            funcType->type->op = (yyvsp[-4].iValue);
                            currentFunctionType = funcType;
                            beginScope();
                        }
#line 1544 "y.tab.c"
    break;

  case 9: /* functionDecl: varType IDENTIFIER '(' param_list ')' $@1 funcBody  */
#line 112 "parser.y"
                {
                    endScope();
                    Symbol* funcSymbol = install((yyvsp[-5].id).name, &identifiers, level, (yyvsp[-5].id).src);
                            if(funcSymbol->type){
                                compileError((yyvsp[-5].id).src, strlen((yyvsp[-5].id).name), "Function %s already declared", (yyvsp[-5].id).name);
                            }
                            // Type* funcType = malloc(sizeof(Type));
                            // funcType->sym = funcSymbol;
                            // funcType->op = T_FUNCTION;
                            // funcType->type = malloc(sizeof(Type));
                            // funcType->type->op = $1;
                            // currentFunctionType = funcType;
                            Type* funcType = currentFunctionType;
                            funcSymbol->type = currentFunctionType;
                            int numParams=0;
                            Node* temp = (yyvsp[-3].node);
                            while(temp){
                                numParams++;
                                if(temp->as.opr.nops == 2)
                                    temp = temp->as.opr.operands[0];
                                else temp = NULL;
                            }
                            funcType->size = numParams;
                            funcType->proto = malloc(sizeof(Type*) * numParams);
                            Node* param = (yyvsp[-3].node);
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
                            // if(funcType->proto)
                            printf("func proto %d\n",1/* ,  funcType->proto[0]->op */);
                    // Symbol* funcSymbol = lookup($2.name, identifiers);
                    // printNode(param_list_node);
                    (yyval.node) = oprNode(OPR_FUNC, 3, identifierNode(funcSymbol), param_list_node, funcBodyNode);
                    currentFunctionType = NULL;
                }
#line 1596 "y.tab.c"
    break;

  case 12: /* param_list: varType IDENTIFIER funcArraySpecifier  */
#line 161 "parser.y"
                                                  {
                        Symbol* psym = install((yyvsp[-1].id).name, &identifiers, level, (yyvsp[-1].id).src);
                        (yyval.node) = oprNode(OPR_LIST, 1, identifierNode(psym)); 
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = (yyvsp[-2].iValue);
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                        param_list_node = (yyval.node);
                    }
#line 1611 "y.tab.c"
    break;

  case 13: /* param_list: param_list ',' varType IDENTIFIER funcArraySpecifier  */
#line 171 "parser.y"
                                                           {
                        Symbol* psym = install((yyvsp[-1].id).name, &identifiers, level, (yyvsp[-1].id).src);
                        if(psym->type){
                            compileError((yyvsp[-1].id).src, strlen((yyvsp[-1].id).name), "Parameter %s already declared", (yyvsp[-1].id).name);
                        }
                        Type* paramType = malloc(sizeof(Type));
                        paramType->op = (yyvsp[-2].iValue);
                        paramType->type=NULL;
                        paramType->sym = psym;
                        psym->type = paramType;
                        (yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-4].node), identifierNode(psym));
                        param_list_node = (yyval.node);
                    }
#line 1629 "y.tab.c"
    break;

  case 14: /* param_list: %empty  */
#line 184 "parser.y"
      {(yyval.node)=NULL; param_list_node = NULL;}
#line 1635 "y.tab.c"
    break;

  case 15: /* varInitialiser: IDENTIFIER arraySpecifier  */
#line 187 "parser.y"
                                          {
                                    (yyval.node) = oprNode('=', 2, identifierNode(install((yyvsp[-1].id).name, &identifiers, level, (yyvsp[-1].id).src)), (yyvsp[0].node));
                                    (yyval.node)->src = (yyvsp[-1].id).src;
                                    }
#line 1644 "y.tab.c"
    break;

  case 16: /* varInitialiser: IDENTIFIER arraySpecifier '=' expr  */
#line 191 "parser.y"
                                         {
                                    (yyval.node) = oprNode('=', 3, identifierNode(install((yyvsp[-3].id).name, &identifiers, level, (yyvsp[-3].id).src)), (yyvsp[-2].node), (yyvsp[0].node));
                                    (yyval.node)->src = (yyvsp[-3].id).src;
                                    }
#line 1653 "y.tab.c"
    break;

  case 17: /* varInitialiser: IDENTIFIER arraySpecifier '=' arrayInitialiser  */
#line 195 "parser.y"
                                                     {(yyval.node) = oprNode('=', 3, identifierNode(install((yyvsp[-3].id).name, &identifiers, level, (yyvsp[-3].id).src)), (yyvsp[-2].node), (yyvsp[0].node)); (yyval.node)->src = (yyvsp[-3].id).src;}
#line 1659 "y.tab.c"
    break;

  case 18: /* arrayInitialiser: '{' array_init_list '}'  */
#line 197 "parser.y"
                                          { (yyval.node) = (yyvsp[-1].node); (yyval.node)->exprType.op = T_ARRAY;}
#line 1665 "y.tab.c"
    break;

  case 19: /* array_init_list: expr  */
#line 199 "parser.y"
                      { /* $$ = oprNode(OPR_LIST, 1, $1); */}
#line 1671 "y.tab.c"
    break;

  case 20: /* array_init_list: array_init_list ',' expr  */
#line 200 "parser.y"
                               { (yyval.node) = oprNode(OPR_LIST, 3, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1677 "y.tab.c"
    break;

  case 21: /* array_init_list: arrayInitialiser  */
#line 201 "parser.y"
                       { /* $$ = oprNode(OPR_LIST, 1, $1); */(yyval.node) = (yyvsp[0].node); (yyval.node)->exprType.op = T_ARRAY;}
#line 1683 "y.tab.c"
    break;

  case 22: /* array_init_list: array_init_list ',' arrayInitialiser  */
#line 202 "parser.y"
                                           { (yyval.node) = oprNode(OPR_LIST, 3, (yyvsp[-2].node), (yyvsp[0].node), NULL); (yyval.node)->exprType.op = T_ARRAY;}
#line 1689 "y.tab.c"
    break;

  case 23: /* varDeclaration: varType varNames  */
#line 210 "parser.y"
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
            Type* outerType = type;
            do {
                arrLastSize = arraySpecifier->as.opr.operands[1]->as.value->as.integer;
                //check if size is declared for dimensions other than first
                if(arrLastSize <= 0 && arraySpecifier->as.opr.operands[0] != NULL){
                    compileError(src, strlen(varSymbol->name), "Array dimensions except the first cannot be empty %d", arrLastSize);
                }
                Type* innerType = malloc(sizeof(Type));
                outerType->sym = installed;
                outerType->op = T_ARRAY;
                outerType->size = arrLastSize;
                outerType->type = innerType;
                outerType = innerType;
            } while((arraySpecifier = arraySpecifier->as.opr.operands[0]));
            outerType->sym = installed;
            outerType->op = (yyvsp[-1].iValue);
            outerType->size = arrLastSize;
            // installed->type=outerType;
            printf("Innermost type is %d\n", outerType->op);
        }

        // printf("\nType op of this var is %d\n", installed->type->op);
        
        //Check if there is an initialiser expression assignment
        if(varInitialiser->as.opr.nops == 3){
            Node* expr = varInitialiser->as.opr.operands[2];
            // printf("Found initialiser %d\n", expr->exprType);
            if(!typeCheckAssign(installed->type->op, expr->exprType.op)){
                compileError(src, strlen(varSymbol->name), "Type mismatch in variable initialisation of '%s'", varSymbol->name);
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
#line 1774 "y.tab.c"
    break;

  case 24: /* varType: K_INT  */
#line 292 "parser.y"
               {(yyval.iValue) = T_INT;}
#line 1780 "y.tab.c"
    break;

  case 25: /* varType: K_CHAR  */
#line 292 "parser.y"
                                      {(yyval.iValue) = T_CHAR;}
#line 1786 "y.tab.c"
    break;

  case 26: /* varType: K_FLOAT  */
#line 292 "parser.y"
                                                              {(yyval.iValue) = T_FLOAT;}
#line 1792 "y.tab.c"
    break;

  case 28: /* varNames: varNames ',' varInitialiser  */
#line 295 "parser.y"
                                  {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1798 "y.tab.c"
    break;

  case 29: /* arraySpecifier: arraySpecifier '[' INTEGER ']'  */
#line 297 "parser.y"
                                               {
                                        (yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-3].node), intNode((yyvsp[-1].iValue)));
                                    }
#line 1806 "y.tab.c"
    break;

  case 30: /* arraySpecifier: arraySpecifier '[' ']'  */
#line 300 "parser.y"
                             {
                            (yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), intNode(0));
                        }
#line 1814 "y.tab.c"
    break;

  case 31: /* arraySpecifier: %empty  */
#line 303 "parser.y"
      { (yyval.node) = NULL; }
#line 1820 "y.tab.c"
    break;

  case 32: /* @2: %empty  */
#line 306 "parser.y"
              {beginScope(); (yyval.node) = NULL;}
#line 1826 "y.tab.c"
    break;

  case 33: /* funcBody: '{' @2 stmtOrDecl '}'  */
#line 308 "parser.y"
              {endScope(); (yyval.node) = (yyvsp[-2].node); printf("Printing stmtordecl\n"); printNode(funcBodyNode);}
#line 1832 "y.tab.c"
    break;

  case 34: /* stmtOrDecl: stmtOrDecl stmt  */
#line 311 "parser.y"
                            {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-1].node), (yyvsp[0].node)); funcBodyNode = (yyval.node);}
#line 1838 "y.tab.c"
    break;

  case 35: /* stmtOrDecl: stmtOrDecl varDeclaration ';'  */
#line 312 "parser.y"
                                    {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), (yyvsp[-1].node)); funcBodyNode = (yyval.node);}
#line 1844 "y.tab.c"
    break;

  case 36: /* stmtOrDecl: %empty  */
#line 313 "parser.y"
      {(yyval.node) = NULL; funcBodyNode = (yyval.node);}
#line 1850 "y.tab.c"
    break;

  case 37: /* stmt: ';'  */
#line 321 "parser.y"
          {(yyval.node) = NULL;}
#line 1856 "y.tab.c"
    break;

  case 48: /* $@3: %empty  */
#line 336 "parser.y"
                 {beginScope();}
#line 1862 "y.tab.c"
    break;

  case 49: /* forStmt: FOR '(' $@3 forInit ';' forCond ';' forIter ')' stmt  */
#line 336 "parser.y"
                                                                          {
    endScope();
    (yyval.node) = oprNode(OPR_FOR, 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
}
#line 1871 "y.tab.c"
    break;

  case 52: /* forInit: %empty  */
#line 343 "parser.y"
      {(yyval.node) = NULL;}
#line 1877 "y.tab.c"
    break;

  case 54: /* forCond: %empty  */
#line 347 "parser.y"
      {(yyval.node) = NULL;}
#line 1883 "y.tab.c"
    break;

  case 56: /* forIter: %empty  */
#line 351 "parser.y"
      {(yyval.node)=NULL;}
#line 1889 "y.tab.c"
    break;

  case 57: /* assignExpr: IDENTIFIER '=' expr  */
#line 354 "parser.y"
                                {
                // printf("Found assign target\n");
                Symbol* sym = getSymbol((yyvsp[-2].id).name, identifiers, (yyvsp[-2].id).src, "Variable '%s' not declared", (yyvsp[-2].id).name);
                if(!typeCheckAssign(sym->type->op, (yyvsp[0].node)->exprType.op)){
                    compileError((yyvsp[-2].id).src, strlen((yyvsp[-2].id).name), "Type mismatch in assignment %s", (yyvsp[-2].id).name);
                }
                (yyval.node) = oprNode(OPR_ASSIGN, 2, identifierNode(sym), (yyvsp[0].node));
            }
#line 1902 "y.tab.c"
    break;

  case 58: /* assignExpr: IDENTIFIER INC  */
#line 362 "parser.y"
                     {
                Symbol* sym = getSymbol((yyvsp[-1].id).name, identifiers, (yyvsp[-1].id).src, "Variable '%s' not declared", (yyvsp[-1].id).name);
                compileError((Coordinate){lineno, col-2}, 2, "Increment operator not allowed");
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError((yyvsp[-1].id).src, strlen((yyvsp[-1].id).name), "Only int and float can be incremented %s", (yyvsp[-1].id).name);
                }
                (yyval.node) = oprNode(OPR_INC, 1, identifierNode(sym));
            }
#line 1915 "y.tab.c"
    break;

  case 59: /* assignExpr: IDENTIFIER DEC  */
#line 370 "parser.y"
                     {
                Symbol* sym = getSymbol((yyvsp[-1].id).name, identifiers, (yyvsp[-1].id).src, "Variable '%s' not declared", (yyvsp[-1].id).name);
                compileError((Coordinate){lineno, col-2}, 2, "Decrement operator not allowed");
                if(sym->type->op != T_INT && sym->type->op != T_FLOAT){
                    compileError((yyvsp[-1].id).src, strlen((yyvsp[-1].id).name), "Only int and float can be decremented %s", (yyvsp[-1].id).name);
                }
                (yyval.node) = oprNode(OPR_DEC, 1, identifierNode(sym));
            }
#line 1928 "y.tab.c"
    break;

  case 60: /* assignExpr: arrayExpr '=' expr  */
#line 378 "parser.y"
                         {
                printf("Got array type as %d = %d\n", (yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);
                if(!typeCheckAssign((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op)){
                    compileError((yyvsp[-2].node)->src, (yyvsp[0].node)->src.length + (yyvsp[-2].node)->src.length, "Type mismatch in assignment to array");
                }
                (yyval.node) = oprNode(OPR_ASSIGN, 2, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1940 "y.tab.c"
    break;

  case 61: /* assignExpr: arrayExpr INC  */
#line 385 "parser.y"
                    {
                if((yyvsp[-1].node)->exprType.op != T_INT && (yyvsp[-1].node)->exprType.op != T_FLOAT){
                    compileError((yyvsp[-1].node)->src, (yyvsp[-1].node)->src.length + 2, "Only int and float can be incremented");
                }
                (yyval.node) = oprNode(OPR_INC, 1, (yyvsp[-1].node));
            }
#line 1951 "y.tab.c"
    break;

  case 62: /* assignExpr: arrayExpr DEC  */
#line 391 "parser.y"
                    {
                if((yyvsp[-1].node)->exprType.op != T_INT || (yyvsp[-1].node)->exprType.op != T_FLOAT){
                    compileError((yyvsp[-1].node)->src, (yyvsp[-1].node)->src.length+2, "Only int and float can be decremented");
                }
                (yyval.node) = oprNode(OPR_DEC, 1, (yyvsp[-1].node));
            }
#line 1962 "y.tab.c"
    break;

  case 63: /* $@4: %empty  */
#line 400 "parser.y"
                    { errorMessage((Coordinate){lineno, col-6, 0}, 6, 
                                    ANSI_COLOR_BOLD ANSI_COLOR_BLUE 
                                    "Warning: " ANSI_COLOR_RESET "Switch statement is not implemented");
                    }
#line 1971 "y.tab.c"
    break;

  case 64: /* $@5: %empty  */
#line 404 "parser.y"
                 {beginScope();}
#line 1977 "y.tab.c"
    break;

  case 65: /* switchStmt: SWITCH $@4 '(' expr ')' $@5 '{' switchBody '}'  */
#line 404 "parser.y"
                                                    { printf("switch end\n"); (yyval.node) = NULL; endScope();}
#line 1983 "y.tab.c"
    break;

  case 67: /* switchBody: %empty  */
#line 405 "parser.y"
                         {(yyval.node) = NULL;}
#line 1989 "y.tab.c"
    break;

  case 74: /* $@6: %empty  */
#line 422 "parser.y"
                    {templineno = lineno; tempcol = col- 4;}
#line 1995 "y.tab.c"
    break;

  case 75: /* caseLabel: caseType $@6 expr ':'  */
#line 422 "parser.y"
                                                                      {
                if((yyvsp[-1].node)->type!= NODE_LITERAL){
                    compileError((Coordinate){templineno, tempcol, 0}, (yyvsp[-1].node)->src.length + 5, "Case label must be a constant");
                }
                if((yyvsp[-1].node)->exprType.op != T_INT){
                    compileError((Coordinate){templineno, tempcol, 0}, (yyvsp[-1].node)->src.length+5, "Case label must be an integer");
                }
}
#line 2008 "y.tab.c"
    break;

  case 78: /* whileStmt: WHILE '(' expr ')' stmt  */
#line 433 "parser.y"
                                   {(yyval.node) = oprNode(OPR_WHILE, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2014 "y.tab.c"
    break;

  case 79: /* $@7: %empty  */
#line 435 "parser.y"
                        {beginScope();}
#line 2020 "y.tab.c"
    break;

  case 80: /* blockStmt: '{' $@7 stmtOrDecl '}'  */
#line 438 "parser.y"
                        {endScope(); (yyval.node) = (yyvsp[-1].node);}
#line 2026 "y.tab.c"
    break;

  case 81: /* ifStmt: IF '(' expr ')' stmt  */
#line 441 "parser.y"
                                       { (yyval.node) = oprNode(OPR_IF, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2032 "y.tab.c"
    break;

  case 82: /* ifStmt: IF '(' expr ')' stmt ELSE stmt  */
#line 442 "parser.y"
                                     { (yyval.node) = oprNode(OPR_IF, 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));}
#line 2038 "y.tab.c"
    break;

  case 83: /* expr: INTEGER  */
#line 444 "parser.y"
              {(yyval.node) = intNode((yyvsp[0].iValue));}
#line 2044 "y.tab.c"
    break;

  case 84: /* expr: CHARACTER  */
#line 445 "parser.y"
                {(yyval.node) = charNode((yyvsp[0].cValue)); }
#line 2050 "y.tab.c"
    break;

  case 85: /* expr: IDENTIFIER  */
#line 446 "parser.y"
                 { 
            Symbol* foundId = getSymbol((yyvsp[0].id).name, identifiers, (yyvsp[0].id).src, "Identifier '%s' not declared in this scope", (yyvsp[0].id).name);
            (yyval.node) = identifierNode(foundId);
        }
#line 2059 "y.tab.c"
    break;

  case 86: /* expr: FLOAT  */
#line 450 "parser.y"
            {(yyval.node) = floatNode((yyvsp[0].fValue));}
#line 2065 "y.tab.c"
    break;

  case 87: /* expr: STRING  */
#line 451 "parser.y"
             {(yyval.node) = strNode((yyvsp[0].sValue), strlen((yyvsp[0].sValue)));}
#line 2071 "y.tab.c"
    break;

  case 88: /* expr: callExpr  */
#line 452 "parser.y"
               {(yyval.node) = (yyvsp[0].node);}
#line 2077 "y.tab.c"
    break;

  case 89: /* expr: '-' expr  */
#line 453 "parser.y"
                            { (yyval.node) = oprNode('-', 1, (yyvsp[0].node)); typeCheckUnary((yyvsp[0].node)); (yyval.node)->exprType.op = (yyvsp[0].node)->exprType.op;}
#line 2083 "y.tab.c"
    break;

  case 90: /* expr: '!' expr  */
#line 454 "parser.y"
                            { (yyval.node) = oprNode('!', 1, (yyvsp[0].node)); typeCheckUnary((yyvsp[0].node)); (yyval.node)->exprType.op = (yyvsp[0].node)->exprType.op;}
#line 2089 "y.tab.c"
    break;

  case 91: /* expr: expr '+' expr  */
#line 455 "parser.y"
                    { (yyval.node) = oprNode('+', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2095 "y.tab.c"
    break;

  case 92: /* expr: expr '-' expr  */
#line 456 "parser.y"
                    { (yyval.node) = oprNode('-', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2101 "y.tab.c"
    break;

  case 93: /* expr: expr '*' expr  */
#line 457 "parser.y"
                    { (yyval.node) = oprNode('*', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2107 "y.tab.c"
    break;

  case 94: /* expr: expr '/' expr  */
#line 458 "parser.y"
                    { (yyval.node) = oprNode('/', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2113 "y.tab.c"
    break;

  case 95: /* expr: expr '<' expr  */
#line 459 "parser.y"
                    { (yyval.node) = oprNode('<', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2119 "y.tab.c"
    break;

  case 96: /* expr: expr '>' expr  */
#line 460 "parser.y"
                    { (yyval.node) = oprNode('>', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2125 "y.tab.c"
    break;

  case 97: /* expr: expr '%' expr  */
#line 461 "parser.y"
                    { (yyval.node) = oprNode('%', 2, (yyvsp[-2].node), (yyvsp[0].node));     (yyval.node)->exprType.op = T_INT; if((yyvsp[-2].node)->exprType.op != T_INT || (yyvsp[0].node)->exprType.op != T_INT){compileError((yyvsp[-2].node)->src, (yyvsp[-2].node)->src.length + (yyvsp[0].node)->src.length, "Modulo operator only works on integers");}}
#line 2131 "y.tab.c"
    break;

  case 98: /* expr: expr GE expr  */
#line 462 "parser.y"
                   { (yyval.node) = oprNode(OPR_GE, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2137 "y.tab.c"
    break;

  case 99: /* expr: expr LE expr  */
#line 463 "parser.y"
                   { (yyval.node) = oprNode(OPR_LE, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2143 "y.tab.c"
    break;

  case 100: /* expr: expr EQ expr  */
#line 464 "parser.y"
                   { (yyval.node) = oprNode(OPR_EQ, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2149 "y.tab.c"
    break;

  case 101: /* expr: expr NE expr  */
#line 465 "parser.y"
                   { (yyval.node) = oprNode(OPR_NE, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = typeWiden((yyvsp[-2].node)->exprType.op, (yyvsp[0].node)->exprType.op);}
#line 2155 "y.tab.c"
    break;

  case 102: /* expr: expr AND expr  */
#line 466 "parser.y"
                    { (yyval.node) = oprNode(OPR_AND, 2, (yyvsp[-2].node), (yyvsp[0].node)); (yyval.node)->exprType.op = T_INT;if((yyvsp[-2].node)->exprType.op != T_INT || (yyvsp[0].node)->exprType.op != T_INT){compileError((yyvsp[-2].node)->src, (yyvsp[-2].node)->src.length + (yyvsp[0].node)->src.length, "Boolean operators only work on integers");}}
#line 2161 "y.tab.c"
    break;

  case 103: /* expr: expr OR expr  */
#line 467 "parser.y"
                   { (yyval.node) = oprNode(OPR_OR, 2, (yyvsp[-2].node), (yyvsp[0].node));   (yyval.node)->exprType.op = T_INT;if((yyvsp[-2].node)->exprType.op != T_INT || (yyvsp[0].node)->exprType.op != T_INT){compileError((yyvsp[-2].node)->src, (yyvsp[-2].node)->src.length + (yyvsp[0].node)->src.length, "Boolean operators only work on integers");}}
#line 2167 "y.tab.c"
    break;

  case 104: /* expr: '(' expr ')'  */
#line 468 "parser.y"
                   { (yyval.node) = (yyvsp[-1].node);   (yyval.node)->exprType.op = (yyvsp[-1].node)->exprType.op;}
#line 2173 "y.tab.c"
    break;

  case 105: /* expr: arrayExpr  */
#line 469 "parser.y"
                {(yyval.node) = (yyvsp[0].node);       (yyval.node)->exprType.op = (yyvsp[0].node)->exprType.op;}
#line 2179 "y.tab.c"
    break;

  case 106: /* arrayExpr: expr '[' expr ']'  */
#line 474 "parser.y"
                                       {
        printf("Found array expression type %d\n", (yyvsp[-3].node)->exprType.ndim);
        if((yyvsp[-3].node)->exprType.op != T_ARRAY){
            compileError((yyvsp[-3].node)->src, (yyvsp[-3].node)->src.length + (yyvsp[-1].node)->src.length + 2, "Invalid indexing target. Only array types can be indexed.");
        }
        if((yyvsp[-1].node)->exprType.op != T_INT){
            compileError((yyvsp[-1].node)->src, (yyvsp[-1].node)->src.length, "Only int types can be used as indices.");
        }
        (yyval.node) = oprNode('[', 2, (yyvsp[-3].node), (yyvsp[-1].node));
        (yyval.node)->exprType.base = (yyvsp[-3].node)->exprType.base;
        (yyval.node)->exprType.op = (yyvsp[-3].node)->exprType.ndim == 1 ? (yyvsp[-3].node)->exprType.base : T_ARRAY;
        (yyval.node)->exprType.ndim = (yyvsp[-3].node)->exprType.ndim - 1;
        (yyval.node)->src.length = (yyvsp[-3].node)->src.length + (yyvsp[-1].node)->src.length + 2;
    }
#line 2198 "y.tab.c"
    break;

  case 107: /* callExpr: IDENTIFIER '(' arg_list ')'  */
#line 489 "parser.y"
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
                //ignore type checking for variadic functions
                if(!callee->type->variadicFunc){
                        printf("here\n");
                if(param){
                        while(param->as.opr.type==OPR_LIST && i >= 0){
                            printf("Comparing with original type= %d\n", callee->type->proto[i]->op);
                            if(!typeCheckAssign(callee->type->proto[i]->op, param->as.opr.operands[1]->exprType.op)){
                                compileError(param->as.opr.operands[1]->src, param->as.opr.operands[1]->src.length, "Type mismatch in function call to '%s'", (yyvsp[-3].id).name);
                            }
                            param = param->as.opr.operands[0];
                            i--;
                        }
                        if(i>=0){
                        printf("Comparing with original type %d \n", /* param->exprType.op, */ callee->type->proto[i]->op);
                        printf("inside %d\n", callee->type->proto[i] == NULL);}
                        if(i<0 && !callee->type->variadicFunc) {
                                compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Too many parameters in function call to '%s'", (yyvsp[-3].id).name);
                        }
                        if(!callee->type->variadicFunc && !typeCheckAssign(callee->type->proto[i]->op, param->exprType.op)){
                            compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Type mismatch in function call to '%s'", (yyvsp[-3].id).name);
                        }
                        i--;
                    }
                    if(i >= 0){
                        compileError((yyvsp[-3].id).src, strlen((yyvsp[-3].id).name), "Too few parameters in function call to '%s'; expected %d", (yyvsp[-3].id).name, callee->type->size);
                    }
                }
                (yyval.node) = oprNode(OPR_CALL, 2, identifierNode(callee), (yyvsp[-1].node));
                (yyval.node)->exprType.op = callee->type->type->op;
                printNode((yyval.node));
                printf("\n");
    }
#line 2249 "y.tab.c"
    break;

  case 108: /* arg_list: expr  */
#line 536 "parser.y"
               {(yyval.node) = (yyvsp[0].node);/* oprNode(OPR_LIST, 1,$1); */}
#line 2255 "y.tab.c"
    break;

  case 109: /* arg_list: arg_list ',' expr  */
#line 537 "parser.y"
                        {(yyval.node) = oprNode(OPR_LIST, 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2261 "y.tab.c"
    break;

  case 110: /* arg_list: %empty  */
#line 538 "parser.y"
      {(yyval.node) = NULL;}
#line 2267 "y.tab.c"
    break;

  case 111: /* returnStmt: RETURN  */
#line 541 "parser.y"
                   {
                Coordinate src;
                src.line = lineno;
                src.col = 0;
                compileError(src, 0, "Expected an expression to return");
                (yyval.node) = oprNode(OPR_RETURN, 0);
            }
#line 2279 "y.tab.c"
    break;

  case 112: /* returnStmt: RETURN expr  */
#line 548 "parser.y"
                      {
            printf("Checking return types %d %d\n", currentFunctionType->type->op, (yyvsp[0].node)->exprType.op);
            if(!typeCheckAssign(currentFunctionType->type->op, (yyvsp[0].node)->exprType.op)){
                compileError((yyvsp[0].node)->src, (yyvsp[0].node)->src.length, "Type mismatch in return statement");
            }
            (yyval.node) = oprNode(OPR_RETURN, 1, (yyvsp[0].node));
        }
#line 2291 "y.tab.c"
    break;

  case 113: /* continueStmt: CONTINUE  */
#line 557 "parser.y"
                       {(yyval.node) = oprNode(OPR_CONTINUE, 0);}
#line 2297 "y.tab.c"
    break;

  case 114: /* breakStmt: BREAK  */
#line 559 "parser.y"
                 {(yyval.node) = oprNode(OPR_BREAK, 0);}
#line 2303 "y.tab.c"
    break;


#line 2307 "y.tab.c"

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

#line 561 "parser.y"

void typeCheckArrayInitialiser(Type* elementType, Node* expr){
    Node* exprList = expr;
    TypeEnum baseType = getArrayBaseType(elementType);
    /* printf("Starting array %d\n", elementType->type->op, exprList); */
    printNode(exprList);
    printf("\n\n======\n");
    if(exprList == NULL) return;
    //if it is not a list, this is the last element
    if(exprList->type != NODE_OPR && exprList->as.opr.type != OPR_LIST){
        Node* insideElement = exprList;//->as.opr.operands[0];
        printf("Checking 1) %d %d\n", elementType->type->op, insideElement->exprType.op);
        if(!typeCheckAssign(elementType->type->op, insideElement->exprType.op) && !typeCheckAssign(baseType, insideElement->exprType.op)){
            compileError( insideElement->src,  insideElement->src.length, "Invalid array element type %d %d", elementType->type->op, insideElement->exprType.op);
        }
        if(insideElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, insideElement);
        }
    } else {
        //this is a list, so check the second operand
        //if it is a list, it will be checked recursively
        /* printf("Checking %d %d\n", elementType->type->op, exprList->as.opr.operands[1]->exprType.op); */
        Node* localElement = exprList->as.opr.operands[1];
        if(localElement->as.opr.type == OPR_LIST){
            typeCheckArrayInitialiser(elementType->type, exprList->as.opr.operands[1]);
        }
        TypeEnum baseType = getArrayBaseType(elementType);
        printf("Checking 2) %d %d\n", baseType, localElement->exprType.op);
        if(localElement->exprType.op != baseType && localElement->exprType.op != elementType->type->op){
            compileError(localElement->src, localElement->src.length, "Invalid array element type 2");
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
    if(varType == T_FUNCTION && exprType != T_FUNCTION){
        return 0;
    }
    if(exprType == T_FLOAT && varType != T_FLOAT){
        return 0;
    }

    return varType == exprType;
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
