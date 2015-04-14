#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "state.h"
#include "lexer.h"
#include "item.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QString query("SELECT * FROM table;");
    //QString query("INSERT INTO mytable VALUES (1, 2, 3)");
//    QString query("SELECT          c.[name], [address] FROM customer c ;");
    //QString query("select number, count(*) from (select NumberOne as number from Results union all select NumberTwo as number from Results union select NumberThree as number from Results ) AllNumbers group by number order by number;");
    //QString query("SELECT DISTINCT name FROM table;");


    //QString query("SELECT Name, ProductNumber, ListPrice AS Price FROM Production.Product WHERE ProductLine = 'R''hello''R' ORDER BY Name ASC;");
    //QString query("SELECT Name, ProductNumber, ListPrice AS Price FROM Production.Product WHERE ProductLine = 'R ORDER BY Name ASC;");
    //QString query("SELECT 10 - 1 AS Price");
    //QString query("SELECT 10 - 1 AS Price -- this is a query");
    //QString query("SELECT 10 - 1 AS Price /* this is a query */");
    //QString query("SELECT 10 - 1 AS Price /* this is a query */ FROM Product");

    QString query("SELECT c.[name], \"address\" FROM customer c ;");

    QTextStream cout(stdout);
    cout << query << endl;

    Lexer lex(query);
    lex.run();

    cout << "Results: " << endl;
    foreach (Item i, lex.items())
        cout << i.value << ", start: " << i.start << ", end: " << i.end << ", typecode: " << i.type << endl;

    return a.exec();
}
