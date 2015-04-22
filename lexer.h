#ifndef LEXER_H
#define LEXER_H

#include <QMap>
#include <QSharedPointer>
#include "itemtype.h"
#include "state.h"
#include "item.h"
#include "state_collection.h"

const QChar eof(-1);

class Lexer {
public:
    Lexer();
    ~Lexer();

    void run(QString sql);
    QChar peek();
    QChar next();
    void produce(itemType t);
    bool accept(QString valid);
    void acceptRun(QString valid);
    StateType error(QString s, QChar r);
    StateType error(QString s);

    itemType keyword(QString name) const { return keywords[name]; }
    QString lexem() const { return _input.mid(start, pos - start); }
    QString clip() const { return _input.mid(pos); }
    QString input() const { return _input; }
    int position() const { return pos; }
    QList<Item> items() const { return _items; }
    int parenDepth() const { return _parenDepth; }
    void forward(int x) { pos += x; }
    void enterParen() { _parenDepth++; }
    void exitParen() { _parenDepth--; }

    // steps back one character. Can be
    // called only once per call of next.
    void backup() { pos -= width; }

private:
    // ignore skips over the pending input before this point.
    void ignore() { start = pos; }
    int lineNumber() const;

    StateCollection states;
    QMap<QString, itemType> keywords;
    QString name;        // used only for error reports.
    QString _input;      // the string being sZeitgeistcanned.
    QList<Item> _items;  // channel of scanned items.

    int start;       // start position of this item.
    int pos;         // current position in the input.
    int width;       // width of last rune read from input.
    int _parenDepth; // depth of the ()
};


#endif // LEXER_H
