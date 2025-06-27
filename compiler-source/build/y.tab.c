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
#line 1 "parser/parser.y"

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"
#include "ast.h"
#include "y.tab.h"
#include <stdarg.h>

#define MAX_RULES 1000
char *rule_names[MAX_RULES];
int rule_counts[MAX_RULES];
int rule_total = 0;

void rule_hit(const char *name) {
    for (int i = 0; i < rule_total; ++i) {
        if (strcmp(rule_names[i], name) == 0) {
            rule_counts[i]++;
            return;
        }
    }
    if (rule_total < MAX_RULES) {
        rule_names[rule_total] = strdup(name);
        rule_counts[rule_total] = 1;
        rule_total++;
    }
}

void print_grammar_coverage() {
    FILE *f = fopen("cobertura.txt", "w");
    if (!f) return;

    fprintf(f, "Cobertura:\n");
    for (int i = 0; i < rule_total; ++i) {
        fprintf(f, "%s: %d\n", rule_names[i], rule_counts[i]);
    }
    fclose(f);
}

extern int yylineno;

void yyerror(const char *s);
int yylex(void);

ASTNode *ast_root = NULL;
int current_scope = 0;

// Funções auxiliares
ASTNode* create_declaration_node(char *type, char *name, ASTNode *init);
ASTNode* create_assignment_node(char *op, ASTNode *lhs, ASTNode *rhs);
ASTNode* create_binary_op(char *op, ASTNode *lhs, ASTNode *rhs);
ASTNode* create_unary_op(char *op, ASTNode *operand);

static ASTNode *func_node_temp = NULL;
static ASTNode *body_node_temp = NULL;
static ASTNode *if_node_temp = NULL;


#line 131 "build/y.tab.c"

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

