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

void MovieSystem::loadEverythingFromSql() {
    mysql->loadAllFilm(movies);
    mysql->loadAllSeries(movies);
}

void MovieSystem::printAllWhatIsLoad() {
    for (auto &iter : movies) {
        iter->print();
    }
}

std::list<Node*> MovieSystem::searchInLocalDatabase(std::string title) {
    std::list<Node*> toReturn;
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
