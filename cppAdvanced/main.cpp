//
//  main.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include <iostream>
#include "MovieSystem.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    MovieSystem database;
    
    database.loadEverythingFromSql();
    
    return 0;
}
