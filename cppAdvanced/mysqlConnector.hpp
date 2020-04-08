//
//  mysqlConnector.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef mysqlConnector_hpp
#define mysqlConnector_hpp

#include <stdio.h>
#include <string>
#include <mysql/jdbc.h>
#include <map>
#include <list>

#include "Film.hpp"
#include "Series.hpp"

class MysqlConnector{
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
public:
    MysqlConnector(std::string url, std::string username, std::string password, std::string database);
    ~MysqlConnector();
    
    std::string getUserPass(std::string username);
    void loadAllFilm(std::list<Film*> &);
    void loadAllSeries(std::list<Film*> &);
    
    void printAllFilm();
    
    
};


#endif /* mysqlConnector_hpp */
