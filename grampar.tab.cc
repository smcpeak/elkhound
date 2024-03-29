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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "grampar.y"


#include "grampar.h"        // yylex, etc.
#include "gramast.ast.gen.h"// grammar syntax AST definition

#include "gramlex.yy.h"     // Needed by gramlex.h.
#include "gramlex.h"        // GrammarLexer

#include "owner.h"          // Owner

#include <stdlib.h>         // malloc, free
#include "sm-iostream.h"    // cout

// enable debugging the parser
#ifndef NDEBUG
  #define YYDEBUG 1
#endif

// name of extra parameter to yylex
#define YYLEX_PARAM parseParam

// make it call my yylex
#define yylex(lv, param) grampar_yylex(lv, param)

// Bison calls yyerror(param, msg) on error, but (for historical
// reasons) my error function accepts them in the opposite order.
#define yyerror(param, msg) grampar_yyerror(msg, param)

// rename the externally-visible parsing routine to make it
// specific to this instance, so multiple bison-generated
// parsers can coexist
#define yyparse grampar_yyparse


// grab the parameter
#define PARAM ((ParseParams*)parseParam)

// return a locstring for 'str' with no location information
#define noloc(str)                                                    \
  new LocString(SL_UNKNOWN,      /* unknown location */               \
                PARAM->lexer.strtable.add(str))

// locstring for NULL, with no location
#define nolocNULL()                                                   \
  new LocString(SL_UNKNOWN, NULL)

// return a locstring with same location info as something else
// (passed as a pointer to a SourceLocation)
#define sameloc(otherLoc, str)                                        \
  new LocString(otherLoc->loc, PARAM->lexer.strtable.add(str))

// interpret the word into an associativity kind specification
AssocKind whichKind(LocString * /*owner*/ kind);


#line 127 "grampar.tab.c"

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

