#include "functionparser.h"
#include <QDebug>

FunctionParser::FunctionParser(QObject *parent) : QObject(parent)
{
    T x = T(0.0);
    T y = T(0.0);
    T z = T(0.0);
    this->symbol_table = new symbol_table_t;
    this->expression = new expression_t;
    this->parser = new parser_t;
    this->symbol_table->add_variable("x",x);
    this->symbol_table->add_variable("y",y);
    this->symbol_table->add_variable("z",z);
    expression->register_symbol_table(*symbol_table);
    std::string expression_string = "z := 2 + x - (3 * y)";
    if (parser->compile(expression_string,*expression))
     {
        qDebug() << "Expression parsing completed successfully.";
     }

     T result = expression->value();
     qDebug()<<result;
}
