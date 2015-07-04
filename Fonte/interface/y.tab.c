/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "../buffend.h"

extern int  yylineno;
extern char* yytext[];
extern FILE * yyin;
extern FILE* outFile_p;
int noerror, col_count, val_count;
int yyparse(rc_parser *parser);
int yylex(rc_parser *parser);
int yylex_destroy();

rc_insert GLOBAL_DATA;
rc_parser GLOBAL_PARSER;

void yyerror(rc_parser *GLOBAL_PARSER, char *s, ...) {
    noerror = 0;
    /*extern yylineno;

    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    */
}

int yywrap() {
    return 1;
}

void connect(char **nome) {
    if (GLOBAL_PARSER.conn_active) {
        printf("Você já está conectado!\n");
        return;
    } else {
    	if (connectDB(*nome) == SUCCESS) {
	        connected.db_name = malloc(sizeof(char)*((strlen(*nome)+1)));

	        strcpylower(connected.db_name, *nome);

	        connected.conn_active = 1;
	    } else {
	    	printf("error: Falha ao conectar no banco.\n");
	    }
    }
}

void setTable(char **nome) {
    if (GLOBAL_PARSER.mode != 0) {
        GLOBAL_PARSER.data->tableName = malloc(sizeof(char)*((strlen(*nome)+1)));

        strcpylower(GLOBAL_PARSER.data->tableName, *nome);
        GLOBAL_PARSER.data->tableName[strlen(*nome)] = '\0';
    } else
        return;
}

void setColumnInsert(char **nome) {
    GLOBAL_DATA.columnName = realloc(GLOBAL_DATA.columnName, (col_count+1)*sizeof(char *));

    GLOBAL_DATA.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.columnName[col_count], *nome);
    GLOBAL_DATA.columnName[col_count][strlen(*nome)] = '\0';

    col_count++;
}

