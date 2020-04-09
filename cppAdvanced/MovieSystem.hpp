//
//  movieSystem.hpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 08..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#ifndef MovieSystem_hpp
#define MovieSystem_hpp

#include <stdio.h>
#include <list>
#include "mysqlConnector.hpp"
#include "Film.hpp"
#include "Series.hpp"

class MovieSystem {
private:
    std::list<Film*> movies;
    MysqlConnector *mysql = new MysqlConnector("mysql://127.0.0.1:3306", "root", "asd123asd123", "cpp");
public:
    MovieSystem();
    ~MovieSystem();
    
    void setMovies(std::list<Film*> pMovies);
    
    void loadEverythingFromSql();
};

#endif /* movieSystem_hpp */
