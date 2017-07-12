/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "js.y" /* yacc.c:339  */

#include <stdio.h>
#include "crowbar.h"
#define YYDEBUG 1

#line 72 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
    GLOBAL_T = 297,
    DOT = 298,
    VAR = 299,
    INCREMENT = 300,
    DECREMENT = 301
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
#define GLOBAL_T 297
#define DOT 298
#define VAR 299
#define INCREMENT 300
#define DECREMENT 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 6 "js.y" /* yacc.c:355  */

    char                *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    ExpressionList      *expression_list;
    Statement           *statement;
    StatementList       *statement_list;
    Block               *block;
    Elsif               *elsif;
    IdentifierList      *identifier_list;

#line 217 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 234 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   435

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    43,    43,    44,    47,    48,    57,    61,    65,    69,
      76,    80,    87,    91,    98,   102,   106,   107,   108,   109,
     110,   111,   112,   116,   123,   127,   131,   135,   141,   142,
     147,   152,   159,   163,   170,   177,   184,   190,   197,   201,
     207,   209,   214,   217,   221,   228,   229,   233,   237,   243,
     244,   251,   252,   258,   259,   263,   269,   270,   274,   278,
     282,   289,   290,   294,   299,   300,   304,   308,   315,   316,
     322,   323,   327,   331,   335,   339,   343,   349,   353,   360,
     364,   368,   372,   376,   377,   378,   379,   383,   387,   391,
     394,   398
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "DOUBLE_LITERAL",
  "STRING_LITERAL", "IDENTIFIER", "FUNCTION", "IF", "ELSE", "ELSIF",
  "WHILE", "FOR", "RETURN_T", "BREAK", "CONTINUE", "NULL_T", "CRLF", "LP",
  "RP", "LC", "RC", "LB", "RB", "SEMICOLON", "COMMA", "ASSIGN",
  "LOGICAL_AND", "LOGICAL_OR", "EQ", "NE", "GT", "GE", "LT", "LE", "ADD",
  "SUB", "MUL", "DIV", "MOD", "TRUE_T", "FALSE_T", "GLOBAL_T", "DOT",
  "VAR", "INCREMENT", "DECREMENT", "$accept", "translation_unit",
  "definition_or_statement", "function_definition", "parameter_list",
  "statement_list", "statement", "break_statement", "if_statement",
  "elsif_list", "elsif", "global_statement", "identifier_list",
  "while_statement", "for_statement", "return_statement",
  "continue_statement", "block", "expression_opt", "expression_list",
  "expression", "logical_or_expression", "logical_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "argument_list", "primary_expression", "array_literal", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF -109

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-109)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     191,  -109,  -109,  -109,   -17,    18,    15,    25,    33,   341,
      42,    53,  -109,   341,   341,   341,   368,  -109,  -109,    34,
     394,   149,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    60,    81,    86,    75,    89,    72,    -8,  -109,
      22,  -109,  -109,   260,   110,     9,   341,   341,   341,   115,
    -109,  -109,  -109,    61,   116,  -109,    71,  -109,    57,  -109,
      90,    52,  -109,  -109,  -109,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   341,   341,
     134,  -109,  -109,  -109,  -109,    56,    16,  -109,   122,    66,
     124,   125,   121,  -109,  -109,   287,  -109,   341,  -109,   140,
    -109,   341,    86,    75,    89,    89,    72,    72,    72,    72,
      -8,    -8,  -109,  -109,  -109,   127,  -109,    24,  -109,   341,
     122,    74,     5,  -109,   122,   141,   122,   122,   341,  -109,
    -109,  -109,  -109,  -109,   314,   151,  -109,  -109,   122,  -109,
     233,  -109,  -109,  -109,   108,  -109,   135,  -109,    87,  -109,
    -109,  -109,  -109,   122,   148,   117,  -109,   341,  -109,  -109,
     341,   122,  -109,   153,   154,  -109,   122,   122,  -109,  -109
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    83,    84,    85,    82,     0,     0,     0,     0,    40,
       0,     0,    88,     0,    42,    42,     0,    86,    87,     0,
       0,     0,     2,     4,     5,    22,    16,    17,    18,    19,
      20,    21,    15,    45,    49,    51,    53,    56,    61,    64,
      68,    70,    89,     0,     0,     0,     0,     0,    40,     0,
      41,    23,    37,     0,     0,    43,     0,    69,    68,    32,
       0,     0,     1,     3,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,    75,    80,    77,     0,     0,    11,     0,     0,
       0,     0,     0,    36,    81,     0,    90,     0,    31,     0,
      48,     0,    50,    52,    54,    55,    57,    58,    59,    60,
      62,    63,    65,    66,    67,     0,    46,     0,    79,     0,
       0,     0,     0,     8,     0,     0,     0,     0,    40,    91,
      44,    33,    47,    71,     0,     0,    78,     7,     0,    39,
       0,    12,     9,    10,    24,    34,     0,    73,     0,    76,
       6,    38,    13,     0,     0,    26,    28,    40,    72,    25,
       0,     0,    29,     0,     0,    27,     0,     0,    35,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,   147,    35,    88,  -109,  -108,  -109,  -109,  -109,
      20,  -109,  -109,  -109,  -109,  -109,  -109,   -37,   -46,   161,
      -9,  -109,   112,   113,    68,    62,    64,    -4,   -13,    44,
    -109,  -109
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    21,    22,    23,    89,   140,    24,    25,    26,   155,
     156,    27,    60,    28,    29,    30,    31,   123,    49,    54,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    85,
      41,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    43,    92,    58,    53,    55,    55,    61,     1,     2,
       3,     4,    57,     6,   141,    87,     7,     8,     9,    10,
      11,    12,    87,    13,    44,    14,   139,    15,    88,    75,
      76,    77,   152,    46,    84,   120,    45,    90,    91,    50,
      59,    16,   134,    47,    78,    17,    18,    19,    79,    20,
     135,    48,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    80,    51,    81,    82,   115,
     116,   112,   113,   114,    78,   118,   100,    52,   101,    78,
      94,   119,   146,   137,    64,   124,   130,   142,   130,   144,
     145,   125,   132,   138,    96,    80,    97,    81,    82,   125,
      80,   150,    81,    82,    67,    68,   158,    73,    74,    65,
     136,   163,   119,    66,    98,    99,   159,   153,   154,    50,
      69,    70,    71,    72,   165,    84,   161,   154,    86,   168,
     169,   106,   107,   108,   109,   104,   105,   110,   111,    93,
     117,    95,   122,   126,   127,   128,   131,   143,    50,    62,
     133,   164,     1,     2,     3,     4,     5,     6,     5,   157,
       7,     8,     9,    10,    11,    12,   160,    13,    63,    14,
     149,    15,   166,   167,   121,   162,    56,   102,   148,   103,
       0,     0,     0,     0,     0,    16,     0,     0,     0,    17,
      18,    19,     0,    20,     1,     2,     3,     4,     5,     6,
       0,     0,     7,     8,     9,    10,    11,    12,     0,    13,
       0,    14,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,     0,     0,
       0,    17,    18,    19,     0,    20,     1,     2,     3,     4,
       0,     6,     0,     0,     7,     8,     9,    10,    11,    12,
       0,    13,     0,    14,   151,    15,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     0,     0,    16,
       0,     0,     0,    17,    18,    19,    12,    20,    13,    83,
      14,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     3,     4,     0,     0,    16,     0,     0,     0,
      17,    18,     0,    12,    20,    13,     0,    14,   129,    15,
       0,     0,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     0,     0,    16,     0,     0,     0,    17,    18,     0,
      12,    20,    13,   147,    14,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     3,     4,     0,     0,
      16,     0,     0,     0,    17,    18,     0,    12,    20,    13,
       0,    14,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     0,     0,    16,     0,     0,
       0,    17,    18,     0,    12,    20,    13,     0,    14,     0,
      15,     0,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     0,     0,     0,    16,     0,     0,     0,    17,    18,
      12,     0,    13,     0,    14,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    18
};

