#include "functionparser.h"

QVector<std::string>X = {"x1","x2","x3","x4","x5"};

FunctionParser::FunctionParser(QString newFunction, QObject *parent) : QObject(parent)
{
    //Dynamically allocation of a symbol table
    this->symbol_table = new symbol_table_t;

    //Dynamically allocation of an expression
    this->expression = new expression_t;

    //Dynamically allocation of parser
    this->parser = new parser_t;

    //TAble of symbols filling - adding x,y,z
    for(int i=0; i< X.length(); i++) {
        this->symbol_table->add_variable(X[i],this->x[i]);
    }

    //Table of symbols registration
    this->expression->register_symbol_table(*symbol_table);

    //-----------------------------------------------
    assert(parser->compile(newFunction.toStdString(),*this->expression)
           && "Expression parsing ERROR!.");
}

T FunctionParser::getValue(QVector<T> x)
{
    for(int i = 0; i < X.length(); i++){
        this->x[i] = T(x[i]);
    }
    return expression->value();
}
