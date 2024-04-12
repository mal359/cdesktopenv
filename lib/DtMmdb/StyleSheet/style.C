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


/* Substitute the variable and function names.  */
#define yyparse         styleparse
#define yylex           stylelex
#define yyerror         styleerror
#define yydebug         styledebug
#define yynerrs         stylenerrs
#define yylval          stylelval
#define yychar          stylechar

/* First part of user prologue.  */

#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "StyleSheetExceptions.h"
#include "VariableTable.h"
#include "FeatureValue.h"
#include "Expression.h"
#include "SSPath.h"
#include "PathTable.h"
#include "Renderer.h"
#include "PathQualifier.h"
#include "Debug.h"
#include "ParserConst.h"
#include "FeatureDefDictionary.h"
#include <utility/funcs.h>

#include "HardCopy/autoNumberFP.h"
extern autoNumberFP gAutoNumberFP;

extern void yyerror(char*);
extern int yylex();

extern void enter_sgmlgi_context();

extern featureDefDictionary* g_FeatureDefDictionary;
extern unsigned g_validation_mode;
extern unsigned g_hasSemanticError;

static char localCharToCharPtrBuf[2];

#undef yywrap

const char* toUpperCase(unsigned char* string)
{
   static char buffer[512];
   int j=0;
   for ( int i=0; i<strlen((const char*)string); i++ ) 
   {
		 if (islower(string[i]))
		   buffer[j] = toupper(string[i]) ;
		 else
		   buffer[j] = (char)string[i] ;
		 j++;
   }
   buffer[j] = 0;
   return buffer;
}



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