#include "y.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_ID = 3,                       /* T_ID  */
  YYSYMBOL_T_STRING = 4,                   /* T_STRING  */
  YYSYMBOL_T_CHAR_LITERAL = 5,             /* T_CHAR_LITERAL  */
  YYSYMBOL_T_NUMBER_FLOAT = 6,             /* T_NUMBER_FLOAT  */
  YYSYMBOL_T_NUMBER_INT = 7,               /* T_NUMBER_INT  */
  YYSYMBOL_T_INT = 8,                      /* T_INT  */
  YYSYMBOL_T_FLOAT = 9,                    /* T_FLOAT  */
  YYSYMBOL_T_CHAR = 10,                    /* T_CHAR  */
  YYSYMBOL_T_VOID = 11,                    /* T_VOID  */
  YYSYMBOL_T_IF = 12,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 13,                    /* T_ELSE  */
  YYSYMBOL_T_WHILE = 14,                   /* T_WHILE  */
  YYSYMBOL_T_FOR = 15,                     /* T_FOR  */
  YYSYMBOL_T_RETURN = 16,                  /* T_RETURN  */
  YYSYMBOL_T_PRINTF = 17,                  /* T_PRINTF  */
  YYSYMBOL_T_SCANF = 18,                   /* T_SCANF  */
  YYSYMBOL_T_SWITCH = 19,                  /* T_SWITCH  */
  YYSYMBOL_T_CASE = 20,                    /* T_CASE  */
  YYSYMBOL_T_DEFAULT = 21,                 /* T_DEFAULT  */
  YYSYMBOL_T_BREAK = 22,                   /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 23,                /* T_CONTINUE  */
  YYSYMBOL_T_DO = 24,                      /* T_DO  */
  YYSYMBOL_T_MOD = 25,                     /* T_MOD  */
  YYSYMBOL_T_INC = 26,                     /* T_INC  */
  YYSYMBOL_T_DEC = 27,                     /* T_DEC  */
  YYSYMBOL_T_PLUS_ASSIGN = 28,             /* T_PLUS_ASSIGN  */
  YYSYMBOL_T_MINUS_ASSIGN = 29,            /* T_MINUS_ASSIGN  */
  YYSYMBOL_T_ARROW = 30,                   /* T_ARROW  */
  YYSYMBOL_T_DOT = 31,                     /* T_DOT  */
  YYSYMBOL_T_AMPERSAND = 32,               /* T_AMPERSAND  */
  YYSYMBOL_T_BIT_OR = 33,                  /* T_BIT_OR  */
  YYSYMBOL_T_PLUS = 34,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 35,                   /* T_MINUS  */
  YYSYMBOL_T_MULT = 36,                    /* T_MULT  */
  YYSYMBOL_T_DIV = 37,                     /* T_DIV  */
  YYSYMBOL_T_ASSIGN = 38,                  /* T_ASSIGN  */
  YYSYMBOL_T_EQ = 39,                      /* T_EQ  */
  YYSYMBOL_T_NEQ = 40,                     /* T_NEQ  */
  YYSYMBOL_T_LT = 41,                      /* T_LT  */
  YYSYMBOL_T_GT = 42,                      /* T_GT  */
  YYSYMBOL_T_LE = 43,                      /* T_LE  */
  YYSYMBOL_T_GE = 44,                      /* T_GE  */
  YYSYMBOL_T_AND = 45,                     /* T_AND  */
  YYSYMBOL_T_OR = 46,                      /* T_OR  */
  YYSYMBOL_T_NOT = 47,                     /* T_NOT  */
  YYSYMBOL_T_LPAREN = 48,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 49,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 50,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 51,                  /* T_RBRACE  */
  YYSYMBOL_T_SEMICOLON = 52,               /* T_SEMICOLON  */
  YYSYMBOL_T_COMMA = 53,                   /* T_COMMA  */
  YYSYMBOL_T_COLON = 54,                   /* T_COLON  */
  YYSYMBOL_T_CONST = 55,                   /* T_CONST  */
  YYSYMBOL_T_UNSIGNED = 56,                /* T_UNSIGNED  */
  YYSYMBOL_T_PRINTF_ARGS = 57,             /* T_PRINTF_ARGS  */
  YYSYMBOL_58_ = 58,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_program = 60,                   /* program  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_function_list = 62,             /* function_list  */
  YYSYMBOL_function_declaration = 63,      /* function_declaration  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_function_parameter = 65,        /* function_parameter  */
  YYSYMBOL_parameter_list = 66,            /* parameter_list  */
  YYSYMBOL_function_call = 67,             /* function_call  */
  YYSYMBOL_argument_list = 68,             /* argument_list  */
  YYSYMBOL_declarations = 69,              /* declarations  */
  YYSYMBOL_declaration = 70,               /* declaration  */
  YYSYMBOL_declarator = 71,                /* declarator  */
  YYSYMBOL_pointer = 72,                   /* pointer  */
  YYSYMBOL_direct_declarator = 73,         /* direct_declarator  */
  YYSYMBOL_type_specifier = 74,            /* type_specifier  */
  YYSYMBOL_statements = 75,                /* statements  */
  YYSYMBOL_statement = 76,                 /* statement  */
  YYSYMBOL_do_while_statement = 77,        /* do_while_statement  */
  YYSYMBOL_scanf_statement = 78,           /* scanf_statement  */
  YYSYMBOL_while_statement = 79,           /* while_statement  */
  YYSYMBOL_assignment_statement = 80,      /* assignment_statement  */
  YYSYMBOL_return_statement = 81,          /* return_statement  */
  YYSYMBOL_if_statement = 82,              /* if_statement  */
  YYSYMBOL_expression = 83,                /* expression  */
  YYSYMBOL_printf_statement = 84,          /* printf_statement  */
  YYSYMBOL_printf_args = 85                /* printf_args  */
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
#define YYLAST   607

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  173

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


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
       2,     2,    58,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   119,   136,   141,   151,   150,   192,   196,
     203,   216,   232,   242,   247,   254,   263,   267,   276,   288,
     314,   319,   326,   330,   338,   345,   346,   347,   348,   349,
     350,   354,   359,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   389,   416,   426,   474,   475,   496,   510,
     565,   575,   584,   598,   611,   632,   642,   650,   656,   662,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   680,   681,   682,   683,   684,   685,   692,   699,
     700,   704,   713,   720
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
  "\"end of file\"", "error", "\"invalid token\"", "T_ID", "T_STRING",
  "T_CHAR_LITERAL", "T_NUMBER_FLOAT", "T_NUMBER_INT", "T_INT", "T_FLOAT",
  "T_CHAR", "T_VOID", "T_IF", "T_ELSE", "T_WHILE", "T_FOR", "T_RETURN",
  "T_PRINTF", "T_SCANF", "T_SWITCH", "T_CASE", "T_DEFAULT", "T_BREAK",
  "T_CONTINUE", "T_DO", "T_MOD", "T_INC", "T_DEC", "T_PLUS_ASSIGN",
  "T_MINUS_ASSIGN", "T_ARROW", "T_DOT", "T_AMPERSAND", "T_BIT_OR",
  "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", "T_ASSIGN", "T_EQ", "T_NEQ",
  "T_LT", "T_GT", "T_LE", "T_GE", "T_AND", "T_OR", "T_NOT", "T_LPAREN",
  "T_RPAREN", "T_LBRACE", "T_RBRACE", "T_SEMICOLON", "T_COMMA", "T_COLON",
  "T_CONST", "T_UNSIGNED", "T_PRINTF_ARGS", "'*'", "$accept", "program",
  "$@1", "function_list", "function_declaration", "$@2",
  "function_parameter", "parameter_list", "function_call", "argument_list",
  "declarations", "declaration", "declarator", "pointer",
  "direct_declarator", "type_specifier", "statements", "statement",
  "do_while_statement", "scanf_statement", "while_statement",
  "assignment_statement", "return_statement", "if_statement", "expression",
  "printf_statement", "printf_args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -68,    10,   -68,   -68,    24,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,    16,   -35,    24,   -21,   -23,    -1,   -68,    24,
     -68,    -5,   -68,    55,   -68,    11,    -1,   -68,   -68,   -68,
     -68,    24,   -68,    -1,   107,    17,   -17,    36,    41,    20,
      43,    49,    48,   -68,   -68,    50,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,    20,   -68,    20,    20,    20,
      20,    20,    20,    53,   -68,   -68,   -68,   -68,    20,    20,
      20,    20,   -68,   259,    20,   100,   -68,   -68,   285,   308,
     331,   354,    28,   487,   377,   399,     7,     7,   421,   -68,
      20,   102,   103,    20,    20,    20,    20,    20,    20,    20,
      20,    20,    20,    20,    20,    20,   -68,   487,    37,    56,
     131,   -68,   -68,   -68,   -68,   -68,    20,    58,    61,   -68,
       7,   -68,   -68,   550,    57,    57,     7,     7,    29,    29,
     570,   570,   570,   570,   530,   509,    60,    20,    88,   108,
     487,   -68,   -68,   -68,   487,   123,    79,   157,   181,    80,
      20,   117,   -68,    83,   443,     6,   -68,    84,    90,   -68,
     -68,    20,   207,   465,   -68,    82,   -68,   231,   133,    94,
     -68,   257,   -68
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     3,    25,    26,    27,    28,    29,
      30,     5,     0,     0,     8,     0,     9,     0,     6,     0,
      24,    22,    10,     0,    21,     0,     0,    23,    20,    16,
      11,    31,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,    42,     0,    35,    32,    38,    34,
      37,    40,    39,    36,    33,     0,    18,     0,     0,     0,
      13,     0,     0,    55,    58,    59,    57,    56,     0,     0,
       0,     0,    80,     0,     0,     0,    31,    41,     0,     0,
       0,     0,     0,    14,     0,     0,    74,    75,     0,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    82,     0,     0,
       0,    19,    48,    49,    47,    12,     0,     0,     0,    76,
      64,    78,    77,    73,    60,    61,    62,    63,    65,    66,
      67,    68,    69,    70,    71,    72,     0,     0,     0,     0,
      15,    31,    31,    81,    83,     0,     0,     0,     0,     0,
       0,    51,    45,     0,     0,     0,    44,     0,     0,    31,
      43,     0,     0,     0,    53,     0,    31,     0,    52,     0,
      31,     0,    54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -34,   -68,
     -68,   119,    -4,   130,   129,    81,   -67,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -54,   -68,   -68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     4,    11,    25,    15,    16,    72,    82,
      31,    46,    22,    23,    24,    33,    34,    47,    48,    49,
      50,    51,    52,    53,    73,    54,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      45,    78,    20,    79,    80,    81,    83,    84,    85,   110,
       3,    57,    58,    14,    86,    87,    88,    89,   158,    13,
     107,    59,    30,    63,    64,    65,    66,    67,    18,    35,
      19,    60,     5,     6,     7,     8,   120,    91,    92,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,    68,    21,    90,    55,   159,    21,    20,    91,
      92,    29,   140,    94,    95,    96,    97,    69,    70,    56,
     100,   101,   102,   103,   147,   148,    45,   115,    71,     9,
      10,   116,    90,   144,    61,    12,   136,    91,    92,    62,
     137,    74,   162,    96,    97,    17,   154,    75,    76,   167,
      26,    60,    77,   171,   109,   121,   122,   163,   141,   138,
      36,   142,   143,    45,    45,     5,     6,     7,     8,    37,
     145,    38,   146,    39,    40,    41,   149,   150,    45,   153,
     155,    42,   166,    45,    36,   156,   160,    45,   161,     5,
       6,     7,     8,    37,   170,    38,   169,    39,    40,    41,
      32,    27,    28,     0,     0,    42,     0,     0,    43,    44,
      36,     0,     9,    10,     0,     5,     6,     7,     8,    37,
       0,    38,     0,    39,    40,    41,     0,     0,     0,     0,
       0,    42,   139,    44,    36,     0,     9,    10,     0,     5,
       6,     7,     8,    37,     0,    38,     0,    39,    40,    41,
       0,     0,     0,     0,     0,    42,     0,     0,   151,    44,
      36,     0,     9,    10,     0,     5,     6,     7,     8,    37,
       0,    38,     0,    39,    40,    41,     0,     0,     0,     0,
       0,    42,   152,    44,    36,     0,     9,    10,     0,     5,
       6,     7,     8,    37,     0,    38,     0,    39,    40,    41,
       0,     0,     0,     0,     0,    42,     0,     0,   164,    44,
      36,     0,     9,    10,     0,     5,     6,     7,     8,    37,
       0,    38,     0,    39,    40,    41,     0,     0,     0,     0,
       0,    42,   168,    44,    90,     0,     9,    10,     0,    91,
      92,     0,    93,    94,    95,    96,    97,     0,    98,    99,
     100,   101,   102,   103,   104,   105,     0,     0,   172,    44,
      90,   106,     9,    10,     0,    91,    92,     0,    93,    94,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
     104,   105,     0,    90,     0,     0,     0,   111,    91,    92,
       0,    93,    94,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,   104,   105,     0,    90,     0,     0,     0,
     112,    91,    92,     0,    93,    94,    95,    96,    97,     0,
      98,    99,   100,   101,   102,   103,   104,   105,     0,    90,
       0,     0,     0,   113,    91,    92,     0,    93,    94,    95,
      96,    97,     0,    98,    99,   100,   101,   102,   103,   104,
     105,     0,    90,     0,     0,     0,   114,    91,    92,     0,
      93,    94,    95,    96,    97,     0,    98,    99,   100,   101,
     102,   103,   104,   105,    90,     0,   117,     0,     0,    91,
      92,     0,    93,    94,    95,    96,    97,     0,    98,    99,
     100,   101,   102,   103,   104,   105,    90,     0,   118,     0,
       0,    91,    92,     0,    93,    94,    95,    96,    97,     0,
      98,    99,   100,   101,   102,   103,   104,   105,    90,     0,
     119,     0,     0,    91,    92,     0,    93,    94,    95,    96,
      97,     0,    98,    99,   100,   101,   102,   103,   104,   105,
      90,     0,   157,     0,     0,    91,    92,     0,    93,    94,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
     104,   105,    90,     0,   165,     0,     0,    91,    92,     0,
      93,    94,    95,    96,    97,     0,    98,    99,   100,   101,
     102,   103,   104,   105,    90,     0,     0,     0,     0,    91,
      92,     0,    93,    94,    95,    96,    97,     0,    98,    99,
     100,   101,   102,   103,   104,    90,     0,     0,     0,     0,
      91,    92,     0,    93,    94,    95,    96,    97,     0,    98,
      99,   100,   101,   102,   103,    90,     0,     0,     0,     0,
      91,    92,     0,     0,    94,    95,    96,    97,     0,    98,
      99,   100,   101,   102,   103,    90,     0,     0,     0,     0,
      91,    92,     0,     0,    94,    95,    96,    97
};

