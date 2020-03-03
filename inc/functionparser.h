#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

#include <QObject>
#include "exprtk.h"

typedef double T; // numeric type (float, double, mpfr etc...)
typedef exprtk::symbol_table<T> symbol_table_t;
typedef exprtk::expression<T>     expression_t;
typedef exprtk::parser<T>             parser_t;

class FunctionParser : public QObject
{
    Q_OBJECT
public:
    explicit FunctionParser(QObject *parent = nullptr);

signals:

public slots:

private:
    symbol_table_t *symbol_table;
    expression_t *expression;
    parser_t *parser;
};

#endif // FUNCTIONPARSER_H
