//
//  mysqlConnector.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 03. 31..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "mysqlConnector.hpp"




MysqlConnector::MysqlConnector(std::string url, std::string username, std::string password, std::string database) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(url, username, password);
        con->setSchema(database);
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }

}

MysqlConnector::~MysqlConnector(){
    delete con;
    delete driver;
}

std::string MysqlConnector::getUserPass(std::string username) {
    std::string password;
    
    try{
    sql::Statement* stmt = con->createStatement();
    
    sql::ResultSet* rs = stmt->executeQuery("SELECT Password FROM Users WHERE Username=" + username);
    while (rs->next()) {
        password = rs->getString("Password");
    }
    
    delete stmt;
    delete rs;
        
    return password;
    } catch(sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    return nullptr;
}

void MysqlConnector::loadAllFilm(std::list<Film*> &movies) {
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *rs = stmt->executeQuery("SELECT * FROM Films WHERE Films.Title NOT REGEXP '.*E[0-9][0-9]'");
        while (rs->next()) {
            movies.push_back(new Film(rs->getString("Title"), rs->getString("Original_title"), rs->getString("Category"), rs->getDouble("Score"), rs->getInt("Watched"), rs->getInt("Lenght"), rs->getString("Audio"), rs->getString("Subtitle"), rs->getInt("Likes"), rs->getInt("Dislikes")));
//            std::cout << rs->getString("Title") << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
}

// TODO: loadAllSeries()!!!!!!
void MysqlConnector::loadAllSeries(std::list<Film*> &movies){
    // navicatben sql serveren ket select mar megvan irva levalogatashoz
}

void MysqlConnector::printAllFilm() {
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *rs = stmt->executeQuery("SELECT Title, Category FROM Films");
        while (rs->next()) {
            std::cout << rs->getString("Title") << "\t\t" << rs->getString("Category") << std::endl;
        }
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
}



