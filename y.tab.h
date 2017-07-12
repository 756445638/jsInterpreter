/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_LITERAL = 258,
    DOUBLE_LITERAL = 259,
    STRING_LITERAL = 260,
    IDENTIFIER = 261,
    FUNCTION = 262,
    IF = 263,
    ELSE = 264,
    ELSIF = 265,
    WHILE = 266,
    FOR = 267,
    RETURN_T = 268,
    BREAK = 269,
    CONTINUE = 270,
    NULL_T = 271,
    CRLF = 272,
    LP = 273,
    RP = 274,
    LC = 275,
    RC = 276,
    LB = 277,
    RB = 278,
    SEMICOLON = 279,
    COMMA = 280,
    ASSIGN = 281,
    LOGICAL_AND = 282,
    LOGICAL_OR = 283,
    EQ = 284,
    NE = 285,
    GT = 286,
    GE = 287,
    LT = 288,
    LE = 289,
    ADD = 290,
    SUB = 291,
    MUL = 292,
    DIV = 293,
    MOD = 294,
    TRUE_T = 295,
    FALSE_T = 296,
    DOT = 297,
    VAR = 298,
    INCREMENT = 299,
    DECREMENT = 300
  };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define DOUBLE_LITERAL 259
#define STRING_LITERAL 260
#define IDENTIFIER 261
#define FUNCTION 262
#define IF 263
#define ELSE 264
#define ELSIF 265
#define WHILE 266
#define FOR 267
#define RETURN_T 268
#define BREAK 269
#define CONTINUE 270
#define NULL_T 271
#define CRLF 272
#define LP 273
#define RP 274
#define LC 275
#define RC 276
#define LB 277
#define RB 278
#define SEMICOLON 279
#define COMMA 280
#define ASSIGN 281
#define LOGICAL_AND 282
#define LOGICAL_OR 283
#define EQ 284
#define NE 285
#define GT 286
#define GE 287
#define LT 288
#define LE 289
#define ADD 290
#define SUB 291
#define MUL 292
#define DIV 293
#define MOD 294
#define TRUE_T 295
#define FALSE_T 296
#define DOT 297
#define VAR 298
#define INCREMENT 299
#define DECREMENT 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 6 "js.y" /* yacc.c:1909  */

    char                *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    ExpressionList      *expression_list;
    Statement           *statement;
    StatementList       *statement_list;
    Block               *block;
    Elsif               *elsif;

#line 156 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
