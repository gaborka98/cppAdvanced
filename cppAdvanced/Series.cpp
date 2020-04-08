//
//  Series.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Series.hpp"


Series::Series(std::string title, std::string originalTitle, std::string category, double score, int watched, int playtime, std::string audio, std::string subtitle, int likes, int dislikes) : Film(title, originalTitle, category, score, watched, playtime, audio, subtitle, likes, dislikes) {}

Series::~Series() {
    for (auto &&d : seasons) {
        for (auto &&e : d.second) {
            delete e;
        }
        d.second.clear();
    }
    seasons.clear();
}

void Series::setSeasons(std::map<int, std::list<Film*>> pSeasons) { seasons = pSeasons; }
