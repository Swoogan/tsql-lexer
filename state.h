#ifndef STATE_H
#define STATE_H

#include <QSharedPointer>
#include "itemtype.h"

struct lexer;

struct State {
    virtual QSharedPointer<State> Execute(lexer* l) = 0;
    virtual ~State() {}
};

struct LexStatement : public State {
    QSharedPointer<State> Execute(lexer* l);
    void CheckForEquals(lexer* l, itemType with, itemType without);
};

struct SelectStatement : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexIdentifier : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexQuotedIdentifier : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexBracketedIdentifier : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexNumber : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexSpace : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexString : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexUnicodeString : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexLessThan : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexComment : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexExclamation : public State {
    QSharedPointer<State> Execute(lexer* l);
};

struct LexMultiLineComment : public State {
    QSharedPointer<State> Execute(lexer* l);
};

#endif // STATE_H
