// ptreeact.h            see license.txt for copyright and terms of use
// a generic set of user actions that build parse trees for any grammar

#ifndef PTREEACT_H
#define PTREEACT_H

#include "lexerint.h"      // LexerInterface
#include "useract.h"       // UserActions

class ParseTables;         // parsetables.h


// lexer to yield PTreeNodes for tokens
class ParseTreeLexer : public LexerInterface {
private:
  LexerInterface *underlying;   // for getting token descriptions
  NextTokenFunc underToken;     // for getting tokens
  UserActions *actions;         // for getting symbol names

private:
  void copyFields();

public:
  ParseTreeLexer(LexerInterface *u, UserActions *a);

  static void nextToken(LexerInterface *lex);
  virtual NextTokenFunc getTokenFunc() const override
    { return &ParseTreeLexer::nextToken; }

  virtual string tokenDesc() const override;
  virtual string tokenKindDesc(int kind) const override;
};


// layer these actions on top of the generated actions to
// build parse trees for the reductions
class ParseTreeActions : public TrivialUserActions {
private:
  UserActions *underlying;   // for getting symbol names
  ParseTables *tables;       // for finding out production lengths

public:
  ParseTreeActions(UserActions *u, ParseTables *t)
    : underlying(u), tables(t) {}

  static SemanticValue reduce(
    UserActions *context,
    int productionId,
    SemanticValue const *svals
    SOURCELOCARG( SourceLoc loc ) );
  virtual ReductionActionFunc getReductionAction() override
    { return &ParseTreeActions::reduce; }

  virtual SemanticValue mergeAlternativeParses(
    int ntIndex, SemanticValue left, SemanticValue right
    SOURCELOCARG( SourceLoc loc ) ) override;

  virtual char const *terminalName(int termId) override;
  virtual char const *nonterminalName(int termId) override;

  ParseTables *getTables() { return tables; }
};


#endif // PTREEACT_H