static const yytype_int16 yycheck[] =
{
      34,    55,     3,    57,    58,    59,    60,    61,    62,    76,
       0,    28,    29,    48,    68,    69,    70,    71,    12,     3,
      74,    38,    26,     3,     4,     5,     6,     7,    49,    33,
      53,    48,     8,     9,    10,    11,    90,    30,    31,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    32,    58,    25,    38,    50,    58,     3,    30,
      31,    50,   116,    34,    35,    36,    37,    47,    48,    52,
      41,    42,    43,    44,   141,   142,   110,    49,    58,    55,
      56,    53,    25,   137,    48,     4,    49,    30,    31,    48,
      53,    48,   159,    36,    37,    14,   150,    48,    50,   166,
      19,    48,    52,   170,     4,     3,     3,   161,    50,    53,
       3,    50,    52,   147,   148,     8,     9,    10,    11,    12,
      32,    14,    14,    16,    17,    18,     3,    48,   162,    49,
      13,    24,    50,   167,     3,    52,    52,   171,    48,     8,
       9,    10,    11,    12,    50,    14,    13,    16,    17,    18,
      31,    21,    23,    -1,    -1,    24,    -1,    -1,    51,    52,
       3,    -1,    55,    56,    -1,     8,     9,    10,    11,    12,
      -1,    14,    -1,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    51,    52,     3,    -1,    55,    56,    -1,     8,
       9,    10,    11,    12,    -1,    14,    -1,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    51,    52,
       3,    -1,    55,    56,    -1,     8,     9,    10,    11,    12,
      -1,    14,    -1,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    51,    52,     3,    -1,    55,    56,    -1,     8,
       9,    10,    11,    12,    -1,    14,    -1,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    51,    52,
       3,    -1,    55,    56,    -1,     8,     9,    10,    11,    12,
      -1,    14,    -1,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    51,    52,    25,    -1,    55,    56,    -1,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    51,    52,
      25,    52,    55,    56,    -1,    30,    31,    -1,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    25,    -1,    -1,    -1,    52,    30,    31,
      -1,    33,    34,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    25,    -1,    -1,    -1,
      52,    30,    31,    -1,    33,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    25,
      -1,    -1,    -1,    52,    30,    31,    -1,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    25,    -1,    -1,    -1,    52,    30,    31,    -1,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    25,    -1,    49,    -1,    -1,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    25,    -1,    49,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    25,    -1,
      49,    -1,    -1,    30,    31,    -1,    33,    34,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      25,    -1,    49,    -1,    -1,    30,    31,    -1,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    25,    -1,    49,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    25,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    25,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    25,    -1,    -1,    -1,    -1,
      30,    31,    -1,    -1,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    25,    -1,    -1,    -1,    -1,
      30,    31,    -1,    -1,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    60,    61,     0,    62,     8,     9,    10,    11,    55,
      56,    63,    74,     3,    48,    65,    66,    74,    49,    53,
       3,    58,    71,    72,    73,    64,    74,    72,    73,    50,
      71,    69,    70,    74,    75,    71,     3,    12,    14,    16,
      17,    18,    24,    51,    52,    67,    70,    76,    77,    78,
      79,    80,    81,    82,    84,    38,    52,    28,    29,    38,
      48,    48,    48,     3,     4,     5,     6,     7,    32,    47,
      48,    58,    67,    83,    48,    48,    50,    52,    83,    83,
      83,    83,    68,    83,    83,    83,    83,    83,    83,    83,
      25,    30,    31,    33,    34,    35,    36,    37,    39,    40,
      41,    42,    43,    44,    45,    46,    52,    83,    85,     4,
      75,    52,    52,    52,    52,    49,    53,    49,    49,    49,
      83,     3,     3,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    49,    53,    53,    51,
      83,    50,    50,    52,    83,    32,    14,    75,    75,     3,
      48,    51,    51,    49,    83,    13,    52,    49,    12,    50,
      52,    48,    75,    83,    51,    49,    50,    75,    51,    13,
      50,    75,    51
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    61,    60,    62,    62,    64,    63,    65,    65,
      66,    66,    67,    68,    68,    68,    69,    69,    70,    70,
      71,    71,    72,    72,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    77,    78,    79,    80,    80,    80,    80,
      81,    82,    82,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    84,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     0,    10,     0,     1,
       2,     4,     4,     0,     1,     3,     0,     2,     3,     5,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     9,     8,     7,     0,     4,     4,     4,
       3,     7,    15,    11,    19,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     2,
       1,     5,     1,     3
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
  case 2: /* $@1: %empty  */
#line 119 "parser/parser.y"
    {
        rule_hit("program");
        init_symbol_table();
        ast_root = create_node(NODE_PROGRAM, "programa");
    }
#line 1413 "build/y.tab.c"
    break;

  case 3: /* program: $@1 function_list  */
#line 125 "parser/parser.y"
    {
        generate_portugol(ast_root);
        free_ast(ast_root);
        print_symbol_table_stderr();
        free_symbol_table();

        print_grammar_coverage();
    }
#line 1426 "build/y.tab.c"
    break;

  case 4: /* function_list: %empty  */
#line 137 "parser/parser.y"
    {
        rule_hit("function_list_empty");
        (yyval.ast) = create_node(NODE_EMPTY, NULL);
    }
#line 1435 "build/y.tab.c"
    break;

  case 5: /* function_list: function_list function_declaration  */
#line 142 "parser/parser.y"
    {
        rule_hit("function_list_append");
        add_child(ast_root, (yyvsp[0].ast));
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1445 "build/y.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 151 "parser/parser.y"
    {
        rule_hit("function_declaration");
        current_scope++;

        insert_symbol((yyvsp[-3].sval), (yyvsp[-4].sval), current_scope - 1);

        add_parameters_to_symbol_table((yyvsp[-1].ast));

        ASTNode *func_node = create_node(NODE_FUNCTION, strdup((yyvsp[-3].sval)));
        ASTNode *type_node = create_node(NODE_TYPE, strdup((yyvsp[-4].sval)));
        ASTNode *body_node = create_node(NODE_BLOCK, NULL);

        add_child(func_node, type_node);
        add_child(func_node, (yyvsp[-1].ast)); 
        add_child(func_node, body_node);

        func_node_temp = func_node;
        body_node_temp = body_node;
    }
#line 1469 "build/y.tab.c"
    break;

  case 7: /* function_declaration: type_specifier T_ID T_LPAREN function_parameter T_RPAREN $@2 T_LBRACE declarations statements T_RBRACE  */
#line 174 "parser/parser.y"
    {
        if ((yyvsp[-2].ast) && (yyvsp[-2].ast)->type != NODE_EMPTY) {
            add_child(body_node_temp, (yyvsp[-2].ast));
        }
        if ((yyvsp[-1].ast) && (yyvsp[-1].ast)->type != NODE_EMPTY) {
            add_child(body_node_temp, (yyvsp[-1].ast));
        }
        
        (yyval.ast) = func_node_temp;
        
        current_scope--;

        func_node_temp = NULL;
        body_node_temp = NULL;
    }
#line 1489 "build/y.tab.c"
    break;

  case 8: /* function_parameter: %empty  */
#line 193 "parser/parser.y"
    {
        (yyval.ast) = create_node(NODE_PARAM_LIST, NULL);
    }
#line 1497 "build/y.tab.c"
    break;

  case 9: /* function_parameter: parameter_list  */
#line 197 "parser/parser.y"
    {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1505 "build/y.tab.c"
    break;

  case 10: /* parameter_list: type_specifier declarator  */
#line 204 "parser/parser.y"
    {
        rule_hit("parameter_list_single");
        ASTNode *param_list_node = create_node(NODE_PARAM_LIST, NULL);
        ASTNode *param_node = create_node(NODE_PARAMETER, strdup((yyvsp[0].sval)));
        ASTNode *type_node = create_node(NODE_TYPE, strdup((yyvsp[-1].sval)));
        
        add_child(param_node, type_node);
        add_child(param_list_node, param_node);
        
        (yyval.ast) = param_list_node;
        
    }
#line 1522 "build/y.tab.c"
    break;

  case 11: /* parameter_list: parameter_list T_COMMA type_specifier declarator  */
#line 217 "parser/parser.y"
    {
        rule_hit("parameter_list_multiple");
        ASTNode *param_node = create_node(NODE_PARAMETER, strdup((yyvsp[0].sval)));
        ASTNode *type_node = create_node(NODE_TYPE, strdup((yyvsp[-1].sval)));
        
        add_child(param_node, type_node);
        add_child((yyvsp[-3].ast), param_node);
        
        (yyval.ast) = (yyvsp[-3].ast);
        
        // free($3); free($4);
    }
#line 1539 "build/y.tab.c"
    break;

  case 12: /* function_call: T_ID T_LPAREN argument_list T_RPAREN  */
#line 233 "parser/parser.y"
    {
        rule_hit("function_call");
        ASTNode *call_node = create_node(NODE_FUNCTION_CALL, (yyvsp[-3].sval));
        add_child(call_node, (yyvsp[-1].ast));
        (yyval.ast) = call_node;
    }
#line 1550 "build/y.tab.c"
    break;

  case 13: /* argument_list: %empty  */
#line 243 "parser/parser.y"
    {
        rule_hit("argument_list_empty");
        (yyval.ast) = create_node(NODE_STATEMENT_LIST, NULL); 
    }
#line 1559 "build/y.tab.c"
    break;

  case 14: /* argument_list: expression  */
#line 248 "parser/parser.y"
    {
        rule_hit("argument_list_single");
        ASTNode *list = create_node(NODE_STATEMENT_LIST, NULL);
        add_child(list, (yyvsp[0].ast));
        (yyval.ast) = list;
    }
#line 1570 "build/y.tab.c"
    break;

  case 15: /* argument_list: argument_list T_COMMA expression  */
#line 255 "parser/parser.y"
    {
        rule_hit("argument_list_multiple");
        add_child((yyvsp[-2].ast), (yyvsp[0].ast));
        (yyval.ast) = (yyvsp[-2].ast);
    }
#line 1580 "build/y.tab.c"
    break;

  case 16: /* declarations: %empty  */
#line 264 "parser/parser.y"
    {
        (yyval.ast) = create_node(NODE_DECLARATION_LIST, NULL);
    }
#line 1588 "build/y.tab.c"
    break;

  case 17: /* declarations: declarations declaration  */
#line 268 "parser/parser.y"
    {
        ASTNode *decls = create_node(NODE_DECLARATION_LIST, NULL);
        add_child((yyvsp[-1].ast), (yyvsp[0].ast));
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1598 "build/y.tab.c"
    break;

  case 18: /* declaration: type_specifier declarator T_SEMICOLON  */
#line 277 "parser/parser.y"
    {
        rule_hit("declaration_simple");
        (yyval.ast) = create_declaration_node((yyvsp[-2].sval), (yyvsp[-1].sval), NULL);
        if (lookup_symbol((yyvsp[-1].sval)) != NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' já declarada.", yylineno, (yyvsp[-1].sval));
            yyerror(msg);
        }
        insert_symbol((yyvsp[-1].sval), (yyvsp[-2].sval), current_scope);
        free((yyvsp[-2].sval)); free((yyvsp[-1].sval));
    }
#line 1614 "build/y.tab.c"
    break;

  case 19: /* declaration: type_specifier declarator T_ASSIGN expression T_SEMICOLON  */
#line 289 "parser/parser.y"
    {
        rule_hit("declaration_with_assignment");
        // Checagem de tipo da atribuição
        if ((yyvsp[-1].ast)->data_type && strcmp((yyvsp[-4].sval), (yyvsp[-1].ast)->data_type) != 0) {
            char msg[256];
            snprintf(msg, sizeof(msg),
                "Erro de tipo na linha %d: não é possível atribuir %s em %s.",
                yylineno, (yyvsp[-1].ast)->data_type, (yyvsp[-4].sval));
            yyerror(msg);
        }

        (yyval.ast) = create_declaration_node((yyvsp[-4].sval), (yyvsp[-3].sval), (yyvsp[-1].ast));

        if (lookup_symbol((yyvsp[-3].sval)) != NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' já declarada.", yylineno, (yyvsp[-3].sval));
            yyerror(msg);
        }

        insert_symbol((yyvsp[-3].sval), (yyvsp[-4].sval), current_scope);
        free((yyvsp[-4].sval)); free((yyvsp[-3].sval));
    }
#line 1641 "build/y.tab.c"
    break;

  case 20: /* declarator: pointer direct_declarator  */
#line 315 "parser/parser.y"
    {
        asprintf(&(yyval.sval), "%s%s", (yyvsp[-1].sval), (yyvsp[0].sval));
        free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1650 "build/y.tab.c"
    break;

  case 21: /* declarator: direct_declarator  */
#line 320 "parser/parser.y"
    {
        (yyval.sval) = (yyvsp[0].sval);
    }
#line 1658 "build/y.tab.c"
    break;

  case 22: /* pointer: '*'  */
#line 327 "parser/parser.y"
    {
        (yyval.sval) = strdup("*");
    }
#line 1666 "build/y.tab.c"
    break;

  case 23: /* pointer: '*' pointer  */
#line 331 "parser/parser.y"
    {
        asprintf(&(yyval.sval), "*%s", (yyvsp[0].sval));
        free((yyvsp[0].sval));
    }
#line 1675 "build/y.tab.c"
    break;

  case 24: /* direct_declarator: T_ID  */
#line 339 "parser/parser.y"
    {
        (yyval.sval) = (yyvsp[0].sval);
    }
#line 1683 "build/y.tab.c"
    break;

  case 25: /* type_specifier: T_INT  */
#line 345 "parser/parser.y"
               { (yyval.sval) = strdup("inteiro"); }
#line 1689 "build/y.tab.c"
    break;

  case 26: /* type_specifier: T_FLOAT  */
#line 346 "parser/parser.y"
                 { (yyval.sval) = strdup("real"); }
#line 1695 "build/y.tab.c"
    break;

  case 27: /* type_specifier: T_CHAR  */
#line 347 "parser/parser.y"
                 { (yyval.sval) = strdup("caracter"); }
#line 1701 "build/y.tab.c"
    break;

  case 28: /* type_specifier: T_VOID  */
#line 348 "parser/parser.y"
                 { (yyval.sval) = strdup("vazio"); }
#line 1707 "build/y.tab.c"
    break;

  case 29: /* type_specifier: T_CONST  */
#line 349 "parser/parser.y"
                 { (yyval.sval) = strdup("constante"); }
#line 1713 "build/y.tab.c"
    break;

  case 30: /* type_specifier: T_UNSIGNED  */
#line 350 "parser/parser.y"
                 { (yyval.sval) = strdup("inteiro"); }
#line 1719 "build/y.tab.c"
    break;

  case 31: /* statements: %empty  */
#line 355 "parser/parser.y"
    {
        rule_hit("statements_empty");
        (yyval.ast) = create_node(NODE_STATEMENT_LIST, NULL);
    }
#line 1728 "build/y.tab.c"
    break;

  case 32: /* statements: statements statement  */
#line 360 "parser/parser.y"
    {
        add_child((yyvsp[-1].ast), (yyvsp[0].ast));
        
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1738 "build/y.tab.c"
    break;

  case 33: /* statement: printf_statement  */
#line 368 "parser/parser.y"
                                      { rule_hit("statement_printf"); (yyval.ast) = (yyvsp[0].ast); }
#line 1744 "build/y.tab.c"
    break;

  case 34: /* statement: scanf_statement  */
#line 369 "parser/parser.y"
                                        { rule_hit("statement_scanf"); (yyval.ast) = (yyvsp[0].ast); }
#line 1750 "build/y.tab.c"
    break;

  case 35: /* statement: declaration  */
#line 370 "parser/parser.y"
                                        { rule_hit("statement_declaration"); (yyval.ast) = (yyvsp[0].ast); }
#line 1756 "build/y.tab.c"
    break;

  case 36: /* statement: if_statement  */
#line 371 "parser/parser.y"
                                        { rule_hit("statement_if"); (yyval.ast) = (yyvsp[0].ast); }
#line 1762 "build/y.tab.c"
    break;

  case 37: /* statement: while_statement  */
#line 372 "parser/parser.y"
                                        { rule_hit("statement_while"); (yyval.ast) = (yyvsp[0].ast); }
#line 1768 "build/y.tab.c"
    break;

  case 38: /* statement: do_while_statement  */
#line 373 "parser/parser.y"
                                        { rule_hit("statement_do_while"); (yyval.ast) = (yyvsp[0].ast); }
#line 1774 "build/y.tab.c"
    break;

  case 39: /* statement: return_statement  */
#line 374 "parser/parser.y"
                                        { rule_hit("statement_return"); (yyval.ast) = (yyvsp[0].ast); }
#line 1780 "build/y.tab.c"
    break;

  case 40: /* statement: assignment_statement  */
#line 375 "parser/parser.y"
                                        { rule_hit("statement_assignment"); (yyval.ast) = (yyvsp[0].ast); }
#line 1786 "build/y.tab.c"
    break;

  case 41: /* statement: function_call T_SEMICOLON  */
#line 376 "parser/parser.y"
                                       { rule_hit("statement_function_call"); (yyval.ast) = (yyvsp[-1].ast); }
#line 1792 "build/y.tab.c"
    break;

  case 42: /* statement: T_SEMICOLON  */
#line 377 "parser/parser.y"
                                        { rule_hit("statement_empty"); (yyval.ast) = create_node(NODE_EMPTY, NULL); }
#line 1798 "build/y.tab.c"
    break;

  case 43: /* do_while_statement: T_DO T_LBRACE statements T_RBRACE T_WHILE T_LPAREN expression T_RPAREN T_SEMICOLON  */
#line 390 "parser/parser.y"
    {
        rule_hit("do_while_statement");
        ASTNode *do_while = create_node(NODE_DO_WHILE, NULL);
        add_child(do_while, (yyvsp[-6].ast)); // Bloco de statements
        add_child(do_while, (yyvsp[-2].ast)); // Condição
        (yyval.ast) = do_while;
    }
#line 1810 "build/y.tab.c"
    break;

  case 44: /* scanf_statement: T_SCANF T_LPAREN T_STRING T_COMMA T_AMPERSAND T_ID T_RPAREN T_SEMICOLON  */
#line 417 "parser/parser.y"
    {
        ASTNode *scanf_node = create_node(NODE_SCANF, (yyvsp[-5].sval));
        add_child(scanf_node, create_node(NODE_IDENTIFIER, (yyvsp[-2].sval)));
        (yyval.ast) = scanf_node;
        free((yyvsp[-5].sval)); free((yyvsp[-2].sval));
    }
#line 1821 "build/y.tab.c"
    break;

  case 45: /* while_statement: T_WHILE T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE  */
#line 427 "parser/parser.y"
    {
        rule_hit("while_statement");
        ASTNode *while_node = create_node(NODE_WHILE, NULL);
        add_child(while_node, (yyvsp[-4].ast)); // Condição
        add_child(while_node, (yyvsp[-1].ast)); // Corpo
        (yyval.ast) = while_node;
    }
#line 1833 "build/y.tab.c"
    break;

  case 47: /* assignment_statement: T_ID T_ASSIGN expression T_SEMICOLON  */
#line 476 "parser/parser.y"
    {
        rule_hit("assignment_simple");
        Symbol *sym = lookup_symbol((yyvsp[-3].sval));
        if (sym == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, (yyvsp[-3].sval));
            yyerror(msg);
        }

        if ((yyvsp[-1].ast)->data_type && strcmp(sym->type, (yyvsp[-1].ast)->data_type) != 0) {
            char msg[256];
            snprintf(msg, sizeof(msg),
                "Erro de tipo na linha %d: não é possível atribuir %s a variável do tipo %s.",
                yylineno, (yyvsp[-1].ast)->data_type, sym->type);
            yyerror(msg);
        }

        (yyval.ast) = create_assignment_node("=", create_node(NODE_IDENTIFIER, (yyvsp[-3].sval)), (yyvsp[-1].ast));
        free((yyvsp[-3].sval));
    }
#line 1858 "build/y.tab.c"
    break;

  case 48: /* assignment_statement: T_ID T_PLUS_ASSIGN expression T_SEMICOLON  */
#line 497 "parser/parser.y"
    {
        rule_hit("assignment_simple");
        if (lookup_symbol((yyvsp[-3].sval)) == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, (yyvsp[-3].sval));
            yyerror(msg);
        }

        ASTNode *lhs = create_node(NODE_IDENTIFIER, (yyvsp[-3].sval));
        ASTNode *rhs = create_binary_op("+", lhs, (yyvsp[-1].ast));
        (yyval.ast) = create_assignment_node("=", lhs, rhs);
        free((yyvsp[-3].sval));
    }
#line 1876 "build/y.tab.c"
    break;

  case 49: /* assignment_statement: T_ID T_MINUS_ASSIGN expression T_SEMICOLON  */
#line 511 "parser/parser.y"
    {
        rule_hit("assignment_simple");
        if (lookup_symbol((yyvsp[-3].sval)) == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, (yyvsp[-3].sval));
            yyerror(msg);
        }

        ASTNode *lhs = create_node(NODE_IDENTIFIER, (yyvsp[-3].sval));
        ASTNode *rhs = create_binary_op("-", lhs, (yyvsp[-1].ast));
        (yyval.ast) = create_assignment_node("=", lhs, rhs);
        free((yyvsp[-3].sval));
    }
#line 1894 "build/y.tab.c"
    break;

  case 50: /* return_statement: T_RETURN expression T_SEMICOLON  */
#line 566 "parser/parser.y"
    {
        rule_hit("return_statement");
        ASTNode *ret = create_node(NODE_RETURN, NULL);
        add_child(ret, (yyvsp[-1].ast));
        (yyval.ast) = ret;
    }
#line 1905 "build/y.tab.c"
    break;

  case 51: /* if_statement: T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE  */
#line 576 "parser/parser.y"
    {
        rule_hit("if_simple");
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, (yyvsp[-4].ast)); // Condição
        add_child(if_node, (yyvsp[-1].ast)); // Then
        if_node_temp = if_node;
        (yyval.ast) = if_node;
    }
#line 1918 "build/y.tab.c"
    break;

  case 52: /* if_statement: T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE  */
#line 585 "parser/parser.y"
    {
        rule_hit("if_simple");
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, (yyvsp[-12].ast)); // Condição
        add_child(if_node, (yyvsp[-9].ast)); // Then
        
        ASTNode *elseif = create_node(NODE_ELSE_IF, NULL);
        add_child(elseif, (yyvsp[-4].ast)); // Condição do else if
        add_child(elseif, (yyvsp[-1].ast)); // Then do else if
        
        add_child(if_node, elseif);
        (yyval.ast) = if_node;
    }
#line 1936 "build/y.tab.c"
    break;

  case 53: /* if_statement: T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_LBRACE statements T_RBRACE  */
#line 599 "parser/parser.y"
    {
        rule_hit("if_simple");
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, (yyvsp[-8].ast)); // Condição
        add_child(if_node, (yyvsp[-5].ast)); // Then
        
        ASTNode *else_node = create_node(NODE_ELSE, NULL);
        add_child(else_node, (yyvsp[-1].ast)); // Bloco else
        
        add_child(if_node, else_node);
        (yyval.ast) = if_node;
    }
