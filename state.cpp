#include "state.h"
#include "lexer.h"

StateType LexIdentifier::Execute(Lexer *lex) {
    /*
     * Valid Identifiers:
     * - Starts with Letter
     * - or _ @ or #
     * - Remaining is:
     *   - Letter
     *   - Digit
     *   - @ $ # _
     */

    for (;;) {
        QChar r = lex->next();
        if (!(r.isLetterOrNumber() || r == '@' || r == '$' || r == '#' || r == '_')) {
            lex->backup();
            QString word = lex->lexem().toLower();

            if (lex->keyword(word) > itemKeyword)
                lex->produce(lex->keyword(word));
            else
                lex->produce(itemIdentifier);

            break;
        }
    }

    return stateLexStatement;
}

// Already saw the [ character
StateType LexBracketedIdentifier::Execute(Lexer *lex) {
    const QString valid = "@$#_ ~!%^&()-{}'.\\`";
    for (;;) {
        lex->acceptRun(valid);
        QChar r = lex->next();
        if (r == eof || r == '\n')
            return lex->error("Unterminated quoted identifier %1", r);
        else if (r.isLetterOrNumber())
            continue;
        else if (r == ']')
            break;
    }

    lex->produce(itemIdentifier);
    return stateLexStatement;
}

StateType LexQuotedIdentifier::Execute(Lexer *lex) {
    const QString valid = "@$#_ ~!%^&()-{}'.\\`";
    for (;;) {
        lex->acceptRun(valid);
        QChar r = lex->next();
        if (r == eof || r == '\n')
            return lex->error("Unterminated quoted identifier %1", r);
        else if (r.isLetterOrNumber())
            continue;
        else if (r == '"')
            break;
    }

    lex->produce(itemIdentifier);
    return stateLexStatement;
}

// Already saw the ' character
StateType LexString::Execute(Lexer *lex) {
    for (;;) {
        QChar r = lex->next();
        if (r == eof || r == '\n')
            return lex->error("Unterminated quoted varchar %1", r);
        else if (r == '\'') {
            r = lex->next();
            if (r != '\'') {
                lex->backup();
                break;
            }
        }
    }

    lex->produce(itemVarchar);
    return stateLexStatement;
}

// Already saw N and know a ' character follows
StateType LexUnicodeString::Execute(Lexer *lex) {
    lex->next();  // accept the '

    for (;;) {
        QChar r = lex->next();
        if (r == eof || r == '\n')
            return lex->error("Unterminated quoted varchar %1", r);
        else if (r == '\'') {
            r = lex->next();
            if (r != '\'') {
                lex->backup();
                break;
            }
        }
    }

    lex->produce(itemVarchar);
    return stateLexStatement;
}


StateType LexNumber::Execute(Lexer *l) {    
    const QString digits = "0123456789";
    l->acceptRun(digits);

    if (l->accept("."))
        l->acceptRun(digits);

    if (l->accept("eE")) {
        l->accept("+-");
        l->acceptRun(digits);
    }

    l->produce(itemNumber);
    return stateLexStatement;
}

StateType LexSpace::Execute(Lexer *l) {
    while (l->peek().isSpace()) {
        l->next();
    }

    l->produce(itemSpace);
    return stateLexStatement;
}


StateType LexLessThan::Execute(Lexer *l) {
    QChar r = l->next();
    if (r == '>') {
        l->produce(itemNotEqual);
    }
    else if (r == '=') {
        l->produce(itemLessThanOrEequal);
    }
    else {
        l->backup();
        l->produce(itemLessThan);
    }

    return stateLexStatement;
}

StateType LexExclamation::Execute(Lexer *l) {
    QChar r = l->next();

    if (r == '>') {
        l->produce(itemNotGreaterThan);
    }
    else if (r == '<') {
        l->produce(itemNotLessThan);
    }
    else if (r == '=') {
        l->produce(itemNotEqual);
    }
    else {
        l->backup();
        l->produce(itemExclamation);
    }

    return stateLexStatement;
}