#include "style.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_OPER_equality = 4,              /* OPER_equality  */
  YYSYMBOL_OPER_relational = 5,            /* OPER_relational  */
  YYSYMBOL_BOOLVAL = 6,                    /* BOOLVAL  */
  YYSYMBOL_REAL = 7,                       /* REAL  */
  YYSYMBOL_OPER_assign = 8,                /* OPER_assign  */
  YYSYMBOL_ARRAYOPEN = 9,                  /* ARRAYOPEN  */
  YYSYMBOL_ARRAYCLOSE = 10,                /* ARRAYCLOSE  */
  YYSYMBOL_SEPARATOR = 11,                 /* SEPARATOR  */
  YYSYMBOL_FSOPEN = 12,                    /* FSOPEN  */
  YYSYMBOL_FSCLOSE = 13,                   /* FSCLOSE  */
  YYSYMBOL_OPER_modify = 14,               /* OPER_modify  */
  YYSYMBOL_OPER_parent = 15,               /* OPER_parent  */
  YYSYMBOL_OPER_attr = 16,                 /* OPER_attr  */
  YYSYMBOL_OPER_oneof = 17,                /* OPER_oneof  */
  YYSYMBOL_OPER_star = 18,                 /* OPER_star  */
  YYSYMBOL_OPER_or = 19,                   /* OPER_or  */
  YYSYMBOL_OPER_and = 20,                  /* OPER_and  */
  YYSYMBOL_OPER_div = 21,                  /* OPER_div  */
  YYSYMBOL_OPER_parenopen = 22,            /* OPER_parenopen  */
  YYSYMBOL_OPER_parenclose = 23,           /* OPER_parenclose  */
  YYSYMBOL_OPER_logicalnegate = 24,        /* OPER_logicalnegate  */
  YYSYMBOL_PMEMOPEN = 25,                  /* PMEMOPEN  */
  YYSYMBOL_PMEMCLOSE = 26,                 /* PMEMCLOSE  */
  YYSYMBOL_OPER_period = 27,               /* OPER_period  */
  YYSYMBOL_OPER_plus = 28,                 /* OPER_plus  */
  YYSYMBOL_OPER_minus = 29,                /* OPER_minus  */
  YYSYMBOL_DIMENSION = 30,                 /* DIMENSION  */
  YYSYMBOL_NORMAL_STRING = 31,             /* NORMAL_STRING  */
  YYSYMBOL_UNIT_STRING = 32,               /* UNIT_STRING  */
  YYSYMBOL_QUOTED_STRING = 33,             /* QUOTED_STRING  */
  YYSYMBOL_GI_CASE_SENSITIVE = 34,         /* GI_CASE_SENSITIVE  */
  YYSYMBOL_SGMLGI_STRING = 35,             /* SGMLGI_STRING  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_stylesheet = 37,                /* stylesheet  */
  YYSYMBOL_sensitivity = 38,               /* sensitivity  */
  YYSYMBOL_39_statement_gp = 39,           /* statement.gp  */
  YYSYMBOL_var_assignment = 40,            /* var_assignment  */
  YYSYMBOL_symbol = 41,                    /* symbol  */
  YYSYMBOL_string_list = 42,               /* string_list  */
  YYSYMBOL_parent = 43,                    /* parent  */
  YYSYMBOL_attr = 44,                      /* attr  */
  YYSYMBOL_45_rhs_gp = 45,                 /* rhs.gp  */
  YYSYMBOL_simple_expr = 46,               /* simple_expr  */
  YYSYMBOL_multi_expr = 47,                /* multi_expr  */
  YYSYMBOL_OPER_mult = 48,                 /* OPER_mult  */
  YYSYMBOL_term = 49,                      /* term  */
  YYSYMBOL_array = 50,                     /* array  */
  YYSYMBOL_array_name = 51,                /* array_name  */
  YYSYMBOL_array_member_list = 52,         /* array_member_list  */
  YYSYMBOL_array_member = 53,              /* array_member  */
  YYSYMBOL_featureset = 54,                /* featureset  */
  YYSYMBOL_feature_list = 55,              /* feature_list  */
  YYSYMBOL_SEPARATOR_OPTL = 56,            /* SEPARATOR_OPTL  */
  YYSYMBOL_feature = 57,                   /* feature  */
  YYSYMBOL_feature_name_list = 58,         /* feature_name_list  */
  YYSYMBOL_path_expr = 59,                 /* path_expr  */
  YYSYMBOL_path_expr_list = 60,            /* path_expr_list  */
  YYSYMBOL_path_term_list = 61,            /* path_term_list  */
  YYSYMBOL_path_term = 62,                 /* path_term  */
  YYSYMBOL_OPER_feature = 63,              /* OPER_feature  */
  YYSYMBOL_OPER_add = 64,                  /* OPER_add  */
  YYSYMBOL_SGMLGI = 65,                    /* SGMLGI  */
  YYSYMBOL_SGMLGI_CONTENT = 66,            /* SGMLGI_CONTENT  */
  YYSYMBOL_67_1 = 67,                      /* $@1  */
  YYSYMBOL_dimension = 68,                 /* dimension  */
  YYSYMBOL_STRING = 69,                    /* STRING  */
  YYSYMBOL_path_selector = 70,             /* path_selector  */
  YYSYMBOL_boolean_expr = 71,              /* boolean_expr  */
  YYSYMBOL_logical_and_expr = 72,          /* logical_and_expr  */
  YYSYMBOL_equality_expr = 73,             /* equality_expr  */
  YYSYMBOL_POSITION_VALUE = 74,            /* POSITION_VALUE  */
  YYSYMBOL_sensitivityOPTL = 75,           /* sensitivityOPTL  */
  YYSYMBOL_76_statement_gpOPTL = 76,       /* statement.gpOPTL  */
  YYSYMBOL_77_statement_gpPLUS = 77,       /* statement.gpPLUS  */
  YYSYMBOL_path_selectorOPTL = 78          /* path_selectorOPTL  */
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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   127

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   193,   193,   198,   204,   207,   237,   252,   257,   261,
     272,   279,   287,   298,   306,   310,   314,   321,   341,   347,
     363,   379,   383,   389,   393,   402,   406,   410,   415,   420,
     425,   429,   433,   439,   455,   462,   467,   473,   478,   485,
     489,   495,   499,   505,   559,   566,   570,   574,   613,   619,
     626,   631,   644,   650,   655,   660,   667,   672,   677,   684,
     688,   691,   696,   718,   718,   728,   737,   743,   767,   771,
     777,   783,   793,   799,   803,   809,   819,   839,   843,   853,
     858,   863,   867,   871,   875,   881,   886
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
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER",
  "OPER_equality", "OPER_relational", "BOOLVAL", "REAL", "OPER_assign",
  "ARRAYOPEN", "ARRAYCLOSE", "SEPARATOR", "FSOPEN", "FSCLOSE",
  "OPER_modify", "OPER_parent", "OPER_attr", "OPER_oneof", "OPER_star",
  "OPER_or", "OPER_and", "OPER_div", "OPER_parenopen", "OPER_parenclose",
  "OPER_logicalnegate", "PMEMOPEN", "PMEMCLOSE", "OPER_period",
  "OPER_plus", "OPER_minus", "DIMENSION", "NORMAL_STRING", "UNIT_STRING",
  "QUOTED_STRING", "GI_CASE_SENSITIVE", "SGMLGI_STRING", "$accept",
  "stylesheet", "sensitivity", "statement.gp", "var_assignment", "symbol",
  "string_list", "parent", "attr", "rhs.gp", "simple_expr", "multi_expr",
  "OPER_mult", "term", "array", "array_name", "array_member_list",
  "array_member", "featureset", "feature_list", "SEPARATOR_OPTL",
  "feature", "feature_name_list", "path_expr", "path_expr_list",
  "path_term_list", "path_term", "OPER_feature", "OPER_add", "SGMLGI",
  "SGMLGI_CONTENT", "$@1", "dimension", "STRING", "path_selector",
  "boolean_expr", "logical_and_expr", "equality_expr", "POSITION_VALUE",
  "sensitivityOPTL", "statement.gpOPTL", "statement.gpPLUS",
  "path_selectorOPTL", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-64)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -26,    11,    28,   -86,    23,    36,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,     5,   -86,    38,   -86,    16,   -86,
      23,   -86,     7,    23,   -86,   -86,    26,    -6,   -86,   -86,
      -1,    25,   -86,   -86,    51,   -86,    21,   -86,   -86,    33,
      42,    62,    40,    50,   -86,    46,   -86,    47,    42,    42,
      85,   -86,   -86,    52,    56,    42,   -86,   -86,    48,    43,
     -86,   -86,    76,   -86,   -86,    84,    59,    42,    86,    -1,
     -86,    42,    23,   -86,    98,     1,   -86,    -6,    -6,   -86,
     -86,   -86,   -86,   -16,   -86,   -86,    42,    56,   -86,   -86,
      85,   -86,   -86,    85,    65,   -86,   -86,   -86,   -86,   -86,
     -86,    70,   -86,   -86,   -86,    50,   -86,   -86,   -86,    43,
     -86,   -86,    48,   -86,    94,    95,   -86,   -86,    85,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      80,     0,     0,    79,    82,     0,     1,    57,    58,    68,
      69,    84,     4,     5,     0,    55,    86,    62,    66,     2,
      81,     3,     0,     0,    50,    54,    66,     0,    85,    56,
      36,    65,    83,    42,    46,    44,     0,    49,    53,     0,
       0,     0,     0,    71,    73,    30,    23,    31,     0,     0,
       0,    67,    27,    25,     9,     0,     7,     6,    14,    18,
      20,    15,     0,    16,    26,    11,     0,    45,     0,    36,
      59,     0,     0,    51,     0,     0,    70,     0,     0,    28,
      29,    12,    13,     0,    11,    24,     0,     8,    60,    61,
       0,    21,    22,     0,    36,    64,    43,    41,    47,    48,
      52,     0,    77,    78,    76,    72,    74,    32,    10,    17,
      19,    34,    39,    40,     0,    38,    75,    33,    36,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,   -86,    88,   -86,   -86,    54,   -86,   -86,    41,
     -49,    15,   -86,    18,   -85,   -86,    -5,   -86,   105,   -86,
     -86,    45,   -86,   -20,   -86,   -86,   106,    87,   -86,     9,
     -86,   -86,   -86,    -4,   -86,   -86,    44,    49,   -86,   -86,
     -86,   -86,   -86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,    11,    12,    53,    54,    55,    56,    57,
      58,    59,    93,    60,    61,    62,   114,   115,    63,    34,
      68,    35,    36,    13,    39,    14,    15,    86,    90,    16,
      17,    66,    64,    26,    28,    42,    43,    44,   104,     4,
      19,    20,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      18,    83,    45,    38,   102,    46,    47,   107,     1,   113,
      40,    22,    88,    89,    48,    49,    18,    22,    37,     5,
      33,    50,     7,     8,    30,    41,    65,    23,     6,    51,
       9,    10,    52,   113,   103,    69,     9,    10,     9,    10,
       7,     8,    21,    31,    72,   112,    84,    27,    70,    74,
      76,    84,   100,    31,     9,    10,    73,    81,    82,    77,
     -63,    91,    67,    37,    92,    65,    75,    99,    45,   112,
      78,    46,    47,     9,    10,   111,    88,    89,    79,    80,
      48,    49,   108,    70,    85,    94,    84,    50,    45,    84,
      65,    46,    47,   -35,    95,    51,     9,    10,    52,    97,
      48,    49,   101,   116,   117,   109,   118,    50,    32,    87,
      98,   110,    96,   119,    65,    51,     9,    10,    52,    24,
      25,   105,     0,    71,     0,     0,     0,   106
};