#line 1953 "build/y.tab.c"
    break;

  case 54: /* if_statement: T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_LBRACE statements T_RBRACE  */
#line 612 "parser/parser.y"
    {
        rule_hit("if_simple");
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, (yyvsp[-16].ast)); // Condição
        add_child(if_node, (yyvsp[-13].ast)); // Then
        
        ASTNode *elseif = create_node(NODE_ELSE_IF, NULL);
        add_child(elseif, (yyvsp[-8].ast)); // Condição do else if
        add_child(elseif, (yyvsp[-5].ast)); // Then do else if
        
        ASTNode *else_node = create_node(NODE_ELSE, NULL);
        add_child(else_node, (yyvsp[-1].ast)); // Bloco else
        
        add_child(elseif, else_node);
        add_child(if_node, elseif);
        (yyval.ast) = if_node;
    }
#line 1975 "build/y.tab.c"
    break;

  case 55: /* expression: T_ID  */
#line 633 "parser/parser.y"
    {
        rule_hit("expression_id");
        Symbol *sym = lookup_symbol((yyvsp[0].sval));
        if (sym == NULL) {
            fprintf(stderr, "Erro semântico: Variável '%s' usada, mas não declarada\n", (yyvsp[0].sval));
            yyerror("erro semântico: variável não declarada");
        }
        (yyval.ast) = create_node(NODE_IDENTIFIER, (yyvsp[0].sval));
    }
