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
#include <regex>

#include "secrets.hpp"
#include "MovieSystem/Film.hpp"
#include "MovieSystem/Series.hpp"
#include "LoginSystem/User.hpp"

class MysqlConnector{
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *rs;
public:
    MysqlConnector();
    ~MysqlConnector();
    
    // LoginSystem
    std::string getUserPass(std::string username);
    User* loadUserData(std::string username);
    
    // MovieSystem
    void loadAllFilm(std::list<Node*> &);
    void loadAllSeries(std::list<Node*> &);
    void loadWatchedMovies(User* loginUser);
    
    std::list<Node*> searchFilms(std::string title);
    void insertEvent(int typeId, int filmId, int userId, int score = -1);
    void updateScore(int filmId);
    void updateWatched(int filmId);
    void updateLikes(int filmId);
    void updateDislikes(int filmId);
    int addToDatabase(std::string title, std::string originalTitle, std::string category, int playTime, std::string audio, std::string subtitle);
    std::vector<std::string> selectMaxWatchedCategoryForRandomSelect(User* loginUser);
    
    int getLastId();
    void deleteFromDatabase(int filmId);
    
    void printAllFilm();
    
    
};


#endif /* mysqlConnector_hpp */
