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
   especially those whose name start with YY_ or _DtCm_yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with _DtCm_yy or YY, to avoid
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
#line 2 "reparser.y"

/*
 *  (c) Copyright 1993, 1994 Hewlett-Packard Company
 *  (c) Copyright 1993, 1994 International Business Machines Corp.
 *  (c) Copyright 1993, 1994 Novell, Inc.
 *  (c) Copyright 1993, 1994 Sun Microsystems, Inc.
 */

#include <EUSCompat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "rerule.h"
#include "iso8601.h"

/* The parsed rule is stored in this structure */
RepeatEvent	*_DtCm_repeat_info;

extern int		 _DtCm_yylex(void);
extern void		 _DtCm_yyerror(char*);

static int CompareNums(const void *, const void *);
static int CompareDayTime(const void *, const void *);
static int CompareWeekDayTime(const void *, const void *);
static unsigned int *ConvertNumList(NumberList *, unsigned int * /* Return */);
static WeekDayTime *ConvertWeekDayTime(WeekDayTimeList *, unsigned int *);
static NumberList *AllocNumber(unsigned int);
static WeekDayTimeList *AllocWeekDayTimeList(NumberList*, NumberList *,
			NumberList *);
static RepeatEvent *HandleEndDate(RepeatEvent *, time_t);
static RepeatEvent *DeriveMinuteEvent(unsigned int, unsigned int);
static RepeatEvent *DeriveDailyEvent(unsigned int, NumberList *,
			unsigned int, RepeatEvent *);
static RepeatEvent *DeriveWeeklyEvent(unsigned int, DayTimeList *,
			unsigned int, RepeatEvent *);
static RepeatEvent *DeriveMonthlyEvent(RepeatType, unsigned int, void *,
			unsigned int, RepeatEvent *);
static RepeatEvent *DeriveYearlyEvent(RepeatType, unsigned int, NumberList *,
			unsigned int, RepeatEvent *);


#line 115 "y.tab.c"

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
extern int _DtCm_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum _DtCm_yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ERROR = 258,                   /* ERROR  */
    ENDMARKER = 259,               /* ENDMARKER  */
    DURATION = 260,                /* DURATION  */
    NUMBER = 261,                  /* NUMBER  */
    FIRSTWEEK = 262,               /* FIRSTWEEK  */
    SECONDWEEK = 263,              /* SECONDWEEK  */
    THIRDWEEK = 264,               /* THIRDWEEK  */
    FOURTHWEEK = 265,              /* FOURTHWEEK  */
    FIFTHWEEK = 266,               /* FIFTHWEEK  */
    LASTWEEK = 267,                /* LASTWEEK  */
    SECONDLAST = 268,              /* SECONDLAST  */
    THIRDLAST = 269,               /* THIRDLAST  */
    FOURTHLAST = 270,              /* FOURTHLAST  */
    FIFTHLAST = 271,               /* FIFTHLAST  */
    MINUTECOMMAND = 272,           /* MINUTECOMMAND  */
    DAILYCOMMAND = 273,            /* DAILYCOMMAND  */
    WEEKLYCOMMAND = 274,           /* WEEKLYCOMMAND  */
    MONTHPOSCOMMAND = 275,         /* MONTHPOSCOMMAND  */
    MONTHDAYCOMMAND = 276,         /* MONTHDAYCOMMAND  */
    YEARDAYCOMMAND = 277,          /* YEARDAYCOMMAND  */
    YEARMONTHCOMMAND = 278,        /* YEARMONTHCOMMAND  */
    LASTDAY = 279,                 /* LASTDAY  */
    SUNDAY = 280,                  /* SUNDAY  */
    MONDAY = 281,                  /* MONDAY  */
    TUESDAY = 282,                 /* TUESDAY  */
    WEDNESDAY = 283,               /* WEDNESDAY  */
    THURSDAY = 284,                /* THURSDAY  */
    FRIDAY = 285,                  /* FRIDAY  */
    SATURDAY = 286,                /* SATURDAY  */
    DATE = 287                     /* DATE  */
  };
  typedef enum _DtCm_yytokentype _DtCm_yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ERROR 258
#define ENDMARKER 259
#define DURATION 260
#define NUMBER 261
#define FIRSTWEEK 262
#define SECONDWEEK 263
#define THIRDWEEK 264
#define FOURTHWEEK 265
#define FIFTHWEEK 266
#define LASTWEEK 267
#define SECONDLAST 268
#define THIRDLAST 269
#define FOURTHLAST 270
#define FIFTHLAST 271
#define MINUTECOMMAND 272
#define DAILYCOMMAND 273
#define WEEKLYCOMMAND 274
#define MONTHPOSCOMMAND 275
#define MONTHDAYCOMMAND 276
#define YEARDAYCOMMAND 277
#define YEARMONTHCOMMAND 278
#define LASTDAY 279
#define SUNDAY 280
#define MONDAY 281
#define TUESDAY 282
#define WEDNESDAY 283
#define THURSDAY 284
#define FRIDAY 285
#define SATURDAY 286
#define DATE 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 52 "reparser.y"

		int		 number;
		RepeatEvent	*re;
		NumberList	*nl;
		WeekDay		 weekday;
		WeekNumber	 weeknum;
		DayTime		*dt;
		DayTimeList	*dtl;
		WeekDayTimeList	*wdtl;
		time_t		 enddate;
		char		 date[64];
	

#line 246 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE _DtCm_yylval;


int _DtCm_rule_parser (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum _DtCm_yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ERROR = 3,                      /* ERROR  */
  YYSYMBOL_ENDMARKER = 4,                  /* ENDMARKER  */
  YYSYMBOL_DURATION = 5,                   /* DURATION  */
  YYSYMBOL_NUMBER = 6,                     /* NUMBER  */
  YYSYMBOL_FIRSTWEEK = 7,                  /* FIRSTWEEK  */
  YYSYMBOL_SECONDWEEK = 8,                 /* SECONDWEEK  */
  YYSYMBOL_THIRDWEEK = 9,                  /* THIRDWEEK  */
  YYSYMBOL_FOURTHWEEK = 10,                /* FOURTHWEEK  */
  YYSYMBOL_FIFTHWEEK = 11,                 /* FIFTHWEEK  */
  YYSYMBOL_LASTWEEK = 12,                  /* LASTWEEK  */
  YYSYMBOL_SECONDLAST = 13,                /* SECONDLAST  */
  YYSYMBOL_THIRDLAST = 14,                 /* THIRDLAST  */
  YYSYMBOL_FOURTHLAST = 15,                /* FOURTHLAST  */
  YYSYMBOL_FIFTHLAST = 16,                 /* FIFTHLAST  */
  YYSYMBOL_MINUTECOMMAND = 17,             /* MINUTECOMMAND  */
  YYSYMBOL_DAILYCOMMAND = 18,              /* DAILYCOMMAND  */
  YYSYMBOL_WEEKLYCOMMAND = 19,             /* WEEKLYCOMMAND  */
  YYSYMBOL_MONTHPOSCOMMAND = 20,           /* MONTHPOSCOMMAND  */
  YYSYMBOL_MONTHDAYCOMMAND = 21,           /* MONTHDAYCOMMAND  */
  YYSYMBOL_YEARDAYCOMMAND = 22,            /* YEARDAYCOMMAND  */
  YYSYMBOL_YEARMONTHCOMMAND = 23,          /* YEARMONTHCOMMAND  */
  YYSYMBOL_LASTDAY = 24,                   /* LASTDAY  */
  YYSYMBOL_SUNDAY = 25,                    /* SUNDAY  */
  YYSYMBOL_MONDAY = 26,                    /* MONDAY  */
  YYSYMBOL_TUESDAY = 27,                   /* TUESDAY  */
  YYSYMBOL_WEDNESDAY = 28,                 /* WEDNESDAY  */
  YYSYMBOL_THURSDAY = 29,                  /* THURSDAY  */
  YYSYMBOL_FRIDAY = 30,                    /* FRIDAY  */
  YYSYMBOL_SATURDAY = 31,                  /* SATURDAY  */
  YYSYMBOL_DATE = 32,                      /* DATE  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_start = 34,                     /* start  */
  YYSYMBOL_begin = 35,                     /* begin  */
  YYSYMBOL_minuteEvent = 36,               /* minuteEvent  */
  YYSYMBOL_dailyEvent = 37,                /* dailyEvent  */
  YYSYMBOL_weeklyEvent = 38,               /* weeklyEvent  */
  YYSYMBOL_monthlyPosEvent = 39,           /* monthlyPosEvent  */
  YYSYMBOL_monthlyDayEvent = 40,           /* monthlyDayEvent  */
  YYSYMBOL_yearlyByMonth = 41,             /* yearlyByMonth  */
  YYSYMBOL_yearlyByDay = 42,               /* yearlyByDay  */
  YYSYMBOL_weekDayTime = 43,               /* weekDayTime  */
  YYSYMBOL_weekdayList = 44,               /* weekdayList  */
  YYSYMBOL_occurrenceList = 45,            /* occurrenceList  */
  YYSYMBOL_weekdayTimePair = 46,           /* weekdayTimePair  */
  YYSYMBOL_weekdayTimeList = 47,           /* weekdayTimeList  */
  YYSYMBOL_occurrence = 48,                /* occurrence  */
  YYSYMBOL_endDate = 49,                   /* endDate  */
  YYSYMBOL_weekday = 50,                   /* weekday  */
  YYSYMBOL_time0List = 51,                 /* time0List  */
  YYSYMBOL_time = 52,                      /* time  */
  YYSYMBOL_endMarker = 53,                 /* endMarker  */
  YYSYMBOL_duration = 54,                  /* duration  */
  YYSYMBOL_timeList = 55,                  /* timeList  */
  YYSYMBOL_dayOfMonthList = 56,            /* dayOfMonthList  */
  YYSYMBOL_monthOfYearList = 57,           /* monthOfYearList  */
  YYSYMBOL_dayOfYearList = 58,             /* dayOfYearList  */
  YYSYMBOL_generic0NumberList = 59,        /* generic0NumberList  */
  YYSYMBOL_genericNumberList = 60          /* genericNumberList  */
};
typedef enum _DtCm_yysymbol_kind_t _DtCm_yysymbol_kind_t;




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
typedef __INT_LEAST8_TYPE__ _DtCm_yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t _DtCm_yytype_int8;
#else
typedef signed char _DtCm_yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ _DtCm_yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t _DtCm_yytype_int16;
#else
typedef short _DtCm_yytype_int16;
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
typedef __UINT_LEAST8_TYPE__ _DtCm_yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t _DtCm_yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char _DtCm_yytype_uint8;
#else
typedef short _DtCm_yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ _DtCm_yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t _DtCm_yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short _DtCm_yytype_uint16;
#else
typedef int _DtCm_yytype_uint16;
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
typedef _DtCm_yytype_uint8 _DtCm_yy_state_t;

