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
    delete stmt;
    delete rs;
}

std::string MysqlConnector::getUserPass(std::string username) {
    std::string password;
    
    try{
        rs = stmt->executeQuery("SELECT Password FROM Users WHERE Username = '" + username + "'");
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

User* MysqlConnector::loadUserData(std::string username) {

    try {
        rs = stmt->executeQuery("SELECT * FROM Users WHERE Username = '" + username + "'");
        
        while (rs->next()) {
            return new User(rs->getInt("ID"), rs->getString("Real_name"), rs->getString("Username"), rs->getString("email"), rs->getString("password"));
        }
        

    } catch (sql::SQLException &e) {
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
            movies.push_back(new Film(rs->getInt("ID"), rs->getString("Title"), rs->getString("Original_title"), rs->getString("Category"), rs->getDouble("Score"), rs->getInt("Watched"), rs->getInt("Lenght"), rs->getString("Audio"), rs->getString("Subtitle"), rs->getInt("Likes"), rs->getInt("Dislikes")));
        }
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    delete rs;
}

void MysqlConnector::loadAllSeries(std::list<Node*> &movies){
    // levalogatja a sorozatokat majd elmenti egy listaban
    std::list<std::string> seriesToLoad;
    try {
    rs = stmt->executeQuery("SELECT Original_title FROM Films WHERE Title REGEXP 'S[0-9][0-9]E[0-9][0-9]' GROUP BY Original_title");
    while (rs->next()) {
        seriesToLoad.push_back(rs->getString("Original_title"));
    }
    delete rs;
    } catch(sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    
    // Levalogatott sorozatok epizodjanak betoltese
    sql::PreparedStatement *prepstmt = con->prepareStatement("SELECT * FROM Films WHERE Original_title = ? ORDER BY Title");
    
    
    std::map<int, std::list<Film*>> seasonsForSeriesClass;
    std::regex reg("S[0-9][0-9]E[0-9][0-9]");
    std::smatch match;
    int seasonNumber = 0, episodeNumber = 0, prevSeasonNumber = 1;
    std::list<Film*> episodes;
    
    for (std::string &iter : seriesToLoad) {
        // TODO: tokenizalni a sorozatok reszeit
        
        prepstmt->setString(1, iter);
        
        std::string title, originalTitle, category, audio, subtitle;
        int watched = 0, likes = 0, dislikes = 0, playtime = 0, id = 0;
        double score = 0;
        
        try {
            rs = prepstmt->executeQuery();
        
            // Evad szamanak kinyerese
        
            while (rs->next()) {
                std::string cuttedTitle;
                id = rs->getInt("ID");
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
                    cuttedTitle = title.erase(match.position(),3);
                }
                if (seasonNumber != prevSeasonNumber) {
                    seasonsForSeriesClass.insert(std::make_pair(prevSeasonNumber, episodes));
                    episodes.clear();
                    episodes.push_back(new Film(id, cuttedTitle, originalTitle, category, score, watched, playtime, audio,subtitle, likes, dislikes));
                } else {
                    episodes.push_back(new Film(id, cuttedTitle,originalTitle,category,score,watched,playtime,audio,subtitle,likes,dislikes));
                }
                
                if (rs->isLast()) {
                    seasonsForSeriesClass.insert(std::make_pair(seasonNumber, episodes));
                }
                
                prevSeasonNumber = seasonNumber;
            }
        }catch (sql::SQLException &e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Error code: " << e.getErrorCode() << std::endl;
            std::cerr << "Statement: " << e.getSQLState() << std::endl;
        }
        
        movies.push_back(new Series(id, originalTitle, originalTitle, category, score, watched, playtime, audio, subtitle, likes, dislikes, seasonsForSeriesClass));
    }
    delete rs;
    delete prepstmt;
    episodes.clear();
    seasonsForSeriesClass.clear();
}

void MysqlConnector::insertEvent(int typeId, int filmId, int userId, int score) {
    sql::PreparedStatement *prepstmt = con->prepareStatement("INSERT INTO Film_events (Type_id, Film_id, User_id, Score) VALUES (?, ?, ?, ?)");
    prepstmt->setInt(1, typeId);
    prepstmt->setInt(2, filmId);
    prepstmt->setInt(3, userId);
    if (score == -1) {
        prepstmt->setNull(4, 0);
    } else { prepstmt->setInt(4, score); }
    
    try {
        prepstmt->execute();
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    
}

void MysqlConnector::updateScore(int filmId) {
    sql::PreparedStatement *prepstmt = con->prepareStatement("SELECT COUNT(ID) AS `count`, SUM(Score) AS total FROM Film_events WHERE Type_id = 4 AND Film_id = ? GROUP BY Type_id");
    
    prepstmt->setInt(1, filmId);
    
    int sumScore = 0;
    int count = 0;
    
    try {
        rs = prepstmt->executeQuery();
        
        while (rs->next()) {
            sumScore = rs->getInt("total");
            count = rs->getInt("count");
        }
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    
    double scoreToUpdate = sumScore / count;
    prepstmt = con->prepareStatement("UPDATE Films SET Score = ? WHERE ID = ?");
    
    prepstmt->setDouble(1, scoreToUpdate);
    prepstmt->setInt(2, filmId);
    
    try {
        prepstmt->executeUpdate();
    } catch (sql::SQLException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "Statement: " << e.getSQLState() << std::endl;
    }
    delete prepstmt;
    delete rs;
}

