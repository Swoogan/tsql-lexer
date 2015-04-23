#ifndef LEXER_ERROR
#define LEXER_ERROR

#include <QString>

class LexerError {
public:
    LexerError();
    LexerError(QString msg, int line, int col);
    QString toString() const;

private:
    QString message;
    int lineNumber;
    int column;

};

#endif // LEXER_ERROR

