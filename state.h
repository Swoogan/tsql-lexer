#ifndef STATE_H
#define STATE_H

#include <QSharedPointer>
#include "item_type.h"
#include "state_type.h"

class Lexer;

struct State {
    virtual StateType Execute(Lexer *lex) = 0;
    virtual ~State() {}
};

struct LexStatement : public State {
    StateType Execute(Lexer *lex);
    void CheckForEquals(Lexer *lex, ItemType with, ItemType without);
};

struct SelectStatement : public State {
    StateType Execute(Lexer *lex);
};

struct LexIdentifier : public State {
    StateType Execute(Lexer *lex);
};

struct LexQuotedIdentifier : public State {
    StateType Execute(Lexer *lex);
};

struct LexBracketedIdentifier : public State {
    StateType Execute(Lexer *lex);
};

struct LexNumber : public State {
    StateType Execute(Lexer *lex);
};

struct LexSpace : public State {
    StateType Execute(Lexer *lex);
};

struct LexString : public State {
    StateType Execute(Lexer *lex);
};

struct LexUnicodeString : public State {
    StateType Execute(Lexer *lex);
};

struct LexLessThan : public State {
    StateType Execute(Lexer *lex);
};

struct LexComment : public State {
    StateType Execute(Lexer *lex);
};

struct LexExclamation : public State {
    StateType Execute(Lexer *lex);
};

struct LexMultiLineComment : public State {
    StateType Execute(Lexer *lex);
};

#endif // STATE_H
