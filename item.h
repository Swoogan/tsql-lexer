#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include "item_type.h"

struct Item
{
    ItemType type;  // Type, such as itemNumber.
    QString value;  // Value, such as "23.2".
    int start;      // Position the token starts
    int end;        // Position the token ends
    int lineNumber; // Line the token is on
};

#endif // ITEM_H
