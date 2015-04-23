#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <QHash>
#include <QString>
#include "item_type.h"

class Keywords
{
public:
    Keywords();
    ~Keywords();

private:
    QHash<QString, ItemType> _keywords;
};

#endif // KEYWORDS_H