void setColumnCreate(char **nome) {
    GLOBAL_DATA.columnName  = realloc(GLOBAL_DATA.columnName, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.attribute   = realloc(GLOBAL_DATA.attribute, (col_count+1)*sizeof(int));
    GLOBAL_DATA.fkColumn    = realloc(GLOBAL_DATA.fkColumn, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.fkTable     = realloc(GLOBAL_DATA.fkTable, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.values      = realloc(GLOBAL_DATA.values, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.type        = realloc(GLOBAL_DATA.type, (col_count+1)*sizeof(char *));

    GLOBAL_DATA.values[col_count] = malloc(sizeof(char));
    GLOBAL_DATA.values[col_count] = 0;

    GLOBAL_DATA.fkTable[col_count] = malloc(sizeof(char));
    GLOBAL_DATA.fkTable[col_count] = 0;

    GLOBAL_DATA.fkColumn[col_count] = malloc(sizeof(char));
    GLOBAL_DATA.fkColumn[col_count] = 0;

    GLOBAL_DATA.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.columnName[col_count], *nome);
    GLOBAL_DATA.columnName[col_count][strlen(*nome)] = '\0';
    GLOBAL_DATA.type[col_count] = 0;
    GLOBAL_DATA.attribute[col_count] = NPK;

    col_count++;
}

void setColumnTypeCreate(char type) {
    GLOBAL_DATA.type[col_count-1] = type;
}

void setColumnSizeCreate(char *size) {
    GLOBAL_DATA.values[col_count-1] = realloc(GLOBAL_DATA.values[col_count-1], sizeof(char)*(strlen(size)+1));
    strcpy(GLOBAL_DATA.values[col_count-1], size);
    GLOBAL_DATA.values[col_count-1][strlen(size)-1] = '\0';
}

void setColumnPKCreate() {
    GLOBAL_DATA.attribute[col_count-1] = PK;
}

void setColumnFKTableCreate(char **nome) {
    GLOBAL_DATA.fkTable[col_count-1] = realloc(GLOBAL_DATA.fkTable[col_count-1], sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.fkTable[col_count-1], *nome);
    GLOBAL_DATA.fkTable[col_count-1][strlen(*nome)] = '\0';
    GLOBAL_DATA.attribute[col_count-1] = FK;
}

void setColumnFKColumnCreate(char **nome) {
    GLOBAL_DATA.fkColumn[col_count-1] = realloc(GLOBAL_DATA.fkColumn[col_count-1], sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.fkColumn[col_count-1], *nome);
    GLOBAL_DATA.fkColumn[col_count-1][strlen(*nome)] = '\0';
}

void setValueInsert(char *nome, char type) {
    int i;
    GLOBAL_DATA.values  = realloc(GLOBAL_DATA.values, (val_count+1)*sizeof(char *));
    GLOBAL_DATA.type    = realloc(GLOBAL_DATA.type, (val_count+1)*sizeof(char));

    // Adiciona o valor no vetor de strings
    GLOBAL_DATA.values[val_count] = malloc(sizeof(char)*(strlen(nome)+1));
    if (type == 'I') {
        strcpy(GLOBAL_DATA.values[val_count], nome);
        GLOBAL_DATA.values[val_count][strlen(nome)] = '\0';
    } else if (type == 'S') {
        for (i = 1; i < strlen(nome)-1; i++) {
            GLOBAL_DATA.values[val_count][i-1] = nome[i];
        }
        GLOBAL_DATA.values[val_count][strlen(nome)-2] = '\0';
    }

    GLOBAL_DATA.type[val_count] = type;

    val_count++;
}

void clearGlobalStructs() {
    int i;

    if (GLOBAL_DATA.tableName)
        free(GLOBAL_DATA.tableName);
    GLOBAL_DATA.tableName = (char *)malloc(sizeof(char *));

    for (i = 0; i < GLOBAL_DATA.N; i++ ) {
        if (GLOBAL_DATA.columnName)
            free(GLOBAL_DATA.columnName[i]);
        if (GLOBAL_DATA.values)
            free(GLOBAL_DATA.values[i]);
        if (GLOBAL_DATA.fkTable)
            free(GLOBAL_DATA.fkTable[i]);
        if (GLOBAL_DATA.fkColumn)
            free(GLOBAL_DATA.fkColumn[i]);
    }

    free(GLOBAL_DATA.columnName);
    GLOBAL_DATA.columnName = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.columnName = NULL;

    free(GLOBAL_DATA.values);
    GLOBAL_DATA.values = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.values = NULL;

    free(GLOBAL_DATA.fkTable);
    GLOBAL_DATA.fkTable = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.fkTable = NULL;

    free(GLOBAL_DATA.fkColumn);
    GLOBAL_DATA.fkColumn = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.fkColumn = NULL;

    free(GLOBAL_DATA.type);
    GLOBAL_DATA.type = (char *)malloc(sizeof(char));

    free(GLOBAL_DATA.attribute);
    GLOBAL_DATA.attribute = (int *)malloc(sizeof(int));

    yylex_destroy();
    noerror = 1;

    val_count = col_count = GLOBAL_DATA.N = 0;

    GLOBAL_PARSER.data              = &GLOBAL_DATA;
    GLOBAL_PARSER.mode              = 0;
}

void setMode(char mode) {
    GLOBAL_PARSER.mode = mode;
}

/*
void createTable(rc_insert *table) {
    int i;
    printf("Table name: %s\n--------\n", table->tableName);
    for (i = 0; i < table->N; i++) {
        printf("Column: %10s | Type: %c | Size: %5s | Attribute: %c | FK Table: %10s | FK Column: %10s\n",
                table->columnName[i], table->type[i], table->values[i], table->attribute[i], table->fkTable[i], table->fkColumn[i]);
    }
}

void createDatabase(char **nome) {
    printf("Banco de dados '%s' criado.\n", *nome);
}*/


int interface() {
    pthread_t pth;

    pthread_create(&pth, NULL, (void*)clearGlobalStructs, NULL);
    pthread_join(pth, NULL);

    while(1){
        if (!connected.conn_active) {
            printf(">");
        } else {
            printf("%s=# ", connected.db_name);
        }

        pthread_create(&pth, NULL, (void*)yyparse, &GLOBAL_PARSER);
        pthread_join(pth, NULL);

        if (noerror) {
            if (GLOBAL_PARSER.mode != 0) {
                if (!connected.conn_active) {
                    printf("Você não está conectado. Utilize \\c <nome_banco> para conectar.\n");
                } else {
                    if (GLOBAL_PARSER.mode == 'I') {
                        if (GLOBAL_PARSER.data->N > 0)
                            insert(&GLOBAL_DATA);
                    } else if (GLOBAL_PARSER.mode == 'S') {
                        imprime(GLOBAL_DATA.tableName);
                    } else if (GLOBAL_PARSER.mode == 'C') {
                        createTable(&GLOBAL_DATA);
                    }
                }
            }
        } else {
            printf("Erro sintático, verifique.\n");
        }

        pthread_create(&pth, NULL, (void*)clearGlobalStructs, NULL);
        pthread_join(pth, NULL);
    }
    return 0;
}


#line 326 "y.tab.c" /* yacc.c:339  */

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
    INSERT = 258,
    INTO = 259,
    VALUES = 260,
    SELECT = 261,
    FROM = 262,
    CREATE = 263,
    TABLE = 264,
    INTEGER = 265,
    VARCHAR = 266,
    DOUBLE = 267,
    PRIMARY = 268,
    KEY = 269,
    REFERENCES = 270,
    DATABASE = 271,
    DROP = 272,
    OBJECT = 273,
    NUMBER = 274,
    VALUE = 275,
    QUIT = 276,
    LIST_TABLES = 277,
    LIST_TABLE = 278,
    ALPHANUM = 279,
    CONNECT = 280,
    HELP = 281
  };
#endif
/* Tokens.  */
#define INSERT 258
#define INTO 259
#define VALUES 260
#define SELECT 261
#define FROM 262
#define CREATE 263
#define TABLE 264
#define INTEGER 265
#define VARCHAR 266
#define DOUBLE 267
#define PRIMARY 268
#define KEY 269
#define REFERENCES 270
#define DATABASE 271
#define DROP 272
#define OBJECT 273
#define NUMBER 274
#define VALUE 275
#define QUIT 276
#define LIST_TABLES 277
#define LIST_TABLE 278
#define ALPHANUM 279
#define CONNECT 280
#define HELP 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 261 "yacc.y" /* yacc.c:355  */

    int intval;
    double floatval;
    int subtok;
    char *strval;

#line 425 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (rc_parser *GLOBAL_PARSER);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 440 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   66

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  88

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

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
      27,    28,    31,     2,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   279,   279,   279,   279,   279,   279,   280,   280,   280,
     280,   280,   281,   281,   288,   291,   294,   303,   312,   319,
     319,   329,   331,   333,   333,   335,   335,   337,   339,   339,
     341,   342,   343,   346,   346,   352,   352,   354,   355,   355,
     356,   358,   360,   361,   362,   364,   366,   369,   372,   375,
     375,   377
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INSERT", "INTO", "VALUES", "SELECT",
  "FROM", "CREATE", "TABLE", "INTEGER", "VARCHAR", "DOUBLE", "PRIMARY",
  "KEY", "REFERENCES", "DATABASE", "DROP", "OBJECT", "NUMBER", "VALUE",
  "QUIT", "LIST_TABLES", "LIST_TABLE", "ALPHANUM", "CONNECT", "HELP",
  "'('", "')'", "';'", "','", "'*'", "$accept", "start", "connection",
  "exit_program", "table_attr", "list_tables", "help_pls", "insert", "$@1",
  "semicolon", "table", "opt_column_list", "column_list", "column",
  "value_list", "value", "create_table", "$@2", "table_column_attr",
  "type", "$@3", "column_create", "attribute", "table_fk", "column_fk",
  "drop_table", "create_database", "select", "$@4", "table_select", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    40,    41,    59,
      44,    42
};
# endif

#define YYPACT_NINF -44

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-44)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,     7,   -44,    -7,     1,   -44,   -44,    -4,     4,   -44,
     -44,    25,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,    -5,   -44,    10,    12,   -44,   -44,
     -44,    13,    26,    13,   -44,   -44,   -44,     5,    16,     8,
      18,    32,   -44,     9,    21,   -44,    14,    11,    17,   -44,
     -44,    15,     6,   -44,    18,   -12,     9,   -44,   -44,   -44,
     -10,   -44,   -44,   -44,   -44,    19,    20,   -44,    22,    31,
      28,    23,     9,   -12,    29,   -44,   -44,    24,    21,   -44,
     -44,    27,    34,   -44,   -44,   -44,    30,   -44
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      13,     0,    49,     0,     0,    15,    17,     0,     0,    18,
      21,     0,     9,    10,     7,     8,    12,     2,    11,     4,
       6,     5,     3,    19,     0,    33,     0,     0,    16,    14,
       1,     0,     0,     0,    48,    47,    22,    23,     0,     0,
       0,     0,    51,     0,     0,    27,     0,    25,     0,    50,
      41,     0,     0,    24,     0,     0,     0,    37,    38,    40,
      42,    26,    31,    30,    32,     0,    28,    34,     0,     0,
       0,    35,     0,     0,     0,    43,    45,     0,     0,    20,
      29,     0,     0,    36,    39,    46,     0,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -43,
      33,   -44,   -14,   -44,   -19,   -44,   -44,   -44,   -22,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    15,    16,    17,    31,    18,
      37,    41,    46,    47,    65,    66,    19,    33,    51,    60,
      68,    52,    71,    77,    86,    20,    21,    22,    24,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,     1,    25,    69,     2,    70,     3,    62,    63,    26,
      27,    23,    64,    67,    28,     4,    57,    58,    59,     5,
       6,     7,    29,     8,     9,    30,    32,    10,    34,    79,
      35,    36,    40,    38,    42,    44,    45,    48,    10,    50,
      61,    54,    53,    56,    55,    75,    76,    72,    81,    74,
      73,    82,    85,    78,    80,    84,    83,     0,    87,     0,
       0,     0,     0,     0,     0,     0,    39
};

