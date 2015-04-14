#ifndef STATE_H
#define STATE_H

#include <QSharedPointer>
#include "itemtype.h"

class Lexer;

struct State {
    virtual QSharedPointer<State> Execute(Lexer *lex) = 0;
    virtual ~State() {}
};

struct LexStatement : public State {
    QSharedPointer<State> Execute(Lexer *lex);
    void CheckForEquals(Lexer *lex, itemType with, itemType without);
};

struct SelectStatement : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexIdentifier : public State {
    QSharedPointer<State> Execute(Lexer *lexex);
};

struct LexQuotedIdentifier : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexBracketedIdentifier : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexNumber : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexSpace : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexString : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexUnicodeString : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexLessThan : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexComment : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexExclamation : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

struct LexMultiLineComment : public State {
    QSharedPointer<State> Execute(Lexer *lex);
};

#endif // STATE_H