#include "grampar.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_INTEGER = 3,                /* TOK_INTEGER  */
  YYSYMBOL_TOK_NAME = 4,                   /* TOK_NAME  */
  YYSYMBOL_TOK_STRING = 5,                 /* TOK_STRING  */
  YYSYMBOL_TOK_LIT_CODE = 6,               /* TOK_LIT_CODE  */
  YYSYMBOL_TOK_LBRACE = 7,                 /* "{"  */
  YYSYMBOL_TOK_RBRACE = 8,                 /* "}"  */
  YYSYMBOL_TOK_COLON = 9,                  /* ":"  */
  YYSYMBOL_TOK_SEMICOLON = 10,             /* ";"  */
  YYSYMBOL_TOK_ARROW = 11,                 /* "->"  */
  YYSYMBOL_TOK_LPAREN = 12,                /* "("  */
  YYSYMBOL_TOK_RPAREN = 13,                /* ")"  */
  YYSYMBOL_TOK_COMMA = 14,                 /* ","  */
  YYSYMBOL_TOK_TERMINALS = 15,             /* "terminals"  */
  YYSYMBOL_TOK_TOKEN = 16,                 /* "token"  */
  YYSYMBOL_TOK_NONTERM = 17,               /* "nonterm"  */
  YYSYMBOL_TOK_FUN = 18,                   /* "fun"  */
  YYSYMBOL_TOK_VERBATIM = 19,              /* "verbatim"  */
  YYSYMBOL_TOK_IMPL_VERBATIM = 20,         /* "impl_verbatim"  */
  YYSYMBOL_TOK_PRECEDENCE = 21,            /* "precedence"  */
  YYSYMBOL_TOK_PRECEDENCE_PREFER_SHIFT = 22, /* "precedence_prefer_shift"  */
  YYSYMBOL_TOK_OPTION = 23,                /* "option"  */
  YYSYMBOL_TOK_EXPECT = 24,                /* "expect"  */
  YYSYMBOL_TOK_CONTEXT_CLASS = 25,         /* "context_class"  */
  YYSYMBOL_TOK_SUBSETS = 26,               /* "subsets"  */
  YYSYMBOL_TOK_DELETE = 27,                /* "delete"  */
  YYSYMBOL_TOK_REPLACE = 28,               /* "replace"  */
  YYSYMBOL_TOK_FORBID_NEXT = 29,           /* "forbid_next"  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_StartSymbol = 31,               /* StartSymbol  */
  YYSYMBOL_TopFormList = 32,               /* TopFormList  */
  YYSYMBOL_TopForm = 33,                   /* TopForm  */
  YYSYMBOL_ContextClass = 34,              /* ContextClass  */
  YYSYMBOL_Verbatim = 35,                  /* Verbatim  */
  YYSYMBOL_Option = 36,                    /* Option  */
  YYSYMBOL_Terminals = 37,                 /* Terminals  */
  YYSYMBOL_TermDecls = 38,                 /* TermDecls  */
  YYSYMBOL_TerminalDecl = 39,              /* TerminalDecl  */
  YYSYMBOL_Type = 40,                      /* Type  */
  YYSYMBOL_TermTypes = 41,                 /* TermTypes  */
  YYSYMBOL_TermType = 42,                  /* TermType  */
  YYSYMBOL_Precedence = 43,                /* Precedence  */
  YYSYMBOL_PrecSpecs = 44,                 /* PrecSpecs  */
  YYSYMBOL_NameOrStringList = 45,          /* NameOrStringList  */
  YYSYMBOL_NameOrString = 46,              /* NameOrString  */
  YYSYMBOL_SpecFuncs = 47,                 /* SpecFuncs  */
  YYSYMBOL_SpecFunc = 48,                  /* SpecFunc  */
  YYSYMBOL_FormalsOpt = 49,                /* FormalsOpt  */
  YYSYMBOL_Formals = 50,                   /* Formals  */
  YYSYMBOL_NTForbidNexts = 51,             /* NTForbidNexts  */
  YYSYMBOL_NTForbidNext = 52,              /* NTForbidNext  */
  YYSYMBOL_Nonterminal = 53,               /* Nonterminal  */
  YYSYMBOL_Productions = 54,               /* Productions  */
  YYSYMBOL_Production = 55,                /* Production  */
  YYSYMBOL_Action = 56,                    /* Action  */
  YYSYMBOL_RHS = 57,                       /* RHS  */
  YYSYMBOL_RHSElt = 58,                    /* RHSElt  */
  YYSYMBOL_Subsets = 59                    /* Subsets  */
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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   95

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   174,   174,   179,   180,   184,   185,   186,   187,   188,
     192,   197,   198,   203,   204,   215,   220,   221,   229,   231,
     236,   237,   241,   242,   246,   248,   253,   254,   259,   260,
     265,   266,   270,   271,   277,   278,   282,   287,   288,   292,
     293,   299,   300,   305,   316,   319,   324,   325,   329,   330,
     331,   335,   336,   340,   341,   350,   351,   352,   353,   354,
     355,   356,   360,   361
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_INTEGER",
  "TOK_NAME", "TOK_STRING", "TOK_LIT_CODE", "\"{\"", "\"}\"", "\":\"",
  "\";\"", "\"->\"", "\"(\"", "\")\"", "\",\"", "\"terminals\"",
  "\"token\"", "\"nonterm\"", "\"fun\"", "\"verbatim\"",
  "\"impl_verbatim\"", "\"precedence\"", "\"precedence_prefer_shift\"",
  "\"option\"", "\"expect\"", "\"context_class\"", "\"subsets\"",
  "\"delete\"", "\"replace\"", "\"forbid_next\"", "$accept", "StartSymbol",
  "TopFormList", "TopForm", "ContextClass", "Verbatim", "Option",
  "Terminals", "TermDecls", "TerminalDecl", "Type", "TermTypes",
  "TermType", "Precedence", "PrecSpecs", "NameOrStringList",
  "NameOrString", "SpecFuncs", "SpecFunc", "FormalsOpt", "Formals",
  "NTForbidNexts", "NTForbidNext", "Nonterminal", "Productions",
  "Production", "Action", "RHS", "RHSElt", "Subsets", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -75,    25,    23,   -75,     5,     8,    21,    38,    54,    53,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    56,   -75,
     -75,    14,    51,    59,     4,    55,   -75,   -75,    57,   -75,
      -8,   -75,   -75,    52,    58,   -75,   -75,    60,     8,    61,
     -75,    62,    49,    -3,   -75,   -75,    18,    67,   -75,   -75,
      68,   -75,    44,    65,   -75,   -75,   -75,    63,   -75,    64,
     -75,   -75,     0,    -3,    69,   -75,    40,    37,    66,    70,
     -75,     9,    47,    50,    50,   -75,   -75,   -75,   -75,   -75,
      74,   -75,    76,    50,    76,   -75,    73,   -75,   -75,   -75,
     -75,    71,    72,    -2,   -75,   -75,    75,    77,    79,    39,
     -75,   -75,   -75,   -75,    29,    80,    83,    84,   -75,   -75,
     -75,   -75,   -75,   -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,    21,     0,     0,     0,     0,
       4,     5,     6,     7,     8,     9,    16,    20,     0,    11,
      12,     0,     0,    22,     0,     0,    13,    10,     0,    17,
      26,    34,    53,     0,     0,    44,    14,     0,    21,     0,
      23,     0,    41,     0,    53,    53,     0,     0,    28,    15,
       0,    35,    46,    55,    57,    51,    52,     0,    60,     0,
      48,    54,     0,     0,     0,    18,     0,     0,     0,     0,
      42,    62,     0,     0,     0,    50,    49,    19,    34,    24,
       0,    27,    37,     0,     0,    47,     0,    56,    58,    32,
      33,     0,     0,     0,    30,    39,     0,    38,     0,     0,
      45,    59,    61,    25,     0,     0,     0,     0,    63,    29,
      31,    36,    40,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
      45,   -75,   -75,   -75,   -75,   -75,   -74,    11,   -75,   -75,
       6,   -75,   -75,   -75,   -75,    22,    32,    12,   -75,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,    11,    12,    13,    14,    23,    29,
      18,    30,    40,    41,    67,   104,    91,    42,    51,    96,
      97,    52,    70,    15,    71,    35,    60,    43,    61,    86
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      92,    53,    54,    55,    53,    54,   103,    56,    38,    98,
      75,    31,    16,    39,    17,    32,    50,    25,    57,    58,
      32,    57,    58,    64,    26,     3,    59,    19,    65,    59,
     110,    33,    34,    89,    90,    84,    33,    34,     4,   109,
       5,    80,     6,     7,    20,    81,     8,    78,     9,   108,
      79,    87,    88,   106,    89,    90,    62,    63,    21,    22,
      24,    27,    28,    44,    46,    36,    37,    50,    48,    45,
      49,    66,    68,    69,    72,    73,    74,    94,    82,    77,
      95,   100,    83,    47,   101,   102,   111,   112,   105,    93,
      99,   106,   107,    85,   113,    76
};

