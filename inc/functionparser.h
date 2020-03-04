#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

#include <QObject>
#include <cassert>
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
    //Table of symbolic variables (x,y,z)
    symbol_table_t *symbol_table;
    //Parsed expression
    expression_t *expression;
    //Parser object
    parser_t *parser;
};

#endif // FUNCTIONPARSER_H
