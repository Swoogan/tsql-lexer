#include "state_collection.h"

StateCollection::StateCollection() {
}

StateCollection::~StateCollection() {
    foreach (State *s, states.values()) {
        delete s;
    }
}

State* StateCollection::get(StateType type){
    if (states.contains(type))
        return states[type];
    else {
        State *s;
        switch (type) {
        case stateLexStatement:
            s = new LexStatement();
            break;
        case stateLexSpace:
            s = new LexSpace();
            break;
        case stateLexExclamation:
            s = new LexExclamation();
            break;
        case stateLexLessThan:
            s = new LexLessThan();
            break;
        case stateLexMultiLineComment:
            s = new LexMultiLineComment();
            break;
        case stateLexComment:
            s = new LexComment();
            break;
        case stateLexBracketedIdentifier:
            s = new LexBracketedIdentifier();
            break;
        case stateLexQuotedIdentifier:
            s = new LexQuotedIdentifier();
            break;
        case stateLexString:
            s = new LexString();
            break;
        case stateLexUnicodeString:
            s = new LexUnicodeString();
            break;
        case stateLexIdentifier:
            s = new LexIdentifier();
            break;
        case stateLexNumber:
            s = new LexNumber();
            break;
	default:
	    throw;
        }
        states[type] = s;
        return s;
    }
}

