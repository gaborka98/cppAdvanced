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
        stmt = con->createStatement();
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
        rs = stmt->executeQuery("SELECT Password FROM Users WHERE Username=" + username);
    while (rs->next()) {
        password = rs->getString("Password");
    }
        delete rs;
    return password;
    } catch(sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    return nullptr;
}

void MysqlConnector::loadAllFilm(std::list<Node*> &movies) {
    try {
        rs = stmt->executeQuery("SELECT * FROM Films WHERE Films.Title NOT REGEXP 'E[0-9][0-9]'");
        while (rs->next()) {
            movies.push_back(new Film(rs->getString("Title"), rs->getString("Original_title"), rs->getString("Category"), rs->getDouble("Score"), rs->getInt("Watched"), rs->getInt("Lenght"), rs->getString("Audio"), rs->getString("Subtitle"), rs->getInt("Likes"), rs->getInt("Dislikes")));
        }
        delete rs;
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
}

void MysqlConnector::loadAllSeries(std::list<Node*> &movies){
    // levalogatja a sorozatokat majd elmenti egy listaban
    rs = stmt->executeQuery("SELECT Original_title FROM Films WHERE Title REGEXP 'S[0-9][0-9]E[0-9][0-9]' GROUP BY Original_title");
    std::list<std::string> seriesToLoad;
    while (rs->next()) {
        seriesToLoad.push_back(rs->getString("Original_title"));
    }
    delete rs;
    
    // Levalogatott sorozatok epizodjanak betoltese
    sql::PreparedStatement *prepstmt = con->prepareStatement("SELECT * FROM Films WHERE Original_title = ?");
    std::map<int, std::list<Film*>> seasonsForSeriesClass;
    
    for (std::string &iter : seriesToLoad) {
        // TODO: tokenizalni a sorozatok reszeit
        
        prepstmt->setString(1, iter);
        rs = prepstmt->executeQuery();
        
        // Evad szamanak kinyerese
        std::regex reg("S[0-9][0-9]E[0-9[0-9]]");
        std::smatch match;
        
        int seasonNumber = -1, episodeNumber = -1;
        
        std::list<Film*> episodes;
        
        std::string title, originalTitle, category, audio, subtitle;
        int watched = 0, likes = 0, dislikes = 0, playtime = 0;
        double score = 0;
        
        while (rs->next()) {
            int previusSeasionNumber;
            
            title = rs->getString("Title");
            originalTitle = rs->getString("Original_title");
            category = rs->getString("Category");
            score = rs->getDouble("Score");
            watched = rs->getInt("Watched");
            playtime = rs->getInt("Lenght");
            audio = rs->getString("Audio");
            subtitle = rs->getString("Subtitle");
            likes = rs->getInt("Likes");
            dislikes = rs->getInt("Dislikes");
            
            if (std::regex_search(title, match, reg)) {
                seasonNumber = std::stoi(title.substr(match.position() + 1, 2));
                episodeNumber = std::stoi(title.substr(match.position() + 4, 2));
            }
            if (seasonNumber != previusSeasionNumber) {
                seasonsForSeriesClass.insert(std::make_pair(previusSeasionNumber, episodes));
            } else {episodes.push_back(new Film(title,originalTitle,category,score,watched,playtime,audio,subtitle,likes,dislikes));}
            previusSeasionNumber = seasonNumber;
        }
        
        seasonsForSeriesClass.insert(std::make_pair(seasonNumber, episodes));
        
        movies.push_back(new Series(originalTitle, originalTitle, category, score, watched, playtime, audio, subtitle, likes, dislikes, seasonsForSeriesClass));
        delete rs;
    }
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



