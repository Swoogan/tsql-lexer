#ifndef STATE_TYPE_H
#define STATE_TYPE_H


enum StateType {
    stateEndProcessing,
    stateLexStatement,
    stateLexSpace,
    stateLexExclamation,
    stateLexLessThan,
    stateLexMultiLineComment,
    stateLexComment,
    stateLexBracketedIdentifier,
    stateLexQuotedIdentifier,
    stateLexString,
    stateLexUnicodeString,
    stateLexIdentifier,
    stateLexNumber
};

#endif // STATE_TYPE_H
