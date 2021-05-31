/* lexer1.lex            see license.txt for copyright and terms of use
   flex scanner for Lexer 1 of C++ compiler
   see lexer1.txt for specification */

%smflex 101

/******************/
/* C declarations */
/******************/

%header{
#include "lexer1.h"        /* Lexer1 */
%}

/****************/
/* flex options */
/****************/

%option prefix="lexer1"

/* Interface to the lexer. */
%option yy_lex_name="lexer1_inner_lex"
%option yy_lex_parameters="Lexer1 &lexer"


/********************/
/* C++ declarations */
/********************/

  #include "growbuf.h"       // GrowBuffer
  GrowBuffer collector;      // place to assemble big tokens

  // used for 2nd and 3rd arguments to lexer1Emit
  #define COLLECTOR (char*)collector.getDataC(), collector.getDataLen()


/***************/
/* sub-regexps */
/***************/

/* newline */
NL            "\n"

/* anything but newline */
NOTNL         .

/* any of 256 source characters */
ANY           ({NOTNL}|{NL})

/* backslash */
BACKSL        "\\"

/* beginnging of line (must be start of a pattern) */
BOL           ^

/* end of line (would like EOF to qualify also, but flex doesn't allow it */
EOL           {NL}

/* letter or underscore */
LETTER        [A-Za-z_]

/* letter or underscore or digit */
ALNUM         [A-Za-z_0-9]

/* decimal digit */
DIGIT         [0-9]

/* sequence of decimal digits */
DIGITS        ({DIGIT}+)

/* sign of a number */
SIGN          ("+"|"-")

/* integer suffix */
/* added 'LL' option for GNU long long compatibility.. */
ELL_SUFFIX    [lL]([lL]?)
INT_SUFFIX    ([uU]{ELL_SUFFIX}?|{ELL_SUFFIX}[uU]?)

/* floating-point suffix letter */
FLOAT_SUFFIX  [flFL]