static const yytype_int8 yycheck[] =
{
      74,     4,     5,     6,     4,     5,     8,    10,    16,    83,
      10,     7,     7,    21,     6,    11,    18,     3,    21,    22,
      11,    21,    22,     5,    10,     0,    29,     6,    10,    29,
     104,    27,    28,     4,     5,    26,    27,    28,    15,    10,
      17,     4,    19,    20,     6,     8,    23,     7,    25,    10,
      10,     4,     5,    14,     4,     5,    44,    45,     4,     6,
       4,    10,     3,    11,     4,    10,     9,    18,     7,    11,
       8,     4,     4,    29,     9,    12,    12,     3,    12,    10,
       4,     8,    12,    38,    13,    13,     6,     4,    13,    78,
      84,    14,    13,    71,    10,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    32,     0,    15,    17,    19,    20,    23,    25,
      33,    34,    35,    36,    37,    53,     7,     6,    40,     6,
       6,     4,     6,    38,     4,     3,    10,    10,     3,    39,
      41,     7,    11,    27,    28,    55,    10,     9,    16,    21,
      42,    43,    47,    57,    11,    11,     4,    40,     7,     8,
      18,    48,    51,     4,     5,     6,    10,    21,    22,    29,
      56,    58,    57,    57,     5,    10,     4,    44,     4,    29,
      52,    54,     9,    12,    12,    10,    56,    10,     7,    10,
       4,     8,    12,    12,    26,    55,    59,     4,     5,     4,
       5,    46,    46,    47,     3,     4,    49,    50,    46,    50,
       8,    13,    13,     8,    45,    13,    14,    13,    10,    10,
      46,     6,     4,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    33,    33,
      34,    35,    35,    36,    36,    37,    38,    38,    39,    39,
      40,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    46,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    52,    53,    53,    54,    54,    55,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       3,     2,     2,     3,     4,     6,     0,     2,     4,     5,
       1,     0,     0,     2,     4,     6,     0,     4,     0,     5,
       0,     2,     1,     1,     0,     2,     6,     0,     1,     1,
       3,     0,     2,     5,     4,     9,     0,     2,     3,     4,
       4,     1,     1,     0,     2,     1,     3,     1,     3,     4,
       1,     4,     0,     3
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
        yyerror (parseParam, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, parseParam); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, ParseParams *parseParam)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (parseParam);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, ParseParams *parseParam)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, parseParam);
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
                 int yyrule, ParseParams *parseParam)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], parseParam);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, parseParam); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, ParseParams *parseParam)
{
  YY_USE (yyvaluep);
  YY_USE (parseParam);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (ParseParams *parseParam)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
      yychar = yylex (&yylval, parseParam);
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
  case 2: /* StartSymbol: TopFormList  */
#line 175 "grampar.y"
               { ((ParseParams*)parseParam)->treeTop = new GrammarAST((yyvsp[0].topFormList)); (yyval.num)=0; }
#line 1254 "grampar.tab.c"
    break;

  case 3: /* TopFormList: %empty  */
#line 179 "grampar.y"
                                    { (yyval.topFormList) = new ASTList<TopForm>; }
#line 1260 "grampar.tab.c"
    break;

  case 4: /* TopFormList: TopFormList TopForm  */
#line 180 "grampar.y"
                                    { ((yyval.topFormList)=(yyvsp[-1].topFormList))->append((yyvsp[0].topForm)); }
#line 1266 "grampar.tab.c"
    break;

  case 5: /* TopForm: ContextClass  */
#line 184 "grampar.y"
                                    { (yyval.topForm) = (yyvsp[0].topForm); }
#line 1272 "grampar.tab.c"
    break;

  case 6: /* TopForm: Verbatim  */
#line 185 "grampar.y"
                                    { (yyval.topForm) = (yyvsp[0].topForm); }
#line 1278 "grampar.tab.c"
    break;

  case 7: /* TopForm: Option  */
#line 186 "grampar.y"
                                    { (yyval.topForm) = (yyvsp[0].topForm); }
#line 1284 "grampar.tab.c"
    break;

  case 8: /* TopForm: Terminals  */
#line 187 "grampar.y"
                                    { (yyval.topForm) = (yyvsp[0].topForm); }
#line 1290 "grampar.tab.c"
    break;

  case 9: /* TopForm: Nonterminal  */
#line 188 "grampar.y"
                                    { (yyval.topForm) = (yyvsp[0].topForm); }
#line 1296 "grampar.tab.c"
    break;

  case 10: /* ContextClass: "context_class" TOK_LIT_CODE ";"  */
#line 193 "grampar.y"
                { (yyval.topForm) = new TF_context((yyvsp[-1].str)); }
#line 1302 "grampar.tab.c"
    break;

  case 11: /* Verbatim: "verbatim" TOK_LIT_CODE  */
#line 197 "grampar.y"
                                           { (yyval.topForm) = new TF_verbatim(false, (yyvsp[0].str)); }
#line 1308 "grampar.tab.c"
    break;

  case 12: /* Verbatim: "impl_verbatim" TOK_LIT_CODE  */
#line 198 "grampar.y"
                                           { (yyval.topForm) = new TF_verbatim(true, (yyvsp[0].str)); }
#line 1314 "grampar.tab.c"
    break;

  case 13: /* Option: "option" TOK_NAME ";"  */
#line 203 "grampar.y"
                                           { (yyval.topForm) = new TF_option((yyvsp[-1].str), 1); }
#line 1320 "grampar.tab.c"
    break;

  case 14: /* Option: "option" TOK_NAME TOK_INTEGER ";"  */
#line 204 "grampar.y"
                                           { (yyval.topForm) = new TF_option((yyvsp[-2].str), (yyvsp[-1].num)); }
#line 1326 "grampar.tab.c"
    break;

  case 15: /* Terminals: "terminals" "{" TermDecls TermTypes Precedence "}"  */
#line 216 "grampar.y"
             { (yyval.topForm) = new TF_terminals((yyvsp[-3].termDecls), (yyvsp[-2].termTypes), (yyvsp[-1].precSpecs)); }
#line 1332 "grampar.tab.c"
    break;

  case 16: /* TermDecls: %empty  */
#line 220 "grampar.y"
                                                   { (yyval.termDecls) = new ASTList<TermDecl>; }
#line 1338 "grampar.tab.c"
    break;

  case 17: /* TermDecls: TermDecls TerminalDecl  */
#line 221 "grampar.y"
                                                   { ((yyval.termDecls)=(yyvsp[-1].termDecls))->append((yyvsp[0].termDecl)); }
#line 1344 "grampar.tab.c"
    break;

  case 18: /* TerminalDecl: TOK_INTEGER ":" TOK_NAME ";"  */
#line 230 "grampar.y"
                { (yyval.termDecl) = new TermDecl((yyvsp[-3].num), (yyvsp[-1].str), sameloc((yyvsp[-1].str), "")); }
#line 1350 "grampar.tab.c"
    break;

  case 19: /* TerminalDecl: TOK_INTEGER ":" TOK_NAME TOK_STRING ";"  */
#line 232 "grampar.y"
                { (yyval.termDecl) = new TermDecl((yyvsp[-4].num), (yyvsp[-2].str), (yyvsp[-1].str)); }
#line 1356 "grampar.tab.c"
    break;

  case 20: /* Type: TOK_LIT_CODE  */
#line 236 "grampar.y"
                                      { (yyval.str) = (yyvsp[0].str); }
#line 1362 "grampar.tab.c"
    break;

  case 21: /* Type: %empty  */
#line 237 "grampar.y"
                                      { (yyval.str) = nolocNULL(); }
#line 1368 "grampar.tab.c"
    break;

  case 22: /* TermTypes: %empty  */
#line 241 "grampar.y"
                                      { (yyval.termTypes) = new ASTList<TermType>; }
#line 1374 "grampar.tab.c"
    break;

  case 23: /* TermTypes: TermTypes TermType  */
#line 242 "grampar.y"
                                      { ((yyval.termTypes)=(yyvsp[-1].termTypes))->append((yyvsp[0].termType)); }
#line 1380 "grampar.tab.c"
    break;

  case 24: /* TermType: "token" Type TOK_NAME ";"  */
#line 247 "grampar.y"
            { (yyval.termType) = new TermType((yyvsp[-1].str), (yyvsp[-2].str), new ASTList<SpecFunc>); }
#line 1386 "grampar.tab.c"
    break;

  case 25: /* TermType: "token" Type TOK_NAME "{" SpecFuncs "}"  */
#line 249 "grampar.y"
            { (yyval.termType) = new TermType((yyvsp[-3].str), (yyvsp[-4].str), (yyvsp[-1].specFuncs)); }
#line 1392 "grampar.tab.c"
    break;

  case 26: /* Precedence: %empty  */
#line 253 "grampar.y"
                                             { (yyval.precSpecs) = new ASTList<PrecSpec>; }
#line 1398 "grampar.tab.c"
    break;

  case 27: /* Precedence: "precedence" "{" PrecSpecs "}"  */
#line 254 "grampar.y"
                                             { (yyval.precSpecs) = (yyvsp[-1].precSpecs); }
#line 1404 "grampar.tab.c"
    break;

  case 28: /* PrecSpecs: %empty  */
#line 259 "grampar.y"
             { (yyval.precSpecs) = new ASTList<PrecSpec>; }
#line 1410 "grampar.tab.c"
    break;

  case 29: /* PrecSpecs: PrecSpecs TOK_NAME TOK_INTEGER NameOrStringList ";"  */
#line 261 "grampar.y"
             { ((yyval.precSpecs)=(yyvsp[-4].precSpecs))->append(new PrecSpec(whichKind((yyvsp[-3].str)), (yyvsp[-2].num), (yyvsp[-1].stringList))); }
#line 1416 "grampar.tab.c"
    break;

  case 30: /* NameOrStringList: %empty  */
#line 265 "grampar.y"
                                                  { (yyval.stringList) = new ASTList<LocString>; }
#line 1422 "grampar.tab.c"
    break;

  case 31: /* NameOrStringList: NameOrStringList NameOrString  */
#line 266 "grampar.y"
                                                  { ((yyval.stringList)=(yyvsp[-1].stringList))->append((yyvsp[0].str)); }
#line 1428 "grampar.tab.c"
    break;

  case 32: /* NameOrString: TOK_NAME  */
#line 270 "grampar.y"
                             { (yyval.str) = (yyvsp[0].str); }
#line 1434 "grampar.tab.c"
    break;

  case 33: /* NameOrString: TOK_STRING  */
#line 271 "grampar.y"
                             { (yyval.str) = (yyvsp[0].str); }
#line 1440 "grampar.tab.c"
    break;

  case 34: /* SpecFuncs: %empty  */
#line 277 "grampar.y"
                                      { (yyval.specFuncs) = new ASTList<SpecFunc>; }
#line 1446 "grampar.tab.c"
    break;

  case 35: /* SpecFuncs: SpecFuncs SpecFunc  */
#line 278 "grampar.y"
                                      { ((yyval.specFuncs)=(yyvsp[-1].specFuncs))->append((yyvsp[0].specFunc)); }
#line 1452 "grampar.tab.c"
    break;

  case 36: /* SpecFunc: "fun" TOK_NAME "(" FormalsOpt ")" TOK_LIT_CODE  */
#line 283 "grampar.y"
            { (yyval.specFunc) = new SpecFunc((yyvsp[-4].str), (yyvsp[-2].stringList), (yyvsp[0].str)); }
#line 1458 "grampar.tab.c"
    break;

  case 37: /* FormalsOpt: %empty  */
#line 287 "grampar.y"
                                      { (yyval.stringList) = new ASTList<LocString>; }
#line 1464 "grampar.tab.c"
    break;

  case 38: /* FormalsOpt: Formals  */
#line 288 "grampar.y"
                                      { (yyval.stringList) = (yyvsp[0].stringList); }
#line 1470 "grampar.tab.c"
    break;

  case 39: /* Formals: TOK_NAME  */
#line 292 "grampar.y"
                                      { (yyval.stringList) = new ASTList<LocString>((yyvsp[0].str)); }
#line 1476 "grampar.tab.c"
    break;

  case 40: /* Formals: Formals "," TOK_NAME  */
#line 293 "grampar.y"
                                      { ((yyval.stringList)=(yyvsp[-2].stringList))->append((yyvsp[0].str)); }
#line 1482 "grampar.tab.c"
    break;

  case 41: /* NTForbidNexts: %empty  */
#line 299 "grampar.y"
                                      { (yyval.stringList) = new ASTList<LocString>; }
#line 1488 "grampar.tab.c"
    break;

  case 42: /* NTForbidNexts: NTForbidNexts NTForbidNext  */
#line 301 "grampar.y"
                                      { ((yyval.stringList)=(yyvsp[-1].stringList))->append((yyvsp[0].str)); }
#line 1494 "grampar.tab.c"
    break;

  case 43: /* NTForbidNext: "forbid_next" "(" NameOrString ")" ";"  */
#line 305 "grampar.y"
                                                         { (yyval.str) = (yyvsp[-2].str); }
#line 1500 "grampar.tab.c"
    break;

  case 44: /* Nonterminal: "nonterm" Type TOK_NAME Production  */
#line 317 "grampar.y"
               { (yyval.topForm) = new TF_nonterm((yyvsp[-1].str), (yyvsp[-2].str), new ASTList<SpecFunc>, NULL,
                                     new ASTList<ProdDecl>((yyvsp[0].prodDecl)), NULL); }
#line 1507 "grampar.tab.c"
    break;

  case 45: /* Nonterminal: "nonterm" Type TOK_NAME "{" SpecFuncs NTForbidNexts Productions Subsets "}"  */
#line 320 "grampar.y"
               { (yyval.topForm) = new TF_nonterm((yyvsp[-6].str), (yyvsp[-7].str), (yyvsp[-4].specFuncs), (yyvsp[-3].stringList), (yyvsp[-2].prodDecls), (yyvsp[-1].stringList)); }
#line 1513 "grampar.tab.c"
    break;

  case 46: /* Productions: %empty  */
#line 324 "grampar.y"
                                           { (yyval.prodDecls) = new ASTList<ProdDecl>; }
#line 1519 "grampar.tab.c"
    break;

  case 47: /* Productions: Productions Production  */
#line 325 "grampar.y"
                                           { ((yyval.prodDecls)=(yyvsp[-1].prodDecls))->append((yyvsp[0].prodDecl)); }
#line 1525 "grampar.tab.c"
    break;

  case 48: /* Production: "->" RHS Action  */
#line 329 "grampar.y"
                                                { (yyval.prodDecl) = new ProdDecl((yyvsp[-2].loc), PDK_NEW, (yyvsp[-1].rhsList), (yyvsp[0].str)); }
#line 1531 "grampar.tab.c"
    break;

  case 49: /* Production: "replace" "->" RHS Action  */
#line 330 "grampar.y"
                                                { (yyval.prodDecl) = new ProdDecl((yyvsp[-2].loc), PDK_REPLACE,(yyvsp[-1].rhsList), (yyvsp[0].str)); }
#line 1537 "grampar.tab.c"
    break;

  case 50: /* Production: "delete" "->" RHS ";"  */
#line 331 "grampar.y"
                                                { (yyval.prodDecl) = new ProdDecl((yyvsp[-2].loc), PDK_DELETE, (yyvsp[-1].rhsList), nolocNULL()); }
#line 1543 "grampar.tab.c"
    break;

  case 51: /* Action: TOK_LIT_CODE  */
#line 335 "grampar.y"
                                           { (yyval.str) = (yyvsp[0].str); }
#line 1549 "grampar.tab.c"
    break;

  case 52: /* Action: ";"  */
#line 336 "grampar.y"
                                           { (yyval.str) = nolocNULL(); }
#line 1555 "grampar.tab.c"
    break;

  case 53: /* RHS: %empty  */
#line 340 "grampar.y"
                                           { (yyval.rhsList) = new ASTList<RHSElt>; }
#line 1561 "grampar.tab.c"
    break;

  case 54: /* RHS: RHS RHSElt  */
#line 341 "grampar.y"
                                           { ((yyval.rhsList)=(yyvsp[-1].rhsList))->append((yyvsp[0].rhsElt)); }
#line 1567 "grampar.tab.c"
    break;

  case 55: /* RHSElt: TOK_NAME  */
#line 350 "grampar.y"
                                { (yyval.rhsElt) = new RH_name(sameloc((yyvsp[0].str), ""), (yyvsp[0].str)); }
#line 1573 "grampar.tab.c"
    break;

  case 56: /* RHSElt: TOK_NAME ":" TOK_NAME  */
#line 351 "grampar.y"
                                { (yyval.rhsElt) = new RH_name((yyvsp[-2].str), (yyvsp[0].str)); }
#line 1579 "grampar.tab.c"
    break;

  case 57: /* RHSElt: TOK_STRING  */
#line 352 "grampar.y"
                                { (yyval.rhsElt) = new RH_string(sameloc((yyvsp[0].str), ""), (yyvsp[0].str)); }
#line 1585 "grampar.tab.c"
    break;

  case 58: /* RHSElt: TOK_NAME ":" TOK_STRING  */
#line 353 "grampar.y"
                                { (yyval.rhsElt) = new RH_string((yyvsp[-2].str), (yyvsp[0].str)); }
#line 1591 "grampar.tab.c"
    break;

  case 59: /* RHSElt: "precedence" "(" NameOrString ")"  */
#line 354 "grampar.y"
                                             { (yyval.rhsElt) = new RH_prec((yyvsp[-1].str)); }
#line 1597 "grampar.tab.c"
    break;

  case 60: /* RHSElt: "precedence_prefer_shift"  */
#line 355 "grampar.y"
                                             { (yyval.rhsElt) = new RH_precedence_prefer_shift(); }
#line 1603 "grampar.tab.c"
    break;

  case 61: /* RHSElt: "forbid_next" "(" NameOrString ")"  */
#line 356 "grampar.y"
                                             { (yyval.rhsElt) = new RH_forbid((yyvsp[-1].str)); }
#line 1609 "grampar.tab.c"
    break;

  case 62: /* Subsets: %empty  */
#line 360 "grampar.y"
                                    { (yyval.stringList) = NULL; }
#line 1615 "grampar.tab.c"
    break;

  case 63: /* Subsets: "subsets" Formals ";"  */
#line 361 "grampar.y"
                                    { (yyval.stringList) = (yyvsp[-1].stringList); }
#line 1621 "grampar.tab.c"
    break;


#line 1625 "grampar.tab.c"

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
      yyerror (parseParam, YY_("syntax error"));
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
                      yytoken, &yylval, parseParam);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, parseParam);
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
  yyerror (parseParam, YY_("memory exhausted"));
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
                  yytoken, &yylval, parseParam);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, parseParam);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 365 "grampar.y"

/* ------------------ extra C code ------------------ */
AssocKind whichKind(LocString * /*owner*/ kind)
{
  // delete 'kind' however we exit
  Owner<LocString> killer(kind);

  #define CHECK(syntax, value)   \
    if (kind->equals(syntax)) {  \
      return value;              \
    }
  CHECK("left", AK_LEFT);
  CHECK("right", AK_RIGHT);
  CHECK("nonassoc", AK_NONASSOC);
  CHECK("prec", AK_NEVERASSOC);
  CHECK("assoc_split", AK_SPLIT);
  #undef CHECK

  xbase(stringc << kind->locString()
                << ": invalid associativity kind: " << *kind);
}
