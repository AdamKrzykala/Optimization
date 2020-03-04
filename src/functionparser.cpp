#include "functionparser.h"
#include <QDebug>

FunctionParser::FunctionParser(QObject *parent) : QObject(parent)
{
    //Initalization of x,y,z values
    T x = T(0.0);
    T y = T(0.0);
    T z = T(0.0);
    //Dynamically allocation of a symbol table
    this->symbol_table = new symbol_table_t;
    //Dynamically allocation of an expression
    this->expression = new expression_t;
    //Dynamically allocation of parser
    this->parser = new parser_t;
    //TAble of symbols filling - adding x,y,z
    this->symbol_table->add_variable("x",x);
    this->symbol_table->add_variable("y",y);
    this->symbol_table->add_variable("z",z);
    //Table of symbols registration
    expression->register_symbol_table(*symbol_table);
    //-----------------------------------------------

    std::string expression_string = "z := 2 + x - (3 * y)";
    assert(parser->compile(expression_string,*expression) && "Expression parsing ERROR!.");
    T result = expression->value();
    qDebug()<<result;
}