#line 1989 "build/y.tab.c"
    break;

  case 56: /* expression: T_NUMBER_INT  */
#line 643 "parser/parser.y"
    { 
        rule_hit("expression_int");
        char num[20]; 
        sprintf(num, "%d", (yyvsp[0].ival)); 
        (yyval.ast) = create_node(NODE_CONST_INT, num); 
        (yyval.ast)->data_type = strdup("inteiro");
    }
#line 2001 "build/y.tab.c"
    break;

  case 57: /* expression: T_NUMBER_FLOAT  */
#line 651 "parser/parser.y"
    { 
        rule_hit("expression_float");
        (yyval.ast) = create_node(NODE_CONST_FLOAT, (yyvsp[0].sval)); 
        (yyval.ast)->data_type = strdup("real");
    }
#line 2011 "build/y.tab.c"
    break;

  case 58: /* expression: T_STRING  */
#line 657 "parser/parser.y"
    { 
        rule_hit("expression_string");
        (yyval.ast) = create_node(NODE_CONST_STRING, (yyvsp[0].sval)); 
        (yyval.ast)->data_type = strdup("string");
    }
#line 2021 "build/y.tab.c"
    break;

  case 59: /* expression: T_CHAR_LITERAL  */
#line 663 "parser/parser.y"
    { 
        rule_hit("expression_char");
        (yyval.ast) = create_node(NODE_CONST_CHAR, (yyvsp[0].sval)); 
        (yyval.ast)->data_type = strdup("caracter");
    }
