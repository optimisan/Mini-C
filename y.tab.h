/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
    INTEGER = 268,                 /* INTEGER  */
    FLOAT = 269,                   /* FLOAT  */
    CHARACTER = 270,               /* CHARACTER  */
    STRING = 271,                  /* STRING  */
    ASSIGN = 272,                  /* ASSIGN  */
    PLUS_ASSIGN = 273,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 274,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 275,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 276,            /* SLASH_ASSIGN  */
    MOD_ASSIGN = 277,              /* MOD_ASSIGN  */
    PLUS = 278,                    /* PLUS  */
    MINUS = 279,                   /* MINUS  */
    STAR = 280,                    /* STAR  */
    SLASH = 281,                   /* SLASH  */
    MOD = 282,                     /* MOD  */
    INC = 283,                     /* INC  */
    DEC = 284,                     /* DEC  */
    EQ = 285,                      /* EQ  */
    LT = 286,                      /* LT  */
    GT = 287,                      /* GT  */
    LE = 288,                      /* LE  */
    GE = 289,                      /* GE  */
    QUESTION_MARK = 290,           /* QUESTION_MARK  */
    NE = 291,                      /* NE  */
    NOT = 292,                     /* NOT  */
    AND = 293,                     /* AND  */
    OR = 294,                      /* OR  */
    COMMA = 295,                   /* COMMA  */
    SEMICOLON = 296,               /* SEMICOLON  */
    COLON = 297,                   /* COLON  */
    SINGLE_START = 298,            /* SINGLE_START  */
    MULTI_START = 299,             /* MULTI_START  */
    MULTI_END = 300,               /* MULTI_END  */
    LEFT_PAREN = 301,              /* LEFT_PAREN  */
    RIGHT_PAREN = 302,             /* RIGHT_PAREN  */
    LEFT_BRACE = 303,              /* LEFT_BRACE  */
    RIGHT_BRACE = 304,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 305,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 306,           /* RIGHT_BRACKET  */
    IDENTIFIER = 307,              /* IDENTIFIER  */
    ERROR = 308,                   /* ERROR  */
    EOF_TOKEN = 309                /* EOF_TOKEN  */
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
#define INTEGER 268
#define FLOAT 269
#define CHARACTER 270
#define STRING 271
#define ASSIGN 272
#define PLUS_ASSIGN 273
#define MINUS_ASSIGN 274
#define STAR_ASSIGN 275
#define SLASH_ASSIGN 276
#define MOD_ASSIGN 277
#define PLUS 278
#define MINUS 279
#define STAR 280
#define SLASH 281
#define MOD 282
#define INC 283
#define DEC 284
#define EQ 285
#define LT 286
#define GT 287
#define LE 288
#define GE 289
#define QUESTION_MARK 290
#define NE 291
#define NOT 292
#define AND 293
#define OR 294
#define COMMA 295
#define SEMICOLON 296
#define COLON 297
#define SINGLE_START 298
#define MULTI_START 299
#define MULTI_END 300
#define LEFT_PAREN 301
#define RIGHT_PAREN 302
#define LEFT_BRACE 303
#define RIGHT_BRACE 304
#define LEFT_BRACKET 305
#define RIGHT_BRACKET 306
#define IDENTIFIER 307
#define ERROR 308
#define EOF_TOKEN 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