static const yytype_int8 yycheck[] =
{
       4,    50,     3,    23,     3,     6,     7,    23,    34,    94,
      16,    12,    28,    29,    15,    16,    20,    12,    22,     8,
      13,    22,    17,    18,     8,    31,    30,    22,     0,    30,
      31,    32,    33,   118,    33,    14,    31,    32,    31,    32,
      17,    18,     6,    27,    11,    94,    50,     9,    27,    40,
      10,    55,    72,    27,    31,    32,    23,    48,    49,    19,
      35,    18,    11,    67,    21,    69,     4,    71,     3,   118,
      20,     6,     7,    31,    32,    10,    28,    29,    32,    32,
      15,    16,    86,    27,    32,     9,    90,    22,     3,    93,
      94,     6,     7,     9,    35,    30,    31,    32,    33,    13,
      15,    16,     4,    33,    10,    90,    11,    22,    20,    55,
      69,    93,    67,   118,   118,    30,    31,    32,    33,    14,
      14,    77,    -1,    36,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    34,    37,    38,    75,     8,     0,    17,    18,    31,
      32,    39,    40,    59,    61,    62,    65,    66,    69,    76,
      77,     6,    12,    22,    54,    62,    69,     9,    70,    78,
       8,    27,    39,    13,    55,    57,    58,    69,    59,    60,
      16,    31,    71,    72,    73,     3,     6,     7,    15,    16,
      22,    30,    33,    41,    42,    43,    44,    45,    46,    47,
      49,    50,    51,    54,    68,    69,    67,    11,    56,    14,
      27,    63,    11,    23,    65,     4,    10,    19,    20,    32,
      32,    65,    65,    46,    69,    32,    63,    42,    28,    29,
      64,    18,    21,    48,     9,    35,    57,    13,    45,    69,
      59,     4,     3,    33,    74,    72,    73,    23,    69,    47,
      49,    10,    46,    50,    52,    53,    33,    10,    11,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    39,    39,    40,    41,    41,    41,
      42,    42,    43,    44,    45,    45,    45,    46,    46,    47,
      47,    48,    48,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    63,
      64,    64,    65,    67,    66,    66,    66,    68,    69,    69,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     1,     1,     3,     1,     2,     1,
       3,     1,     2,     2,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     2,
       1,     1,     3,     4,     3,     1,     0,     3,     1,     1,
       1,     4,     2,     3,     1,     1,     0,     3,     3,     1,
       2,     4,     3,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     0,     4,     2,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     4,     3,     1,     1,     1,
       0,     1,     0,     2,     1,     1,     0
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
  case 2: /* stylesheet: sensitivityOPTL statement.gpOPTL  */
        {
	}
    break;

  case 3: /* sensitivity: GI_CASE_SENSITIVE OPER_assign BOOLVAL  */
        {
          gGI_CASE_SENSITIVE = (yyvsp[0].boolData);
	}
    break;

  case 4: /* statement.gp: var_assignment  */
        {
	}
    break;

  case 5: /* statement.gp: path_expr  */
        {
	  /* copy items form the feature list into the path table */
          PathFeatureListIterator l_Iter(*((yyvsp[0].PathFeatureListPtrData)));

          PathFeature *x = 0;

          while ( ++l_Iter ) {

            x = l_Iter.key();

            if ( g_validation_mode == true )
              if ( g_FeatureDefDictionary -> checkSemantics(x -> featureSet()) == false )
                 g_hasSemanticError = true;
               
	    gPathTab -> addPathFeatureSet( x );


          }

/* clear out the first list so the elements are not deleted
             with the list because they are still referenced by the
             path table */

	  (yyvsp[0].PathFeatureListPtrData) -> clear();
	  delete (yyvsp[0].PathFeatureListPtrData);

	}
    break;

  case 6: /* var_assignment: STRING OPER_assign rhs.gp  */
        {
           Expression *x = new Expression(new ConstantNode((yyvsp[0].FeatureValuePtrData)));

           if ( gAutoNumberFP.accept((const char*)(yyvsp[-2].charPtrData), x) ) {
	         delete (yyvsp[-2].charPtrData);
	         delete x;
                 break;
           }

           gVariableTable -> enter( gSymTab -> intern((const char*)(yyvsp[-2].charPtrData)), x);
	   delete (yyvsp[-2].charPtrData);
	}
    break;

  case 7: /* symbol: attr  */
        {
          (yyval.termNodePtrData)=(yyvsp[0].termNodePtrData);
	}
    break;

  case 8: /* symbol: parent string_list  */
        {
          (yyval.termNodePtrData)=(yyvsp[-1].termNodePtrData);
	}
    break;

  case 9: /* symbol: string_list  */
        {
          const Symbol* x = (yyvsp[0].CompositeVariableNodePtrData) -> convertableToVariable();
          if ( x ) {
            (yyval.termNodePtrData)=new VariableNode(*x);
            delete (yyvsp[0].CompositeVariableNodePtrData);
          } else
            (yyval.termNodePtrData)=(yyvsp[0].CompositeVariableNodePtrData);
	}
    break;

  case 10: /* string_list: string_list OPER_feature STRING  */
        {

	  (yyvsp[-2].CompositeVariableNodePtrData)->appendItem(gSymTab->intern(toUpperCase((yyvsp[0].charPtrData))));
	  (yyval.CompositeVariableNodePtrData)=(yyvsp[-2].CompositeVariableNodePtrData);
	  delete (yyvsp[0].charPtrData) ;
	}
    break;

  case 11: /* string_list: STRING  */
        {
	  (yyval.CompositeVariableNodePtrData)=new CompositeVariableNode;
          (yyval.CompositeVariableNodePtrData) -> appendItem(gSymTab->intern(toUpperCase((yyvsp[0].charPtrData))));
	  delete (yyvsp[0].charPtrData);
	}
    break;

  case 12: /* parent: OPER_parent SGMLGI  */
        {
/*
	  $$=new
            ParentNode(gSymTab->intern((const char*)$1));
*/
          MESSAGE(cerr, "^ operator not supported.");
          throw(StyleSheetException());
	}
    break;

  case 13: /* attr: OPER_attr SGMLGI  */
        {
	  (yyval.termNodePtrData)=new
            SgmlAttributeNode(gSymTab->intern((const char*)(yyvsp[0].charPtrData)));
	  delete (yyvsp[0].charPtrData);
	}
    break;

  case 14: /* rhs.gp: simple_expr  */
        {
	  (yyval.FeatureValuePtrData)=new FeatureValueExpression((yyvsp[0].expPtrData));
	}
    break;

  case 15: /* rhs.gp: array  */
        {
          (yyval.FeatureValuePtrData)=(yyvsp[0].FeatureValuePtrData);
	}
    break;

  case 16: /* rhs.gp: featureset  */
        {
	  (yyval.FeatureValuePtrData)=new FeatureValueFeatureSet((yyvsp[0].FeatureSetPtrData));
	}
    break;

  case 17: /* simple_expr: simple_expr OPER_add multi_expr  */
        {
	   BinaryOperatorNode::operatorType opType;
           switch ((yyvsp[-1].charData)) {
             case '+': opType=BinaryOperatorNode::PLUS; break;
             case '-': opType=BinaryOperatorNode::MINUS; break;
             default:
              throw(badEvaluationException());
           }

           FeatureValueExpression* FVexprL = new FeatureValueExpression((yyvsp[-2].expPtrData));
           FeatureValueExpression* FVexprR = new FeatureValueExpression((yyvsp[0].expPtrData));
           
           (yyval.expPtrData) = new Expression(
		 new BinaryOperatorNode(opType, 
					new ConstantNode(FVexprL),
					new ConstantNode(FVexprR)
				       )
			      );
	}
    break;

  case 18: /* simple_expr: multi_expr  */
        {
	   (yyval.expPtrData)=(yyvsp[0].expPtrData);
	}
    break;

  case 19: /* multi_expr: multi_expr OPER_mult term  */
        {
	   BinaryOperatorNode::operatorType opType;
           switch ((yyvsp[-1].charData)) {
             case '*': opType=BinaryOperatorNode::TIMES; break;
             case '/': opType=BinaryOperatorNode::DIVIDE; break;
             default:
              throw(badEvaluationException());
           }

           FeatureValueExpression* FVexpr = new FeatureValueExpression((yyvsp[-2].expPtrData));
           
           (yyval.expPtrData) = new Expression(
		 new BinaryOperatorNode(opType, new ConstantNode(FVexpr), (yyvsp[0].termNodePtrData))
			      );
	}
    break;

  case 20: /* multi_expr: term  */
        {
           (yyval.expPtrData) = new Expression((yyvsp[0].termNodePtrData));
	}
    break;

  case 21: /* OPER_mult: OPER_star  */
        {
	   (yyval.charData)=(yyvsp[0].charData);
        }
    break;

  case 22: /* OPER_mult: OPER_div  */
        {
	   (yyval.charData)=(yyvsp[0].charData);
        }
    break;

  case 23: /* term: BOOLVAL  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueInt(int((yyvsp[0].boolData))));
        }
    break;

  case 24: /* term: symbol UNIT_STRING  */
        {
	  FeatureValueExpression* fve = 
		new FeatureValueExpression(new Expression((yyvsp[-1].termNodePtrData)));
          FeatureValueDimension* x = 
             new FeatureValueDimension(fve, (const char*)(yyvsp[0].charPtrData));
	  delete (yyvsp[0].charPtrData) ;
          (yyval.termNodePtrData)=new ConstantNode(x);
	}
    break;

  case 25: /* term: symbol  */
        {
	  (yyval.termNodePtrData)=(yyvsp[0].termNodePtrData);
	}
    break;

  case 26: /* term: dimension  */
        {
	  (yyval.termNodePtrData)=(yyvsp[0].termNodePtrData);
	}
    break;

  case 27: /* term: QUOTED_STRING  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueString((const char*)(yyvsp[0].charPtrData)));
	  delete (yyvsp[0].charPtrData) ;
        }
    break;

  case 28: /* term: INTEGER UNIT_STRING  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueDimension(new FeatureValueInt((yyvsp[-1].intData)), (const char*)(yyvsp[0].charPtrData)));
	  delete (yyvsp[0].charPtrData) ;
        }
    break;

  case 29: /* term: REAL UNIT_STRING  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueDimension(new FeatureValueReal((yyvsp[-1].realData)), (const char*)(yyvsp[0].charPtrData)));
	  delete (yyvsp[0].charPtrData) ;
        }
    break;

  case 30: /* term: INTEGER  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueInt((yyvsp[0].intData)));
        }
    break;

  case 31: /* term: REAL  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueReal((yyvsp[0].realData)));
        }
    break;

  case 32: /* term: OPER_parenopen simple_expr OPER_parenclose  */
        {
          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueExpression((yyvsp[-1].expPtrData)));
        }
    break;

  case 33: /* array: array_name ARRAYOPEN array_member_list ARRAYCLOSE  */
        {
          FeatureValueArray* x = 
	     new FeatureValueArray((const char*)(yyvsp[-3].charPtrData), (yyvsp[-1].FeatureValueSlistPtrData) -> entries());
          CC_TPtrSlistIterator<FeatureValue> iter(*(yyvsp[-1].FeatureValueSlistPtrData));

          int i = 0;
          while ( ++iter ) {
            (*x)[i++] = iter.key();
          }

          delete (yyvsp[-3].charPtrData);
          delete (yyvsp[-1].FeatureValueSlistPtrData);

          (yyval.FeatureValuePtrData) = x;
	}
    break;

  case 34: /* array: array_name ARRAYOPEN ARRAYCLOSE  */
        {
          (yyval.FeatureValuePtrData) = new FeatureValueArray((const char*)(yyvsp[-2].charPtrData), 0);
          delete (yyvsp[-2].charPtrData);
	}
    break;

  case 35: /* array_name: STRING  */
        {
          (yyval.charPtrData) = (yyvsp[0].charPtrData);
	}
    break;

  case 36: /* array_name: %empty  */
        {
          (yyval.charPtrData) = new unsigned char[1];
          (yyval.charPtrData)[0] = 0;
	}
    break;

  case 37: /* array_member_list: array_member SEPARATOR array_member_list  */
        {
           (yyvsp[0].FeatureValueSlistPtrData) -> prepend((yyvsp[-2].FeatureValuePtrData));
           (yyval.FeatureValueSlistPtrData) = (yyvsp[0].FeatureValueSlistPtrData);
	}
    break;

  case 38: /* array_member_list: array_member  */
        {
           (yyval.FeatureValueSlistPtrData)=new CC_TPtrSlist<FeatureValue>;
           (yyval.FeatureValueSlistPtrData) -> append((yyvsp[0].FeatureValuePtrData));
	}
    break;

  case 39: /* array_member: simple_expr  */
        {
	   (yyval.FeatureValuePtrData) = new FeatureValueExpression((yyvsp[0].expPtrData));
	}
    break;

  case 40: /* array_member: array  */
        {
	   (yyval.FeatureValuePtrData)=(yyvsp[0].FeatureValuePtrData);
	}
    break;

  case 41: /* featureset: FSOPEN feature_list SEPARATOR_OPTL FSCLOSE  */
        {
	   (yyval.FeatureSetPtrData)=(yyvsp[-2].FeatureSetPtrData);
	}
    break;

  case 42: /* featureset: FSOPEN FSCLOSE  */
        {
	  (yyval.FeatureSetPtrData) = new FeatureSet ();
	}
    break;

  case 43: /* feature_list: feature_list SEPARATOR feature  */
        {
	   if ((yyvsp[0].FeaturePtrData) -> name() == Symbol(gSymTab->intern("FAMILY"))) {
	     // the evaluate() call clones $3 
	     FeatureValueFeatureSet *fvfs = 
	       (FeatureValueFeatureSet*) (yyvsp[0].FeaturePtrData)->evaluate();
	     const FeatureSet* fs = fvfs->value();
	      const Feature* charsetF =
		fs->lookup(gSymTab->intern("CHARSET"));
	      // charsetF is a mandatory entry in fontfamily
	      assert( charsetF );
	      const FeatureValueString* fv_string =
			(FeatureValueString*)charsetF->value();
	      const char* charset = *fv_string;
	      assert( charset );
	      
	      int entries = (yyvsp[-2].FeatureSetPtrData) -> entries();
	      for (int i=0; i<entries; i++) {
		const Feature* entry = (yyvsp[-2].FeatureSetPtrData)->at(i);
		if (! (entry->name() == Symbol(gSymTab->intern("FAMILY"))))
		  continue;
		const FeatureSet* entry_fs =
			((FeatureValueFeatureSet*)(entry->evaluate()))->value();
		const Feature* entry_charsetF =
			entry_fs->lookup(gSymTab->intern("CHARSET"));
		assert( entry_charsetF );
		const char* entry_charset =
			*((FeatureValueString*)(entry_charsetF->value()));
		assert( entry_charset );
		if (! strcmp(charset, entry_charset)) {
		  delete (yyvsp[-2].FeatureSetPtrData) -> removeAt(i);
		  break; // escape from for-loop
		}
	      }
	      delete fvfs ;

	      (yyval.FeatureSetPtrData) = (yyvsp[-2].FeatureSetPtrData);
	      (yyval.FeatureSetPtrData) -> add((yyvsp[0].FeaturePtrData));
	   }
	   else {
	      if ( (yyvsp[-2].FeatureSetPtrData) -> find((Feature*)(yyvsp[0].FeaturePtrData)) ) {
		FeatureSet* fs = new FeatureSet();
		fs -> add((yyvsp[0].FeaturePtrData));

		(yyval.FeatureSetPtrData) =new FeatureSet(*(yyvsp[-2].FeatureSetPtrData), *fs);
		delete (yyvsp[-2].FeatureSetPtrData);
		delete fs;
	      }
	      else {
		(yyval.FeatureSetPtrData)=(yyvsp[-2].FeatureSetPtrData);
		(yyval.FeatureSetPtrData) -> add((yyvsp[0].FeaturePtrData));
	      }
	   }
	}
    break;

  case 44: /* feature_list: feature  */
        {
	   (yyval.FeatureSetPtrData)=new FeatureSet();
	   (yyval.FeatureSetPtrData) -> add((yyvsp[0].FeaturePtrData));
	}
    break;

  case 45: /* SEPARATOR_OPTL: SEPARATOR  */
        {
	}
    break;

  case 46: /* SEPARATOR_OPTL: %empty  */
        {
	}
    break;

  case 47: /* feature: feature_name_list OPER_modify rhs.gp  */
        {
          CC_TPtrDlistIterator<char> l_Iter(*((yyvsp[-2].charPtrDlistData)));

          FeatureSet *fs = 0;
          Feature *f = 0;
          FeatureValue *fv = (yyvsp[0].FeatureValuePtrData);
          const char* cptr = 0;
	  char buffer[256];
          while (++l_Iter) {
             cptr = l_Iter.key();
	     int index = 0 ;
	     const char *c = cptr ;
	     while (*c)
	       {
		 if (islower(*c))
		   buffer[index] = toupper(*c) ;
		 else
		   buffer[index] = *c ;
		 c++ ;
		 index++;
	       }
	     buffer[index] = 0;
	     /* fprintf(stderr, "converted: %s to %s\n", cptr, buffer); */
	     f = new Feature(gSymTab -> intern(buffer), fv);

             if ( (yyvsp[-2].charPtrDlistData) -> last() != cptr ) {
                fs = new FeatureSet();
                fs -> add(f);
                fv = new FeatureValueFeatureSet(fs);
             }
	  }

	  (yyvsp[-2].charPtrDlistData)->clearAndDestroy();
	  delete (yyvsp[-2].charPtrDlistData) ;
	  (yyval.FeaturePtrData)=f;
	}
    break;

  case 48: /* feature_name_list: feature_name_list OPER_feature STRING  */
        {
          (yyvsp[-2].charPtrDlistData) -> prepend((char *)(yyvsp[0].charPtrData));
          (yyval.charPtrDlistData)=(yyvsp[-2].charPtrDlistData);
	}
    break;

  case 49: /* feature_name_list: STRING  */
        {
          (yyval.charPtrDlistData)=new CC_TPtrDlist<char>;
          (yyval.charPtrDlistData) -> append((char *)(yyvsp[0].charPtrData));
	}
    break;

  case 50: /* path_expr: path_term_list featureset  */
        {
           (yyval.PathFeatureListPtrData)=new PathFeatureList;
           (yyval.PathFeatureListPtrData) -> append(new PathFeature((yyvsp[-1].PathPtrData), (yyvsp[0].FeatureSetPtrData)));
	}
    break;

  case 51: /* path_expr: path_term_list OPER_parenopen path_expr_list OPER_parenclose  */
        {
	  
          PathFeatureListIterator l_Iter(*((yyvsp[-1].PathFeatureListPtrData)));

          while ( ++l_Iter ) {
             (l_Iter.key()) -> path() -> prependPath(*(yyvsp[-3].PathPtrData));
          }
	  delete (yyvsp[-3].PathPtrData);
          (yyval.PathFeatureListPtrData)=(yyvsp[-1].PathFeatureListPtrData);
	}
    break;

  case 52: /* path_expr_list: path_expr_list SEPARATOR path_expr  */
        {
           (yyval.PathFeatureListPtrData)=(yyvsp[-2].PathFeatureListPtrData);
           (yyval.PathFeatureListPtrData) -> appendList(*(yyvsp[0].PathFeatureListPtrData));
	   delete (yyvsp[0].PathFeatureListPtrData) ;
	}
    break;

  case 53: /* path_expr_list: path_expr  */
        {
           (yyval.PathFeatureListPtrData)=(yyvsp[0].PathFeatureListPtrData);
	}
    break;

  case 54: /* path_term_list: path_term_list path_term  */
        {
	  (yyvsp[-1].PathPtrData) -> appendPathTerm((yyvsp[0].PathTermPtrData));
	  (yyval.PathPtrData)=(yyvsp[-1].PathPtrData);
	}
    break;

  case 55: /* path_term_list: path_term  */
        {
          (yyval.PathPtrData) = new SSPath;
          (yyval.PathPtrData) -> appendPathTerm((yyvsp[0].PathTermPtrData));
	}
    break;

  case 56: /* path_term: SGMLGI path_selectorOPTL  */
        {
	  (yyval.PathTermPtrData)=new PathTerm((const char*)(yyvsp[-1].charPtrData), (yyvsp[0].PQExprPtrData));
          delete (yyvsp[-1].charPtrData);
	}
    break;

  case 57: /* path_term: OPER_oneof  */
        {
          localCharToCharPtrBuf[0]=(yyvsp[0].charData); localCharToCharPtrBuf[1]=0;
	  (yyval.PathTermPtrData)=new PathTerm(localCharToCharPtrBuf, 0);
	}
    break;

  case 58: /* path_term: OPER_star  */
        {
          localCharToCharPtrBuf[0]=(yyvsp[0].charData); localCharToCharPtrBuf[1]=0;
	  (yyval.PathTermPtrData)=new PathTerm(localCharToCharPtrBuf, 0);
	}
    break;

  case 59: /* OPER_feature: OPER_period  */
        {
	}
    break;

  case 60: /* OPER_add: OPER_plus  */
        {
	}
    break;

  case 61: /* OPER_add: OPER_minus  */
        {
	}
    break;

  case 62: /* SGMLGI: SGMLGI_CONTENT  */
        {
	// char % can start an OLIAS internal element which
	// is used only by the browser.
	// Example %BOGUS within HEAD1 in OLIAS book

           if ( (yyvsp[0].charPtrData)[0] != '%' && isalnum((yyvsp[0].charPtrData)[0]) == 0 ) {
              MESSAGE(cerr, form("%s is not a SGMLGI", (yyvsp[0].charPtrData)));
              throw(badEvaluationException());
           }
          /* note, should probably be using RCStrings, would make wide */
          /* char handling better too? */
           if ( gGI_CASE_SENSITIVE == false )
             {
               for (int i=0; i<strlen((const char*)(yyvsp[0].charPtrData)); i++)
                 if ( islower((yyvsp[0].charPtrData)[i]) )
                   (yyvsp[0].charPtrData)[i] = toupper((yyvsp[0].charPtrData)[i]);
             }
           (yyval.charPtrData)=(yyvsp[0].charPtrData);
	}
    break;

  case 63: /* $@1: %empty  */
                                    {enter_sgmlgi_context();}
    break;

  case 64: /* SGMLGI_CONTENT: STRING OPER_period $@1 SGMLGI_STRING  */
        {
           int l = strlen((char*)(yyvsp[-3].charPtrData)) + strlen((char*)(yyvsp[0].charPtrData)) + 2;
           (yyval.charPtrData)=new unsigned char[l];
           strcpy((char*)(yyval.charPtrData), (char*)(yyvsp[-3].charPtrData));
           strcat((char*)(yyval.charPtrData), ".");
           strcat((char*)(yyval.charPtrData), (char*)(yyvsp[0].charPtrData));
           delete (yyvsp[-3].charPtrData);
           delete (yyvsp[0].charPtrData);
	}
    break;

  case 65: /* SGMLGI_CONTENT: STRING OPER_period  */
        {
           int l = strlen((char*)(yyvsp[-1].charPtrData)) + 2;
           (yyval.charPtrData)=new unsigned char[l];
           strcpy((char*)(yyval.charPtrData), (char*)(yyvsp[-1].charPtrData));
           strcat((char*)(yyval.charPtrData), ".");
           delete (yyvsp[-1].charPtrData);
	}
    break;

  case 66: /* SGMLGI_CONTENT: STRING  */
        {
           (yyval.charPtrData)=(yyvsp[0].charPtrData);
	}
    break;

  case 67: /* dimension: DIMENSION  */
        {
          int i;

          for (i=0; i<strlen((const char*)(yyvsp[0].charPtrData)); i++) {

            if ( isalpha((yyvsp[0].charPtrData)[i]) ) 
               break;
          }

          char c;
          float x;
          if ( i > 0 ) {
             c = (yyvsp[0].charPtrData)[i]; (yyvsp[0].charPtrData)[i]=0;
             x = atof((const char*)(yyvsp[0].charPtrData));
             (yyvsp[0].charPtrData)[i]=c;
          } else
             x = 1;

          (yyval.termNodePtrData)=new ConstantNode(new FeatureValueDimension(new FeatureValueReal(x), (const char*)&(yyvsp[0].charPtrData)[i]));

          delete (yyvsp[0].charPtrData);
	}
    break;

  case 68: /* STRING: NORMAL_STRING  */
        {
 	   (yyval.charPtrData)=(yyvsp[0].charPtrData);
	}
    break;

  case 69: /* STRING: UNIT_STRING  */
        {
 	   (yyval.charPtrData)=(yyvsp[0].charPtrData);
	}
    break;

  case 70: /* path_selector: ARRAYOPEN boolean_expr ARRAYCLOSE  */
        {
           (yyval.PQExprPtrData)=(yyvsp[-1].PQExprPtrData);
	}
    break;

  case 71: /* boolean_expr: logical_and_expr  */
        {
//////////////////////////////////////////////////////
// This portion of the code (up to equality_expr) is 
// hacked for V1.1 only. Due to the way 
// PathQualifier.h is written, this code is not 
// general at all. qfc 8/16/94
//////////////////////////////////////////////////////
           (yyval.PQExprPtrData)=(yyvsp[0].PQExprPtrData);
	}
    break;

  case 72: /* boolean_expr: boolean_expr OPER_or logical_and_expr  */
        {
           (yyval.PQExprPtrData) = new PQLogExpr((yyvsp[-2].PQExprPtrData), PQor, (yyvsp[0].PQExprPtrData));
	}
    break;

  case 73: /* logical_and_expr: equality_expr  */
        {
           (yyval.PQExprPtrData)=(yyvsp[0].PQExprPtrData);
	}
    break;

  case 74: /* logical_and_expr: logical_and_expr OPER_and equality_expr  */
        {
           (yyval.PQExprPtrData) = new PQLogExpr((yyvsp[-2].PQExprPtrData), PQand, (yyvsp[0].PQExprPtrData));
	}
    break;

  case 75: /* equality_expr: OPER_attr SGMLGI OPER_equality QUOTED_STRING  */
        {
          (yyval.PQExprPtrData) = new PQAttributeSelector(
			gSymTab->intern((const char*)(yyvsp[-2].charPtrData)),
			( (yyvsp[-1].intData) == EQUAL ) ? PQEqual : PQNotEqual,
			(const char*)(yyvsp[0].charPtrData)
				      );
          delete (yyvsp[-2].charPtrData);
          delete (yyvsp[0].charPtrData);
	}
    break;

  case 76: /* equality_expr: NORMAL_STRING OPER_equality POSITION_VALUE  */
        {
           if ( strcasecmp((char*)(yyvsp[-2].charPtrData), "position") == 0 ) {
             (yyval.PQExprPtrData)=new PQPosition(
	  	  ( (yyvsp[-1].intData) == EQUAL ) ? PQEqual : PQNotEqual, 
		  (yyvsp[0].intData)
				);
           } else
           if ( strcasecmp((char*)(yyvsp[-2].charPtrData), "sibling") == 0 ) {
             (yyval.PQExprPtrData)=new PQSibling(
	  	  ( (yyvsp[-1].intData) == EQUAL ) ? PQEqual : PQNotEqual, 
		  (yyvsp[0].intData)
				);
           } else
              throw(StyleSheetException());

           delete (yyvsp[-2].charPtrData);
	}
    break;

  case 77: /* POSITION_VALUE: INTEGER  */
        {
           (yyval.intData) = (int)(yyvsp[0].intData);
	}
    break;

  case 78: /* POSITION_VALUE: QUOTED_STRING  */
        {
           if ( strcasecmp((char*)(yyvsp[0].charPtrData), "#LAST") != 0 ) 
              throw(StyleSheetException());

           (yyval.intData) = -1;
	}
    break;

  case 79: /* sensitivityOPTL: sensitivity  */
        {

	}
    break;

  case 80: /* sensitivityOPTL: %empty  */
        {

	}
    break;

  case 81: /* statement.gpOPTL: statement.gpPLUS  */
        {
	}
    break;

  case 82: /* statement.gpOPTL: %empty  */
        {
	}
    break;

  case 83: /* statement.gpPLUS: statement.gpPLUS statement.gp  */
        {

	}
    break;

  case 84: /* statement.gpPLUS: statement.gp  */
        {

	}
    break;

  case 85: /* path_selectorOPTL: path_selector  */
        {
          (yyval.PQExprPtrData)=(yyvsp[0].PQExprPtrData);
	}
    break;

  case 86: /* path_selectorOPTL: %empty  */
        {
          (yyval.PQExprPtrData)=0;
	}
    break;



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

