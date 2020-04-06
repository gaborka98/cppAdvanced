//
//  main.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include <iostream>
#include "mysqlConnector.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    MysqlConnector *mysql = new MysqlConnector("mysql://127.0.0.1:3306", "root", "Gaborka11", "cpp");
    mysql->loadAllFilm();
    
    
    
    
    return 0;
}
