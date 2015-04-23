#include <QDebug>
#include "lexer.h"

Lexer::Lexer()
{

}

Lexer::~Lexer()
{

}

void Lexer::produce(ItemType t) {
    _items.append(Item{t, lexem(), _start, _pos, lineNumber()});
    _start = _pos;
}

// next returns the next rune in the input.
QChar Lexer::next() {
    if (_pos >= _input.length()) {
        _width = 0;
        return eof;
    }

    QChar rune = _input.at(_pos);
    _width = 1;
    _pos += _width;
    return rune;
}

// peek returns but does not consume the next rune in the input.
QChar Lexer::peek() {
    QChar r = next();
    backup();
    return r;
}

int Lexer::lineNumber() const
{
    QString scanned = _input.mid(0, _pos);
    return scanned.count("\n") + 1;
}

int Lexer::column() const
{
    int index = _input.lastIndexOf("\n", _pos);
    return (index < 0) ? _pos : _pos - index;
}

StateType Lexer::setError(const QString &s, const QChar &r) {
    const QString msg = s.arg(r);
    _error = LexerError(msg, lineNumber(), column());
    return stateError;
}

StateType Lexer::setError(const QString &msg) {
    _error = LexerError(msg, lineNumber(), column());
    return stateError;
}

// accept consumes the next rune
// if it's from the valid set.
bool Lexer::accept(QString valid) {
    if (valid.indexOf(next()) >= 0) {
        return true;
    }
    backup();
    return false;
}

// acceptRun consumes a run of runes from the valid set.
void Lexer::acceptRun(QString valid) {
    while (valid.indexOf(next()) >= 0) {  }
    backup();
}

// run lexes the input by executing state functions
// until the state is stateEndProcessing.
// returns true if successful.
bool Lexer::run(QString sql) {
    _input = sql;
    _parenDepth = 0;
    _items.clear();
    _start = 0;
    _pos = 0;
    _width = 1;

    StateType type = stateLexStatement;
    while (type != stateEndProcessing) {
        State *state = _states.get(type);
        type = state->Execute(this);

        if (type == stateError)
            return false;
    }

    return true;
}
