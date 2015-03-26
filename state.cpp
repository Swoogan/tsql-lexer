#include "state.h"
#include "lexer.h"


QSharedPointer<State> LexIdentifier::Execute(lexer *l) {
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
        QChar r = l->next();
        if (!(r.isLetterOrNumber() || r == '@' || r == '$' || r == '#' || r == '_')) {
            l->backup();
            QString word = l->lexem().toLower();

            if (l->keywords[word] > itemKeyword)
                l->emitt(l->keywords[word]);
            else
                l->emitt(itemIdentifier);

            break;
        }
    }

    return QSharedPointer<LexStatement>(new LexStatement());
}

// Already saw the [ character
QSharedPointer<State> LexBracketedIdentifier::Execute(lexer *l) {
    const QString valid = "@$#_ ~!%^&()-{}'.\`";
    for (;;) {
        l->acceptRun(valid);
        QChar r = l->next();
        if (r == eof || r == '\n')
            return l->error("Unterminated quoted identifier %1", r);
        else if (r.isLetterOrNumber())
            continue;
        else if (r == ']')
            break;
    }

    l->emitt(itemIdentifier);
    return QSharedPointer<LexStatement>(new LexStatement());
}

QSharedPointer<State> LexQuotedIdentifier::Execute(lexer *l) {
    const QString valid = "@$#_ ~!%^&()-{}'.\`";
    for (;;) {
        l->acceptRun(valid);
        QChar r = l->next();
        if (r == eof || r == '\n')
            return l->error("Unterminated quoted identifier %1", r);
        else if (r.isLetterOrNumber())
            continue;
        else if (r == '"')
            break;
    }

    l->emitt(itemIdentifier);
    return QSharedPointer<LexStatement>(new LexStatement());
}

// Already saw the ' character
QSharedPointer<State> LexString::Execute(lexer *l) {
    for (;;) {
        QChar r = l->next();
        if (r == eof || r == '\n')
            return l->error("Unterminated quoted varchar %1", r);
        else if (r == '\'') {
            r = l->next();
            if (r != '\'') {
                l->backup();
                break;
            }
        }
    }

    l->emitt(itemVarchar);
    return QSharedPointer<LexStatement>(new LexStatement());
}

// Already saw N and know a ' character follows
QSharedPointer<State> LexUnicodeString::Execute(lexer *l) {
    l->next();  // accept the '

    for (;;) {
        QChar r = l->next();
        if (r == eof || r == '\n')
            return l->error("Unterminated quoted varchar %1", r);
        else if (r == '\'') {
            r = l->next();
            if (r != '\'') {
                l->backup();
                break;
            }
        }
    }

    l->emitt(itemVarchar);
    return QSharedPointer<LexStatement>(new LexStatement());
}


QSharedPointer<State> LexNumber::Execute(lexer *l) {    
    const QString digits = "0123456789";
    l->acceptRun(digits);

    if (l->accept("."))
        l->acceptRun(digits);

    if (l->accept("eE")) {
        l->accept("+-");
        l->acceptRun(digits);
    }

    l->emitt(itemNumber);
    return QSharedPointer<LexStatement>(new LexStatement());
}

QSharedPointer<State> LexSpace::Execute(lexer *l) {
    while (l->peek().isSpace()) {
        l->next();
    }

    l->emitt(itemSpace);
    return QSharedPointer<LexStatement>(new LexStatement());
}


QSharedPointer<State> LexLessThan::Execute(lexer *l) {
    QChar r = l->next();
    if (r == '>') {
        l->emitt(itemNotEqual);
    }
    else if (r == '=') {
        l->emitt(itemLessThanOrEequal);
    }
    else {
        l->backup();
        l->emitt(itemLessThan);
    }

    return QSharedPointer<LexStatement>(new LexStatement());
}

QSharedPointer<State> LexExclamation::Execute(lexer *l) {
    QChar r = l->next();

    if (r == '>') {
        l->emitt(itemNotGreaterThan);
    }
    else if (r == '<') {
        l->emitt(itemNotLessThan);
    }
    else if (r == '=') {
        l->emitt(itemNotEqual);
    }
    else {
        l->backup();
        l->emitt(itemExclamation);
    }

    return QSharedPointer<LexStatement>(new LexStatement());
}

QSharedPointer<State> LexComment::Execute(lexer *l) {
    l->accept("-");
    for (;;) {
        QChar r = l->next();
        if (r == eof || r == '\n')
            break;
    }

    l->emitt(itemComment);
    return QSharedPointer<LexStatement>(new LexStatement());
}

