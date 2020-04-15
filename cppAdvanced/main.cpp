//
//  main.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include <iostream>
#include "MovieSystem/MovieSystem.hpp"
#include "mysqlConnector.hpp"
#include "menuSystem.hpp"
#include "LoginSystem/Login.hpp"

int main(int argc, const char * argv[]) {
    MysqlConnector* mysql = new MysqlConnector();
    MovieSystem* database = new MovieSystem(mysql);
    User* loggedInUser = loginProcess(mysql);
    
    database->refreshDatabaseFromSql();
//    database->printAllWhatIsLoad();
    
    printMenu(database, mysql, loggedInUser);
    
    
    return 0;
}
