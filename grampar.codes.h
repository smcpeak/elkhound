  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_INTEGER = 258,             /* TOK_INTEGER  */
    TOK_NAME = 259,                /* TOK_NAME  */
    TOK_STRING = 260,              /* TOK_STRING  */
    TOK_LIT_CODE = 261,            /* TOK_LIT_CODE  */
    TOK_LBRACE = 262,              /* "{"  */
    TOK_RBRACE = 263,              /* "}"  */
    TOK_COLON = 264,               /* ":"  */
    TOK_SEMICOLON = 265,           /* ";"  */
    TOK_ARROW = 266,               /* "->"  */
    TOK_LPAREN = 267,              /* "("  */
    TOK_RPAREN = 268,              /* ")"  */
    TOK_COMMA = 269,               /* ","  */
    TOK_TERMINALS = 270,           /* "terminals"  */
    TOK_TOKEN = 271,               /* "token"  */
    TOK_NONTERM = 272,             /* "nonterm"  */
    TOK_FUN = 273,                 /* "fun"  */
    TOK_VERBATIM = 274,            /* "verbatim"  */
    TOK_IMPL_VERBATIM = 275,       /* "impl_verbatim"  */
    TOK_PRECEDENCE = 276,          /* "precedence"  */
    TOK_PRECEDENCE_PREFER_SHIFT = 277, /* "precedence_prefer_shift"  */
    TOK_OPTION = 278,              /* "option"  */
    TOK_EXPECT = 279,              /* "expect"  */
    TOK_CONTEXT_CLASS = 280,       /* "context_class"  */
    TOK_SUBSETS = 281,             /* "subsets"  */
    TOK_DELETE = 282,              /* "delete"  */
    TOK_REPLACE = 283,             /* "replace"  */
    TOK_FORBID_NEXT = 284          /* "forbid_next"  */
  };