#line 2031 "build/y.tab.c"
    break;

  case 60: /* expression: expression T_PLUS expression  */
#line 668 "parser/parser.y"
                                      { rule_hit("expression_plus"); (yyval.ast) = create_binary_op("+", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2037 "build/y.tab.c"
    break;

  case 61: /* expression: expression T_MINUS expression  */
#line 669 "parser/parser.y"
                                      { rule_hit("expression_minus"); (yyval.ast) = create_binary_op("-", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2043 "build/y.tab.c"
    break;

  case 62: /* expression: expression T_MULT expression  */
#line 670 "parser/parser.y"
                                      { rule_hit("expression_mult"); (yyval.ast) = create_binary_op("*", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2049 "build/y.tab.c"
    break;

  case 63: /* expression: expression T_DIV expression  */
#line 671 "parser/parser.y"
                                      { rule_hit("expression_div"); (yyval.ast) = create_binary_op("/", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2055 "build/y.tab.c"
    break;

  case 64: /* expression: expression T_MOD expression  */
#line 672 "parser/parser.y"
                                      { rule_hit("expression_mod"); (yyval.ast) = create_binary_op("%", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2061 "build/y.tab.c"
    break;

  case 65: /* expression: expression T_EQ expression  */
#line 673 "parser/parser.y"
                                      { rule_hit("expression_eq"); (yyval.ast) = create_binary_op("==", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2067 "build/y.tab.c"
    break;

  case 66: /* expression: expression T_NEQ expression  */
#line 674 "parser/parser.y"
                                      { rule_hit("expression_neq"); (yyval.ast) = create_binary_op("!=", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2073 "build/y.tab.c"
    break;

  case 67: /* expression: expression T_LT expression  */
#line 675 "parser/parser.y"
                                      { rule_hit("expression_lt"); (yyval.ast) = create_binary_op("<", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2079 "build/y.tab.c"
    break;

  case 68: /* expression: expression T_GT expression  */
#line 676 "parser/parser.y"
                                      { rule_hit("expression_gt"); (yyval.ast) = create_binary_op(">", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2085 "build/y.tab.c"
    break;

  case 69: /* expression: expression T_LE expression  */
#line 677 "parser/parser.y"
                                      { rule_hit("expression_le"); (yyval.ast) = create_binary_op("<=", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2091 "build/y.tab.c"
    break;

  case 70: /* expression: expression T_GE expression  */
#line 678 "parser/parser.y"
                                      { rule_hit("expression_ge"); (yyval.ast) = create_binary_op(">=", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2097 "build/y.tab.c"
    break;

  case 71: /* expression: expression T_AND expression  */
#line 679 "parser/parser.y"
                                      { rule_hit("expression_and"); (yyval.ast) = create_binary_op("e", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2103 "build/y.tab.c"
    break;

  case 72: /* expression: expression T_OR expression  */
#line 680 "parser/parser.y"
                                      { rule_hit("expression_or"); (yyval.ast) = create_binary_op("ou", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2109 "build/y.tab.c"
    break;

  case 73: /* expression: expression T_BIT_OR expression  */
#line 681 "parser/parser.y"
                                      { rule_hit("expression_bit_or"); (yyval.ast) = create_binary_op("|", (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2115 "build/y.tab.c"
    break;

  case 74: /* expression: T_AMPERSAND expression  */
#line 682 "parser/parser.y"
                                     { rule_hit("expression_amp"); (yyval.ast) = create_unary_op("&", (yyvsp[0].ast)); }
#line 2121 "build/y.tab.c"
    break;

  case 75: /* expression: T_NOT expression  */
#line 683 "parser/parser.y"
                                     { rule_hit("expression_not"); (yyval.ast) = create_unary_op("nao", (yyvsp[0].ast)); }
#line 2127 "build/y.tab.c"
    break;

  case 76: /* expression: T_LPAREN expression T_RPAREN  */
#line 684 "parser/parser.y"
                                     { (yyval.ast) = (yyvsp[-1].ast); }
#line 2133 "build/y.tab.c"
    break;

  case 77: /* expression: expression T_DOT T_ID  */
#line 685 "parser/parser.y"
                                      { 
        ASTNode *dot = create_node(NODE_MEMBER_ACCESS, ".");
        add_child(dot, (yyvsp[-2].ast));
        add_child(dot, create_node(NODE_IDENTIFIER, (yyvsp[0].sval)));
        (yyval.ast) = dot;
        free((yyvsp[0].sval));
    }
#line 2145 "build/y.tab.c"
    break;

  case 78: /* expression: expression T_ARROW T_ID  */
#line 692 "parser/parser.y"
                                      { 
        ASTNode *arrow = create_node(NODE_POINTER_ACCESS, "->");
        add_child(arrow, (yyvsp[-2].ast));
        add_child(arrow, create_node(NODE_IDENTIFIER, (yyvsp[0].sval)));
        (yyval.ast) = arrow;
        free((yyvsp[0].sval));
    }
#line 2157 "build/y.tab.c"
    break;

  case 79: /* expression: '*' expression  */
#line 699 "parser/parser.y"
                                      { (yyval.ast) = create_unary_op("*", (yyvsp[0].ast)); }
#line 2163 "build/y.tab.c"
    break;

  case 80: /* expression: function_call  */
#line 700 "parser/parser.y"
                    { (yyval.ast) = (yyvsp[0].ast); }
#line 2169 "build/y.tab.c"
    break;

  case 81: /* printf_statement: T_PRINTF T_LPAREN printf_args T_RPAREN T_SEMICOLON  */
#line 705 "parser/parser.y"
    {
        ASTNode *printf_node = create_node(NODE_PRINTF, NULL);
        add_child(printf_node, (yyvsp[-2].ast));
        (yyval.ast) = printf_node;
    }
#line 2179 "build/y.tab.c"
    break;

  case 82: /* printf_args: expression  */
#line 714 "parser/parser.y"
    {
        rule_hit("printf_args_single");
        ASTNode *args = create_node(NODE_PRINTF_ARGS, NULL);
        add_child(args, (yyvsp[0].ast));
        (yyval.ast) = args;
    }
#line 2190 "build/y.tab.c"
    break;

  case 83: /* printf_args: printf_args T_COMMA expression  */
#line 721 "parser/parser.y"
    {
        rule_hit("printf_args_multiple");
        add_child((yyvsp[-2].ast), (yyvsp[0].ast));
        (yyval.ast) = (yyvsp[-2].ast);
    }
#line 2200 "build/y.tab.c"
    break;


#line 2204 "build/y.tab.c"

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

#line 728 "parser/parser.y"


// Funções auxiliares
ASTNode* create_declaration_node(char *type, char *name, ASTNode *init) {
    ASTNode *decl = create_node(NODE_DECLARATION, name);
    add_child(decl, create_node(NODE_TYPE, type));
    if (init) {
        ASTNode *assign = create_node(NODE_ASSIGNMENT, "=");
        add_child(assign, create_node(NODE_IDENTIFIER, name));
        add_child(assign, init);
        add_child(decl, assign);
    }
    return decl;
}

ASTNode* create_assignment_node(char *op, ASTNode *lhs, ASTNode *rhs) {
    ASTNode *assign = create_node(NODE_ASSIGNMENT, op);
    add_child(assign, lhs);
    add_child(assign, rhs);
    return assign;
}

ASTNode* create_binary_op(char *op, ASTNode *lhs, ASTNode *rhs) {
    ASTNode *binop = create_node(NODE_BINARY_OP, op);
    add_child(binop, lhs);
    add_child(binop, rhs);
    return binop;
}

ASTNode* create_unary_op(char *op, ASTNode *operand) {
    ASTNode *unop = create_node(NODE_UNARY_OP, op);
    add_child(unop, operand);
    return unop;
}

// Mensagem de erro sintático com linha
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}
