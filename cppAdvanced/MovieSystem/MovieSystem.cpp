//
//  movieSystem.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 08..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "MovieSystem.hpp"

MovieSystem::MovieSystem(MysqlConnector* &mysql): mysql(mysql) {}

MovieSystem::~MovieSystem() {}

void MovieSystem::setMovies(std::list<Node*> pMovies) { movies = pMovies; }

void MovieSystem::refreshDatabaseFromSql() {
    movies.clear();
    mysql->loadAllFilm(movies);
    mysql->loadAllSeries(movies);
}

void MovieSystem::printAllWhatIsLoad() {
    for (auto &iter : movies) {
        iter->print();
    }
}

std::vector<Node*> MovieSystem::searchInLocalDatabase(std::string title) {
    std::vector<Node*> toReturn;
    std::smatch match;
    
    for (Node* &iter : movies) {
        std::string lowerSearchingTitle = title;
        std::string lowerIterTitle = iter->getTitle();
        
        std::regex regTitle(lowerSearchingTitle);
        
        std::transform(lowerIterTitle.begin(), lowerIterTitle.end(), lowerIterTitle.begin(), ::tolower);
        std::transform(lowerSearchingTitle.begin(), lowerSearchingTitle.end(), lowerSearchingTitle.begin(), ::tolower);
        
        
        if (std::regex_search(lowerIterTitle, match, regTitle)) {
            toReturn.push_back(iter);
        }
    }
    return toReturn;
}

void MovieSystem::deleteFromLocalDatabase(Node* selected) {
    movies.remove(selected);
    delete selected;
}

void MovieSystem::addFilm(int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int dislikes) {
    movies.push_back(new Film(id, title, originalTitle, category, score, watched, playTime, audio, subtitle, likes, dislikes));
}
void MovieSystem::addSeries(int id, std::string title, std::string originalTitle, std::string category, double score, int watched, int playTime, std::string audio, std::string subtitle, int likes, int dislikes, std::map<int, std::list<Film*>> seasons) {
    movies.push_back(new Series(id,title,originalTitle,category,score,watched,playTime,audio,subtitle,likes,dislikes, seasons));
}
