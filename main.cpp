#include <QCoreApplication>
#include <QTextStream>

#include "state.h"
#include "lexer.h"
#include "item.h"

bool run(Lexer &lex, const QString &query)
{
    QTextStream cout(stdout);
    cout << query << endl;

    bool success = lex.run(query);

    cout << "Results: " << endl;
    foreach (Item i, lex.items())
        cout << i.value << ", start: " << i.start << ", end: " << i.end << ", typecode: " << i.type << endl;

    cout << endl;

    return success;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cout(stdout);

    //QString query("SELECT * FROM table;");
    //QString query("INSERT INTO mytable VALUES (1, 2, 3)");
    //    QString query("SELECT          c.[name], [address] FROM customer c ;");
    //QString query("select number, count(*) from (select NumberOne as number from Results union all select NumberTwo as number from Results union select NumberThree as number from Results ) AllNumbers group by number order by number;");
    //QString query("SELECT DISTINCT name FROM table;");


    //QString query("SELECT Name, ProductNumber, ListPrice AS Price FROM Production.Product WHERE ProductLine = "hello" ORDER BY Name ASC;");
    //
    //QString query("SELECT 10 - 1 AS Price");
    //QString query("SELECT 10 - 1 AS Price -- this is a query");
    //QString query("SELECT 10 - 1 AS Price /* this is a query */");

    Lexer lex;

    QString query("SELECT c.[name], \"address\" FROM customer c ;");
    bool success = run(lex, query);
    if (!success)
        cout << lex.error().toString() << endl;

    query = "SELECT 10 - 1 AS Price /* this is a query */ FROM Product";
    success = run(lex, query);
    if (!success)
        cout << lex.error().toString() << endl;

    query = "SELECT Name, ProductNumber, ListPrice AS Price FROM Production.Product WHERE ProductLine = \"hello ORDER BY Name ASC;";
    success = run(lex, query);
    if (!success)
        cout << lex.error().toString() << endl;

    return a.exec();
}