StateType LexComment::Execute(Lexer *l) {
    l->accept("-");
    for (;;) {
        QChar r = l->next();
        if (r == eof || r == '\n')
            break;
    }

    l->produce(itemComment);
    return stateLexStatement;
}

StateType LexMultiLineComment::Execute(Lexer *lex) {
    QString current = lex->clip();

    int i = current.indexOf("*/");
    if (i < 0)
        return lex->error("Unclosed comment");

    lex->forward(i + 2); // move past the '*/' ... not sure if this is unicode safe
    lex->produce(itemComment);
    return stateLexStatement;
}

/*
 * If quoted identifiers is off, strings can be in quotes: http://technet.microsoft.com/en-us/library/aa224033(v=sql.80).aspx
 */
StateType LexStatement::Execute(Lexer *lex) {
    for(;;) {
        QChar r = lex->next();
        if (r == eof)
            break;
        if (r.isSpace())
            return stateLexSpace;
        else if (r == '*')
            CheckForEquals(lex, itemMutilpyEqual, itemAsterisk);
        else if (r == ';')
            lex->produce(itemSemiColon);
        else if (r == ',')
            lex->produce(itemComma);
        else if (r == '.')
            lex->produce(itemPeriod);
        else if (r == '=')
            lex->produce(itemEqual);
        else if (r == '(') {
            lex->enterParen();
            lex->produce(itemLParen);
        }
        else if (r == ')') {
            lex->produce(itemRParen);
            lex->exitParen();
            if (lex->parenDepth() < 0) {
                return lex->error("Unexpected right paren %1", r);
            }
        }
        else if (r == '+')
            CheckForEquals(lex, itemPlusEqual, itemPlus);
        else if (r == '%')
            CheckForEquals(lex, itemModuloEqual, itemPercentSymbol);
        else if (r == '~')
            lex->produce(itemTilde);
        else if (r == '&')
            CheckForEquals(lex, itemBitwiseAndEqual, itemBitwiseAnd);
        else if (r == '|')
            CheckForEquals(lex, itemBitwiseOrEqual, itemBitwiseOr);
        else if (r == '^')
            CheckForEquals(lex, itemBitwiseXorEqual, itemBitwiseXor);
        else if (r == '>')
            CheckForEquals(lex, itemGreaterThanOrEqual, itemGreaterThan);
        else if (r == '!')
            return stateLexExclamation;
        else if (r == '<')
            return stateLexLessThan;
        else if (r == ']')
            return lex->error("Unexpected right bracket");
        else if (r == '/') {
            QChar r = lex->next();
            if (r == '=') {
                lex->produce(itemDivideEqual);
            }
            else if (r == '*') {
                return stateLexMultiLineComment;
            }
            else {
                lex->backup();
                lex->produce(itemSlash);
            }
        }
        else if (r == '-') {
            r = lex->peek();
            if (r == '-') {
                lex->backup();
                return stateLexComment;
            }
            else {
                lex->produce(itemMinus);
            }
        }
        else if (r == '[')
            return stateLexBracketedIdentifier;
        else if (r == '"')
            return stateLexQuotedIdentifier;
        else if (r == ':') {
            r = lex->next();
            if (r != ':')
                return lex->error("Expected ::");

            lex->produce(itemScopeResolution);
        }
        else if (r == '\'')
            return stateLexString;
        else if (r == 'N') {
            if (lex->peek() == '\'') {
                return stateLexUnicodeString;
            }
            return stateLexIdentifier;
        }
        else if (r.isLetter() || r == '@' || r == '#' || r == '_') {
            return stateLexIdentifier;
        }
        else if (r.isDigit()) {
            lex->backup();
            return stateLexNumber;
        }
        else
            return lex->error("Unknown token: %1", r);
    }

    if (lex->parenDepth() > 0)
        return lex->error("Unclosed left paren");

    lex->produce(itemEOF);  // Useful to make EOF a token.
    return stateEndProcessing;       // Stop the run loop.
}

void LexStatement::CheckForEquals(Lexer *lex, itemType with, itemType without) {
    QChar r = lex->next();
    if (r == '=')
        lex->produce(with);
    else {
        lex->backup();
        lex->produce(without);
    }
}


