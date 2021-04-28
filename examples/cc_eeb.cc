// cc_eeb.cc
// *** DO NOT EDIT BY HAND ***
// automatically generated by gramanl, from cc_eeb.gr

// GLR source location information is enabled

#include "cc_eeb.h"     // EEB
#include "parsetables.h" // ParseTables
#include "srcloc.h"      // SourceLoc

#include <assert.h>      // assert
#include <iostream.h>    // cout
#include <stdlib.h>      // abort

static char const *termNames[] = {
  "TOK_EOF",  // 0
  "TOK_PLUS",  // 1
  "TOK_B",  // 2
};

string EEB::terminalDescription(int termId, SemanticValue sval)
{
  return stringc << termNames[termId]
                 << "(" << (sval % 100000) << ")";
}


static char const *nontermNames[] = {
  "empty",  // 0
  "__EarlyStartSymbol",  // 1
  "E",  // 2
};

string EEB::nonterminalDescription(int nontermId, SemanticValue sval)
{
  return stringc << nontermNames[nontermId]
                 << "(" << (sval % 100000) << ")";
}


char const *EEB::terminalName(int termId)
{
  return termNames[termId];
}

char const *EEB::nonterminalName(int nontermId)
{
  return nontermNames[nontermId];
}

// ------------------- actions ------------------
// [0] __EarlyStartSymbol[Node*] -> top:E TOK_EOF
inline Node* EEB::action0___EarlyStartSymbol(SourceLoc loc, Node* top)
#line 507 "grampar.cc"
{ return top;  }
#line 57 "cc_eeb.cc"

// [1] E[Node*] -> e1:E + e2:E
inline Node* EEB::action1_E(SourceLoc loc, Node* e1, Node* e2)
#line 18 "cc_eeb.gr"
{ return new PlusNode(e1, e2);  }
#line 63 "cc_eeb.cc"

// [2] E[Node*] -> b:b
inline Node* EEB::action2_E(SourceLoc loc, int b)
#line 19 "cc_eeb.gr"
{ return new LeafNode(b);  }
#line 69 "cc_eeb.cc"


/*static*/ SemanticValue EEB::doReductionAction(
  EEB *ths,
  int productionId, SemanticValue const *semanticValues,
  SourceLoc loc)
{
  switch (productionId) {
    case 0:
      return (SemanticValue)(ths->action0___EarlyStartSymbol(loc, (Node*)(semanticValues[0])));
    case 1:
      return (SemanticValue)(ths->action1_E(loc, (Node*)(semanticValues[0]), (Node*)(semanticValues[2])));
    case 2:
      return (SemanticValue)(ths->action2_E(loc, (int)(semanticValues[0])));
    default:
      assert(!"invalid production code");
      return (SemanticValue)0;   // silence warning
  }
}

UserActions::ReductionActionFunc EEB::getReductionAction()
{
  return (ReductionActionFunc)&EEB::doReductionAction;
}


// ---------------- dup/del/merge/keep nonterminals ---------------

inline Node* EEB::dup_E(Node* n)
#line 14 "cc_eeb.gr"
{ n->incRefCt();  }
#line 101 "cc_eeb.cc"

inline void EEB::del_E(Node* n)
#line 15 "cc_eeb.gr"
{ n->delRefCt();  }
#line 106 "cc_eeb.cc"

inline Node* EEB::merge_E(Node* a, Node* b)
#line 16 "cc_eeb.gr"
{ return pickLeftAssocTree(a,b);  }
#line 111 "cc_eeb.cc"

SemanticValue EEB::duplicateNontermValue(int nontermId, SemanticValue sval)
{
  switch (nontermId) {
    case 2:
      return (SemanticValue)dup_E((Node*)sval);
    default:
      return (SemanticValue)0;
  }
}

void EEB::deallocateNontermValue(int nontermId, SemanticValue sval)
{
  switch (nontermId) {
    case 2:
      del_E((Node*)sval);
      return;
    default:
      cout << "WARNING: there is no action to deallocate nonterm "
           << nontermNames[nontermId] << endl;
  }
}

SemanticValue EEB::mergeAlternativeParses(int nontermId, SemanticValue left,
                                           SemanticValue right,  SourceLoc loc)
{
  switch (nontermId) {
    case 2:
      return (SemanticValue)merge_E((Node*)left, (Node*)right);
    default:
      cout << toString(loc)
           << ": WARNING: there is no action to merge nonterm "
           << nontermNames[nontermId] << endl;
      return left;
  }
}

