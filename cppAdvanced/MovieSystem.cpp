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
        iter->print();
    }
}
