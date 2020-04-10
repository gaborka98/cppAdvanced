//
//  movieSystem.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 08..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "MovieSystem.hpp"

MovieSystem::MovieSystem() {}

MovieSystem::~MovieSystem() {}

void MovieSystem::setMovies(std::list<Node*> pMovies) { movies = pMovies; }

void MovieSystem::loadEverythingFromSql() {
    mysql->loadAllFilm(movies);
    mysql->loadAllSeries(movies);
}

void MovieSystem::printAllWhatIsLoad() {
    for (auto &iter : movies) {
        std::cout << iter->getTitle()<< std::endl;
    }
}

void MovieSystem::printAllSeriesEpisodes() {
    for (auto &iter : movies) {
        if (Series* castedIter = dynamic_cast<Series*>(iter)) {
            for (auto &d : castedIter->getSeasons()) {
                std::cout << d.first << ". evad:" << std::endl;;
                for (auto &&asd : d.second) {
                    std::cout << "\t" << asd->getTitle() << std::endl;
                }
            }
        }
    }
}
