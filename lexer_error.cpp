#include "lexer_error.h"

LexerError::LexerError()
{

}

LexerError::LexerError(QString msg, int line, int col) :
    message(msg), lineNumber(line), column(col)
{

}

QString LexerError::toString() const
{
    const QString fmt("%1 at (%2, %3)");
    return fmt.arg(message).arg(lineNumber).arg(column);
}