QSharedPointer<State> LexMultiLineComment::Execute(lexer *l) {
    QString current = l->input.mid(l->pos);

    int i = current.indexOf("*/");
    if (i < 0)
        return l->error("Unclosed comment");

    l->pos += i + 2; // move past the */ ... not sure if this is unicode safe

    l->emitt(itemComment);
    return QSharedPointer<LexStatement>(new LexStatement());
}

/*
 * If quoted identifiers is off, strings can be in quotes: http://technet.microsoft.com/en-us/library/aa224033(v=sql.80).aspx
 */
QSharedPointer<State> LexStatement::Execute(lexer* l) {
    for(;;) {
        QChar r = l->next();
        if (r == eof)
            break;
        if (r.isSpace())
            return QSharedPointer<LexSpace>(new LexSpace());
        else if (r == '*')
            CheckForEquals(l, itemMutilpyEqual, itemAsterisk);
        else if (r == ';')
            l->emitt(itemSemiColon);
        else if (r == ',')
            l->emitt(itemComma);
        else if (r == '.')
            l->emitt(itemPeriod);
        else if (r == '=')
            l->emitt(itemEqual);
        else if (r == '(') {
            l->parenDepth++;
            l->emitt(itemLParen);
        }
        else if (r == ')') {
            l->emitt(itemRParen);
            l->parenDepth--;
            if (l->parenDepth < 0) {
                return l->error("Unexpected right paren %1", r);
            }
        }
        else if (r == '+')
            CheckForEquals(l, itemPlusEqual, itemPlus);        
        else if (r == '%')
            CheckForEquals(l, itemModuloEqual, itemPercentSymbol);
        else if (r == '~')
            l->emitt(itemTilde);
        else if (r == '&')
            CheckForEquals(l, itemBitwiseAndEqual, itemBitwiseAnd);
        else if (r == '|')
            CheckForEquals(l, itemBitwiseOrEqual, itemBitwiseOr);
        else if (r == '^')
            CheckForEquals(l, itemBitwiseXorEqual, itemBitwiseXor);
        else if (r == '>')
            CheckForEquals(l, itemGreaterThanOrEqual, itemGreaterThan);
        else if (r == '!')
            return QSharedPointer<LexExclamation>(new LexExclamation());
        else if (r == '<')
            return QSharedPointer<LexLessThan>(new LexLessThan());
        else if (r == ']')
            return l->error("Unexpected right bracket");
        else if (r == '/') {
            QChar r = l->next();
            if (r == '=') {
                l->emitt(itemDivideEqual);
            }
            else if (r == '*') {
                return QSharedPointer<LexMultiLineComment>(new LexMultiLineComment());
            }
            else {
                l->backup();
                l->emitt(itemSlash);
            }
        }
        else if (r == '-') {
            r = l->peek();
            if (r == '-') {
                l->backup();
                return QSharedPointer<LexComment>(new LexComment());
            }
            else {
                l->emitt(itemMinus);
            }
        }
        else if (r == '[')
            return QSharedPointer<LexBracketedIdentifier>(new LexBracketedIdentifier());
        else if (r == '"')
            return QSharedPointer<LexQuotedIdentifier>(new LexQuotedIdentifier());
        else if (r == ':') {
            r = l->next();
            if (r != ':')
                return l->error("Expected ::");

            l->emitt(itemScopeResolution);
        }
        else if (r == '\'')
            return QSharedPointer<LexString>(new LexString());
        else if (r == 'N') {
            if (l->peek() == '\'') {                
                return QSharedPointer<LexUnicodeString>(new LexUnicodeString());
            }

            return QSharedPointer<LexIdentifier>(new LexIdentifier());

        }
        else if (r.isLetter() || r == '@' || r == '#' || r == '_') {
            return QSharedPointer<LexIdentifier>(new LexIdentifier());
        }
        else if (r.isDigit()) {
            l->backup();
            return QSharedPointer<LexNumber>(new LexNumber());
        }
        else
            return l->error("Unknown token: %1", r);
    }

    if (l->parenDepth > 0)
        return l->error("Unclosed left paren");

    l->emitt(itemEOF);  // Useful to make EOF a token.
    return QSharedPointer<State>();       // Stop the run loop.
}

void LexStatement::CheckForEquals(lexer* l, itemType with, itemType without) {
    QChar r = l->next();
    if (r == '=')
        l->emitt(with);
    else {
        l->backup();
        l->emitt(without);
    }
}


