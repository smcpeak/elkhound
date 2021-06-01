// arith.h
// declarations shared across the arith evaluator

#ifndef ARITH_H
#define ARITH_H

#include "lexerint.h"        // LexerInterface
#include "arith.gr.gen.h"    // Arith, the parser context class
#include "arithyy.h"         // yy_lex, yy_lexer_t

class ParseTables;           // parsetables.h
class UserActions;           // useract.h



// interface to the parser generator's output;
// defined in arith.gr -> arith.gr.gen.cc
UserActions *makeUserActions();
ParseTables *make_Arith_tables();


// token codes
enum ArithTokenCodes {
  TOK_EOF    =0,
  TOK_NUMBER =1,
  TOK_PLUS   =2,
  TOK_MINUS  =3,
  TOK_TIMES  =4,
  TOK_DIVIDE =5,
  TOK_LPAREN =6,
  TOK_RPAREN =7,
};

char const *toString(ArithTokenCodes code);


// lexer interface object
class ArithLexer : public LexerInterface {
private:     // data
  yy_lexer_t lexerState;

public:      // methods
  ArithLexer();
  ~ArithLexer();

  static void nextToken(ArithLexer *ths);

  // LexerInterface functions
  virtual NextTokenFunc getTokenFunc() const;
  virtual string tokenDesc() const;
  virtual string tokenKindDesc(int kind) const;
};

// there will be only one
extern ArithLexer lexer;



#endif // ARITH_H
