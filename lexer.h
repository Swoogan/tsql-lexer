#ifndef LEXER_H
#define LEXER_H

#include <QMap>
#include <QSharedPointer>
#include "itemtype.h"
#include "state.h"

struct item {
    itemType type;  // Type, such as itemNumber.
    QString value;  // Value, such as "23.2".
    int start;      // Position the token starts
    int end;        // Position the token ends
    int lineNumber; // Line the token is on
};

const QChar eof(-1);

struct lexer {
    lexer();

    QMap<QString, itemType> keywords;
    QString name;    // used only for error reports.
    QString input;    // the string being sZeitgeistcanned.
    int start = 0;       // start position of this item.
    int pos = 0;       // current position in the input.
    int width = 1;       // width of last rune read from input.
    int parenDepth = 0; // depth of the ()
    QList<item> items; // channel of scanned items.

    void run();
    void ignore();
    void backup();
    void emitt(itemType t);
    QChar next();
    QSharedPointer<State> error(QString s, QChar r);
    QSharedPointer<State> error(QString s);
    bool accept(QString valid);
    void acceptRun(QString valid);
    QString lexem();
    QChar peek();
    int lineNumber();
};


#endif // LEXER_H
