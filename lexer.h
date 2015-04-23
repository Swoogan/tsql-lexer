#ifndef LEXER_H
#define LEXER_H

#include <QMap>
#include "item_type.h"
#include "state.h"
#include "item.h"
#include "state_collection.h"
#include "lexer_error.h"

const QChar eof(-1);

class Lexer {
public:
    Lexer();
    ~Lexer();

    bool run(QString sql);
    QChar peek();
    QChar next();
    void produce(ItemType t);
    bool accept(QString valid);
    void acceptRun(QString valid);
    StateType setError(const QString &s, const QChar &r);
    StateType setError(const QString &msg);

    ItemType keyword(QString name) const { return _keywords[name]; }
    QString lexem() const { return _input.mid(_start, _pos - _start); }
    QString clip() const { return _input.mid(_pos); }
    QString input() const { return _input; }
    int position() const { return _pos; }
    QList<Item> items() const { return _items; }
    int parenDepth() const { return _parenDepth; }
    LexerError error() const { return _error; }
    int lineNumber() const;
    int column() const;
    void forward(int x) { _pos += x; }
    void enterParen() { _parenDepth++; }
    void exitParen() { _parenDepth--; }

    // steps back one character. Can be
    // called only once per call of next.
    void backup() { _pos -= _width; }

private:
    // ignore skips over the pending input before this point.
    void ignore() { _start = _pos; }


    StateCollection _states;
    QMap<QString, ItemType> _keywords;
    QString _name;        // used only for error reports.
    QString _input;      // the string being sZeitgeistcanned.
    QList<Item> _items;  // channel of scanned items.
    LexerError _error;

    int _start;       // start position of this item.
    int _pos;         // current position in the input.
    int _width;       // width of last rune read from input.
    int _parenDepth; // depth of the ()
};


#endif // LEXER_H
