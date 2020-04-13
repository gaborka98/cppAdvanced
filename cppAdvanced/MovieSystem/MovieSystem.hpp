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
    std::list<Node*> movies;
    MysqlConnector *mysql;
public:
    MovieSystem(MysqlConnector* &mysql);
    ~MovieSystem();
    
    void setMovies(std::list<Node*> pMovies);
    
    void refreshDatabaseFromSql();
    
    std::vector<Node*> searchInLocalDatabase(std::string);
    
    void printAllWhatIsLoad();
    void printAllSeriesEpisodes();
};

#endif /* movieSystem_hpp */
