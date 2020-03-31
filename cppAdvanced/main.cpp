//
//  main.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include <iostream>
#include <mysql/jdbc.h>


using namespace std;

int main(int argc, const char * argv[]) {
    
    try {
        sql::Driver *driver;
        sql::Connection *conn;
        sql::Statement *stmt;
        sql::ResultSet *rs;
        
        driver = sql::mysql::get_driver_instance();
        conn = driver->connect("tcp://gaborka98.mooo.com:3306", "projekt", "projekt123");
        conn->setSchema("cpp");
        
        stmt = conn->createStatement();
        rs = stmt->executeQuery("SELECT Title, Category FROM Films");
        
        while (rs->next()) {
            cout<< rs->getString("Title") << "\t" << rs->getString("Category") << endl;
        }
        
        
        delete conn;
        delete stmt;
        delete rs;
    } catch (sql::SQLException &e) {
        cerr << e.what() << endl;
    }
    
    
    
    return 0;
}
