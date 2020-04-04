#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

#include <QObject>
#include <QVector>
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
    explicit FunctionParser(QString, QObject *parent = nullptr);
    T getValue(QVector<T>);

signals:

public slots:

private:
    //Table of symbolic variables (x,y,z)
    symbol_table_t *symbol_table;
    //Parsed expression
    expression_t *expression;
    //Parser object
    parser_t *parser;
    //x vector
    QVector<T> x = {0,0,0,0,0};
};

#endif // FUNCTIONPARSER_H