static const yytype_int8 yycheck[] =
{
      43,     3,     9,    13,     6,    15,     8,    19,    20,    16,
       9,     4,    24,    56,    18,    17,    10,    11,    12,    21,
      22,    23,    18,    25,    26,     0,    31,    29,    18,    72,
      18,    18,    27,     7,    18,    27,    18,     5,    29,    18,
      54,    30,    28,    28,    27,    14,    18,    28,    19,    27,
      30,    27,    18,    30,    73,    28,    78,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     8,    17,    21,    22,    23,    25,    26,
      29,    33,    34,    35,    36,    37,    38,    39,    41,    48,
      57,    58,    59,     4,    60,     9,    16,     9,    18,    18,
       0,    40,    31,    49,    18,    18,    18,    42,     7,    42,
      27,    43,    18,    61,    27,    18,    44,    45,     5,    41,
      18,    50,    53,    28,    30,    27,    28,    10,    11,    12,
      51,    44,    19,    20,    24,    46,    47,    41,    52,    13,
      15,    54,    28,    30,    27,    14,    18,    55,    30,    41,
      46,    19,    27,    50,    28,    18,    56,    28
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    34,    35,    36,    37,    38,    40,
      39,    41,    42,    43,    43,    44,    44,    45,    46,    46,
      47,    47,    47,    49,    48,    50,    50,    51,    52,    51,
      51,    53,    54,    54,    54,    55,    56,    57,    58,    60,
      59,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     1,     2,     1,     1,     0,
      10,     1,     1,     0,     3,     1,     3,     1,     1,     3,
       1,     1,     1,     0,     8,     3,     5,     1,     0,     5,
       1,     1,     0,     2,     5,     1,     1,     3,     3,     0,
       6,     1
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
      yyerror (GLOBAL_PARSER, YY_("syntax error: cannot back up")); \
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
                  Type, Value, GLOBAL_PARSER); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, rc_parser *GLOBAL_PARSER)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (GLOBAL_PARSER);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, rc_parser *GLOBAL_PARSER)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, GLOBAL_PARSER);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, rc_parser *GLOBAL_PARSER)
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
                                              , GLOBAL_PARSER);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, GLOBAL_PARSER); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, rc_parser *GLOBAL_PARSER)
{
  YYUSE (yyvaluep);
  YYUSE (GLOBAL_PARSER);
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
yyparse (rc_parser *GLOBAL_PARSER)
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
      yychar = yylex (GLOBAL_PARSER);
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
        case 11:
#line 280 "yacc.y" /* yacc.c:1646  */
    {return 0;}
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 288 "yacc.y" /* yacc.c:1646  */
    {connect(yytext); return 0;}
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 291 "yacc.y" /* yacc.c:1646  */
    {exit(0);}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 294 "yacc.y" /* yacc.c:1646  */
    {
    if(connected.conn_active)
        printTable(yylval.strval);
    else
        printf("Você não está conectado\n");
    return 0;
}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 303 "yacc.y" /* yacc.c:1646  */
    {
    if(connected.conn_active)
        printTable(NULL);
    else
        printf("Você não está conectado\n");
    return 0;
}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 312 "yacc.y" /* yacc.c:1646  */
    {help(); return 0;}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 319 "yacc.y" /* yacc.c:1646  */
    {setMode('I');}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 319 "yacc.y" /* yacc.c:1646  */
    {
    if (col_count == val_count || GLOBAL_DATA.columnName == NULL)
        GLOBAL_DATA.N = val_count;
    else {
        printf("The column counter doesn't match the value counter.\n");
        noerror=0;
    }
    return 0;
}
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 331 "yacc.y" /* yacc.c:1646  */
    {setTable(yytext);}
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 337 "yacc.y" /* yacc.c:1646  */
    {setColumnInsert(yytext);}
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 341 "yacc.y" /* yacc.c:1646  */
    {setValueInsert(yylval.strval, 'I');}
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 342 "yacc.y" /* yacc.c:1646  */
    {setValueInsert(yylval.strval, 'I');}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 343 "yacc.y" /* yacc.c:1646  */
    {setValueInsert(yylval.strval, 'S');}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 346 "yacc.y" /* yacc.c:1646  */
    {setMode('C');}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 346 "yacc.y" /* yacc.c:1646  */
    {
    GLOBAL_DATA.N = col_count;

    return 0;
}
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 354 "yacc.y" /* yacc.c:1646  */
    {setColumnTypeCreate('I');}
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 355 "yacc.y" /* yacc.c:1646  */
    {setColumnTypeCreate('S');}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 355 "yacc.y" /* yacc.c:1646  */
    {setColumnSizeCreate(yylval.strval);}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 356 "yacc.y" /* yacc.c:1646  */
    {setColumnTypeCreate('D');}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 358 "yacc.y" /* yacc.c:1646  */
    {setColumnCreate(yytext);}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 361 "yacc.y" /* yacc.c:1646  */
    {setColumnPKCreate();}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 364 "yacc.y" /* yacc.c:1646  */
    {setColumnFKTableCreate(yytext);}
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 366 "yacc.y" /* yacc.c:1646  */
    {setColumnFKColumnCreate(yytext);}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 369 "yacc.y" /* yacc.c:1646  */
    {excluirTabela(*yytext); return 0;}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 372 "yacc.y" /* yacc.c:1646  */
    {createDB(*yytext); return 0;}
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 375 "yacc.y" /* yacc.c:1646  */
    {setMode('S');}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 375 "yacc.y" /* yacc.c:1646  */
    {return 0;}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 377 "yacc.y" /* yacc.c:1646  */
    {setTable(yytext);}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1766 "y.tab.c" /* yacc.c:1646  */
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
      yyerror (GLOBAL_PARSER, YY_("syntax error"));
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
        yyerror (GLOBAL_PARSER, yymsgp);
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
                      yytoken, &yylval, GLOBAL_PARSER);
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
                  yystos[yystate], yyvsp, GLOBAL_PARSER);
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
  yyerror (GLOBAL_PARSER, YY_("memory exhausted"));
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
                  yytoken, &yylval, GLOBAL_PARSER);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, GLOBAL_PARSER);
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
#line 380 "yacc.y" /* yacc.c:1906  */

