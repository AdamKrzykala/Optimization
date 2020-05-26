//
//  Math_Parser.cpp
//  TiMO_Projekt
//
//  Created by Michal on 04/03/2020.
//  Copyright © 2020 Michal_Nowak & Kacper_Stenka. All rights reserved.
//

#include "Math_Parser.hpp"

// --------------------------------------------------------------------

Math_Parser::Math_Parser() {

}

// --------------------------------------------------------------------

Math_Parser::~Math_Parser() {
    
}

// --------------------------------------------------------------------

void Math_Parser::Math_Parser_Add_Expression(string expression) {
    
    Expression_String = expression;
}

// --------------------------------------------------------------------

void Math_Parser::Math_Parser_Clear_Expression() {
    
    Expression_String.clear();
    Number_Of_Variables = 0;
}

// --------------------------------------------------------------------

float Math_Parser::Math_Parser_Get_Expression_Value() {
    
    return Expression_Value;
}

// --------------------------------------------------------------------

void Math_Parser::Math_Parser_Add_Variable(string variable_key, float variable_value) {
    
    Variable_Key_List.push_back(variable_key);
    Variable_Value_List.push_back(variable_value);
    
    Number_Of_Variables++;
}

// --------------------------------------------------------------------

void Math_Parser::Math_Parser_Calculate() {
    
    exprtk::symbol_table<float> Symbol_Table;
    exprtk::expression<float>   Expression;
    exprtk::parser<float>       Parser;
    
    for(int i = 0; i < Number_Of_Variables; ++i) {
        
        Symbol_Table.add_variable( Variable_Key_List[i], Variable_Value_List[i] );
    }
    
    Variable_Key_List.clear();
    Variable_Value_List.clear();
    Number_Of_Variables = 0;
    
    Expression.register_symbol_table(Symbol_Table);
    Parser.compile(Expression_String,Expression);
    
    Expression_Value = Expression.value();
}

// --------------------------------------------------------------------
