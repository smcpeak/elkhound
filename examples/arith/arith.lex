/* arith.lex
 * lexical analyzer for arithmetic language */

%smflex 101


/* C++ declarations */
  #include "arith.h"       // lexer, ArithTokenCodes


/* token definitions */
%%

[0-9]+      {
  lexer.sval = (SemanticValue)atoi(YY_TEXT);
  return TOK_NUMBER;
}

  /* operators, punctuators */
"+"         { return TOK_PLUS; }
"-"         { return TOK_MINUS; }
"*"         { return TOK_TIMES; }
"/"         { return TOK_DIVIDE; }
"("         { return TOK_LPAREN; }
")"         { return TOK_RPAREN; }

[ \t\n]     {
  /* whitespace; ignore */
}

"#.*\n"     {
  /* comment; ignore */
}

.           {
  printf("illegal character: %c\n", YY_TEXT[0]);
  /* but continue anyway */
}
