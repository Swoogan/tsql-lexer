# tsql-lexer
A very simple, fast and easy to read Microsoft Transact SQL lexical analyzer.

Simple to use:

    QString query("SELECT Name, ProductNumber, ListPrice AS Price FROM Production.Product WHERE ProductLine = 'R ORDER BY Name ASC;");

    lexer l;
    l.name = "name";
    l.input = query;
    l.run();

    cout << "Results: " << endl;
    foreach (item i, l.items)
        cout << i.value << ", start: " << i.start << ", end: " << i.end << ", typecode: " << i.type << endl;

This is something I wrote in my spare time that will hopefully become part of a larger project.

