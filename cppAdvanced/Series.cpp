//
//  Series.cpp
//  cppAdvanced
//
//  Created by Gábor Horváth on 2020. 04. 06..
//  Copyright © 2020. Gábor Horváth. All rights reserved.
//

#include "Series.hpp"


Series::Series(std::string title, std::string category, std::map<int, std::list<Film*>> seasons) : Film(title, category),  seasons(seasons){}

Series::~Series() {
    for (auto &&d : seasons) {
        for (auto &&e : d.second) {
            delete e;
        }
        d.second.clear();
    }
    seasons.clear();
}