/* normal string character: any but quote, newline, or backslash */
STRCHAR       [^\"\n\\]

/* (start of) an escape sequence */
ESCAPE        ({BACKSL}{ANY})

/* double quote */
QUOTE         [\"]

/* normal character literal character: any but single-quote, newline, or backslash */
CCCHAR        [^\'\n\\]

/* single quote */
TICK          [\']

/* space or tab */
SPTAB         [ \t]

/* preprocessor "character" -- any but escaped newline */
PPCHAR        ([^\\\n]|{BACKSL}{NOTNL})


/********************/
/* start conditions */
/********************/

%x ST_C_COMMENT
%x ST_STRING


/**************************/
/* token definition rules */
/**************************/
%%

  /* identifier: e.g. foo */
{LETTER}{ALNUM}* {
  lexer.emit(L1_IDENTIFIER, YY_TEXT, YY_LENG);
}

  /* integer literal; dec, oct, or hex */
[1-9][0-9]*{INT_SUFFIX}?           |
[0][0-7]*{INT_SUFFIX}?             |
[0][xX][0-9A-Fa-f]+{INT_SUFFIX}?   {
  lexer.emit(L1_INT_LITERAL, YY_TEXT, YY_LENG);
}

  /* floating literal */
{DIGITS}"."{DIGITS}?([eE]{SIGN}?{DIGITS})?{FLOAT_SUFFIX}?   |
{DIGITS}"."?([eE]{SIGN}?{DIGITS})?{FLOAT_SUFFIX}?           |
"."{DIGITS}([eE]{SIGN}?{DIGITS})?{FLOAT_SUFFIX}?            {
  lexer.emit(L1_FLOAT_LITERAL, YY_TEXT, YY_LENG);
}

  /* ----- string literal ------- */
  /* intial */
"L"?{QUOTE}   {
  collector.setFromBlock(YY_TEXT, YY_LENG);
  YY_SET_START_CONDITION(ST_STRING);
}

  /* continuation */
<ST_STRING>({STRCHAR}|{ESCAPE})*   {
  collector.append(YY_TEXT, YY_LENG);
}

  /* final */
<ST_STRING>{QUOTE} {
  collector.append(YY_TEXT, YY_LENG);
  lexer.emit(L1_STRING_LITERAL, COLLECTOR);
  YY_SET_START_CONDITION(INITIAL);
}

  /* dsw: user-defined qualifier; example: $tainted */
\${ALNUM}+ {
  lexer.emit(L1_UDEF_QUAL, YY_TEXT, YY_LENG);
}

  /* final, error */
<ST_STRING>{EOL}   |
<ST_STRING><<EOF>> {
  if (YY_TEXT[0] == '\n') {
    collector.append(YY_TEXT, YY_LENG);
  }
  else {
    // when matching <<EOF>>, YY_TEXT[0]=0 and YY_LENG=1 (possibly
    // a bug in flex; its man page doesn't specify what it does), so we
    // get an extra NUL in the collected token, which I don't want
  }

  if (!lexer.allowMultilineStrings) {
    lexer.error("unterminated string literal");
    lexer.emit(L1_STRING_LITERAL, COLLECTOR);
    YY_SET_START_CONDITION(INITIAL);
  }

  if (YY_TEXT[0] != '\n') {
    YY_TERMINATE();       // flex man page says to do this for <<EOF>>
  }
}


  /* character literal */
"L"?{TICK}({CCCHAR}|{ESCAPE})*{TICK}   {
  lexer.emit(L1_CHAR_LITERAL, YY_TEXT, YY_LENG);
}


  /* operator */
  /* extensions for theorem prover: "==>" */
"("|")"|"["|"]"|"->"|"::"|"."|"!"|"~"|"+"|"-"|"++"|"--"|"&"|"*"  |
".*"|"->*"|"/"|"%"|"<<"|">>"|"<"|"<="|">"|">="                   |
"=="|"!="|"^"|"|"|"&&"|"||"|"?"|":"|"="|"*="|"/="|"%="|"+="      |
"-="|"&="|"^="|"|="|"<<="|">>="|","|"..."|";"|"{"|"}"|"==>"      {
  lexer.emit(L1_OPERATOR, YY_TEXT, YY_LENG);
}

  /* preprocessor */
  /* technically, if this isn't at the start of a line (possibly after
   * some whitespace, it should be an error.. I'm not sure right now how
   * I want to deal with that (I originally was using '^', but that
   * interacts badly with the whitespace rule) */
"#"{PPCHAR}*({BACKSL}{NL}{PPCHAR}*)*   {
  lexer.emit(L1_PREPROCESSOR, YY_TEXT, YY_LENG);
}

  /* whitespace */
  /* 10/20/02: added '\r' to accomodate files coming from Windows */
[ \t\n\f\v\r]+  {
  lexer.emit(L1_WHITESPACE, YY_TEXT, YY_LENG);
}

  /* C++ comment */
  /* we don't match the \n because that way this works at EOF */
"//"{NOTNL}*    {
  lexer.emit(L1_COMMENT, YY_TEXT, YY_LENG);
}

  /* ------- C comment --------- */
  /* initial */
"/""*"     {
  collector.setFromBlock(YY_TEXT, YY_LENG);
  YY_SET_START_CONDITION(ST_C_COMMENT);
}

  /* continuation */
<ST_C_COMMENT>([^*]|"*"[^/])*   {
  collector.append(YY_TEXT, YY_LENG);
}

  /* final */
<ST_C_COMMENT>"*/"     {
  collector.append(YY_TEXT, YY_LENG);
  lexer.emit(L1_COMMENT, COLLECTOR);
  YY_SET_START_CONDITION(INITIAL);
}

  /* final, error */
<ST_C_COMMENT><<EOF>>     {
  lexer.error("unterminated /**/ comment");
  lexer.emit(L1_COMMENT, COLLECTOR);
  YY_SET_START_CONDITION(INITIAL);
}

  /* illegal */
.  {
  lexer.emit(L1_ILLEGAL, YY_TEXT, YY_LENG);
}


%%
/**************/
/* extra code */
/**************/


/* wrapper around main lex routine to do init */
int lexer1_lex(Lexer1 &lexer, FILE *inputFile)
{
  lexer1_lexer_t lexState;
  lexer1_construct(&lexState);
  lexer1_restart(&lexState, inputFile);

  // this collects all the tokens
  int ret = lexer1_inner_lex(&lexState, lexer);

  // Clean up.
  lexer1_destroy(&lexState);

  return ret;
}



/*********/
/* trash */
/*********/
#if 0

  /* Notes
   *
   * 1) Contrary to usual lexer practice, I want this lexer to match potentially huge
   *    tokens, like entire blocks of C comments.  This is because I want those
   *    to become single L1 tokens, and it's easier to let flex create them
   *    (inefficiently) than to go write code to do so efficiently.  I'd reconsider
   *    if I decided some tool (like an editor) would rather break comments up into
   *    smaller pieces.
   *
   * 2) To avoid backtracking over these large tokens, they all have rules to cover
   *    all the possible endings, including <<EOF>>.
   */

{QUOTE}({STRCHAR}|{ESCAPE})*{QUOTE}   {
  lexer.emit(L1_STRING_LITERAL);
}

  /* unterminated string literal */
{QUOTE}({STRCHAR}|{ESCAPE})*{EOL}     |
{QUOTE}({STRCHAR}|{ESCAPE})*<<EOF>>   {
  lexer.emit(L1_STRING_LITERAL);
}


  /* unterminated character literal */
{TICK}({CCCHAR}|{ESCAPE})*{EOL}     |
{TICK}({CCCHAR}|{ESCAPE})*<<EOF>>   {
  lexer.error("unterminated character literal");
  lexer.emit(L1_CHAR_LITERAL);
}

%x ST_PREPROC

  /* ------- preprocessor ---------- */
  /* initial */
{BOL}{SPTAB}*"#"    {
  collector.setFromBlock(YY_TEXT, YY_LENG);
  YY_SET_START_CONDITION(ST_PREPROC);
}

  /* continuation */
<ST_PREPROC>({BACKSL}{NL}|{PPCHAR})+     {
  collector.append(YY_TEXT, YY_LENG);
}

  /* final */
<ST_PREPROC>{EOL}   |
<ST_PREPROC><<EOF>> {
  collector.append(YY_TEXT, YY_LENG);
  lexer.emit(L1_PREPROCESSOR, COLLECTOR);
  YY_SET_START_CONDITION(INITIAL);
}


#endif // 0