/* State numbers in computations.  */
typedef int _DtCm_yy_state_fast_t;

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

/* Suppress an incorrect diagnostic about _DtCm_yylval being uninitialized.  */
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

#if !defined _DtCm_yyoverflow

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
#endif /* !defined _DtCm_yyoverflow */

#if (! defined _DtCm_yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union _DtCm_yyalloc
{
  _DtCm_yy_state_t _DtCm_yyss_alloc;
  YYSTYPE _DtCm_yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union _DtCm_yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (_DtCm_yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T _DtCm_yynewbytes;                                         \
        YYCOPY (&_DtCm_yyptr->Stack_alloc, Stack, _DtCm_yysize);                    \
        Stack = &_DtCm_yyptr->Stack_alloc;                                    \
        _DtCm_yynewbytes = _DtCm_yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        _DtCm_yyptr += _DtCm_yynewbytes / YYSIZEOF (*_DtCm_yyptr);                        \
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
          YYPTRDIFF_T _DtCm_yyi;                      \
          for (_DtCm_yyi = 0; _DtCm_yyi < (Count); _DtCm_yyi++)   \
            (Dst)[_DtCm_yyi] = (Src)[_DtCm_yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by _DtCm_yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (_DtCm_yysymbol_kind_t, _DtCm_yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by _DtCm_yylex.  */
static const _DtCm_yytype_int8 _DtCm_yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const _DtCm_yytype_int16 _DtCm_yyrline[] =
{
       0,    81,    81,    85,    96,   100,   104,   108,   112,   116,
     120,   127,   130,   141,   149,   154,   162,   168,   174,   182,
     187,   192,   199,   204,   209,   214,   220,   228,   233,   238,
     243,   248,   257,   260,   273,   289,   293,   309,   313,   329,
     345,   357,   386,   391,   396,   401,   406,   411,   416,   421,
     426,   431,   439,   442,   450,   455,   460,   465,   470,   475,
     480,   489,   492,   508,   519,   522,   530,   536,   546,   547,
     548,   549,   552,   555,   561,   568,   577,   593
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (_DtCm_yysymbol_kind_t, _DtCm_yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *_DtCm_yysymbol_name (_DtCm_yysymbol_kind_t _DtCm_yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const _DtCm_yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ERROR", "ENDMARKER",
  "DURATION", "NUMBER", "FIRSTWEEK", "SECONDWEEK", "THIRDWEEK",
  "FOURTHWEEK", "FIFTHWEEK", "LASTWEEK", "SECONDLAST", "THIRDLAST",
  "FOURTHLAST", "FIFTHLAST", "MINUTECOMMAND", "DAILYCOMMAND",
  "WEEKLYCOMMAND", "MONTHPOSCOMMAND", "MONTHDAYCOMMAND", "YEARDAYCOMMAND",
  "YEARMONTHCOMMAND", "LASTDAY", "SUNDAY", "MONDAY", "TUESDAY",
  "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "DATE", "$accept",
  "start", "begin", "minuteEvent", "dailyEvent", "weeklyEvent",
  "monthlyPosEvent", "monthlyDayEvent", "yearlyByMonth", "yearlyByDay",
  "weekDayTime", "weekdayList", "occurrenceList", "weekdayTimePair",
  "weekdayTimeList", "occurrence", "endDate", "weekday", "time0List",
  "time", "endMarker", "duration", "timeList", "dayOfMonthList",
  "monthOfYearList", "dayOfYearList", "generic0NumberList",
  "genericNumberList", YY_NULLPTR
};

static const char *
_DtCm_yysymbol_name (_DtCm_yysymbol_kind_t _DtCm_yysymbol)
{
  return _DtCm_yytname[_DtCm_yysymbol];
}
#endif

#define YYPACT_NINF (-80)

#define _DtCm_yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-12)

#define _DtCm_yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const _DtCm_yytype_int8 _DtCm_yypact[] =
{
      62,   -80,     9,    12,    14,    42,    64,    66,    67,    68,
     -80,    43,    43,    43,    43,    43,    43,    43,    71,   -80,
      61,   -80,    11,    11,    11,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,    87,   -80,     3,   107,   107,   107,
     107,   107,   107,   107,   -80,    61,   -80,    95,   115,   107,
     107,    71,   -80,    41,    71,   -80,    71,   -80,   -80,   107,
     -80,    95,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,    95,   126,   -80,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,    88,   -80,   121,   -80,   -80,   121,
     107,   107,   116,   116,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
      41
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const _DtCm_yytype_int8 _DtCm_yydefact[] =
{
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       2,    52,    52,    52,    52,    52,    52,    52,    66,    61,
      66,    32,    72,    72,    72,     1,    53,     4,     5,     6,
       7,     8,     9,    10,     0,    12,    66,    64,    64,    64,
      64,    64,    64,    64,    40,    66,    61,    11,    66,    64,
      64,    66,    69,    73,    66,    71,    66,    70,    67,    64,
      62,    11,    65,    54,    55,    56,    57,    58,    59,    60,
      41,    11,    39,    15,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,     0,    37,    11,    74,    75,    11,
      64,    64,    11,    11,    63,    13,    14,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    33,    38,    35,
      16,    17,    18,    19,    20,    21,    76,    77,    27,    28,
      29,    30,    31,    22,    23,    24,    25,    26,    36,    34,
      68
};

/* YYPGOTO[NTERM-NUM].  */
static const _DtCm_yytype_int8 _DtCm_yypgoto[] =
{
     -80,   -80,   -80,   -15,   -79,   -70,   -42,   -33,   -80,   -80,
     -80,   -80,   -80,    76,   -80,    57,    93,   -50,    96,   -80,
     -38,    13,   -80,   -80,   -80,   -80,    31,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const _DtCm_yytype_uint8 _DtCm_yydefgoto[] =
{
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      48,   107,    84,    44,    45,    85,    27,    46,    36,    60,
      63,    35,   129,    51,    56,    54,    52,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const _DtCm_yytype_int16 _DtCm_yytable[] =
{
      64,    65,    66,    67,    68,    69,    49,   111,    34,    59,
     114,    87,    88,   119,   124,    18,   112,    49,    19,   115,
      20,    94,   120,   125,    50,    37,    38,    39,    40,    41,
      42,    43,    73,    47,   109,    50,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,    95,    90,    21,    61,
     121,   126,   116,   117,    55,    57,    96,   128,    71,   122,
     127,    86,   -11,     1,    89,    91,    34,    92,    25,    93,
      22,   110,    23,    24,   113,    26,    34,   118,   123,     2,
       3,     4,     5,     6,     7,     8,    37,    38,    39,    40,
      41,    42,    43,    58,   -11,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    28,    29,    30,    31,    32,
      33,    62,     2,    37,    38,    39,    40,    41,    42,    43,
      34,    70,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    59,     2,     3,     4,     5,     6,     2,     3,
       4,   108,    72,   130
};

static const _DtCm_yytype_int8 _DtCm_yycheck[] =
{
      38,    39,    40,    41,    42,    43,     6,    86,     5,     6,
      89,    49,    50,    92,    93,     6,    86,     6,     6,    89,
       6,    59,    92,    93,    24,    25,    26,    27,    28,    29,
      30,    31,    47,    20,    84,    24,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    61,     6,     6,    36,
      92,    93,    90,    91,    23,    24,    71,   107,    45,    92,
      93,    48,     0,     1,    51,    24,     5,    54,     0,    56,
       6,    86,     6,     6,    89,    32,     5,    92,    93,    17,
      18,    19,    20,    21,    22,    23,    25,    26,    27,    28,
      29,    30,    31,     6,    32,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    12,    13,    14,    15,    16,
      17,     4,    17,    25,    26,    27,    28,    29,    30,    31,
       5,    45,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,     6,    17,    18,    19,    20,    21,    17,    18,
      19,    84,    46,   107
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const _DtCm_yytype_int8 _DtCm_yystos[] =
{
       0,     1,    17,    18,    19,    20,    21,    22,    23,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     6,     6,
       6,     6,     6,     6,     6,     0,    32,    49,    49,    49,
      49,    49,    49,    49,     5,    54,    51,    25,    26,    27,
      28,    29,    30,    31,    46,    47,    50,    54,    43,     6,
      24,    56,    59,    60,    58,    59,    57,    59,     6,     6,
      52,    54,     4,    53,    53,    53,    53,    53,    53,    53,
      46,    54,    51,    36,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    45,    48,    54,    53,    53,    54,
       6,    24,    54,    54,    53,    36,    36,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    44,    48,    50,
      36,    37,    38,    36,    37,    38,    53,    53,    36,    37,
      38,    39,    40,    36,    37,    38,    39,    40,    50,    55,
      60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const _DtCm_yytype_int8 _DtCm_yyr1[] =
{
       0,    33,    34,    34,    35,    35,    35,    35,    35,    35,
      35,    36,    36,    37,    38,    38,    39,    39,    39,    40,
      40,    40,    41,    41,    41,    41,    41,    42,    42,    42,
      42,    42,    43,    43,    43,    44,    44,    45,    45,    46,
      47,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    52,    53,    53,    54,    54,    55,    56,
      57,    58,    59,    59,    60,    60,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const _DtCm_yytype_int8 _DtCm_yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     0,     3,     5,     5,     4,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     0,     3,     4,     1,     2,     1,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     0,     1,     2,     2,     2,     2,     2,     2,
       2,     0,     2,     2,     0,     1,     0,     2,     1,     1,
       1,     1,     0,     1,     2,     2,     3,     3
};


enum { YYENOMEM = -2 };

#define _DtCm_yyerrok         (_DtCm_yyerrstatus = 0)
#define _DtCm_yyclearin       (_DtCm_yychar = YYEMPTY)

#define YYACCEPT        goto _DtCm_yyacceptlab
#define YYABORT         goto _DtCm_yyabortlab
#define YYERROR         goto _DtCm_yyerrorlab
#define YYNOMEM         goto _DtCm_yyexhaustedlab


#define YYRECOVERING()  (!!_DtCm_yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (_DtCm_yychar == YYEMPTY)                                        \
      {                                                           \
        _DtCm_yychar = (Token);                                         \
        _DtCm_yylval = (Value);                                         \
        YYPOPSTACK (_DtCm_yylen);                                       \
        _DtCm_yystate = *_DtCm_yyssp;                                         \
        goto _DtCm_yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        _DtCm_yyerror (YY_("syntax error: cannot back up")); \
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
  if (_DtCm_yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (_DtCm_yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      _DtCm_yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
_DtCm_yy_symbol_value_print (FILE *_DtCm_yyo,
                       _DtCm_yysymbol_kind_t _DtCm_yykind, YYSTYPE const * const _DtCm_yyvaluep)
{
  FILE *_DtCm_yyoutput = _DtCm_yyo;
  YY_USE (_DtCm_yyoutput);
  if (!_DtCm_yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (_DtCm_yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
_DtCm_yy_symbol_print (FILE *_DtCm_yyo,
                 _DtCm_yysymbol_kind_t _DtCm_yykind, YYSTYPE const * const _DtCm_yyvaluep)
{
  YYFPRINTF (_DtCm_yyo, "%s %s (",
             _DtCm_yykind < YYNTOKENS ? "token" : "nterm", _DtCm_yysymbol_name (_DtCm_yykind));

  _DtCm_yy_symbol_value_print (_DtCm_yyo, _DtCm_yykind, _DtCm_yyvaluep);
  YYFPRINTF (_DtCm_yyo, ")");
}

/*------------------------------------------------------------------.
| _DtCm_yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
_DtCm_yy_stack_print (_DtCm_yy_state_t *_DtCm_yybottom, _DtCm_yy_state_t *_DtCm_yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; _DtCm_yybottom <= _DtCm_yytop; _DtCm_yybottom++)
    {
      int _DtCm_yybot = *_DtCm_yybottom;
      YYFPRINTF (stderr, " %d", _DtCm_yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (_DtCm_yydebug)                                                  \
    _DtCm_yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
_DtCm_yy_reduce_print (_DtCm_yy_state_t *_DtCm_yyssp, YYSTYPE *_DtCm_yyvsp,
                 int _DtCm_yyrule)
{
  int _DtCm_yylno = _DtCm_yyrline[_DtCm_yyrule];
  int _DtCm_yynrhs = _DtCm_yyr2[_DtCm_yyrule];
  int _DtCm_yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             _DtCm_yyrule - 1, _DtCm_yylno);
  /* The symbols being reduced.  */
  for (_DtCm_yyi = 0; _DtCm_yyi < _DtCm_yynrhs; _DtCm_yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", _DtCm_yyi + 1);
      _DtCm_yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+_DtCm_yyssp[_DtCm_yyi + 1 - _DtCm_yynrhs]),
                       &_DtCm_yyvsp[(_DtCm_yyi + 1) - (_DtCm_yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (_DtCm_yydebug)                          \
    _DtCm_yy_reduce_print (_DtCm_yyssp, _DtCm_yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int _DtCm_yydebug;
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
_DtCm_yydestruct (const char *_DtCm_yymsg,
            _DtCm_yysymbol_kind_t _DtCm_yykind, YYSTYPE *_DtCm_yyvaluep)
{
  YY_USE (_DtCm_yyvaluep);
  if (!_DtCm_yymsg)
    _DtCm_yymsg = "Deleting";
  YY_SYMBOL_PRINT (_DtCm_yymsg, _DtCm_yykind, _DtCm_yyvaluep, _DtCm_yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (_DtCm_yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int _DtCm_yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE _DtCm_yylval;
/* Number of syntax errors so far.  */
int _DtCm_yynerrs;




/*----------.
| _DtCm_rule_parser.  |
`----------*/

int
_DtCm_rule_parser (void)
{
    _DtCm_yy_state_fast_t _DtCm_yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int _DtCm_yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow _DtCm_yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T _DtCm_yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    _DtCm_yy_state_t _DtCm_yyssa[YYINITDEPTH];
    _DtCm_yy_state_t *_DtCm_yyss = _DtCm_yyssa;
    _DtCm_yy_state_t *_DtCm_yyssp = _DtCm_yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE _DtCm_yyvsa[YYINITDEPTH];
    YYSTYPE *_DtCm_yyvs = _DtCm_yyvsa;
    YYSTYPE *_DtCm_yyvsp = _DtCm_yyvs;

  int _DtCm_yyn;
  /* The return value of _DtCm_rule_parser.  */
  int _DtCm_yyresult;
  /* Lookahead symbol kind.  */
  _DtCm_yysymbol_kind_t _DtCm_yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE _DtCm_yyval;



#define YYPOPSTACK(N)   (_DtCm_yyvsp -= (N), _DtCm_yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int _DtCm_yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  _DtCm_yychar = YYEMPTY; /* Cause a token to be read.  */

  goto _DtCm_yysetstate;


/*------------------------------------------------------------.
| _DtCm_yynewstate -- push a new state, which is found in _DtCm_yystate.  |
`------------------------------------------------------------*/
_DtCm_yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  _DtCm_yyssp++;


/*--------------------------------------------------------------------.
| _DtCm_yysetstate -- set current state (the top of the stack) to _DtCm_yystate.  |
`--------------------------------------------------------------------*/
_DtCm_yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", _DtCm_yystate));
  YY_ASSERT (0 <= _DtCm_yystate && _DtCm_yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *_DtCm_yyssp = YY_CAST (_DtCm_yy_state_t, _DtCm_yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (_DtCm_yyss, _DtCm_yyssp);

  if (_DtCm_yyss + _DtCm_yystacksize - 1 <= _DtCm_yyssp)
#if !defined _DtCm_yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T _DtCm_yysize = _DtCm_yyssp - _DtCm_yyss + 1;

# if defined _DtCm_yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        _DtCm_yy_state_t *_DtCm_yyss1 = _DtCm_yyss;
        YYSTYPE *_DtCm_yyvs1 = _DtCm_yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if _DtCm_yyoverflow is a macro.  */
        _DtCm_yyoverflow (YY_("memory exhausted"),
                    &_DtCm_yyss1, _DtCm_yysize * YYSIZEOF (*_DtCm_yyssp),
                    &_DtCm_yyvs1, _DtCm_yysize * YYSIZEOF (*_DtCm_yyvsp),
                    &_DtCm_yystacksize);
        _DtCm_yyss = _DtCm_yyss1;
        _DtCm_yyvs = _DtCm_yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= _DtCm_yystacksize)
        YYNOMEM;
      _DtCm_yystacksize *= 2;
      if (YYMAXDEPTH < _DtCm_yystacksize)
        _DtCm_yystacksize = YYMAXDEPTH;

      {
        _DtCm_yy_state_t *_DtCm_yyss1 = _DtCm_yyss;
        union _DtCm_yyalloc *_DtCm_yyptr =
          YY_CAST (union _DtCm_yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (_DtCm_yystacksize))));
        if (! _DtCm_yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (_DtCm_yyss_alloc, _DtCm_yyss);
        YYSTACK_RELOCATE (_DtCm_yyvs_alloc, _DtCm_yyvs);
#  undef YYSTACK_RELOCATE
        if (_DtCm_yyss1 != _DtCm_yyssa)
          YYSTACK_FREE (_DtCm_yyss1);
      }
# endif

      _DtCm_yyssp = _DtCm_yyss + _DtCm_yysize - 1;
      _DtCm_yyvsp = _DtCm_yyvs + _DtCm_yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, _DtCm_yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (_DtCm_yyss + _DtCm_yystacksize - 1 <= _DtCm_yyssp)
        YYABORT;
    }
#endif /* !defined _DtCm_yyoverflow && !defined YYSTACK_RELOCATE */


  if (_DtCm_yystate == YYFINAL)
    YYACCEPT;

  goto _DtCm_yybackup;


/*-----------.
| _DtCm_yybackup.  |
`-----------*/
_DtCm_yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  _DtCm_yyn = _DtCm_yypact[_DtCm_yystate];
  if (_DtCm_yypact_value_is_default (_DtCm_yyn))
    goto _DtCm_yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (_DtCm_yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      _DtCm_yychar = _DtCm_yylex ();
    }

  if (_DtCm_yychar <= YYEOF)
    {
      _DtCm_yychar = YYEOF;
      _DtCm_yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (_DtCm_yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      _DtCm_yychar = YYUNDEF;
      _DtCm_yytoken = YYSYMBOL_YYerror;
      goto _DtCm_yyerrlab1;
    }
  else
    {
      _DtCm_yytoken = YYTRANSLATE (_DtCm_yychar);
      YY_SYMBOL_PRINT ("Next token is", _DtCm_yytoken, &_DtCm_yylval, &_DtCm_yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  _DtCm_yyn += _DtCm_yytoken;
  if (_DtCm_yyn < 0 || YYLAST < _DtCm_yyn || _DtCm_yycheck[_DtCm_yyn] != _DtCm_yytoken)
    goto _DtCm_yydefault;
  _DtCm_yyn = _DtCm_yytable[_DtCm_yyn];
  if (_DtCm_yyn <= 0)
    {
      if (_DtCm_yytable_value_is_error (_DtCm_yyn))
        goto _DtCm_yyerrlab;
      _DtCm_yyn = -_DtCm_yyn;
      goto _DtCm_yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (_DtCm_yyerrstatus)
    _DtCm_yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", _DtCm_yytoken, &_DtCm_yylval, &_DtCm_yylloc);
  _DtCm_yystate = _DtCm_yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++_DtCm_yyvsp = _DtCm_yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  _DtCm_yychar = YYEMPTY;
  goto _DtCm_yynewstate;


/*-----------------------------------------------------------.
| _DtCm_yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
_DtCm_yydefault:
  _DtCm_yyn = _DtCm_yydefact[_DtCm_yystate];
  if (_DtCm_yyn == 0)
    goto _DtCm_yyerrlab;
  goto _DtCm_yyreduce;


/*-----------------------------.
| _DtCm_yyreduce -- do a reduction.  |
`-----------------------------*/
_DtCm_yyreduce:
  /* _DtCm_yyn is the number of a rule to reduce with.  */
  _DtCm_yylen = _DtCm_yyr2[_DtCm_yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  _DtCm_yyval = _DtCm_yyvsp[1-_DtCm_yylen];


  YY_REDUCE_PRINT (_DtCm_yyn);
  switch (_DtCm_yyn)
    {
  case 2: /* start: begin  */
#line 82 "reparser.y"
                    {
			_DtCm_repeat_info = (_DtCm_yyval.re);
		    }
#line 1380 "y.tab.c"
    break;

  case 3: /* start: error  */
#line 86 "reparser.y"
                    {
			/*
			 * XXX: Memory leak: We need to free up any portion
			 * of the re struct that has be allocated before the
			 * error was encountered.
			 */
			_DtCm_repeat_info = NULL;
		    }
#line 1393 "y.tab.c"
    break;

  case 4: /* begin: minuteEvent endDate  */
#line 97 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1401 "y.tab.c"
    break;

  case 5: /* begin: dailyEvent endDate  */
#line 101 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1409 "y.tab.c"
    break;

  case 6: /* begin: weeklyEvent endDate  */
#line 105 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1417 "y.tab.c"
    break;

  case 7: /* begin: monthlyPosEvent endDate  */
#line 109 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1425 "y.tab.c"
    break;

  case 8: /* begin: monthlyDayEvent endDate  */
#line 113 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1433 "y.tab.c"
    break;

  case 9: /* begin: yearlyByMonth endDate  */
#line 117 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1441 "y.tab.c"
    break;

  case 10: /* begin: yearlyByDay endDate  */
#line 121 "reparser.y"
                    {
			(_DtCm_yyval.re) = HandleEndDate((_DtCm_yyvsp[-1].re), (_DtCm_yyvsp[0].enddate));
		    }
#line 1449 "y.tab.c"
    break;

  case 11: /* minuteEvent: %empty  */
#line 127 "reparser.y"
                    {
			(_DtCm_yyval.re) = NULL;
		    }
#line 1457 "y.tab.c"
    break;

  case 12: /* minuteEvent: MINUTECOMMAND NUMBER duration  */
#line 131 "reparser.y"
                    {
#ifdef MINUTE
			(_DtCm_yyval.re) = DeriveMinuteEvent((_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].number));
#else
			(_DtCm_yyval.re) = NULL;
#endif /* MINUTE */
	  	    }
#line 1469 "y.tab.c"
    break;

  case 13: /* dailyEvent: DAILYCOMMAND NUMBER time0List duration minuteEvent  */
#line 142 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveDailyEvent((_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1478 "y.tab.c"
    break;

  case 14: /* weeklyEvent: WEEKLYCOMMAND NUMBER weekdayTimeList duration minuteEvent  */
#line 150 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveWeeklyEvent((_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].dtl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1487 "y.tab.c"
    break;

  case 15: /* weeklyEvent: WEEKLYCOMMAND NUMBER duration minuteEvent  */
#line 155 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveWeeklyEvent((_DtCm_yyvsp[-2].number), NULL, (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1496 "y.tab.c"
    break;

  case 16: /* monthlyPosEvent: MONTHPOSCOMMAND NUMBER weekDayTime duration minuteEvent  */
#line 163 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveMonthlyEvent(RT_MONTHLY_POSITION,
						(_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].wdtl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1506 "y.tab.c"
    break;

  case 17: /* monthlyPosEvent: MONTHPOSCOMMAND NUMBER weekDayTime duration dailyEvent  */
#line 169 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveMonthlyEvent(RT_MONTHLY_POSITION,
						(_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].wdtl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1516 "y.tab.c"
    break;

  case 18: /* monthlyPosEvent: MONTHPOSCOMMAND NUMBER weekDayTime duration weeklyEvent  */
#line 175 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveMonthlyEvent(RT_MONTHLY_POSITION,
						(_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].wdtl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1526 "y.tab.c"
    break;

  case 19: /* monthlyDayEvent: MONTHDAYCOMMAND NUMBER dayOfMonthList duration minuteEvent  */
#line 183 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveMonthlyEvent(RT_MONTHLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1535 "y.tab.c"
    break;

  case 20: /* monthlyDayEvent: MONTHDAYCOMMAND NUMBER dayOfMonthList duration dailyEvent  */
#line 188 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveMonthlyEvent(RT_MONTHLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1544 "y.tab.c"
    break;

  case 21: /* monthlyDayEvent: MONTHDAYCOMMAND NUMBER dayOfMonthList duration weeklyEvent  */
#line 193 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveMonthlyEvent(RT_MONTHLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1553 "y.tab.c"
    break;

  case 22: /* yearlyByMonth: YEARMONTHCOMMAND NUMBER monthOfYearList duration minuteEvent  */
#line 200 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_MONTH, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1562 "y.tab.c"
    break;

  case 23: /* yearlyByMonth: YEARMONTHCOMMAND NUMBER monthOfYearList duration dailyEvent  */
#line 205 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_MONTH, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1571 "y.tab.c"
    break;

  case 24: /* yearlyByMonth: YEARMONTHCOMMAND NUMBER monthOfYearList duration weeklyEvent  */
#line 210 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_MONTH, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1580 "y.tab.c"
    break;

  case 25: /* yearlyByMonth: YEARMONTHCOMMAND NUMBER monthOfYearList duration monthlyPosEvent  */
#line 216 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_MONTH, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1589 "y.tab.c"
    break;

  case 26: /* yearlyByMonth: YEARMONTHCOMMAND NUMBER monthOfYearList duration monthlyDayEvent  */
#line 222 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_MONTH, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1598 "y.tab.c"
    break;

  case 27: /* yearlyByDay: YEARDAYCOMMAND NUMBER dayOfYearList duration minuteEvent  */
#line 229 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1607 "y.tab.c"
    break;

  case 28: /* yearlyByDay: YEARDAYCOMMAND NUMBER dayOfYearList duration dailyEvent  */
#line 234 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1616 "y.tab.c"
    break;

  case 29: /* yearlyByDay: YEARDAYCOMMAND NUMBER dayOfYearList duration weeklyEvent  */
#line 239 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1625 "y.tab.c"
    break;

  case 30: /* yearlyByDay: YEARDAYCOMMAND NUMBER dayOfYearList duration monthlyPosEvent  */
#line 244 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1634 "y.tab.c"
    break;

  case 31: /* yearlyByDay: YEARDAYCOMMAND NUMBER dayOfYearList duration monthlyDayEvent  */
#line 249 "reparser.y"
                    {
			(_DtCm_yyval.re) = DeriveYearlyEvent(RT_YEARLY_DAY, (_DtCm_yyvsp[-3].number), (_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].number), (_DtCm_yyvsp[0].re));
			if ((_DtCm_yyvsp[0].re)) (_DtCm_yyval.re) = NULL;
		    }
#line 1643 "y.tab.c"
    break;

  case 32: /* weekDayTime: %empty  */
#line 257 "reparser.y"
                    {
			(_DtCm_yyval.wdtl) = NULL;
		    }
#line 1651 "y.tab.c"
    break;

  case 33: /* weekDayTime: weekDayTime occurrenceList weekdayList  */
#line 261 "reparser.y"
                    {
			WeekDayTimeList	*wdtl;

			wdtl = AllocWeekDayTimeList((_DtCm_yyvsp[-1].nl), (_DtCm_yyvsp[0].nl), NULL);

			if ((_DtCm_yyvsp[-2].wdtl) == NULL) {
				(_DtCm_yyval.wdtl) = wdtl;
			} else {
				wdtl->wdtl_next = (_DtCm_yyval.wdtl)->wdtl_next;
				(_DtCm_yyval.wdtl)->wdtl_next = wdtl;
			}
		    }
#line 1668 "y.tab.c"
    break;

  case 34: /* weekDayTime: weekDayTime occurrenceList weekdayList timeList  */
#line 274 "reparser.y"
                    {
			WeekDayTimeList	*wdtl;

			wdtl = AllocWeekDayTimeList((_DtCm_yyvsp[-2].nl), (_DtCm_yyvsp[-1].nl), (_DtCm_yyvsp[0].nl));

			if ((_DtCm_yyvsp[-3].wdtl) == NULL) {
				(_DtCm_yyval.wdtl) = wdtl;
			} else {
				wdtl->wdtl_next = (_DtCm_yyval.wdtl)->wdtl_next;
				(_DtCm_yyval.wdtl)->wdtl_next = wdtl;
			}
		    }
#line 1685 "y.tab.c"
    break;

  case 35: /* weekdayList: weekday  */
#line 290 "reparser.y"
                    {
			(_DtCm_yyval.nl) = AllocNumber((_DtCm_yyvsp[0].weekday));
		    }
#line 1693 "y.tab.c"
    break;

  case 36: /* weekdayList: weekdayList weekday  */
#line 294 "reparser.y"
                    {
			NumberList	*nl;

			nl = AllocNumber((_DtCm_yyvsp[0].weekday));

			if ((_DtCm_yyvsp[-1].nl) == NULL) {
				(_DtCm_yyval.nl) = nl;
			} else {
				nl->nl_next = (_DtCm_yyval.nl)->nl_next;
				(_DtCm_yyval.nl)->nl_next = nl;
			}
		    }
#line 1710 "y.tab.c"
    break;

  case 37: /* occurrenceList: occurrence  */
#line 310 "reparser.y"
                    {
			(_DtCm_yyval.nl) = AllocNumber((_DtCm_yyvsp[0].number));
		    }
#line 1718 "y.tab.c"
    break;

  case 38: /* occurrenceList: occurrenceList occurrence  */
#line 314 "reparser.y"
                    {
			NumberList	*nl;

			nl = AllocNumber((_DtCm_yyvsp[0].number));

			if ((_DtCm_yyvsp[-1].nl) == NULL) {
				(_DtCm_yyval.nl) = nl;
			} else {
				nl->nl_next = (_DtCm_yyval.nl)->nl_next;
				(_DtCm_yyval.nl)->nl_next = nl;
			}
		   }
#line 1735 "y.tab.c"
    break;

  case 39: /* weekdayTimePair: weekday time0List  */
#line 330 "reparser.y"
                    {
			DayTime		*dt;

			dt = (DayTime *)calloc(1, sizeof(DayTime));

			dt->dt_day = (_DtCm_yyvsp[-1].weekday);
				/* Convert from list to array, sort */

			dt->dt_time =
				(Time *)ConvertNumList((_DtCm_yyvsp[0].nl), &(dt->dt_ntime));
			(_DtCm_yyval.dt) = dt;
		    }
#line 1752 "y.tab.c"
    break;

  case 40: /* weekdayTimeList: weekdayTimePair  */
#line 346 "reparser.y"
                    {
			DayTimeList	*dtl;

			dtl = (DayTimeList *)calloc(1, sizeof(DayTimeList));

			dtl->dtl_daytime = (_DtCm_yyvsp[0].dt);
			dtl->dtl_next = NULL;

			(_DtCm_yyval.dtl) = dtl;

		    }
#line 1768 "y.tab.c"
    break;

  case 41: /* weekdayTimeList: weekdayTimeList weekdayTimePair  */
#line 358 "reparser.y"
                    {
			DayTimeList	*dtl,
					*dtl_end;

			dtl = (DayTimeList *)calloc(1, sizeof(DayTimeList));

			dtl->dtl_daytime = (_DtCm_yyvsp[0].dt);
			dtl->dtl_next = NULL;

			if ((_DtCm_yyvsp[-1].dtl) == NULL) {
				(_DtCm_yyval.dtl) = dtl;
			} else {
				/* Insert the new entry at the end.  This is
				 * so that MO TU 200 300 TH will maintain the
				 * same order in the list since MO uses the
				 * times next to TU and TH is dependent on the
				 * appt time.
				 */
				dtl_end = (_DtCm_yyval.dtl);
				while (dtl_end->dtl_next)
					dtl_end = dtl_end->dtl_next;
				
				dtl_end->dtl_next = dtl;
			}
		   }
#line 1798 "y.tab.c"
    break;

  case 42: /* occurrence: FIRSTWEEK endMarker  */
#line 387 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_F1;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1807 "y.tab.c"
    break;

  case 43: /* occurrence: SECONDWEEK endMarker  */
#line 392 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_F2;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1816 "y.tab.c"
    break;

  case 44: /* occurrence: THIRDWEEK endMarker  */
#line 397 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_F3;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1825 "y.tab.c"
    break;

  case 45: /* occurrence: FOURTHWEEK endMarker  */
#line 402 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_F4;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1834 "y.tab.c"
    break;

  case 46: /* occurrence: FIFTHWEEK endMarker  */
#line 407 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_F5;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1843 "y.tab.c"
    break;

  case 47: /* occurrence: LASTWEEK endMarker  */
#line 412 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_L1;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1852 "y.tab.c"
    break;

  case 48: /* occurrence: SECONDLAST endMarker  */
#line 417 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_L2;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1861 "y.tab.c"
    break;

  case 49: /* occurrence: THIRDLAST endMarker  */
#line 422 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_L3;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1870 "y.tab.c"
    break;

  case 50: /* occurrence: FOURTHLAST endMarker  */
#line 427 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_L4;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1879 "y.tab.c"
    break;

  case 51: /* occurrence: FIFTHLAST endMarker  */
#line 432 "reparser.y"
                    {
			(_DtCm_yyval.number) = WK_L5;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.number));
		    }
#line 1888 "y.tab.c"
    break;

  case 52: /* endDate: %empty  */
#line 439 "reparser.y"
                    {
			(_DtCm_yyval.enddate) = '\0';
		    }
#line 1896 "y.tab.c"
    break;

  case 53: /* endDate: DATE  */
#line 443 "reparser.y"
                    {
			if (_csa_iso8601_to_tick((_DtCm_yyvsp[0].date), &(_DtCm_yyval.enddate)) == -1)
				(_DtCm_yyval.enddate) = '\0';
		    }
#line 1905 "y.tab.c"
    break;

  case 54: /* weekday: SUNDAY endMarker  */
#line 451 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_SUN;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1914 "y.tab.c"
    break;

  case 55: /* weekday: MONDAY endMarker  */
#line 456 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_MON;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1923 "y.tab.c"
    break;

  case 56: /* weekday: TUESDAY endMarker  */
#line 461 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_TUE;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1932 "y.tab.c"
    break;

  case 57: /* weekday: WEDNESDAY endMarker  */
#line 466 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_WED;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1941 "y.tab.c"
    break;

  case 58: /* weekday: THURSDAY endMarker  */
#line 471 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_THU;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1950 "y.tab.c"
    break;

  case 59: /* weekday: FRIDAY endMarker  */
#line 476 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_FRI;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1959 "y.tab.c"
    break;

  case 60: /* weekday: SATURDAY endMarker  */
#line 481 "reparser.y"
                    {
			(_DtCm_yyval.weekday) = WD_SAT;
			if ((_DtCm_yyvsp[0].number)) RE_SET_FLAG((_DtCm_yyval.weekday));
		    }
#line 1968 "y.tab.c"
    break;

  case 61: /* time0List: %empty  */
#line 489 "reparser.y"
                   {
			(_DtCm_yyval.nl) = NULL;
		   }
#line 1976 "y.tab.c"
    break;

  case 62: /* time0List: time0List time  */
#line 493 "reparser.y"
                   {
			NumberList	*nl;

			nl = AllocNumber((_DtCm_yyvsp[0].number));

			if ((_DtCm_yyvsp[-1].nl) == NULL) {
				(_DtCm_yyval.nl) = nl;
			} else {
				nl->nl_next = (_DtCm_yyval.nl)->nl_next;
				(_DtCm_yyval.nl)->nl_next = nl;
			}
		   }
#line 1993 "y.tab.c"
    break;

  case 63: /* time: NUMBER endMarker  */
#line 509 "reparser.y"
                    {
			if ((_DtCm_yyvsp[0].number))
				RE_SET_FLAG((_DtCm_yyvsp[-1].number));
			(_DtCm_yyval.number) = (_DtCm_yyvsp[-1].number);
		    }
#line 2003 "y.tab.c"
    break;

  case 64: /* endMarker: %empty  */
#line 519 "reparser.y"
                    {
			(_DtCm_yyval.number) = FALSE;
		    }
#line 2011 "y.tab.c"
    break;

  case 65: /* endMarker: ENDMARKER  */
#line 523 "reparser.y"
                    {
			(_DtCm_yyval.number) = TRUE;
		    }
#line 2019 "y.tab.c"
    break;

  case 66: /* duration: %empty  */
#line 530 "reparser.y"
                    {
			/* If no duration then default to 2 - set later if 
			 * end date not used.
			 */
			(_DtCm_yyval.number) = RE_NOTSET;
		    }
#line 2030 "y.tab.c"
    break;

  case 67: /* duration: DURATION NUMBER  */
#line 537 "reparser.y"
                    {
			/* If duration == 0 then repeat forever */
			if ((_DtCm_yyvsp[0].number) == 0)
				(_DtCm_yyval.number) = RE_INFINITY; 
			else
				(_DtCm_yyval.number) = (_DtCm_yyvsp[0].number);
		    }
#line 2042 "y.tab.c"
    break;

  case 72: /* generic0NumberList: %empty  */
#line 552 "reparser.y"
                    {
			(_DtCm_yyval.nl) = NULL;
		    }
#line 2050 "y.tab.c"
    break;

  case 73: /* generic0NumberList: genericNumberList  */
#line 556 "reparser.y"
                    {
			(_DtCm_yyval.nl) = (_DtCm_yyvsp[0].nl);
		    }
#line 2058 "y.tab.c"
    break;

  case 74: /* genericNumberList: NUMBER endMarker  */
#line 562 "reparser.y"
                    {
			if ((_DtCm_yyvsp[0].number))
				RE_SET_FLAG((_DtCm_yyvsp[-1].number));

			(_DtCm_yyval.nl) = AllocNumber((_DtCm_yyvsp[-1].number));
		    }
#line 2069 "y.tab.c"
    break;

  case 75: /* genericNumberList: LASTDAY endMarker  */
#line 569 "reparser.y"
                    {
			int	number = RE_LASTDAY;

			if ((_DtCm_yyvsp[0].number))
				RE_SET_FLAG(number);

			(_DtCm_yyval.nl) = AllocNumber(number);
		    }
#line 2082 "y.tab.c"
    break;

  case 76: /* genericNumberList: genericNumberList NUMBER endMarker  */
#line 578 "reparser.y"
                    {
			NumberList	*nl;

			if ((_DtCm_yyvsp[0].number))
				RE_SET_FLAG((_DtCm_yyvsp[-1].number));

			nl = AllocNumber((_DtCm_yyvsp[-1].number));

			if ((_DtCm_yyvsp[-2].nl) == NULL) {
				(_DtCm_yyval.nl) = nl;
			} else {
				nl->nl_next = (_DtCm_yyval.nl)->nl_next;
				(_DtCm_yyval.nl)->nl_next = nl;
		    	}
		    }
#line 2102 "y.tab.c"
    break;

  case 77: /* genericNumberList: genericNumberList LASTDAY endMarker  */
#line 594 "reparser.y"
                    {
			NumberList	*nl;
			int		 number = RE_LASTDAY;

			if ((_DtCm_yyvsp[0].number))
				RE_SET_FLAG(number);

			nl = AllocNumber(number);

			if ((_DtCm_yyvsp[-2].nl) == NULL) {
				(_DtCm_yyval.nl) = nl;
			} else {
				nl->nl_next = (_DtCm_yyval.nl)->nl_next;
				(_DtCm_yyval.nl)->nl_next = nl;
		    	}
		    }
#line 2123 "y.tab.c"
    break;


#line 2127 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter _DtCm_yychar, and that requires
     that _DtCm_yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of _DtCm_yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering _DtCm_yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (_DtCm_yysymbol_kind_t, _DtCm_yyr1[_DtCm_yyn]), &_DtCm_yyval, &_DtCm_yyloc);

  YYPOPSTACK (_DtCm_yylen);
  _DtCm_yylen = 0;

  *++_DtCm_yyvsp = _DtCm_yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int _DtCm_yylhs = _DtCm_yyr1[_DtCm_yyn] - YYNTOKENS;
    const int _DtCm_yyi = _DtCm_yypgoto[_DtCm_yylhs] + *_DtCm_yyssp;
    _DtCm_yystate = (0 <= _DtCm_yyi && _DtCm_yyi <= YYLAST && _DtCm_yycheck[_DtCm_yyi] == *_DtCm_yyssp
               ? _DtCm_yytable[_DtCm_yyi]
               : _DtCm_yydefgoto[_DtCm_yylhs]);
  }

  goto _DtCm_yynewstate;


/*--------------------------------------.
| _DtCm_yyerrlab -- here on detecting error.  |
`--------------------------------------*/
_DtCm_yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  _DtCm_yytoken = _DtCm_yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (_DtCm_yychar);
  /* If not already recovering from an error, report this error.  */
  if (!_DtCm_yyerrstatus)
    {
      ++_DtCm_yynerrs;
      _DtCm_yyerror (YY_("syntax error"));
    }

  if (_DtCm_yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (_DtCm_yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (_DtCm_yychar == YYEOF)
            YYABORT;
        }
      else
        {
          _DtCm_yydestruct ("Error: discarding",
                      _DtCm_yytoken, &_DtCm_yylval);
          _DtCm_yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto _DtCm_yyerrlab1;


/*---------------------------------------------------.
| _DtCm_yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
_DtCm_yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label _DtCm_yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++_DtCm_yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (_DtCm_yylen);
  _DtCm_yylen = 0;
  YY_STACK_PRINT (_DtCm_yyss, _DtCm_yyssp);
  _DtCm_yystate = *_DtCm_yyssp;
  goto _DtCm_yyerrlab1;


/*-------------------------------------------------------------.
| _DtCm_yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
_DtCm_yyerrlab1:
  _DtCm_yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      _DtCm_yyn = _DtCm_yypact[_DtCm_yystate];
      if (!_DtCm_yypact_value_is_default (_DtCm_yyn))
        {
          _DtCm_yyn += YYSYMBOL_YYerror;
          if (0 <= _DtCm_yyn && _DtCm_yyn <= YYLAST && _DtCm_yycheck[_DtCm_yyn] == YYSYMBOL_YYerror)
            {
              _DtCm_yyn = _DtCm_yytable[_DtCm_yyn];
              if (0 < _DtCm_yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (_DtCm_yyssp == _DtCm_yyss)
        YYABORT;


      _DtCm_yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (_DtCm_yystate), _DtCm_yyvsp);
      YYPOPSTACK (1);
      _DtCm_yystate = *_DtCm_yyssp;
      YY_STACK_PRINT (_DtCm_yyss, _DtCm_yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++_DtCm_yyvsp = _DtCm_yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (_DtCm_yyn), _DtCm_yyvsp, _DtCm_yylsp);

  _DtCm_yystate = _DtCm_yyn;
  goto _DtCm_yynewstate;


/*-------------------------------------.
| _DtCm_yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
_DtCm_yyacceptlab:
  _DtCm_yyresult = 0;
  goto _DtCm_yyreturnlab;


/*-----------------------------------.
| _DtCm_yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
_DtCm_yyabortlab:
  _DtCm_yyresult = 1;
  goto _DtCm_yyreturnlab;


/*-----------------------------------------------------------.
| _DtCm_yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
_DtCm_yyexhaustedlab:
  _DtCm_yyerror (YY_("memory exhausted"));
  _DtCm_yyresult = 2;
  goto _DtCm_yyreturnlab;


/*----------------------------------------------------------.
| _DtCm_yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
_DtCm_yyreturnlab:
  if (_DtCm_yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      _DtCm_yytoken = YYTRANSLATE (_DtCm_yychar);
      _DtCm_yydestruct ("Cleanup: discarding lookahead",
                  _DtCm_yytoken, &_DtCm_yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (_DtCm_yylen);
  YY_STACK_PRINT (_DtCm_yyss, _DtCm_yyssp);
  while (_DtCm_yyssp != _DtCm_yyss)
    {
      _DtCm_yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*_DtCm_yyssp), _DtCm_yyvsp);
      YYPOPSTACK (1);
    }
#ifndef _DtCm_yyoverflow
  if (_DtCm_yyss != _DtCm_yyssa)
    YYSTACK_FREE (_DtCm_yyss);
#endif

  return _DtCm_yyresult;
}

#line 612 "reparser.y"


/*
 * Convert the NumberList (linked list) to an array, sort the array.
 */
static unsigned int *
ConvertNumList(
	NumberList	*nl,
	unsigned int	*count)
{
	NumberList	*nl_head = nl;
	unsigned int	*array;
	int		 i = 0;

	if (!nl) return (unsigned int *)NULL;

	while (nl) {
		i++;
		nl = nl->nl_next;
	}

	array = (unsigned int *) calloc(i, sizeof(unsigned int));
	i = 0;
			/* Convert the list into an array */
	nl = nl_head;
	while (nl) {
		NumberList	*nl_prev;

		array[i] = nl->nl_number;
		i++;

		nl_prev = nl;
		nl = nl->nl_next;

		free(nl_prev);
	}

	*count = i;

			/* Sort the array */
	qsort((void *)array, i, sizeof(unsigned int), CompareNums);

	return array;
}

/*
 * Convert the DayTimeList to an array, sort the array.
 */
static DayTime *
ConvertDayTime(
	DayTimeList	*dtl,
	unsigned int	*count)
{
	DayTimeList	*dtl_head = dtl;
	DayTime		*daytime_array;
	int		 i = 0,
			 no_time = -1;

	if (!dtl) return (DayTime *)NULL;

	while (dtl) {
		i++;
		dtl = dtl->dtl_next;
	}

	daytime_array = (DayTime *) calloc(i, sizeof(DayTime));
	i = 0;
			/* Convert the list into an array */
	dtl = dtl_head;
	while (dtl) {
		DayTimeList	*dtl_prev;

		daytime_array[i].dt_day = dtl->dtl_daytime->dt_day;
		daytime_array[i].dt_ntime = dtl->dtl_daytime->dt_ntime;
		daytime_array[i].dt_time = dtl->dtl_daytime->dt_time;
		i++;

		dtl_prev = dtl;
		dtl = dtl->dtl_next;
			/* alloc'ed in <weekdayTimeList> */
		free(dtl_prev);
	}

	*count = i;

	for (i = 0; i < *count; i++) {
		if (daytime_array[i].dt_time == NULL) {
			if (no_time == -1)
				no_time = i;
		} else {
			if (no_time != -1) {
				int j;

				for (j = no_time; j < i; j++) {
					daytime_array[j].dt_ntime = 
						daytime_array[i].dt_ntime;
					daytime_array[j].dt_time = 
						(Time *)calloc(
						     daytime_array[j].dt_ntime,
						     sizeof(Time));
					memcpy(daytime_array[j].dt_time,
					       daytime_array[i].dt_time,
					       daytime_array[j].dt_ntime *
								sizeof(Time));
				}
				no_time = -1;
			}
		}
	}

			/* Sort the array */
	qsort((void *)daytime_array, *count, sizeof(DayTime), CompareDayTime);

	return daytime_array;
}

/*
 * Used by qsort()
 */
static int
CompareNums(
	const void	*data1,
	const void	*data2)
{
	const unsigned int	*i = (const unsigned int *)data1;
	const unsigned int	*j = (const unsigned int *)data2;

	if ((unsigned )RE_MASK_STOP(*i) > (unsigned )RE_MASK_STOP(*j))
		return(1);
	if ((unsigned )RE_MASK_STOP(*i) < (unsigned )RE_MASK_STOP(*j))
		return(-1);
	return (0);
}

/*
 * Used by qsort()
 */
static int
CompareDayTime(
	const void	*data1,
	const void	*data2)
{
	const DayTime	*i = (const DayTime *)data1;
	const DayTime	*j = (const DayTime *)data2;

	if ((unsigned )RE_MASK_STOP(i->dt_day) >
					(unsigned )RE_MASK_STOP(j->dt_day))
		return(1);
	if ((unsigned )RE_MASK_STOP(i->dt_day) <
					(unsigned )RE_MASK_STOP(j->dt_day))
		return(-1);
	return (0);
}

/*
 * Used by qsort()
 */
static int
CompareWeekDayTime(
	const void	*data1,
	const void	*data2)
{
	const WeekDayTime	*i = (const WeekDayTime *)data1;
	const WeekDayTime	*j = (const WeekDayTime *)data2;

	if ((unsigned )RE_MASK_STOP(i->wdt_week[0]) >
					(unsigned )RE_MASK_STOP(j->wdt_week[0]))
		return(1);
	if ((unsigned )RE_MASK_STOP(i->wdt_week[0]) <
					(unsigned )RE_MASK_STOP(j->wdt_week[0]))
		return(-1);
	return (0);
}

static NumberList *
AllocNumber(
	unsigned int num)
{
	NumberList	*nl;

	nl = (NumberList *)calloc(1, sizeof(NumberList));

	nl->nl_number = num;
	nl->nl_next = NULL;

	return nl;
}

/*
 * Given three NumberLists convert them into arrays and return a WeekDayTime.
 */
static WeekDayTimeList *
AllocWeekDayTimeList(
	NumberList	*week_list,
	NumberList	*day_list,
	NumberList	*time_list)
{
	WeekDayTime	*wdt;
	WeekDayTimeList	*wdtl;

	wdt = (WeekDayTime *)calloc(1, sizeof(WeekDayTime));
	wdtl = (WeekDayTimeList *)calloc(1, sizeof(WeekDayTimeList));

	wdt->wdt_week =
		(WeekNumber *)ConvertNumList(week_list, &(wdt->wdt_nweek));
	wdt->wdt_day =
		(WeekDay *)ConvertNumList(day_list, &(wdt->wdt_nday));
	wdt->wdt_time =
		(Time *)ConvertNumList(time_list, &(wdt->wdt_ntime));
	wdtl->wdtl_weektime = wdt;

	return wdtl;
}

/*
 * Convert the DayTimeList to an array, sort the array.
 */
static WeekDayTime *
ConvertWeekDayTime(
	WeekDayTimeList	*wdtl,
	unsigned int	*count)
{
	WeekDayTimeList	*wdtl_head = wdtl;
	WeekDayTime	*array;
	int		 i = 0;

	if (!wdtl) return (WeekDayTime *)NULL;

	while (wdtl) {
		i++;
		wdtl = wdtl->wdtl_next;
	}

	array = (WeekDayTime *) calloc(i, sizeof(WeekDayTime));
	i = 0;
			/* Convert the list into an array */
	wdtl = wdtl_head;
	while (wdtl) {
		WeekDayTimeList	*wdtl_prev;

		array[i].wdt_day = wdtl->wdtl_weektime->wdt_day;
		array[i].wdt_nday = wdtl->wdtl_weektime->wdt_nday;
		array[i].wdt_time = wdtl->wdtl_weektime->wdt_time;
		array[i].wdt_ntime = wdtl->wdtl_weektime->wdt_ntime;
		array[i].wdt_week = wdtl->wdtl_weektime->wdt_week;
		array[i].wdt_nweek = wdtl->wdtl_weektime->wdt_nweek;
		i++;

		wdtl_prev = wdtl;
		wdtl = wdtl->wdtl_next;

		free(wdtl_prev);
	}

	*count = i;

			/* Sort the array */
	qsort((void *)array, i, sizeof(WeekDayTime), CompareWeekDayTime);

	return array;
}

static RepeatEvent *
HandleEndDate(
	RepeatEvent *re,
	time_t	     enddate)
{
	if (re) {
		if (enddate) {
			re->re_end_date = enddate;
		} else if (re->re_duration == RE_NOTSET) {
			re->re_duration = 2;
		}
	}
	return re;
}

/*
 * Create a RepeatEvent for the minute portion of a rule.
 */
static RepeatEvent *
DeriveMinuteEvent(
	unsigned int	 interval,
	unsigned int	 duration)
{
	RepeatEvent	*re;

	if (interval < 1)
		return NULL;

	re = (RepeatEvent *)calloc(1, sizeof(RepeatEvent));
				
	re->re_interval = interval;
	re->re_duration = duration;
	re->re_type = RT_MINUTE;

	return re;
}

/*
 * Create a RepeatEvent for the daily portion of a rule.
 */
static RepeatEvent *
DeriveDailyEvent(
	unsigned int	 interval,
	NumberList	*time_list,
	unsigned int	 duration,
	RepeatEvent	*other_event)
{
	RepeatEvent	*re;
	DailyData	*dd;

	dd = (DailyData *)calloc(1, sizeof(DailyData));

		/* Convert from list to array, sort */
	dd->dd_time = (Time *)ConvertNumList(time_list, &(dd->dd_ntime));

	if (interval < 1) {
		free(dd);
		return NULL;
	}

	re = (RepeatEvent *)calloc(1, sizeof(RepeatEvent));
				
	re->re_interval = interval;
	re->re_duration = duration;
	re->re_type = RT_DAILY;
	re->re_data.re_daily = dd;

		/* If there is a minuteEvent, tack it on */
	if (other_event) {
		re->re_next = other_event;
		other_event->re_prev = re;
	}

	return re;
}

/*
 * Create a RepeatEvent for the weekly portion of a rule.
 */
static RepeatEvent *
DeriveWeeklyEvent(
	unsigned int	 interval,
	DayTimeList	*dtl,
	unsigned int	 duration,
	RepeatEvent	*other_event)
{
	RepeatEvent	*re;
	WeeklyData	*wd;

	wd = (WeeklyData *)calloc(1, sizeof(WeeklyData));

		/* Convert from list to array, sort */
	wd->wd_daytime = ConvertDayTime(dtl, &(wd->wd_ndaytime));

	if (interval < 1) {
		free(wd);
		return NULL;
	}

	re = (RepeatEvent *)calloc(1, sizeof(RepeatEvent));
				
	re->re_interval = interval;
	re->re_duration = duration;
	re->re_type = RT_WEEKLY;
	re->re_data.re_weekly = wd;

	if (other_event) {
		re->re_next = other_event;
		other_event->re_prev = re;
	}

	return re;
}

/*
 * Create a RepeatEvent for the monthly portion of a rule.
 */
static RepeatEvent *
DeriveMonthlyEvent(
	RepeatType	 type,
	unsigned int	 interval,
	void		*data_list,
	unsigned int	 duration,
	RepeatEvent	*other_event)
{
	RepeatEvent	*re;
	MonthlyData	*md;

	md = (MonthlyData *)calloc(1, sizeof(MonthlyData));

			/* Convert from list to array, sort */
	if (type == RT_MONTHLY_POSITION) {
		md->md_weektime = ConvertWeekDayTime(
			(WeekDayTimeList *)data_list, &(md->md_nitems));
	} else {
		md->md_days = ConvertNumList(
			(NumberList *)data_list, &(md->md_nitems));
	}

	if (interval < 1) {
		free(md);
		return NULL;
	}

	re = (RepeatEvent *)calloc(1, sizeof(RepeatEvent));
				
	re->re_interval = interval;
	re->re_duration = duration;
	re->re_type = type;
	re->re_data.re_monthly = md;

		/* If there is an another event, tack it on */
	if (other_event) {
		re->re_next = other_event;
		other_event->re_prev = re;
	}

	return re;
}

/*
 * Create a RepeatEvent for the yearly portion of a rule.
 */
static RepeatEvent *
DeriveYearlyEvent(
	RepeatType	 type,
	unsigned int	 interval,
	NumberList	*nl,
	unsigned int	 duration,
	RepeatEvent	*other_event)
{
	RepeatEvent	*re;
	YearlyData	*yd;

	yd = (YearlyData *)calloc(1, sizeof(YearlyData));

			/* Convert from list to array, sort */
	yd->yd_items = ConvertNumList(nl, &(yd->yd_nitems));

	if (interval < 1) {
		free(yd);
		return NULL;
	}

	re = (RepeatEvent *)calloc(1, sizeof(RepeatEvent));
				
	re->re_interval = interval;
	re->re_duration = duration;
	re->re_type = type;
	re->re_data.re_yearly = yd;

		/* If there is an another event, tack it on */
	if (other_event) {
		re->re_next = other_event;
		other_event->re_prev = re;
	}

	return re;
}

void
_DtCm_yyerror(
	char 	*str)
{
	/* Don't do anything */
}
