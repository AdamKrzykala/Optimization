//
//  Math_Parser.hpp
//  TiMO_Projekt
//
//  Created by Michal_Nowak & Kacper_Stenka on 04/03/2020.
//  Copyright © 2020 Michal_Nowak & Kacper_Stenka. All rights reserved.
//

#ifndef Math_Parser_hpp
#define Math_Parser_hpp

#include <stdio.h>
#include <iostream>
#include "exprtk.hpp"

using namespace std;

class Math_Parser {

private:
    
    string Expression_String;
    float Expression_Value;
    
    int Number_Of_Variables;
    vector<string> Variable_Key_List;
    vector<float> Variable_Value_List;
    
protected:
    
public:
    Math_Parser();
    ~Math_Parser();
    
    void Math_Parser_Calculate();
    
    void Math_Parser_Add_Expression(string expression);
    void Math_Parser_Clear_Expression();
    float Math_Parser_Get_Expression_Value();
    
    void Math_Parser_Add_Variable(string variable_key, float variable_value);
};

#endif /* Math_Parser_hpp */