static const yytype_int16 yycheck[] =
{
       9,    18,    48,    16,    13,    14,    15,    20,     3,     4,
       5,     6,    16,     8,   122,     6,    11,    12,    13,    14,
      15,    16,     6,    18,     6,    20,    21,    22,    19,    37,
      38,    39,   140,    18,    43,    19,    18,    46,    47,    48,
       6,    36,    18,    18,    22,    40,    41,    42,    26,    44,
      26,    18,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    43,    24,    45,    46,    78,
      79,    75,    76,    77,    22,    19,    24,    24,    26,    22,
      19,    25,   128,   120,    24,    19,    95,   124,    97,   126,
     127,    25,   101,    19,    23,    43,    25,    45,    46,    25,
      43,   138,    45,    46,    29,    30,    19,    35,    36,    28,
     119,   157,    25,    27,    24,    25,   153,     9,    10,   128,
      31,    32,    33,    34,   161,   134,     9,    10,    18,   166,
     167,    69,    70,    71,    72,    67,    68,    73,    74,    24,
       6,    25,    20,    19,    19,    24,     6,     6,   157,     0,
      23,   160,     3,     4,     5,     6,     7,     8,     7,    24,
      11,    12,    13,    14,    15,    16,    18,    18,    21,    20,
     135,    22,    19,    19,    86,   155,    15,    65,   134,    66,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    12,    13,    14,    15,    16,    -1,    18,
      -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,     3,     4,     5,     6,
      -1,     8,    -1,    -1,    11,    12,    13,    14,    15,    16,
      -1,    18,    -1,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,    -1,    36,
      -1,    -1,    -1,    40,    41,    42,    16,    44,    18,    19,
      20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,    -1,    36,    -1,    -1,    -1,
      40,    41,    -1,    16,    44,    18,    -1,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,    -1,    36,    -1,    -1,    -1,    40,    41,    -1,
      16,    44,    18,    19,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,    -1,
      36,    -1,    -1,    -1,    40,    41,    -1,    16,    44,    18,
      -1,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,    -1,    36,    -1,    -1,
      -1,    40,    41,    -1,    16,    44,    18,    -1,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,    41,
      16,    -1,    18,    -1,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    11,    12,    13,
      14,    15,    16,    18,    20,    22,    36,    40,    41,    42,
      44,    48,    49,    50,    53,    54,    55,    58,    60,    61,
      62,    63,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    77,    78,    18,     6,    18,    18,    18,    18,    65,
      67,    24,    24,    67,    66,    67,    66,    74,    75,     6,
      59,    75,     0,    49,    24,    28,    27,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    22,    26,
      43,    45,    46,    19,    67,    76,    18,     6,    19,    51,
      67,    67,    65,    24,    19,    25,    23,    25,    24,    25,
      24,    26,    69,    70,    71,    71,    72,    72,    72,    72,
      73,    73,    74,    74,    74,    67,    67,     6,    19,    25,
      19,    51,    20,    64,    19,    25,    19,    19,    24,    21,
      67,     6,    67,    23,    18,    26,    67,    64,    19,    21,
      52,    53,    64,     6,    64,    64,    65,    19,    76,    50,
      64,    21,    53,     9,    10,    56,    57,    24,    19,    64,
      18,     9,    57,    65,    67,    64,    19,    19,    64,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    55,    55,    55,    55,    56,    56,
      57,    58,    59,    59,    60,    61,    62,    63,    64,    64,
      65,    65,    66,    66,    66,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    71,    71,    71,    71,
      71,    72,    72,    72,    73,    73,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     6,     5,     4,     5,
       3,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     7,     6,     8,     1,     2,
       5,     3,     1,     3,     5,     9,     3,     2,     3,     2,
       0,     1,     0,     1,     3,     1,     3,     4,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       1,     4,     6,     5,     2,     2,     5,     1,     3,     4,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 5:
#line 49 "js.y" /* yacc.c:1646  */
    {
            CRB_Interpreter *inter = crb_get_current_interpreter();

            inter->statement_list
                = crb_chain_statement_list(inter->statement_list, (yyvsp[0].statement));
        }
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 58 "js.y" /* yacc.c:1646  */
    {
            crb_function_define((yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].block));
        }
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 62 "js.y" /* yacc.c:1646  */
    {
            crb_function_define((yyvsp[-3].identifier), NULL, (yyvsp[0].block));
        }
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 66 "js.y" /* yacc.c:1646  */
    {
            printf("no name function");
        }
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 70 "js.y" /* yacc.c:1646  */
    {
            printf("no name function");
        }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 77 "js.y" /* yacc.c:1646  */
    {
        (yyval.parameter_list) = crb_chain_parameter((yyvsp[-2].parameter_list), (yyvsp[0].identifier));
    }
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 81 "js.y" /* yacc.c:1646  */
    {
         (yyval.parameter_list) = crb_create_parameter((yyvsp[0].identifier));
    }
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 88 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement_list) = crb_create_statement_list((yyvsp[0].statement));
    }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 92 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement_list) = crb_chain_statement_list((yyvsp[-1].statement_list), (yyvsp[0].statement));
    }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 99 "js.y" /* yacc.c:1646  */
    {
         (yyval.statement) = crb_create_expression_statement((yyvsp[-1].expression));
    }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 103 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_expression_statement((yyvsp[0].expression));
    }
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 117 "js.y" /* yacc.c:1646  */
    {
            (yyval.statement) = crb_create_break_statement();
    }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "js.y" /* yacc.c:1646  */
    {
         (yyval.statement) = crb_create_if_statement((yyvsp[-2].expression), (yyvsp[0].block), NULL, NULL);
    }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 128 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_if_statement((yyvsp[-4].expression), (yyvsp[-2].block), NULL, (yyvsp[0].block));
    }
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 132 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_if_statement((yyvsp[-3].expression), (yyvsp[-1].block), (yyvsp[0].elsif), NULL);
    }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 136 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_if_statement((yyvsp[-5].expression), (yyvsp[-3].block), (yyvsp[-2].elsif), (yyvsp[0].block));
    }
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 143 "js.y" /* yacc.c:1646  */
    {
         (yyval.elsif) = crb_chain_elsif_list((yyvsp[-1].elsif), (yyvsp[0].elsif));
    }
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 147 "js.y" /* yacc.c:1646  */
    {
         (yyval.elsif) = crb_create_elsif((yyvsp[-2].expression), (yyvsp[0].block));
    }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 153 "js.y" /* yacc.c:1646  */
    {
         (yyval.statement) = crb_create_global_statement((yyvsp[-1].identifier_list));
    }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 160 "js.y" /* yacc.c:1646  */
    {
        (yyval.identifier_list) = crb_create_global_identifier((yyvsp[0].identifier));
    }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 164 "js.y" /* yacc.c:1646  */
    {
         (yyval.identifier_list) = crb_chain_identifier((yyvsp[-2].identifier_list), (yyvsp[0].identifier));
    }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 171 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_while_statement((yyvsp[-2].expression), (yyvsp[0].block));
    }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 178 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_for_statement((yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].block));
    }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 185 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_return_statement((yyvsp[-1].expression));
    }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 191 "js.y" /* yacc.c:1646  */
    {
        (yyval.statement) = crb_create_continue_statement();
    }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 198 "js.y" /* yacc.c:1646  */
    {
        (yyval.block) = crb_create_block((yyvsp[-1].statement_list));
    }
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 202 "js.y" /* yacc.c:1646  */
    {
        (yyval.block) = crb_create_block(NULL);
    }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 214 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression_list) = NULL;
        }
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 218 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression_list) = crb_create_expression_list((yyvsp[0].expression));
        }
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 222 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression_list) = crb_chain_expression_list((yyvsp[-2].expression_list), (yyvsp[0].expression));
        }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 230 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_assign_expression((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 234 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_assign_expression((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 238 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_assign_expression((yyvsp[-1].expression), NULL);
    }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 245 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(LOGICAL_OR_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 253 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(LOGICAL_AND_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 260 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(EQ_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 264 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(NE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 271 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(GT_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 275 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(GE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 279 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(LT_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 283 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(LE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 291 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(ADD_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 294 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(SUB_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 301 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(MUL_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 305 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(DIV_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 309 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_binary_expression(MOD_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 317 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_minus_expression((yyvsp[0].expression));
    }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 324 "js.y" /* yacc.c:1646  */
    {
         (yyval.expression) = crb_create_index_expression((yyvsp[-3].expression), (yyvsp[-1].expression));
    }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 328 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_method_call_expression((yyvsp[-5].expression), (yyvsp[-3].identifier), (yyvsp[-1].argument_list));
    }
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 332 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_method_call_expression((yyvsp[-4].expression), (yyvsp[-2].identifier), NULL);
    }
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 336 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_incdec_expression((yyvsp[-1].expression), INCREMENT_EXPRESSION);
    }
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 340 "js.y" /* yacc.c:1646  */
    {
        (yyval.expression) = crb_create_incdec_expression((yyvsp[-1].expression), DECREMENT_EXPRESSION);
    }
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 344 "js.y" /* yacc.c:1646  */
    {
        printf("create method for a object");
    }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 350 "js.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = crb_create_argument_list((yyvsp[0].expression));
        }
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 354 "js.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = crb_chain_argument_list((yyvsp[-2].argument_list), (yyvsp[0].expression));
        }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 361 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_function_call_expression((yyvsp[-3].identifier), (yyvsp[-1].argument_list));
        }
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 365 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_function_call_expression((yyvsp[-2].identifier), NULL);
        }
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 369 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = (yyvsp[-1].expression);
        }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 373 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_identifier_expression((yyvsp[0].identifier));
        }
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 380 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_boolean_expression(CRB_TRUE);
        }
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 384 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_boolean_expression(CRB_FALSE);
        }
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 388 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_null_expression();
        }
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 395 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_array_expression((yyvsp[-1].expression_list));
        }
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 399 "js.y" /* yacc.c:1646  */
    {
            (yyval.expression) = crb_create_array_expression((yyvsp[-2].expression_list));
        }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2002 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 403 "js.y" /* yacc.c:1906  */