bool EEB::keepNontermValue(int nontermId, SemanticValue sval)
{
  switch (nontermId) {
    default:
      return true;
  }
}


// ---------------- dup/del/classify terminals ---------------
SemanticValue EEB::duplicateTerminalValue(int termId, SemanticValue sval)
{
  switch (termId) {
    default:
      return (SemanticValue)0;
  }
}

void EEB::deallocateTerminalValue(int termId, SemanticValue sval)
{
  switch (termId) {
    default:
      cout << "WARNING: there is no action to deallocate terminal "
           << termNames[termId] << endl;
  }
}

/*static*/ int EEB::reclassifyToken(EEB *ths, int oldTokenType, SemanticValue sval)
{
  switch (oldTokenType) {
    default:
      return oldTokenType;
  }
}

UserActions::ReclassifyFunc EEB::getReclassifier()
{
  return (ReclassifyFunc)&EEB::reclassifyToken;
}


// this makes a ParseTables from some literal data;
// the code is written by ParseTables::emitConstructionCode()
// in parsetables.cc
class EEB_ParseTables : public ParseTables {
public:
  EEB_ParseTables();
};

EEB_ParseTables::EEB_ParseTables()
  : ParseTables(false /*owning*/)
{
  numTerms = 3;
  numNonterms = 3;
  numStates = 6;
  numProds = 3;
  actionCols = 3;
  actionRows = 6;
  gotoCols = 3;
  gotoRows = 6;
  ambigTableSize = 3;
  startState = (StateId)0;
  finalProductionIndex = 0;
  bigProductionListSize = 0;
  errorBitsRowSize = 4;
  uniqueErrorRows = 0;

  static ActionEntry const actionTable_static[18] = {
    /*0*/ 0, 0, 4,
    /*1*/ 0, 0, 0,
    /*2*/ 0, 0, 4,
    /*3*/ -3, -3, 0,
    /*4*/ 2, 3, 0,
    /*5*/ -2, 7, 0,
  };
  actionTable = const_cast<ActionEntry*>(actionTable_static);

  static GotoEntry const gotoTable_static[18] = {
    /*0*/ 65535, 65535, 4,
    /*1*/ 65535, 65535, 65535,
    /*2*/ 65535, 65535, 5,
    /*3*/ 65535, 65535, 65535,
    /*4*/ 65535, 65535, 65535,
    /*5*/ 65535, 65535, 65535,
  };
  gotoTable = const_cast<GotoEntry*>(gotoTable_static);

  static ParseTables::ProdInfo const prodInfo_static[3] = {
    /*0*/ {2,1}, {3,2}, {1,2},
  };
  prodInfo = const_cast<ParseTables::ProdInfo*>(prodInfo_static);

  static SymbolId const stateSymbol_static[6] = {
    /*0*/ 0, 1, 2, 3, -3, -3,
  };
  stateSymbol = const_cast<SymbolId*>(stateSymbol_static);

  static ActionEntry const ambigTable_static[3] = {
    /*0*/ 2, 3, -2,
  };
  ambigTable = const_cast<ActionEntry*>(ambigTable_static);

  static NtIndex const nontermOrder_static[3] = {
    /*0*/ 2, 1, 0,
  };
  nontermOrder = const_cast<NtIndex*>(nontermOrder_static);

  ErrorBitsEntry *errorBits_static = NULL;
  errorBits = const_cast<ErrorBitsEntry*>(errorBits_static);

  errorBitsPointers = NULL;

  TermIndex *actionIndexMap_static = NULL;
  actionIndexMap = const_cast<TermIndex*>(actionIndexMap_static);

  actionRowPointers = NULL;

  NtIndex *gotoIndexMap_static = NULL;
  gotoIndexMap = const_cast<NtIndex*>(gotoIndexMap_static);

  gotoRowPointers = NULL;

  firstWithTerminal = NULL;
  firstWithNonterminal = NULL;
  bigProductionList = NULL;
  productionsForState = NULL;
  ambigStateTable = NULL;
}


ParseTables *EEB::makeTables()
{
  return new EEB_ParseTables;
}

